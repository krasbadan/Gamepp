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
                tiles[y][x] = Tile(this, (x*x*17+x*5+y*29+x*y)%1+6);
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
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++){
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
