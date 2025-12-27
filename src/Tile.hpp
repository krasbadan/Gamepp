#pragma once
#include "Utils.hpp"

struct TileType {
	const char* texture_filename;
	bool is_passable;
};

const int n_tile_types = 7;

/*
0 - чернота
1 - трава
2 - земля
3 - дорога
4 - песок
5 - скала
6 - вода
*/

const TileType tile_types[n_tile_types] = {
	{"Assets/void.png", false},
	{"Assets/grass.png", true},
	{"Assets/dirt.png", true},
	{"Assets/road.png", true},
	{"Assets/sand.png", true},
	{"Assets/cliff.png", false},
	{"Assets/water.png", true}
};

struct Tile {
    World* worldptr;
	int type;
	bool is_passable;
	MapObject* map_object;
	sf::Sprite sprite;

    Tile(World* _worldptr, int _type, bool _is_passable, MapObject* _map_object);
    Tile(World* _worldptr, int _type);
    Tile();
};