#ifndef RHSECTOR_H
#define RHSECTOR_H

#include "SB.h"
#include "Decomp.h"
#include <string.h>
#include <vector>
#include <string>

void RHSerializeName(SBFile &file, const char *name);
class RHMissionArrayStorage;
class SBGeoBoundingBox2D;

// SIZE 0x58
class RHSector
{
public:
    RHSector();
    virtual void UnkV0(); // vtable+0x00
    int Unk0057cd60(SBFile &file, bool mode);
    void FUN_0057d390(void *draw, unsigned long surface, const SBGeoBoundingBox2D &box, float scale, unsigned short layer);
    undefined m_pad4[0x2c]; // 0x04
    int m_30; // 0x30
    undefined m_pad34[0x24]; // 0x34
};

template <class T>
class RHSectorArray : public std::vector<T>
{
public:
    char m_pad10[4];
    char m_dirty; // [0x14]
    char m_pad15[3];
    void Resize(unsigned int count, const T &value = T())
    {
        if (size() < count)
            insert(end(), count - size(), value);
        else if (count < size())
            ((RHMissionArrayStorage *)this)->FUN_004609a0(begin() + count, end());
        m_dirty = 1;
    }
};

class RHUnk00522540;

// SIZE 0x84
class RHSectorArchery : public RHSector
{
public:
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    RHSectorArray<RHUnk00522540 *> m_58; // [0x58]
    char m_pad70[8];
    void *m_78; // [0x78]
    unsigned short m_7c; // [0x7c]
    unsigned short m_7e; // [0x7e]
    unsigned short m_80; // [0x80]
    unsigned short m_82; // 0x82
};

struct RHUnkSectorGlobal
{
    char m_pad0[0x4064];
    void **m_4064; // [0x4064]
    char m_pad4068[0x11c];
    void *m_4184; // [0x4184]
};

extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
};

// VTABLE: GAME 0x00679140
// SIZE 0x1c
class RHUnk00522540
{
public:
    RHUnk00522540();
    virtual ~RHUnk00522540(); // vtable+0x00
    void Unk005225a0(SBFile &file);
    bool FUN_00522680(SBFile &file);
    SBGeoPoint2D m_4; // 0x04
    undefined2 m_c; // 0x0c
    undefined2 m_e; // 0x0e
    void *m_10; // 0x10
    undefined m_14; // 0x14
    undefined m_15; // 0x15
    undefined2 m_16; // 0x16
    void *m_18; // 0x18
};

// SIZE 0x2c
class RHUnkSectorPoints
{
public:
    unsigned int Unk0060ce80();
    SBGeoPoint2D &Unk0060cef0(unsigned int index);
    void Unk0060ced0(const SBGeoPoint2D &point, unsigned int index);
    SBGeoPoint2D &FUN_006112c0(unsigned int index);
    void FUN_006112a0(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060c2e0();
    undefined m_pad0[0x28]; // 0x00
    undefined m_28; // 0x28
    undefined m_29; // 0x29
    undefined m_pad2a[2]; // 0x2a
};

class RHUnkSectorScript
{
public:
    bool Unk00639a30(const std::string &name);
};

extern float g_unk0x679cc4;
extern char g_unk0x6c0691;

struct RHUnkSectorPosition
{
    char m_pad0[0x24];
    float m_24; // [0x24]
    float m_28; // [0x28]
};

enum RHUnkSectorActorType
{
    RHUnkSectorType0,
    RHUnkSectorType12 = 12
};

class RHElementActor
{
public:
    char m_pad0[4];
    unsigned int m_4; // [0x04]
    char m_pad8[0x48];
    RHUnkSectorPosition *m_50; // [0x50]
    char m_pad54[0x578];
    RHElementActor *m_5cc; // [0x5cc]
    char m_pad5d0[0x20];
    int m_5f0; // [0x5f0]

    RHUnkSectorActorType UnkType() const { return (RHUnkSectorActorType)(m_4 & 0xf); }
};

struct RHSectorActorNode
{
    RHSectorActorNode *m_next;
    RHSectorActorNode *m_prev;
    RHElementActor *m_data;
};

struct RHSectorActorAccess
{
    static RHSectorActorNode *&Next(RHSectorActorNode *p) { return p->m_next; }
    static RHElementActor *&Value(RHSectorActorNode *p) { return p->m_data; }
};

class RHSectorActorConstIter
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorConstIter(RHSectorActorNode *p) : m_p(p) {}
};

class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter(RHSectorActorNode *p) : RHSectorActorConstIter(p) {}
    RHSectorActorIter operator++(int);
    RHElementActor *&operator*() const { return RHSectorActorAccess::Value(m_p); }
};

class RHSectorActorList
{
public:
    char m_pad0[4];
    RHSectorActorNode *m_head; // [0x04]
    int m_count; // [0x08]
    RHSectorActorIter m_cur; // [0x0c]
    char m_valid; // [0x10]
    char m_pad11[3];
    int m_index; // [0x14]
    char m_searchValid; // [0x18]
    char m_pad19[3];
    int m_searchIndex; // [0x1c]
    RHElementActor *m_searchValue; // [0x20]

