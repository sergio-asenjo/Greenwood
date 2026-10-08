#include "RHPath.h"
#include "VMCore.h"

DECOMP_SIZE_ASSERT(RHPathArray, 0x10)
DECOMP_SIZE_ASSERT(RHPathHistory, 0x14)
DECOMP_SIZE_ASSERT(RHPathHistoryNode, 0x1c)
DECOMP_SIZE_ASSERT(RHPathHistoryList, 0x18)
DECOMP_SIZE_ASSERT(RHPath, 0x24)
DECOMP_SIZE_ASSERT(RHUnkWaypointRef, 0x04)
DECOMP_SIZE_ASSERT(RHWaypoint, 0x7c)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHMalignitySegment, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityRectangle, 0x50)
DECOMP_SIZE_ASSERT(RHPathHelperNode, 0x0c)
DECOMP_SIZE_ASSERT(RHPathHelperList, 0x18)
DECOMP_SIZE_ASSERT(RHMalignityQueryList, 0x24)
DECOMP_SIZE_ASSERT(RHUnk004dab90Rectangle, 0x50)
DECOMP_SIZE_ASSERT(RHUnk004f9260List, 0x24)

// Parked: string cleanup scheduling and annotated VM calls.
// deferred: 0x00408660, unannotated pending reccmp #534.
int RHUnkWaypointRef::Unk00408660()
{
    {
        std::string name("Initialize");
        ((VMCore *)m_0)->FUN_00639300(&name);
    }
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// Parked: frame layout, register allocation and coupled calls.
// deferred: 0x004dab90, unannotated pending reccmp #534.
void RHUnkPathEngine::Unk004dab90(RHPathArray *path, unsigned short index)
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    RHPathHelperList &list = RHPathField<RHPathHelperList>(this, 0x4c9c);
    unsigned count = list.m_count;
    for (unsigned short i = 0; i < (unsigned short)count; ++i)
    {
        list.FUN_005c8e40(i);
        if (RHPathField<RHPathArray *>(list.m_cur->m_data, 0x4c) == path)
        {
            list.FUN_005c8e40(i);
            RHPathField<unsigned short *>(list.m_cur->m_data, 0x30)[index] = 0xf000;
            return;
        }
    }
    RHWaypoint *waypoint = (*path)[0];
    ((RHUnkPathPointSet *)&previous)->Set(waypoint->m_64, waypoint->m_66);
    RHMalignityRectangle *rectangle = new RHUnk004dab90Rectangle;
    RHMalignityArrayCalls &indices = RHPathField<RHMalignityArrayCalls>(rectangle, 0x2c);
    RHPathField<RHPathArray *>(rectangle, 0x4c) = path;
    unsigned short size = path->size();
    if (size > 1)
    {
        unsigned marked = index + 1;
        for (unsigned i = 1, remaining = size - 1; remaining != 0; ++i, --remaining)
        {
            waypoint = (*path)[i];
            ((RHUnkPathPointSet *)&current)->Set(waypoint->m_64, waypoint->m_66);
            ((RHMalignityArrayCalls *)rectangle)->FUN_004e62b0(RHPathField<void *>(rectangle, 8), 1, RHMalignitySegment(previous, current));
            RHPathField<undefined>(rectangle, 0x14) = 1;
            unsigned flag = i == marked ? 0xf000 : 0;
            indices.FUN_004e60a0(RHPathField<void *>(&indices, 8), 1, flag);
            RHPathField<undefined>(&indices, 0x14) = 1;
            previous = current;
        }
    }
    RHPathHelperNode *head = list.m_head;
    RHPathHelperNode *prev = head->m_prev;
    RHPathHelperNode *node = (RHPathHelperNode *)operator new(0x0c);
    node->m_next = head ? head : node;
    node->m_prev = prev ? prev : node;
    head->m_prev = node;
    node->m_prev->m_next = node;
    if (&node->m_data)
        node->m_data = rectangle;
    ++RHPathField<int>(this, 0x4ca4);
    RHPathField<undefined>(this, 0x4cac) = 1;
}

