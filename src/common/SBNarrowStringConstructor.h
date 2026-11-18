#ifndef SBNARROWSTRINGCONSTRUCTOR_H
#define SBNARROWSTRINGCONSTRUCTOR_H

#include "SBNullstr.h"

#pragma inline_depth(0)
namespace std {
template<> inline basic_string<char, char_traits<char>, allocator<char> >::basic_string(const allocator_type &_Al)
    : allocator(_Al) {_Tidy(); }
}
#pragma inline_depth(8)

namespace std {
template<> inline basic_string<char, char_traits<char>, allocator<char> >::basic_string(size_type _N, char _C, const allocator_type &_Al)
    : allocator(_Al)
{
    _Tidy();
    if (_N != 0)
        assign(_N, _C);
}
}

#endif
