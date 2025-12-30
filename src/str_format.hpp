#pragma once

#include <stdexcept>



const int FORMAT_BUFFER_SIZE = 255;

class FormatError: public std::runtime_error {
public:
    FormatError(const char* msg): std::runtime_error(msg) {}
};

template<typename T>
wchar_t* wstr_format(const wchar_t* _format, T arg) {
    const wchar_t* arg_str = std::to_wstring(arg).c_str();
    wchar_t* out = new wchar_t[FORMAT_BUFFER_SIZE+1];
    bool inserted = false;
    int o_i=0, f_i=0, a_i=0;
    while (o_i < FORMAT_BUFFER_SIZE && _format[f_i] != '\0') {
        if (inserted)
            out[o_i++] = _format[f_i++];
        else {
            if (_format[f_i] == '{') {
                if (arg_str[a_i] == '\0')
                    ++f_i;
                else
                    out[o_i++] = arg_str[a_i++];
            } else {
                if (_format[f_i] == '}') {
                    inserted = true;
                    ++f_i;
                } else
                    out[o_i++] = _format[f_i++];
            }
        }
    }
    if (o_i >= FORMAT_BUFFER_SIZE)
        throw FormatError("Format buffer overflow");
    out[o_i] = '\0';
    return out;
}

template<typename T>
wchar_t* wstr_format(wchar_t* _format, T arg) {
    const wchar_t* arg_str = std::to_wstring(arg).c_str();
    wchar_t* out = new wchar_t[FORMAT_BUFFER_SIZE+1];
    bool inserted = false;
    int o_i=0, f_i=0, a_i=0;
    while (o_i < FORMAT_BUFFER_SIZE && _format[f_i] != '\0') {
        if (inserted)
            out[o_i++] = _format[f_i++];
        else {
            if (_format[f_i] == '{') {
                if (arg_str[a_i] == '\0')
                    ++f_i;
                else
                    out[o_i++] = arg_str[a_i++];
            } else {
                if (_format[f_i] == '}') {
                    inserted = true;
                    ++f_i;
                } else
                    out[o_i++] = _format[f_i++];
            }
        }
    }
    delete _format;
    if (o_i >= FORMAT_BUFFER_SIZE)
        throw FormatError("Format buffer overflow");
    out[o_i] = '\0';
    return out;
}