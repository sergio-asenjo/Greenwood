#include "Decomp.h"
// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14]; // 0x00
};
#include "RHDrawManager.h"
#include <math.h>

DECOMP_SIZE_ASSERT(SBDrawViewport, 0x14)
DECOMP_SIZE_ASSERT(RHDrawManager, 0x20)

// GLOBAL: GAME 0x006c0814
RHDrawManager *RHDrawManager::mpDrawManager;

// GLOBAL: GAME 0x00677688
double g_unk0x00677688 = 0.573576436351046;

// FUNCTION: GAME 0x00460a60
RHDrawManager::RHDrawManager(SBDrawManager *drawManager)
{
    mpDrawManager = this;
    m_drawManager = drawManager;
}

// FUNCTION: GAME 0x00460a80
bool RHDrawManager::CheckPointForDrawing(short x, short y, unsigned short width, unsigned short height)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

// FUNCTION: GAME 0x00460ad0
void RHDrawManager::DrawEllipsePoints(const SBDrawViewport &viewport, const SBGeoPoint2D &center, short x, short y, unsigned short color)
{
    unsigned short width = viewport.m_width;
    unsigned short height = viewport.m_height;
    if (CheckPointForDrawing((short)(x + center.m_x), (short)(y + center.m_y), width, height))
        viewport.m_pixels[(int)(y + center.m_y) * (viewport.m_pitch >> 1) + (int)(x + center.m_x)] = color;
    if (CheckPointForDrawing((short)(x + center.m_x), (short)(center.m_y - y), width, height))
        viewport.m_pixels[(int)(center.m_y - y) * (viewport.m_pitch >> 1) + (int)(x + center.m_x)] = color;
    if (CheckPointForDrawing((short)(center.m_x - x), (short)(y + center.m_y), width, height))
        viewport.m_pixels[(int)(y + center.m_y) * (viewport.m_pitch >> 1) + (int)(center.m_x - x)] = color;
    if (CheckPointForDrawing((short)(center.m_x - x), (short)(center.m_y - y), width, height))
        viewport.m_pixels[(int)(center.m_y - y) * (viewport.m_pitch >> 1) + (int)(center.m_x - x)] = color;
}

// FUNCTION: GAME 0x00460c90
void RHDrawManager::DrawSegment(const SBGeoSegment2D &segment, unsigned short color)
{
    RHUnk0060fbf0 clipped;
    clipped.FUN_0060fca0(FUN_006093f0(segment));
    if (((SCQuadArg *)&clipped)->GetType() == 4)
    {
        SBGeoPoint2D first;
        SBGeoPoint2D second;
        first = ((SBGeoSegment2D *)((RHUnk0053bf20 *)&clipped)->FUN_0053bf20())->First().Unk005fc110(m_min);
        second = ((SBGeoSegment2D *)((RHUnk0053bf20 *)&clipped)->FUN_0053bf20())->Second().Unk005fc110(m_min);
        if (m_14 != 1.0f)
        {
            first.m_x *= m_14;
            first.m_y *= m_14;
            second.m_x *= m_14;
            second.m_y *= m_14;
        }
        m_drawManager->FUN_005ecbd0(m_18, first, second, color);
    }
}

// FUNCTION: GAME 0x00460e10
void RHDrawManager::FillBox(const SBGeoBoundingBox2D &box, unsigned short color)
{
    RHUnk0060fbf0 unused;
    SBGeoBoundingBox2D clipped;
    if ((unsigned char)((RHUnk00608f10 *)this)->FUN_00608f10((void *)&box))
    {
        ((RHMobileUnk00607da0 *)&clipped)->FUN_00607da0((const RHMobileUnk00607da0 &)FUN_006092c0(box));
        {
            SBGeoVector2D offset(static_cast<const SBGeoVector2D &>(m_min));
            clipped.FUN_006092a0(offset);
        }
        if (m_14 != 1.0f)
        {
            clipped.m_10 = true;
            clipped.m_min.m_x *= m_14;
            clipped.m_min.m_y *= m_14;
            clipped.m_max.m_x *= m_14;
            clipped.m_max.m_y *= m_14;
        }
        m_drawManager->FUN_005e61e0(m_18, clipped, color, 0);
    }
}

