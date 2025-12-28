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

void World::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const {
    sf::Vector2f center = target.getView().getCenter();
    sf::Vector2f size = target.getView().getSize();
    int top_y = floor(center.y - 0.5*size.y);
    int bottom_y = ceil(center.y + 0.5*size.y);
    int left_x = floor(center.x - 0.5*size.x);
    int right_x = ceil(center.x + 0.5*size.x);
    
    for (int y = std::max(0, top_y); y < std::min(height, bottom_y); y++) {
        for (int x = std::max(0, left_x); x < std::min(width, right_x); x++){
            tiles[y][x].sprite.setPosition({static_cast<float>(x), static_cast<float>(y)});
            target.draw(tiles[y][x].sprite);
        }
    }
    
	target.draw(player);
}