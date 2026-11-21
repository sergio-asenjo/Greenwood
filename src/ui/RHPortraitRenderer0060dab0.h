#ifndef RHPORTRAITRENDERER0060DAB0_H
#define RHPORTRAITRENDERER0060DAB0_H

#include "Decomp.h"
#include "RHPortraitRenderer0060d470.h"

// VTABLE: GAME 0x0067a610
// SIZE 0x50
class RHPortraitRenderer0060dab0 : public RHPortraitRenderer0060d470
{
public:
    RHPortraitRenderer0060dab0();
    ~RHPortraitRenderer0060dab0();
    RHPortraitRenderer0060dab0 &operator=(const RHPortraitRenderer0060dab0 &other);
    RHPortraitRenderer0060dab0 &Assign(const RHPortraitRenderer0060dab0 &other);
    bool FUN_0060dae0(unsigned int id);
    unsigned int FUN_0060db80(unsigned int id);
    unsigned short m_4c;    // 0x4c
    unsigned short m_4e;    // 0x4e
};

#endif
