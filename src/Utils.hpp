#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>



const float EPS = 1e-9;

const int TILESIZE = 16;
const float ISO_SCALE_Y = 0.707;

class TextureManager; class Tile; class MapObject; class World; class Character; class Player;

int mod(int a, int b);

sf::Vector2f operator*(sf::Vector2f vec, float c);
sf::Vector2f operator/(sf::Vector2f vec, float c);
sf::Vector2i floor(sf::Vector2f vec);

sf::RenderStates translate(sf::RenderStates states, sf::Vector2f shift);