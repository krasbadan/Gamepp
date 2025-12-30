#include "Presenter.hpp"

#include "SFML/Graphics.hpp"



Presenter::Presenter():
    n_E_like_keys(default_n_E_like_keys),
    E_like_scancodes(default_E_like_scancodes),
    E_like_names(default_E_like_names),
    
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