#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "TextureManager.hpp"
#include "Tile.hpp"
#include "MapObject.hpp"



World::World(int _width, int _height):
    player(this, Tx["Assets/Sprites/player.png"]),
    width(_width), height(_height),
    map_objects()
{
    tiles = new Tile*[height];
    const int road_y = height/2;
    for (int y=0; y<height; ++y) {
        tiles[y] = new Tile[width];
        for (int x=0; x<height; ++x) {
            if (x == 1 && y == 1) {
                tiles[y][x] = Tile(this, 5);
            }
            else if (x == 10 && y < 10) {
                tiles[y][x] = Tile(this, 5);
            }
            else if (abs(y - road_y) < road_width/2) {
                tiles[y][x] = Tile(this, (x*x*17+x*5+y*29+x*y)%7+0);
            } else {
                tiles[y][x] = Tile(this, 0);
            }
        }
    }
    
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {4, 10}, 8));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {7, 13}, 8));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {10, 14}, 8));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {4, 15}, 8));
    
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {18, 15}, 8));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {17, 15}, 3));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {18, 14}, 3));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {19, 15}, 3));
    map_objects.push_back(new MapObject(this, Tx["Assets/Sprites/MapObjects/birch.png"], {18, 16}, 3));
}

void World::update(float deltaTime) {
    player.update(deltaTime);
}

sf::Vector2f World::get_iso_pos(sf::Vector2f logicPos) {
    sf::Transform isoMatrix;
    isoMatrix.scale({1.0f, ISO_SCALE_Y}); 
    isoMatrix.rotate(sf::degrees(45.0f));
    
    return isoMatrix.transformPoint(logicPos);
}


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

    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            tiles[y][x].sprite.setPosition({(float)x, (float)y});
            target.draw(tiles[y][x].sprite, tileStates);
        }
    }

    sf::Vector2f playerLogicPos = player.getPosition();
    sf::Vector2f playerIsoPos = isoMatrix.transformPoint(playerLogicPos);

    sf::RenderStates playerStates = states;
    
    playerStates.transform.translate(playerIsoPos);
    playerStates.transform.translate(-playerLogicPos);
    
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            if (tiles[y][x].map_object != nullptr) {
                MapObject* obj = tiles[y][x].map_object;
                sf::Vector2f logicPos = {(float)x, (float)y};
                sf::Vector2f isoPos = isoMatrix.transformPoint(logicPos);
                sf::RenderStates objStates = states;
                objStates.transform.translate(isoPos);

                target.draw(*obj, objStates);
            }
        }
    }
    
    target.draw(player, playerStates);
}
