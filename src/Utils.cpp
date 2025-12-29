#include "Utils.hpp"



int mod(int a, int b) {
    return (a%b + b)%b;
}

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

sf::RenderStates translate_states(sf::RenderStates states, sf::Vector2f shift) {
    sf::Transform transform;
    transform.translate(shift);
    states.transform *= transform;
    return states;
}
sf::RenderStates scale_states(sf::RenderStates states, sf::Vector2f scale) {
    sf::Transform transform;
    transform.scale(scale);
    states.transform *= transform;
    return states;
}