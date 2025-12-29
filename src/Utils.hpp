#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>



const float EPS = 1e-9;

const int TILESIZE = 16;
const float ISO_SCALE_Y = 0.707;

class Building;
class Character;
class FontManager;
class Interactable;
class MapObject;
class MapResource;
class NPC;
class Player;
class TextureManager;
class AnimationHandler;
class Tile;
class World;

int mod(int a, int b);

sf::Vector2f operator*(sf::Vector2f vec, float c);
sf::Vector2f operator/(sf::Vector2f vec, float c);
sf::Vector2i floor(sf::Vector2f vec);

sf::RenderStates translate_states(sf::RenderStates states, sf::Vector2f shift);
sf::RenderStates scale_states(sf::RenderStates states, sf::Vector2f scale);