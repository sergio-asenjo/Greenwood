#include "SBNullstr.h"
#include "RHFastFindGrid.h"
#include "RHArtificialIntelligenceCore.h"
#include "RHSectorObstacle.h"
#include "RHMobileUnk00607da0.h"
#include <stddef.h>

typedef std::vector<void *> RHFastFindPointerVector;

bool RHFastFindGrid::IsReachableImpact(const RHUnk00613e90 &, const RHUnk00613e90 &, RHUnk00613e90 &, void *&, int)
{
    return false;
}

// FUNCTION: GAME 0x0051e630
void *RHUnk0051e5e0::FUN_0051e630(unsigned flags)
{
    this->RHUnk0051e5e0::~RHUnk0051e5e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051e650
RHUnk0051e5e0::~RHUnk0051e5e0()
{
    *(unsigned long *)this = 0x006790c8;
    RHFastFindPointerVector *second = (RHFastFindPointerVector *)((char *)this + 0x78);
    second->clear();
    second->~RHFastFindPointerVector();
    RHFastFindPointerVector *lines = (RHFastFindPointerVector *)&m_lines;
    lines->clear();
    lines->~RHFastFindPointerVector();
    ((RHSector *)this)->RHSector::~RHSector();
}



// FUNCTION: GAME 0x0051f450
float RHFastFindLine::FUN_0051f450() { return First().m_x > Second().m_x ? First().m_x : Second().m_x; }
// FUNCTION: GAME 0x0051f470
float RHFastFindLine::FUN_0051f470() { return First().m_x > Second().m_x ? Second().m_x : First().m_x; }
// FUNCTION: GAME 0x0051f490
float RHFastFindLine::FUN_0051f490() { return First().m_y > Second().m_y ? Second().m_y : First().m_y; }
// FUNCTION: GAME 0x0051f4b0
float RHFastFindLine::FUN_0051f4b0() { return First().m_y > Second().m_y ? First().m_y : Second().m_y; }

DECOMP_SIZE_ASSERT(RHUnk0051a5e0, 0x88)
DECOMP_SIZE_ASSERT(RHUnk0051aa00, 0xbc)
DECOMP_SIZE_ASSERT(RHUnk0051b6e0, 0x90)
DECOMP_SIZE_ASSERT(RHUnk005209d0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk00520ae0, 0x40)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00520ae0, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00520ae0, m_id) == 0x3c)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindGrid, m_repulsivePoints) == 0x41b4)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindGrid, m_repulsiveLayers) == 0x41c4)

// FUNCTION: GAME 0x0060ad50
bool SBGeoSegment2D::FUN_0060ad50(const SBGeoBoundingBox2D &box) const
{
    return box.FUN_00608650(Line());
}


void RHFastFindSector::UnkSlot0() {}
void RHFastFindSector::UnkSlot4() {}
void RHFastFindSector::UnkSlot8() {}
void RHFastFindSector::UnkSlotc() {}
void RHFastFindSector::UnkSlot10(SBFile &, RHFastFindGrid *) {}

// FUNCTION: GAME 0x00520a90
void RHUnk00522470::FUN_00520a90(SBFile &file)
{
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    this->x = x;
    this->y = y;
}
RHUnk0051b6e0::~RHUnk0051b6e0() {}
// GLOBAL: GAME 0x006c1064
unsigned long g_unk0x006c1064;

DECOMP_SIZE_ASSERT(RHFastFindSightList<RHFastFindSightVertex>, 0x30)
DECOMP_SIZE_ASSERT(RHFastFindSightList<void *>, 0x24)
DECOMP_SIZE_ASSERT(RHFastFindSightList<RHFastFindSightVertex>::Node, 0x18)
DECOMP_SIZE_ASSERT(RHUnk0057d3a0, 0x5c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0057d3a0, m_58) == 0x58)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindSightList<RHFastFindSightVertex>, m_current) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindSightList<RHFastFindSightVertex>, m_dirty) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindSightList<RHFastFindSightVertex>, m_index) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindSightVertex, upper) == 0x08)
DECOMP_SIZE_ASSERT(RHUnk005a3450, 0x1a8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_box) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_bounds) == 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_otherBounds) == 0x38)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_vertices) == 0x4c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_polygon) == 0x7c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_firstPlane) == 0xa8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_secondPlane) == 0x100)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_materials) == 0x170)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_motionArea) == 0x194)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005a3450, m_active) == 0x1a6)

