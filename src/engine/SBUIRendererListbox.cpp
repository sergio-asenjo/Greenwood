#include "SBNullstr.h"
#include "SBUIRendererListbox.h"
#include "SB.h"
#include "SBGeoBoundingBox2D.h"

#include "RHPortraitRenderer0060d470.h"

// VTABLE: GAME 0x0067ae1c
class RHPortraitInputRenderer : public RHPortraitRenderer0060d470
{
public:
    RHPortraitInputRenderer();
    ~RHPortraitInputRenderer();
    void *FUN_0061c590(unsigned flags);
    char m_4c[0x18];
    int m_64;
    int m_68;
    SBGeoPoint2D m_6c;
    char m_74[0xe];
    unsigned short m_82;
};

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
    this->~RHPortraitInputRenderer();
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

void EmitSBUIRendererListbox(SBUIListboxUnk0061d980 *listbox,
    SBUIListboxUnk0061e890 *font)
{
    ((RHPortraitInputRenderer *)listbox)->FUN_0061c590(0);
    listbox->FUN_0061d1c0();
    listbox->FUN_0061d980(font, font, font, false);
}
