#include "SBNullstr.h"
#include "SBUIRendererListbox.h"
#include "SB.h"
#include "SBUIRendererInputField.h"
#include "RHPortraitInputRenderer.h"
#include "RHMobileUnk00607da0.h"
#include "RHUnk00600820.h"
#include "RHPortraitDrawCalls.h"
#include "RHMobileUnk006091b0.h"

DECOMP_SIZE_ASSERT(RHPortraitInputRenderer, 0x84)

// FUNCTION: GAME 0x0061c530
RHPortraitInputRenderer::RHPortraitInputRenderer() : m_64(-1), m_68(-1), m_82(0x14)
{
}

// FUNCTION: GAME 0x0061c5b0
RHPortraitInputRenderer::~RHPortraitInputRenderer()
{
}

// FUNCTION: GAME 0x0061c590
void *RHPortraitInputRenderer::FUN_0061c590(unsigned flags)
{
    this->RHPortraitInputRenderer::~RHPortraitInputRenderer();
    if (flags & 1)
        operator delete(this);
    return this;
}

inline void RHListboxAssign(SBGeoBoundingBox2D &destination, const SBGeoBoundingBox2D &source)
{
    ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)source);
}

// STUB: GAME 0x0061c610
bool RHPortraitInputRenderer::FUN_0061c610(unsigned long)
{
    SBGeoBoundingBox2D source;
    SBGeoBoundingBox2D destination;
    unsigned int top;
    unsigned int middle;
    unsigned int bottom;
    if (m_64 == -1)
    {
        bool finished = false;
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 3, (float *)&top);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 4, (float *)&middle);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 5, (float *)&bottom);
        m_64 = ((SBDrawManager *)m_drawManager)->Unk005e4ed0(
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(top),
            (unsigned short)(m_position.m_p1.m_y - m_position.m_p0.m_y), 0, false);
        *(unsigned short *)((char *)this + 0x7c) = (unsigned short)(m_position.m_p1.m_y - m_position.m_p0.m_y);
        RHListboxAssign(source, SBGeoBoundingBox2D(0, 0,
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(top),
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(top)));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(top, &source, m_64, &source, 0);
        float height = m_position.m_p1.m_y - m_position.m_p0.m_y;
        RHListboxAssign(destination, SBGeoBoundingBox2D(0,
            height - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            m_position.m_p1.m_y - m_position.m_p0.m_y));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(bottom, 0, m_64, &destination, 0);
        RHListboxAssign(destination, SBGeoBoundingBox2D(0,
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            m_position.m_p1.m_y - m_position.m_p0.m_y
                - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom)
                - ((SBDrawManager *)m_drawManager)->FUN_005e5750(top)));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(middle, 0, m_64, &destination, 0);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 0, (float *)&top);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 1, (float *)&middle);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 2, (float *)&bottom);
        m_68 = ((SBDrawManager *)m_drawManager)->Unk005e4ed0(
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(top),
            (unsigned short)(m_position.m_p1.m_y - m_position.m_p0.m_y), 0, false);
        RHListboxAssign(source, SBGeoBoundingBox2D(0, 0,
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(top),
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(top)));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(top, &source, m_68, &source, 0);
        RHListboxAssign(destination, SBGeoBoundingBox2D(0,
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(top)
                + ((SBDrawManager *)m_drawManager)->FUN_005e5750(middle)));
        do
        {
            ((SBDrawManager *)m_drawManager)->FUN_005e6440(middle, 0, m_68, &destination, 0);
            float end = destination.m_p1.m_y;
            if (m_position.m_p1.m_y - m_position.m_p0.m_y
                    - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom) <= end)
                finished = true;
            ((RHMobileUnk006091b0 *)&destination)->FUN_006091b0(
                SBGeoVector2D(0, ((SBDrawManager *)m_drawManager)->FUN_005e5750(middle)));
        } while (!finished);
        height = m_position.m_p1.m_y - m_position.m_p0.m_y;
        RHListboxAssign(destination, SBGeoBoundingBox2D(0,
            height - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            m_position.m_p1.m_y - m_position.m_p0.m_y));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(bottom, 0, m_68, &destination, 0);
    }
    float lower = m_position.m_p1.m_y;
    float right = m_position.m_p1.m_x;
    float upper = m_position.m_p0.m_y;
    float left = right;
    RHListboxAssign(destination, SBGeoBoundingBox2D(
        left - ((SBDrawManager *)m_drawManager)->FUN_005e56c0(m_68), upper, right, lower));
    ((SBDrawManager *)m_drawManager)->FUN_005e6440(m_68, 0, m_hardware, &destination, 1);
    RHListboxAssign(destination, FUN_0061d620());
    {
        SBGeoVector2D origin(m_position.m_p0);
        RHListboxAssign(source, FUN_0061d620() - origin);
    }
    RHListboxAssign(source, source - SBGeoVector2D(source.m_p0.m_x, source.m_p0.m_y));
    if (source.m_p1.m_y - source.m_p0.m_y != *(unsigned short *)((char *)this + 0x7c))
    {
        SBGeoBoundingBox2D part;
        SBGeoBoundingBox2D target;
        *(unsigned short *)((char *)this + 0x7c) = (unsigned short)(source.m_p1.m_y - source.m_p0.m_y);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 3, (float *)&top);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 4, (float *)&middle);
        ((RHUnk00600820 *)m_resources)->ResolveSurface((void *)m_widgetResource, 5, (float *)&bottom);
        RHListboxAssign(part, SBGeoBoundingBox2D(0, 0,
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(top),
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(top)));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(top, &part, m_64, &part, 0);
        float height = source.m_p1.m_y - source.m_p0.m_y;
        RHListboxAssign(target, SBGeoBoundingBox2D(0,
            height - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            height));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(bottom, 0, m_64, &target, 0);
        RHListboxAssign(target, SBGeoBoundingBox2D(0,
            ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom),
            ((SBDrawManager *)m_drawManager)->FUN_005e56c0(bottom),
            source.m_p1.m_y - source.m_p0.m_y - ((SBDrawManager *)m_drawManager)->FUN_005e5750(bottom)));
        ((SBDrawManager *)m_drawManager)->FUN_005e6440(middle, 0, m_64, &target, 0);
    }
    ((SBDrawManager *)m_drawManager)->BlitAlphaKeying(m_64, &source, m_hardware,
        &destination.FUN_006090d0(SBGeoVector2D(0, 0)), 31, 20, 1);
    return true;
}

