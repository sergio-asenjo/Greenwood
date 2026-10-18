class RHUnkSightPlane
{
public:
    void *FUN_005df990();
};

#include "RHActorCrossingHumanCalls.h"

// GLOBAL: GAME 0x00677ba8
float g_unk0x00677ba8;

// FUNCTION: GAME 0x004843a0
bool RHActorCrossingHumanCalls::FUN_004843a0(void *area)
{
    if (area &&
        *(float *)((char *)((RHUnkSightPlane *)((char *)area + 0xa8))->FUN_005df990() + 8) <= g_unk0x00677ba8)
        return true;
    return false;
}
