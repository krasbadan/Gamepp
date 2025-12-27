#include "TextureManager.hpp"

const sf::Texture& TextureManager::operator[](const std::string& texture) {
    std::map<std::string, sf::Texture>::iterator T = textures.find(texture);
    if (T == textures.end()) {
        sf::Texture tex;
        if (!tex.loadFromFile(texture)) {
            throw;
        }
        textures[texture] = tex;
    }
    return textures[texture];
}