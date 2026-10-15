#include "SBNullstr.h"
#include "RHShadowPolygon.h"
#include <math.h>

DECOMP_SIZE_ASSERT(RHUnk005c9010Node, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005c9010Iterator, 0x04)
DECOMP_SIZE_ASSERT(RHUnk0058e7f0List, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowPolygonList, 0x18)
DECOMP_SIZE_ASSERT(RHShadowPolygonFindList, 0x24)
DECOMP_SIZE_ASSERT(RHShadowAreaBox, 0x14)
DECOMP_SIZE_ASSERT(RHShadowPointListBase, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowPointList<RHShadowPointStdList>, 0x30)
DECOMP_SIZE_ASSERT(RHUnk00597a70, 0xa0)
DECOMP_SIZE_ASSERT(RHUnk005977e0, 0x4c)
DECOMP_SIZE_ASSERT(RHShadowPolygonActorPosition, 0x1c)
DECOMP_SIZE_ASSERT(RHUnk004a96a0, 0x54)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBGeoPoint3D, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowUnk0060c260, 0x30)
DECOMP_SIZE_ASSERT(RHMapBox, 0x14)
DECOMP_SIZE_ASSERT(RHShadowPolygon, 0x218)

// GLOBAL: GAME 0x006774c8
float g_unk0x006774c8 = 40.0f;

// GLOBAL: GAME 0x00677504
float g_unk0x00677504 = 0.573576450347900390625f;

// GLOBAL: GAME 0x00677f9c
float g_unk0x00677f9c = 90.0f;

// Coupled park: 0x004c9d20; annotation breaks DisplayDebug.
void RHEngine::FUN_004c9d20(void *box)
{
    unsigned short count = (unsigned short)FUN_004c9d20Size();
    if (count > 0)
    {
        unsigned remaining = count;
        for (unsigned index = 0; remaining != 0; ++index, --remaining)
        {
            RHUnk004a96a0 *actor = m_48dc[index];
            if (actor->m_10 == 0x1001 && actor->m_50->m_18 == g_unk0x00677488)
                actor->FUN_004a96a0(m_48c4, m_475c, box, false);
        }
    }
}

// FUNCTION: GAME 0x0058c590
void RHShadowPolygon::FUN_0058c590(bool flag, unsigned short width, unsigned short height)
{
    m_64.FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)g_unk0x6c0a9c + 0x3e84));
    m_4c = *(undefined4 *)((char *)g_pEngine + 0x48c4);
    FUN_0058c6f0(flag);
    FUN_0058c630(width, height);
    m_c2 = 0xff;
    m_c4 = 0xff;
    m_c6 = 0xff;
    int value = *(int *)((char *)g_pEngine + 0x4ad0);
    m_60 = value == 4 || value == 2;
    if (m_60)
        m_c0 = 0x78;
    else
        m_c0 = 0xc0;
}

// FUNCTION: GAME 0x0058c630
void RHShadowPolygon::FUN_0058c630(unsigned short width, unsigned short height)
{
    if (m_50)
        operator delete((void *)m_50);
    m_50 = (int)operator new(width * height);
    m_54 = width;
    FUN_0058fe30((const SBGeoBoundingBox2D &)RHMapBox(0.0f, 0.0f, (float)(width - 1), (float)(height - 1)));
}

// FUNCTION: GAME 0x0058c6f0
void RHShadowPolygon::FUN_0058c6f0(bool doubled)
{
    if (doubled == true)
    {
        if (m_4->m_10c == 0xf)
        {
            m_20c = &RHShadowPolygon::FUN_0058cd00;
            m_210 = &RHShadowPolygon::FUN_0058d450;
            m_214 = &RHShadowPolygon::FUN_0058d7e0;
        }
        else
        {
            m_20c = &RHShadowPolygon::FUN_0058c960;
            m_210 = &RHShadowPolygon::FUN_0058d0a0;
            m_214 = &RHShadowPolygon::FUN_0058d630;
        }
    }
    else if (m_4->m_10c == 0xf)
    {
        m_20c = &RHShadowPolygon::FUN_0058cb40;
        m_210 = &RHShadowPolygon::FUN_0058d290;
        m_214 = &RHShadowPolygon::FUN_0058d7e0;
    }
    else
    {
        m_20c = &RHShadowPolygon::FUN_0058c7a0;
        m_210 = &RHShadowPolygon::FUN_0058cee0;
        m_214 = &RHShadowPolygon::FUN_0058d630;
    }
}

// FUNCTION: GAME 0x0058c7a0
void RHShadowPolygon::FUN_0058c7a0(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 2);

    char *pMask = (char *)((m_4->FUN_005e56c0(m_28) & 0xffff) * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; ++y)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x3f) * weight >> 0xe) + (green >> 0x10)) >> 5 & 0x7c0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xb) * weight >> 0xd) + (red >> 0x10)) & 0xf800));
        }
        pMask += m_54;
        pSrc += m_48;
        pDest += m_24;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058c960
void RHShadowPolygon::FUN_0058c960(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if ((x ^ y1) & 1)
    {
        ++y1;
        intensity += intensityDelta;
    }
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 2);
    char *pMask = (char *)((m_4->FUN_005e56c0(m_28) & 0xffff) * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta << 1;
    unsigned int dGreen = m_c4 * intensityDelta << 1;
    unsigned int dBlue = m_c6 * intensityDelta << 1;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    intensityDelta <<= 1;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x3f) * weight >> 0xe) + (green >> 0x10)) >> 5 & 0x7c0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xb) * weight >> 0xd) + (red >> 0x10)) & 0xf800));
        }
        pSrc += m_48 * 2;
        pDest += m_24 * 2;
        pMask += m_54 * 2;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058cb40
void RHShadowPolygon::FUN_0058cb40(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 2);

    char *pMask = (char *)((m_4->FUN_005e56c0(m_28) & 0xffff) * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; ++y)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x1f) * weight >> 0xd) + (green >> 0x10)) >> 6 & 0x3e0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xa) * weight >> 0xd) + (red >> 0x10)) >> 1 & 0x7c00));
        }
        pMask += m_54;
        pSrc += m_48;
        pDest += m_24;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058cd00
void RHShadowPolygon::FUN_0058cd00(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if ((x ^ y1) & 1)
    {
        ++y1;
        intensity += intensityDelta;
    }
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 2);
    char *pMask = (char *)((m_4->FUN_005e56c0(m_28) & 0xffff) * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta << 1;
    unsigned int dGreen = m_c4 * intensityDelta << 1;
    unsigned int dBlue = m_c6 * intensityDelta << 1;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    intensityDelta <<= 1;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x1f) * weight >> 0xd) + (green >> 0x10)) >> 6 & 0x3e0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xa) * weight >> 0xd) + (red >> 0x10)) >> 1 & 0x7c00));
        }
        pSrc += m_48 * 2;
        pDest += m_24 * 2;
        pMask += m_54 * 2;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058cee0
void RHShadowPolygon::FUN_0058cee0(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 4);
    char *pMask = (char *)(m_54 * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; ++y)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            unsigned int value = ((((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 6) & 0x3e0
                | ((((pixel >> 5) & 0x3f) * weight >> 0xe) + (green >> 0x10)) & 0xf800) >> 5)
                | ((((pixel >> 0xb) * weight >> 0xd) + (red >> 0x10)) & 0xf800);
            value |= value << 0x10;
            *(unsigned int *)pDest = value;
            *(unsigned int *)(pDest + m_24) = value;
        }
        pSrc += m_48;
        pDest += m_24 * 2;
        pMask += m_54;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058d0a0
void RHShadowPolygon::FUN_0058d0a0(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if ((x ^ y1) & 1)
    {
        ++y1;
        intensity += intensityDelta;
    }
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 4);
    char *pMask = (char *)(m_54 * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta << 1;
    unsigned int dGreen = m_c4 * intensityDelta << 1;
    unsigned int dBlue = m_c6 * intensityDelta << 1;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    intensityDelta <<= 1;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            unsigned int value = ((((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 6) & 0x3e0
                | ((((pixel >> 5) & 0x3f) * weight >> 0xe) + (green >> 0x10)) & 0xf800) >> 5)
                | ((((pixel >> 0xb) * weight >> 0xd) + (red >> 0x10)) & 0xf800);
            value |= value << 0x10;
            *(unsigned int *)pDest = value;
            *(unsigned int *)(pDest + m_24) = value;
        }
        pSrc += m_48 * 2;
        pDest += m_24 * 4;
        pMask += m_54 * 2;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058d290
void RHShadowPolygon::FUN_0058d290(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 4);
    char *pMask = (char *)(m_54 * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; ++y)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            unsigned int value = (((((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 5) & 0x7c0
                | ((((pixel >> 5) & 0x1f) * weight >> 0xd) + (green >> 0x10)) & 0xf800) >> 5)
                | ((((pixel >> 0xa) * weight >> 0xd) + (red >> 0x10)) & 0xf800)) >> 1;
            value |= value << 0x10;
            *(unsigned int *)pDest = value;
            *(unsigned int *)(pDest + m_24) = value;
        }
        pSrc += m_48;
        pDest += m_24 * 2;
        pMask += m_54;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058d450
void RHShadowPolygon::FUN_0058d450(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if ((x ^ y1) & 1)
    {
        ++y1;
        intensity += intensityDelta;
    }
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * y1 + x) * 4);
    char *pMask = (char *)(m_54 * y1 + m_50 + x);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1) * m_48 + m_90 + x) * 2);
    unsigned int dRed = m_c2 * intensityDelta << 1;
    unsigned int dGreen = m_c4 * intensityDelta << 1;
    unsigned int dBlue = m_c6 * intensityDelta << 1;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    intensityDelta <<= 1;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            unsigned int value = (((((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 5) & 0x7c0
                | ((((pixel >> 5) & 0x1f) * weight >> 0xd) + (green >> 0x10)) & 0xf800) >> 5)
                | ((((pixel >> 0xa) * weight >> 0xd) + (red >> 0x10)) & 0xf800)) >> 1;
            value |= value << 0x10;
            *(unsigned int *)pDest = value;
            *(unsigned int *)(pDest + m_24) = value;
        }
        pSrc += m_48 * 2;
        pDest += m_24 * 4;
        pMask += m_54 * 2;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058d630
void RHShadowPolygon::FUN_0058d630(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * (y1 >> 1) + (x >> 1)) * 2);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1 + 1) * m_48 + m_90 + x + 1) * 2);
    char *pMask = (char *)(m_54 * (y1 >> 1) + m_50 + (x >> 1));
    intensityDelta <<= 1;
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x3f) * weight >> 0xe) + (green >> 0x10)) >> 5 & 0x7c0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xb) * weight >> 0xd) + (red >> 0x10)) & 0xf800));
        }
        pSrc += m_48 * 2;
        pDest += m_24;
        pMask += m_54;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058d7e0
