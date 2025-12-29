#pragma once

#include "dialogue.hpp"
#include "Character.hpp"
#include "Utils.hpp"
#include "TextureManager.hpp"


class Player : public Character {
    float speed = 6.0f;
public:
    Dialogue* active_dialogue;
    
    Player(World* _worldptr, sf::Vector2f pos,
           const sf::Texture& texture = Tx["Assets/Sprites/KingAnimated/FullAnimation.png"],
           sf::Vector2f anim_origin = sf::Vector2f(85.f, 105.f),
           float _ingame_height = 2.25f, int _hp_max = 100);
    
    virtual void update(float deltaTime) override;
};