#pragma once

#include <map>
#include <string>

#include "Utils.hpp"



class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;
 
public:
    const sf::Texture& operator[](const std::string& texture);
};

extern TextureManager Tx;