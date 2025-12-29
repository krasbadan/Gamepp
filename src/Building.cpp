#include "Building.hpp"

#include "NPC.hpp"



Building::Building(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, float ingame_height):
    MapObject(_worldptr, texture, pos, ingame_height), worker(nullptr)
{}