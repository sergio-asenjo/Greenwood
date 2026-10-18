#include "RHElementMobile.h"

class RHUnk00609170
{
public:
    int FUN_00609170(const RHUnk00609170 &other) const;
    SBGeoPoint2D m_00;
    SBGeoPoint2D m_08;
    unsigned char m_10;
};

// FUNCTION: GAME 0x00609170
int RHUnk00609170::FUN_00609170(const RHUnk00609170 &other) const
{
    if (other.m_00 == m_00 && other.m_08 == m_08)
        return 0;
    return 1;
}
