#include "SBNullstr.h"
// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14]; // 0x00
};
#include "rhuirenderer_005cb420.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBUIInputFieldDrawUnk, 0x30)
DECOMP_SIZE_ASSERT(RHPopupRenderer0060dbc0, 0x7c)
DECOMP_SIZE_ASSERT(RHUnk005cba10, 0x9c)

#define m_box (*(SBGeoBoundingBox2D *)((char *)this + 0x08))
#define m_text (*(std::wstring *)((char *)this + 0x28))
#define m_40 ((unsigned int *)((char *)this + 0x40))
#define m_48 (*(unsigned int *)((char *)this + 0x48))


inline float Min(float first, float second)
{
    if (second > first)
        return first;
    return second;
}

// FUNCTION: GAME 0x005cb420
RHUnk005cba10::RHUnk005cba10()
    : m_dropped(0, 0)
{
    m_characters = 0;
    m_lines = 0;
}

#pragma auto_inline(off)
// FUNCTION: GAME 0x005cb4a0
void *RHUnk005cba10::FUN_005cb4a0(unsigned flags)
{
    this->RHUnk005cba10::~RHUnk005cba10();
    if (flags & 1)
        operator delete(this);
    return this;
}

#pragma auto_inline(on)

// Parked: 91.38% — the first m_64 read must not CSE with the per-branch reloads; only a volatile
// read achieves that and it emits `mov dx;and edx,0xffff` for `xor edx,edx;mov dx`. The target
// also pops the Min operand with fcomp and reloads m_dropped.m_x, keeping the result in st(1).
// STUB: GAME 0x005cb550
SBGeoBoundingBox2D RHUnk005cba10::FUN_005cb550(SBUIListboxUnk0061e890 *font, bool clip) const
{
    SBGeoBoundingBox2D box(m_box);
    float height = m_dropped.m_y;
    float lines = height / (unsigned int)(font->FUN_0061e890() - *(volatile unsigned short *)&m_64);
    unsigned int count = (unsigned int)lines;
    if (lines - count != 0.0f)
        lines = count + 1;
    if (clip)
    {
        float shift = Min(box.m_08.m_x - box.m_00.m_x, m_dropped.m_x);
        box.SetMaxX(box.m_08.m_x - shift);
        float top = box.m_00.m_y;
        int pad = m_64;
        box.SetMaxY((unsigned int)(font->FUN_0061e890() - pad) * lines + pad + top);
    }
    else
    {
        float top = box.m_00.m_y;
        int pad = m_64;
        box.SetMinY((unsigned int)(font->FUN_0061e890() - pad) * lines + pad + top);
    }
    return box;
}

#include "RHSectorProductionCampaign.h"

// FUNCTION: GAME 0x005cb6f0
RHSectorProductionRelics *RHSectorProductionCampaign::FUN_005cb6f0()
{
    return (RHSectorProductionRelics *)((char *)this + 0x84);
}

// FUNCTION: GAME 0x005cb700
void RHUnk005cba10::FUN_005cb700(SBUIListboxUnk0061e890 *font)
{
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned int, unsigned int);
    SBUIInputFieldDrawUnk drawer;
    std::wstring text;
    SBGeoBoundingBox2D box;
    Assign assign = &std::wstring::assign;
    (text.*assign)(m_text, 0, std::wstring::npos);
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)FUN_005cb550(font, true));
    m_characters = 0;
    m_lines += drawer.FUN_00614230(font, &text, box, m_60, m_64, 1);
    m_characters += drawer.FUN_00613e80();
    std::wstring &rest = drawer.FUN_00613e90();
    (text.*assign)(rest, 0, std::wstring::npos);
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)FUN_005cb550(font, false));
    box.SetMinY(box.m_00.m_y - m_64);
    m_lines += drawer.FUN_00614230(font, &text, box, m_60, m_64, 1);
    m_characters += drawer.FUN_00613e80();
    std::wstring &remaining = drawer.FUN_00613e90();
    (m_rendered.*assign)(remaining, 0, std::wstring::npos);
}

// FUNCTION: GAME 0x005cb9d0
void RHUnk005cba10::FUN_005cb9d0(unsigned long width, unsigned long height)
{
    m_dropped.m_x = width;
    m_dropped.m_y = height;
}

// FUNCTION: GAME 0x005cba10
bool RHUnk005cba10::FUN_005cba10(unsigned id)
{
    if (m_dropped.m_x == 0.0f && m_dropped.m_y == 0.0f)
        return FUN_0060dd10(id);
    if (id == 0xff)
    {
        m_40[m_48 & 1] = 0;
        return false;
    }
    SBUIListboxUnk0061e890 *font;
    switch (id)
    {
    case 0:
        font = m_54;
        break;
    case 2:
        font = m_58;
        break;
    case 3:
        font = m_5c;
        break;
    case 1:
        font = m_50;
        break;
    default:
        font = m_50;
        break;
    }
    if (font)
    {
        if (m_box.m_08.m_x - m_box.m_00.m_x > 0.0f)
        {
            FUN_005cb700(font);
            return true;
        }
        return false;
    }
    m_40[m_48 & 1] = 0;
    return true;
}
