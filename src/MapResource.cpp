#include "MapResource.hpp"



MapResource::MapResource(World* _worldptr, const sf::Texture& texture, sf::Vector2i pos, const char* _name, int _amount, float ingame_height):
    MapObject(_worldptr, texture, pos, ingame_height), name(_name), amount(_amount)
{}

Dialogue* MapResource::interact() {
    return new Dialogue(L"Добыть берёзового сока?", 0, {});
}

sf::Vector2f MapResource::get_interact_pos() const {
    return sf::Vector2f(pos) + sf::Vector2f(0.5, 0.5);
}
float MapResource::get_interact_distance() const {
    return 1.f;
}