#include "Player.hpp"
#include "World.hpp"
#include "Tile.hpp"

Player::Player(World* _worldptr, const sf::Texture& texture, int _hp_max) : Character(_worldptr, texture, _hp_max) {}

void Player::update(float deltaTime) {
    sf::Vector2f movement{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) movement.y += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) movement.x += speed * deltaTime;

    if (movement.x != 0 && movement.y != 0) {movement.x *= 0.707; movement.y *= 0.707;}

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