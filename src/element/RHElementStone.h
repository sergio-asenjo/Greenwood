#ifndef RHELEMENTSTONE_H
#define RHELEMENTSTONE_H

#include "RHProjectileLifetime.h"

class RHElementActorHuman;

class __declspec(novtable) RHElementStone : public RHProjectileLifetime
{
public:
    RHElementStone(void *victim);
    bool FUN_004ba900(bool flag);
    virtual int FUN_004ba970();
    virtual bool HitHuman(RHElementActorHuman *actor);
    virtual bool FUN_004ba980(void *target);
    void *InteractionTarget() const { return target; }
};

DECOMP_SIZE_ASSERT(RHElementStone, 0x15c)
DECOMP_SIZE_ASSERT(RHProjectileLifetime, 0x15c)
DECOMP_SIZE_ASSERT(RHScriptNode, 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHScriptNode, prev) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHScriptNode, data) == 8)
DECOMP_STATIC_ASSERT(offsetof(RHElementStone, m_b0) == 0xb0)
DECOMP_STATIC_ASSERT(offsetof(RHElementStone, point100) == 0x100)
DECOMP_STATIC_ASSERT(offsetof(RHElementStone, impactPosition) == 0x118)
DECOMP_STATIC_ASSERT(offsetof(RHElementStone, target) == 0x12c)
DECOMP_STATIC_ASSERT(offsetof(RHElementStone, list) == 0x138)

#endif
