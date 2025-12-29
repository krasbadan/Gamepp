#pragma once

#include "Utils.hpp"



class Character : public sf::Drawable, public sf::Transformable {
protected:
    World* worldptr;
    float speed;
	float ingame_height;
    int hp_max, hp;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f get_bottom_point() const;

public:
    sf::Vector2f get_central_point() const;

    Character(World* _worldptr, const sf::Texture& texture, float _ingame_height, int _hp_max = 100);

    bool can_move(sf::Vector2f vec);

    virtual void update(float deltaTime) = 0;
};