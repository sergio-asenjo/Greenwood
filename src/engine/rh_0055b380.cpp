// Anonymous cluster at 0x0055b380.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "Decomp.h"
#include "SBGeoVector2D.h"
#include <vector>

class RHUnk0055b320 : public std::vector<SBGeoPoint2D>
{
public:
    RHUnk0055b320();
    undefined4 m_10;
    bool m_14;
    undefined m_18[4];
    SBGeoVector2D m_1c;
};

// FUNCTION: GAME 0x0055b320
RHUnk0055b320::RHUnk0055b320() : m_14(true)
{
}

class SBResourceArrayLifecycle44
{
public:
    void FUN_0051d120();
};

class RHUnk0055b380
{
public:
    RHUnk0055b380();
    void FUN_0055b4d0();
    char m_0;
    char m_1[3];
    int m_4;
    int m_8;
    int m_c;
    char m_10[4];
    bool m_14;
    char m_15[3];
    char m_18[4];
    char m_1c;
    char m_1d[3];
    int m_20;
    int m_24;
    int m_28;
    char m_2c[4];
    bool m_30;
};

// FUNCTION: GAME 0x0055b380
RHUnk0055b380::RHUnk0055b380()
{
    char first;
    char second;
    m_0 = first;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_14 = true;
    *(char volatile *)&m_1c = second;
    m_20 = 0;
    m_24 = 0;
    m_28 = 0;
    m_30 = 1;
}

// FUNCTION: GAME 0x0055b4d0
void RHUnk0055b380::FUN_0055b4d0()
{
    unsigned char *last = (unsigned char *)m_8;
    unsigned char *first = (unsigned char *)m_4;
    while (first != last)
    {
        ((SBResourceArrayLifecycle44 *)first)->FUN_0051d120();
        first += 0x20;
    }
    operator delete((void *)m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}
