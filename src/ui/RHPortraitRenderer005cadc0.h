#ifndef RHPORTRAITRENDERER005CADC0_H
#define RHPORTRAITRENDERER005CADC0_H

#include "Decomp.h"
#include <string>
#include "RHPortraitRenderer0060dab0.h"

class SBUIListboxUnk0061e890;

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
