#include "str_format.hpp"



wchar_t* wstr_format(const wchar_t* _format, const wchar_t* arg_wstr) {
    wchar_t* out = new wchar_t[std::wcslen(_format) + std::wcslen(arg_wstr) + 1];
    bool inserted = false;
    int o_i=0, f_i=0, a_i=0;
    while (_format[f_i] != '\0') {
        if (inserted)
            out[o_i++] = _format[f_i++];
        else {
            if (_format[f_i] == '{') {
                if (arg_wstr[a_i] == '\0')
                    ++f_i;
                else
                    out[o_i++] = arg_wstr[a_i++];
            } else {
                if (_format[f_i] == '}') {
                    inserted = true;
                    ++f_i;
                } else
                    out[o_i++] = _format[f_i++];
            }
        }
    }
    out[o_i] = '\0';
    return out;
}

wchar_t* wstr_format(const wchar_t* _format, wchar_t* arg_wstr) {
    wchar_t* out = wstr_format(_format, const_cast<const wchar_t*>(arg_wstr));
    delete[] arg_wstr;
    return out;
}
wchar_t* wstr_format(wchar_t* _format, const wchar_t* arg_wstr) {
    wchar_t* out = wstr_format(const_cast<const wchar_t*>(_format), arg_wstr);
    delete[] _format;
    return out;
}
wchar_t* wstr_format(wchar_t* _format, wchar_t* arg_wstr) {
    wchar_t* out = wstr_format(const_cast<const wchar_t*>(_format), const_cast<const wchar_t*>(arg_wstr));
    delete[] _format;
    delete[] arg_wstr;
    return out;
}

wchar_t* wstr_format(const wchar_t* _format, const char* arg_str) {
    int len = std::strlen(arg_str) + 1;
    wchar_t* arg_wstr = new wchar_t[len];
    std::mbstowcs(arg_wstr, arg_str, len);
    return wstr_format(_format, arg_wstr);
}
template wchar_t* wstr_format<const char*>(wchar_t* _format, const char* arg_str);

wchar_t* wstr_format(const wchar_t* _format, const std::string arg) {
    const char* arg_str = arg.c_str();
    int len = std::strlen(arg_str) + 1;
    wchar_t* arg_wstr = new wchar_t[len];
    std::mbstowcs(arg_wstr, arg_str, len);
    return wstr_format(_format, arg_wstr);
}
template wchar_t* wstr_format<const std::string>(wchar_t* _format, const std::string arg);