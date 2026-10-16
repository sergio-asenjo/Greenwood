#ifndef RHELEMENTWASPNEST_H
#define RHELEMENTWASPNEST_H

#include "RHElementProjectile.h"

class RHElementWaspNest : public RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);
    void WaspKilled();
    void FUN_004be0e0();
    bool FUN_004be1a0();

private:
    unsigned int m_unk15c; // [0x15c]
};

#endif
