#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "dialogue.hpp"

#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Utils.hpp"

#include "Player.hpp"
#include "World.hpp"
#include "MapObject.hpp"


TextureManager Tx;
FontManager Fx;



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
    
    
    
    World world(50, 50);
    MapObject tree1(&world, Tx["Assets/Sprites/MapObjects/birch.png"], {4, 10}, 8);
    MapObject tree2(&world, Tx["Assets/Sprites/MapObjects/birch.png"], {7, 13}, 8);
    MapObject tree3(&world, Tx["Assets/Sprites/MapObjects/birch.png"], {10, 14}, 8);
    MapObject tree4(&world, Tx["Assets/Sprites/MapObjects/birch.png"], {4, 15}, 8);
    
    
    
    const auto onClosed = [&window](const sf::Event::Closed& event) {
        window.close();
    };
    const auto onKeyPressed = [&window, &world](const sf::Event::KeyPressed& event) {
        Dialogue* ad;
        
        switch (event.scancode) {
            case sf::Keyboard::Scancode::Escape:
                ad = world.player.active_dialogue;
                if (ad == nullptr) {
                    world.player.active_dialogue = new Dialogue(
                        L"Выйти из игры?",
                        2,
                        {
                            DialogueOption(L"Нет", []() -> Dialogue* {
                                return nullptr;
                            }),
                            DialogueOption(L"Да", [&window]() -> Dialogue* {
                                window.close();
                                return nullptr;
                            }),
                        }
                    );
                } else {
                    delete ad;
                    world.player.active_dialogue = nullptr;
                }
                break;
            case sf::Keyboard::Scancode::Up:
                ad = world.player.active_dialogue;
                if (ad != nullptr) {
                    ad->set_active_option(mod(ad->get_active_option() - 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Down:
                ad = world.player.active_dialogue;
                if (ad != nullptr) {
                    ad->set_active_option(mod(ad->get_active_option() + 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Enter:
                ad = world.player.active_dialogue;
                if (ad != nullptr) {
                    Dialogue* new_dial = ad->choose_active_option();
                    delete ad;
                    world.player.active_dialogue = new_dial;
                }
                break;
        }
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
    
    

    while (window.isOpen()) {
        window.handleEvents(onClosed, onKeyPressed, onFocusLost, onFocusGained, onResized, onMouseWheelScrolled);
        
        float deltaTime = clock.restart().asSeconds();
        world.update(deltaTime);
        
        if (window_focus) {
            window.clear(sf::Color {0, 100, 20});
            
            view.setCenter(World::get_iso_pos(world.player.get_central_point()));
            window.setView(view);
            window.draw(world);
            
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            if (world.player.active_dialogue != nullptr) {
                window.draw(*world.player.active_dialogue);
            }
        }
        window.display();
    }

    return 0;
}
