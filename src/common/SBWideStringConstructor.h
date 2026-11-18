#ifndef SBWIDESTRINGCONSTRUCTOR_H
#define SBWIDESTRINGCONSTRUCTOR_H

#include "SBNullstr.h"

#pragma inline_depth(0)
namespace std {
template<> inline basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(const allocator_type &_Al)
    : allocator(_Al) {_Tidy(); }
}
#pragma inline_depth(8)

#endif
