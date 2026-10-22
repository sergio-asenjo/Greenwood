#ifndef AVITOOLBOX_H
#define AVITOOLBOX_H

#include "SB.h"

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    char m_00[6];
    unsigned short m_06; // +0x06, WORD
    unsigned long m_08; // +0x08, DWORD
    char m_0c[4];
    void *m_10; // +0x10, pointer; object size 0x18
    char m_14[4];
};

class RHUnkFXDraw
{
public:
    void FUN_005e5260();
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
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