// FUNCTION: GAME 0x00460f60
void RHDrawManager::DrawPolyLine(const SBGeoPolyLine2DList &list, unsigned short color)
{
    unsigned long count = (unsigned long)((RHUnk0053bf20 *)&list)->FUN_0053bf20();
    if (count >= 2)
    {
        bool second = false;
        SBGeoSegment2D segment(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
        RHUnk0060fbf0 clipped;
        segment.First() = list.FUN_00610cb0(0);
        for (unsigned long i = 1; i < count; i++)
        {
            if (second)
            {
                segment.First() = list.FUN_00610cb0(i);
                second = false;
            }
            else
            {
                segment.Second() = list.FUN_00610cb0(i);
                second = true;
            }
            clipped.FUN_0060fca0(FUN_006093f0(segment));
            if (((SCQuadArg *)&clipped)->GetType() == 4)
            {
                SBGeoPoint2D first;
                SBGeoPoint2D last;
                first = ((SBGeoSegment2D *)((RHUnk0053bf20 *)&clipped)->FUN_0053bf20())->First().Unk005fc110(m_min);
                last = ((SBGeoSegment2D *)((RHUnk0053bf20 *)&clipped)->FUN_0053bf20())->Second().Unk005fc110(m_min);
                if (m_14 != 1.0f)
                {
                    first.m_x *= m_14;
                    first.m_y *= m_14;
                    last.m_x *= m_14;
                    last.m_y *= m_14;
                }
                m_drawManager->FUN_005ecbd0(m_18, first, last, color);
            }
        }
    }
}

// Parked 84.12%: VC6 orders the offset/scale temporaries and loop guard differently.
// STUB: GAME 0x004611d0
void RHDrawManager::DrawDottedLine(const SBGeoPoint2D &from, const SBGeoPoint2D &to, float &phase, float dash, float thickness, unsigned short color)
{
    RHUnk0060fbf0 unused;
    SBGeoPoint2D direction = to.Unk005fc110(from);
    float length = ((RHUnk005fc3b0 *)&direction)->Unk005fc6a0(1.0f);
    if (length < phase)
    {
        if (length != g_unk0x00677488)
            phase -= length;
    }
    else
    {
        ((RHUnk005fc3b0 *)&direction)->FUN_005fc4d0(g_unk0x0067749c / length);
        SBGeoPoint2D start;
        start.m_x = direction.m_x * phase + from.m_x;
        start.m_y = direction.m_y * phase + from.m_y;
        SBGeoVector2D offset(m_min);
        ((RHUnk005fc3b0 *)&direction)->FUN_005fc4d0(dash);
        float remaining = length - phase;
        unsigned long count = (unsigned long)(remaining / dash);
        float covered = count * dash;
        phase = covered + (dash - remaining);
        for (unsigned long i = 0; i != count + 1; i++)
        {
            SBGeoBoundingBox2D box;
            box.FUN_00609050(SBGeoPoint2D(start.m_x - thickness, start.m_y - thickness), SBGeoPoint2D(start.m_x + thickness, start.m_y + thickness));
            ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)FUN_006092c0(box));
            if (box.Unk00608f30())
            {
                box.FUN_006092a0(offset);
                box.SetMin(m_14 * SBGeoVector2D(box.m_min));
                box.SetMax(m_14 * SBGeoVector2D(box.m_max));
                m_drawManager->FUN_005e61e0(m_18, box, color, 0);
            }
            start.FUN_005fc1e0(direction);
        }
    }
}

// FUNCTION: GAME 0x004615a0
unsigned short RHDrawManager::GetPackedColor(unsigned long color)
{
    switch (m_drawManager->m_10c)
    {
    case 15:
        return (unsigned short)((((((color >> 3) & 0x1f0000) | (color & 0xf800)) >> 3) | (color & 0xf8)) >> 3);
    case 16:
        return (unsigned short)((((((color >> 3) & 0x1f0000) | (color & 0xfc00)) >> 2) | (color & 0xf8)) >> 3);
    }
    return 0;
}

// FUNCTION: GAME 0x00461610
void RHDrawManager::DrawEllipse(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color)
{
    SBGeoPoint2D position;
    position = center.Unk005fc110(m_min);
    if (m_14 != 1.0f)
    {
        position.m_x *= m_14;
        position.m_y *= m_14;
        radius = (unsigned short)(radius * m_14);
    }
    float a = radius;
    float b = radius * g_unk0x00677688;
    short y = (short)b;
    short x = 0;
    float a2 = a * a;
    float b2 = b * b;
    float quarter = a2;
    float d = b2 - a2 * b + quarter * g_actorStepScale;
    DrawEllipsePoints(viewport, position, x, y, color);
    while (a2 * (y - g_unk0x006774b8) > b2 * (x + 1))
    {
        if (d < g_unk0x00677488)
        {
            d += b2 * (2 * x + 3);
            x++;
        }
        else
        {
            d += a2 * (2 - 2 * y) + b2 * (2 * x + 3);
            x++;
            y--;
        }
        DrawEllipsePoints(viewport, position, x, y, color);
    }
    d = b2 * pow(x + g_unk0x006774b8, g_unk0x00677670) + a2 * pow(y - 1, g_unk0x00677670) - b2 * a2;
    while (y > 0)
    {
        if (d < g_unk0x00677488)
        {
            d += a2 * (3 - 2 * y) + b2 * (2 * x + 2);
            x++;
            y--;
        }
        else
        {
            d += a2 * (3 - 2 * y);
            y--;
        }
        DrawEllipsePoints(viewport, position, x, y, color);
    }
}

// FUNCTION: GAME 0x004618f0
void RHDrawManager::DrawCircle(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color)
{
    SBGeoPoint2D position;
    position = center.Unk005fc110(m_min);
    if (m_14 != 1.0f)
    {
        position.m_x *= m_14;
        position.m_y *= m_14;
        radius = (unsigned short)(radius * m_14);
    }
    float a = radius;
    float b = radius;
    short y = (short)b;
    short x = 0;
    float a2 = a * a;
    float b2 = b * b;
    float quarter = a2;
    float d = b2 - a2 * b + quarter * g_actorStepScale;
    DrawEllipsePoints(viewport, position, x, y, color);
    while (a2 * (y - g_unk0x006774b8) > b2 * (x + 1))
    {
        if (d < g_unk0x00677488)
        {
            d += b2 * (2 * x + 3);
            x++;
        }
        else
        {
            d += a2 * (2 - 2 * y) + b2 * (2 * x + 3);
            x++;
            y--;
        }
        DrawEllipsePoints(viewport, position, x, y, color);
    }
    d = b2 * pow(x + g_unk0x006774b8, g_unk0x00677670) + a2 * pow(y - 1, g_unk0x00677670) - b2 * a2;
    while (y > 0)
    {
        if (d < g_unk0x00677488)
        {
            d += a2 * (3 - 2 * y) + b2 * (2 * x + 2);
            x++;
            y--;
        }
        else
        {
            d += a2 * (3 - 2 * y);
            y--;
        }
        DrawEllipsePoints(viewport, position, x, y, color);
    }
}
