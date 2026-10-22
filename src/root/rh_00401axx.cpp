// Anonymous cluster at 0x00401axx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Layout is exact from Game.exe: a 16-byte element array with first at +0x8
// and last at +0xc.

#include "SBNullstr.h"
#include <vector>
#include <string.h>
#include "RHUnk00401490.h"

extern char g_unk0x6c0560[4];

// FUNCTION: GAME 0x00401a30
int RHUnk00401a00::FUN_00401a30()
{
    if (m_8 == 0)
        return 0;
    return (int)(m_c - m_8) >> 4;
}

// FUNCTION: GAME 0x00401a50
int RHUnk00401a00::FUN_00401a50(int index)
{
    int *element = (int *)(m_8 + index * 16);
    if (element[1] == 0)
        return 0;
    return (element[2] - element[1]) >> 4;
}

// FUNCTION: GAME 0x00401a80
int RHUnk00401a00::FUN_00401a80(int i, int j)
{
    return *(int *)(m_8 + i * 16 + 4) + j * 16;
}

// FUNCTION: GAME 0x00401aa0
int FUN_00401aa0(const std::vector<std::string> &values)
{
    if (!values.empty() && strcmp(values[0].c_str(), g_unk0x6c0560) != 0)
        return 0;
    return 1;
}

void EmitRHUnk00401a00(RHUnk00401a00 *object)
{
    object->FUN_00401a30();
    object->FUN_00401a50(0);
    object->FUN_00401a80(0, 0);
}

// FUNCTION: GAME 0x00402d60
void *RHUnk00402d60::FUN_00402d60(unsigned flags)
{
    char *last = m_8;
    char *first = m_4;
    while (first != last)
    {
        ((std::string *)first)->~basic_string();
        first += 0x10;
    }
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    if (flags & 1)
        operator delete(this);
    return this;
}
