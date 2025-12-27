#include "World.hpp"
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

void World::update() {
    
}

void World::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++){
            tiles[y][x].sprite.setPosition({static_cast<float>(x*TILESIZE), static_cast<float>(y*TILESIZE)});
            target.draw(tiles[y][x].sprite);
        }
    }
}