#pragma once

#include "Utils.hpp"



class MapObject : public sf::Drawable, public sf::Transformable {
protected:
    Tile* tile;
    sf::Vector2i pos;
    sf::Sprite sprite;
    float ingame_height = 3.f;
    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f get_bottom_point() const;

public:
    World* const worldptr;
    
    sf::Vector2f get_central_point() const;
    sf::Vector2i get_pos() const;
    
    MapObject(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, float ingame_height = 2.f);
    
    virtual void update(float deltaTime);
};