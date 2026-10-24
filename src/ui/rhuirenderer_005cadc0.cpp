#include "SBNullstr.h"
#include "rhuirenderer_005cadc0.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBUIInputFieldDrawUnk, 0x30)
DECOMP_SIZE_ASSERT(RHPortraitRenderer0060dab0, 0x50)
DECOMP_SIZE_ASSERT(RHPortraitRenderer005cadc0, 0x58)


// FUNCTION: GAME 0x005cadc0
RHPortraitRenderer005cadc0::RHPortraitRenderer005cadc0()
{
    m_vptr = 0x00679e7c;
    m_enabled = 0;
    m_disabled = 0;
}

// FUNCTION: GAME 0x005cade0
void *RHPortraitRenderer005cadc0::FUN_005cade0(unsigned flags)
{
    this->~RHPortraitRenderer005cadc0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005cae00
RHPortraitRenderer005cadc0::~RHPortraitRenderer005cadc0()
{
    m_vptr = 0x00679e7c;
}

// FUNCTION: GAME 0x005cae10
void RHPortraitRenderer005cadc0::FUN_005cae10(int screen)
{
    if (screen)
    {
        // STRING: GAME 0x006b8cb8
        m_enabled = (SBUIListboxUnk0061e890 *)((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("MenuButtonEnabled"));
        // STRING: GAME 0x006b8ca4
        m_disabled = (SBUIListboxUnk0061e890 *)((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("MenuButtonDisabled"));
    }
}

// FUNCTION: GAME 0x005cafa0
bool RHPortraitRenderer005cadc0::FUN_005cafa0(unsigned id)
{
    if (((SBUIUnk0060dae0 *)this)->FUN_0060dae0(id))
    {
        SBGeoBoundingBox2D area(*(SBGeoBoundingBox2D *)((SBUIUnk0060d530 *)this)->FUN_0060d690());
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((SBUIUnk0060d530 *)this)->FUN_0060d690());
        SBUIInputFieldDrawUnk drawer;
        SBUIListboxUnk0061e890 *font = id ? m_enabled : m_disabled;
        if (font)
        {
            float height = box.m_08.m_y - box.m_00.m_y;
            float top = box.m_00.m_y;
            float y = (height - (unsigned int)font->FUN_0061e890()) * 0.5f + top;
            box.SetMinY(y);
            box.SetMaxY((unsigned int)font->FUN_0061e890() + y);
        }
        drawer.FUN_00614230(font, (std::wstring *)((char *)this + 0x28), box, 2, 0, 1);
        return true;
    }
    return false;
}