// Parked: temporary cleanup scheduling and coupled calls.
// deferred: 0x004f9170, unannotated pending reccmp #534.
bool RHUnkPathGeometry::Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius)
{
    SBGeoBoundingBox2D *box = (SBGeoBoundingBox2D *)radius;
    bool blocked;
    {
        SBGeoVector2D vector(b);
        blocked = !((RHPathObstacleGrid *)this)->FUN_004f5750(box->FUN_006090d0(vector), layer);
    }
    if (blocked)
        return false;
    return ((RHEngineReinforcementCalls *)this)->FUN_004f6c20(a, (SBGeoPoint2D &)b, layer, SBGeoVector2D(box->m_8));
}

// Parked: container cleanup, frame layout and coupled calls.
// deferred: 0x004f9260, unannotated pending reccmp #534.
bool RHUnkPathGeometry::Unk004f9260(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer)
{
    RHMalignitySegment segment(SBGeoVector2D(0, 0), SBGeoVector2D(0, 0));
    SBGeoBoundingBox2D box;
    char allocator;
    RHUnk004f9260List lines(allocator);
    segment.m_0 = a;
    segment.m_8 = b;
    box.FUN_00607e30(segment);
    ((RHMalignityGridCalls *)this)->FUN_004ed070((RHMalignityQueryList &)lines, layer, box, 2);
    unsigned short count = lines.m_count;
    for (unsigned short i = 0; i < count; ++i)
    {
        lines.FUN_005c8e40(i);
        if (RHPathField<RHMalignitySegment>(lines.m_cur->m_data, 4).FUN_0060a990(segment))
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x00550690
bool RHPath::TestIfPathIsFine(RHElementActor *actor)
{
    SBGeoPoint2D current;
    SBGeoPoint2D previous;
    bool fine = true;
    RHWaypoint *last = (*m_4)[0];
    unsigned short count = m_4 == 0 ? 0 : m_4->size();
    for (unsigned short i = 1; i < count; ++i)
    {
        RHWaypoint *waypoint = (*m_4)[i];
        if (waypoint->m_6c == last->m_6c && waypoint->m_68 == last->m_68)
        {
            ((RHUnkPathPointSet *)&current)->Set(waypoint->m_64, waypoint->m_66);
            ((RHUnkPathPointSet *)&previous)->Set(last->m_64, last->m_66);
            if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9260(previous, current, waypoint->m_6c))
            {
                SBAssert(0,
                         // STRING: GAME 0x006b143c
                         "P:\\Robin Hood\\RHpath.cpp", 267,
                         // STRING: GAME 0x006b14f0
                         "Path intersects obstacle between waypoints (%u, %u) and (%u, %u).",
                         (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                         (unsigned short)current.m_x, (unsigned short)current.m_y);
                ((RHUnkPathEngine *)g_pEngine)->Unk004dab90(m_4, i - 1);
                fine = false;
            }
            else if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9170(previous, current, waypoint->m_6c,
                         ((RHUnkPathActorView *)actor)->UnkRadius()))
            {
                ((RHUnkPathEngine *)g_pEngine)->Unk004dab90(m_4, i - 1);
                if (actor->m_4 == 0x103 &&
                    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9170(previous, current, waypoint->m_6c,
                        ((RHUnkPathEngineView *)g_pEngine)->Actor().UnkRadius()))
                {
                    SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", 277,
                             // STRING: GAME 0x006b149c
                             "Path too near to obstacle (for a rider) between waypoints (%u, %u) and (%u, %u).",
                             (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                             (unsigned short)current.m_x, (unsigned short)current.m_y);
                }
                else
                {
                    SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", 281,
                             // STRING: GAME 0x006b1458
                             "Path too near to obstacle between waypoints (%u, %u) and (%u, %u).",
                             (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                             (unsigned short)current.m_x, (unsigned short)current.m_y);
                }
                fine = false;
            }
        }
        last = waypoint;
    }
    return fine;
}

#define RH_PATH_ACCESS(value, bytes, line) \
    if (file.Access(&(value), bytes) < 0) \
    { \
        SBString *err = file.GetError(); \
        const char *reason = err->m_chars ? err->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// FUNCTION: GAME 0x00550990
bool RHPath::SerializeStatus(SBFile &file)
{
    unsigned int count;
    unsigned short index;
    RHPathHistory value;
    // STRING: GAME 0x006b1534
    RHSerializeName(file, "RHPath::SerializeStatus");
    RH_PATH_ACCESS(m_0, 1, 319);
    RH_PATH_ACCESS(m_1, 1, 320);
    RH_PATH_ACCESS(m_2, 1, 321);
    if (file.m_bLoading)
    {
        RH_PATH_ACCESS(m_8, 2, 325);
        if (m_8 == 0xffff)
            m_4 = 0;
        else
            m_4 = g_unk0x6c0b9c->m_8[m_8];
        RH_PATH_ACCESS(count, 2, 337);
        RHPathHistoryList &list = m_c;
        list.clear();
        for (index = 0; index < (unsigned short)count; ++index)
        {
            RH_PATH_ACCESS(value.m_0, 4, 341);
            RH_PATH_ACCESS(value.m_4, 4, 342);
            ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, value.m_8);
            RH_PATH_ACCESS(value.m_c, 2, 344);
            RH_PATH_ACCESS(value.m_10, 1, 345);
            RH_PATH_ACCESS(value.m_12, 2, 346);
            list.insert(list.end(), value);
            list.m_valid = 1;
        }
    }
    else
    {
        index = m_4 == 0 ? 0xffff : m_8;
        RH_PATH_ACCESS(index, 2, 362);
        count = m_c.m_count;
        RH_PATH_ACCESS(count, 2, 366);
        for (index = 0; index < (unsigned short)count; ++index)
        {
            value = m_c[index];
            RH_PATH_ACCESS(value.m_0, 4, 371);
            RH_PATH_ACCESS(value.m_4, 4, 372);
            ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, value.m_8);
            RH_PATH_ACCESS(value.m_c, 2, 374);
            RH_PATH_ACCESS(value.m_10, 1, 375);
            RH_PATH_ACCESS(value.m_12, 2, 376);
        }
    }
    return true;
}

