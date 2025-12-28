#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "TextureManager.hpp"
#include "Utils.hpp"

#include "Player.hpp"
#include "World.hpp"



TextureManager Tx;



void update_view_size(const sf::RenderWindow& window, sf::View& view, const float& zoomout) {
    view.setSize(sf::Vector2f(window.getSize())*zoomout);
};



int main() {
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Game++");
    sf::Clock clock;
    
    window.setFramerateLimit(60);
    
    bool window_focus = true;
    float zoomout = 0.015;
    sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())*zoomout));
    
    
    
    const auto onClosed = [&window](const sf::Event::Closed& event) {
        window.close();
    };
    const auto onFocusLost = [&window_focus](const sf::Event::FocusLost& event) {
        window_focus = false;
    };
    const auto onFocusGained = [&window_focus](const sf::Event::FocusGained& event) {
        window_focus = true;
    };
    const auto onResized = [&window, &view, &zoomout](const sf::Event::Resized& event) {
        update_view_size(window, view, zoomout);
    };
    const auto onMouseWheelScrolled = [&window, &view, &zoomout](const sf::Event::MouseWheelScrolled& event) {
        zoomout *= pow(1.1, -event.delta);
        update_view_size(window, view, zoomout);
    };
    const auto onKeyPressed = [&window](const sf::Event::KeyPressed& event) {
        if (event.scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    };
    
    
    
    World world(50, 50);

    while (window.isOpen()) {
        window.handleEvents(onClosed, onFocusLost, onFocusGained, onResized, onMouseWheelScrolled, onKeyPressed);
        
        float deltaTime = clock.restart().asSeconds();
        world.update(deltaTime);
        
        if (window_focus) {
            window.clear(sf::Color {0, 100, 20});
            view.setCenter(world.player.get_central_point());
            window.setView(view);
            window.draw(world);
        }
        window.display();
    }

    return 0;
}
