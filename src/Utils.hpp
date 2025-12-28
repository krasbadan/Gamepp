#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>



const int TILESIZE = 16;

class TextureManager; class Tile; class MapObject; class World; class Character; class Player;

sf::Vector2f operator*(sf::Vector2f vec, float c);
sf::Vector2f operator/(sf::Vector2f vec, float c);
sf::Vector2i floor(sf::Vector2f vec);