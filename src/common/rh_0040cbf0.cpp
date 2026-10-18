#include "SBGeoPoint2D.h"

struct RHUnk004237d0Holder
{
    char m_00[0x10];
    float m_10;
    float m_14;
};

class RHUnk004237d0
{
public:
    SBGeoPoint2D FUN_004237d0();
    char m_00[0x50];
    RHUnk004237d0Holder *m_50;
};

// FUNCTION: GAME 0x004237d0
SBGeoPoint2D RHUnk004237d0::FUN_004237d0()
{
    return SBGeoPoint2D(m_50->m_10, m_50->m_14);
}
