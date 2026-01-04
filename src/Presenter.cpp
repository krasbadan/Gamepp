#include "Presenter.hpp"

#include <SFML/Graphics.hpp>

#include "str_format.hpp"

#include "Economy.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "World.hpp"



TextureManager Tx;
FontManager Fx;



Dialogue* WindowInteractable::interact() {
    return nullptr;
}
sf::Vector2f WindowInteractable::get_interact_pos() const {
    return sf::Vector2f(0.f, 0.f);
}
float WindowInteractable::get_interact_distance() const {
    return INFINITY;
}



void Presenter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f screen_size = target.getView().getSize();
    
    if (active_dialogue != nullptr) {
        target.draw(*active_dialogue);
    }
    
    float margin = 0.02f*std::min(screen_size.x, screen_size.y);
    float font_size = 2.f*margin;
    
    Time time = player->worldptr->time;
    sf::Text sf_text(Fx["cambria.ttc"], wstr_format(wstr_format(L"{}:{}", time.days), (int)floor(time.seconds)), font_size);
    sf_text.setFillColor({255, 255, 255});
    sf_text.setOutlineColor({0, 0, 0});
    sf_text.setOutlineThickness(-0.05f*font_size);
    sf_text.setPosition({margin, margin});
    target.draw(sf_text, states);
    
    target.draw(*player->worldptr->player_economy, states);
}

Presenter::Presenter(Player* _player):
    n_E_like_keys(default_n_E_like_keys),
    E_like_scancodes(default_E_like_scancodes),
    E_like_names(default_E_like_names),
    
    player(_player),
    active_dialogue(nullptr)
{
    available_interactables = new Interactable*[n_E_like_keys];
    for (int i=0; i<n_E_like_keys; ++i)
        available_interactables[i] = nullptr;
    
    window_interactable = new WindowInteractable;
}
Presenter::~Presenter() {
    delete window_interactable;
}

bool Presenter::check_input_move_up() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);
}
bool Presenter::check_input_move_down() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S);
}
bool Presenter::check_input_move_left() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
}
bool Presenter::check_input_move_right() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D);
}
bool Presenter::check_input_space() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space);
}
bool Presenter::check_input_shift() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift);
}

void Presenter::update_presentation() {
    for (int ai = 0; ai < n_E_like_keys; ++ai) {
        available_interactables[ai] = nullptr;
    }
    
    int ai = 0;
    for (Interactable* inter : player->worldptr->interactables) {
        sf::Vector2f iLogicPos = inter->get_interact_pos();
        
        if ((iLogicPos - player->getPosition()).length() <= inter->get_interact_distance()) {
            if (ai < n_E_like_keys) {
                inter->key_name = E_like_names[ai];
                available_interactables[ai++] = inter;
            } else {
                inter->key_name = nullptr;
            }
        }
    }
    
    // Quit active dialogue if distance to interactable is 1.5f times more than interact distance
    if (active_dialogue != nullptr) {
        Interactable* inter = active_dialogue->interactable;
        if ((player->getPosition() - inter->get_interact_pos()).length() > 1.5f*inter->get_interact_distance()) {
            delete active_dialogue;
            active_dialogue = nullptr;
        }
    }
}



void update_view_size(const sf::RenderWindow& window, sf::View& view, const float& zoomout) {
    view.setSize(sf::Vector2f(window.getSize())*zoomout);
};

void Presenter::main() {
    sf::RenderWindow window(sf::VideoMode({864, 486}), "Game++");
    sf::Clock clock;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    bool window_focus = true;
    float zoomout = 0.015;
    sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())*zoomout));
    
    Interactable* window_interactable = new WindowInteractable();
    
    
    
    const auto onClosed = [&window](const sf::Event::Closed& event) {
        window.close();
    };
    const auto onKeyPressed = [this, &window, &window_interactable](const sf::Event::KeyPressed& event) {
        Dialogue* ad;
        
        switch (event.scancode) {
            case sf::Keyboard::Scancode::Escape:
                ad = active_dialogue;
                if (ad == nullptr) {
                    active_dialogue = new Dialogue(
                        window_interactable,
                        L"Выйти из игры?",
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
                    active_dialogue = nullptr;
                }
                break;
            case sf::Keyboard::Scancode::Up:
                ad = active_dialogue;
                if (ad != nullptr && ad->get_n_options() != 0) {
                    ad->set_active_option(mod(ad->get_active_option() - 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Down:
                ad = active_dialogue;
                if (ad != nullptr && ad->get_n_options() != 0) {
                    ad->set_active_option(mod(ad->get_active_option() + 1, ad->get_n_options()));
                }
                break;
            case sf::Keyboard::Scancode::Enter:
                ad = active_dialogue;
                if (ad != nullptr) {
                    if (ad->get_n_options() == 0) {
                        delete ad;
                        active_dialogue = nullptr;
                    } else {
                        Dialogue* new_dial = ad->choose_active_option();
                        delete ad;
                        active_dialogue = new_dial;
                    }
                }
                break;
            default:
                for (int ai = 0; ai < n_E_like_keys; ++ai) {
                    if (event.scancode == E_like_scancodes[ai] && available_interactables[ai] != nullptr) {
                        delete active_dialogue;
                        active_dialogue = available_interactables[ai]->interact();
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
        player->worldptr->update(deltaTime);
        
        if (window_focus) {
            update_presentation();
            
            window.clear(sf::Color {0, 100, 20});
            
            view.setCenter(World::get_iso_pos(player->getPosition() - sf::Vector2f(1, 1)/1.5));
            window.setView(view);
            window.draw(*player->worldptr);
            
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            window.draw(*this);
        }
        window.display();
    }
}