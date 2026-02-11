#pragma once

#include "Character.hpp"
#include "Interactable.hpp"
#include "Time.hpp"
#include "Utils.hpp"



class NPC : public Character, public Interactable {
    float speed = 4.0f;
public:
    NPC(
        World* _worldptr, sf::Vector2f pos,
        const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
        float _ingame_height = 1.8f, int _hp_max = 100
    );
    
    virtual void update(float deltaTime) override;
};



class Citizen: public NPC {
public:
    Citizen(
        World* _worldptr, sf::Vector2f pos,
        const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
        float _ingame_height = 1.8f, int _hp_max = 100
    );
    
    virtual Dialogue* interact() override;
    virtual sf::Vector2f get_interact_pos() const override;
    virtual float get_interact_distance() const override;
};



class Traveler: public NPC {
    Time departure_time;
    
public:
    Traveler(
        World* _worldptr, sf::Vector2f pos,
        const sf::Texture& texture, sf::Vector2i anim_frame_size, sf::Vector2f anim_origin,
        float _ingame_height = 1.8f, int _hp_max = 100
    );
    
    virtual Dialogue* interact() override;
    virtual sf::Vector2f get_interact_pos() const override;
    virtual float get_interact_distance() const override;
};