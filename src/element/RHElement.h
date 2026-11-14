#ifndef RHELEMENT_H
#define RHELEMENT_H

#include "SB.h"
#include "RHSectorActorList.h"
#include "Decomp.h"
#include "RHElementCore.h"

#ifndef SBGEO_VECTOR2D_VIEW
#include "SBGeoVector2D.h"
#endif
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2D.h"
#endif

class RHUnkSectorPoints;

// SIZE 0xfc
class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa70(void *area);
    undefined m_00[4]; // 0x00
    undefined4 m_04; // 0x04
    undefined4 m_08; // 0x08
    undefined m_0c[0x14]; // 0x0c
    SBGeoPoint2D m_20; // 0x20
    undefined m_28[0xb2]; // 0x28
    undefined2 m_da; // 0xda
    undefined m_dc[0x0c]; // 0xdc
    void *m_e8; // 0xe8
    void *m_ec; // 0xec
    undefined m_f0[8]; // 0xf0
    void *m_f8; // 0xf8
};

#include "RHUnkSectorPoints.h"

#include "RHElementAreaShape.h"

class RHElementArea
{
public:
    undefined m_00[4]; // 0x00
    RHElementAreaShape m_04; // 0x04
    undefined m_2a[0x12]; // 0x2a
    SBGeoBoundingBox2D m_3c; // 0x3c
    undefined m_50[8]; // 0x50
    char *m_58; // 0x58
    undefined m_5c[4]; // 0x5c
    void *m_60; // 0x60
};

// SIZE 0x2c
class RHElevationLine
{
public:
    undefined m_00[4]; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
    float m_10; // 0x10
    undefined m_14[0xc]; // 0x14
    short m_20; // 0x20
    unsigned short m_22; // 0x22
    void *m_24; // 0x24
    void *m_28; // 0x28
};

// SIZE 0x0c
struct RHElementAreaNode
{
    RHElementAreaNode(RHElementAreaNode *nextNode, RHElementAreaNode *previousNode)
        : next(nextNode ? nextNode : this), prev(previousNode ? previousNode : this) {}
    RHElementAreaNode *next; // 0x00
    RHElementAreaNode *prev; // 0x04
    RHElementArea *data; // 0x08
};

// SIZE 0x04
struct RHElementAreaIter
{
    RHElementAreaNode *node; // 0x00
    RHElementAreaIter(RHElementAreaNode *value) : node(value) {}
};

// SIZE 0x0c
class RHElementAreaListBase
{
public:
    RHElementAreaListBase(const char &allocator);
    ~RHElementAreaListBase();
    void Clear();
    RHElementAreaIter begin();
    RHElementAreaIter erase(RHElementAreaIter first, RHElementAreaIter last);
    undefined m_00[4]; // 0x00
    RHElementAreaNode *m_04; // 0x04
    unsigned m_08; // 0x08
};

// SIZE 0x18
class RHElementAreaList : public RHElementAreaListBase
{
public:
    RHElementAreaList(const char &allocator) : RHElementAreaListBase(allocator) { m_10 = true; }
    ~RHElementAreaList()
    {
        erase(begin(), RHElementAreaIter(m_04));
    }
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    RHElementAreaNode *m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
};

#include "RHTransientPointerList.h"
typedef RHTransientPointerList<RHElementArea> RHElementAreaTransientList;

#include "RHElementGrid.h"

#endif
