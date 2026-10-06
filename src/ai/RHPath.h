#ifndef RHPATH_H
#define RHPATH_H

#include "RHSector.h"

class RHWaypoint;

struct RHPathArray
{
    int m_grow; // +0x00
    RHWaypoint **m_first; // +0x04
    RHWaypoint **m_last; // +0x08
    RHWaypoint **m_end; // +0x0c

    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    RHWaypoint **begin() { return m_first; }
    RHWaypoint *&operator[](unsigned index) { return *(begin() + index); }
};

struct RHPathHistory
{
    int m_0; // +0x00
    int m_4; // +0x04
    void *m_8; // +0x08
    int m_c; // +0x0c
    char m_10; // +0x10
    char m_pad11;
    unsigned short m_12; // +0x12
};

struct RHPathHistoryNode
{
    RHPathHistoryNode *m_next; // +0x00
    RHPathHistoryNode *m_prev; // +0x04
    RHPathHistory m_data; // +0x08
};

struct RHTitbitNode;
class RHTitbitList
{
public:
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last);
    void At(int index);
};

class RHPathHistoryIter
{
public:
    RHPathHistoryNode *m_p;
    RHPathHistoryIter() {}
    RHPathHistoryIter(RHPathHistoryNode *p) : m_p(p) {}
};

void RHPathUnk0048f180(RHPathHistory *dst, const RHPathHistory *src);

class RHPathHistoryList
{
public:
    int m_0; // +0x00
    RHPathHistoryNode *m_head; // +0x04
    int m_count; // +0x08
    RHPathHistoryNode *m_cur; // +0x0c
    char m_valid; // +0x10
    char m_pad11[3];
    int m_index; // +0x14

    RHPathHistoryNode *Unk00551de0(RHPathHistoryNode *next, RHPathHistoryNode *prev);
    RHPathHistoryIter begin() { return RHPathHistoryIter(m_head->m_next); }
    RHPathHistoryIter end() { return RHPathHistoryIter(m_head); }
    RHPathHistoryIter insert(RHPathHistoryIter pos, const RHPathHistory &value)
    {
        RHPathHistoryNode *node = pos.m_p;
        node->m_prev = Unk00551de0(node, node->m_prev);
        node = node->m_prev;
        node->m_prev->m_next = node;
        RHPathUnk0048f180(&node->m_data, &value);
        ++m_count;
        return RHPathHistoryIter(node);
    }
    RHPathHistoryIter erase(RHPathHistoryIter first, RHPathHistoryIter last)
    {
        RHPathHistoryIter result;
        ((RHTitbitList *)this)->Clear(&result, (RHTitbitNode *)first.m_p, (RHTitbitNode *)last.m_p);
        return result;
    }
    void clear()
    {
        erase(begin(), end());
        m_valid = 1;
    }
    RHPathHistory &operator[](int index)
    {
        ((RHTitbitList *)this)->At(index);
        return m_cur->m_data;
    }
};

class RHPath
{
public:
    bool TestIfPathIsFine(RHElementActor *actor);
    bool SerializeStatus(SBFile &file);
    void Emit(SBFile &file, RHElementActor *actor);

    char m_0; // +0x00
    char m_1; // +0x01
    char m_2; // +0x02
    char m_pad3;
    RHPathArray *m_4; // +0x04
    unsigned short m_8; // +0x08
    char m_pada[2];
    RHPathHistoryList m_c; // +0x0c
};

class RHUnkWaypointRef
{
public:
    RHWaypoint *m_0; // +0x00
    void Unk00408660();
};

class RHWaypoint
{
public:
    unsigned int LoadDataFromFile(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[0x60];
    RHUnkWaypointRef m_60; // +0x60
    short m_64; // +0x64
    short m_66; // +0x66
    void *m_68; // +0x68
    unsigned short m_6c; // +0x6c
    char m_6e; // +0x6e
    char m_pad6f;
    unsigned short m_70; // +0x70
    char m_pad72[2];
    void *m_74; // +0x74
    char *m_78; // +0x78
};

struct RHUnkPathRegistry
{
    char m_pad0[8];
    RHPathArray **m_8; // +0x08
};
extern RHUnkPathRegistry *g_unk0x6c0b9c;

class RHUnkPathGeometry
{
public:
    bool Unk004f9260(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer);
    bool Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius);
    bool Unk004fbec0(SBFile &file, void *&value);
};

class RHUnkPathEngine
{
public:
    void Unk004dab90(RHPathArray *path, unsigned short index);
};
class RHEngine;
extern RHEngine *g_pEngine;

class RHUnkPathActorInfoBase
{
public:
    char m_pad0[0x88];
    int m_88; // +0x88
    void *Unk0055fa10(int value);
    void *Current() { return Unk0055fa10(*(volatile int *)&m_88); }
};
struct RHUnkPathActorInfo
{
    char m_pad0[4];
    RHUnkPathActorInfoBase m_4; // +0x04
};
struct RHUnkPathActorView
{
    char m_pad0[0x50];
    RHUnkPathActorInfo *m_50; // +0x50
    RHUnkPathActorInfoBase &Base() { return m_50->m_4; }
    void *UnkRadius() { return Base().Current(); }
};
struct RHUnkPathPointSet
{
    float m_x;
    float m_y;
    void Set(float x, float y) { m_x = x; m_y = y; }
};
struct RHUnkPathEngineView
{
    struct ActorPointer
    {
        RHUnkPathActorView *m_0;
        RHUnkPathActorView *&Get() { return m_0; }
    };
    char m_pad0[0x493c];
    ActorPointer *m_493c; // +0x493c
    RHUnkPathActorView &Actor()
    {
        ActorPointer *pointer = m_493c;
        RHUnkPathActorView *actor = pointer->Get();
        return *actor;
    }
};

#endif
