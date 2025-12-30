#pragma once

#include <stdexcept>



const int FORMAT_BUFFER_SIZE = 255;

class FormatError: public std::runtime_error {
public:
    FormatError(const char* msg): std::runtime_error(msg) {}
};



wchar_t* wstr_format(const wchar_t* _format, const wchar_t* arg_str);
wchar_t* wstr_format(wchar_t* _format, const wchar_t* arg_str);

wchar_t* wstr_format(const wchar_t* _format, wchar_t* arg_str);
wchar_t* wstr_format(wchar_t* _format, wchar_t* arg_str);

wchar_t* wstr_format(const wchar_t* _format, int arg);
wchar_t* wstr_format(wchar_t* _format, int arg);



/*template<typename T>
wchar_t* wstr_format(const wchar_t* _format, T arg) {
    return wstr_format(_format, std::to_wstring(arg).c_str());
}

template<typename T>
wchar_t* wstr_format(wchar_t* _format, T arg) {
    return wstr_format(_format, std::to_wstring(arg).c_str());
}*/
