#ifndef RHELEMENTTARGET_H
#define RHELEMENTTARGET_H

#include "RHElementFXCore.h"
#include "VMCoreCustom.h"
#include "RHEngineElementArray.h"

class RHMobileUnk006100e0;
class RHUnkTargetSprite;
class RHTargetSequenceCalls;
class RHElementActorPC;
class SBDrawManager;
class VMCore;
struct RHBonusGlobalView;

class RHUnkTargetScriptRef
{
public:
    RHUnkTargetScriptRef() : m_0(0) {}
    int FUN_004034e0();
    int FUN_004035d0(int activator);
    int FUN_004036d0(int activator);
    int FUN_004037d0(int activator);
    int FUN_004038d0(int activator);
    int FUN_004039d0(int activator);
    int FUN_00403ad0(int activator);
    int FUN_00403bd0(int activator);
    int FUN_00403cd0(int activator);
    int FUN_00403dd0(int activator);
    int FUN_00403ed0(int activator);
    VMCore *m_0;
};

// VTABLE: GAME 0x006789a4
// VTABLE: GAME 0x006789a0 SBSimpleVirtualMachine
// VTABLE: GAME 0x0067899c RHScript
class RHElementTarget : public RHElementFX, public RHUnkTargetScriptRef, public VMCoreCustom
{
public:
    RHElementTarget();
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    virtual char FUN_004b9f40();
    int FUN_004baf50(void *actor);
    int FUN_004baff0(void *actor);
    int FUN_004bb0a0(void *actor);
    RHUnk00613e90 GetCenter() const;
    virtual bool FUN_004b23c0(const void *point, void *pc, int focus);
    virtual void *FUN_004b29c0(void *actor);
    virtual bool FUN_004b26a0(const SBGeoPoint2D *point, unsigned short flags, RHElementActorPC *selectedPC);
    void FUN_004bae60(RHTargetSequenceCalls *sequence, int (RHUnkTargetScriptRef::*callback)(int));
    virtual char Instruct(RHSequenceElementCalls *sequence);
    void FUN_004bc3d0(int activator);
    void Emit(SBFile &file);
    RHUnkTargetSprite *&Info() { return *(RHUnkTargetSprite **)((char *)this + 0x50); }
    SBDrawManager *&Draw() { return *(SBDrawManager **)((char *)this + 0x60); }
    RHBonusGlobalView *&Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); }
    int m_160;
    int m_164;
    unsigned m_168;
    RHEngineElementArray<RHMobileUnk006100e0> m_16c;
};

#define RHElementTarget_m_a8 (*(int *)((char *)this + 0xa8))
#define RHElementTarget_m_f8 (*(float *)((char *)this + 0xf8))
#define RHElementTarget_m_fc (*(RHUnkSectorScript *)((char *)this + 0xfc))
#define RHElementTarget_m_154 (*(char *)((char *)this + 0x154))
#define RHElementTarget_m_160 (*(int *)((char *)this + 0x160))
#define RHElementTarget_m_164 (*(int *)((char *)this + 0x164))
#define RHElementTarget_m_15c (*(RHUnkSectorScript **)((char *)this + 0x15c))
#define RHElementTarget_m_168 (*(unsigned *)((char *)this + 0x168))

#endif
