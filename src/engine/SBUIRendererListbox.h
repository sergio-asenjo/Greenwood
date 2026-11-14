#ifndef SB_UI_RENDERER_LISTBOX_H
#define SB_UI_RENDERER_LISTBOX_H

#include <string>

#include "SBUIListboxFont.h"

class SBUIListboxUnk0061d980
{
public:
    char m_00[0x4c];
    SBUIListboxUnk0061e890 *m_4c;
    SBUIListboxUnk0061e890 *m_50;
    SBUIListboxUnk0061e890 *m_54;
    SBUIListboxUnk0061e890 *m_58;
    SBUIListboxUnk0061e890 *m_5c;
    SBUIListboxUnk0061e890 *m_60;
    char m_64[0x1a];
    unsigned short m_7e;

    bool FUN_0061d1c0();

    bool FUN_0061d980(SBUIListboxUnk0061e890 *, SBUIListboxUnk0061e890 *,
        SBUIListboxUnk0061e890 *, bool);

    bool FUN_0061d1d0(std::wstring *text, unsigned flags);
};

#endif
