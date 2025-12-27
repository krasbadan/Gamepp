#pragma once
#include "Character.hpp"
#include "Utils.hpp"

class Player : public Character {
public:
    virtual void update(float deltaTime) override;
    Player(World* _worldptr, const sf::Texture& texture, int _hp_max = 100);
};