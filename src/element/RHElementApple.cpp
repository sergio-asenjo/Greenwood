#include "RHProjectileLifetime.h"
#include "RHUnkTargetSpriteCalls.h"
#include "RHProjectileSoundCalls.h"
#include "RHEngineWidenedCalls.h"
#include "RHElementActorSoldier.h"

class RHElementActorHuman;

class __declspec(novtable) RHElementApple : public RHProjectileLifetime
{
public:
    RHElementApple(RHElementActorHuman *actor);
    ~RHElementApple();
    void FUN_004a6380();
    bool FUN_004a63a0(void *target);
    void *InteractionTarget() const { return target; }
    bool HitHuman(RHElementActorHuman *actor);
    bool FUN_004a6510();
    void *FUN_004a6650(unsigned flags);
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

#include "RHSequenceInteractionAction.h"

typedef char RHAppleInteractionSize[(sizeof(RHUnk00585ea0) == 0x68) ? 1 : -1];

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;
extern char g_unk0x6c0560[4];

class RHScriptBatchCalls
{
public:
    unsigned int Unk004baea0();
    void *Unk0058a940(void *context, int value, void *element);
};

// FUNCTION: GAME 0x004a63a0
bool RHElementApple::FUN_004a63a0(void *target)
{
    (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    if (((RHScriptBatchCalls *)target)->Unk004baea0() & 0x40)
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x99, target, InteractionTarget());
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, action);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004a6450
bool RHElementApple::HitHuman(RHElementActorHuman *actor)
{
    (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    unsigned kind = *(unsigned *)((char *)actor + 4) & 0x1f;
    if (kind == 0x14)
    {
        ((RHElementActorSoldier *)actor)->SetAppleSmell(true);
        ((RHSoldierStimulusCalls *)((char *)actor + 0x49c +
            (*(int **)((char *)actor + 0x49c))[1]))->FUN_004a64a0(
            0x1c, *(RHMalignityPosition *)((char *)this + 0x118));
    }
    return true;
}

// FUNCTION: GAME 0x004a6510
bool RHElementApple::FUN_004a6510()
{
    bool result = ((RHProjectileRefreshCalls *)this)->FUN_004b82e0();
    if (!*((char *)this + 0x132))
        *((bool *)this + 0x12) = (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(0) != 3;
    return result;
}

// FUNCTION: GAME 0x004a6650
void *RHElementApple::FUN_004a6650(unsigned flags)
{
    this->~RHElementApple();
    if (flags & 1)
        operator delete(this);
    return this;
}

RHElementApple::~RHElementApple() {}

void EmitRHElementApple(void *storage, RHElementActorHuman *actor)
{
    ((RHElementApple *)storage)->RHElementApple::RHElementApple(actor);
}
