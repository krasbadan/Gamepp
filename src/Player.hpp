#pragma once

#include "dialogue.hpp"

#include "Character.hpp"
#include "Presenter.hpp"
#include "Utils.hpp"



class Player : public Character {
    float speed = 6.0f;
public:
    Presenter presenter;
    Dialogue* active_dialogue;
    
    Player(const Presenter& _presenter, World* _worldptr, const sf::Texture& texture, sf::Vector2f pos, float _ingame_height = 2.25f, int _hp_max = 100);
    
    virtual void update(float deltaTime) override;
};