void RHShadowPolygon::FUN_0058d7e0(unsigned short color, int x, int y1, int y2, int intensity, int intensityDelta)
{
    if (y2 <= y1)
        return;
    unsigned short *pDest = (unsigned short *)(m_20 + (m_24 * (y1 >> 1) + (x >> 1)) * 2);
    unsigned short *pSrc = (unsigned short *)(m_44 + ((m_94 + y1 + 1) * m_48 + m_90 + x + 1) * 2);
    char *pMask = (char *)(m_54 * (y1 >> 1) + m_50 + (x >> 1));
    intensityDelta <<= 1;
    unsigned int dRed = m_c2 * intensityDelta;
    unsigned int dGreen = m_c4 * intensityDelta;
    unsigned int dBlue = m_c6 * intensityDelta;
    unsigned int red = m_c2 * intensity;
    unsigned int green = m_c4 * intensity;
    unsigned int blue = m_c6 * intensity;
    unsigned int weight = 0x1000000 - intensity;
    for (int y = y1; y <= y2; y += 2)
    {
        if (*pMask < (char)color)
        {
            unsigned short pixel = *pSrc;
            *pDest = (unsigned short)(((((pixel >> 5) & 0x1f) * weight >> 0xd) + (green >> 0x10)) >> 6 & 0x3e0
                | ((((pixel & 0x1f) * weight >> 0xd) + (blue >> 0x10)) >> 0xb & 0x1f)
                | ((((pixel >> 0xa) * weight >> 0xd) + (red >> 0x10)) >> 1 & 0x7c00));
        }
        pSrc += m_48 * 2;
        pDest += m_24;
        pMask += m_54;
        weight -= intensityDelta;
        red += dRed;
        green += dGreen;
        blue += dBlue;
    }
}

// FUNCTION: GAME 0x0058e7f0
void RHShadowPolygon::DisplayDebug(const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    const float *bounds = (const float *)&box;
    if (bounds[0] < g_unk0x00677488 || bounds[1] < g_unk0x00677488)
        SBAssert(1,
                 // STRING: GAME 0x006b7728
                 "P:\\Robin Hood\\rhshadowpolygon.cpp",
                 3928,
                 // STRING: GAME 0x006b774c
                 "Shadow polygon : unable to zoom in because of too small map !");

    m_28 = flags;
    FUN_00594bf0(box, zoom, actor, point, view);
    FUN_005973f0();
    FUN_0058d990();
    FUN_00595020();
    FUN_005959e0();
    FUN_005971f0();
    FUN_0058ec60();
    g_pEngine->FUN_004c9d20(m_11c);

    for (unsigned short index = 0; index < (int)m_134.m_list.size(); ++index)
    {
        FUN_00597910();
        RHUnk00597a70 *area = m_134[index];
        if (FUN_00597a70(area))
        {
            FUN_0058ffa0(area);
            if (*(unsigned long *)&m_8c == 0x3f800000)
                FUN_00590c90(area);
            else if (m_8c > g_unk0x0067749c)
                FUN_005934b0(area);
            else
                FUN_00592080(area);
        }
    }
}

// FUNCTION: GAME 0x0058ea70
void RHShadowPolygon::FUN_0058ea70()
{
    RHShadowViewport viewport;
    if (((RHUnkFXDraw *)g_unk0x6c11d0)->Unk005e5a00(0, (RHUnk00613e90 &)viewport, 0))
    {
        SBGeoPoint2D center;
        for (short index = -50; index <= 50; ++index)
        {
            float offset = index * g_unk0x00677438;
            float limit = m_a0 * 0.35f;
            if (offset < limit && -offset < limit)
            {
                float radius = sqrt(m_a0 * m_a0 - offset * offset * 8.163265228271484f);
                center.m_x = m_a4.m_0;
                center.m_y = m_a4.m_4 - m_a4.m_8 - offset;
                RHDrawManager::mpDrawManager->DrawEllipse((const SBDrawViewport &)viewport, center, (unsigned short)radius, index ? 0 : 0xfa00);
            }
        }
        float limit = m_a0 * 0.35f;
        if (limit > m_a4.m_8 && -m_a4.m_8 < limit)
        {
            float radius = sqrt(m_a0 * m_a0 - m_a4.m_8 * m_a4.m_8 * 8.163265228271484f);
            float y = m_a4.m_4;
            center.m_x = m_a4.m_0;
            center.m_y = y;
            RHDrawManager::mpDrawManager->DrawEllipse((const SBDrawViewport &)viewport, center, (unsigned short)radius, 0xffff);
        }
        ((RHUnkFXDraw *)g_unk0x6c11d0)->Unk005e5ea0((RHUnk00613e90 &)viewport);
    }
}

#pragma optimize("", off)
// FUNCTION: GAME 0x0058f200
void RHShadowPolygon::FUN_0058f200(RHMask *mask, SBGeoBoundingBox2D &box, unsigned short xOffset, unsigned short lineOffset, unsigned char value)
{
    unsigned char *pDst;
    bool compressed;
    unsigned char *nextRow;
    unsigned short excess;
    unsigned short leftToDo;
    unsigned short xSize;
    unsigned short length;
    int lineSkip;
    unsigned short lineCount;
    unsigned char bitMask;
    unsigned char *pData;
    unsigned short position;
    unsigned short line;
    unsigned char control;

    xSize = (unsigned short)(box.m_8 - box.m_0);
    lineCount = (unsigned short)(box.m_c - box.m_4);
    lineSkip = m_54 - xSize;
    pDst = (unsigned char *)(m_50 + (unsigned short)box.Value4() * m_54 + (unsigned short)box.Value0());
    pData = mask->m_data;
    for (line = 0; line < lineOffset; line++)
        pData = pData + *pData + 1;
    for (line = 0; line < lineCount; line++)
    {
        nextRow = pData + *pData + 1;
        pData++;
        position = 0;
        if (xOffset == 0)
        {
            control = *pData++;
            compressed = (control & 0x80) != 0;
            length = (control & 0x7f) << 3;
            control = *pData++;
            bitMask = 0x80;
        }
        else
        {
            while (position < xOffset)
            {
                control = *pData++;
                length = (control & 0x7f) << 3;
                if (position + length < xOffset)
                {
                    if (control & 0x80)
                        pData++;
                    else
                        pData += control & 0x7f;
                    position += length;
                }
                else
                {
                    excess = xOffset - position;
                    length -= excess;
                    compressed = (control & 0x80) != 0;
                    if (!compressed)
                        pData += excess >> 3;
                    control = *pData++;
                    bitMask = 0x80 >> (xOffset & 7);
                    break;
                }
            }
        }
        leftToDo = xSize;
        while (leftToDo > 0)
        {
            if (length > leftToDo)
                length = leftToDo;
            if (compressed)
            {
                switch (control)
                {
                case 0:
                    pDst += length;
                    break;
                case 0xff:
                    for (position = 0; position < length; position++)
                        *pDst++ = value;
                    break;
                default:
                    for (position = 0; position < length; position++)
                    {
                        if (control & bitMask)
                            *pDst = value;
                        __asm ror bitMask, 1
                        pDst++;
                    }
                    break;
                }
                control = *pData++;
            }
            else
            {
                for (position = 0; position < length; position++)
                {
                    if (control & bitMask)
                        *pDst = value;
                    __asm ror bitMask, 1
                    __asm jnc next
                    control = *pData++;
                next:
                    pDst++;
                }
            }
            leftToDo -= length;
            if (leftToDo == 0)
                break;
            compressed = (control & 0x80) != 0;
            length = (control & 0x7f) << 3;
            control = *pData++;
            bitMask = 0x80;
        }
        pData = nextRow;
        pDst += lineSkip;
    }
}
#pragma optimize("", on)

#pragma optimize("", off)
// FUNCTION: GAME 0x0058f6b0
void RHShadowPolygon::FUN_0058f6b0(RHMask *mask, SBGeoBoundingBox2D &box, unsigned short xOffset, unsigned short lineOffset, unsigned char value)
{
    unsigned short num;
    unsigned char *pDst;
    bool compressed;
    unsigned char *nextRow;
    unsigned short startCol;
    unsigned short maxRow;
    unsigned short excess;
    unsigned short xEnd;
    unsigned short leftToDo;
    unsigned short xSize;
    unsigned short length;
    int lineSkip;
    bool write;
    unsigned short lineCount;
    unsigned char bitMask;
    unsigned short yMin;
    unsigned char *pData;
    unsigned short position;
    unsigned short line;
    unsigned char control;

    startCol = (unsigned short)box.Value0();
    xEnd = (unsigned short)box.Value8();
    yMin = (unsigned short)box.Value4();
    maxRow = (unsigned short)box.ValueC();
    xSize = xEnd - startCol;
    lineCount = maxRow - yMin;
    if (xSize == 0 || lineCount == 0)
        return;
    if (startCol & 1)
    {
        xOffset++;
        startCol++;
        xSize--;
    }
    if (yMin & 1)
    {
        lineOffset++;
        yMin++;
        lineCount--;
    }
    lineSkip = m_54 - ((xSize + 1) >> 1);
    pDst = (unsigned char *)(m_50 + (yMin >> 1) * m_54 + (startCol >> 1));
    pData = mask->m_data;
    for (line = 0; line < lineOffset; line++)
        pData = pData + *pData + 1;
    for (line = 0; line < lineCount; line += 2)
    {
        write = true;
        nextRow = pData + *pData + 1;
        pData++;
        nextRow = nextRow + *nextRow + 1;
        position = 0;
        if (xOffset == 0)
        {
            control = *pData++;
            compressed = (control & 0x80) != 0;
            length = (control & 0x7f) << 3;
            control = *pData++;
            bitMask = 0x80;
        }
        else
        {
            while (position < xOffset)
            {
                control = *pData++;
                length = (control & 0x7f) << 3;
                if (position + length < xOffset)
                {
                    if (control & 0x80)
                        pData++;
                    else
                        pData += control & 0x7f;
                    position += length;
                }
                else
                {
                    excess = xOffset - position;
                    length -= excess;
                    compressed = (control & 0x80) != 0;
                    if (!compressed)
                        pData += excess >> 3;
                    control = *pData++;
                    bitMask = 0x80 >> (xOffset & 7);
                    break;
                }
            }
        }
        leftToDo = xSize;
        while (leftToDo > 0)
        {
            if (length > leftToDo)
                length = leftToDo;
            if (compressed)
            {
                switch (control)
                {
                case 0:
                    if (write)
                    {
                        if (length & 1)
                        {
                            pDst += (length >> 1) + 1;
                            write = false;
                        }
                        else
                        {
                            pDst += length >> 1;
                            write = true;
                        }
                    }
                    else
                    {
                        if (length & 1)
                        {
                            pDst += length >> 1;
                            write = true;
                        }
                        else
                        {
                            pDst += length >> 1;
                            write = false;
                        }
                    }
                    break;
                case 0xff:
                    if (write)
                    {
                        if (length & 1)
                        {
                            num = (length >> 1) + 1;
                            for (position = 0; position < num; position++)
                                *pDst++ = value;
                            write = false;
                        }
                        else
                        {
                            num = length >> 1;
                            for (position = 0; position < num; position++)
                                *pDst++ = value;
                            write = true;
                        }
                    }
                    else
                    {
                        if (length & 1)
                        {
                            num = length >> 1;
                            for (position = 0; position < num; position++)
                                *pDst++ = value;
                            write = true;
                        }
                        else
                        {
                            num = length >> 1;
                            for (position = 0; position < num; position++)
                                *pDst++ = value;
                            write = false;
                        }
                    }
                    break;
                default:
                    for (position = 0; position < length; position++)
                    {
                        if (write)
                        {
                            if (control & bitMask)
                                *pDst = value;
                            pDst++;
                        }
                        __asm ror bitMask, 1
                        write = !write;
                    }
                    break;
                }
                control = *pData++;
            }
            else
            {
                for (position = 0; position < length; position++)
                {
                    if (write)
                    {
                        if (control & bitMask)
                            *pDst = value;
                        pDst++;
                    }
                    __asm ror bitMask, 1
                    __asm jnc next
                    control = *pData++;
                next:
                    write = !write;
                }
            }
            leftToDo -= length;
            if (leftToDo == 0)
                break;
            compressed = (control & 0x80) != 0;
            length = (control & 0x7f) << 3;
            control = *pData++;
            bitMask = 0x80;
        }
        pData = nextRow;
        pDst += lineSkip;
    }
}
#pragma optimize("", on)

