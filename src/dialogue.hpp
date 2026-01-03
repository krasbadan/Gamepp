#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>

#include "Utils.hpp"



class DialogueError: public std::runtime_error {
public:
    DialogueError(const char* msg): std::runtime_error(msg) {}
};



class Dialogue;



class DialogueOption: public sf::Drawable {
    friend Dialogue;
    
    wchar_t* text;
    std::function<Dialogue* ()> func;
    bool is_active;
    
    DialogueOption();
    
    static float calculate_margin(sf::Vector2f screen_size);
    static sf::Vector2f calculate_size(sf::Vector2f screen_size, float margin);
    
    static float calculate_font_size(sf::Vector2f option_size);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    DialogueOption(const wchar_t* _text, std::function<Dialogue* ()> _func);
    DialogueOption(wchar_t* _text, std::function<Dialogue* ()> _func);
    
    Dialogue* operator()();
    
    friend std::wostream& operator<<(std::wostream& os, const DialogueOption& self);
};

std::wostream& operator<<(std::wostream& os, const DialogueOption& self);



class Dialogue: public sf::Drawable {
    wchar_t* text;
    int n_options;
    int active_option;
    DialogueOption* options;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Interactable* interactable;
    
    Dialogue(Interactable* _interactable, const wchar_t* _text, const std::initializer_list<DialogueOption> &list);
    Dialogue(Interactable* _interactable, wchar_t* _text, const std::initializer_list<DialogueOption> &list);
    ~Dialogue();
    
    int get_n_options() const;
    int get_active_option() const;
    void set_active_option(int index);
    
    Dialogue* choose_active_option();
    Dialogue* choose_option(int index);
    
    friend std::wostream& operator<<(std::wostream& os, const Dialogue& self);
};

std::wostream& operator<<(std::wostream& os, const Dialogue& self);