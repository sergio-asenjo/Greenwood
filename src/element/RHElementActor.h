#ifndef RHELEMENTACTOR_H
#define RHELEMENTACTOR_H

#include "RHElementActor_calls.h"

enum RHcommand { RHcommandUnk0 = 0 };

class RHElementActor : public RHElement, public RHActorScriptBase
{
public:
    virtual bool Serialize(SBFile &file);
    void ExecuteImmediately(RHSequenceElement *element);
    void Translate(RHSequenceElement *element, RHcommand command);
    void CheckForLineCrossing();
    void FUN_0046c8e0(int value);
    void FUN_0046bcb0(int value);
    const SBGeoPoint2D &FUN_004679b0() const;
    bool FUN_004679c0(SBGeoPoint2D point, int value);
    void FUN_00478c20(RHUnk00613e90 &point, bool value);
    void FUN_00478ae0(RHUnk00613e90 &point);
    void FUN_00462700(unsigned short value);
    void FUN_00462730(RHElementActor *actor, bool value);
    void FUN_00464630();
    RHBonusInfo *Info() const { return *(RHBonusInfo *const *)((char *)this + 0x50); }
    RHBonusInfoBase *Position() const { return (RHBonusInfoBase *)((char *)Info() + 4); }
    RHActorGridCalls *Grid() const { return *(RHActorGridCalls *const *)((char *)this + 0x64); }
    char Type() const { return (char)(*(const unsigned *)((char *)this + 4) & 15); }
    void InitializeScript(std::string &name);
    void Emit(SBFile &file, std::string &name);

    RHActorScriptContext m_108;
    int m_10c;
    char m_110;
    char m_111[3];
    int m_114;
    char m_118;
    char m_119;
    char m_11a[2];
    void *m_11c;
    void *m_120;
    int m_124;
    SBGeoPoint2D m_128;
    RHSequenceElement *m_130;
    RHOrder *m_134;
    RHSequenceElement *m_138;
    char m_13c;
    char m_13d[3];
    int m_140;
    int m_144;
    char m_148;
    char m_149;
    char m_14a[2];
    int m_14c;
    void *m_150;
    SBGeoPoint2D m_154;
    RHSequence *m_15c;
    int m_160;
    char m_164;
    char m_165;
    char m_166[2];
    void *m_168;
    short m_16c;
    char m_16e;
    char m_16f;
    void *m_170;
    SBGeoPoint2D m_174;
    RHActorPointList m_17c;
    char m_194[0x10];
    char m_1a4;
    char m_1a5;
    char m_1a6[2];
    RHActorString m_1a8;
};

#endif
