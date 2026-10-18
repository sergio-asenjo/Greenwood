#include "RHUnk0060c2xx.h"

unsigned long RHUnk0060c2xx::FUN_0060c250() const
{
    return (unsigned long)((const RHUnk0053bf20 *)this)->FUN_0053bf20();
}

unsigned int RHUnkSectorPoints::Unk0060ce80()
{
    return ((const RHMobileUnk00611360 *)this)->FUN_00610f30();
}

// FUNCTION: GAME 0x0060c260
void RHUnk0060c2xx::FUN_0060c260(const SBGeoPoint2D &point)
{
    m_2c = false;
    m_2d = false;
    FUN_00610a60(point);
}

// FUNCTION: GAME 0x0060c280
void RHUnk0060c2xx::FUN_0060c280()
{
    m_2c = false;
    m_2d = false;
    FUN_00610ac0();
}

// FUNCTION: GAME 0x0060c290
void RHUnk0060c2xx::FUN_0060c290(unsigned long index)
{
    m_2c = false;
    m_2d = false;
    FUN_00610b50(index);
}

// FUNCTION: GAME 0x0060c2b0
const SBGeoPoint2D &RHUnk0060c2xx::FUN_0060c2b0(unsigned long index) const
{
    return FUN_00610cb0(index);
}

// SIZE 0x2c
class RHUnk0060c2c0 : public RHMobileUnk00611360
{
public:
    RHUnk0060c2c0();
    unsigned short m_24; // 0x24
    unsigned short m_26; // 0x26
    bool m_28; // 0x28
    bool m_29; // 0x29
};

// FUNCTION: GAME 0x0060c2c0
RHUnk0060c2c0::RHUnk0060c2c0()
{
    m_24 = 3;
    m_28 = 1;
    m_29 = 1;
    m_26 = 7;
}

void EmitRHUnk0060c2xx(RHUnk0060c2xx *self, const SBGeoPoint2D &point)
{
    void (RHUnk0060c2xx::*add)(const SBGeoPoint2D &) = &RHUnk0060c2xx::FUN_0060c260;
    (self->*add)(point);
    void (RHUnk0060c2xx::*clear)() = &RHUnk0060c2xx::FUN_0060c280;
    (self->*clear)();
    void (RHUnk0060c2xx::*erase)(unsigned long) = &RHUnk0060c2xx::FUN_0060c290;
    (self->*erase)(0);
    const SBGeoPoint2D &(RHUnk0060c2xx::*at)(unsigned long) const = &RHUnk0060c2xx::FUN_0060c2b0;
    (self->*at)(0);
    RHUnk0060c2c0 other;
}
