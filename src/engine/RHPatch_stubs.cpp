#include "SBNullstr.h"
#include "RHPatch.h"

void RHPatch::FUN_00550070(bool) {}
void RHPatch::FUN_00550150() {}

// FUNCTION: GAME 0x0051b660
void RHPatchDoorCalls::FUN_0051b660()
{
    char *self = (char *)this;
    char first0 = self[0x8c];
    char first3 = self[0x8f];
    char first1 = self[0x8d];
    char first2 = self[0x8e];
    self[0x8c] = self[0x90];
    self[0x8f] = self[0x93];
    self[0x8d] = self[0x91];
    self[0x8e] = self[0x92];
    self[0x90] = first0;
    self[0x93] = first3;
    self[0x91] = first1;
    self[0x92] = first2;
}