    int Unk004b8f80(RHElementActor *const &actor, bool mode);
    RHSectorActorIter insert(RHSectorActorIter pos, RHElementActor *const &actor);
    RHSectorActorIter erase(RHSectorActorIter pos);
    void Unk005c8e40(int index);

    int FindValue(RHElementActor *actor) { return Unk004b8f80(actor, true); }
    RHSectorActorIter begin() { return RHSectorActorIter(RHSectorActorAccess::Next(m_head)); }
    RHSectorActorIter Current() const { return m_cur; }
    RHElementActor *CurrentValue() const { return *m_cur; }

    int Find(RHElementActor *actor)
    {
        int count = m_count;
        m_searchValue = actor;
        m_searchValid = 1;
        m_cur = begin();
        int index = 0;
        for (; index < count; ++index, m_cur++)
        {
            if (CurrentValue() == m_searchValue)
                break;
        }
        if (index < count)
        {
            m_searchIndex = index;
            m_valid = 0;
            m_index = index;
        }
        else
        {
            m_valid = 1;
            m_searchIndex = -1;
        }
        return m_searchIndex;
    }
};

// SIZE 0x11c
class RHSectorBuilding
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    undefined m_pad0[0xf4]; // 0x00
    RHSectorActorList m_f4; // 0xf4
    undefined m_118; // 0x118
    undefined m_pad119[3]; // 0x119
};

class RHUnkSectorScriptRef
{
public:
    int Unk004089f0(RHElementActor *actor);
    int Unk00408af0(RHElementActor *actor);
    int Unk00408900();
    void *m_0; // 0x00
};

// SIZE 0xf8
class RHSectorScript
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void Emit(RHElementActor *actor);
    void Emit(SBFile &file);

    char m_pad0[0x36];
    unsigned short m_36; // [0x36]
    char m_pad38[0x80];
    char m_b8; // [0xb8]
    char m_padb9[7];
    char *m_c0; // [0xc0]
    RHUnkSectorScriptRef m_c4; // [0xc4]
    unsigned short m_c8; // [0xc8]
    char m_padca[2];
    RHSectorActorList m_cc; // [0xcc]
    char m_padf0[4];
    int m_f4; // [0xf4]
};

extern RHElementActor *g_unk0x6c100c;

class RHSectorGateCalls
{
public:
    void FUN_0057dea0(RHElementActor *actor, bool mode);
    bool FUN_0057deb0(RHElementActor *actor, bool mode);
    undefined m_00[0xb4];
    bool m_b4;
};

// SIZE 0x108
class RHSectorLift
{
public:
    int FUN_0057dcf0(int animation);
    int FUN_0057dd90(int animation);
    bool FUN_0057de30(RHElementActor *actor);
    bool FUN_0057dec0();
    bool FUN_0057def0();
    int Unk0057e060(SBFile &file, class RHUnkSectorLiftGrid *grid);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void Emit(SBFile &file, class RHUnkSectorLiftGrid *grid);

    char m_pad0[0xf0];
    int m_f0; // [0xf0]
    short m_f4; // [0xf4]
    short m_f6; // [0xf6]
    char m_f8; // [0xf8]
    char m_f9; // [0xf9]
    short m_fa; // [0xfa]
    int m_fc; // [0xfc]
    class RHUnk0051aa00 *m_100; // [0x100]
    class RHUnk0051aa00 *m_104; // [0x104]
};

class RHUnk005f5440
{
public:
    int Unk();
};

class RHUnk0057d490
{
public:
    void FUN_0057d760(void *gate, bool side);
    void Emit(void *gate, bool side);
};

// VTABLE: GAME 0x00679c24
// SIZE 0x5c
class RHUnk0057d440 : public RHSector
{
public:
    RHUnk0057d440();
    ~RHUnk0057d440();
    virtual void UnkV0(); // vtable+0x00
    virtual void UnkV4(SBFile &file, bool mode); // vtable+0x04
    virtual void UnkV8(); // vtable+0x08
    virtual void UnkVc(); // vtable+0x0c
    RHSectorLift *m_58; // [0x58]
};

class RHUnk0051aa00
{
public:
    RHUnk0051aa00();
    ~RHUnk0051aa00();
    void Unk0051b2a0(SBFile &file, bool mode);
    char m_pad0[0x1c];
    float m_1c; // [0x1c]
    char m_pad20[0x9c];
};

class RHSectorLiftArray : public std::vector<RHUnk0051aa00 *>
{
public:
    // [0x00] allocator; [0x04] _First; [0x08] _Last; [0x0c] _End.
    char m_pad10[4];
    char m_dirty; // [0x14]
    char m_pad15[3];
    void InsertLast(RHUnk0051aa00 *const &value)
    {
        insert(end(), 1, value);
        m_dirty = 1;
    }
};

class RHUnkSectorLiftGrid
{
public:
    char m_pad0[0x4080];
    RHSectorLiftArray m_4080; // [0x4080]
};

// SIZE 0x35
class RHSectorDoor
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[0x34];
    char m_34; // [0x34]
};

#endif