#pragma optimize("", off)
// FUNCTION: GAME 0x0058fe30
void RHShadowPolygon::FUN_0058fe30(const SBGeoBoundingBox2D &box)
{
    unsigned short firstX = (unsigned short)box.Value0();
    unsigned short maxX = (unsigned short)box.Value8();
    unsigned short yStart = (unsigned short)box.Value4();
    unsigned short maxY = (unsigned short)box.ValueC();
    unsigned short dwordCount = maxX - firstX;
    unsigned short lineCount = maxY - yStart;
    unsigned char *pMask = (unsigned char *)(m_50 + yStart * m_54 + firstX);
    unsigned short misalign = firstX & 3;
    if (misalign)
    {
        pMask -= misalign;
        dwordCount += misalign;
    }
    misalign = maxX & 3;
    if (misalign)
        dwordCount += 4 - misalign;
    int lineSkip = m_54 - dwordCount;
    dwordCount >>= 2;
    __asm
    {
        cld
        movzx edx, lineCount
        inc edx
        mov edi, pMask
        mov ebx, lineSkip
        movzx esi, dwordCount
        xor eax, eax
        not eax
    next:
        mov ecx, esi
        rep stosd
        add edi, ebx
        dec edx
        jne next
    }
}
#pragma optimize("", on)

// FUNCTION: GAME 0x00594800
void RHShadowPolygon::FUN_00594800(RHUnk00597a70 *item)
{
    unsigned short count = (unsigned short)m_1bc.m_list.size();
    int key = ((RHShadowUnk00594800Item *)item)->m_14;
    for (unsigned short index = 0; index < count; ++index)
    {
        RHShadowPolygonFindList &list = m_1bc;
        list.FUN_005c8e40(index);
        RHShadowUnk00594800Item *current = (RHShadowUnk00594800Item *)*list.m_current;
        if (key < current->m_14 || (key == current->m_14 && ((RHShadowUnk00594800Item *)item)->m_18 < current->m_18))
        {
            m_1bc.InsertAt(index, item);
            return;
        }
    }
    m_1bc.InsertLast(item);
}

// FUNCTION: GAME 0x005949e0
void RHShadowPolygon::FUN_005949e0(RHUnk00597a70 *item)
{
    m_1bc.RemoveAt(m_1bc.Find(item));
}

// FUNCTION: GAME 0x00594b40
void RHShadowPolygon::FUN_00594b40(RHUnk00597a70 *item)
{
    unsigned short index = m_1bc.Find(item);
    if (index + 1 < m_1bc.m_list.m_count)
        m_1bc.SwapWithNext(index);
}

// Coupled park: 0x00594bf0; annotation breaks DisplayDebug.
void RHShadowPolygon::FUN_00594bf0(const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view)
{
    RHUnk005fc3b0 temporary;
    RHUnk005fc3b0 initial;
    RHShadowField<SBGeoBoundingBox2D>(this, 0x78).SetValue0(box.m_0);
    RHShadowField<SBGeoBoundingBox2D>(this, 0x78).SetValue8(box.m_8 - g_unk0x0067749c);
    RHShadowField<SBGeoBoundingBox2D>(this, 0x78).SetValue4(box.m_4);
    RHShadowField<SBGeoBoundingBox2D>(this, 0x78).SetValueC(box.m_c - g_unk0x0067749c);
    m_8c = zoom;
    RHShadowField<int>(this, 0x90) = (int)RHShadowField<SBGeoBoundingBox2D>(this, 0x78).m_0;
    RHShadowField<int>(this, 0x94) = (int)RHShadowField<SBGeoBoundingBox2D>(this, 0x78).m_4;
    RHShadowField<RHElementActor *>(this, 0xbc) = actor;
    m_a4.m_0 = point.m_0;
    m_a4.m_4 = point.m_4;
    m_a4.m_8 = point.m_8;
    RHShadowField<float>(this, 0xb0) = point.m_0;
    RHShadowField<float>(this, 0xb4) = point.m_4;
    RHUnk005fc3b0 &direction = RHShadowField<RHUnk005fc3b0>(this, 0x98);
    direction.FUN_005fc430(RHShadowField<SBGeoPoint2D>(&view, 0x48));
    if (direction.m_x == g_unk0x00677488 && direction.m_y == g_unk0x00677488)
    {
        direction.m_x = 1.0f;
        direction.m_y = 0.0f;
    }
    else
        direction.FUN_005fc7c0(1.0f);
    m_61 = RHShadowField<bool>(&view, 0);
    m_a0 = (float)RHShadowField<unsigned short>(&view, 0x78);
    float extent = RHShadowField<float>(&view, 0x24) + RHShadowField<float>(&view, 0x24);
    RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc430(direction.FUN_005fc9e0(-RHShadowField<float>(&view, 0x24), 1.0f));
    initial.FUN_005fc430(RHShadowField<RHUnk005fc3b0>(this, 0xc8));
    RHShadowField<RHUnk005fc3b0>(this, 0xc8).m_y = RHShadowField<RHUnk005fc3b0>(this, 0xc8).m_y * 0.573576450347900390625f;
    RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc430(direction.FUN_005fc9e0(RHShadowField<float>(&view, 0x24), 1.0f));
    RHShadowField<RHUnk005fc3b0>(this, 0xd0).m_y = RHShadowField<RHUnk005fc3b0>(this, 0xd0).m_y * 0.573576450347900390625f;
    RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c280();
    RHShadowField<SBGeoBoundingBox2D>(this, 0x108).FUN_00607d90();
    float sector = g_unk0x00677f9c / m_a0;
    unsigned short count = (unsigned short)(int)ceil(extent / sector);
    float step = extent / (count + 1);
    RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c260(RHShadowField<SBGeoPoint2D>(this, 0xb0));
    RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c260(RHShadowField<RHUnk005fc3b0>(this, 0xc8));
    float rotation = 0.0f;
    for (unsigned remaining = count; remaining != 0; --remaining)
    {
        rotation += step;
        temporary.FUN_005fc430(initial.FUN_005fc9e0(rotation, 1.0f));
        temporary.m_y = temporary.m_y * 0.573576450347900390625f;
        RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c260(temporary);
    }
    RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c260(RHShadowField<RHUnk005fc3b0>(this, 0xd0));
    SBGeoPoint2D origin;
    SBGeoPoint2D projected;
    origin = RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c2b0(0);
    RHShadowField<SBGeoBoundingBox2D>(this, 0x108).Unk00607dc0(origin);
    for (unsigned short index = 1; index < (int)count + 3; ++index)
    {
        SBGeoPoint2D vector(RHShadowField<RHShadowUnk0060c260>(this, 0xd8).FUN_0060c2b0(index));
        projected = origin.Unk005fc190(operator*(m_a0, (const SBGeoVector2D &)vector));
        RHShadowField<SBGeoBoundingBox2D>(this, 0x108).Unk00607dc0(projected);
    }
}

// FUNCTION: GAME 0x00595630
bool RHShadowPolygon::FUN_00595630(const SBGeoBoundingBox2D &box)
{
    SBGeoPoint2D corner;
    if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).m_x > g_unk0x00677488)
    {
        if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).m_y > g_unk0x00677488)
        {
            float y = box.m_c;
            corner.m_x = box.m_0;
            corner.m_y = y;
            if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc680((const RHUnk005fc3b0 &)corner.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) < g_unk0x00677488)
                return false;
        }
        else if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc680((const RHUnk005fc3b0 &)box.Max().Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) < g_unk0x00677488)
            return false;
    }
    else
    {
        if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).m_y > g_unk0x00677488)
        {
            if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc680((const RHUnk005fc3b0 &)box.Min().Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) < g_unk0x00677488)
                return false;
        }
        else
        {
            float y = box.m_4;
            corner.m_x = box.m_8;
            corner.m_y = y;
            if (RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc680((const RHUnk005fc3b0 &)corner.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) < g_unk0x00677488)
                return false;
        }
    }
    if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).m_x > g_unk0x00677488)
    {
        if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).m_y > g_unk0x00677488)
        {
            float y = box.m_4;
            corner.m_x = box.m_8;
            corner.m_y = y;
            if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc680((const RHUnk005fc3b0 &)corner.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) > g_unk0x00677488)
                return false;
        }
        else if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc680((const RHUnk005fc3b0 &)box.Min().Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) > g_unk0x00677488)
            return false;
    }
    else
    {
        if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).m_y > g_unk0x00677488)
        {
            if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc680((const RHUnk005fc3b0 &)box.Max().Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) > g_unk0x00677488)
                return false;
        }
        else
        {
            float y = box.m_c;
            corner.m_x = box.m_0;
            corner.m_y = y;
            if (RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc680((const RHUnk005fc3b0 &)corner.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) > g_unk0x00677488)
                return false;
        }
    }
    return true;
}

// Parked: in the inlined dirty Locate VC6 hoists &m_current above the branch (target recomputes it per arm).
// STUB: GAME 0x005971f0
void RHShadowPolygon::FUN_005971f0()
{
    unsigned short count = (unsigned short)m_158.m_list.size();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            RHUnk005977e0 *area = (RHUnk005977e0 *)m_158.GetAt(index);
            undefined *field = area->m_0 + 0x4c;
            unsigned short limit = (unsigned short)area->m_10.m_list.size();
            for (unsigned short item = 0; item < limit; ++item)
            {
                RHUnk00564020 *boundary = (RHUnk00564020 *)area->m_10.GetAt(item);
                if (!FUN_0059e7e0(field, boundary))
                {
                    delete boundary;
                    area->m_10.RemoveAt(item);
                    --item;
                    --limit;
                }
            }
            ++index;
        } while (--remaining != 0);
    }
}

