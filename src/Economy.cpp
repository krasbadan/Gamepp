#include "Economy.hpp"

#include <cstring>

#include "FontManager.hpp"
#include "Map.hpp"
#include "str_format.hpp"



void Economy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f screen_size = target.getView().getSize();
    
    float margin = 0.02f*std::min(screen_size.x, screen_size.y);
    float font_size = 2.f*margin;
    
    wchar_t* wstr = new wchar_t[1024];
    wchar_t* arg_wstr = new wchar_t[1024];
    int i = 0;
    for (const std::pair<const std::string, int>& kv : resources) {
        const char* arg_str = kv.first.c_str();
        std::mbstowcs(arg_wstr, arg_str, std::strlen(arg_str));
        sf::Text sf_text(Fx["cambria.ttc"], wstr_format(wstr_format(L"{}: {}", arg_wstr), kv.second), font_size);
        sf_text.setFillColor({255, 255, 255});
        sf_text.setOutlineColor({0, 0, 0});
        sf_text.setOutlineThickness(-0.05f*font_size);
        sf_text.setPosition({screen_size.x/2, margin});
        target.draw(sf_text, states);
    }
}