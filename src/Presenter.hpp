#pragma once

#include "Interactable.hpp"
#include "Utils.hpp"



class WindowInteractable: public Interactable {
    virtual Dialogue* interact() override;
    virtual sf::Vector2f get_interact_pos() const override;
    virtual float get_interact_distance() const override;
};



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
    const int n_E_like_keys;
    const sf::Keyboard::Scancode* E_like_scancodes;
    const char* const* const E_like_names;
    
    Interactable* window_interactable;
    Player* const player;
    Dialogue* active_dialogue;
    
    Interactable** available_interactables;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Interactable* get_window_interactable() const;
    Player* get_player() const;
    Dialogue* get_active_dialogue() const;
    Interactable* const* get_available_interactables() const;

    void set_active_dialogue(Dialogue* _active_dialogue);

    Presenter(Player* _player);
    
    bool check_input_move_up();
    bool check_input_move_down();
    bool check_input_move_left();
    bool check_input_move_right();
    bool check_input_space();
    bool check_input_shift();
    
    void update();
    
    void main();
};

