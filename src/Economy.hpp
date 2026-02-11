#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Map.hpp"



struct Economy: public sf::Drawable {
    Map<std::string, int> resources;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};