#ifndef RHELEMENTSCROLLCORE_H
#define RHELEMENTSCROLLCORE_H

#include "Decomp.h"

class SBFile;
class SBGeoBoundingBox2D;
class RHBonusInfo;
class RHUnkSectorScript;
struct RHBonusGlobalView;

#ifndef RHELEMENTOBJECT_VIEW
#define RHELEMENTOBJECT_VIEW
class RHElementObject
{
public:
    virtual bool Serialize(SBFile &file);
    undefined m_pad4[0x0e];
    undefined m_12;
    undefined m_pad13[0x3d];
    RHBonusInfo *m_50;
    undefined m_pad54[0xac];
};
#endif

class RHScrollScript
{
public:
    undefined m_pad0[0x58];
    undefined m_58;
    undefined m_pad59[7];
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
    void *FUN_004ba580(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags);
    static void ResetScrollExecutingScript();
    void *FUN_004ba5d0();
    virtual bool Serialize(SBFile &file);
    static void SetScrollExecutingScript(RHElementScroll *scroll);
    void FUN_004ba400();
    void Emit(SBFile &file);
    RHBonusInfo *Info() { return *(RHBonusInfo **)((char *)this + 0x50); }
    RHBonusGlobalView *Global() { return *(RHBonusGlobalView **)((char *)this + 0x64); }

    RHScrollScript m_100;
    RHUnkSectorScript *m_160;
    int m_164;
    undefined4 m_168;
    undefined m_16c[3];
    undefined m_16f;
};

#endif