// FUNCTION: GAME 0x0061d1c0
bool SBUIListboxUnk0061d980::FUN_0061d1c0()
{
    m_7e = 0;
    return true;
}

// FUNCTION: GAME 0x0061d980
bool SBUIListboxUnk0061d980::FUN_0061d980(SBFontUnk0061e840 *first,
    SBFontUnk0061e840 *second, SBFontUnk0061e840 *third, bool alternate)
{
    if (alternate) {
        m_58 = first;
        m_60 = second;
        m_5c = third;
        int value = m_4c->GetHeight();
        if (first->GetHeight() != value ||
            (value = m_54->GetHeight(), m_60->GetHeight() != value) ||
            (value = m_50->GetHeight(), m_5c->GetHeight() != value)) {
            SBAssert(0,
                // STRING: GAME 0x006bb7a8
                "P:\\Robin Hood\\SBLibNG\\SBUIRendererListbox.cpp", 0x1ac,
                // STRING: GAME 0x006bb7f0
                "Inconsistency in alternate font.");
            return false;
        }
    } else {
        m_4c = first;
        m_54 = second;
        m_50 = third;
        int value;
        if (m_4c->GetHeight() != m_54->GetHeight() ||
            (value = m_50->GetHeight(), m_54->GetHeight() != value)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRendererListbox.cpp", 0x1b8,
                // STRING: GAME 0x006bb7d8
                "Inconsistency in font.");
            return false;
        }
    }
    return true;
}

// STUB: GAME 0x0061d1d0
bool SBUIListboxUnk0061d980::FUN_0061d1d0(std::wstring *text, unsigned flags)
{
    SBGeoBoundingBox2D lineBox;
    SBUIInputFieldDrawUnk drawer;
    ((RHMobileUnk00607da0 *)&lineBox)->FUN_00607da0(
        *(const RHMobileUnk00607da0 *)&((RHPortraitInputRenderer *)this)
            ->FUN_0061d3f0(m_7e, flags));
    unsigned mode;
    switch (flags & 0xf00)
    {
    case 0x200:
        mode = 2;
        break;
    case 0:
        mode = 1;
        break;
    case 0x100:
        mode = 8;
        break;
    case 0x300:
        mode = 4;
        break;
    default:
        mode = (unsigned)(unsigned long)text;
        break;
    }
    if (!(flags & 0x2000))
    {
        unsigned style = flags & 0xf0;
        if (style == 0)
            drawer.FUN_00614230(m_4c, (*(std::wstring *volatile *)&text)[0], lineBox, mode, 0, 1);
        else if (style == 0x10 || style == 0x20)
            drawer.FUN_00614230(m_54, (*(std::wstring *volatile *)&text)[0], lineBox, mode, 0, 1);
    }
    else
    {
        unsigned style = flags & 0xf0;
        if (style == 0)
            drawer.FUN_00614230(m_58, (*(std::wstring *volatile *)&text)[0], lineBox, mode, 0, 1);
        else if (style == 0x10 || style == 0x20)
            drawer.FUN_00614230(m_60, (*(std::wstring *volatile *)&text)[0], lineBox, mode, 0, 1);
    }
    ++m_7e;
    return ((SBGeoBoundingBox2D *)((char *)this + 8))->FUN_006084a0(
        ((RHPortraitInputRenderer *)this)->FUN_0061d3f0(m_7e, flags));
}

void EmitSBUIRendererListbox(SBUIListboxUnk0061d980 *listbox,
    SBFontUnk0061e840 *font)
{
    ((RHPortraitInputRenderer *)listbox)->FUN_0061c590(0);
    listbox->FUN_0061d1c0();
    listbox->FUN_0061d980(font, font, font, false);
    listbox->FUN_0061d1d0(0, 0);
}
