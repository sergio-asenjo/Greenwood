#ifndef RHELEMENTFXMASKED_H
#define RHELEMENTFXMASKED_H

#include "RHElementFXCore.h"

class RHElementMobile;

// VTABLE: GAME 0x00678508
class RHElementFXMasked : public RHElementFX
{
public:
    RHElementFXMasked();
    virtual ~RHElementFXMasked();
    virtual void *Refresh(unsigned long surface, float scale, const SBGeoBoundingBox2D &box, unsigned long flags);
    virtual char FUN_004b9f40();
    virtual bool Serialize(SBFile &file);
    float m_fc;
    RHElementMobile *m_100;
};

#endif
