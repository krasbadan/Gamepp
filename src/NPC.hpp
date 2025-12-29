#pragma once

#include "Character.hpp"
#include "Interactable.hpp"
#include "Utils.hpp"



class NPC : public Character, public Interactable {
    float speed = 4.0f;
public:
    NPC(World* _worldptr, const sf::Texture& texture, float _ingame_height = 1.8f, int _hp_max = 100);
    
    virtual void update(float deltaTime) override;
    
    virtual Dialogue* interact() override;
    virtual sf::Vector2f get_interact_pos() const override;
    virtual float get_interact_distance() const override;
};