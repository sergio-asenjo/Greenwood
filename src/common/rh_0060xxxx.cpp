#include "SBGeoPoint2D.h"

class RHUnk00606040 : public SBGeoPoint2D
{
public:
    RHUnk00606040(const RHUnk00606040 &other);
    short m_8;
    short m_a;
};

// FUNCTION: GAME 0x00606040
RHUnk00606040::RHUnk00606040(const RHUnk00606040 &other)
    : SBGeoPoint2D(other)
{
    m_8 = other.m_8;
    m_a = other.m_a;
}
