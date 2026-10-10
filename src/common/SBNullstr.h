#ifndef SBNULLSTR_H
#define SBNULLSTR_H

#include <string>

namespace std {
template<> inline const char *__cdecl basic_string<char, char_traits<char>, allocator<char> >::_Nullstr()
{
    return "";
}
}

#endif
