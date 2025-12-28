#include "TextureManager.hpp"



const sf::Texture& TextureManager::operator[](const std::string& filename) {
    std::map<std::string, sf::Texture>::iterator T = textures.find(filename);
    if (T == textures.end()) {
        sf::Texture tex; sf::IntRect area = {};
        if (filename.find("Assets/Tiles/") != std::string::npos) {
            area = sf::IntRect({0, 0}, {16, 16});
        }
        if (!tex.loadFromFile(filename, false, area)) {
            throw;
        }
        textures[filename] = tex;
    }
    return textures[filename];
}