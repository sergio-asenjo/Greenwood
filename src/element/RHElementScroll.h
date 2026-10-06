#ifndef RHELEMENTSCROLL_H
#define RHELEMENTSCROLL_H

#include "RHElementBonus.h"
#include <string>

class RHElementObject
{
public:
    virtual bool Serialize(SBFile &file);
    char m_pad4[0xfc];
};

class RHUnkSectorScript
{
public:
    bool Unk00639a30(const std::string &name);
};

class RHScrollScript
{
public:
    bool FUN_006348f0(SBFile &file);
    char m_pad0[0x58];
    char m_58;
    char m_pad59[7];
};

class RHUnk004ba7a0
{
public:
    void Set(int status);
};

class RHElementScroll : public RHElementObject
{
public:
    void InitializeFromMissionStream(SBFile &file);
    virtual bool Serialize(SBFile &file);
    static void SetScrollExecutingScript(RHElementScroll *scroll);
    void FUN_004ba400();
    void Emit(SBFile &file);
    RHBonusInfo *Info() { return *(RHBonusInfo **)((char *)this + 0x50); } // +0x50
    RHBonusGlobalView *Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); } // +0x64

    RHScrollScript m_100; // +0x100, flag +0x158
    RHUnkSectorScript *m_160; // +0x160
    int m_164; // +0x164
    int m_168; // +0x168
    char m_16c[3]; // +0x16c
    char m_16f; // +0x16f
};

void RHSerializeName(SBFile &file, const char *name);
void FUN_005e0c90(SBFile &file, std::string &value);
extern char g_unk0x6c0691;
extern RHElementScroll *g_scrollExecutingScript;

#endif
