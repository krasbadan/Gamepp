#include "NPC.hpp"



NPC::NPC(World* _worldptr, const sf::Texture& texture, sf::Vector2f pos, sf::Vector2f anim_origin, float _ingame_height, int _hp_max):
    Character(_worldptr, texture, pos, anim_origin, _ingame_height, _hp_max)
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
    return 3.f;
}