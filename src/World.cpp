#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "sequence.hpp"

#include "Building.hpp"
#include "FontManager.hpp"
#include "Interactable.hpp"
#include "MapResource.hpp"
#include "NPC.hpp"
#include "Presenter.hpp"
#include "TextureManager.hpp"
#include "Tile.hpp"
#include "MapObject.hpp"
#include "Campfire.hpp"


struct CurrentDrawable {
    const sf::Drawable* drawable;
    sf::RenderStates states;
    float z;
};

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform isoMatrix;
    isoMatrix.scale({1.0f, ISO_SCALE_Y}); 
    isoMatrix.rotate(sf::degrees(45.0f));

    sf::RenderStates tileStates = states;
    tileStates.transform *= isoMatrix;
    
    sf::Vector2f pPos = player.get_central_point();
    
    float size_x = target.getView().getSize().x;
    float size_y = target.getView().getSize().y;
    float min_r = 4;
    float radius = std::max({size_x/2, size_y/2/ISO_SCALE_Y, min_r});
    float margin = 1.5; // > sqrt(2);

    int start_x = std::max(0, (int)floor(pPos.x - radius * margin));
    int end_x = std::min(width, (int)ceil(pPos.x + radius * margin));
    int start_y = std::max(0, (int)floor(pPos.y - radius * margin));
    int end_y = std::min(height, (int)ceil(pPos.y + radius * margin));
    
    Sequence<CurrentDrawable> draw_order;
    
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            tiles[y][x].sprite.setPosition({(float)x, (float)y});
            target.draw(tiles[y][x].sprite, tileStates);
            
            /*if (tiles[y][x].map_object != nullptr) {
                MapObject* obj = tiles[y][x].map_object;
                sf::Vector2f logicPos = {(float)x, (float)y};
                sf::Vector2f isoPos = isoMatrix.transformPoint(logicPos);
                sf::RenderStates objStates = states;
                objStates.transform.translate(isoPos);
                
                // (x, y) is the coords of the on-screen top corner of the tile.
                // (x+0.5, y+0.5) is the coords of the tile center, which is 1.f further at z. 
                draw_order.push_back({obj, objStates, (float)(x+y)+1.f});
            }*/
        }
    }
    
    sf::Vector2f playerLogicPos = player.getPosition();
    sf::Vector2f playerIsoPos = isoMatrix.transformPoint(playerLogicPos);

    sf::RenderStates playerStates = states;
    
    playerStates.transform.translate(playerIsoPos);
    playerStates.transform.translate(-playerLogicPos);
    
    draw_order.push_back({&player, playerStates, playerLogicPos.x + playerLogicPos.y});
    
    for (MapObject* obj : map_objects) {
        sf::Vector2f logicPos = static_cast<sf::Vector2f>(obj->get_pos());
        if ((logicPos - playerLogicPos).length() < 1.5f*(radius + obj->get_ingame_height())) {
            sf::Vector2f isoPos = isoMatrix.transformPoint(logicPos);
            sf::RenderStates objStates = states;
            objStates.transform.translate(isoPos);
            
            // (x, y) is the coords of the on-screen top corner of the tile.
            // (x+0.5, y+0.5) is the coords of the tile center, which is 1.f further at z. 
            draw_order.push_back({obj, objStates, (float)(logicPos.x + logicPos.y) + 1.f});
        }
    }
    
    
    
    // Draw all z-sorted objects
    draw_order.sort([](const CurrentDrawable& a, const CurrentDrawable& b) -> bool {return a.z < b.z;});
    
    for (CurrentDrawable& a : draw_order) {
        target.draw(*a.drawable, a.states);
    }
    
    
    
    for (Interactable* inter : interactables) {
        sf::Vector2f iLogicPos = inter->get_interact_pos();
        
        if ((iLogicPos - player.getPosition()).length() <= inter->get_interact_distance()) {
            sf::Vector2f iIsoPos = isoMatrix.transformPoint(iLogicPos);
            sf::RenderStates iStates = states;
            iStates.transform.translate(iIsoPos);
            iStates.transform.translate(-iLogicPos);
            target.draw(*inter, iStates);
        }
    }
}



