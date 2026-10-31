#include "RHUnk0060c2xx.h"
#include "RHUnk0060c2c0.h"
#include "RHUnk005fc3b0.h"
#include "SBGeoBoundingBox2DCore.h"

DECOMP_SIZE_ASSERT(RHUnk0060c2c0, 0x2c)

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

// FUNCTION: GAME 0x0060be00
bool RHUnk0060c2xx::FUN_0060be00(const SBGeoPoint2D &point) const
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    float targetX = point.m_x;
    float targetY = point.m_y;
    bool convex = m_28 == 3;
    unsigned long last = FUN_0060c250();
    if (last == 0)
        return false;
    --last;
    previous = FUN_0060c2b0(last);
    bool below = previous.m_y < targetY;
    bool above = previous.m_y > targetY;
    float x = previous.m_x;
    float y = previous.m_y;
    bool inside = false;
    float cross1;
    float cross2;
    for (unsigned long index = 0; index <= last; ++index)
    {
        current = FUN_0060c2b0(index);
        float oldX = x;
        float oldY = y;
        x = current.m_x;
        y = current.m_y;
        if (below)
        {
            if (current.m_y == targetY)
            {
                below = false;
                if (current.m_x == targetX)
                    return true;
            }
            else if (current.m_y > targetY)
            {
                bool oldRight = oldX >= targetX;
                bool newRight = current.m_x >= targetX;
                if ((oldRight && newRight) ||
                    ((oldRight || newRight) &&
                        (cross1 = (current.m_x - oldX) * (targetY - oldY),
                         cross2 = (current.m_y - oldY) * (targetX - oldX), !((double)cross1 < (double)cross2))))
                {
                    if (convex && inside)
                        return false;
                    inside = !inside;
                }
                below = false;
                above = true;
                if (oldX == targetX && current.m_x == targetX)
                    return true;
                if (oldRight != newRight && cross1 == cross2)
                    return true;
            }
        }
        else if (above)
        {
            if (current.m_y == targetY)
            {
                if (current.m_x >= targetX)
                {
                    if (convex && inside)
                        return false;
                    inside = !inside;
                }
                above = false;
                if (current.m_x == targetX)
                    return true;
            }
            else if (current.m_y < targetY)
            {
                bool oldRight = oldX >= targetX;
                bool newRight = current.m_x >= targetX;
                if ((oldRight && newRight) ||
                    ((oldRight || newRight) &&
                        (cross1 = (current.m_x - oldX) * (targetY - oldY),
                         cross2 = (current.m_y - oldY) * (targetX - oldX), !((double)cross1 > (double)cross2))))
                {
                    if (convex && inside)
                        return false;
                    inside = !inside;
                }
                above = false;
                below = true;
                if (oldX == targetX && current.m_x == targetX)
                    return true;
                if (oldRight != newRight && cross1 == cross2)
                    return true;
            }
        }
        else if (current.m_y > targetY)
        {
            above = true;
            below = false;
            if (oldX >= targetX)
            {
                if (convex && inside)
                    return false;
                inside = !inside;
            }
        }
        else if (current.m_y < targetY)
        {
            above = false;
            below = true;
        }
        else if ((oldX <= targetX && current.m_x >= targetX) ||
            (oldX >= targetX && current.m_x <= targetX))
            return true;
        previous = current;
    }
    return inside;
}

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

// FUNCTION: GAME 0x0060cab0
float RHUnk0060c2c0::FUN_0060cab0(const SBGeoPoint2D &point, float scale)
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    SBGeoPoint2D target;
    SBGeoVector2D direction;
    SBGeoBoundingBox2D bounds;
    float closest = 1.701411733e38f;
    unsigned count = ((RHUnkSectorPoints *)this)->Unk0060ce80();
    if (count == 0)
        return 1.701411733e38f;
    target = point;
    target.m_y *= scale;
    for (unsigned index = 0; index < count; ++index)
    {
        previous = ((RHUnkSectorPoints *)this)->Unk0060cef0(index);
        previous.m_y *= scale;
        float distance = target.Unk005fc110(previous).FUN_005fc780(1.0f);
        if (distance < closest)
            closest = distance;
    }
    previous = ((RHUnkSectorPoints *)this)->Unk0060cef0(((RHUnkSectorPoints *)this)->Unk0060ce80() - 1);
    previous.m_y *= scale;
    for (unsigned edge = 0; edge < count; ++edge)
    {
        current = ((RHUnkSectorPoints *)this)->Unk0060cef0(edge);
        current.m_y *= scale;
        direction = current.Unk005fc110(previous);
        bool horizontal;
        if (direction.m_x > direction.m_y)
            horizontal = direction.m_x > -direction.m_y;
        else
            horizontal = direction.m_x < -direction.m_y;
        bounds.FUN_00607d90();
        bounds.Unk00607dc0(previous);
        bounds.Unk00607dc0(current);
        float distance;
        if (horizontal)
        {
            if (target.m_x > bounds.m_p0.m_x && target.m_x < bounds.m_p1.m_x &&
                target.m_y > bounds.m_p0.m_y - closest && target.m_y < bounds.m_p1.m_y + closest)
            {
                distance = target.m_y - (((target.m_x - previous.m_x) / direction.m_x) * direction.m_y + previous.m_y);
            }
            else
                distance = 3.402823466e38f;
        }
        else
        {
            if (target.m_y > bounds.m_p0.m_y && target.m_y < bounds.m_p1.m_y &&
                target.m_x > bounds.m_p0.m_x - closest && target.m_x < bounds.m_p1.m_x + closest)
            {
                distance = target.m_x - (((target.m_y - previous.m_y) / direction.m_y) * direction.m_x + previous.m_x);
            }
            else
                distance = 3.402823466e38f;
        }
        if (distance < 0.0f)
            distance = -distance;
        if (distance < closest)
            closest = distance;
        previous = current;
    }
    return closest;
}

// FUNCTION: GAME 0x0060ce80
unsigned int RHUnkSectorPoints::Unk0060ce80()
{
    return ((const RHMobileUnk00611360 *)this)->FUN_00610f30();
}