// FUNCTION: GAME 0x005973f0
void RHShadowPolygon::FUN_005973f0()
{
    unsigned short count = (unsigned short)m_134.m_list.size();
    if (count > 0)
    {
        int index = 0;
        RHShadowPolygonList &projections = m_134;
        unsigned remaining = count;
        do
        {
            projections.FUN_005c8e40(index);
            delete *projections.m_current;
            ++index;
        } while (--remaining != 0);
    }
    m_134.ClearAll();

    count = (unsigned short)m_158.m_list.size();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            RHShadowPolygonList &areas = m_158;
            areas.FUN_005c8e40(index);
            RHUnk005977e0 *area = (RHUnk005977e0 *)*areas.m_current;
            unsigned short items = (unsigned short)area->m_10.m_list.size();
            if (items > 0)
            {
                RHShadowPolygonList &boundaries = area->m_10;
                int item = 0;
                unsigned left = items;
                do
                {
                    boundaries.FUN_005c8e40(item);
                    delete (RHUnk00564020 *)*boundaries.m_current;
                    ++item;
                } while (--left != 0);
            }
            area->m_10.ClearAll();
            items = (unsigned short)area->m_34.m_list.size();
            if (items > 0)
            {
                RHShadowPolygonList &projected = area->m_34;
                int item = 0;
                unsigned left = items;
                do
                {
                    projected.FUN_005c8e40(item);
                    delete (RHUnk00564020 *)*projected.m_current;
                    ++item;
                } while (--left != 0);
            }
            area->m_34.ClearAll();
            delete area;
            ++index;
        } while (--remaining != 0);
    }
    m_158.ClearNodes();
    m_190->FUN_0059f000();
    m_198.ClearNodes();
    m_1bc.ClearNodes();
    m_194->FUN_0059ec90();
    m_1e0.EraseAll();
}

// FUNCTION: GAME 0x00597690
RHUnk00597a70::~RHUnk00597a70()
{
}

// FUNCTION: GAME 0x005977e0
RHUnk005977e0::~RHUnk005977e0()
{
}

// FUNCTION: GAME 0x00597910
void RHShadowPolygon::FUN_00597910()
{
    m_190->FUN_0059f000();
    m_198.ClearNodes();
    m_1bc.ClearNodes();
    m_194->FUN_0059ec90();
    m_1e0.ClearNodes();
    unsigned short count = (unsigned short)m_158.m_list.size();
    if (count > 0)
    {
        RHShadowPolygonList &areas = m_158;
        int index = 0;
        unsigned remaining = count;
        do
        {
            areas.FUN_005c8e40(index);
            RHUnk005977e0 *area = (RHUnk005977e0 *)*areas.m_current;
            unsigned short itemCount = (unsigned short)area->m_34.m_list.size();
            if (itemCount > 0)
            {
                int item = 0;
                RHShadowPolygonList &boundaries = area->m_34;
                unsigned items = itemCount;
                do
                {
                    boundaries.FUN_005c8e40(item);
                    delete (RHUnk00564020 *)*boundaries.m_current;
                    ++item;
                } while (--items != 0);
            }
            RHUnk005c9010Node *head = area->m_34.m_list.m_head;
            RHUnk005c9010Node *current = head->m_next;
            while (current != head)
            {
                RHUnk005c9010Node *node = current;
                current = current->m_next;
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
                operator delete(node);
                --area->m_34.m_list.m_count;
            }
            area->m_34.m_dirty = true;
            ++index;
        } while (--remaining != 0);
    }
}

// Coupled park: 0x00597a70; annotation breaks DisplayDebug.
bool RHShadowPolygon::FUN_00597a70(RHUnk00597a70 *area)
{
    RHShadowField<RHUnk00597a70 *>(this, 0x130) = area;
    int &left = RHShadowField<int>(this, 0x17c);
    int &right = RHShadowField<int>(this, 0x180);
    int &top = RHShadowField<int>(this, 0x184);
    int &bottom = RHShadowField<int>(this, 0x188);
    left = (int)area->m_2c.m_min.m_x;
    right = (int)area->m_2c.m_max.m_x;
    top = (int)area->m_2c.m_min.m_y;
    bottom = (int)area->m_2c.m_max.m_y;
    if (*(undefined4 *)&m_8c == 0x3f000000)
    {
        if (left & 1)
            ++left;
        if (top & 1)
            ++top;
        if (right & 1)
            --right;
        if (bottom & 1)
            --bottom;
        if (right < left || bottom < top)
            return false;
    }
    float &height = RHShadowField<float>(this, 0xb8);
    RHShadowUnk005df9e0 *plane;
    if (area->m_0 == 0)
    {
        RHShadowField<unsigned short>(this, 0x18c) = 1;
        RHShadowField<unsigned short>(this, 0x18e) = 1;
        height = RHShadowField<float>(this, 0xac);
        plane = 0;
    }
    else
    {
        RHShadowField<unsigned short>(this, 0x18c) = 2;
        RHShadowField<unsigned short>(this, 0x18e) = 2;
        plane = (RHShadowUnk005df9e0 *)(area->m_0 + 0xa8);
        height = RHShadowField<float>(this, 0xac) - plane->FUN_005df9e0(
            RHShadowField<float>(this, 0xa4), RHShadowField<float>(this, 0xa8));
        plane = (RHShadowUnk005df9e0 *)(RHShadowField<RHUnk00597a70 *>(this, 0x130)->m_0 + 0xa8);
    }
    unsigned short count = (unsigned short)m_158.m_list.size();
    if (height <= g_unk0x00677488)
    {
        height -= g_unk0x006774c8;
        for (unsigned short index = 0; index < count; ++index)
        {
            RHUnk005977e0 *obstacle = (RHUnk005977e0 *)m_158[index];
            undefined *object = obstacle->m_0;
            if (RHShadowField<undefined>(obstacle, 0x0b) && FUN_0059b6b0(object, plane))
            {
                FUN_0059c720(obstacle, plane);
                if (!FUN_00598b90(obstacle, plane))
                    return false;
            }
        }
        return true;
    }
    if (plane == 0)
    {
        for (unsigned short index = 0; index < count; ++index)
        {
            m_158.FUN_005c8e40(index);
            RHUnk005977e0 *obstacle = (RHUnk005977e0 *)*m_158.m_current;
            undefined *object = obstacle->m_0;
            if (RHShadowField<undefined>(obstacle, 0x0a))
            {
                FUN_0059d5b0(obstacle);
                if (!FUN_00598230(obstacle, 0, false))
                    return false;
            }
            height -= g_unk0x006774c8;
            bool above = height > g_unk0x00677488;
            unsigned remaining = (unsigned short)obstacle->m_34.m_list.size();
            while (remaining != 0)
            {
                obstacle->m_34.FUN_005c8e40(0);
                delete (RHUnk00564020 *)*obstacle->m_34.m_current;
                RHUnk005c9010Node *node = obstacle->m_34.m_list.m_head->m_next;
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
                operator delete(node);
                --obstacle->m_34.m_list.m_count;
                obstacle->m_34.m_dirty = true;
                --remaining;
            }
            if (above)
            {
                if (RHShadowField<undefined>(obstacle, 0x0a) && FUN_0059b1f0(object))
                {
                    FUN_0059d7f0(obstacle);
                    if (!FUN_00598230(obstacle, 0, true))
                        return false;
                }
            }
            else if (RHShadowField<undefined>(obstacle, 0x0b) && FUN_0059b380(object))
            {
                FUN_0059ce90(obstacle);
                if (!FUN_00598b90(obstacle, 0))
                    return false;
            }
            height += g_unk0x006774c8;
        }
        return true;
    }
    for (unsigned short index = 0; index < count; ++index)
    {
        m_158.FUN_005c8e40(index);
        RHUnk005977e0 *obstacle = (RHUnk005977e0 *)*m_158.m_current;
        undefined *object = obstacle->m_0;
        if (RHShadowField<undefined>(obstacle, 0x0a) && object != area->m_0)
        {
            FUN_0059b850(obstacle, plane);
            if (!FUN_00598230(obstacle, plane, false))
                return false;
        }
        height -= g_unk0x006774c8;
        bool above = height > g_unk0x00677488;
        unsigned remaining = (unsigned short)obstacle->m_34.m_list.size();
        while (remaining != 0)
        {
            delete (RHUnk00564020 *)obstacle->m_34[0];
            RHUnk005c9010Node *node = obstacle->m_34.m_list.m_head->m_next;
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;
            operator delete(node);
            --obstacle->m_34.m_list.m_count;
            obstacle->m_34.m_dirty = true;
            --remaining;
        }
        if (above)
        {
            if (RHShadowField<undefined>(obstacle, 0x0a) && object != area->m_0 && FUN_0059b510(object, plane))
            {
                FUN_0059bfb0(obstacle, plane);
                if (!FUN_00598230(obstacle, plane, true))
                    return false;
            }
        }
        else if (RHShadowField<undefined>(obstacle, 0x0b) && object != area->m_0 && FUN_0059b6b0(object, plane))
        {
            FUN_0059c720(obstacle, plane);
            if (!FUN_00598b90(obstacle, plane))
                return false;
        }
        height += g_unk0x006774c8;
    }
    return true;
}

// Parked: VC6 keeps the second shared `return 1` EH tail (target keeps the first, after the above-branch range check).
// STUB: GAME 0x005994f0
unsigned char RHShadowPolygon::FUN_005994f0(const SBGeoPoint3D &point, SBGeoPoint2D &out, bool project, bool above)
{
    if (point.m_8 != g_unk0x00677488)
    {
        float height = point.m_8 - m_b8;
        if (height < g_unk0x006775d8 && height > -0.5f)
            return 3;
        if (above)
        {
            if (point.m_8 > g_unk0x00677488)
            {
                if (point.m_8 > m_b8)
                {
                    if (project)
                        out = RHShadowField<SBGeoPoint2D>(this, 0xb0).Unk005fc190(operator*(m_b8 / (m_b8 - point.m_8), SBGeoVector2D(point.m_0 - m_a4.m_0, point.m_4 - m_a4.m_4)));
                    return 2;
                }
                if (point.m_8 < m_b8)
                {
                    out = RHShadowField<SBGeoPoint2D>(this, 0xb0).Unk005fc190(operator*(m_b8 / (m_b8 - point.m_8), SBGeoVector2D(point.m_0 - m_a4.m_0, point.m_4 - m_a4.m_4)));
                    float offset = out.m_x - RHShadowField<SBGeoPoint2D>(this, 0xb0).m_x;
                    if (offset > 10000.0f || offset < -10000.0f)
                        return 1;
                    return 0;
                }
            }
        }
        else if (point.m_8 < g_unk0x00677488)
        {
            if (point.m_8 < m_b8)
            {
                if (project)
                    out = RHShadowField<SBGeoPoint2D>(this, 0xb0).Unk005fc190(operator*(m_b8 / (m_b8 - point.m_8), SBGeoVector2D(point.m_0 - m_a4.m_0, point.m_4 - m_a4.m_4)));
                return 2;
            }
            if (point.m_8 > m_b8)
            {
                out = RHShadowField<SBGeoPoint2D>(this, 0xb0).Unk005fc190(operator*(m_b8 / (m_b8 - point.m_8), SBGeoVector2D(point.m_0 - m_a4.m_0, point.m_4 - m_a4.m_4)));
                float offset = out.m_x - RHShadowField<SBGeoPoint2D>(this, 0xb0).m_x;
                if (offset > 10000.0f || offset < -10000.0f)
                    return 1;
                return 0;
            }
        }
    }
    out.Set(point.m_0, point.m_4);
    return 0;
}

