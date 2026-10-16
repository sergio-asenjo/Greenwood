#ifndef RHELEMENTACTOR_H
#define RHELEMENTACTOR_H

#include "RHElementActor_calls.h"
#include "Decomp.h"

enum RHcommand { RHcommandUnk0 = 0 };

// SIZE 0x14
struct RHHumanMapNode
{
    RHHumanMapNode *m_left; // 0x00
    RHHumanMapNode *m_parent; // 0x04
    RHHumanMapNode *m_right; // 0x08
    int m_key; // 0x0c
    undefined4 m_value; // 0x10
};

// SIZE 0x04
struct RHHumanMapIterator
{
    RHHumanMapNode *m_node; // 0x00
    RHHumanMapIterator(RHHumanMapNode *node) : m_node(node) {}
    RHHumanMapNode &operator*() const { return *m_node; }
    RHHumanMapNode *operator->() const { return &**this; }
    bool operator==(const RHHumanMapIterator &other) const { return m_node == other.m_node; }
    bool operator!=(const RHHumanMapIterator &other) const { return !(*this == other); }
};

// SIZE 0x10
class RHHumanMap
{
public:
    RHHumanMapNode *FUN_00588060(const int &key);
    RHHumanMapIterator end() const { return RHHumanMapIterator(m_head); }
    RHHumanMapIterator find(const int &key)
    {
        RHHumanMapIterator position = FUN_00588060(key);
        return position == end() || key < position->m_key ? end() : position;
    }
    undefined m_00[4]; // 0x00
    RHHumanMapNode *m_head; // 0x04
    undefined4 m_08; // 0x08
    undefined4 m_0c; // 0x0c
};

// SIZE 0x74
class RHActorSequencePointCalls
{
public:
    SBGeoPoint2D FUN_005871b0(int key);
    undefined m_00[0x64]; // 0x00
    RHHumanMap m_64; // 0x64
};

// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    undefined m_00[0x14]; // 0x00
};

// SIZE 0x0c
class RHUnk0053bf20
{
public:
    void *FUN_0053bf20() const;
    undefined m_0[8]; // 0x00
    void *m_8; // 0x08
};

#include "RHActorDirectionCalls.h"

// SIZE 0x0c
class RHUnk0060fbf0
{
public:
    RHUnk0060fbf0();
    RHUnk0060fbf0 &FUN_0060fca0(const RHUnk0060fbf0 &other);
    void FUN_0060fa20();
    void FUN_0060fa30(const RHUnk0060fbf0 &other);
    undefined m_0; // 0x00
    undefined m_1; // 0x01
    undefined2 m_2; // 0x02
    undefined2 m_4; // 0x04
    undefined2 m_6; // 0x06
    void *m_8; // 0x08
};

// SIZE 0x0c
class RHUnk004e52a0
{
public:
    void FUN_004e52a0();
    undefined m_0[4]; // 0x00
    RHScriptNode *m_head; // 0x04
    undefined4 m_count; // 0x08
};

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
    void FUN_00463240(unsigned first, unsigned second, unsigned third);
    void FUN_00463250(unsigned value);
    void FUN_00463260(unsigned first, unsigned second, unsigned third, unsigned fourth);
    virtual bool Serialize(SBFile &file); // vtable+0x00 (interim model)
    void ExecuteImmediately(RHSequenceElement *element);
    void Translate(RHSequenceElement *element, RHcommand command);
    void CheckForLineCrossing();
    void FUN_0046d5f0(void *door, bool reverse);
    void *FUN_0046d750(const SBGeoPoint2D &origin, unsigned short radius);
    bool FUN_0046d710();
    bool FUN_0046e270();
    unsigned short FUN_004626e0() const;
    void FUN_0046c8e0(int value);
    void FUN_0046bcb0(int value);
    const SBGeoPoint2D &FUN_004679b0() const;
    SBGeoVector2D FUN_00468ee0(int value) const;
    void FUN_00478c20(RHUnk00613e90 &point, bool value);
    void FUN_00478ae0(RHUnk00613e90 &point);
    void FUN_00462700(unsigned short value);
    void FUN_00462730(RHElementActor *actor, bool value);
    SBGeoPoint2D FUN_00462920();
    void FUN_00464630();
    int FUN_00467200() const;
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
    int m_160; // 0x160
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
    undefined m_194[0x10]; // 0x194
    char m_1a4; // 0x1a4
    char m_1a5; // 0x1a5
    undefined m_1a6[2]; // 0x1a6
    RHActorString m_1a8; // 0x1a8
};

#endif
