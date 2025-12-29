#include "Player.hpp"
#include <iostream>


Player::Player(World* _worldptr, const sf::Texture& texture, float _ingame_height, int _hp_max):
    Character(_worldptr, texture, _ingame_height, _hp_max),
    active_dialogue(nullptr)
{}

void Player::update(float deltaTime) {
    sf::Vector2f movement{0.f, 0.f};
    float s = speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { movement.x -= s; movement.y -= s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { movement.x += s; movement.y += s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) { movement.x -= s; movement.y += s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) { movement.x += s; movement.y -= s; }

    if (abs(movement.x) < EPS && abs(movement.y) < EPS) return;
    if (movement.x == 0 || movement.y == 0) {movement.x *= 0.707; movement.y *= 0.707;}

    /*
    std::cout << "Logic: " << logicPos.x << ", " << logicPos.y << std::endl;
    std::cout << "Iso (Screen): " << isoPos.x << ", " << isoPos.y << std::endl;
    //*/

    //std::cout << sprite.getGlobalBounds().getCenter().x << " " << sprite.getGlobalBounds().getCenter().y << std::endl;
    
    if (can_move(getPosition() + movement)) {
        move(movement);
        return;
    }
    if (can_move(getPosition() + sf::Vector2f({movement.x, 0}))) {
        move(sf::Vector2f({movement.x, 0}));
        return;
    }
    if (can_move(getPosition() + sf::Vector2f({0, movement.y}))) {
        move(sf::Vector2f({0, movement.y}));
        return;
    }
}