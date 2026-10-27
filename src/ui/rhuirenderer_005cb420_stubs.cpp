#include "SBNullstr.h"
#include "rhuirenderer_005cb420.h"

class SBUIUnk0060dae0
{
public:
    bool FUN_0060dae0(unsigned int id);
};

class SBUIUnk0060dd00
{
public:
    int FUN_0060dda0(SBUIListboxUnk0061e890 *font, bool flag);
};

unsigned short SBUIInputFieldDrawUnk::FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned short, unsigned int) { return 0; }
std::wstring &SBUIInputFieldDrawUnk::FUN_00613e90() { return m_00; }

// FUNCTION: GAME 0x0060dbc0
RHPopupRenderer0060dbc0::RHPopupRenderer0060dbc0()
    : m_50(0), m_54(0), m_58(0), m_5c(0), m_60(2), m_64(0), m_78(0)
{
}

// FUNCTION: GAME 0x0060dc00
void *RHPopupRenderer0060dbc0::FUN_0060dc00(unsigned flags)
{
    this->RHPopupRenderer0060dbc0::~RHPopupRenderer0060dbc0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0060dc80
RHPopupRenderer0060dbc0::~RHPopupRenderer0060dbc0()
{
}

// FUNCTION: GAME 0x0060dd10
bool RHPopupRenderer0060dbc0::FUN_0060dd10(unsigned id)
{
    if (*(void **)((char *)this + 0x38))
        ((SBUIUnk0060dae0 *)this)->FUN_0060dae0(id);
    if (id == 0xff)
    {
        ((unsigned int *)((char *)this + 0x40))[*(unsigned int *)((char *)this + 0x48) & 1] = 0;
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
        ((SBUIUnk0060dd00 *)this)->FUN_0060dda0(font, false);
        return true;
    }
    ((unsigned int *)((char *)this + 0x40))[*(unsigned int *)((char *)this + 0x48) & 1] = 0;
    return true;
}