// FUNCTION: GAME 0x00551bb0
unsigned int RHWaypoint::LoadDataFromFile(SBFile &file)
{
    file.Access(&m_64, 2);
    file.Access(&m_66, 2);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_68);
    file.Access(&m_6c, 2);
    file.Access(&m_6e, 1);
    file.Access(&m_70, 2);
    unsigned int size = 11;
    if (m_70 > 0)
    {
        if (m_6e)
        {
            m_78 = new char[m_70 + 1];
            file.Access(m_78, m_70);
            m_78[m_70] = 0;
            size += m_70;
            if (g_unk0x6c0691)
            {
                if (!((RHUnkSectorScript *)this)->Unk00639a30(m_78))
                    SBAssert(1, "P:\\Robin Hood\\RHpath.cpp", 819,
                             // STRING: GAME 0x006b154c
                             "Structural error in RHD, a Waypoint has got a script reference that does not exist !");
                m_60.m_0 = this;
                m_60.Unk00408660();
            }
        }
        else
        {
            m_74 = new char[m_70];
            file.Access(m_74, m_70);
            size += m_70;
        }
    }
    return size;
}

void RHPath::Emit(SBFile &file, RHElementActor *actor)
{
    TestIfPathIsFine(actor);
    SerializeStatus(file);
}

void RHWaypoint::Emit(SBFile &file)
{
    LoadDataFromFile(file);
}
