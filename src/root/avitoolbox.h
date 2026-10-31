#ifndef AVITOOLBOX_H
#define AVITOOLBOX_H

#include "SB.h"
#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

class RHUnkFXDraw
{
public:
    void FUN_005e5260();
    char m_00[0x10c];
    unsigned short m_10c; // +0x10c, WORD
};

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
class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;
extern unsigned char g_unk0x006a6d27;
unsigned long FUN_005f0ce0();
bool FUN_005f1150(ToolboxMouseState &, unsigned char *);
bool FUN_005e17a0(unsigned char *);
void FUN_005e1380();
void FUN_005e1400();
bool FUN_00401130(const char *);

#endif
