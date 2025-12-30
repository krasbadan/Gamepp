#pragma once

#include "Interactable.hpp"
#include "Utils.hpp"



const int default_n_E_like_keys = 4;
const sf::Keyboard::Scancode default_E_like_scancodes[default_n_E_like_keys] = {
    sf::Keyboard::Scancode::E,
    sf::Keyboard::Scancode::F,
    sf::Keyboard::Scancode::G,
    sf::Keyboard::Scancode::H
};
const char* const default_E_like_names[default_n_E_like_keys] = {
    "E",
    "F",
    "G",
    "H"
};

class Presenter: public sf::Drawable {
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    const int n_E_like_keys;
    const sf::Keyboard::Scancode* E_like_scancodes;
    const char* const* const E_like_names;
    
    Interactable* window_interactable;
    Player* const player;
    Dialogue* active_dialogue;
    
    Interactable** available_interactables;
    
    Presenter(Interactable* window_interactable, Player* _player);
    
    bool check_input_move_up();
    bool check_input_move_down();
    bool check_input_move_left();
    bool check_input_move_right();
    bool check_input_space();
    bool check_input_shift();
    
    void update_presentation();
};

