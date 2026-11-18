#include "SBNullstr.h"
#include "RHSectorActorList.h"
#include "RHUnk00422c40.h"

// STUB: GAME 0x00422c40
void RHUnk00422c40::FUN_00422c40()
{
    RHSectorActorList *events = (RHSectorActorList *)((char *)this + 0x34c);
    unsigned short count = (unsigned short)*(unsigned *)((char *)this + 0x354);
    bool ready = false;
    for (unsigned short index = 0; index < count && !ready; ++index)
    {
        events->Unk005c8e40(index);
        ready = *(int *)(*(char **)((char *)this + 0x358) + 8) == 2;
    }
}
