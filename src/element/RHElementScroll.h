#ifndef RHELEMENTSCROLL_H
#define RHELEMENTSCROLL_H

#include "RHElementBonus.h"
#include "Decomp.h"
#include <string>

// SIZE 0x100
class RHElementObject
{
public:
    virtual bool Serialize(SBFile &file); // vtable+0x00
    undefined m_pad4[0x0e]; // 0x04
    undefined m_12; // 0x12
    undefined m_pad13[0x3d]; // 0x13
    RHBonusInfo *m_50; // 0x50
    undefined m_pad54[0xac]; // 0x54
};

#include "RHUnkSectorScript.h"

// SIZE 0x60
class RHScrollScript
{
public:
    bool FUN_006348f0(SBFile &file);
    undefined m_pad0[0x58]; // 0x00
    undefined m_58; // 0x58
    undefined m_pad59[7]; // 0x59
};

class RHUnk004ba7a0
{
public:
    void Set(int status);
    void FUN_004ba7e0();
};

class RHUnk00404860
{
public:
    void FUN_00404780();
    int FUN_00404860(unsigned long value);
    void FUN_00404960(int value);
    void *m_0;
};

class RHUnk00462730
{
public:
    void FUN_00462730(void *, int);
};

#include "RHUnk004d8460Calls.h"

// SIZE 0x170
class RHElementScroll : public RHElementObject
{
public:
    void InitializeFromMissionStream(SBFile &file);
    bool FUN_004b9f40();
    void FUN_004b9fa0();
    bool FUN_004ba470(void *first, void *second, void *third);
    bool IsRevealable() const;
    bool FUN_004ba4e0(unsigned long value);
    int FUN_004ba550();
    int FUN_004ba580(unsigned long first, unsigned long second, unsigned long third, unsigned long fourth) const;
    static void ResetScrollExecutingScript();
    void *FUN_004ba5d0();
    virtual bool Serialize(SBFile &file); // vtable+0x00
    static void SetScrollExecutingScript(RHElementScroll *scroll);
    void FUN_004ba400();
    void Emit(SBFile &file);
    RHBonusInfo *Info() { return *(RHBonusInfo **)((char *)this + 0x50); } // +0x50
    RHBonusGlobalView *Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); } // +0x64

    RHScrollScript m_100; // 0x100
    RHUnkSectorScript *m_160; // 0x160
    int m_164; // 0x164
    undefined4 m_168; // 0x168
    undefined m_16c[3]; // 0x16c
    undefined m_16f; // 0x16f
};

void RHSerializeName(SBFile &file, const char *name);
#include "RHScrollObjectCalls.h"
#include "RHEngineWidenedCalls.h"
bool FUN_005e0c90(SBFile &file, std::string &value);
extern char g_unk0x6c0691;
extern RHElementScroll *g_scrollExecutingScript;
extern undefined g_unk0x006c0e48[];

#endif