// FUNCTION: GAME 0x005a3450
RHUnk005a3450::RHUnk005a3450()
{
    m_158[0] = true;
    m_active = false;
    m_enabled = true;
    m_flags = 3;
    m_id = g_unk0x006c1064++;
    m_164 = 1.0f;
    m_160 = 1.0f;
}

// FUNCTION: GAME 0x005a3560
RHUnk005a3450::RHUnk005a3450(int type)
{
    m_158[0] = true;
    m_active = false;
    m_enabled = true;
    m_flags = type;
    m_id = g_unk0x006c1064++;
    m_164 = 1.0f;
    m_160 = 1.0f;
}

// STUB: GAME 0x005a3670
RHUnk005a3450::~RHUnk005a3450() {}
// STUB: GAME 0x005a5780
void *RHUnk005a3450::Unk005a5780()
{
    SBGeoPoint2D point;
    RHUnk0057d3a0 *sector = new RHUnk0057d3a0;
    sector->m_58 = this;
    ((RHMobileUnk00607da0 *)&sector->m_3c)->FUN_00607da0((const RHMobileUnk00607da0 &)m_otherBounds);
    unsigned count = m_vertices.m_count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHFastFindSightVertex vertex = m_vertices.At(index);
        point.m_x = vertex.x;
        point.m_y = vertex.y - vertex.upper;
        ((RHUnkSectorPoints *)((char *)sector + 4))->FUN_0060ceb0(point);
    }
    ((RHUnkSectorPoints *)((char *)sector + 4))->FUN_0060c2e0();
    return sector;
}
// FUNCTION: GAME 0x005223f0
void RHUnk005223f0::FUN_005223f0(SBFile &file)
{
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    *(float *)this = (float)x;
    *(float *)((char *)this + 4) = (float)y;
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
    file.Access((char *)this + 0xc, 2);
    file.Access((char *)this + 0x10, 2);
}
// FUNCTION: GAME 0x00418390
void FUN_00418390(RHUnk005223f0 *hole)
{
    for (short index = g_unk0x006c06f0.size() - 1; index >= 0; --index)
    {
        if (g_unk0x006c06f0[index]->FUN_00522070((const RHSeekPointDirectionView *)hole))
            return;
    }
    RHSeekPoint *point = new RHSeekPoint((const RHSeekPointDirectionView *)hole);
    point->m_3a = (unsigned short)g_unk0x006c06f0.size();
    g_unk0x006c06f0.InsertLast(point);
}
// FUNCTION: GAME 0x005209d0
RHUnk005209d0::RHUnk005209d0(int type)
{
    *(unsigned *)this = 0x678b58;
    m_0c = type;
    m_10 = 1;
}

// FUNCTION: GAME 0x00520a00
RHUnk005209d0::RHUnk005209d0(SBGeoPoint2D point, int type) : SBGeoPoint2D(point)
{
    *(unsigned *)this = 0x678b58;
    m_0c = type;
    m_10 = 1;
}

// FUNCTION: GAME 0x00520a70
RHUnk005209d0::~RHUnk005209d0()
{
    *(unsigned *)this = 0x678b58;
}
// FUNCTION: GAME 0x0051a5e0
RHUnk0051a5e0::RHUnk0051a5e0()
{
    m_kind = 0;
}
RHUnk0051aa00::~RHUnk0051aa00() {}

// FUNCTION: GAME 0x0051a680
bool RHUnk0051a5e0::FUN_0051abe0(bool, RHElementActor *, bool, bool, bool) { return false; }
// TEMPLATE: GAME 0x0057cd50 FOLDED
// ?Serialize@RHUnk0051a5e0@@UAE_NAAVSBFile@@@Z
bool RHUnk0051a5e0::Serialize(SBFile &) { return true; }

class RHScriptBatchCalls
{
public:
    bool Unk0049d560(int action);
};

// FUNCTION: GAME 0x0051b870
bool RHUnk0051b6e0::FUN_0051abe0(bool first, RHElementActor *actor, bool second, bool third, bool)
{
    if ((*(unsigned *)((char *)actor + 0x4) & 0xf) != 0xc ||
        !((RHScriptBatchCalls *)actor)->Unk0049d560(0x16))
        return false;
    if (first)
    {
        if (*(char *)(*(char **)((char *)this + 0x88) + 0x39))
            goto check;
    }
    else if (*(char *)(*(char **)((char *)this + 0x8c) + 0x39))
        goto check;
    return true;
check:
    if (second)
        return *(int *)(*(char **)((char *)actor + 0x50) + 0x8c) == 0x10;
    return third;
}
