#ifndef RHELEMENTTARGET_H
#define RHELEMENTTARGET_H

#include "RHElementMobileBaseView.h"
#include "RHScriptCore.h"
#include "SBSimpleVirtualMachine.h"
#include "VMCoreCustom.h"
#include "RHElementScroll.h"
#include <vector>

class RHMobileUnk006100e0;

#ifndef RHUNK_TARGET_POINTS_DEFINED
#define RHUNK_TARGET_POINTS_DEFINED
class RHUnkTargetPoints
{
public:
    void FUN_00611100(const SBGeoPoint2D &point);
};
#endif

#include "RHTargetResourceCalls.h"

#include "RHCivilianSpriteView.h"

class RHUnk005df4f0 : public RHBonusTriple
{
public:
    RHUnk005df4f0(float x, float y, float z);
};

class RHUnkTargetScriptRef
{
public:
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
    void *m_0;
};

class RHTargetSequenceCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c(void *actor, bool active) = 0;
    undefined m_04[0x60];
    int m_64;
};

class __declspec(novtable) RHElementTarget : public RHMobileBase004a8130, public VMCoreCustom
{
public:
    RHElementTarget();
    virtual ~RHElementTarget();
    RHElementTarget *FUN_004bad60(char flags);
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    bool FUN_004bbf80();
    int FUN_004baf50(void *actor);
    int FUN_004baff0(void *actor);
    int FUN_004bb0a0(void *actor);
    bool FUN_004bb240(void *point, void *pc, int focus) const;
    bool FUN_004bb3a0(void *point, unsigned flags, RHElementActorPC *actor);
    void FUN_004bae60(RHTargetSequenceCalls *sequence, int (RHUnkTargetScriptRef::*callback)(int));
    bool FUN_004bc1d0(RHTargetSequenceCalls *sequence);
    void FUN_004bc3d0(int activator);
    void Emit(SBFile &file);
    RHUnkTargetSprite *&Info() { return *(RHUnkTargetSprite **)((char *)this + 0x50); }
    RHUnkFXDraw *&Draw() { return *(RHUnkFXDraw **)((char *)this + 0x60); }
    RHBonusGlobalView *&Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); }
    VMCore *m_15c;
    int m_160;
    int m_164;
    unsigned m_168;
    std::vector<RHMobileUnk006100e0 *> m_16c;
    char m_17c[0x10];
};

#define RHElementTarget_m_a8 (*(int *)((char *)this + 0xa8))
#define RHElementTarget_m_d4 (*(RHUnkTargetPoints *)((char *)this + 0xd4))
#define RHElementTarget_m_f8 (*(float *)((char *)this + 0xf8))
#define RHElementTarget_m_fc (*(RHUnkSectorScript *)((char *)this + 0xfc))
#define RHElementTarget_m_154 (*(char *)((char *)this + 0x154))
#define RHElementTarget_m_160 (*(int *)((char *)this + 0x160))
#define RHElementTarget_m_164 (*(int *)((char *)this + 0x164))
#define RHElementTarget_m_15c (*(RHUnkSectorScript **)((char *)this + 0x15c))
#define RHElementTarget_m_168 (*(unsigned *)((char *)this + 0x168))

#endif
