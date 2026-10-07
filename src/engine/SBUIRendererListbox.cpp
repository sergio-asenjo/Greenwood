#include "SBUIRendererListbox.h"
#include "SB.h"

// STUB: GAME 0x0061d980
bool SBUIListboxUnk0061d980::FUN_0061d980(SBUIListboxUnk0061e890 *first,
    SBUIListboxUnk0061e890 *second, SBUIListboxUnk0061e890 *third, bool alternate)
{
    if (alternate) {
        m_58 = first;
        m_5c = third;
        m_60 = second;
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
        if (first->FUN_0061e890() != second->FUN_0061e890() ||
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
    listbox->FUN_0061d980(font, font, font, false);
}
