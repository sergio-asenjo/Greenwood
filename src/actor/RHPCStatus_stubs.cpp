#include "SBNullstr.h"
#include "RHPCStatus.h"

// GLOBAL: GAME 0x006775e0
// std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> >::npos
template class std::basic_string<unsigned short>;

// LIBRARY: GAME 0x0064e850
extern "C" int _stricmp(const char *left, const char *right)
{
    return 0;
}

// LIBRARY: GAME 0x00642bac
extern "C" unsigned int wcslen(const unsigned short *value)
{
    const unsigned short *end = value;
    while (*end)
        ++end;
    return end - value;
}

std::wstring FUN_005e23d0(unsigned long id)
{
    return std::wstring();
}

void FUN_005e0ea0(SBFile &file, std::wstring &value)
{
}
