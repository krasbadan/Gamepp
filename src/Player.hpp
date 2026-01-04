#pragma once

#include "dialogue.hpp"

#include "Character.hpp"
#include "Presenter.hpp"
#include "Utils.hpp"
#include "TextureManager.hpp"


class Player : public Character {
    float speed = 6.0f;
public:
    Presenter presenter;
    
    Player(World* _worldptr, sf::Vector2f pos,
           const sf::Texture& texture = Tx["Assets/Sprites/KingAnimated/FullAnimation.png"],
           sf::Vector2i anim_frame_size = {160, 111}, sf::Vector2f anim_origin = {85.f, 105.f},
           float _ingame_height = 3.6f, int _hp_max = 100);
    
    virtual void update(float deltaTime) override;
};