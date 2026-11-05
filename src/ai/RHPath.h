#ifndef RHPATH_H
#define RHPATH_H
#include "RHSectorActorList.h"

#include "RHSector.h"

#include "RHPathCore.h"

#include "RHWaypoint.h"

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

#include "RHPositionInterfaceCore.h"
struct RHUnkPathActorInfo
{
    char m_pad0[4];
    RHPositionInterface m_4; // +0x04
};
struct RHUnkPathActorView
{
    char m_pad0[0x50];
    RHUnkPathActorInfo *m_50; // +0x50
    RHPositionInterface &Base() { return m_50->m_4; }
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
#include "RHUnk005fc3b0.h"

#include "SBGeoBoundingBox2DCore.h"

#include "RHPathObstacleGrid.h"

class RHEngineReinforcementCalls
{
public:
    bool FUN_004f6c20(const SBGeoPoint2D &a, SBGeoPoint2D &b, unsigned short layer, const SBGeoPoint2D &point);
};

#include "RHMalignityQueryList.h"

class RHMalignityGridCalls
{
public:
    void FUN_004ed070(RHMalignityQueryList &list, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned mask);
};

// SIZE 0x10
class RHMalignitySegment
{
public:
    RHMalignitySegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMalignitySegment();
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
