#pragma once

#include <functional>
#include <iostream>

#include "Utils.hpp"



class Dialogue;



class DialogueOption: public sf::Drawable {
    friend Dialogue;
    
    const char* text;
    std::function<Dialogue* ()> func;
    
    DialogueOption(): text(""), func() {}
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        sf::RectangleShape rect({1.f, 1.f});
        rect.setFillColor({0, 0, 0});
        rect.setOutlineThickness(0.05f);
        target.draw(rect, states);
    }
public:
    DialogueOption(const char* _text, std::function<Dialogue* ()> _func):
        text(_text), func(_func)
    {}
    
    Dialogue* operator()() {
        return func();
    }
    
    friend std::ostream& operator<<(std::ostream& os, const DialogueOption& self);
};

std::ostream& operator<<(std::ostream& os, const DialogueOption& self) {
    return os << self.text;
}



class Dialogue: public sf::Drawable {
    const char* text;
    int n_options;
    DialogueOption* options;
public:
    Dialogue(const char* _text, int _n_options, const std::initializer_list<DialogueOption> &list):
        text(_text), n_options(_n_options)
    {
        options = new DialogueOption[_n_options];
        int i = 0;
        for (DialogueOption x : list) {
            options[i] = x;
            ++i;
        }
    }
    
    int get_n_options() const {
        return n_options;
    }
    
    Dialogue* choose_option(int index) {
        return options[index]();
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Dialogue& self);
};

std::ostream& operator<<(std::ostream& os, const Dialogue& self) {
    os << self.text << std::endl;
    for (int i=0; i < self.n_options; ++i) {
        os << i << ") " << self.options[i] << std::endl;
    }
    return os;
}