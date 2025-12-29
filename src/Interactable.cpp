#include "Interactable.hpp"

#include "FontManager.hpp"



void Interactable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    float rect_size = 0.5f;
    float font_size = 0.75f*rect_size;
    int font_antialias_k = 100;
    
    sf::Vector2f draw_pos = get_interact_pos() - sf::Vector2f(0, 1.f);
    
    sf::RectangleShape rect(sf::Vector2f(rect_size, rect_size));
    rect.setFillColor({0, 0, 0, 128});
    rect.setOutlineColor({255, 255, 255, 128});
    rect.setOutlineThickness(-0.1f*rect_size);
    rect.setPosition(draw_pos - sf::Vector2f(0.5f, 0.5f)*rect_size);
    target.draw(rect, states);
    
    sf::Text sf_text(Fx["cambria.ttc"], "E", font_antialias_k);
    sf_text.setFillColor({255, 255, 255});
    sf_text.setOutlineColor({0, 0, 0});
    sf_text.setOutlineThickness(-0.05f*font_antialias_k);
    sf::Vector2f size = sf_text.getGlobalBounds().size;
    sf_text.setOrigin(size/2.f + sf_text.getLocalBounds().position);
    sf_text.setScale(sf::Vector2f(font_size/font_antialias_k, font_size/font_antialias_k));
    sf_text.setPosition(draw_pos);
    target.draw(sf_text, states);
}