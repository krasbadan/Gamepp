#pragma once

#include <cstring>
#include <stdexcept>



class StrFormatError: public std::runtime_error {
public:
    StrFormatError(const char* msg): std::runtime_error(msg) {}
};



wchar_t* wstr_format(const wchar_t* _format, const wchar_t* arg_wstr);
wchar_t* wstr_format(const wchar_t* _format, wchar_t* arg_wstr);
wchar_t* wstr_format(wchar_t* _format, const wchar_t* arg_wstr);
wchar_t* wstr_format(wchar_t* _format, wchar_t* arg_wstr);

wchar_t* wstr_format(const wchar_t* _format, const char* arg_str);
wchar_t* wstr_format(const wchar_t* _format, const std::string arg);

template<typename arg_T>
wchar_t* wstr_format(const wchar_t* _format, arg_T arg) {
    return wstr_format(_format, std::to_wstring(arg).c_str());
}

template<typename arg_T>
wchar_t* wstr_format(wchar_t* _format, arg_T arg) {
    wchar_t* out = wstr_format(const_cast<const wchar_t*>(_format), arg);
    delete[] _format;
    return out;
}
