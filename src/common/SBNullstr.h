#ifndef SBNULLSTR_H
#define SBNULLSTR_H

#include <string>

void RHConstructWideString(std::wstring *, const std::wstring &);

namespace std {
template<> inline void allocator<std::wstring>::construct(std::wstring *destination, const std::wstring &source)
{
    RHConstructWideString(destination, source);
}
template<> inline const char *__cdecl basic_string<char, char_traits<char>, allocator<char> >::_Nullstr()
{
    return "";
}
}

#endif
