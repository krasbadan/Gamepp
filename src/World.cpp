#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "TextureManager.hpp"
#include "Tile.hpp"



World::World(int _width, int _height):
    player(this, Tx["Assets/player.png"]),
    width(_width), height(_height)
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
                tiles[y][x] = Tile(this, 1);
            }
        }
    }
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
    
    int size_x = target.getView().getSize().x, size_y = target.getView().getSize().y, min_r = 4;
    int radius = std::max({size_x/2, size_y/2, min_r});
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

    target.draw(player, playerStates);
}
