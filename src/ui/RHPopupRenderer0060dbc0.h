#ifndef RHPOPUPRENDERER0060DBC0_H
#define RHPOPUPRENDERER0060DBC0_H

#include "RHPortraitRenderer0060dab0.h"

class SBUIListboxUnk0061e890;

// SIZE 0x7c
// VTABLE: GAME 0x0067a860
class RHPopupRenderer0060dbc0 : public RHPortraitRenderer0060dab0
{
public:
    RHPopupRenderer0060dbc0();
    ~RHPopupRenderer0060dbc0();
    void *FUN_0060dc00(unsigned flags);
    bool FUN_0060dd10(unsigned id);
    SBUIListboxUnk0061e890 *m_50;
    SBUIListboxUnk0061e890 *m_54;
    SBUIListboxUnk0061e890 *m_58;
    SBUIListboxUnk0061e890 *m_5c;
    void SetM60(unsigned int value) { m_60 = value; }
    unsigned int m_60;
    void SetM64(unsigned short value) { m_64 = value; }
    unsigned short m_64;
    undefined m_66[2];
    std::wstring m_68;
    char m_78;
    undefined m_79[3];
};

#endif
