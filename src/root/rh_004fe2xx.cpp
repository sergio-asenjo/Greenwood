// Anonymous cluster at 0x004fe2xx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe; the element strides are 192 and 160.

#include "RHFastFindRecords.h"

class RHUnk004fe1f0List
{
public:
    RHUnk004fe1f0List *m_next;
    RHUnk004fe1f0List *m_prev;
    char m_08[0x0c];
};

class RHUnk004fe1f0
{
public:
    RHUnk004fe1f0(const char *value);
    char m_0;
    char m_1[3];
    RHUnk004fe1f0List *m_4;
    int m_8;
};

// FUNCTION: GAME 0x004fe1f0
RHUnk004fe1f0::RHUnk004fe1f0(const char *value)
{
    m_0 = *value;
    RHUnk004fe1f0List *list = new RHUnk004fe1f0List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}

// FUNCTION: GAME 0x004fe220
int RHUnk004fe200::FUN_004fe220()
{
    return m_4 == 0 ? 0 : m_8 - m_4;
}

// FUNCTION: GAME 0x004fe250
void RHUnk004fe200::FUN_004fe250(RHUnk004fd7f0 *first, RHUnk004fd7f0 *last)
{
    for (; first != last; ++first)
        first->~RHUnk004fd7f0();
}

// FUNCTION: GAME 0x004fe280
int RHUnk004fe260::FUN_004fe280()
{
    return m_4 == 0 ? 0 : m_8 - m_4;
}

// FUNCTION: GAME 0x004fe2b0
void RHUnk004fe260::FUN_004fe2b0(RHUnk004fda20 *first, RHUnk004fda20 *last)
{
    for (; first != last; ++first)
        first->~RHUnk004fda20();
}

void EmitRHUnk004fe200(RHUnk004fe200 *object)
{
    object->FUN_004fe220();
}

void EmitRHUnk004fe260(RHUnk004fe260 *object)
{
    object->FUN_004fe280();
}