sf::Vector2f World::get_iso_pos(sf::Vector2f logicPos) {
    sf::Transform isoMatrix;
    isoMatrix.scale({1.0f, ISO_SCALE_Y}); 
    isoMatrix.rotate(sf::degrees(45.0f));
    
    return isoMatrix.transformPoint(logicPos);
}

World::World(int _width, int _height):
    player(this, sf::Vector2f(0, _height/2)),
    width(_width), height(_height),
    map_objects()
{
    const int road_y = height/2;
    const int mess_x = height*3/4;
    
    
    
    tiles = new Tile*[height];
    
    for (int y=0; y<height; ++y) {
        tiles[y] = new Tile[width];
        for (int x=0; x<height; ++x) {
            if ((x == 10 && y > road_y && y < road_y + 10) || (x == 1 && y == road_y + 1)) {
                tiles[y][x] = Tile(this, 6);
            }
            else if (abs(x - mess_x) < road_width/2) {
                tiles[y][x] = Tile(this, (x*x*17+x*5+y*29+x*y+2)%7+0);
            }
            else if (abs(y - road_y) < road_width/2) {
                tiles[y][x] = Tile(this, 3);
            }
            else {
                tiles[y][x] = Tile(this, 1);
            }
        }
    }
    
    
    
    spawn_map_resource(new BirchNPC(this, {4, road_y + 10}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 50, 8));
    spawn_map_resource(new BirchNPC(this, {7, road_y + 13}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 50, 8));
    spawn_map_resource(new BirchNPC(this, {10, road_y + 14}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 50, 8));
    spawn_map_resource(new BirchNPC(this, {4, road_y + 15}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 50, 8));
    
    spawn_map_resource(new BirchNPC(this, {18, road_y + 15}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 50, 8));
    spawn_map_resource(new BirchNPC(this, {17, road_y + 15}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 10, 3));
    spawn_map_resource(new BirchNPC(this, {19, road_y + 15}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 10, 3));
    spawn_map_resource(new BirchNPC(this, {18, road_y + 16}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 10, 3));
    spawn_map_resource(new BirchNPC(this, {490, road_y - 16}, Tx["Assets/Sprites/MapObjects/birch.png"], "birch_juice", 10, 3));
    
    spawn_map_resource(new BirchNPC(this, {5, road_y - 12}, Tx["Assets/Sprites/MapObjects/stones.png"], "stone", 20, 1));
    spawn_map_resource(new BirchNPC(this, {8, road_y - 10}, Tx["Assets/Sprites/MapObjects/stones.png"], "stone", 20, 1));
    spawn_map_resource(new BirchNPC(this, {9, road_y - 14}, Tx["Assets/Sprites/MapObjects/stones.png"], "stone", 20, 1));

    spawn_building(new Campfire(this, {5, 250}));
    
    
    
    player_economy = new Economy;
}

World::~World() {
    for (int y=0; y<height; ++y) {
        delete[] tiles[y];
    }
    delete[] tiles;
    
    for (int i=0; i<map_objects.get_size(); ++i) {
        delete map_objects[i];
    }
    
    delete player_economy;
}

void World::update(float deltaTime) {
    player.update(deltaTime);
    
    for (MapObject* x : map_objects) {
        x->update(deltaTime);
    }
    
    time += deltaTime;
}



void World::spawn_building(Building* building) {
    map_objects.push_back(building);
    
    sf::Vector2i pos = building->get_pos();
    tiles[pos.y][pos.x].map_object = building;
    tiles[pos.y][pos.x].is_passable = false;
}

void World::spawn_map_resource(MapResource* map_resource) {
    map_objects.push_back(map_resource);
    interactables.push_back(map_resource);
    
    sf::Vector2i pos = map_resource->get_pos();
    tiles[pos.y][pos.x].map_object = map_resource;
    tiles[pos.y][pos.x].is_passable = false;
}

void World::spawn_npc(NPC* npc) {
    npcs.push_back(npc);
    interactables.push_back(npc);
}