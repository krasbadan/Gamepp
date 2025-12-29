#pragma once

#include "MapObject.hpp"
#include "Utils.hpp"



class Building: public MapObject {
public:
    NPC* worker;
    
    Building(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, float ingame_height = 2.f);
};