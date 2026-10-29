#include "RHUnk0060c2xx.h"
#include "RHUnk0060c2c0.h"
#include "RHUnk005fc3b0.h"

DECOMP_SIZE_ASSERT(RHUnk0060c2c0, 0x2c)

// FUNCTION: GAME 0x0060c250
unsigned long RHUnk0060c2xx::FUN_0060c250() const
{
    return (unsigned long)((const RHUnk0053bf20 *)this)->FUN_0053bf20();
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

// FUNCTION: GAME 0x0060c2c0
RHUnk0060c2c0::RHUnk0060c2c0()
{
    m_24 = 3;
    m_28 = 1;
    m_29 = 1;
    m_26 = 7;
}

// FUNCTION: GAME 0x0060c2e0
unsigned short RHUnkSectorPoints::FUN_0060c2e0()
{
    SBGeoVector2D previous;
    SBGeoVector2D current;
    SBGeoPoint2D before;
    SBGeoPoint2D at;
    SBGeoPoint2D next;
    if (m_28)
        return m_24;
    bool negative = false;
    bool positive = false;
    unsigned last = Unk0060ce80();
    if (last <= 2)
    {
        m_24 = 3;
        m_28 = 1;
        return 1;
    }
    --last;
    if (m_24 == 1)
        return 1;
    before = Unk0060cef0(last - 1);
    at = Unk0060cef0(last);
    previous = at.Unk005fc110(before);
    for (unsigned i = 0; i <= last; ++i)
    {
        next = Unk0060cef0(i);
        current = next.Unk005fc110(at);
        float cross = ((RHUnk005fc3b0 *)&previous)->FUN_005fc680((const RHUnk005fc3b0 &)current, 1.0f);
        if (cross < 0.0f)
            negative = true;
        else if (cross > 0.0f)
            positive = true;
        if (positive && negative)
        {
            m_24 = 4;
            m_26 = 0;
            m_28 = 1;
            m_29 = 1;
            return 4;
        }
        at = next;
        previous = current;
    }
    if (positive)
        m_26 = 5;
    else if (negative)
        m_26 = 6;
    else
        m_26 = 7;
    m_24 = 3;
    m_28 = 1;
    m_29 = 1;
    return 3;
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

// FUNCTION: GAME 0x0060ce80
unsigned int RHUnkSectorPoints::Unk0060ce80()
{
    return ((const RHMobileUnk00611360 *)this)->FUN_00610f30();
}
