#include "FontManager.hpp"



FontManager::FontManager(): font("Assets/Fonts/cambria.ttc") {}

const sf::Font& FontManager::operator[](const std::string& name) {
    return font;
}