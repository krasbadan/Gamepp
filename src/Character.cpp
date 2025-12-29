#include "Character.hpp"

#include "Tile.hpp"
#include "World.hpp"



void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

sf::Vector2f Character::get_bottom_point() const {
    sf::Vector2f bottom = sprite.getGlobalBounds().getCenter();
	bottom.y *= 2;
    return bottom;
}

sf::Vector2f Character::get_central_point() const {
    // need to divide both coords because of the iso-projection
    return getPosition() - sf::Vector2f(ingame_height / 2.f, ingame_height / 2.f);
}

Character::Character(World* _worldptr, const sf::Texture& texture, float _ingame_height, int _hp_max):
    worldptr(_worldptr), sprite(texture), ingame_height(_ingame_height), hp_max(_hp_max), hp(_hp_max)
{
    sprite.setOrigin(get_bottom_point());
	float scale = ingame_height/texture.getSize().y;
	sprite.setScale(sf::Vector2f(scale, scale));
}

bool Character::can_move(sf::Vector2f vec) {
    sf::Vector2i newpos = floor(vec);
    return (0 <= newpos.y && worldptr->height > newpos.y &&
            0 <= newpos.x && worldptr->width  > newpos.x &&
            worldptr->tiles[newpos.y][newpos.x].is_passable);
}