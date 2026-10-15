#ifndef RHPORTRAITRENDERER005CADC0_H
#define RHPORTRAITRENDERER005CADC0_H

#include "Decomp.h"
#include <string>

class SBUIListboxUnk0061e890;

class RHPortraitRenderer0060dab0
{
public:
    RHPortraitRenderer0060dab0();
    ~RHPortraitRenderer0060dab0();
    undefined4 m_vptr;
    undefined m_04[0x24];
    std::wstring m_text;
    undefined m_38[0x18];
};

class RHPortraitRenderer005cadc0 : public RHPortraitRenderer0060dab0
{
public:
    RHPortraitRenderer005cadc0();
    ~RHPortraitRenderer005cadc0();
    void *FUN_005cade0(unsigned flags);
    void FUN_005cae10(int screen);
    bool FUN_005cafa0(unsigned id);
    SBUIListboxUnk0061e890 *m_enabled;
    SBUIListboxUnk0061e890 *m_disabled;
};

#endif
