#include "dialogue.hpp"

#include <cstring>

#include "FontManager.hpp"



DialogueOption::DialogueOption(): func(), is_active(false) {
    text = new wchar_t[1];
    text[0] = L'\0';
}

float DialogueOption::calculate_margin(sf::Vector2f screen_size) {
    //return 0.01*std::min(screen_size.x, screen_size.y);
    return 0.01f*screen_size.y;
}
sf::Vector2f DialogueOption::calculate_size(sf::Vector2f screen_size, float margin) {
    return sf::Vector2f(0.9f*(screen_size.x - 2*margin), 0.075f*screen_size.y);
}
float DialogueOption::calculate_font_size(sf::Vector2f option_size) {
    return 0.6f*option_size.y;;
}

void DialogueOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f screen_size = target.getView().getSize();
    sf::Vector2f option_size = calculate_size(screen_size, calculate_margin(screen_size));
    float font_size = calculate_font_size(option_size);
    float padding = 0.5f*(option_size.y - font_size);
    float border = 0.1f*font_size;
    
    sf::RectangleShape rect(option_size);
    rect.setFillColor(is_active ? sf::Color(0, 32, 0) : sf::Color(0, 0, 0));
    rect.setOutlineColor(is_active ? sf::Color(128, 255, 128) : sf::Color(64, 64, 64));
    rect.setOutlineThickness(-border);
    target.draw(rect, states);
    
    sf::Text sf_text(Fx["cambria.ttc"]);
    sf_text.setString(text);
    sf_text.setCharacterSize(font_size);
    target.draw(sf_text, translate_states(states, sf::Vector2f({padding, padding})));
}

DialogueOption::DialogueOption(const wchar_t* _text, std::function<Dialogue* ()> _func):
    func(_func), is_active(false)
{
    int len = wcslen(_text)+1;
    text = new wchar_t[len];
    memcpy(text, _text, len*sizeof(wchar_t));
}
DialogueOption::DialogueOption(wchar_t* _text, std::function<Dialogue* ()> _func):
    text(_text), func(_func), is_active(false)
{}

Dialogue* DialogueOption::operator()() {
    return func();
}

std::wostream& operator<<(std::wostream& os, const DialogueOption& self) {
    return os << self.text;
}



// Before call, set window.view to true pixel scale as
// window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))))
void Dialogue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f screen_size = target.getView().getSize();
    float margin = DialogueOption::calculate_margin(screen_size);
    sf::Vector2f option_size = DialogueOption::calculate_size(screen_size, margin);
    float font_size = DialogueOption::calculate_font_size(option_size);
    
    sf::Vector2f dialogue_size(option_size.x + 2*margin,
        font_size + 2*margin                  // text
        + n_options*(option_size.y + margin)  // options
    );
    
    float x = 0.5f*(screen_size.x - dialogue_size.x);
    float y = screen_size.y - margin - dialogue_size.y;
    
    sf::RectangleShape rect(dialogue_size);
    rect.setFillColor({0, 0, 0, 128});
    rect.setPosition(sf::Vector2f(x, y));
    target.draw(rect, states);
    x += margin;
    
    sf::Text sf_text(Fx["cambria.ttc"]);
    sf_text.setString(text);
    sf_text.setCharacterSize(font_size);
    sf_text.setPosition(sf::Vector2f(x, y));
    target.draw(sf_text, states);
    y += font_size + 2*margin;
    
    for (int i=0; i<n_options; ++i) {
        target.draw(options[i], translate_states(states, sf::Vector2f(x, y)));
        y += option_size.y + margin;
    }
}

Dialogue::Dialogue(Interactable* _interactable, const wchar_t* _text, const std::initializer_list<DialogueOption> &list):
    interactable(_interactable), n_options(list.size()), active_option(0)
{
    int len = wcslen(_text)+1;
    text = new wchar_t[len];
    memcpy(text, _text, len*sizeof(wchar_t));
    
    if (n_options == 0) {
        options = nullptr;
    } else {
        options = new DialogueOption[n_options];
        int i = 0;
        for (DialogueOption x : list) {
            options[i] = x;
            ++i;
        }
        options[0].is_active = true;
    }
}
Dialogue::Dialogue(Interactable* _interactable, wchar_t* _text, const std::initializer_list<DialogueOption> &list):
    interactable(_interactable), text(_text), n_options(list.size()), active_option(0)
{
    if (n_options == 0) {
        options = nullptr;
    } else {
        options = new DialogueOption[n_options];
        int i = 0;
        for (DialogueOption x : list) {
            options[i] = x;
            ++i;
        }
        options[0].is_active = true;
    }
}
Dialogue::~Dialogue() {
    delete[] text;
    
    for (int i=0; i<n_options; ++i) {
        delete[] options[i].text;
    }
    delete[] options;
}

int Dialogue::get_n_options() const {
    return n_options;
}
int Dialogue::get_active_option() const {
    return active_option;
}
void Dialogue::set_active_option(int index) {
    if (index < 0 || index >= n_options)
        throw DialogueError("New active option index must be in range [0, n_options)");
    options[active_option].is_active = false;
    active_option = index;
    options[active_option].is_active = true;
}

Dialogue* Dialogue::choose_active_option() {
    if (active_option < 0 || active_option >= n_options)
        throw DialogueError("New active option index must be in range [0, n_options)");
    return options[active_option]();
}
Dialogue* Dialogue::choose_option(int index) {
    return options[index]();
}

std::wostream& operator<<(std::wostream& os, const Dialogue& self) {
    os << self.text << std::endl;
    for (int i=0; i < self.n_options; ++i) {
        os << i << ") " << self.options[i] << std::endl;
    }
    return os;
}