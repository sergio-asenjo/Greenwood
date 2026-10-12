#include "SBNullstr.h"
#include "RHElementScroll.h"

void RHUnk004ba7a0::FUN_004ba7e0()
{
    int status = *(int *)((char *)this + 0x164);
    *(unsigned short *)((char *)this + 0x8c) = status == 1 || status == 3 ? 1 : 0;
}
int __cdecl RHUnk00404860::FUN_00404860(unsigned long) { return 0; }
void RHUnk004a7150::FUN_004a7150(int, int, int) {}
void RHUnk00462730::FUN_00462730(void *, int) {}
void RHUnk004d8460::FUN_004d8460(void *, int, int) {}
bool __stdcall FUN_004b23c0(void *, void *, void *) { return false; }
bool __stdcall FUN_004b2b60(unsigned long, unsigned long, unsigned long, unsigned long) { return false; }
bool RHScrollScript::FUN_006348f0(SBFile &) { return true; }
