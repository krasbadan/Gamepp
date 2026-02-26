#pragma once

#include "dialogue.hpp"

#include "Utils.hpp"



class Interactable: public sf::Drawable {
    const char* key_name;

public:
    const char* get_key_name() const;
    void set_key_name(const char* _key_name);
    
    Interactable();

    virtual Dialogue* interact() = 0;
    
    virtual sf::Vector2f get_interact_pos() const = 0;
    virtual float get_interact_distance() const = 0;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};