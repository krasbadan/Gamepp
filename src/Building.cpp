#include "Building.hpp"

#include "NPC.hpp"



Building::Building(World* _worldptr, sf::Vector2i pos, const sf::Texture& texture, float ingame_height):
    MapObject(_worldptr, pos, texture, ingame_height), worker(nullptr)
{}

NPC* Building::get_worker() const {
    return worker;
}
void Building::set_worker(NPC* _worker) {
    worker = _worker;
}