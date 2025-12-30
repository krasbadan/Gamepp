#include "NPC.hpp"



NPC::NPC(
    World* _worldptr, sf::Vector2f pos,
    const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
    float _ingame_height, int _hp_max
):
    Character(_worldptr, pos, texture, anim_frame_size, anim_origin, _ingame_height, _hp_max)
{}

void NPC::update(float deltaTime) {
    
}

Dialogue* NPC::interact() {
    return new Dialogue(this, L"Привет!", 0, {});
}

sf::Vector2f NPC::get_interact_pos() const {
    return getPosition();
}
float NPC::get_interact_distance() const {
    return 3.f;
}