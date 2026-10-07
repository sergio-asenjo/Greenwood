#ifndef SB_UI_RENDERER_LISTBOX_H
#define SB_UI_RENDERER_LISTBOX_H

class SBUIListboxUnk0061e890
{
public:
    char m_00[0x40];
    int m_40;
    int FUN_0061e890();
};

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

    bool FUN_0061d980(SBUIListboxUnk0061e890 *, SBUIListboxUnk0061e890 *,
        SBUIListboxUnk0061e890 *, bool);
};

#endif
