#pragma once

#include "map.hpp"
#include <string>

#include "Utils.hpp"



class TextureManager {
private:
    Map<std::string, sf::Texture> textures;
 
public:
    const sf::Texture& operator[](const std::string& filename);
};

extern TextureManager Tx;