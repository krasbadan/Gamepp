#pragma once
#include "Utils.hpp"

class Character : public sf::Drawable, public sf::Transformable {
protected:
    World* worldptr;
    sf::Sprite sprite;
    float speed = 200.0f;
    int hp_max, hp;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f get_bottom_point();

public:
    sf::Vector2f get_central_point();

    Character(World* _worldptr, const sf::Texture& texture, int _hp_max = 100);

    bool can_move(sf::Vector2f vec);

    virtual void update(float deltaTime) = 0;
};