// FUNCTION: GAME 0x0059a770
void RHShadowPolygon::FUN_0059a770(const SBGeoPoint2D &a, const SBGeoPoint2D &b)
{
    bool reversed;
    int x0;
    int y0;
    int x1;
    int y1;
    if (a.m_x > b.m_x)
    {
        reversed = false;
        x0 = (int)b.m_x;
        y0 = (int)b.m_y;
        x1 = (int)a.m_x;
        y1 = (int)a.m_y;
    }
    else
    {
        reversed = true;
        x0 = (int)a.m_x;
        y0 = (int)a.m_y;
        x1 = (int)b.m_x;
        y1 = (int)b.m_y;
    }
    if (x0 == x1)
        return;
    RHShadowIterator *iterator = m_190->FUN_0059f1a0();
    m_198.InsertLast((RHUnk00597a70 *)iterator);
    iterator->m_0 = reversed;
    iterator->m_1 = true;
    iterator->m_2 = true;
    iterator->m_4 = x0;
    iterator->m_8 = y0;
    iterator->m_c = x1;
    iterator->m_10 = y1;
    iterator->m_18 = ((y1 - y0) << 16) / (x1 - x0);
    if (x0 <= m_17c)
    {
        iterator->m_14 = (m_17c - x0) * iterator->m_18 + (y0 << 16);
        m_1bc.InsertLast((RHUnk00597a70 *)iterator);
    }
    else
    {
        iterator->m_14 = y0 << 16;
        RHShadowEvent *event = m_194->FUN_0059ee30();
        event->m_c = iterator;
        event->m_10 = x0;
        event->m_4 = 0;
        event->m_8 = 3;
        FUN_0059eab0(event);
    }
    if (x1 <= m_180)
    {
        RHShadowEvent *event = m_194->FUN_0059ee30();
        event->m_c = iterator;
        event->m_10 = x1;
        event->m_4 = 0;
        event->m_8 = 4;
        FUN_0059eab0(event);
    }
}

// Parked 93.57%: VC6 stores the list count before the dirty flag and loads x1 straight into ecx (target: dirty first, x1 via eax copy).
// STUB: GAME 0x0059ada0
void RHShadowPolygon::FUN_0059ada0(const SBGeoPoint2D &a, long alphaA, const SBGeoPoint2D &b, long alphaB)
{
    bool reversed;
    int x0;
    int y0;
    int x1;
    int y1;
    if (a.m_x > b.m_x)
    {
        reversed = false;
        x0 = (int)b.m_x;
        y0 = (int)b.m_y;
        x1 = (int)a.m_x;
        y1 = (int)a.m_y;
        long swap = alphaA;
        alphaA = alphaB;
        alphaB = swap;
    }
    else
    {
        reversed = true;
        x0 = (int)a.m_x;
        y0 = (int)a.m_y;
        x1 = (int)b.m_x;
        y1 = (int)b.m_y;
    }
    if (x0 == x1 || x0 > m_180 || x1 <= m_17c)
        return;
    RHShadowAlphaIterator *iterator = (RHShadowAlphaIterator *)m_190->FUN_0059f1a0();
    m_198.InsertLast((RHUnk00597a70 *)iterator);
    iterator->m_0 = reversed;
    iterator->m_1 = false;
    iterator->m_4 = x0;
    iterator->m_8 = y0;
    iterator->m_c = x1;
    iterator->m_10 = y1;
    iterator->m_18 = ((y1 - y0) << 16) / (x1 - x0);
    iterator->m_20 = ((alphaB - alphaA) << 16) / (x1 - x0);
    iterator->m_1c = alphaA << 16;
    if (x0 <= m_17c)
    {
        iterator->m_14 = (m_17c - x0) * iterator->m_18 + (y0 << 16);
        iterator->m_1c += (m_17c - x0) * iterator->m_20;
        if (reversed)
            m_204 = iterator;
        else
            m_208 = iterator;
    }
    else
    {
        iterator->m_14 = y0 << 16;
        iterator->m_1c = alphaA << 16;
        RHShadowEvent *event = m_194->FUN_0059ee30();
        event->m_c = iterator;
        event->m_10 = x0;
        event->m_4 = 2;
        if (reversed)
            event->m_8 = 3;
        else
            event->m_8 = 4;
        FUN_0059eab0(event);
    }
}

// Parked 96.10%: VC6 slots the line ctor's two temporaries above the unused point local (target: below).
// STUB: GAME 0x0059afc0
unsigned char RHShadowPolygon::FUN_0059afc0(SBGeoPoint2D &out, SBGeoPoint2D &in, SBGeoPoint2D &direction)
{
    RHMobileUnk006100e0 line(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    SBGeoPoint2D result;
    line.SBGeoPoint2D::operator=(in);
    line.FUN_00610160(direction);
    unsigned char side = FUN_0059ec40(&in, &direction);
    float x;
    float y;
    for (;;)
    {
        switch (side)
        {
        case 1:
        {
            y = Bounds().m_4 - g_rhuirendererportrait_percent;
            x = line.FUN_006104f0(y);
            out.m_x = x;
            out.m_y = y;
            if (x > Bounds().m_8 + 1000.0f)
                side = 2;
            else if (x < Bounds().m_0 - 1000.0f)
                side = 8;
            else
                return side;
            break;
        }
        case 2:
        {
            x = RHShadowField<float>(this, 0xb0) + 10000.0f;
            y = line.FUN_00610520(x);
            out.m_x = x;
            out.m_y = y;
            return side;
        }
        case 4:
        {
            y = Bounds().m_c;
            y += g_rhuirendererportrait_percent;
            x = line.FUN_006104f0(y);
            out.m_x = x;
            out.m_y = y;
            if (x > Bounds().m_8 + 1000.0f)
                side = 2;
            else if (x < Bounds().m_0 - 1000.0f)
                side = 8;
            else
                return side;
            break;
        }
        case 8:
        {
            x = RHShadowField<float>(this, 0xb0) - 10000.0f;
            y = line.FUN_00610520(x);
            out.m_x = x;
            out.m_y = y;
            return side;
        }
        }
    }
}

// Parked 95.6%: in the inlined Locate's backward branches VC6 loads the advance tag into edx/eax (target: ecx/edx).
// STUB: GAME 0x0059b1f0
bool RHShadowPolygon::FUN_0059b1f0(undefined *object)
{
    RHShadowSight *sight = (RHShadowSight *)object;
    unsigned short count = (unsigned short)sight->m_4c.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        sight->m_4c.Locate(index);
        RHShadowVertex vertex = *(RHShadowVertex *)&sight->m_4c.m_current.m_node->m_data;
        if (vertex.m_08 >= g_unk0x006774c8)
            return true;
    }
    return false;
}

// Parked: same cached-list navigation schedule seam as 0x0059b1f0.
// STUB: GAME 0x0059b380
bool RHShadowPolygon::FUN_0059b380(undefined *object)
{
    RHShadowSight *sight = (RHShadowSight *)object;
    unsigned short count = (unsigned short)sight->m_4c.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        sight->m_4c.Locate(index);
        RHShadowVertex vertex = *(RHShadowVertex *)&sight->m_4c.m_current.m_node->m_data;
        if (g_unk0x006774c8 >= vertex.m_0c)
            return true;
    }
    return false;
}

// Parked: same cached-list navigation schedule seam as 0x0059b1f0.
// STUB: GAME 0x0059b510
bool RHShadowPolygon::FUN_0059b510(undefined *object, RHShadowUnk005df9e0 *plane)
{
    RHShadowSight *sight = (RHShadowSight *)object;
    unsigned short count = (unsigned short)sight->m_4c.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        sight->m_4c.Locate(index);
        RHShadowVertex vertex = *(RHShadowVertex *)&sight->m_4c.m_current.m_node->m_data;
        if (plane->FUN_005df9e0(vertex.m_00, vertex.m_04) + g_unk0x006774c8 <= vertex.m_08)
            return true;
    }
    return false;
}

// Parked: same cached-list navigation schedule seam as 0x0059b1f0.
// STUB: GAME 0x0059b6b0
bool RHShadowPolygon::FUN_0059b6b0(undefined *object, RHShadowUnk005df9e0 *plane)
{
    RHShadowSight *sight = (RHShadowSight *)object;
    unsigned short count = (unsigned short)sight->m_4c.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        sight->m_4c.Locate(index);
        RHShadowVertex vertex = *(RHShadowVertex *)&sight->m_4c.m_current.m_node->m_data;
        if (plane->FUN_005df9e0(vertex.m_00, vertex.m_04) + g_unk0x006774c8 >= vertex.m_0c)
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0059d5b0
void RHShadowPolygon::FUN_0059d5b0(RHUnk005977e0 *area)
{
    RHUnk00613e90 point;
    RHShadowPolygonList &vertices = *(RHShadowPolygonList *)&((RHShadowSight *)area->m_0)->m_4c;
    unsigned short count = (unsigned short)area->m_10.m_list.size();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            RHShadowPolygonList &boundaries = area->m_10;
            boundaries.FUN_005c8e40(index);
            RHShadowEdgeList *edges = (RHShadowEdgeList *)*boundaries.m_current;
            RHUnk00597a70 *projection = (RHUnk00597a70 *)new RHShadowProjection;
            unsigned short items = (unsigned short)edges->size();
            if (items > 0)
            {
                int item = 0;
                unsigned left = items;
                do
                {
                    ((RHShadowPolygonList *)edges)->FUN_005c8e40(item);
                    bool upper = edges->m_current->m_data.m_2;
                    ((RHShadowPolygonList *)edges)->FUN_005c8e40(item);
                    unsigned short vertex = edges->m_current->m_data.m_0;
                    vertices.FUN_005c8e40(vertex);
                    point.m_0 = ((RHShadowVertex *)&vertices.m_current.m_node->m_data)->m_00;
                    vertices.FUN_005c8e40(vertex);
                    point.m_4 = ((RHShadowVertex *)&vertices.m_current.m_node->m_data)->m_04;
                    if (upper)
                    {
                        vertices.FUN_005c8e40(vertex);
                        point.m_8 = ((RHShadowVertex *)&vertices.m_current.m_node->m_data)->m_08;
                    }
                    else
                    {
                        vertices.FUN_005c8e40(vertex);
                        point.m_8 = ((RHShadowVertex *)&vertices.m_current.m_node->m_data)->m_0c;
                    }
                    ((RHShadowProjection *)projection)->InsertLast(point);
                    ++item;
                } while (--left != 0);
            }
            area->m_34.InsertLastCopy(projection);
            ++index;
        } while (--remaining != 0);
    }
}

