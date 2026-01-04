#include "Player.hpp"

#include <iostream>
#include <random>

#include "dialogue.hpp"
#include "Utils.hpp"
#include "World.hpp"



Player::Player(
    World* _worldptr, sf::Vector2f pos,
    const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
    float _ingame_height, int _hp_max
):
    Character(_worldptr, pos, texture, anim_frame_size, anim_origin, _ingame_height, _hp_max),
    presenter(this)
{
    Animation idle(0, 7, 0.15f); animation_handler.addAnim(idle);
    Animation run(0, 7, 0.1f); animation_handler.addAnim(run);
    Animation jump(0, 1, 0.15f); animation_handler.addAnim(jump);
    Animation fall(0, 1, 0.15f); animation_handler.addAnim(fall);
    Animation attack1(0, 3, 0.1f); animation_handler.addAnim(attack1);
    Animation attack2(0, 3, 0.1f); animation_handler.addAnim(attack2);
    Animation attack3(0, 3, 0.1f); animation_handler.addAnim(attack3);
    Animation ouch(0, 3, 0.15f); animation_handler.addAnim(ouch);
    Animation ouch_white_silhouette(0, 7, 0.15f); animation_handler.addAnim(ouch_white_silhouette);
    Animation death(0, 5, 0.15f); animation_handler.addAnim(death);
    Animation dead(0, 1, 1.f); animation_handler.addAnim(dead);
    animation_handler.changeAnim(0);
    sprite.setTextureRect(animation_handler.bounds);

    sprite.setOrigin(anim_origin);
    float scale = animation_handler.count_animations()*ingame_height/texture.getSize().y;
	sprite.setScale(sf::Vector2f(scale, scale));
}

void Player::update(float deltaTime) {
    if (hp == 0) {
        animation_handler.update(deltaTime);
        animation_handler.changeAnim(10);
        sprite.setTextureRect(animation_handler.bounds);
        return;
    }

    sf::Vector2f movement{0.f, 0.f};
    float s = speed * deltaTime;
    bool was_flipped = is_flipped;
    
    if (animation_handler.get_anim_duration() != 0) s /= 1000;
    else if (presenter.check_input_shift()) s *= 5;

    if (presenter.check_input_move_up()) { movement.x -= s; movement.y -= s; }
    if (presenter.check_input_move_down()) { movement.x += s; movement.y += s; }
    if (presenter.check_input_move_left()) { movement.x -= s; movement.y += s; }
    if (presenter.check_input_move_right()) { movement.x += s; movement.y -= s; }

    if (hp != 0 && fabs(movement.x) < EPS && fabs(movement.y) < EPS) {
        animation_handler.changeAnim(0);
    } else {
        // Run animation
        if (presenter.check_input_shift()) animation_handler.changeAnim(3);
        else animation_handler.changeAnim(1);
        
        if (movement.x == 0 || movement.y == 0) { movement.x *= 0.707f; movement.y *= 0.707f; }
        
        sf::Vector2f real_movement;

        if      (can_move(getPosition() + movement))                      real_movement = movement;
        else if (can_move(getPosition() + sf::Vector2f({movement.x, 0}))) real_movement = {movement.x, 0};
        else if (can_move(getPosition() + sf::Vector2f({0, movement.y}))) real_movement = {0, movement.y};
        
        if (fabs(real_movement.x) >= EPS || fabs(real_movement.y) >= EPS)
            move(real_movement);
        
        float screen_dx = real_movement.x - real_movement.y;
        bool was_flipped = is_flipped;
        if (screen_dx < -EPS) is_flipped = true;
        else if (screen_dx > EPS) is_flipped = false;
        if (is_flipped != was_flipped) sprite.scale({-1.f, 1.f});
    }

    if (presenter.check_input_space()) {
        //animation_handler.breakAnim();
        animation_handler.playAnim(4 + std::rand()%3);
    }

    animation_handler.update(deltaTime);
    sprite.setTextureRect(animation_handler.bounds);

    //std::cout << getPosition().x << " " << getPosition().y << std::endl;
    
    if (worldptr->player_economy->resources["birch_juice"] >= 290 && !worldptr->story.birch_juice_ending) {
        worldptr->story.birch_juice_ending = true;
        presenter.active_dialogue = new Dialogue(
            presenter.window_interactable,
            L"Вы собрали весь берёзовый сок в этом мире. Ваша жадность стала вашим концом.",
            {
                DialogueOption(L"...", [this]() -> Dialogue* {
                    worldptr->player_economy->resources["birch_juice"] = -1000;
                    animation_handler.playAnim(9);
                    hp = 0;
                    return nullptr;
                }),
            }
        );
    }

    return;
}