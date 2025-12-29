#include "MapResource.hpp"

#include "TextureManager.hpp"



MapResource::MapResource(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, const char* _name, int _amount, float ingame_height):
    MapObject(_worldptr, texture, pos, ingame_height), name(_name), amount(_amount)
{}

sf::Vector2f MapResource::get_interact_pos() const {
    return sf::Vector2f(pos) + sf::Vector2f(0.5, 0.5);
}
float MapResource::get_interact_distance() const {
    return 1.5f;
}



BirchTree::BirchTree(World* _worldptr, sf::Vector2i pos, const char* _name, int _amount, float ingame_height):
    MapResource(_worldptr, Tx["Assets/Sprites/MapObjects/birch.png"], pos, _name, _amount, ingame_height)
{}