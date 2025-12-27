#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;
 
public:
    const sf::Texture& operator[](const std::string& texture);
};

extern TextureManager Tx;