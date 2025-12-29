#pragma once

#include <stdexcept>
#include <string>



const int FORMAT_BUFFER_SIZE = 1023;

class FormatError: public std::runtime_error {
public:
    FormatError(const char* msg): std::runtime_error(msg) {}
};

template<typename T>
const wchar_t* str_format(const wchar_t* _format, T arg) {
    const wchar_t* arg_str = std::to_wstring(arg).c_str();
    wchar_t* out = new wchar_t[FORMAT_BUFFER_SIZE+1];
    int o_i=0, f_i=0, a_i=0;
    while (o_i < FORMAT_BUFFER_SIZE && _format[f_i] != '\0') {
        if (_format[f_i] == '{') {
            if (arg_str[a_i] == '\0')
                ++f_i;
            else
                out[o_i++] = arg_str[a_i++];
        } else {
            if (_format[f_i] == '}')
                ++f_i;
            else
                out[o_i++] = _format[f_i++];
        }
    }
    if (o_i >= FORMAT_BUFFER_SIZE)
        throw FormatError("Format buffer overflow");
    out[o_i] = '\0';
    return out;
}