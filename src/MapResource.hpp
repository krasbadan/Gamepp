#pragma once

#include "Interactable.hpp"
#include "MapObject.hpp"
#include "Utils.hpp"



class MapResource: public MapObject, public Interactable {
public:
    const char* name;
    int amount;
    
    MapResource(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, const char* _name, int _amount, float ingame_height = 2.f);
    
    virtual sf::Vector2f get_interact_pos() const override;
    virtual float get_interact_distance() const override;
};



class BirchTree: public MapResource {
public:
    BirchTree(World* _worldptr, sf::Vector2i pos, const char* _name, int _amount, float ingame_height = 2.f);
    
    virtual Dialogue* interact() override;
    Dialogue* next_dial();
};