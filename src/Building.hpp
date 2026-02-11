#pragma once

#include "MapObject.hpp"
#include "Utils.hpp"



class Building: public MapObject {
protected:
    NPC* worker;

public:
    NPC* get_worker() const;
    void set_worker(NPC* worker);
    
    Building(World* _worldptr, sf::Vector2i pos, const sf::Texture& texture, float ingame_height = 2.f);
};