#ifndef RHUNK004BA8D0_H
#define RHUNK004BA8D0_H

#include "RHProjectileLifetime.h"

class __declspec(novtable) RHUnk004ba8d0 : public RHProjectileLifetime
{
public:
    RHUnk004ba8d0(void *victim);
};

DECOMP_SIZE_ASSERT(RHUnk004ba8d0, 0x15c)
DECOMP_SIZE_ASSERT(RHProjectileLifetime, 0x15c)
DECOMP_SIZE_ASSERT(RHScriptNode, 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHScriptNode, prev) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHScriptNode, data) == 8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004ba8d0, m_b0) == 0xb0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004ba8d0, point100) == 0x100)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004ba8d0, target) == 0x12c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004ba8d0, list) == 0x138)

#endif
