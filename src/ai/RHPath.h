#ifndef RHPATH_H
#define RHPATH_H

#include "RHSector.h"

class RHWaypoint;

// SIZE 0x10
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

// SIZE 0x14
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

// SIZE 0x1c
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

// SIZE 0x18
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

// SIZE 0x24
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

// SIZE 0x04
class RHElementMobile;

class RHUnkWaypointRef
{
public:
    RHWaypoint *m_0; // +0x00
    int Unk00408660();
    int Unk00408750(RHElementMobile *mobile);
};

// SIZE 0x7c
class RHWaypoint
{
public:
    unsigned int LoadDataFromFile(SBFile &file);
    void Emit(SBFile &file);

    undefined m_pad0[0x60]; // 0x00
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

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &point);
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    void FUN_00607e30(const class RHMalignitySegment &segment);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &vector) const;
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    undefined m_10; // 0x10
};

class RHPathObstacleGrid
{
public:
    bool FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short layer);
};

class RHEngineReinforcementCalls
{
public:
    bool FUN_004f6c20(const SBGeoPoint2D &a, SBGeoPoint2D &b, unsigned short layer, const SBGeoPoint2D &point);
};

class RHMalignityGridCalls
{
public:
    void FUN_004ed070(class RHMalignityQueryList &list, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned mask);
};

// SIZE 0x10
class RHMalignitySegment
{
public:
    RHMalignitySegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMalignitySegment();
    bool FUN_0060a990(const RHMalignitySegment &other);
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
};

class RHMalignityArrayCalls
{
public:
    void FUN_0059fba0(const unsigned &value);
    void FUN_004e60a0(void *position, unsigned count, const unsigned &value);
    void FUN_004e62b0(void *position, unsigned count, const RHMalignitySegment &value);
};

// SIZE 0x50
class RHMalignityRectangle
{
public:
    RHMalignityRectangle();
    ~RHMalignityRectangle();
    undefined m_00[0x50]; // 0x00
};

// SIZE 0x0c
struct RHPathHelperNode
{
    RHPathHelperNode *m_next; // 0x00
    RHPathHelperNode *m_prev; // 0x04
    void *m_data; // 0x08
};

// SIZE 0x18
class RHPathHelperList
{
public:
    RHPathHelperList(const char &allocator);
    void FUN_005c8e40(unsigned index) { ((RHTitbitList *)this)->At(index); }
    undefined4 m_0; // 0x00
    RHPathHelperNode *m_head; // 0x04
    int m_count; // 0x08
    RHPathHelperNode *m_cur; // 0x0c
    undefined m_valid; // 0x10
    undefined m_pad11[3]; // 0x11
    int m_index; // 0x14
};

// SIZE 0x24
class RHMalignityQueryList : public RHPathHelperList
{
public:
    RHMalignityQueryList();
    ~RHMalignityQueryList() { FUN_004e6c10(); FUN_004e52a0(); }
    void FUN_004e6c10();
    void FUN_004e52a0();
    undefined m_18[0x0c]; // 0x18
};

// SIZE 0x50
class RHUnk004dab90Rectangle : public RHMalignityRectangle
{
public:
    RHUnk004dab90Rectangle()
    {
        unsigned value = 0;
        RHMalignityArrayCalls &indices = *(RHMalignityArrayCalls *)(m_00 + 0x2c);
        indices.FUN_0059fba0(value);
        m_00[0x40] = 1;
    }
    ~RHUnk004dab90Rectangle();
};

// SIZE 0x24
class RHUnk004f9260List : public RHPathHelperList
{
public:
    RHUnk004f9260List(const char &allocator) : RHPathHelperList(allocator) { m_valid = 1; }
    ~RHUnk004f9260List()
    {
        Clear();
        Clear();
        operator delete(m_head);
    }
    void Clear()
    {
        RHPathHelperNode *node = m_head->m_next;
        while (node != m_head)
        {
            RHPathHelperNode *removed = node;
            node = node->m_next;
            removed->m_prev->m_next = removed->m_next;
            removed->m_next->m_prev = removed->m_prev;
            operator delete(removed);
            --m_count;
        }
    }
    undefined m_18[0x0c]; // 0x18
};

template <class T>
inline T &RHPathField(void *object, unsigned offset)
{
    return *(T *)((undefined *)object + offset);
}

#endif