// FUNCTION: GAME 0x0059df10
float RHShadowPolygon::FUN_0059df10(RHUnk0059df10Object *object)
{
    if (object->m_0 == 0)
    {
        if (!m_61)
        {
            if (m_a0 * 0.35f >= m_a4.m_8)
                return sqrt(m_a0 * m_a0 - m_a4.m_8 * m_a4.m_8 * 8.163265228271484f);
        }
        else if (m_a4.m_8 <= m_a0)
            return m_a4.m_8 * 0.8f;
    }
    else
    {
        RHUnk00613e90 offset;
        RHUnkSightPlane *plane = (RHUnkSightPlane *)(object->m_0 + 0xa8);
        offset = ((const RHUnk00613e90 &)m_a4).FUN_005df550(*(const RHUnk00613e90 *)plane);
        float height = offset.FUN_005df5f0(*(const RHUnk00613e90 *)plane->FUN_005df990());
        if (!m_61)
        {
            float limit = m_a0 * 0.35f;
            if (height < limit && -height < limit)
                return sqrt(m_a0 * m_a0 - height * height * 8.163265228271484f);
            return g_unk0x00677488;
        }
        if (height < m_a0 && height > g_unk0x00677488)
            return height * 0.8f;
    }
    return g_unk0x00677488;
}

// FUNCTION: GAME 0x0059e780
void RHShadowPolygon::FUN_0059e780(SBGeoPoint2D &out, SBGeoPoint2D &in, RHShadowUnk005df9e0 *plane)
{
    if (plane == 0)
    {
        float mx = RHShadowField<float>(this, 0x78);
        out.m_x = in.m_x - mx;
        float my = RHShadowField<float>(this, 0x7c);
        out.m_y = in.m_y - my;
    }
    else
    {
        float mx = RHShadowField<float>(this, 0x78);
        out.m_x = in.m_x - mx;
        float y = RHShadowField<float>(this, 0x7c);
        out.m_y = in.m_y - plane->FUN_005df9e0(in.m_x, in.m_y) - y;
    }
}

// FUNCTION: GAME 0x0059e7e0
bool RHShadowPolygon::FUN_0059e7e0(undefined *field, RHUnk00564020 *boundary)
{
    bool left = true;
    bool right = true;
    SBGeoPoint2D point;
    RHShadowPolygonList *vertices = (RHShadowPolygonList *)field;
    RHShadowEdgeList *edges = (RHShadowEdgeList *)boundary;
    unsigned short count = (unsigned short)edges->size();
    for (unsigned short index = 0; index < count; ++index)
    {
        ((RHShadowPolygonList *)edges)->FUN_005c8e40(index);
        unsigned short corner = edges->m_current->m_data.m_0;
        vertices->FUN_005c8e40(corner);
        RHShadowVertex vertex = *(RHShadowVertex *)&vertices->m_current.m_node->m_data;
        point.Set(vertex.m_00, vertex.m_04);
        if (left && RHShadowField<RHUnk005fc3b0>(this, 0xc8).FUN_005fc680((const RHUnk005fc3b0 &)point.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) > g_unk0x00677488)
        {
            if (!right)
                return true;
            left = false;
        }
        if (right && RHShadowField<RHUnk005fc3b0>(this, 0xd0).FUN_005fc680((const RHUnk005fc3b0 &)point.Unk005fc110(RHShadowField<SBGeoPoint2D>(this, 0xb0)), 1.0f) < g_unk0x00677488)
        {
            if (!left)
                return true;
            right = false;
        }
    }
    return !left && !right;
}

// FUNCTION: GAME 0x0059e9b0
unsigned char RHShadowPolygon::FUN_0059e9b0(RHShadowPolygonList *points)
{
    RHUnk00613e90 point;
    SBGeoPoint2D flat;
    RHShadowBox box;
    unsigned short count = (unsigned short)points->m_list.size();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            points->FUN_005c8e40(index);
            point = *(RHUnk00613e90 *)&points->m_current.m_node->m_data;
            float x = point.m_0;
            flat.m_x = x;
            float y = point.m_4;
            flat.m_y = y;
            ((SBGeoBoundingBox2D &)box).Unk00607dc0(flat);
            ++index;
        } while (--remaining != 0);
    }
    return (unsigned char)((RHUnk00608f10 *)(RHShadowField<undefined *>(this, 0x130) + 4))->FUN_00608f10(&box);
}

// Parked 58%: VC6 gives the loop's list base edi and pos esi (target: esi/edi), so the empty-list InsertNode tail is not cross-jumped.
// STUB: GAME 0x0059eab0
void RHShadowPolygon::FUN_0059eab0(RHShadowEvent *event)
{
    unsigned short count = (unsigned short)m_1e0.m_list.size();
    if (count == 0)
    {
        m_1e0.InsertNode(m_1e0.m_list.m_head, *(RHUnk00597a70 **)&event);
        return;
    }
    unsigned short pos = count >> 1;
    unsigned short below = pos;
    unsigned short size = pos;
    unsigned short above;
    if (count & 1)
        above = pos;
    else
        above = pos - 1;
    while (true)
    {
        RHShadowEvent *current = (RHShadowEvent *)m_1e0.GetAt(pos);
        if (event->m_10 == current->m_10)
        {
            m_1e0.InsertAtIndex(pos, *(RHUnk00597a70 **)&event);
            return;
        }
        if (event->m_10 > current->m_10)
        {
            if (above == 0)
            {
                m_1e0.InsertAtIndex(pos + 1, *(RHUnk00597a70 **)&event);
                return;
            }
            below = above >> 1;
            pos += below + 1;
            if (above & 1)
            {
                size = below;
                above = below;
            }
            else
            {
                size = below;
                above = below - 1;
            }
        }
        else
        {
            if (below == 0)
            {
                m_1e0.InsertAtCurrent(pos, *(RHUnk00597a70 **)&event);
                return;
            }
            below >>= 1;
            if (size & 1)
            {
                above = below;
                size = below;
                pos -= below + 1;
            }
            else
            {
                pos -= below;
                size = below;
                above = below - 1;
            }
        }
    }
}

// FUNCTION: GAME 0x0059ec40
unsigned char RHShadowPolygon::FUN_0059ec40(SBGeoPoint2D *a, SBGeoPoint2D *b)
{
    if (b->m_x != g_unk0x00677488)
    {
        if (b->m_x > g_unk0x00677488)
            return 2;
        return 8;
    }
    if (b->m_y > g_unk0x00677488)
        return 4;
    return 1;
}

// FUNCTION: GAME 0x0059fbe0
void RHShadowMemoryList::FUN_0059fbe0(const RHShadowMemoryRange &value)
{
    RHShadowMemoryNode *next = m_head;
    RHShadowMemoryNode *previous = next->m_previous;
    RHShadowMemoryNode *node = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
    node->m_next = next ? next : node;
    node->m_previous = previous ? previous : node;
    next->m_previous = node;
    node->m_previous->m_next = node;
    new (&node->m_value) RHShadowMemoryRange(value);
    ++m_count;
}

