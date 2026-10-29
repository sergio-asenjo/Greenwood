#include "SBNullstr.h"
#include "RHElementObject.h"

#include "RHCampaignValueCalls.h"
extern RHUnk00452030 *g_unk0x6c07fc;

class RHEngine;
extern RHEngine *g_pEngine;

class RHUnk004a7b00
{
public:
    bool FUN_004a7b00();
};

#include "RHScrollObjectCalls.h"

// FUNCTION: GAME 0x004a7840
bool RHElementObject::FUN_004a7840(void *point, void *actor, int focus)
{
    if (!*((char *)this + 0x12) || !actor ||
        *(unsigned int *)((char *)g_pEngine + 0x4a00) > 1)
        return false;
    if (focus == 3 && *(void **)((char *)actor + 0x268) == 0)
    {
        RHUnk00452030 *quests = g_unk0x6c07fc;
        if ((((RHUnk004a7b00 *)this)->FUN_004a7b00() &&
             *(int *)((char *)quests + 0x148) == *(int *)((char *)quests + 0x178)) ||
            m_b0 == 0x12)
            return false;
    }
    return ((RHScrollObjectCalls *)this)->FUN_004b23c0(point, actor, (void *)focus);
}

// FUNCTION: GAME 0x004a78c0
bool RHElementObject::FUN_004a78c0(void *actor)
{
    if (m_b0 == 0xe)
    {
        if (g_unk0x6c07fc->Get(0) >= 0xa)
            return false;
    }
    return FUN_004b2420(actor);
}
