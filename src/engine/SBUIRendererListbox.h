#ifndef SB_UI_RENDERER_LISTBOX_H
#define SB_UI_RENDERER_LISTBOX_H

#include <string>

#include "SBUIListboxFont.h"

class SBUIListboxUnk0061d980
{
public:
    char m_00[0x4c];
    SBFontUnk0061e840 *m_4c;
    SBFontUnk0061e840 *m_50;
    SBFontUnk0061e840 *m_54;
    SBFontUnk0061e840 *m_58;
    SBFontUnk0061e840 *m_5c;
    SBFontUnk0061e840 *m_60;
    char m_64[0x1a];
    unsigned short m_7e;

    bool FUN_0061d1c0();

    bool FUN_0061d980(SBFontUnk0061e840 *, SBFontUnk0061e840 *,
        SBFontUnk0061e840 *, bool);

    bool FUN_0061d1d0(std::wstring *text, unsigned flags);
};

#endif
