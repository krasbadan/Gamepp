#pragma once

#include "Utils.hpp"



class MapObject : public sf::Drawable, public sf::Transformable {
protected:
    Tile* tile;
    sf::Vector2i pos;
    sf::Sprite sprite;
    float ingame_height;
    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f get_bottom_point() const;

    World* const worldptr;

public:
    World* get_worldptr() const;
    
    sf::Vector2f get_central_point() const;
    sf::Vector2i get_pos() const;
    float get_ingame_height() const;
    
    MapObject(World* _worldptr, sf::Vector2i pos, const sf::Texture& texture, float ingame_height = 2.f);
    
    virtual void update(float deltaTime);
};