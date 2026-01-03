#include "Economy.hpp"

#include <cstring>

#include "FontManager.hpp"
#include "map.hpp"
#include "str_format.hpp"



void Economy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f screen_size = target.getView().getSize();
    
    float margin = 0.02f*std::min(screen_size.x, screen_size.y);
    float font_size = 2.f*margin;
    
    wchar_t* wstr = new wchar_t[1024];
    int i = 0;
    for (const std::pair<const std::string, int>& kv : resources) {
        wchar_t* f_wstr = wstr_format(wstr_format(L"{}: {}\n", kv.first), kv.second);
        while (*f_wstr != L'\0') {
            if (i >= 1024)
                throw StrFormatError("i >= 1024");
            wstr[i++] = *(f_wstr++);
        }
    }
    wstr[i] = L'\0';
    
    sf::Text sf_text(Fx["cambria.ttc"], wstr, font_size);
    sf_text.setFillColor({255, 255, 255});
    sf_text.setOutlineColor({0, 0, 0});
    sf_text.setOutlineThickness(-0.05f*font_size);
    sf_text.setPosition({margin, 2*margin + font_size});
    target.draw(sf_text, states);
    
    delete[] wstr;
}