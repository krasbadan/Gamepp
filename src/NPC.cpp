#include "NPC.hpp"



NPC::NPC(World* _worldptr, const sf::Texture& texture, float _ingame_height, int _hp_max):
    Character(_worldptr, texture, _ingame_height, _hp_max)
{}

void NPC::update(float deltaTime) {
    
}

Dialogue* NPC::interact() {
    return new Dialogue(L"Привет!", 0, {});
}

sf::Vector2f NPC::get_interact_pos() const {
    return getPosition();
}
float NPC::get_interact_distance() const {
    return 2.f;
}