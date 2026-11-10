#ifndef RHUNK0051F0F0_H
#define RHUNK0051F0F0_H

#include "SBGeoSegment2D.h"

class __declspec(novtable) RHUnk0051f0f0 : public SBGeoSegment2D
{
public:
    RHUnk0051f0f0();
    virtual ~RHUnk0051f0f0(); // vtable+0x00
    void *FUN_0051f190(unsigned flags);
    void SetFlags(unsigned flags) { m_14 |= flags; }
    void SetEnabled(bool enabled) { m_18 = enabled; }
    void SetReverse(bool reverse)
    {
        if (reverse)
            m_14 |= 1;
        else
            m_14 &= ~1;
    }
    unsigned m_14;
    bool m_18;
    unsigned m_1c;
};

#endif
