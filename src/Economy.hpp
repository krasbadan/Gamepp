#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Map.hpp"



class Economy: public sf::Drawable {
public:
    Map<std::string, int> resources;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};