// FUNCTION: GAME 0x0059fc40
void RHShadowMemoryVector::FUN_0059fc40()
{
    RHShadowMemoryBlock *last = m_last;
    for (RHShadowMemoryBlock *first = m_first; first != last; ++first)
        first->FUN_0059f4e0();
    operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// FUNCTION: GAME 0x0059fc80
void **RHShadowPointerVector::FUN_0059fc80(void **position)
{
    std::copy(position + 1, m_last, position);
    Destroy(m_last - 1, m_last);
    --m_last;
    return position;
}

// FUNCTION: GAME 0x0059fcc0
RHShadowMemoryNode *RHShadowMemoryList::FUN_0059fcc0(RHShadowMemoryNode *next, RHShadowMemoryNode *previous)
{
    RHShadowMemoryNode *node = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
    node->m_next = next ? next : node;
    node->m_previous = previous ? previous : node;
    return node;
}

void FUN_005a0d10(RHShadowMemoryBlock *destination, const RHShadowMemoryBlock &source);
void FUN_005a0df0(RHShadowMemoryBlock *destination, const RHShadowMemoryBlock &source);
void FUN_005a0a30(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, const RHShadowMemoryBlock &value);
RHShadowMemoryBlock *FUN_005a0b90(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination);

// FUNCTION: GAME 0x0059fcf0
RHShadowMemoryBlock *RHShadowMemoryVector::FUN_0059fcf0(RHShadowMemoryBlock *position, const RHShadowMemoryBlock &value)
{
    unsigned offset = position - m_first;
    if ((unsigned)(m_end - m_last) < 1)
    {
        unsigned growth = (m_first != 0 && (unsigned)(m_last - m_first) > 1) ? m_last - m_first : 1;
        unsigned capacity = (m_first == 0 ? 0 : m_last - m_first) + growth;
        RHShadowMemoryBlock *allocation = std::_Allocate((int)capacity, (RHShadowMemoryBlock *)0);
        RHShadowMemoryBlock *destination = allocation;
        for (RHShadowMemoryBlock *first = m_first; first != position; ++first, ++destination)
            FUN_005a0d10(destination, *first);
        FUN_005a0d10(destination, value);
        FUN_005a0920(position, m_last, destination + 1);
        FUN_0059fef0(m_first, m_last);
        operator delete(m_first);
        m_end = allocation + capacity;
        unsigned (RHShadowMemoryVector::*size)() const = &RHShadowMemoryVector::FUN_005a0990;
        m_last = allocation + (this->*size)() + 1;
        m_first = allocation;
    }
    else if ((unsigned)(m_last - position) < 1)
    {
        FUN_005a0920(position, m_last, position + 1);
        FUN_005a0960(m_last, 1 - (m_last - position), value);
        FUN_005a0a30(position, m_last, value);
        ++m_last;
    }
    else
    {
        FUN_005a0920(m_last - 1, m_last, m_last);
        FUN_005a0b90(position, m_last - 1, m_last);
        FUN_005a0a30(position, position + 1, value);
        ++m_last;
    }
    return m_first + offset;
}

// FUNCTION: GAME 0x0059fef0
void RHShadowMemoryVector::FUN_0059fef0(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last)
{
    for (; first != last; ++first)
        first->FUN_0059f4e0();
}

#include <stdexcept>

// Parked: exception base construction uses a pooled empty string instead of the target's shared empty-data object.
// STUB: GAME 0x0059ff20
void RHShadowMemoryVector::FUN_0059ff20() const
{
    throw std::out_of_range(
        // STRING: GAME 0x006afb90
        "invalid vector<T> subscript");
}

// FUNCTION: GAME 0x005a0000
RHShadowMemoryBlock *RHShadowMemoryVector::FUN_005a0000(RHShadowMemoryBlock *position, const RHShadowMemoryBlock &value)
{
    unsigned offset = position - m_first;
    if ((unsigned)(m_end - m_last) < 1)
    {
        unsigned growth = (m_first != 0 && (unsigned)(m_last - m_first) > 1) ? m_last - m_first : 1;
        unsigned capacity = (m_first == 0 ? 0 : m_last - m_first) + growth;
        RHShadowMemoryBlock *allocation = std::_Allocate((int)capacity, (RHShadowMemoryBlock *)0);
        RHShadowMemoryBlock *destination = allocation;
        for (RHShadowMemoryBlock *first = m_first; first != position; ++first, ++destination)
            FUN_005a0df0(destination, *first);
        FUN_005a0df0(destination, value);
        FUN_005a09c0(position, m_last, destination + 1);
        FUN_0059fef0(m_first, m_last);
        operator delete(m_first);
        m_end = allocation + capacity;
        unsigned (RHShadowMemoryVector::*size)() const = &RHShadowMemoryVector::FUN_005a0990;
        m_last = allocation + (this->*size)() + 1;
        m_first = allocation;
    }
    else if ((unsigned)(m_last - position) < 1)
    {
        FUN_005a09c0(position, m_last, position + 1);
        FUN_005a0a00(m_last, 1 - (m_last - position), value);
        FUN_005a0a30(position, m_last, value);
        ++m_last;
    }
    else
    {
        FUN_005a09c0(m_last - 1, m_last, m_last);
        FUN_005a0b90(position, m_last - 1, m_last);
        FUN_005a0a30(position, position + 1, value);
        ++m_last;
    }
    return m_first + offset;
}

// Parked: exception base construction uses a pooled empty string instead of the target's shared empty-data object.
// STUB: GAME 0x005a0200
void RHShadowMemoryVector::FUN_005a0200() const
{
    throw std::out_of_range("invalid vector<T> subscript");
}

inline RHShadowMemoryBlock *RHShadowCopyBlocks0(const RHShadowMemoryBlock *first, const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    for (; first != last; ++destination, ++first)
        FUN_005a0d10(destination, *first);
    return destination;
}
inline void RHShadowFillBlocks0(RHShadowMemoryBlock *destination, unsigned count, const RHShadowMemoryBlock &value)
{
    for (; count > 0; --count, ++destination)
        FUN_005a0d10(destination, value);
}
inline RHShadowMemoryBlock *RHShadowCopyBlocks1(const RHShadowMemoryBlock *first, const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    for (; first != last; ++destination, ++first)
        FUN_005a0df0(destination, *first);
    return destination;
}
inline void RHShadowFillBlocks1(RHShadowMemoryBlock *destination, unsigned count, const RHShadowMemoryBlock &value)
{
    for (; count > 0; --count, ++destination)
        FUN_005a0df0(destination, value);
}
inline void RHShadowAssignBlocks(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, const RHShadowMemoryBlock &value);
inline void RHShadowMoveBlocks(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination);

// FUNCTION: GAME 0x005a02e0
void RHShadowMemoryVector::FUN_005a02e0(RHShadowMemoryBlock *position, unsigned count, const RHShadowMemoryBlock &value)
{
    if ((unsigned)(m_end - m_last) < count)
    {
        unsigned growth = (m_first != 0 && count < (unsigned)(m_last - m_first)) ? m_last - m_first : count;
        unsigned capacity = (m_first == 0 ? 0 : m_last - m_first) + growth;
        RHShadowMemoryBlock *allocation = std::_Allocate((int)capacity, (RHShadowMemoryBlock *)0);
        RHShadowMemoryBlock *destination = RHShadowCopyBlocks0(m_first, position, allocation);
        RHShadowFillBlocks0(destination, count, value);
        RHShadowCopyBlocks0(position, m_last, destination + count);
        RHShadowMemoryBlock *last = m_last;
        for (RHShadowMemoryBlock *first = m_first; first != last; ++first)
            first->FUN_0059f4e0();
        operator delete(m_first);
        m_end = allocation + capacity;
        m_last = allocation + (m_first == 0 ? 0 : m_last - m_first) + count;
        m_first = allocation;
    }
    else if ((unsigned)(m_last - position) < count)
    {
        RHShadowCopyBlocks0(position, m_last, position + count);
        RHShadowFillBlocks0(m_last, count - (m_last - position), value);
        RHShadowAssignBlocks(position, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        RHShadowCopyBlocks0(m_last - count, m_last, m_last);
        RHShadowMoveBlocks(position, m_last - count, m_last);
        RHShadowAssignBlocks(position, position + count, value);
        m_last += count;
    }
}

// FUNCTION: GAME 0x005a0600
void RHShadowMemoryVector::FUN_005a0600(RHShadowMemoryBlock *position, unsigned count, const RHShadowMemoryBlock &value)
{
    if ((unsigned)(m_end - m_last) < count)
    {
        unsigned growth = (m_first != 0 && count < (unsigned)(m_last - m_first)) ? m_last - m_first : count;
        unsigned capacity = (m_first == 0 ? 0 : m_last - m_first) + growth;
        RHShadowMemoryBlock *allocation = std::_Allocate((int)capacity, (RHShadowMemoryBlock *)0);
        RHShadowMemoryBlock *destination = RHShadowCopyBlocks1(m_first, position, allocation);
        RHShadowFillBlocks1(destination, count, value);
        RHShadowCopyBlocks1(position, m_last, destination + count);
        RHShadowMemoryBlock *last = m_last;
        for (RHShadowMemoryBlock *first = m_first; first != last; ++first)
            first->FUN_0059f4e0();
        operator delete(m_first);
        m_end = allocation + capacity;
        m_last = allocation + (m_first == 0 ? 0 : m_last - m_first) + count;
        m_first = allocation;
    }
    else if ((unsigned)(m_last - position) < count)
    {
        RHShadowCopyBlocks1(position, m_last, position + count);
        RHShadowFillBlocks1(m_last, count - (m_last - position), value);
        RHShadowAssignBlocks(position, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        RHShadowCopyBlocks1(m_last - count, m_last, m_last);
        RHShadowMoveBlocks(position, m_last - count, m_last);
        RHShadowAssignBlocks(position, position + count, value);
        m_last += count;
    }
}

// FUNCTION: GAME 0x005a0920
RHShadowMemoryBlock *RHShadowMemoryVector::FUN_005a0920(const RHShadowMemoryBlock *first,
    const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    for (; first != last; ++first, ++destination)
        FUN_005a0d10(destination, *first);
    return destination;
}

// FUNCTION: GAME 0x005a0960
void RHShadowMemoryVector::FUN_005a0960(RHShadowMemoryBlock *destination, unsigned count,
    const RHShadowMemoryBlock &value)
{
    for (; count > 0; --count, ++destination)
        FUN_005a0d10(destination, value);
}

// FUNCTION: GAME 0x005a0990
unsigned RHShadowMemoryVector::FUN_005a0990() const
{
    return m_first == 0 ? 0 : m_last - m_first;
}

// FUNCTION: GAME 0x005a09c0
RHShadowMemoryBlock *RHShadowMemoryVector::FUN_005a09c0(const RHShadowMemoryBlock *first,
    const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    for (; first != last; ++first, ++destination)
        FUN_005a0df0(destination, *first);
    return destination;
}

// FUNCTION: GAME 0x005a0a00
void RHShadowMemoryVector::FUN_005a0a00(RHShadowMemoryBlock *destination, unsigned count,
    const RHShadowMemoryBlock &value)
{
    for (; count > 0; --count, ++destination)
        FUN_005a0df0(destination, value);
}

inline void RHShadowAssignBlock(RHShadowMemoryBlock &destination, const RHShadowMemoryBlock &source);

// Parked: descriptor assignment inlining and cursor scheduling remain under comparison.
// STUB: GAME 0x005a0a30
void FUN_005a0a30(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, const RHShadowMemoryBlock &value)
{
    while (first != last)
    {
        RHShadowAssignBlock(*first, value);
        first = first + 1;
    }
}

// Parked: descriptor assignment inlining and cursor scheduling remain under comparison.
// STUB: GAME 0x005a0b90
RHShadowMemoryBlock *FUN_005a0b90(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    while (first != last)
    {
        --last;
        --destination;
        RHShadowAssignBlock(*destination, *last);
    }
    return destination;
}

template<int Kind>
class RHShadowMemoryCopyList : public RHShadowMemoryList
{
public:
    RHShadowMemoryCopyList(const std::allocator<RHShadowMemoryRange> &allocator)
    {
        m_allocator = *(const unsigned char *)&allocator;
        RHShadowMemoryNode *head = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
        head->m_next = head;
        head->m_previous = head;
        m_head = head;
        m_count = 0;
    }
    ~RHShadowMemoryCopyList()
    {
        RHShadowMemoryNode *last = m_head;
        RHShadowMemoryNode *first = last->m_next;
        while (first != last)
        {
            RHShadowMemoryNode *node = first;
            first = first->m_next;
            node->m_previous->m_next = node->m_next;
            node->m_next->m_previous = node->m_previous;
            operator delete(node);
            --m_count;
        }
        operator delete(m_head);
        m_head = 0;
        m_count = 0;
    }
};

template<int Kind>
class RHShadowMemoryCachedList
{
public:
    RHShadowMemoryCachedList(const RHShadowMemoryCachedList &source)
        : m_list(std::allocator<RHShadowMemoryRange>())
    {
        RHShadowMemoryNode *position = m_list.m_head->m_next;
        m_current = position;
        RHShadowMemoryNode *last = source.m_list.m_head;
        for (RHShadowMemoryNode *first = last->m_next; first != last; first = first->m_next)
        {
            RHShadowMemoryNode *previous = position->m_previous;
            RHShadowMemoryNode *node = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
            node->m_next = position ? position : node;
            node->m_previous = previous ? previous : node;
            position->m_previous = node;
            node->m_previous->m_next = node;
            new (&node->m_value) RHShadowMemoryRange(first->m_value);
            ++m_list.m_count;
        }
        m_dirty = true;
    }
    RHShadowMemoryCopyList<Kind> m_list;
    RHShadowMemoryNode *m_current;
    bool m_dirty;
    unsigned char m_unknown[23];
};

template<int Kind>
class RHShadowMemoryCopyBlock
{
public:
    RHShadowMemoryCopyBlock(const RHShadowMemoryCopyBlock &source)
        : m_tag(source.m_tag), m_ranges(source.m_ranges) {}
    unsigned long m_tag;
    RHShadowMemoryCachedList<Kind> m_ranges;
};

DECOMP_SIZE_ASSERT(RHShadowMemoryCopyBlock<0>, 0x2c)

// FUNCTION: GAME 0x005a0d10
void FUN_005a0d10(RHShadowMemoryBlock *destination, const RHShadowMemoryBlock &source)
{
    new (destination) RHShadowMemoryCopyBlock<0>((const RHShadowMemoryCopyBlock<0> &)source);
}

// FUNCTION: GAME 0x005a0df0
void FUN_005a0df0(RHShadowMemoryBlock *destination, const RHShadowMemoryBlock &source)
{
    new (destination) RHShadowMemoryCopyBlock<1>((const RHShadowMemoryCopyBlock<1> &)source);
}

// FUNCTION: GAME 0x005a0ed0
RHShadowMemoryBlock *RHShadowMemoryBlock::FUN_005a0ed0(unsigned flags)
{
    FUN_0059f4e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

struct RHsoundGroup;
void *FUN_0048f170(void *value);

struct RHHumanOpponent
{
    void *m_actor;
    void *m_line;
};
struct RHHumanOpponentNode;
struct RHHumanOpponentIterator
{
    RHHumanOpponentNode *node;
    RHHumanOpponentIterator(RHHumanOpponentNode *value) : node(value) {}
};
class RHHumanOpponentListCalls
{
public:
    RHHumanOpponentIterator FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value);
};

class RHShadowMemoryAssignmentList : public RHShadowMemoryList
{
public:
    void Assign(const RHShadowMemoryAssignmentList &source, bool constructValue, bool destroyNode = false)
    {
        if (&source != this)
        {
            RHShadowMemoryNode *last = m_head;
            RHShadowMemoryNode *first = last->m_next;
            while (first != last)
            {
                RHShadowMemoryNode *node = first;
                first = first->m_next;
                if (destroyNode)
                    FUN_0048f170(node);
                node->m_previous->m_next = node->m_next;
                node->m_next->m_previous = node->m_previous;
                operator delete(node);
                --m_count;
            }
            if (m_count == 0)
            {
                int count = source.m_count;
                for (int index = 0; index < count; ++index)
                {
                    ((RHShadowPolygonList *)&source)->FUN_005c8e40(index);
                    void (RHShadowMemoryList::*append)(const RHShadowMemoryRange &) = &RHShadowMemoryList::FUN_0059fbe0;
                    (this->*append)(source.m_current->m_value);
                }
            }
            else
            {
                ((RHShadowPolygonList *)this)->FUN_005c8e40(0);
                int count = source.m_count;
                for (int index = 0; index < count; ++index)
                {
                    ((RHShadowPolygonList *)&source)->FUN_005c8e40(index);
                    RHShadowMemoryNode *position = m_current;
                    const RHShadowMemoryRange &value = source.m_current->m_value;
                    RHShadowMemoryNode *previous = position->m_previous;
                    RHShadowMemoryNode *node = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
                    node->m_next = position ? position : node;
                    node->m_previous = previous ? previous : node;
                    position->m_previous = node;
                    node->m_previous->m_next = node;
                    if (constructValue)
                    {
                        typedef std::pair<const unsigned long, RHsoundGroup *> Pair;
                        void (__cdecl *construct)(Pair *, const Pair &) = &std::_Construct;
                        construct((Pair *)&node->m_value, (const Pair &)value);
                    }
                    else
                        new (&node->m_value) RHShadowMemoryRange(value);
                    ++m_count;
                }
            }
            m_dirty = true;
        }
    }
    RHShadowMemoryAssignmentList &FUN_005a1020(const RHShadowMemoryAssignmentList &source);
    void FUN_005a1140(const RHShadowMemoryAssignmentList &source, int index);
    void LocateForInsert(int index)
    {
        RHShadowPolygonList &list = *(RHShadowPolygonList *)this;
        int count = m_count;
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                list.m_current = RHUnk005c9010Iterator(list.m_list.m_head->m_next);
                FUN_005c9010(list.m_current, index, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                list.m_current = RHUnk005c9010Iterator(list.m_list.m_head);
                FUN_005c9010(list.m_current, index - count, category);
            }
            m_dirty = false;
            list.m_index = index;
        }
        else
        {
            int previous = list.m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        list.m_current = RHUnk005c9010Iterator(list.m_list.m_head->m_next);
                        FUN_005c9010(list.m_current, index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(list.m_current, index - previous, category);
                    }
                }
                else if (index < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010(list.m_current, index - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    list.m_current = RHUnk005c9010Iterator(list.m_list.m_head);
                    FUN_005c9010(list.m_current, index - count, category);
                }
                list.m_index = index;
            }
        }
    }
    RHShadowMemoryNode *m_current;
    bool m_dirty;
    unsigned char m_unknown[23];
};

class RHShadowMemoryAssignmentBlock
{
public:
    unsigned long m_tag;
    RHShadowMemoryAssignmentList m_ranges;
    RHShadowMemoryAssignmentBlock &operator=(const RHShadowMemoryAssignmentBlock &source)
    {
        m_tag = source.m_tag;
        m_ranges.Assign(source.m_ranges, true, true);
        return *this;
    }
};

inline void RHShadowAssignBlock(RHShadowMemoryBlock &destination, const RHShadowMemoryBlock &source)
{
    (RHShadowMemoryAssignmentBlock &)destination = (const RHShadowMemoryAssignmentBlock &)source;
}

DECOMP_SIZE_ASSERT(RHShadowMemoryNode, 0x10)
DECOMP_SIZE_ASSERT(RHShadowMemoryList, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowMemoryVector, 0x10)
DECOMP_SIZE_ASSERT(RHShadowMemoryBlock, 0x2c)
DECOMP_SIZE_ASSERT(RHShadowMemoryAssignmentList, 0x28)

// Parked: conditional register saves and return reloads differ from the target's shared assignment epilogue.
// STUB: GAME 0x005a0ef0
RHShadowMemoryBlock &RHShadowMemoryBlock::FUN_005a0ef0(const RHShadowMemoryBlock &source)
{
    *(unsigned long *)this = *(const unsigned long *)&source;
    ((RHShadowMemoryAssignmentList *)((char *)this + 4))->Assign(
        *(const RHShadowMemoryAssignmentList *)((const char *)&source + 4), true);
    return *this;
}

// Parked: conditional EBX/ESI saves split the self-assignment return from the target's shared epilogue.
// STUB: GAME 0x005a1020
RHShadowMemoryAssignmentList &RHShadowMemoryAssignmentList::FUN_005a1020(const RHShadowMemoryAssignmentList &source)
{
    Assign(source, false);
    return *this;
}

// Parked: cached-list cursor and insertion temporary scheduling remain under comparison.
// STUB: GAME 0x005a1140
void RHShadowMemoryAssignmentList::FUN_005a1140(const RHShadowMemoryAssignmentList &source, int index)
{
    if (index == (int)m_count)
    {
        int count = source.m_count;
        for (int i = 0; i < count; ++i)
        {
            ((RHShadowPolygonList *)&source)->FUN_005c8e40(i);
            ((RHHumanOpponentListCalls *)this)->FUN_00486110(
                RHHumanOpponentIterator((RHHumanOpponentNode *)m_head),
                (const RHHumanOpponent &)source.m_current->m_value);
        }
    }
    else
    {
        LocateForInsert(index);
        int count = source.m_count;
        for (int i = 0; i < count; ++i)
        {
            ((RHShadowPolygonList *)&source)->FUN_005c8e40(i);
            const RHShadowMemoryRange &value = source.m_current->m_value;
            RHShadowMemoryNode *position = m_current;
            RHShadowMemoryNode *previous = position->m_previous;
            RHShadowMemoryNode *node = (RHShadowMemoryNode *)operator new(sizeof(RHShadowMemoryNode));
            node->m_next = position ? position : node;
            node->m_previous = previous ? previous : node;
            position->m_previous = node;
            node->m_previous->m_next = node;
            new (&node->m_value) RHShadowMemoryRange(value);
            ++m_count;
        }
    }
    m_dirty = true;
}

inline void RHShadowAssignBlocks(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, const RHShadowMemoryBlock &value)
{
    for (; first != last; ++first)
    {
        RHShadowMemoryAssignmentBlock &destination = (RHShadowMemoryAssignmentBlock &)*first;
        const RHShadowMemoryAssignmentBlock &source = (const RHShadowMemoryAssignmentBlock &)value;
        destination.m_tag = source.m_tag;
        RHShadowMemoryAssignmentList &(RHShadowMemoryAssignmentList::*assign)(const RHShadowMemoryAssignmentList &) = &RHShadowMemoryAssignmentList::FUN_005a1020;
        (destination.m_ranges.*assign)(source.m_ranges);
    }
}

#include <list>

class RHMission;

inline void RHShadowMoveBlocks(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination)
{
    while (first != last)
    {
        const RHShadowMemoryAssignmentBlock &from = (const RHShadowMemoryAssignmentBlock &)*--last;
        RHShadowMemoryAssignmentBlock &to = (RHShadowMemoryAssignmentBlock &)*--destination;
        to.m_tag = from.m_tag;
        if (&from.m_ranges != &to.m_ranges)
        {
            void (std::list<RHMission *>::*clear)() = &std::list<RHMission *>::clear;
            (((std::list<RHMission *> *)&to.m_ranges)->*clear)();
            void (RHShadowMemoryAssignmentList::*insert)(const RHShadowMemoryAssignmentList &, int) = &RHShadowMemoryAssignmentList::FUN_005a1140;
            (to.m_ranges.*insert)(from.m_ranges, 0);
        }
    }
}

void rh_shadow_memory_emit(RHShadowMemoryList *list, RHShadowMemoryVector *blocks,
    RHShadowPointerVector *pointers, RHShadowMemoryBlock *first, RHShadowMemoryBlock *last,
    RHShadowMemoryNode *node, const RHShadowMemoryRange &value)
{
    list->FUN_0059fbe0(value);
    blocks->FUN_0059fc40();
    blocks->FUN_0059fcf0(first, *last);
    blocks->FUN_005a0000(first, *last);
    blocks->FUN_005a02e0(first, 2, *last);
    blocks->FUN_005a0600(first, 2, *last);
    pointers->FUN_0059fc80(pointers->m_first);
    list->FUN_0059fcc0(node, node);
    blocks->FUN_0059fef0(first, last);
    blocks->FUN_005a0990();
    blocks->FUN_005a0920(first, last, first);
    blocks->FUN_005a0960(first, 1, *last);
    blocks->FUN_005a09c0(first, last, first);
    blocks->FUN_005a0a00(first, 1, *last);
    FUN_005a0a30(first, last, *last);
    FUN_005a0b90(first, last, last);
    first->FUN_005a0ed0(0);
    first->FUN_005a0ef0(*last);
    ((RHShadowMemoryAssignmentList *)list)->FUN_005a1020(*(RHShadowMemoryAssignmentList *)list);
    ((RHShadowMemoryAssignmentList *)list)->FUN_005a1140(*(RHShadowMemoryAssignmentList *)list, 0);
}

void rh_shadowpolygon_emit(RHShadowPolygon *polygon, const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    polygon->DisplayDebug(box, zoom, actor, point, view, flags);
}

void rh_shadow_memory_range_error_emit(const RHShadowMemoryVector *blocks, bool second)
{
    if (second)
        blocks->FUN_005a0200();
    else
        blocks->FUN_0059ff20();
}
