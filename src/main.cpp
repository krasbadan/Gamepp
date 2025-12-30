#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "dialogue.hpp"

#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Utils.hpp"

#include "Player.hpp"
#include "Presenter.hpp"
#include "World.hpp"
#include "MapObject.hpp"



TextureManager Tx;
FontManager Fx;



class WindowInteractable: public Interactable {
    virtual Dialogue* interact() override {
        return nullptr;
    }
    
    virtual sf::Vector2f get_interact_pos() const override {
        return sf::Vector2f(0.f, 0.f);
    }
    virtual float get_interact_distance() const override {
        return INFINITY;
    }
};



void update_view_size(const sf::RenderWindow& window, sf::View& view, const float& zoomout) {
    view.setSize(sf::Vector2f(window.getSize())*zoomout);
};



int main() {
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Game++");
    sf::Clock clock;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    bool window_focus = true;
    float zoomout = 0.015;
    sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())*zoomout));
    
    
    
    Interactable* window_interactable = new WindowInteractable();
    
    Presenter presenter;
    World world(presenter, 500, 500);
    
    
    
    const auto onClosed = [&window](const sf::Event::Closed& event) {
        window.close();
    };
    const auto onKeyPressed = [&window, &window_interactable, &presenter, &world](const sf::Event::KeyPressed& event) {
        Dialogue* ad;
        
        switch (event.scancode) {
            case sf::Keyboard::Scancode::Escape:
                ad = presenter.active_dialogue;
                if (ad == nullptr) {
                    presenter.active_dialogue = new Dialogue(
                        window_interactable,
                        L"Выйти из игры?",
                        2,
                        {
                            DialogueOption(L"Да", [&window]() -> Dialogue* {
                                window.close();
                                return nullptr;
                            }),
                            DialogueOption(L"Нет", []() -> Dialogue* {
                                return nullptr;
                            }),
                        }
                    );
                } else {
                    delete ad;
                    presenter.active_dialogue = nullptr;
                }
                break;
            case sf::Keyboard::Scancode::Up:
                ad = presenter.active_dialogue;
                if (ad != nullptr && ad->get_n_options() != 0) {
                    ad->set_active_option(mod(ad->get_active_option() - 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Down:
                ad = presenter.active_dialogue;
                if (ad != nullptr && ad->get_n_options() != 0) {
                    ad->set_active_option(mod(ad->get_active_option() + 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Enter:
                ad = presenter.active_dialogue;
                if (ad != nullptr) {
                    if (ad->get_n_options() == 0) {
                        delete ad;
                        presenter.active_dialogue = nullptr;
                    } else {
                        Dialogue* new_dial = ad->choose_active_option();
                        delete ad;
                        presenter.active_dialogue = new_dial;
                    }
                }
                break;
            default:
                for (int ai = 0; ai < presenter.n_E_like_keys; ++ai) {
                    if (event.scancode == presenter.E_like_scancodes[ai] && presenter.available_interactables[ai] != nullptr) {
                        delete presenter.active_dialogue;
                        presenter.active_dialogue = presenter.available_interactables[ai]->interact();
                        break;
                    }
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
            
            view.setCenter(World::get_iso_pos(world.player.getPosition() - sf::Vector2f(1, 1)/1.5));
            window.setView(view);
            window.draw(world);
            
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            if (presenter.active_dialogue != nullptr) {
                window.draw(*presenter.active_dialogue);
            }
        }
        window.display();
    }

    return 0;
}
