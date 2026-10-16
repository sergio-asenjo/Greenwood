#ifndef RHUIRENDERERSHIFTINGTITBITCLASS_H
#define RHUIRENDERERSHIFTINGTITBITCLASS_H

#include "RHUIRendererShiftingClass.h"

class RHUIRendererShiftingTitbit : public RHUIRendererShifting
{
public:
    RHUIRendererShiftingTitbit();
    ~RHUIRendererShiftingTitbit();
    void *FUN_005cc0f0(unsigned flags);
    bool Render(unsigned);
    void Emit();
    unsigned m_54;
    bool m_58;
    bool m_59;
};

#endif
