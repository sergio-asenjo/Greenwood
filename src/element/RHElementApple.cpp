#include "RHProjectileLifetime.h"
#include "RHUnkTargetSpriteCalls.h"

class RHElementActorHuman;

class RHElementApple : public RHProjectileLifetime
{
public:
    RHElementApple(RHElementActorHuman *actor);
    void FUN_004a6380();
};

// FUNCTION: GAME 0x004a62e0
RHElementApple::RHElementApple(RHElementActorHuman *actor)
    : RHProjectileLifetime(11, actor)
{
    *(unsigned long *)this = 0x006781f8;
    *(int *)((char *)this + 0xb0) = 4;
}

// FUNCTION: GAME 0x004a6380
void RHElementApple::FUN_004a6380()
{
    (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    ((RHElementProjectile *)this)->FUN_004b8230();
}

void EmitRHElementApple(void *storage, RHElementActorHuman *actor)
{
    ((RHElementApple *)storage)->RHElementApple::RHElementApple(actor);
}
