// Anonymous cluster at 0x0059fxxx (list-node ctors).
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

class RHUnk0059f6f0List
{
public:
    RHUnk0059f6f0List *m_next;
    RHUnk0059f6f0List *m_prev;
    char m_08[0x08];
};

class RHUnk0059f6f0
{
public:
    RHUnk0059f6f0();
    char m_0[4];
    char m_4;
    char m_5[3];
    RHUnk0059f6f0List *m_8;
    int m_c;
    char m_10[4];
    bool m_14;
};

// FUNCTION: GAME 0x0059f6f0
RHUnk0059f6f0::RHUnk0059f6f0()
{
    char value;
    m_4 = value;
    RHUnk0059f6f0List *list = new RHUnk0059f6f0List;
    list->m_next = list;
    list->m_prev = list;
    m_8 = list;
    m_c = 0;
    m_14 = 1;
}

#include "RHShadowPoolLifetime.h"

// FUNCTION: GAME 0x0059f900
RHUnk0059f900::RHUnk0059f900()
{
    char value;
    m_0 = value;
    RHUnk0059f900List *list = new RHUnk0059f900List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
    m_10 = 1;
}

#include "RHUnk0059fae0.h"

// FUNCTION: GAME 0x0059fae0
RHUnk0059fae0::RHUnk0059fae0() : m_14(1)
{
}
