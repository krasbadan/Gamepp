#include "TextureManager.hpp"
#include "Utils.hpp"



const sf::Texture& TextureManager::operator[](const std::string& filename) {
    Map<std::string, sf::Texture>::iterator T = textures.find(filename);
    if (T == textures.end()) {
        sf::Texture tex; sf::IntRect area = {};
        if (filename.find("Assets/Sprites/Tiles/") != std::string::npos) {
            area = sf::IntRect({0, 0}, {TILESIZE, TILESIZE});
        }
        if (!tex.loadFromFile(filename, false, area)) {
            throw;
        }
        textures[filename] = tex;
    }
    return textures[filename];
}