#include "Presenter.hpp"

#include <SFML/Graphics.hpp>

#include "str_format.hpp"

#include "Economy.hpp"
#include "FontManager.hpp"
#include "Player.hpp"
#include "World.hpp"



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

Presenter::Presenter(Interactable* window_interactable, Player* _player):
    n_E_like_keys(default_n_E_like_keys),
    E_like_scancodes(default_E_like_scancodes),
    E_like_names(default_E_like_names),
    
    window_interactable(window_interactable),
    player(_player),
    active_dialogue(nullptr)
{
    available_interactables = new Interactable*[n_E_like_keys];
    for (int i=0; i<n_E_like_keys; ++i)
        available_interactables[i] = nullptr;
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