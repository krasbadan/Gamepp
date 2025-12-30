#include "Campfire.hpp"

#include <iostream>



Campfire::Campfire(World* _worldptr, sf::Vector2i pos, float _ingame_height):
                   Building(_worldptr, Tx["Assets/Sprites/MapObjects/campfire_burning.png"], pos, _ingame_height),
                   animation_handler(sf::IntRect({0, 0}, {32, 64}))
{
    Animation burn(0, 8, 0.3f); animation_handler.addAnim(burn);
    animation_handler.changeAnim(0);
    sprite.setTextureRect(animation_handler.bounds);

    sprite.setOrigin(sf::Vector2f(16, 60));
    float scale = ingame_height/Tx["Assets/Sprites/MapObjects/campfire_burning.png"].getSize().y;
	sprite.setScale(sf::Vector2f(scale, scale));
};

void Campfire::update(float deltaTime) {
    animation_handler.update(deltaTime);
    sprite.setTextureRect(animation_handler.bounds);
}