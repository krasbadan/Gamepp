#include "Tile.hpp"
#include "TextureManager.hpp"

Tile::Tile(World* _worldptr, int _type, bool _is_passable, MapObject* _map_object):
    worldptr(_worldptr),
    type(_type),
    is_passable(_is_passable),
    map_object(_map_object),
    sprite(Tx[tile_types[_type].texture_filename])
{}
Tile::Tile(World* _worldptr, int _type):
    worldptr(_worldptr),
    type(_type),
    is_passable(tile_types[_type].is_passable),
    map_object(nullptr),
    sprite(Tx[tile_types[_type].texture_filename])
{}
Tile::Tile():
    worldptr(nullptr),
    type(0),
    is_passable(false),
    map_object(nullptr),
    sprite(Tx[tile_types[0].texture_filename])
{}