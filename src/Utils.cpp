#include "Utils.hpp"

sf::Vector2f operator*(sf::Vector2f vec, float c){
    vec.x *= c; vec.y *= c;
    return vec;
}
sf::Vector2f operator/(sf::Vector2f vec, float c){
    vec.x /= c; vec.y /= c;
    return vec;
}
sf::Vector2i floor(sf::Vector2f vec){
    return sf::Vector2i({static_cast<int>(floor(vec.x)), static_cast<int>(floor(vec.y))});
}