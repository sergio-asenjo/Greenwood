#include "SBNullstr.h"
#include "SBUIRendererListbox.h"
#include "SB.h"
#include "SBUIRendererInputField.h"
#include "RHPortraitInputRenderer.h"
#include "RHMobileUnk00607da0.h"

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

// FUNCTION: GAME 0x0061d1c0
bool SBUIListboxUnk0061d980::FUN_0061d1c0()
{
    m_7e = 0;
    return true;
}

// FUNCTION: GAME 0x0061d980
bool SBUIListboxUnk0061d980::FUN_0061d980(SBUIListboxUnk0061e890 *first,
    SBUIListboxUnk0061e890 *second, SBUIListboxUnk0061e890 *third, bool alternate)
{
    if (alternate) {
        m_58 = first;
        m_60 = second;
        m_5c = third;
        int value = m_4c->FUN_0061e890();
        if (first->FUN_0061e890() != value ||
            (value = m_54->FUN_0061e890(), m_60->FUN_0061e890() != value) ||
            (value = m_50->FUN_0061e890(), m_5c->FUN_0061e890() != value)) {
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
        if (m_4c->FUN_0061e890() != m_54->FUN_0061e890() ||
            (value = m_50->FUN_0061e890(), m_54->FUN_0061e890() != value)) {
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
            drawer.FUN_00614230(m_4c, *(std::wstring *volatile *)&text, lineBox, mode, 0, 1);
        else if (style == 0x10 || style == 0x20)
            drawer.FUN_00614230(m_54, *(std::wstring *volatile *)&text, lineBox, mode, 0, 1);
    }
    else
    {
        unsigned style = flags & 0xf0;
        if (style == 0)
            drawer.FUN_00614230(m_58, *(std::wstring *volatile *)&text, lineBox, mode, 0, 1);
        else if (style == 0x10 || style == 0x20)
            drawer.FUN_00614230(m_60, *(std::wstring *volatile *)&text, lineBox, mode, 0, 1);
    }
    ++m_7e;
    return ((SBGeoBoundingBox2D *)((char *)this + 8))->FUN_006084a0(
        ((RHPortraitInputRenderer *)this)->FUN_0061d3f0(m_7e, flags));
}

void EmitSBUIRendererListbox(SBUIListboxUnk0061d980 *listbox,
    SBUIListboxUnk0061e890 *font)
{
    ((RHPortraitInputRenderer *)listbox)->FUN_0061c590(0);
    listbox->FUN_0061d1c0();
    listbox->FUN_0061d980(font, font, font, false);
    listbox->FUN_0061d1d0(0, 0);
}
