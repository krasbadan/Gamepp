#pragma once

#include "dialogue.hpp"

#include "Utils.hpp"



class Interactable: public sf::Drawable {
public:
    const char* key_name = nullptr;
    
    virtual Dialogue* interact() = 0;
    
    virtual sf::Vector2f get_interact_pos() const = 0;
    virtual float get_interact_distance() const = 0;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};