#pragma once

#include "MapObject.hpp"
#include "Utils.hpp"



class Building: public MapObject {
public:
    NPC* worker;
    
    Building(World* _worldptr, sf::Vector2i pos, const sf::Texture& texture, float ingame_height = 2.f);
};