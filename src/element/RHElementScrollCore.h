#ifndef RHELEMENTSCROLLCORE_H
#define RHELEMENTSCROLLCORE_H

#include "Decomp.h"
#include "RHElementObject.h"
#include "VMCoreCustom.h"

class SBFile;
class SBGeoBoundingBox2D;
class RHBonusInfo;
class RHUnkSectorScript;
struct RHBonusGlobalView;

class RHUnk004ba7a0
{
public:
    void Set(int status);
    void FUN_004ba7e0();
};

class RHUnk00404860
{
public:
    RHUnk00404860() : m_0(0) {}
    void FUN_00404780();
    int FUN_00404860(unsigned long value);
    void FUN_00404960(int value);
    void *m_0;
};

// VTABLE: GAME 0x00678898
// VTABLE: GAME 0x00678894 SBSimpleVirtualMachine
// VTABLE: GAME 0x00678890 RHScript
class RHElementScroll : public RHElementObject, public RHUnk00404860, public VMCoreCustom
{
public:
    RHElementScroll();
    virtual ~RHElementScroll();
    void InitializeFromMissionStream(SBFile &file);
    char FUN_004b9f40();
    void FUN_004b9fa0();
    virtual bool FUN_004b23c0(const void *first, void *second, int third);
    bool IsRevealable() const;
    bool FUN_004ba4e0(unsigned long value);
    int FUN_004ba550();
    virtual void *Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags);
    static void ResetScrollExecutingScript();
    RHElement *FUN_004ba5d0();
    virtual bool Serialize(SBFile &file);
    virtual unsigned V68();
    static void SetScrollExecutingScript(RHElementScroll *scroll);
    void FUN_004ba400();
    void Emit(SBFile &file);
    RHBonusInfo *Info() { return *(RHBonusInfo **)((char *)this + 0x50); }
    RHBonusGlobalView *Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); }

    int m_164;
    undefined4 m_168;
    undefined m_16c[3];
    undefined m_16f;
};

#endif
