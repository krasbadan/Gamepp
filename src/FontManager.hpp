#pragma once

#include "Utils.hpp"



class FontManager {
    sf::Font font;
public:
    FontManager();
    const sf::Font& operator[](const std::string& filename);
};

extern FontManager Fx;