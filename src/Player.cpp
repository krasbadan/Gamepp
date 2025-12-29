#include "Player.hpp"

#include <iostream>


Player::Player(const Presenter& _presenter, World* _worldptr, sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f anim_origin, float _ingame_height, int _hp_max):
    Character(_worldptr, texture, pos, anim_origin, _ingame_height, _hp_max),
    presenter(_presenter),
    active_dialogue(nullptr)
{
    Animation idle(0, 7, 0.15f); animation_handler.addAnim(idle);
    Animation jump(0, 7, 0.1f); animation_handler.addAnim(jump);
    Animation fall(0, 1, 0.15f); animation_handler.addAnim(fall);
    Animation attack1(0, 3, 0.15f); animation_handler.addAnim(attack1);
    Animation attack2(0, 3, 0.15f); animation_handler.addAnim(attack2);
    Animation attack3(0, 3, 0.15f); animation_handler.addAnim(attack3);
    Animation ouch(0, 3, 0.15f); animation_handler.addAnim(ouch);
    Animation ouch_white_silhouette(0, 7, 0.15f); animation_handler.addAnim(ouch_white_silhouette);
    Animation death(0, 5, 0.15f); animation_handler.addAnim(death);
    animation_handler.changeAnim(0);
    sprite.setTextureRect(animation_handler.bounds);

    sprite.setOrigin(anim_origin);
    float scale = animation_handler.count_animations()*ingame_height/texture.getSize().y;
	sprite.setScale(sf::Vector2f(scale, scale));
}

void Player::update(float deltaTime) {
    sf::Vector2f movement{0.f, 0.f};
    float s = speed * deltaTime;
    bool was_flipped = is_flipped;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { movement.x -= s; movement.y -= s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { movement.x += s; movement.y += s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) { movement.x -= s; movement.y += s; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) { movement.x += s; movement.y -= s; }

    if (fabs(movement.x) < EPS && fabs(movement.y) < EPS) {
        animation_handler.changeAnim(0);
    } else {
        animation_handler.changeAnim(1);

        if (movement.x == 0 || movement.y == 0) { movement.x *= 0.707f; movement.y *= 0.707f; }
        
        float screen_dx = movement.x - movement.y;
        bool was_flipped = is_flipped;
        if (screen_dx < -EPS) is_flipped = true;
        else if (screen_dx > EPS) is_flipped = false;
        if (is_flipped != was_flipped) sprite.scale({-1.f, 1.f});

        if      (can_move(getPosition() + movement))                      move(movement);
        else if (can_move(getPosition() + sf::Vector2f({movement.x, 0}))) move(sf::Vector2f({movement.x, 0}));
        else if (can_move(getPosition() + sf::Vector2f({0, movement.y}))) move(sf::Vector2f({0, movement.y}));
    }

    animation_handler.update(deltaTime);
    sprite.setTextureRect(animation_handler.bounds);

    return;
}