#pragma once

#include "Utils.hpp"
#include "AnimationHandler.hpp"



class Character : public sf::Drawable, public sf::Transformable {
protected:
    float speed;
	float ingame_height;
    int hp_max, hp;
    sf::Sprite sprite;
    AnimationHandler animation_handler;
    bool is_flipped = 0;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f get_bottom_point() const;
    
public:
    World* const worldptr;
    
    sf::Vector2f get_central_point() const;

    Character(
        World* _worldptr, sf::Vector2f pos,
        const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
        float _ingame_height, int _hp_max = 100
    );

    bool can_move(sf::Vector2f vec);

    virtual void update(float deltaTime) = 0;
};