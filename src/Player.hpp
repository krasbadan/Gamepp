#pragma once

#include "dialogue.hpp"
#include "Character.hpp"
#include "Utils.hpp"



class Player : public Character {
    float speed = 6.0f;
public:
    Dialogue* active_dialogue;
    
    Player(World* _worldptr, const sf::Texture& texture, float _ingame_height = 2.25f, int _hp_max = 100);
    
    virtual void update(float deltaTime) override;
};