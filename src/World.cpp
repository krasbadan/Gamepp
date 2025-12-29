#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "sequence.hpp"

#include "Building.hpp"
#include "Interactable.hpp"
#include "MapResource.hpp"
#include "NPC.hpp"
#include "TextureManager.hpp"
#include "Tile.hpp"
#include "MapObject.hpp"



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
            
            if (tiles[y][x].map_object != nullptr) {
                MapObject* obj = tiles[y][x].map_object;
                sf::Vector2f logicPos = {(float)x, (float)y};
                sf::Vector2f isoPos = isoMatrix.transformPoint(logicPos);
                sf::RenderStates objStates = states;
                objStates.transform.translate(isoPos);
                
                // (x, y) is the coords of the on-screen top corner of the tile.
                // (x+0.5, y+0.5) is the coords of the tile center, which is 1.f further at z. 
                draw_order.push_back({obj, objStates, (float)(x+y)+1.f});
            }
        }
    }

    sf::Vector2f playerLogicPos = player.getPosition();
    sf::Vector2f playerIsoPos = isoMatrix.transformPoint(playerLogicPos);

    sf::RenderStates playerStates = states;
    
    playerStates.transform.translate(playerIsoPos);
    playerStates.transform.translate(-playerLogicPos);
    
    draw_order.push_back({&player, playerStates, playerLogicPos.x + playerLogicPos.y});
    
    
    
    draw_order.sort([](const CurrentDrawable& a, const CurrentDrawable& b) -> bool {return a.z < b.z;});
    
    for (CurrentDrawable& a : draw_order) {
        target.draw(*a.drawable, a.states);
    }
    
    
    
    for (Interactable* a : interactables) {
        sf::Vector2f iLogicPos = a->get_interact_pos();
        
        if ((iLogicPos - player.getPosition()).length() <= a->get_interact_distance()) {
            sf::Vector2f iIsoPos = isoMatrix.transformPoint(iLogicPos);
            sf::RenderStates iStates = states;
            iStates.transform.translate(iIsoPos);
            iStates.transform.translate(-iLogicPos);
            target.draw(*a, iStates);
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
    tiles = new Tile*[height];
    const int road_y = height/2;
    const int mess_y = height*3/4;
    for (int y=0; y<height; ++y) {
        tiles[y] = new Tile[width];
        for (int x=0; x<height; ++x) {
            if (x == 1 && y == road_y + 1) {
                tiles[y][x] = Tile(this, 5);
            }
            else if (x == 10 && y > road_y && y < road_y + 10) {
                tiles[y][x] = Tile(this, 5);
            }
            else if (abs(y - road_y) < road_width/2) {
                tiles[y][x] = Tile(this, 3);
            }
            else if (abs(y - mess_y) < road_width/2) {
                tiles[y][x] = Tile(this, (x*x*17+x*5+y*29+x*y)%7+0);
            }
            else {
                tiles[y][x] = Tile(this, 1);
            }
        }
    }
    
    spawn_map_resource(new BirchTree(this, {4, road_y + 10}, "Wood", 50, 8));
    spawn_map_resource(new BirchTree(this, {7, road_y + 13}, "Wood", 50, 8));
    spawn_map_resource(new BirchTree(this, {10, road_y + 14}, "Wood", 50, 8));
    spawn_map_resource(new BirchTree(this, {4, road_y + 15}, "Wood", 50, 8));
    
    spawn_map_resource(new BirchTree(this, {18, road_y + 15}, "Wood", 50, 8));
    spawn_map_resource(new BirchTree(this, {17, road_y + 15}, "Wood", 10, 3));
    spawn_map_resource(new BirchTree(this, {18, road_y + 14}, "Wood", 10, 3));
    spawn_map_resource(new BirchTree(this, {19, road_y + 15}, "Wood", 10, 3));
    spawn_map_resource(new BirchTree(this, {18, road_y + 16}, "Wood", 10, 3));
}

World::~World() {
    for (int y=0; y<height; ++y) {
        delete[] tiles[y];
    }
    delete[] tiles;
    
    for (int i=0; i<map_objects.get_size(); ++i) {
        delete map_objects[i];
    }
}

void World::update(float deltaTime) {
    player.update(deltaTime);
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