#include "Tile.hpp"

#include "TextureManager.hpp"



Tile::Tile(World* _worldptr, int _type, bool _is_passable, MapObject* _map_obj) :
    worldptr(_worldptr), 
    type(_type), 
    is_passable(_is_passable), 
    map_object(_map_obj),
    sprite(Tx[tile_types[_type].texture_filename]) 
{
    sprite.setScale({1.f/TILESIZE, 1.f/TILESIZE});
}
