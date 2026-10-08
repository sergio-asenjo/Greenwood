#include "RHElementScroll.h"

bool RHElementScroll::FUN_004ba550() { return false; }
void RHUnk004ba7a0::FUN_004ba7e0()
{
    int status = *(int *)((char *)this + 0x164);
    *(unsigned short *)((char *)this + 0x8c) = status == 1 || status == 3 ? 1 : 0;
}
bool RHScrollScript::FUN_006348f0(SBFile &) { return true; }
