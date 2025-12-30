#include "MapObject.hpp"

#include "TextureManager.hpp"

#include "Tile.hpp"
#include "World.hpp"



void MapObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

sf::Vector2f MapObject::get_bottom_point() const {
    sf::Vector2f bottom = sprite.getGlobalBounds().getCenter();
	bottom.y *= 2;
    return bottom;
}

sf::Vector2f MapObject::get_central_point() const {
    // need to divide both coords because of the iso-projection
    return getPosition() - sf::Vector2f(ingame_height / 2.f, ingame_height / 2.f);
}

sf::Vector2i MapObject::get_pos() const {
    return pos;
}

float MapObject::get_ingame_height() const {
    return ingame_height;
}

MapObject::MapObject(World* _worldptr, const sf::Texture& texture, sf::Vector2i _pos, float _ingame_height): 
    worldptr(_worldptr), sprite(texture), pos(_pos), ingame_height(_ingame_height),
    tile(&_worldptr->tiles[_pos.y][_pos.x]) 
{
    sprite.setOrigin(get_bottom_point() - sf::Vector2f(0.f, texture.getSize().y/ingame_height)*0.75);
	float scale = ingame_height/texture.getSize().y;
	sprite.setScale(sf::Vector2f(scale, scale));
}

void MapObject::update(float deltaTime) {}