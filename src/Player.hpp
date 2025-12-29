#pragma once

#include "dialogue.hpp"
#include "Character.hpp"
#include "Utils.hpp"



class Player : public Character {
    float speed = 6.0f;
	float ingame_height = 2.25f;
public:
    Dialogue* active_dialogue;
    
    virtual void update(float deltaTime) override;
    Player(World* _worldptr, const sf::Texture& texture, int _hp_max = 100);
};