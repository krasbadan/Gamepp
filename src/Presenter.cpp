#include "Presenter.hpp"

#include "SFML/Graphics.hpp"

#include "Player.hpp"
#include "World.hpp"



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