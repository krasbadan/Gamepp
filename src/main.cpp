#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "TextureManager.hpp"
#include "Utils.hpp"

#include "MapObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "World.hpp"

TextureManager Tx;

int main() {
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "SFML 3 Character");
    int zoomout = 2;
    sf::View view(sf::FloatRect({0.f, 0.f}, {zoomout*144.f, zoomout*96.f}));

    World world(50, 50);


    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) 
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        world.player.update(deltaTime);
        
        window.clear(sf::Color {0, 100, 20});
        view.setCenter(world.player.get_central_point());
        window.setView(view);
        window.draw(world);
        window.draw(world.player);
        window.display();
    }

    return 0;
}
