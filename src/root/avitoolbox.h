#ifndef AVITOOLBOX_H
#define AVITOOLBOX_H

#include "SB.h"
#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

class RHArtificialIntelligenceSoundCalls;

#include "ToolboxMouseState.h"

struct RHUnkBink
{
    unsigned long m_00;
    unsigned long m_04;
    unsigned long m_08;
    unsigned long m_0c;
};

extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
extern SBDrawManager *g_unk0x6c11d0;
extern unsigned char g_unk0x006a6d27;
unsigned long FUN_005f0ce0();
bool FUN_005f1150(ToolboxMouseState &, unsigned char *);
bool FUN_005e17a0(unsigned char *);
void FUN_005e1380();
void FUN_005e1400();
bool FUN_00401130(const char *);

#endif
