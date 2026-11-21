#ifndef RHELEMENTACTOR_H
#define RHELEMENTACTOR_H

#include "RHActorElementBase.h"
#include "RHActorPointList.h"
#include "RHActorString.h"
#include "RHActorScriptContext.h"
#include "RHUnkSectorScript.h"
#include "Decomp.h"

#include "RHActorCommand.h"
#include "RHScriptCore.h"
#include "SBSimpleVirtualMachineCore.h"

class RHSequenceElement;
class RHSequence;
class RHOrder;
class RHUnk00613e90;
class RHActorTranslationSequenceCalls;
class RHBonusInfo;
class RHBonusInfoBase;
class RHActorGridCalls;
class RHUnk00588530;

class RHActorScriptBase : public SBSimpleVirtualMachine, public RHScript
{
};

#include "RHSequencePropertyPointCalls.h"

// SIZE 0x14
#include "RHMobileUnk00607da0.h"

// SIZE 0x0c
#include "RHUnk0053bf20.h"

#include "RHActorDirectionCalls.h"

#include "SBGeoIntersection2D.h"

// SIZE 0x0c
#include "RHUnk004e52a0.h"

// SIZE 0x58c
class RHUnk004679c0
{
public:
    bool FUN_004679c0(SBGeoPoint2D point, unsigned short value);
    undefined m_0[0x50]; // 0x00
    char *m_info; // 0x50
    undefined m_54[0x580 - 0x54]; // 0x54
    undefined2 m_580; // 0x580
    undefined2 m_582; // 0x582
    SBGeoPoint2D m_584; // 0x584
};

// SIZE 0x1b8
class RHElementActor : public RHElement, public RHActorScriptBase
{
public:
    char FUN_00463200() const;
    SBGeoVector2D FUN_00463210();
    void FUN_00463240(unsigned first, unsigned second, unsigned third);
    void FUN_00463250(unsigned value);
    void FUN_00463260(unsigned first, unsigned second, unsigned third, unsigned fourth);
    virtual ~RHElementActor();
    int FUN_00463d90(unsigned value) const;
    virtual bool Serialize(SBFile &file);
    void ExecuteImmediately(RHSequenceElement *element);
    void Translate(RHSequenceElement *element, RHcommand command);
    void CheckForLineCrossing();
    void FUN_0046d5f0(void *door, bool reverse);
    void *FUN_0046d750(const SBGeoPoint2D &origin, unsigned short radius);
    bool FUN_0046d710();
    bool FUN_0046e270();
    void FUN_0046e7c0(unsigned short layer, void *sector);
    int FUN_0046e960();
    void FUN_0046e980(bool first, bool second);
    void FUN_0046ea20();
    unsigned short FUN_004626e0() const;
    void FUN_0046c8e0(int value);
    void FUN_0046bcb0(int value);
    const SBGeoPoint2D &FUN_004679b0() const;
    SBGeoVector2D FUN_00468ee0(int value) const;
    SBGeoVector2D FUN_004135b0();
    void FUN_00469300(RHUnk00588530 *sequence, bool reverse);
    void FUN_00469770(RHUnk00588530 *sequence, bool first, bool reverse);
    void FUN_00478c20(RHUnk00613e90 &point, int posture);
    void FUN_00478960(RHUnk00613e90 &point);
    void FUN_00478ae0(RHUnk00613e90 &point);
    void FUN_00462700(unsigned short value);
    int FUN_00462a30(RHElementActor *other);
    bool FUN_004640c0();
    float FUN_00464150();
    bool FUN_00464230();
    void FUN_004645f0();
    void FUN_00468f40(void *value);
    void FUN_0046a900(RHActorTranslationSequenceCalls *sequence, bool first, bool reverse);
    int FUN_0046ad00(void *first, void *second);
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    bool FUN_0046b210(RHSequenceElement *element);
    bool FUN_0046b2b0(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    bool FUN_0046b4b0(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    bool FUN_0046b760(unsigned flags, void *sequence);
    void FUN_0046bb80();
    void FUN_0046bab0();
    void FUN_0046bbf0();
    void FUN_0046bd40(RHSequenceElement *element);
    void FUN_0046c6b0(int style, const SBGeoPoint2D &destination);
    int FUN_00467200() const;
    bool FUN_00467210();
    void *FUN_00467220() const;
    RHBonusInfo *Info() const { return *(RHBonusInfo *const *)((char *)this + 0x50); }
    RHBonusInfoBase *Position() const { return (RHBonusInfoBase *)((char *)Info() + 4); }
    RHActorGridCalls *Grid() const { return *(RHActorGridCalls *const *)((char *)this + 0x64); }
    char Type() const { return (char)(*(const unsigned *)((char *)this + 4) & 15); }
    void InitializeScript(std::string &name);
    void Emit(SBFile &file, std::string &name);

    RHActorScriptContext m_108; // 0x108
    int m_10c; // 0x10c
    char m_110; // 0x110
    undefined m_111[3]; // 0x111
    int m_114; // 0x114
    char m_118; // 0x118
    char m_119; // 0x119
    undefined m_11a[2]; // 0x11a
    void *m_11c; // 0x11c
    void *m_120; // 0x120
    int m_124; // 0x124
    SBGeoPoint2D m_128; // 0x128
    RHSequenceElement *m_130; // 0x130
    RHOrder *m_134; // 0x134
    RHSequenceElement *m_138; // 0x138
    char m_13c; // 0x13c
    undefined m_13d[3]; // 0x13d
    int m_140; // 0x140
    int m_144; // 0x144
    char m_148; // 0x148
    char m_149; // 0x149
    undefined m_14a[2]; // 0x14a
    int m_14c; // 0x14c
    void *m_150; // 0x150
    SBGeoPoint2D m_154; // 0x154
    RHSequence *m_15c; // 0x15c
    float m_160; // 0x160
    char m_164; // 0x164
    char m_165; // 0x165
    undefined m_166[2]; // 0x166
    void *m_168; // 0x168
    short m_16c; // 0x16c
    char m_16e; // 0x16e
    char m_16f; // 0x16f
    void *m_170; // 0x170
    SBGeoPoint2D m_174; // 0x174
    RHActorPointList m_17c; // 0x17c
    undefined m_194[8]; // 0x194
    SBGeoPoint2D m_19c; // 0x19c
    char m_1a4; // 0x1a4
    char m_1a5; // 0x1a5
    undefined m_1a6[2]; // 0x1a6
    RHActorString m_1a8; // 0x1a8
};

#endif
