#include "SBNullstr.h"
#include "RHFastFindGrid.h"
#include "SBFilePosition.h"
#include "RHUnk0051f0f0.h"
#include "RHSectorBuilding.h"
#include "RHElementGrid.h"
#include "RHPathQueryCalls.h"
#include "RHSectorActorIterator.h"

// TEMPLATE: GAME 0x00522780
// ?insert@?$vector@GV?$allocator@G@std@@@std@@QAEPAGPAGABG@Z
template class std::vector<unsigned short>;

// TEMPLATE: GAME 0x004ff210
// ?assign@?$vector@KV?$allocator@K@std@@@std@@QAEXPBK0@Z
template class std::vector<unsigned long>;

// TEMPLATE: GAME 0x004598e0 FOLDED
// ?copy@std@@YAPAKPBK0PAK@Z

// GLOBAL: GAME 0x006c06f0
RHFastFindTacticalArray g_unk0x006c06f0;
// GLOBAL: GAME 0x006c0718
RHFastFindTacticalArray g_unk0x006c0718;


// GLOBAL: GAME 0x006c0bcc
unsigned long g_unk0x006c0bcc;

// GLOBAL: GAME 0x006c0aa8
float g_unk0x006c0aa8[2] = {0.0f, 0.0f};

// TEMPLATE: GAME 0x004e5270 FOLDED
// ??0RHSeqList@@QAE@ABD@Z
RHSeqList::RHSeqList(const char &allocator)
{
    m_00[0] = allocator;
    RHSeqNode *head = (RHSeqNode *)operator new(0xc);
    head->m_next = head;
    head->m_prev = head;
    m_head = head;
    m_count = 0;
}

// FUNCTION: GAME 0x004e9d00
void RHFastFindGrid::FUN_004e9d00(unsigned char enabled, unsigned short layer, void *sector)
{
    unsigned short identifier = *(unsigned short *)((char *)sector + 0x38);
    unsigned short count = m_layers[layer].m_lineCount;
    if (count > 0)
    {
        unsigned char state = enabled;
        unsigned offset = 0;
        unsigned remaining = count;
        do
        {
            char *line = *(char **)((char *)m_layers[layer].m_lines + offset);
            if (*(unsigned char *)(line + 0x18) != state &&
                ((unsigned char)(*(unsigned *)(line + 0x14) >> 1) & 1) &&
                *(short *)(line + 0x20) == (unsigned)identifier)
                *(unsigned char *)(line + 0x18) = state;
            offset += 4;
        } while (--remaining != 0);
    }
}

// FUNCTION: GAME 0x004ebbd0
void RHFastFindGrid::InitializeLiftsFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x20415a20, 2);
    unsigned short count;
    unsigned short sectorIndex;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        file.Access(&sectorIndex, 2);
        RHFastFindSector *sector = (RHFastFindSector *)m_sectors.m_first[sectorIndex];
        ((RHProfileFile &)file).FUN_005f5370(2, 1);
        if (!(sector->LiftFlag() & 1))
        {
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xc22,
                // STRING: GAME 0x006afbd0
                "DA FALLEN MIR DIE OHREN AB : Illegal lift sector : %d !\n", sector->m_id);
        }
        sector->UnkSlot10(file, this);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004ebc80
void RHFastFindGrid::InitializeBuildingsFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x4641524d, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        bool isLift;
        file.Access(&isLift, 1);
        if (isLift)
        {
            void *lift = new RHSectorBuilding;
            ((RHFastFindSector *)lift)->UnkSlot10(file, this);
            fastfind_lifts.InsertLast(lift);
            FUN_004e8bd0(lift, m_layerCount - 1, true);
        }
        else
        {
            unsigned short gates;
            file.Access(&gates, 2);
            for (unsigned short j = 0; j < gates; ++j)
            {
                RHUnk0051aa00 *gate = new RHUnk0051aa00;
                gate->Unk0051b2a0(file, 0);
                if (gate->m_88 != 0 && gate->m_88 != 3 && gate->m_88 != 7)
                    SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xc9b,
                        // STRING: GAME 0x006afc0c
                        "VERBOTEN : Non-building & non-lift doors must be of type DEFAULT or GATE (%d,%d) !",
                        gate->m_94.m_x, gate->m_94.m_y);
                void *value = gate;
                fastfind_gateObjects.InsertLast(value);
            }
        }
    }
    FUN_005e20c0(file);
}

// Parked: capacity-aware insertion receiver and clamped grid-coordinate register allocation differ.
// STUB: GAME 0x004ebfe0
void RHFastFindGrid::FUN_004ebfe0(void *point, unsigned short layer, bool mode)
{
    if (mode) {
        char *layers = *(char **)((char *)this + 0x3ea4);
        RHFastFindPointerArray &array = *(RHFastFindPointerArray *)(layers + layer * 0xc0);
        array.InsertLast(point);
    }
    short x = (short)((float *)point)[1] >> 6;
    short y = (short)((float *)point)[2] >> 6;
    if (x < 0) x = 0;
    else if (x >= m_width) x = m_width - 1;
    if (y < 0) y = 0;
    else if (y >= m_height) y = m_height - 1;
    unsigned long cell = (m_height * layer + y) * m_width + x;
    (*(RHFastFindGateArray *)(*(char **)((char *)this + 0x3f80) + cell * 0xa0)).InsertLast((void *const &)point, false);
}

inline RHFastFindRepulsive *CopyFastFindRepulsive(RHFastFindRepulsive *first, RHFastFindRepulsive *last, RHFastFindRepulsive *destination)
{
    for (; first != last; ++destination, ++first)
    {
        destination->Unk004fdc20(*first);
        ((SBGeoVector2D *)&destination->m_14)->operator=((const SBGeoVector2D &)first->m_14);
        ((SBGeoVector2D *)&destination->m_1c)->operator=((const SBGeoVector2D &)first->m_1c);
        destination->m_24 = first->m_24;
        destination->m_28 = first->m_28;
        destination->m_2c = first->m_2c;
        destination->m_30 = first->m_30;
        destination->m_34 = first->m_34;
        destination->m_35 = first->m_35;
        destination->m_36 = first->m_36;
        destination->m_37 = first->m_37;
        destination->m_38 = first->m_38;
        destination->m_id = first->m_id;
    }
    return destination;
}

namespace std
{
template <>
inline RHFastFindRepulsive *vector<RHFastFindRepulsive>::erase(RHFastFindRepulsive *position)
{
    CopyFastFindRepulsive(position + 1, end(), position);
    _Destroy(_Last - 1, _Last);
    --_Last;
    return position;
}
}

// FUNCTION: GAME 0x004eca10
void RHFastFindGrid::DeleteStaticRepulsivePoint(unsigned long id)
{
    RHFastFindRepulsive *point = m_repulsivePoints.begin();
    unsigned short *layer = m_repulsiveLayers.begin();
    for (; point != m_repulsivePoints.end(); ++point, ++layer)
    {
        if (point->m_id == id)
        {
            m_repulsivePoints.erase(point);
            m_repulsiveLayers.erase(layer);
            return;
        }
    }
    SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xdcc,
        // STRING: GAME 0x006afc60
        "ACHTUNG : Trying to delete inexisting static repulsive point (ID : %d)", id);
}

struct RHFastFindRawNode
{
    RHFastFindRawNode *next;
    RHFastFindRawNode *previous;
    void *value;
};

void *FUN_0048f170(void *value);

// FUNCTION: GAME 0x004fc590
void RHFastFindGrid::EmptyAllScriptSectors()
{
    RHFastFindPointerArray &sectors = *(RHFastFindPointerArray *)((char *)this + 0x40e0);
    unsigned short count = sectors.size();
    for (unsigned short i = 0; i < count; ++i)
    {
        void *object = sectors.m_first[i];
        if (*(int *)((char *)object + 4) == 2)
        {
            char *owner = object ? (char *)object - 0xb8 : 0;
            RHFastFindRawNode *head = *(RHFastFindRawNode **)(owner + 0xd0);
            RHFastFindRawNode *next = head->next;
            while (next != head)
            {
                RHFastFindRawNode *node = next;
                next = next->next;
                FUN_0048f170(node);
                node->previous->next = node->next;
                node->next->previous = node->previous;
                ::operator delete(node);
                --*(int *)(owner + 0xd4);
            }
            *(char *)(owner + 0xdc) = 1;
        }
    }
}

// Residual: the target's geometric projection and three-way closest-point comparisons are missing.
// STUB: GAME 0x004fc8f0
bool RHFastFindGrid::FUN_004fc8f0(void *first, void *second, void *third, void *fourth)
{
    if (!first || !second || !third || !fourth)
        return false;
    SBGeoPoint2D &start = *(SBGeoPoint2D *)first;
    SBGeoPoint2D &end = *(SBGeoPoint2D *)second;
    float left = *(float *)third;
    float top = *(float *)fourth;
    return start.m_x <= end.m_x && start.m_y <= end.m_y && start.m_x <= left && start.m_y <= top;
}

// FUNCTION: GAME 0x004fcfd0
void *RHFastFindGrid::GetPatch(void *value)
{
    unsigned short count = m_patches.size();
    if (*(void **)((char *)value + 0xb0))
        return *(void **)((char *)value + 0xb0);
    for (unsigned short i = 0; i < count; ++i)
    {
        void *patch = m_patches.m_first[i];
        RHFastFindPointerArray &doors = *(RHFastFindPointerArray *)((char *)patch + 0x158);
        void **first = *(void **volatile *)&doors.m_first;
        unsigned short doorCount = first == 0 ? 0 : doors.m_last - first;
        for (unsigned short j = 0; j < doorCount; ++j)
            if (doors.m_first[j] == value)
                return patch;
    }
    return 0;
}

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

#include "RHFastFindUniqueList.h"

inline void RHFastFindUniqueList::InsertLastCall(void *const &value)
{
    ((RHUnkListSeq *)this)->insert(RHSeqIter(Head()), (RHSequence *const &)value);
    m_changed = true;
}

DECOMP_SIZE_ASSERT(RHFastFindUniqueList, 0x24)
DECOMP_SIZE_ASSERT(RHFastFindUniqueList::Iterator, 0x04)

#include "SBUIInputFieldBoxCalls.h"

#include "RHUnk00608f10.h"

class RHEngine;
extern RHEngine *g_pEngine;

class RHMobileUnk00520c50
{
public:
    void FUN_00520c50(float first, float second);
};

struct RHFastFindRepulsiveStorage
{
    undefined m_00[0x40];
    RHFastFindRepulsiveStorage(const SBGeoPoint2D &point, float radius, float strength)
    {
        ((RHUnk00520ae0 *)this)->RHUnk00520ae0::RHUnk00520ae0(point, radius, strength);
    }
    ~RHFastFindRepulsiveStorage() { ((RHUnk00520ae0 *)this)->~RHUnk00520ae0(); }
};

class RHMalignityArrayCalls
{
public:
    void FUN_004e60a0(void *, unsigned, const unsigned &);
};

class RHScriptBatchCalls
{
public:
    int Unk004ec910(void *, float, float, int);
};

void FUN_004fd680(RHUnk00520ae0 *destination, const RHUnk00520ae0 &other);

class RHUnk004fd0c0
{
public:
    char m_00[4];
    RHFastFindRepulsive *m_first;
    RHFastFindRepulsive *m_last;
    RHFastFindRepulsive *m_end;
    void Insert(RHFastFindRepulsive *position, unsigned count, const RHFastFindRepulsive &value);
    unsigned Size() const { return m_first == 0 ? 0 : m_last - m_first; }
    RHFastFindRepulsive *Copy(const RHFastFindRepulsive *first, const RHFastFindRepulsive *last, RHFastFindRepulsive *destination)
    {
        for (; first != last; ++destination, ++first)
            FUN_004fd680((RHUnk00520ae0 *)destination, *(const RHUnk00520ae0 *)first);
        return destination;
    }
    void Fill(RHFastFindRepulsive *destination, unsigned count, const RHFastFindRepulsive &value)
    {
        for (; count > 0; --count, ++destination)
            FUN_004fd680((RHUnk00520ae0 *)destination, (const RHUnk00520ae0 &)value);
    }
};

DECOMP_SIZE_ASSERT(RHFastFindRepulsiveBase, 0x14)
DECOMP_SIZE_ASSERT(RHFastFindRepulsive, 0x40)
DECOMP_SIZE_ASSERT(RHUnk004fd0c0, 0x10)

struct RHFastFindCell
{
    unsigned short m_localPointCount;
    undefined m_02[2];
    void **m_localPoints;
    unsigned short m_lineCount;
    undefined m_0a[2];
    void **m_lines;
    undefined m_10[8];
    unsigned short m_obstacleCount;
    undefined m_1a[2];
    void **m_obstacles;
    unsigned short m_pointCount;
    undefined m_22[2];
    void **m_points;

};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

#include "SBGeoSegment2D.h"
#include <stddef.h>

struct RHFastFindRepulsiveOwner
{
    undefined m_00[0x50];
    undefined *m_position;
    undefined m_54[0xf0];
    RHFastFindPointerArray m_points;
    RHFastFindPointerArray m_lines;
    undefined m_184[0x28];
    SBGeoBoundingBox2D m_bounds;
};

struct RHFastFindRepulsiveOwnerArray
{
    RHFastFindRepulsiveOwner **m_first;
    RHFastFindRepulsiveOwner **m_last;
    RHFastFindRepulsiveOwner *&operator[](unsigned index)
    {
        RHFastFindRepulsiveOwner **first = *(RHFastFindRepulsiveOwner **volatile *)&m_first;
        return first[index];
    }
};

DECOMP_STATIC_ASSERT(offsetof(RHFastFindRepulsiveOwner, m_position) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindRepulsiveOwner, m_points) + offsetof(RHFastFindPointerArray, m_first) == 0x148)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindRepulsiveOwner, m_lines) + offsetof(RHFastFindPointerArray, m_first) == 0x168)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindRepulsiveOwner, m_bounds) == 0x1ac)
DECOMP_SIZE_ASSERT(RHFastFindRepulsiveOwnerArray, 0x08)

// Parked: frame is 0x28 rather than 0x24; owner/output registers and uniqueness-search scheduling differ.
// STUB: GAME 0x004ec240
void RHFastFindGrid::FUN_004ec240(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    RHFastFindRepulsiveOwnerArray &owners = *(RHFastFindRepulsiveOwnerArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.m_first == 0 ? 0 : *(RHFastFindRepulsiveOwner ***)((char *)g_pEngine + 0x4980) - owners.m_first;
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindRepulsiveOwner *owner = owners[i];
        if (*(unsigned short *)(owner->m_position + 0xde) != layer) continue;
        if (!(unsigned char)((RHUnk00608f10 *)&owner->m_bounds)->FUN_00608f10((void *)&box)) continue;
        unsigned short lineCount = owner->m_lines.m_first == 0 ? 0 : owner->m_lines.m_last - owner->m_lines.m_first;
        if (lineCount > 0) {
            for (unsigned short j = 0; j < lineCount; ++j) {
                void **first = *(void **volatile *)&owner->m_lines.m_first;
                RHUnk0051f0f0 *value = (RHUnk0051f0f0 *)first[j];
                bool intersects = ((SBUIInputFieldBoxCalls *)&box)->FUN_00608450(SBGeoSegment2D(*value));
                if (intersects) {
                    void *copy = value;
                    if (output.Find(copy) == -1) output.InsertLastExternal(copy);
                }
            }
        }
    }
}

// FUNCTION: GAME 0x004ec450
void RHFastFindGrid::FUN_004ec450(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **first = *(void **volatile *)&entry.m_localPoints;
    unsigned short count = entry.m_localPointCount;
    if (count > 0)
    {
        void **values = first;
        unsigned long remaining = count;
        do
        {
            void *value = *values;
            if (*(bool *)((char *)value + 0x10) && (*(unsigned long *)((char *)value + 0xc) & mask) == mask)
                if (output.Find(value) == -1) output.InsertLast(value);
            ++values;
        } while (--remaining);
    }
}

// FUNCTION: GAME 0x004ec560
void RHFastFindGrid::FUN_004ec560(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y) {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004ec450(output, cell, mask);
        cell += skip;
    }
    if (mask & 2) FUN_004ec240(output, layer, box, mask);
}

// Parked: frame is 0x28 rather than 0x24; owner/output registers and uniqueness-search scheduling differ.
// STUB: GAME 0x004ec700
void RHFastFindGrid::FUN_004ec700(RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask)
{
    RHFastFindRepulsiveOwnerArray &owners = *(RHFastFindRepulsiveOwnerArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.m_first == 0 ? 0 : *(RHFastFindRepulsiveOwner ***)((char *)g_pEngine + 0x4980) - owners.m_first;
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindRepulsiveOwner *owner = owners[i];
        if (*(unsigned short *)(owner->m_position + 0xde) != layer) continue;
        if (!(unsigned char)((RHUnk00608f10 *)((char *)owner + 0x128))->FUN_00608f10((void *)&segment)) continue;
        unsigned short lineCount = owner->m_lines.m_first == 0 ? 0 : owner->m_lines.m_last - owner->m_lines.m_first;
        if (lineCount > 0) {
            for (unsigned short j = 0; j < lineCount; ++j) {
                void **first = *(void **volatile *)&owner->m_lines.m_first;
                RHUnk0051f0f0 *value = (RHUnk0051f0f0 *)first[j];
                bool intersects = ((SBGeoBoundingBox2D *)&segment)->FUN_00608650(SBGeoSegment2D(*value).Line());
                if (intersects) {
                    void *copy = value;
                    if (output.Find(copy) == -1) output.InsertLastExternal(copy);
                }
            }
        }
    }
}

// Parked: frame is 0x48 rather than 0x60; coordinate spills, temporary lifetime and insertion entity differ.
// STUB: GAME 0x004ec910
int RHScriptBatchCalls::Unk004ec910(void *location, float radius, float strength, int flags)
{
    RHUnk00522470 *point = (RHUnk00522470 *)location;
    RHFastFindGrid *grid = (RHFastFindGrid *)this;
    float x = ((float *)point)[1];
    float y = ((float *)point)[2];
    RHFastFindRepulsiveStorage value(SBGeoPoint2D(x, y), radius, strength);
    unsigned bits = flags;
    ((char *)&value)[0x35] = (unsigned char)bits & 1;
    ((char *)&value)[0x37] = (unsigned char)(bits >> 2) & 1;
    ((char *)&value)[0x36] = (unsigned char)(bits >> 1) & 1;
    ((char *)&value)[0x38] = (unsigned char)(bits >> 3) & 1;
    ((RHUnk004fd0c0 *)&grid->m_repulsivePoints)->Insert(grid->m_repulsivePoints.end(), 1, *(RHFastFindRepulsive *)&value);
    unsigned layer = point->m_layer;
    ((RHMalignityArrayCalls *)&grid->m_repulsiveLayers)->FUN_004e60a0(grid->m_repulsiveLayers.end(), 1, layer);
    return *(unsigned long *)((char *)&value + 0x3c);
}

// FUNCTION: GAME 0x004ecb50
bool RHFastFindGrid::FUN_004ecb50(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long kind)
{
    unsigned index = 0;
    for (RHFastFindRepulsive *point = m_repulsivePoints.begin(); point != m_repulsivePoints.end(); ++index, ++point) {
        if (m_repulsiveLayers[index] != layer) continue;
        if (((kind == 12 && point->m_35) || (kind == 20 && point->m_36) ||
             (kind == 4 && point->m_37) || (kind == 0 && point->m_38)) &&
            box.FUN_00608400(*(SBGeoPoint2D *)(point ? (char *)point + 4 : 0)))
            output.InsertLast(point);
    }
    return true;
}

// FUNCTION: GAME 0x004ecc60
bool RHFastFindGrid::FUN_004ecc60(RHFastFindUniqueList &owners, RHFastFindUniqueList &points, RHFastFindUniqueList &lines, unsigned short layer, const SBGeoBoundingBox2D &box)
{
    bool found = false;
    RHFastFindRepulsiveOwner ***first = (RHFastFindRepulsiveOwner ***)((char *)g_pEngine + 0x497c);
    RHFastFindRepulsiveOwner ***last = (RHFastFindRepulsiveOwner ***)((char *)g_pEngine + 0x4980);
    unsigned short count = *first == 0 ? 0 : *last - *first;
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindRepulsiveOwner *owner = (*first)[i];
        if (*(unsigned short *)(owner->m_position + 0xde) != layer) continue;
        bool added = false;
        if (!(unsigned char)((RHUnk00608f10 *)&owner->m_bounds)->FUN_00608f10((void *)&box)) continue;
        unsigned short lineCount = owner->m_lines.m_first == 0 ? 0 : owner->m_lines.m_last - owner->m_lines.m_first;
        for (unsigned short j = 0; j < lineCount; ++j) {
            void **lineValues = *(void **volatile *)&owner->m_lines.m_first;
            void *line = lineValues[j];
            bool intersects = box.FUN_00608650(SBGeoSegment2D(
                *(const SBGeoSegment2D *)(line ? (char *)line + 4 : 0)).Line());
            if (intersects) {
                lines.InsertLastCall(line);
                if (!added) {
                    void *value = owner;
                    owners.InsertLastCall(value);
                    added = true;
                    found = true;
                }
            }
        }
        unsigned short pointCount = owner->m_points.m_first == 0 ? 0 : owner->m_points.m_last - owner->m_points.m_first;
        for (unsigned short k = 0; k < pointCount; ++k) {
            void **pointValues = *(void **volatile *)&owner->m_points.m_first;
            void *value = pointValues[k];
            bool intersects = box.FUN_00608400(SBGeoPoint2D(*(SBGeoPoint2D *)(value ? (char *)value + 4 : 0)));
            if (intersects) {
                points.InsertLast(value);
                if (!added) {
                    owners.InsertLast(owner);
                    added = true;
                    found = true;
                }
            }
        }
    }
    return found;
}

// FUNCTION: GAME 0x004ecf60
void RHFastFindGrid::FUN_004ecf60(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **first = *(void **volatile *)&entry.m_lines;
    unsigned short count = entry.m_lineCount;
    if (count > 0)
    {
        void **values = first;
        unsigned long remaining = count;
        do
        {
            void *value = *values;
            if (*(bool *)((char *)value + 0x18) && (*(unsigned long *)((char *)value + 0x14) & mask) == mask)
                if (output.Find(value) == -1) output.InsertLast(value);
            ++values;
        } while (--remaining);
    }
}

// FUNCTION: GAME 0x004ed070
void RHFastFindGrid::FUN_004ed070(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    int previousCount = output.GetSize();
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y) {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004ecf60(output, cell, mask);
        cell += skip;
    }
    unsigned short count = output.GetSize();
    for (unsigned short i = previousCount; i < count; ++i) {
        ((RHSeqList *)&output)->GoTo(i);
        void *value = output.m_current.node->value;
        if (!((RHMalignitySegment *)((char *)value + 4))->FUN_0060ad50(box)) {
            output.Remove(i);
            --i;
            --count;
        }
    }
}

// FUNCTION: GAME 0x004ed370
void RHFastFindGrid::FUN_004ed370(RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask)
{
    SBGeoPoint2D point;
    SBGeoBoundingBox2D box;
    int previousCount = output.GetSize();
    box.FUN_00607e30(segment);
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= lastY; ++y) {
        for (unsigned short x = firstX; x <= lastX; ++cell, ++x) {
            point.m_x = (float)(x << 6);
            point.m_y = (float)(y << 6);
            box.FUN_00609050(point, point.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0aa8));
            if (((RHMalignitySegment *)&segment)->FUN_0060ad50(box)) FUN_004ecf60(output, cell, mask);
        }
        cell += skip;
    }
    unsigned short count = output.GetSize();
    for (unsigned short i = previousCount; i < count; ++i) {
        ((RHSeqList *)&output)->GoTo(i);
        void *value = output.m_current.node->value;
        if (!((SBGeoSegment2D *)((char *)value + 4))->IsIntersecting((const SBGeoSegment2D &)segment)) {
            ((RHSeqList *)&output)->GoTo(i);
            RHFastFindUniqueNode *node = output.m_current.node;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            operator delete(node);
            --output.count;
            output.m_changed = true;
            --i;
            --count;
        }
    }
}

// Parked: array insertion receivers allocate this/index to different registers; initial argument pushes move before receiver scaling.
// STUB: GAME 0x004ed690
void RHFastFindGrid::FUN_004ed690(void *value, unsigned short layer, bool mode)
{
    SBGeoPoint2D point;
    SBGeoBoundingBox2D box;
    if (mode) {
        RHFastFindPointerArray &array = *(RHFastFindPointerArray *)(*(char **)((char *)this + 0x3ea4) + layer * 0xc0 + 0x20);
        ((SBArray<RHSaveGame *> *)&array)->Insert((RHSaveGame **)array.m_last, 1, (RHSaveGame *const &)value);
        array.m_changed = true;
    }
    short firstX = (short)((RHFastFindLine *)value)->FUN_0051f470() >> 6;
    short firstY = (short)((RHFastFindLine *)value)->FUN_0051f490() >> 6;
    short lastX = (short)((RHFastFindLine *)value)->FUN_0051f450() >> 6;
    short lastY = (short)((RHFastFindLine *)value)->FUN_0051f4b0() >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y) {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell) {
            point.m_x = (float)(x << 6);
            point.m_y = (float)(y << 6);
            box.FUN_00609050(point, point.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0aa8));
            if (((RHMalignitySegment *)((char *)value + 4))->FUN_0060ad50(box)) {
                RHFastFindPointerArray *array = (RHFastFindPointerArray *)(*(char **)((char *)this + 0x3f80) + cell * 0xa0 + 0x20);
                ((SBArray<RHSaveGame *> *)array)->Insert((RHSaveGame **)array->m_last, 1, (RHSaveGame *const &)value);
                array->m_changed = true;
            }
        }
        cell += skip;
    }
}

// FUNCTION: GAME 0x004ed9b0
void RHFastFindGrid::FUN_004ed9b0(SBFile &file)
{
    FUN_005e1d50(file, 0x30303720, 2);
    unsigned short count;
    unsigned short layer;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindLine *line = new RHFastFindLine;
        line->FUN_0051faf0(file, *(RHFastFindPointerArray *)((char *)this + 0x4140));
        file.Access(&layer, 2);
        FUN_004ed690(line, layer, true);
    }
    FUN_005e20c0(file);
}

// Parked: insertion receiver scheduling changes this/index registers and argument slots.
// STUB: GAME 0x004eda80
void RHFastFindGrid::FUN_004eda80(void *value, unsigned short layer, bool mode)
{
    SBGeoBoundingBox2D box;
    if (mode)
        (*(RHFastFindPointerArray *)(*(char **)((char *)this + 0x3ea4) + layer * 0xc0 + 0x80)).InsertLast(value);
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)value + 8));
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            (*(RHFastFindPointerArray *)(*(char **)((char *)this + 0x3f80) + cell * 0xa0 + 0x80)).InsertLast(value);
        cell += skip;
    }
}

// FUNCTION: GAME 0x004edcf0
void RHFastFindGrid::FUN_004edcf0(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **first = *(void **volatile *)&entry.m_points;
    unsigned short count = entry.m_pointCount;
    if (count > 0)
    {
        void **values = first;
        unsigned long remaining = count;
        do
        {
            void *value = *values;
            if (*(bool *)value && (*(unsigned long *)((char *)value + 4) & mask) == mask)
                if (output.Find(value) == -1) output.InsertLast(value);
            ++values;
        } while (--remaining);
    }
}

class RHMask
{
public:
    RHMask();
    void InitializeFromProtoStream(SBFile &file, RHFastFindGrid *grid);
    bool IsAppliedToPointCharacter(const SBGeoPoint2D &point) const;
    bool IsAppliedToPoint(const SBGeoPoint3D &point, bool flag) const;

    undefined m_00[4]; // +0x00
    unsigned long m_flags; // +0x04
    undefined m_08[0x88]; // +0x08
};

// FUNCTION: GAME 0x004ede00
void RHFastFindGrid::FUN_004ede00(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point)
{
    int previousCount = output.GetSize();
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004edcf0(output, cell, 1);
        cell += skip;
    }
    unsigned short count = output.GetSize();
    if (count != 0)
    {
        for (unsigned short i = previousCount; i < count; ++i)
        {
            ((RHSeqList *)&output)->GoTo(i);
            void *value = output.m_current.node->value;
            if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box) ||
                !((RHMask *)value)->IsAppliedToPointCharacter(*(const SBGeoPoint2D *)point))
            {
                output.Remove(i);
                --i;
                --count;
            }
        }
    }
}

// Parked: inlined list-seek register allocation differs after center-point construction.
// STUB: GAME 0x004ee120
void RHFastFindGrid::FUN_004ee120(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point, undefined4 mode)
{
    int previousCount = output.GetSize();
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004edcf0(output, cell, 2);
        cell += skip;
    }
    unsigned short count = output.GetSize();
    if (count != 0)
    {
        SBGeoPoint2D center = box.FUN_00608f40();
        for (unsigned short i = previousCount; i < count; ++i)
        {
            ((RHSeqList *)&output)->GoTo(i);
            void *value = output.m_current.node->value;
            if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box) ||
                !((RHMask *)value)->IsAppliedToPoint(*(const SBGeoPoint3D *)point, *(const bool *)&mode))
            {
                output.Remove(i);
                --i;
                --count;
            }
        }
    }
}

// FUNCTION: GAME 0x004ee470
void RHFastFindGrid::FUN_004ee470(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box)
{
    int previousCount = output.GetSize();
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004edcf0(output, cell, 4);
        cell += skip;
    }
    unsigned short count = output.GetSize();
    for (unsigned short i = previousCount; i < count; ++i)
    {
        ((RHSeqList *)&output)->GoTo(i);
        void *value = output.m_current.node->value;
        if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box))
        {
            output.Remove(i);
            --i;
            --count;
        }
    }
}

// Parked: mask-check snapshot registers and copy differ.
// STUB: GAME 0x004ee770
void RHFastFindGrid::FUN_004ee770(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **first = *(void **volatile *)&entry.m_obstacles;
    unsigned short count = entry.m_obstacleCount;
    if (count > 0)
    {
        void **values = first;
        unsigned long remaining = count;
        do
        {
            void *value = *values;
            if (*(bool *)((char *)value + 8) && (*(unsigned long *)value & mask) == mask)
                if (output.Find(value) == -1) output.InsertLast(value);
            ++values;
        } while (--remaining);
    }
}

struct RHFastFindMobileOwner
{
    undefined m_00[0x50];
    undefined *m_position;
    undefined m_54[0x7c];
    void **m_first;
    void **m_last;
    undefined m_d8[0xd4];
    SBGeoBoundingBox2D m_bounds;
};

struct RHFastFindMobileArray
{
    RHFastFindMobileOwner **m_first;
    RHFastFindMobileOwner **m_last;
    int Size() { return m_first == 0 ? 0 : m_last - m_first; }
    RHFastFindMobileOwner *&operator[](unsigned index)
    {
        RHFastFindMobileOwner **first = *(RHFastFindMobileOwner **volatile *)&m_first;
        return first[index];
    }
};

class RHEngine;
extern RHEngine *g_pEngine;

// FUNCTION: GAME 0x004ee880
void RHFastFindGrid::FUN_004ee880(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    RHFastFindMobileArray &owners = *(RHFastFindMobileArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.m_first == 0 ? 0 : *(RHFastFindMobileOwner ***)((char *)g_pEngine + 0x4980) - owners.m_first;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHFastFindMobileOwner *owner = owners[i];
        if (*(unsigned short *)(owner->m_position + 0xde) == layer &&
            (unsigned char)((RHUnk00608f10 *)&owner->m_bounds)->FUN_00608f10((void *)&box))
        {
            unsigned short obstacleCount = owner->m_first == 0 ? 0 : owner->m_last - owner->m_first;
            for (unsigned short j = 0; j < obstacleCount; ++j)
            {
                void *value = owner->m_first[j];
                if ((unsigned char)((RHUnk00608f10 *)&box)->FUN_00608f10((char *)value + 0x24))
                {
                    if (output.Find(value) == -1)
                        output.InsertLastExternal(value);
                }
            }
        }
    }
}

// FUNCTION: GAME 0x004eea50
void RHFastFindGrid::FUN_004eea50(RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask)
{
    RHFastFindMobileArray &owners = *(RHFastFindMobileArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.m_first == 0 ? 0 : *(RHFastFindMobileOwner ***)((char *)g_pEngine + 0x4980) - owners.m_first;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHFastFindMobileOwner *owner = owners[i];
        if (*(unsigned short *)(owner->m_position + 0xde) == layer &&
            owner->m_bounds.FUN_00608650(reinterpret_cast<const RHMobileUnk006100e0 &>(segment)))
        {
            unsigned short obstacleCount = owner->m_first == 0 ? 0 : owner->m_last - owner->m_first;
            for (unsigned short j = 0; j < obstacleCount; ++j)
            {
                void *value = owner->m_first[j];
                if (((SBGeoBoundingBox2D *)((char *)value + 0x24))->FUN_00608650(reinterpret_cast<const RHMobileUnk006100e0 &>(segment)))
                {
                    if (output.Find(value) == -1)
                        output.InsertLastExternal(value);
                }
            }
        }
    }
}

// FUNCTION: GAME 0x004eec20
void RHFastFindGrid::FUN_004eec20(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    int previousCount = output.GetSize();
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
            FUN_004ee770(output, cell, mask);
        cell += skip;
    }
    if (mask & 3)
        FUN_004ee880(output, layer, box, mask);
    unsigned short count = output.GetSize();
    for (unsigned short i = previousCount; i < count; ++i)
    {
        ((RHSeqList *)&output)->GoTo(i);
        void *value = output.m_current.node->value;
        if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 0x24))->FUN_00608f10((void *)&box))
        {
            output.Remove(i);
            --i;
            --count;
        }
    }
}

// Parked: segment begin/erase return slots and seek register scheduling differ.
// STUB: GAME 0x004eef30
void RHFastFindGrid::FUN_004eef30(RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask)
{
    SBGeoPoint2D point;
    SBGeoBoundingBox2D box;
    int previousCount = output.GetSize();
    box.FUN_00607e30(segment);
    const float *bounds = (const float *)&box;
    short firstX = (short)bounds[0] >> 6;
    short firstY = (short)bounds[1] >> 6;
    short lastX = (short)bounds[2] >> 6;
    short lastY = (short)bounds[3] >> 6;
    if (firstX < 0) firstX = 0;
    else if (firstX >= m_width) firstX = m_width - 1;
    if (firstY < 0) firstY = 0;
    else if (firstY >= m_height) firstY = m_height - 1;
    if (lastX < 0) lastX = 0;
    else if (lastX >= m_width) lastX = m_width - 1;
    if (lastY < 0) lastY = 0;
    else if (lastY >= m_height) lastY = m_height - 1;
    unsigned long cell = (m_height * layer + firstY) * m_width + firstX;
    int skip = m_width - (lastX - firstX) - 1;
    for (unsigned short y = firstY; y <= (unsigned short)lastY; ++y)
    {
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++cell, ++x)
        {
            point.m_x = (float)(x << 6);
            point.m_y = (float)(y << 6);
            box.FUN_00609050(point, point.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0aa8));
            if (((RHMalignitySegment *)&segment)->FUN_0060ad50(box))
                FUN_004ee770(output, cell, mask);
        }
        cell += skip;
    }
    if (mask & 3)
        FUN_004eea50(output, layer, segment, mask);
    unsigned short count = output.GetSize();
    for (unsigned short i = previousCount; i < count; ++i)
    {
        ((RHSeqList *)&output)->GoTo(i);
        void *value = *output.Current();
        if (!((SBGeoBoundingBox2D *)((char *)value + 0x24))->FUN_00608650(reinterpret_cast<const RHMobileUnk006100e0 &>(segment)))
        {
            output.GoToSegment(i);
            ((RHUnk0046eb30 *)&output)->erase(*(const RHScriptIter *)&output.m_current);
            output.m_changed = true;
            --i;
            --count;
        }
    }
}

struct RHFastFindPatchView
{
    char m_00[0xac];
    RHFastFindUniqueList m_lines; // +0xac
    RHFastFindUniqueList m_points; // +0xd0
    char m_f4[0x54];
    void *m_148; // +0x148
};

// FUNCTION: GAME 0x004efd10
void RHFastFindGrid::FUN_004efd10(void *patch, unsigned short layer, bool mode)
{
    m_patches.InsertLast(patch);
    if (mode)
        (*(RHFastFindPointerArray *)(*(char **)((char *)this + 0x3ea4) + layer * 0xc0 + 0xa0)).InsertLast(patch);
    RHFastFindUniqueList *list = &((RHFastFindPatchView *)patch)->m_lines;
    unsigned short count = list->GetSize();
    for (unsigned short i = 0; i < count; ++i)
    {
        ((RHSeqList *)list)->GoTo(i);
        FUN_004e8bd0(list->m_current.node->value, layer, true);
    }
    list = &((RHFastFindPatchView *)patch)->m_points;
    count = list->GetSize();
    for (unsigned short j = 0; j < count; ++j)
    {
        ((RHSeqList *)list)->GoTo(j);
        FUN_004e8bd0(list->m_current.node->value, layer, true);
    }
    void *obstacle = ((RHFastFindPatchView *)patch)->m_148;
    if (obstacle)
    {
        FUN_004e8bd0(obstacle, layer, true);
        unsigned char shifted = (unsigned char)(*(unsigned long *)((char *)obstacle + 0x30) >> 7);
        if (shifted & 1)
            FUN_004e99e0(obstacle, layer, true);
    }
}

// FUNCTION: GAME 0x004efe40
bool RHFastFindGrid::FUN_004efe40(const SBGeoPoint3D &first, const SBGeoPoint3D &second, float &slope, float &intercept)
{
    RHUnk005fc3b0 direction;
    float dy = second.m_y - first.m_y;
    float dx = second.m_x - first.m_x;
    direction.m_x = second.m_x - first.m_x;
    direction.m_y = second.m_y - first.m_y;
    if (second.m_x - first.m_x > 0)
    {
        if (second.m_y - first.m_y > 0)
        {
            if (second.m_x - first.m_x > second.m_y - first.m_y)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
            else
            {
                slope = (second.m_z - first.m_z) / dy;
                intercept = first.m_z - slope * first.m_y;
                return false;
            }
        }
        else
        {
            if (second.m_x - first.m_x > -(second.m_y - first.m_y))
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
            else
            {
                slope = (second.m_z - first.m_z) / dy;
                intercept = first.m_z - slope * first.m_y;
                return false;
            }
        }
    }
    else
    {
        if (second.m_y - first.m_y > 0)
        {
            if (-(second.m_x - first.m_x) > second.m_y - first.m_y)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
            else
            {
                slope = (second.m_z - first.m_z) / dy;
                intercept = first.m_z - slope * first.m_y;
                return false;
            }
        }
        else
        {
            if (second.m_x - first.m_x < second.m_y - first.m_y)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
            else
            {
                slope = (second.m_z - first.m_z) / dy;
                intercept = first.m_z - slope * first.m_y;
                return false;
            }
        }
    }
}

// parked: best probe 61.16%.
// STUB: GAME 0x004ef340
void RHFastFindGrid::InitializeSightObstaclesFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x574f4157, 3);
    RHUnk005a3450 *area = new RHUnk005a3450(4);
    {
        SBGeoPoint3D first(0.0f, 10.0f, 0.0f);
        SBGeoPoint3D second(10.0f, 0.0f, 0.0f);
        SBGeoPoint3D third(0.0f, 0.0f, 0.0f);
        area->FirstPlane().Unk005df860(third, second, first);
        area->FirstPlane().Unk005dfa00();
    }
    {
        SBGeoPoint3D first(0.0f, 10.0f, 0.0f);
        SBGeoPoint3D second(10.0f, 0.0f, 0.0f);
        SBGeoPoint3D third(0.0f, 0.0f, 0.0f);
        area->SecondPlane().Unk005df860(third, second, first);
        area->SecondPlane().Unk005dfa00();
    }
    area->Bounds().Unk00607dc0(SBGeoPoint2D(0.0f, 0.0f));
    area->Bounds().Unk00607dc0(SBGeoPoint2D(2000.0f, 2000.0f));
    area->OtherBounds() = area->Bounds();
    area->SetLayer(0);
    area->SetSector(0);
    area->m_flags |= 4;
    area->m_active = false;
    m_projectionAreas.InsertLast((void *const &)area);
    RHFastFindPointerArray &materials = *(RHFastFindPointerArray *)((char *)this + 0x4120);
    unsigned short materialCount;
    unsigned short materialIndex;
    file.Access(&materialCount, 2);
    for (unsigned short i = 0; i < materialCount; ++i)
    {
        file.Access(&materialIndex, 2);
        if (materialIndex >= materials.size())
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1406,
                // STRING: GAME 0x006afcdc
                "HALT ! STEHENBLEIBEN ! : Trying to associate non-existing material with default sight obstacle !");
        FUN_004e8bd0(materials.m_first[materialIndex], 0, true);
        FUN_004e99e0(materials.m_first[materialIndex], 0, true);
    }
    unsigned short obstacleCount;
    file.Access(&obstacleCount, 2);
    for (unsigned short j = 0; j < obstacleCount; ++j)
    {
        area = new RHUnk005a3450;
        area->Unk005a3810(file, materials);
        if (area->ProjectionFlag() & 1)
        {
            m_projectionAreas.InsertLast((void *const &)area);
            RHFastFindSightSector *sector = (RHFastFindSightSector *)m_sectors.m_first[area->m_sector];
            if ((sector->SectorFlag() & 1) && (sector->BaseFlag() & 1))
            {
                void *value = area;
                RHSeqNode *head = sector->m_head;
                RHSeqNode *previous = head->m_prev;
                RHSeqNode *node = (RHSeqNode *)operator new(0xc);
                node->m_next = head ? head : node;
                node->m_prev = previous ? previous : node;
                head->m_prev = node;
                node->m_prev->m_next = node;
                RHSeqList::CopyData(&node->m_data, (RHSequenceElement *const *)&value);
                ++sector->m_count;
                sector->m_changed = true;
            }
            else
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1420,
                    // STRING: GAME 0x006afca8
                    "Illegal sight obstacle/motion area association !\n");
            area->m_motionArea = area->Unk005a5780();
            FUN_004e8bd0(area->m_motionArea, 0, true);
        }
        FUN_004ef8e0(area, 0, true);
        (*(RHFastFindGateArray *)((char *)this + 0x4140)).InsertLast((void *const &)area, false, true);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004efbb0
bool RHFastFindGrid::Unk004efbb0(SBFile &file, void **value)
{
    short index;
    if (!file.m_bLoading)
    {
        if (*value == 0)
        {
            index = -1;
            file.Access(&index, 2);
            return true;
        }
        index = m_patches.Find(*value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            // STRING: GAME 0x006afbac
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1498, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x149f, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            *value = 0;
            return true;
        }
        *value = m_patches.m_first[index];
    }
    return true;
}

// parked: best probe 71.97%.
// STUB: GAME 0x004f9490
bool RHFastFindGrid::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006afd40
        "RHFastFindGrid");
    if (file.m_bLoading)
    {
        for (unsigned short i = 0; i <= m_layerCount - 1; ++i)
        {
            RHFastFindLayer &layer = m_layers[i];
            RHUnk0054f870 **paths = layer.m_paths;
            for (short j = layer.m_pathCount - 1; j >= 0; --j)
                paths[j]->Unk00550220();
        }
    }
    for (unsigned short i = 0; i <= m_layerCount - 1; ++i)
    {
        unsigned short count = m_layers[i].m_pathCount;
        RHUnk0054f870 **paths = m_layers[i].m_paths;
        for (unsigned short j = 0; j < count; ++j)
            if (!paths[j]->Unk0054f870(file))
                return false;
    }
    unsigned short gateCount = m_gates.size();
    for (unsigned short gateIndex = 0; gateIndex < gateCount; ++gateIndex)
        if (!((RHFastFindSerializableGate *)m_gates.m_first[gateIndex])->UnkSlot4(file))
            return false;
    RHFastFindPointerArray &scripts = *(RHFastFindPointerArray *)((char *)this + 0x40e0);
    unsigned short scriptCount = scripts.size();
    for (unsigned short scriptIndex = 0; scriptIndex < scriptCount; ++scriptIndex)
    {
        void *data = scripts.m_first[scriptIndex];
        if (*(int *)((char *)data + 4) == 2)
        {
            RHFastFindSerializableSector *sector = data ? (RHFastFindSerializableSector *)((char *)data - 0xb8) : 0;
            if (!sector->UnkSlotc(file))
                return false;
        }
    }
    unsigned short sectorCount = m_sectors.size();
    for (unsigned short sectorIndex = 0; sectorIndex < sectorCount; ++sectorIndex)
    {
        RHFastFindSerializableSector *sector = (RHFastFindSerializableSector *)m_sectors.m_first[sectorIndex];
        if (sector)
        {
            if (sector->Flag12() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
            else if (sector->Flag13() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
            else if (sector->Flag9() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
        }
    }
    if (file.m_bLoading && file.m_version < 4)
    {
        bool legacyFlag;
        unsigned short count;
        if (file.Access(&legacyFlag, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2307, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2309, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            float legacyValue;
            if (file.Access(&legacyValue, 4) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x230c, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
            if (file.Access(&legacyValue, 4) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x230d, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
    }
    RHUnk004b2190Member point;
    unsigned int pointCount;
    unsigned short layerIndex;
    if (file.m_bLoading)
    {
        m_repulsivePoints.erase(m_repulsivePoints.begin(), m_repulsivePoints.end());
        m_repulsiveLayers.erase(m_repulsiveLayers.begin(), m_repulsiveLayers.end());
        if (file.Access(&pointCount, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x234a, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned int i = 0; i < pointCount; ++i)
        {
            point.Serialize(file);
            if (file.Access(&layerIndex, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x234e, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
            ((SBArray<RHUnk004b2190Member> *)&m_repulsivePoints)->Insert((RHUnk004b2190Member *)m_repulsivePoints.end(), 1, point);
            ((SBArray<unsigned short> *)&m_repulsiveLayers)->Insert(m_repulsiveLayers.end(), 1, layerIndex);
        }
    }
    else
    {
        pointCount = m_repulsivePoints.size();
        if (file.Access(&pointCount, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2358, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned int i = 0; i < pointCount; ++i)
        {
            ((RHUnk004b2190Member *)&m_repulsivePoints[i])->Serialize(file);
            layerIndex = m_repulsiveLayers[i];
            if (file.Access(&layerIndex, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x235e, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
    }
    return true;
}

struct RHFastFindPathEdge
{
    class RHFastFindPathGate *first;
    class RHFastFindPathGate *second;
    undefined m_08[4];
    float distance;
};

class RHFastFindPathGate
{
public:
    virtual bool CanPass(bool, RHElementActor *, bool, bool, int);
    undefined m_04[8];
    void *m_firstSector;
    void *m_secondSector;
    undefined m_14[4];
    SBGeoPoint2D m_firstPoint;
    SBGeoPoint2D m_secondPoint;
    float m_penalty;
    RHFastFindUniqueList m_firstEdges;
    RHFastFindUniqueList m_secondEdges;
    float m_cost;
    float m_estimate;
    float m_total;
    bool m_visited;
    bool m_direction;
    undefined m_82[2];
    RHFastFindPathEdge *m_previous;
};

DECOMP_SIZE_ASSERT(RHFastFindPathGate, 0x88)

#include "RHActorGridCalls.h"

struct RHUnk004b1520List
{
    RHScriptIter FUN_00424410(RHScriptIter, void *const &);
};

struct RHArtificialIntelligenceElement;
struct RHArtificialIntelligenceList
{
public:
    RHArtificialIntelligenceElement *&FUN_00423c20(int);
};

// FUNCTION: GAME 0x004f9a80
bool RHActorGridCalls::FUN_004f9a80(void *sectors, RHElementActor *actor, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned endLayer, int mode)
{
    RHFastFindGrid *grid = (RHFastFindGrid *)this;
    unsigned steps = 0;
    grid->FUN_004fa660();
    unsigned short count = ((RHFastFindUniqueList *)((char *)startArea + 0x5c))->GetSize();
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindUniqueList *directions = (RHFastFindUniqueList *)((char *)startArea + 0x80);
        ((RHSeqList *)directions)->GoTo(i);
        bool direction = *(bool *)&directions->m_current.node->value;
        RHFastFindUniqueList *gates = (RHFastFindUniqueList *)((char *)startArea + 0x5c);
        ((RHSeqList *)gates)->GoTo(i);
        RHFastFindPathGate *gate = (RHFastFindPathGate *)gates->m_current.node->value;
        if (gate->CanPass(direction, actor, true, false, mode)) {
            gate->m_visited = true;
            gate->m_previous = 0;
            if (direction) {
                gate->m_direction = true;
                gate->m_cost = ((RHUnk005fc3b0 *)&start.Unk005fc110(gate->m_firstPoint))->Unk005fc6a0(1.0f);
                gate->m_estimate = ((RHUnk005fc3b0 *)&end.Unk005fc110(gate->m_secondPoint))->Unk005fc6a0(1.0f);
            } else {
                gate->m_direction = false;
                gate->m_cost = ((RHUnk005fc3b0 *)&start.Unk005fc110(gate->m_secondPoint))->Unk005fc6a0(1.0f);
                gate->m_estimate = ((RHUnk005fc3b0 *)&end.Unk005fc110(gate->m_firstPoint))->Unk005fc6a0(1.0f);
            }
            gate->m_total = gate->m_penalty + gate->m_estimate + gate->m_cost;
            grid->FUN_004fa6f0(gate);
        }
    }
    RHFastFindPathGate *gate = grid->FUN_004f9d60(actor, start, startArea, startLayer, end, endArea, endLayer, 0);
    if (!gate) return false;
    RHFastFindUniqueList &output = *(RHFastFindUniqueList *)sectors;
    output.InsertFirst(gate);
    while (gate->m_previous) {
        if (steps > 100) return false;
        ++steps;
        RHFastFindPathEdge *edge = gate->m_previous;
        gate = gate == edge->first ? edge->second : edge->first;
        output.InsertFirst(gate);
    }
    return true;
}

// Parked: four distance-temporary branches differ in x87 spills, state-store order and expansion register allocation.
// STUB: GAME 0x004f9d60
RHFastFindPathGate *RHFastFindGrid::FUN_004f9d60(RHElementActor *actor, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned endLayer, int mode)
{
    while (*(int *)((char *)this + 0x4194) > 0) {
        RHFastFindPathGate *gate = (RHFastFindPathGate *)(*(RHFastFindUniqueNode **)((char *)this + 0x4190))->next->value;
        RHFastFindUniqueList &open = *(RHFastFindUniqueList *)((char *)this + 0x418c);
        ((RHUnk0046eb30 *)&open)->erase(((RHUnk0046eb30 *)&open)->FUN_0046eb80());
        open.m_changed = true;
        RHFastFindUniqueList *edges;
        if (gate->m_direction) {
            if (gate->m_secondSector == endArea) return gate;
            edges = &gate->m_firstEdges;
        } else {
            if (gate->m_firstSector == endArea) return gate;
            edges = &gate->m_secondEdges;
        }
        unsigned short count = edges->GetSize();
        for (unsigned short i = 0; i < count; ++i) {
            ((RHSeqList *)edges)->GoTo(i);
            RHFastFindPathEdge *edge = (RHFastFindPathEdge *)edges->m_current.node->value;
            if (edge == gate->m_previous) continue;
            RHFastFindPathGate *next = edge->first;
            void *firstSector = gate->m_direction ? next->m_firstSector : next->m_secondSector;
            void *secondSector = gate->m_direction ? edge->second->m_firstSector : edge->second->m_secondSector;
            if (firstSector == secondSector) continue;
            if (gate == next) next = edge->second;
            float penalty = gate->m_penalty;
            float cost = gate->m_cost + edge->distance + penalty;
            if (!(cost < next->m_cost || !next->m_visited)) continue;
            next->m_previous = edge;
            next->m_cost = cost;
            if (gate->m_direction) {
                if (gate->m_secondSector == next->m_secondSector) {
                    next->m_direction = false;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_firstPoint.Unk005fc110(end))->Unk005fc6a0(1.0f);
                } else {
                    next->m_direction = true;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_secondPoint.Unk005fc110(end))->Unk005fc6a0(1.0f);
                }
            } else {
                if (gate->m_firstSector == next->m_secondSector) {
                    next->m_direction = false;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_firstPoint.Unk005fc110(end))->Unk005fc6a0(1.0f);
                } else {
                    next->m_direction = true;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_secondPoint.Unk005fc110(end))->Unk005fc6a0(1.0f);
                }
            }
            next->m_visited = true;
            next->m_total = (next->m_penalty + next->m_estimate) + cost;
            if (next->CanPass(next->m_direction, actor, false, false, mode)) FUN_004fa6f0(next);
        }
    }
    return 0;
}

// FUNCTION: GAME 0x004fa080
bool RHFastFindGrid::FUN_004fa080(RHFastFindUniqueList &output, RHElementActor *actor, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, RHFastFindPathGate *door, int mode)
{
    FUN_004fa660();
    RHFastFindUniqueList *directions = (RHFastFindUniqueList *)((char *)startArea + 0x80);
    RHFastFindUniqueList *gates = (RHFastFindUniqueList *)((char *)startArea + 0x5c);
    unsigned short count = gates->GetSize();
    for (unsigned short i = 0; i < count; ++i) {
        ((RHSeqList *)directions)->GoTo(i);
        bool direction = *(bool *)&directions->m_current.node->value;
        RHFastFindPathGate *gate = (RHFastFindPathGate *)((RHArtificialIntelligenceList *)gates)->FUN_00423c20(i);
        if (gate->CanPass(direction, actor, true, false, mode)) {
            gate->m_visited = true;
            gate->m_previous = 0;
            if (direction) {
                gate->m_direction = true;
                gate->m_cost = ((RHUnk005fc3b0 *)&start.Unk005fc110(gate->m_firstPoint))->Unk005fc6a0(1.0f);
                gate->m_estimate = ((RHUnk005fc3b0 *)&((SBGeoPoint2D *)((char *)door + 0x94))->Unk005fc110(gate->m_secondPoint))->Unk005fc6a0(1.0f);
            } else {
                gate->m_direction = false;
                gate->m_cost = ((RHUnk005fc3b0 *)&start.Unk005fc110(gate->m_secondPoint))->Unk005fc6a0(1.0f);
                gate->m_estimate = ((RHUnk005fc3b0 *)&((SBGeoPoint2D *)((char *)door + 0x94))->Unk005fc110(gate->m_firstPoint))->Unk005fc6a0(1.0f);
            }
            gate->m_total = gate->m_penalty + gate->m_estimate + gate->m_cost;
            FUN_004fa6f0(gate);
        }
    }
    RHFastFindPathGate *gate = FUN_004fa340(actor, start, startArea, startLayer, door, mode);
    if (!gate) return false;
    output.InsertFirst(gate);
    while (gate->m_previous) {
        RHFastFindPathEdge *edge = gate->m_previous;
        gate = gate == edge->first ? edge->second : edge->first;
        output.InsertFirst(gate);
    }
    return true;
}

// Parked: four door-distance branches differ in temporary scheduling, state-store order and expansion registers.
// STUB: GAME 0x004fa340
RHFastFindPathGate *RHFastFindGrid::FUN_004fa340(RHElementActor *actor, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, RHFastFindPathGate *door, int mode)
{
    while (*(int *)((char *)this + 0x4194) > 0) {
        RHFastFindPathGate *gate = (RHFastFindPathGate *)(*(RHFastFindUniqueNode **)((char *)this + 0x4190))->next->value;
        RHFastFindUniqueList &open = *(RHFastFindUniqueList *)((char *)this + 0x418c);
        ((RHUnk0046eb30 *)&open)->erase(((RHUnk0046eb30 *)&open)->FUN_0046eb80());
        open.m_changed = true;
        if (gate == door) return gate;
        RHFastFindUniqueList *edges = gate->m_direction ? &gate->m_firstEdges : &gate->m_secondEdges;
        unsigned short count = edges->GetSize();
        for (unsigned short i = 0; i < count; ++i) {
            ((RHSeqList *)edges)->GoTo(i);
            RHFastFindPathEdge *edge = (RHFastFindPathEdge *)edges->m_current.node->value;
            if (edge == gate->m_previous) continue;
            RHFastFindPathGate *next = edge->first;
            void *firstSector = gate->m_direction ? next->m_firstSector : next->m_secondSector;
            void *secondSector = gate->m_direction ? edge->second->m_firstSector : edge->second->m_secondSector;
            if (firstSector == secondSector) continue;
            if (gate == next) next = edge->second;
            float cost = gate->m_cost + edge->distance;
            if (!(cost < next->m_cost || !next->m_visited)) continue;
            next->m_previous = edge;
            next->m_cost = cost;
            if (gate->m_direction) {
                if (gate->m_secondSector == next->m_secondSector) {
                    next->m_direction = false;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_firstPoint.Unk005fc110(*(SBGeoPoint2D *)((char *)door + 0x94)))->Unk005fc6a0(1.0f);
                } else {
                    next->m_direction = true;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_secondPoint.Unk005fc110(*(SBGeoPoint2D *)((char *)door + 0x94)))->Unk005fc6a0(1.0f);
                }
            } else {
                if (gate->m_firstSector == next->m_secondSector) {
                    next->m_direction = false;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_firstPoint.Unk005fc110(*(SBGeoPoint2D *)((char *)door + 0x94)))->Unk005fc6a0(1.0f);
                } else {
                    next->m_direction = true;
                    if (!next->m_visited) next->m_estimate = ((RHUnk005fc3b0 *)&next->m_secondPoint.Unk005fc110(*(SBGeoPoint2D *)((char *)door + 0x94)))->Unk005fc6a0(1.0f);
                }
            }
            next->m_visited = true;
            next->m_total = (next->m_penalty + next->m_estimate) + cost;
            if (next->CanPass(next->m_direction, actor, false, false, mode)) FUN_004fa6f0(next);
        }
    }
    return 0;
}

// FUNCTION: GAME 0x004fa660
void RHFastFindGrid::FUN_004fa660()
{
    RHFastFindUniqueList &open = *(RHFastFindUniqueList *)((char *)this + 0x418c);
    RHFastFindUniqueNode *head = open.Head();
    RHFastFindUniqueNode *node = head->next;
    while (node != head) {
        RHFastFindUniqueNode *removed = node;
        node = node->next;
        ((RHUnk0046eb30 *)&open)->erase(RHScriptIter((RHScriptNode *)removed));
    }
    open.m_changed = true;
    *(float *)((char *)this + 0x41b0) = 1.0e15f;
    unsigned short count = m_gates.size();
    for (unsigned short i = 0; i < count; ++i) {
        RHFastFindPathGate *gate = (RHFastFindPathGate *)m_gates.m_first[i];
        gate->m_visited = false;
        gate->m_previous = 0;
    }
}

inline void RHFastFindInsertAt(RHFastFindUniqueList &list, int index, void *const &value)
{
    list.GoToSegment(index);
    ((RHUnk004b1520List *)&list)->FUN_00424410(RHScriptIter((RHScriptNode *)list.m_current.node), value);
    list.m_changed = true;
}

// Parked: extra saved ebp, cursor address retained in ebx and inline cursor-seek scheduling differ.
// STUB: GAME 0x004fa6f0
void RHFastFindGrid::FUN_004fa6f0(void *value)
{
    unsigned short count = ((RHFastFindUniqueList *)((char *)this + 0x418c))->GetSize();
    float total = ((RHFastFindPathGate *)value)->m_total;
    if (count == 0) {
        RHFastFindUniqueList &open = *(RHFastFindUniqueList *)((char *)this + 0x418c);
        RHFastFindUniqueNode *position = open.Head()->next;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)((RHUnk0046eb30 *)&open)->Unk0059f720((RHScriptNode *)position, (RHScriptNode *)position->previous);
        position->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++open.count;
        open.m_changed = true;
    }
    else {
        RHFastFindUniqueList &open = *(RHFastFindUniqueList *)((char *)this + 0x418c);
        unsigned short index = 0;
        ((RHSeqList *)&open)->GoTo(0);
        while (total > ((RHFastFindPathGate *)(*(RHFastFindUniqueNode *volatile *)&open.m_current)->value)->m_total) {
            ++index;
            if (index >= count) break;
            ((RHSeqList *)&open)->GoTo(index);
            if ((*(RHFastFindUniqueNode *volatile *)&open.m_current)->value == value) return;
        }
        if (index == open.GetSize()) open.InsertLastAllocator(value);
        else {
            RHFastFindInsertAt(open, index, value);
        }
    }
}

// New probe: marker flip leaves default-branch cleanup split at 93.24% and creates an effective row.
// STUB: GAME 0x004fa8e0
void RHFastFindGrid::InitializeTacticalInfosFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x4849524e, 2);
    RHFastFindClearTactical(g_unk0x006c06f0);
    RHFastFindClearTactical(g_unk0x006c0718);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        switch (FUN_005e1d00(file))
        {
        case 0x42555348:
            FUN_004faf40(file);
            break;
        case 0x484f4c45:
            FUN_004fb1d0(file);
            break;
        case 0x4e4c4950:
            FUN_004fb230(file);
            break;
        case 0x504f5720:
            InitializeReinforcementPointsFromMissionStream(file);
            break;
        default:
            char chunk[5];
            *(unsigned long *)chunk = FUN_005e1d00(file);
            chunk[4] = 0;
            FUN_005e2300(file);
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x265f,
                // STRING: GAME 0x006afd50
                "ACHTUNG : Unimplemented or unknown chunk %s, skipped", chunk);
            break;
        }
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004faaa0
    void RHFastFindGrid::InitializeReinforcementPointsFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x504f5720, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short x;
        short y;
        int directionValue;
        int nextDirection;
        unsigned short layer;
        unsigned short sectorIndex;
        short direction;
        file.Access(&x, 2);
        file.Access(&y, 2);
        file.Access(&directionValue, 4);
        file.Access(&nextDirection, 4);
        file.Access(&layer, 2);
        file.Access(&sectorIndex, 2);
        file.Access(&direction, 2);
        RHFastFindSector *sector;
        if (sectorIndex == 0xffff)
            sector = fastfind_defaultSector;
        else
            sector = (RHFastFindSector *)m_sectors.m_first[sectorIndex];
        if (!(sector->SectorFlag() & 1) || !(sector->BaseFlag() & 1))
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x268e,
                // STRING: GAME 0x006afd88
                "DA LACHEN DIE H\334HNER ! Reinforcemenent point lies in invalid sector !");
        SBGeoPoint2D destination((float)x, (float)y);
        SBGeoPoint2D first;
        SBGeoPoint2D second;
        ((RHScriptRecordWorld *)this)->Unk004fc8f0(second, first, &destination, (unsigned short)directionValue);
        RHUnk0051aa00 *gate = new RHUnk0051aa00;
        gate->m_88 = 8;
        gate->m_9c = 6;
        gate->m_a0 = 6;
        gate->m_a4 = 6;
        gate->m_a8 = 6;
        gate->m_b0 = 0;
        gate->m_14 = m_layerCount;
        gate->m_0c = fastfind_defaultSector;
        gate->m_18.Set((short)first.m_x, (short)first.m_y);
        gate->m_94.Set((short)second.m_x, (short)second.m_y);
        gate->m_10 = sector;
        gate->m_16 = direction;
        gate->m_20.Set(x, y);
        FUN_004fad80(gate);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004fad80
void RHFastFindGrid::FUN_004fad80(void *gate)
{
    (*(RHFastFindPointerArray *)((char *)this + 0x4100)).InsertLast(gate);
    void *value = gate;
    fastfind_gateObjects.InsertLast(value, true, false, true);
}

// FUNCTION: GAME 0x004fb1d0
void RHFastFindGrid::FUN_004fb1d0(SBFile &file)
{
    FUN_005e1d50(file, 0x484f4c45, 2);
    unsigned short count;
    file.Access(&count, 2);
    RHUnk005223f0 hole;
    for (unsigned short i = 0; i < count; ++i)
    {
        hole.FUN_005223f0(file);
        FUN_00418390(&hole);
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004fb510
void RHFastFindGrid::InitializeJumpStuffFromProtoStream(SBFile &file)
{
    char allocator;
    RHUnk004e5270 sectors(allocator);
    FUN_005e1d50(file, 0x50505050, 4);
    unsigned short sectorCount;
    file.Access(&sectorCount, 2);
    for (unsigned short i = 0; i < sectorCount; ++i)
    {
        void *sector = new RHUnk0051e5e0;
        ((RHUnk0051e5e0 *)sector)->Unk0051e700(file);
        sectors.InsertLast(sector);
    }
    unsigned short jumpCount;
    file.Access(&jumpCount, 2);
    for (unsigned short j = 0; j < jumpCount; ++j)
    {
        RHUnk0051e1e0 *first = new RHUnk0051e1e0;
        first->Unk0051e230(file, sectors);
        RHUnk0051e1e0 *second = new RHUnk0051e1e0;
        second->Unk0051e230(file, sectors);
        first->m_other = second;
        second->m_other = first;
        bool mode;
        file.Access(&mode, 1);
        first->m_mode = mode;
        second->m_mode = mode;
        first->m_layer = second->m_sector->m_layer;
        first->m_owner = second->m_sector->m_98;
        void *value = first;
        ((RHUnk004e5270 *)((char *)first->m_owner + 0xc8))->InsertLast(value);
        second->m_layer = first->m_sector->m_layer;
        second->m_owner = first->m_sector->m_98;
        value = second;
        ((RHUnk004e5270 *)((char *)second->m_owner + 0xc8))->InsertLast(value);
        FUN_004ed690(first, first->m_layer, true);
        FUN_004ed690(second, second->m_layer, true);
        RHUnk0051b6e0 *gate = new RHUnk0051b6e0(first, second);
        value = gate;
        m_gates.InsertLast(value);
        first->m_gate = gate;
        second->m_gate = gate;
    }
    for (unsigned short k = 0; k < sectorCount; ++k)
    {
        sectors.GoTo(k);
        RHUnk0051e5e0 *sector = (RHUnk0051e5e0 *)sectors.m_current->m_data;
        sector->Unk0051e800();
        FUN_004e8bd0(sector, sector->m_layer, true);
        if (sector->m_lines.size() == 0)
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x27da,
                // STRING: GAME 0x006afdd0
                "AUF WIEDERSEHEN : Jump-zone (%f,%f) has no jump-line !",
                ((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060cef0(0).m_x,
                ((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060cef0(0).m_y);
    }
    FUN_005e20c0(file);
}

// Parked: word-argument registers and sector-constructor cleanup scheduling differ.
// STUB: GAME 0x004fb8e0
void RHFastFindGrid::InitializeScriptStuffFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x47554c50, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk00522470 *point = new RHUnk00522470;
        point->Unk005224d0(file);
        FUN_004ebfe0(point, point->m_layer, true);
        void *value = point ? (char *)point + 0x14 : 0;
        (*(RHFastFindPointerArray *)((char *)this + 0x40e0)).InsertLast(value);
    }
    file.Access(&count, 2);
    for (unsigned short j = 0; j < count; ++j)
    {
        RHSectorScript *sector = new RHSectorScript;
        sector->InitializeFromMissionStream(file);
        if (!sector->m_active)
            sector->m_flags &= ~0x80;
        if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() >= 3)
        {
            FUN_004e8bd0(sector, sector->m_layer, true);
            FUN_004e99e0(sector, sector->m_layer, true);
        }
        else
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x284d,
                // STRING: GAME 0x006afe08
                "ACHTUNG : Script sector with less than 3 points !");
        void *value = sector ? (char *)sector + 0xb8 : 0;
        (*(RHFastFindGateArray *)((char *)this + 0x40e0)).InsertLast(value, false);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004fbc30
void RHFastFindGrid::InitializeMaskFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x46414345, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned short layer;
        file.Access(&layer, 2);
        RHMask *mask = new RHMask;
        mask->InitializeFromProtoStream(file, this);
        FUN_004eda80(mask, layer, true);
        if ((unsigned char)(mask->m_flags >> 1) & 1)
            FUN_004eda80(mask, m_layerCount, false);
    }
    FUN_005e20c0(file);
}

#include "RHUnk00613e90.h"
#include "RHActorAreaCalls.h"

#include "RHUnk00571160Position.h"

struct RHFastFindAreaPlane
{
    undefined m_00[0xf4];
    float m_f4;
    float m_f8;
    float m_fc;
};


// FUNCTION: GAME 0x004fbd30
void RHFastFindGrid::Convert2DTo3D(RHUnk00613e90 &point, const SBGeoPoint2D &position, int type)
{
    float height = (float)(m_height << 6);
    RHUnk00613e90 from(position.X(), height, height - position.Y());
    RHUnk00613e90 to(position.X(), position.Y(), 0.0f);
    void *obstacle;
    if (IsReachableImpact(from, to, point, obstacle, type))
        point = to;
}

// FUNCTION: GAME 0x004fbdd0
RHUnk00613e90 RHFastFindGrid::PositionToPoint3D(RHUnk00571160Position &position)
{
    SBGeoPoint2D point;
    RHUnk00613e90 result;
    point.m_x = position.x;
    point.m_y = position.y;
    RHFastFindAreaPlane *plane = 0;
    if (position.area && (unsigned char)(*(unsigned long *)((char *)position.area + 0x30) >> 1) & 1)
        plane = (RHFastFindAreaPlane *)((RHActorAreaCalls *)position.area)->FUN_0057d800(point);
    float z;
    if (!plane)
        z = 0.0f;
    else
        z = (plane->m_f4 * position.x + position.y * plane->m_f8 + plane->m_fc) / (1.0f - plane->m_f8);
    result.x = position.x;
    result.y = z + position.y;
    result.z = z;
    return result;
}

// FUNCTION: GAME 0x004fbec0
bool RHUnkPathGeometry::Unk004fbec0(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    unsigned short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = 0xffff;
        else
        {
            index = *(unsigned short *)((char *)value + 0x38);
            if (index >= grid.m_sectors.size())
            {
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2928,
                    // STRING: GAME 0x006afe3c
                    "VERBOTEN : Serializing unknown sector.");
            }
        }
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x292c, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2930, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index != 0xffff)
        {
            if (index >= grid.m_sectors.size())
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2936, "VERBOTEN : Serializing unknown sector.");
            value = grid.m_sectors.m_first[index];
            return true;
        }
        value = 0;
    }
    return true;
}

// FUNCTION: GAME 0x004fc030
bool RHUnkPathGeometry::Unk004fc030(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = grid.m_gates.Find(value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2953, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2957, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_gates.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x004fc180
bool RHUnkPathGeometry::Unk004fc180(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = grid.m_projectionAreas.Find(value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2976, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x297a, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_projectionAreas.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x004fc2d0
bool RHUnkPathGeometry::Unk004fc2d0(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = *(short *)((char *)value + 4) - 1;
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2998, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x299c, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_layers->m_obstacles[index];
    }
    return true;
}

// FUNCTION: GAME 0x004fc3b0
bool RHFastFindGrid::SerializeLinePointer(SBFile &file, void *&value)
{
    unsigned short layerIndex;
    short lineIndex;
    if (!file.m_bLoading)
    {
        if (value == 0)
        {
            lineIndex = -1;
            layerIndex = 0xffff;
        }
        else
        {
            bool found = false;
            for (unsigned short i = 0; i < m_layerCount; ++i)
            {
                unsigned short lineCount = m_layers[i].m_lineCount;
                for (unsigned short j = 0; j < lineCount; ++j)
                {
                    found = m_layers[i].m_lines[j] == value;
                    if (found)
                    {
                        layerIndex = i;
                        lineIndex = j;
                        break;
                    }
                }
                if (found)
                    break;
            }
        }
        if (file.Access(&layerIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29da, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&lineIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29db, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&layerIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29df, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&lineIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29e0, "Serialize failed reason is %s", reason);
            return false;
        }
        if (lineIndex == -1)
        {
            value = 0;
            return true;
        }
        value = m_layers[layerIndex].m_lines[lineIndex];
    }
    return true;
}

// FUNCTION: GAME 0x004fdb90
inline RHFastFindRepulsive &RHFastFindRepulsive::operator=(const RHFastFindRepulsive &other)
{
    *(SBGeoPoint2D *)((char *)this + 4) = *(const SBGeoPoint2D *)(&other ? (const char *)&other + 4 : 0);
    *(int *)((char *)this + 0xc) = *(const int *)((const char *)&other + 0xc);
    *((char *)this + 0x10) = *((const char *)&other + 0x10);
    ((RHUnk005fc3b0 *)&m_14)->FUN_005fc430(other.m_14);
    ((RHUnk005fc3b0 *)&m_1c)->FUN_005fc430(other.m_1c);
    m_24 = other.m_24;
    m_28 = other.m_28;
    m_2c = other.m_2c;
    m_30 = other.m_30;
    m_34 = other.m_34;
    m_35 = other.m_35;
    m_36 = other.m_36;
    m_37 = other.m_37;
    m_38 = other.m_38;
    m_id = other.m_id;
    return *this;
}

// FUNCTION: GAME 0x004fd680
void FUN_004fd680(RHUnk00520ae0 *destination, const RHUnk00520ae0 &other)
{
    new (destination) RHUnk00520ae0(other);
}

class RHUnk004fd070Item
{
public:
    virtual ~RHUnk004fd070Item();
    char m_04[0x3c];
};

class RHUnk004fd070
{
public:
    char m_00[4];
    RHUnk004fd070Item *m_first;
    RHUnk004fd070Item *m_last;
    RHUnk004fd070Item *m_end;
    ~RHUnk004fd070();
};

DECOMP_SIZE_ASSERT(RHUnk004fd070Item, 0x40)

// FUNCTION: GAME 0x004fd070
RHUnk004fd070::~RHUnk004fd070()
{
    RHUnk004fd070Item *last = m_last;
    for (RHUnk004fd070Item *item = m_first; item != last; ++item)
        item->~RHUnk004fd070Item();
    ::operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// FUNCTION: GAME 0x004fd0c0
void RHUnk004fd0c0::Insert(RHFastFindRepulsive *position, unsigned count, const RHFastFindRepulsive &value)
{
    if ((unsigned)(m_end - m_last) < count)
    {
        unsigned capacity = Size() + (count < Size() ? Size() : count);
        RHFastFindRepulsive *storage = std::allocator<RHFastFindRepulsive>().allocate(capacity, 0);
        RHFastFindRepulsive *destination = Copy(m_first, position, storage);
        Fill(destination, count, value);
        Copy(position, m_last, destination + count);
        RHFastFindRepulsive *last = m_last;
        for (RHFastFindRepulsive *destroyed = m_first; destroyed != last; ++destroyed)
            ((RHUnk00520ae0 *)destroyed)->~RHUnk00520ae0();
        ::operator delete(m_first);
        m_end = storage + capacity;
        m_last = storage + Size() + count;
        m_first = storage;
    }
    else if ((unsigned)(m_last - position) < count)
    {
        Copy(position, m_last, position + count);
        Fill(m_last, count - (m_last - position), value);
        std::fill(position, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        Copy(m_last - count, m_last, m_last);
        std::copy_backward(position, m_last - count, m_last);
        std::fill(position, position + count, value);
        m_last += count;
    }
}

#include "RHCampaignArrayOps.h"
#include "RHFastFindRecords.h"

DECOMP_SIZE_ASSERT(RHFastFindClearedWordRecord, 0x20)
DECOMP_SIZE_ASSERT(RHFastFindClearedPointerRecord, 0x20)
DECOMP_SIZE_ASSERT(RHUnk004fd7f0, 0xc0)
DECOMP_SIZE_ASSERT(RHUnk004fda20, 0xa0)
DECOMP_SIZE_ASSERT(RHUnk004fe200, 0x10)
DECOMP_SIZE_ASSERT(RHUnk004fe260, 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe200, m_4) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe200, m_8) == 8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe200, m_c) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe260, m_4) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe260, m_8) == 8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004fe260, m_c) == 0xc)

class RHFastFindClearedArray
{
public:
    std::vector<unsigned short> m_values;
    char m_10[0x10];
    ~RHFastFindClearedArray()
    {
        void (RHCampaignArrayOps::*clear)() = &RHCampaignArrayOps::FUN_0044ea70;
        (((RHCampaignArrayOps *)this)->*clear)();
    }
};

class RHFastFindClearedIntegerArray
{
public:
    std::vector<unsigned short> m_values;
    char m_10[0x10];
    ~RHFastFindClearedIntegerArray()
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)this)->*erase)((int *)m_values.begin(), (int *)m_values.end());
    }
};

class RHFastFindCachedRecordC0
{
public:
    RHFastFindClearedArray m_00;
    RHFastFindClearedArray m_20;
    RHFastFindClearedArray m_40;
    RHFastFindClearedArray m_60;
    RHFastFindClearedArray m_80;
    RHFastFindClearedArray m_a0;
};

class RHFastFindCachedRecordA0
{
public:
    RHFastFindClearedIntegerArray m_00;
    RHFastFindClearedArray m_20;
    RHFastFindClearedArray m_40;
    RHFastFindClearedArray m_60;
    RHFastFindClearedArray m_80;
};

class RHUnk004fd3d0
{
public:
    std::vector<RHUnk004fd7f0> m_values;
    char m_10[0xc];
    RHFastFindCachedRecordC0 m_1c;
    ~RHUnk004fd3d0();
};

// Parked: cached-array cleanup emits extra EH-state and temporary-pointer stores.
// STUB: GAME 0x004fd3d0
RHUnk004fd3d0::~RHUnk004fd3d0()
{
    m_values.erase(m_values.begin(), m_values.end());
}

class RHUnk004fd530
{
public:
    std::vector<RHUnk004fda20> m_values;
    char m_10[0xc];
    RHFastFindCachedRecordA0 m_1c;
    ~RHUnk004fd530();
};

DECOMP_SIZE_ASSERT(RHFastFindClearedArray, 0x20)
DECOMP_SIZE_ASSERT(RHFastFindClearedIntegerArray, 0x20)
DECOMP_SIZE_ASSERT(RHFastFindCachedRecordC0, 0xc0)
DECOMP_SIZE_ASSERT(RHFastFindCachedRecordA0, 0xa0)
DECOMP_SIZE_ASSERT(RHUnk004fd3d0, 0xdc)
DECOMP_SIZE_ASSERT(RHUnk004fd530, 0xbc)

// Parked: cached-array cleanup emits extra EH-state and temporary-pointer stores.
// STUB: GAME 0x004fd530
RHUnk004fd530::~RHUnk004fd530()
{
    m_values.erase(m_values.begin(), m_values.end());
}

class RHFastFindDefaultArray
{
public:
    RHFastFindDefaultArray(const std::allocator<void *> &allocator = std::allocator<void *>())
        : m_values(allocator), m_changed(true)
    {
    }

    std::vector<void *> m_values;
    void **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    void *m_value;
};

class RHUnk004fd750
{
public:
    RHFastFindDefaultArray m_00;
    RHFastFindDefaultArray m_20;
    RHFastFindDefaultArray m_40;
    RHFastFindDefaultArray m_60;
    RHFastFindDefaultArray m_80;
    RHFastFindDefaultArray m_a0;
    RHUnk004fd750();
};

// FUNCTION: GAME 0x004fd750
RHUnk004fd750::RHUnk004fd750()
{
}

// Parked at 0.5762: nested cleanup EH states, array temporaries and destructor inlining differ.
// STUB: GAME 0x004fd7f0
RHUnk004fd7f0::~RHUnk004fd7f0()
{
}

// FUNCTION: GAME 0x004fd9a0
RHUnk004fda20::RHUnk004fda20()
{
}

// Parked at 0.6299: nested cleanup EH states, receiver registers and destructor inlining differ.
// STUB: GAME 0x004fda20
RHUnk004fda20::~RHUnk004fda20()
{
}

// FUNCTION: GAME 0x004fdc20
RHFastFindRepulsiveBase &RHFastFindRepulsiveBase::Unk004fdc20(const RHFastFindRepulsiveBase &other)
{
    *(SBGeoPoint2D *)((char *)this + 4) = *(const SBGeoPoint2D *)(&other ? (const char *)&other + 4 : 0);
    *(int *)((char *)this + 0xc) = *(const int *)((const char *)&other + 0xc);
    *((char *)this + 0x10) = *((const char *)&other + 0x10);
    return *this;
}

class RHUnk004fdc90
{
public:
    void FUN_004fdc90();
    int m_0;
    RHUnk004fd7f0 *m_4;
    RHUnk004fd7f0 *m_8;
    RHUnk004fd7f0 *m_c;
};

// FUNCTION: GAME 0x004fdc90
void RHUnk004fdc90::FUN_004fdc90()
{
    RHUnk004fd7f0 *last = m_8;
    RHUnk004fd7f0 *first = m_4;
    for (; first != last; ++first)
        first->~RHUnk004fd7f0();
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}

class RHUnk004fdf40
{
public:
    void FUN_004fdf40();
    int m_0;
    RHUnk004fda20 *m_4;
    RHUnk004fda20 *m_8;
    RHUnk004fda20 *m_c;
};

// FUNCTION: GAME 0x004fdf40
void RHUnk004fdf40::FUN_004fdf40()
{
    RHUnk004fda20 *last = m_8;
    RHUnk004fda20 *first = m_4;
    for (; first != last; ++first)
        first->~RHUnk004fda20();
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}

#include "RHCopyPointers.h"

__forceinline void AssignFastFindIntegers(RHFastFindPointerArray &destination,
    const RHFastFindPointerArray &source)
{
    if (&source != &destination)
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)&destination)->*erase)((int *)destination.m_first, (int *)destination.m_last);
        ((SBResourceSurfaceArray *)&destination)->Assign(*(const SBResourceSurfaceArray *)&source, 0);
    }
}

__forceinline void AssignFastFindPointers(RHFastFindPointerArray &destination,
    const RHFastFindPointerArray &source)
{
    if (&source != &destination)
    {
        void **last = FUN_004598e0(destination.end(), destination.end(), destination.begin());
        ((RHScriptFXArray *)&destination)->Unk005008e0(last, destination.end());
        destination.m_last = last;
        ((SBResourceSurfaceArray *)&destination)->Assign(*(const SBResourceSurfaceArray *)&source, 0);
    }
}

__forceinline void AssignFastFindPlain(RHFastFindPointerArray &destination,
    const RHFastFindPointerArray &source)
{
    if (&source != &destination)
    {
        void **last = std::copy(destination.end(), destination.end(), destination.begin());
        ((RHScriptFXArray *)&destination)->Unk005008e0(last, destination.end());
        destination.m_last = last;
        ((SBResourceSurfaceArray *)&destination)->Assign(*(const SBResourceSurfaceArray *)&source, 0);
    }
}

// SIZE 0xc0
struct RHFastFindRecordC0
{
    char m_data[0xc0];
};
typedef RHUnk004fda20 RHFastFindRecordA0;

DECOMP_SIZE_ASSERT(RHFastFindRangeArray, 0x20)
DECOMP_SIZE_ASSERT(RHFastFindRecordC0, 0xc0)
DECOMP_SIZE_ASSERT(RHFastFindRecordA0, 0xa0)

// TEMPLATE: GAME 0x0051d120 FOLDED
// ??1RHFastFindRangeArray@@QAE@XZ

// TEMPLATE: GAME 0x0051d120 FOLDED
// ??1SBResourceSurfaceArray@@QAE@XZ

// LIBRARY: GAME 0x00570330 FOLDED
// ??1?$vector@KV?$allocator@K@std@@@std@@QAE@XZ

void FUN_004fe9d0(RHFastFindRecordC0 *destination, const RHFastFindRecordC0 &value);

// FUNCTION: GAME 0x004feb10
void FUN_004feb10(RHFastFindRecordA0 *destination, const RHFastFindRecordA0 &value)
{
    new (destination) RHFastFindRecordA0(value);
}

class RHFastFindRecordArray
{
public:
    RHFastFindRecordC0 *Unk004fe340(const RHFastFindRecordC0 *first, const RHFastFindRecordC0 *last,
        RHFastFindRecordC0 *destination);
    void Unk004fe380(RHFastFindRecordC0 *destination, unsigned int count, const RHFastFindRecordC0 &value);
    RHFastFindRecordA0 *Unk004fe3b0(const RHFastFindRecordA0 *first, const RHFastFindRecordA0 *last,
        RHFastFindRecordA0 *destination);
    void Unk004fe3f0(RHFastFindRecordA0 *destination, unsigned int count, const RHFastFindRecordA0 &value);
    static void FUN_004fe480(RHFastFindRecordC0 *first, RHFastFindRecordC0 *last,
        const RHFastFindRecordC0 &value);
    static RHFastFindRecordC0 *FUN_004fe5e0(const RHFastFindRecordC0 *first,
        const RHFastFindRecordC0 *last, RHFastFindRecordC0 *destination);
    static void FUN_004fe750(RHFastFindRecordA0 *first, RHFastFindRecordA0 *last,
        const RHFastFindRecordA0 &value);
    static RHFastFindRecordA0 *FUN_004fe880(const RHFastFindRecordA0 *first,
        const RHFastFindRecordA0 *last, RHFastFindRecordA0 *destination);
};

inline void RHUnk004fe260::Insert(RHUnk004fda20 *position, unsigned count, const RHUnk004fda20 &value)
{
    RHFastFindRecordArray *operations = (RHFastFindRecordArray *)this;
    if ((unsigned)(m_c - m_8) < count)
    {
        unsigned capacity = FUN_004fe280() + (count < Size() ? Size() : count);
        RHUnk004fda20 *storage = std::allocator<RHUnk004fda20>().allocate(capacity, 0);
        RHUnk004fda20 *destination = operations->Unk004fe3b0(m_4, position, storage);
        operations->Unk004fe3f0(destination, count, value);
        operations->Unk004fe3b0(position, m_8, destination + count);
        FUN_004fe2b0(m_4, m_8);
        ::operator delete(m_4);
        m_c = storage + capacity;
        m_8 = storage + FUN_004fe280() + count;
        m_4 = storage;
    }
    else if ((unsigned)(m_8 - position) < count)
    {
        operations->Unk004fe3b0(position, m_8, position + count);
        operations->Unk004fe3f0(m_8, count - (m_8 - position), value);
        RHFastFindRecordArray::FUN_004fe750(position, m_8, value);
        m_8 += count;
    }
    else if (count > 0)
    {
        operations->Unk004fe3b0(m_8 - count, m_8, m_8);
        RHFastFindRecordArray::FUN_004fe880(position, m_8 - count, m_8);
        RHFastFindRecordArray::FUN_004fe750(position, position + count, value);
        m_8 += count;
    }
}

// FUNCTION: GAME 0x004fdf80
void RHUnk004fe260::Resize(unsigned count, const RHUnk004fda20 &value)
{
    if (Size() < count)
        Insert(m_8, count - Size(), value);
    else if (count < Size())
    {
        RHUnk004fda20 *destination = std::copy(m_8, m_8, m_4 + count);
        RHUnk004fda20 *last = m_8;
        for (RHUnk004fda20 *destroyed = destination; destroyed != last; ++destroyed)
            destroyed->~RHUnk004fda20();
        m_8 = destination;
    }
}

// FUNCTION: GAME 0x004fe340
RHFastFindRecordC0 *RHFastFindRecordArray::Unk004fe340(const RHFastFindRecordC0 *first,
    const RHFastFindRecordC0 *last, RHFastFindRecordC0 *destination)
{
    for (; first != last; ++destination, ++first)
        FUN_004fe9d0(destination, *first);
    return destination;
}

// FUNCTION: GAME 0x004fe380
void RHFastFindRecordArray::Unk004fe380(RHFastFindRecordC0 *destination, unsigned int count,
    const RHFastFindRecordC0 &value)
{
    for (; count > 0; --count, ++destination)
        FUN_004fe9d0(destination, value);
}

// FUNCTION: GAME 0x004fe3b0
RHFastFindRecordA0 *RHFastFindRecordArray::Unk004fe3b0(const RHFastFindRecordA0 *first,
    const RHFastFindRecordA0 *last, RHFastFindRecordA0 *destination)
{
    for (; first != last; ++destination, ++first)
        FUN_004feb10(destination, *first);
    return destination;
}

// FUNCTION: GAME 0x004fe3f0
void RHFastFindRecordArray::Unk004fe3f0(RHFastFindRecordA0 *destination, unsigned int count,
    const RHFastFindRecordA0 &value)
{
    for (; count > 0; --count, ++destination)
        FUN_004feb10(destination, value);
}

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@KV?$allocator@K@std@@@std@@IAEPAKPBK0PAK@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHPCDescription@@V?$allocator@PAVRHPCDescription@@@std@@@std@@IAEPAPAVRHPCDescription@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAXV?$allocator@PAX@std@@@std@@IAEPAPAXPBQAX0PAPAX@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHReceiverInterface@@V?$allocator@PAVRHReceiverInterface@@@std@@@std@@IAEPAPAVRHReceiverInterface@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHUnk0051aa00@@V?$allocator@PAVRHUnk0051aa00@@@std@@@std@@IAEPAPAVRHUnk0051aa00@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHMission@@V?$allocator@PAVRHMission@@@std@@@std@@IAEPAPAVRHMission@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHSaveGame@@V?$allocator@PAVRHSaveGame@@@std@@@std@@IAEPAPAVRHSaveGame@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@HV?$allocator@H@std@@@std@@IAEPAHPBH0PAH@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?Unk004fe420@RHScriptFXArray@@QAEPAPAXPAPAX00@Z
void **RHScriptFXArray::Unk004fe420(void **first, void **last, void **destination)
{
    for (; first != last; ++first, ++destination)
        if (destination)
            *destination = *first;
    return destination;
}

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@KV?$allocator@K@std@@@std@@IAEXPAKIABK@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@PAVRHPCDescription@@V?$allocator@PAVRHPCDescription@@@std@@@std@@IAEXPAPAVRHPCDescription@@IABQAV3@@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@PAVRHReceiverInterface@@V?$allocator@PAVRHReceiverInterface@@@std@@@std@@IAEXPAPAVRHReceiverInterface@@IABQAV3@@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@PAVRHUnk0051aa00@@V?$allocator@PAVRHUnk0051aa00@@@std@@@std@@IAEXPAPAVRHUnk0051aa00@@IABQAV3@@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@PAVRHSaveGame@@V?$allocator@PAVRHSaveGame@@@std@@@std@@IAEXPAPAVRHSaveGame@@IABQAV3@@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?Unk004fe450@RHScriptFXArray@@QAEXPAPAXIABQAX@Z
void RHScriptFXArray::Unk004fe450(void **destination, unsigned int count, void *const &value)
{
    for (; count > 0; --count, ++destination)
        if (destination)
            *destination = value;
}

__forceinline void AssignFastFindC0(RHFastFindRecordC0 &destination, const RHFastFindRecordC0 &source)
{
    RHFastFindPointerArray *output = (RHFastFindPointerArray *)&destination;
    const RHFastFindPointerArray *input = (const RHFastFindPointerArray *)&source;
    AssignFastFindIntegers(output[0], input[0]);
    AssignFastFindIntegers(output[1], input[1]);
    AssignFastFindIntegers(output[2], input[2]);
    AssignFastFindIntegers(output[3], input[3]);
    AssignFastFindPointers(output[4], input[4]);
    AssignFastFindPointers(output[5], input[5]);
}

__forceinline void AssignFastFindA0(RHFastFindRecordA0 &destination, const RHFastFindRecordA0 &source)
{
    RHFastFindPointerArray *output = (RHFastFindPointerArray *)&destination;
    const RHFastFindPointerArray *input = (const RHFastFindPointerArray *)&source;
    AssignFastFindIntegers(output[0], input[0]);
    AssignFastFindIntegers(output[1], input[1]);
    AssignFastFindIntegers(output[2], input[2]);
    AssignFastFindPointers(output[3], input[3]);
    AssignFastFindPlain(output[4], input[4]);
}

// FUNCTION: GAME 0x004fe480
void RHFastFindRecordArray::FUN_004fe480(RHFastFindRecordC0 *first, RHFastFindRecordC0 *last,
    const RHFastFindRecordC0 &value)
{
    for (; first != last; ++first)
        AssignFastFindC0(*first, value);
}

// FUNCTION: GAME 0x004fe5e0
RHFastFindRecordC0 *RHFastFindRecordArray::FUN_004fe5e0(const RHFastFindRecordC0 *first,
    const RHFastFindRecordC0 *last, RHFastFindRecordC0 *destination)
{
    while (first != last)
        AssignFastFindC0(*--destination, *--last);
    return destination;
}

// FUNCTION: GAME 0x004fe750
void RHFastFindRecordArray::FUN_004fe750(RHFastFindRecordA0 *first, RHFastFindRecordA0 *last,
    const RHFastFindRecordA0 &value)
{
    for (; first != last; ++first)
        AssignFastFindA0(*first, value);
}

// FUNCTION: GAME 0x004fe880
RHFastFindRecordA0 *RHFastFindRecordArray::FUN_004fe880(const RHFastFindRecordA0 *first,
    const RHFastFindRecordA0 *last, RHFastFindRecordA0 *destination)
{
    while (first != last)
        AssignFastFindA0(*--destination, *--last);
    return destination;
}

// FUNCTION: GAME 0x004fec70
RHFastFindAssignmentC0 &RHFastFindAssignmentC0::FUN_004fec70(const RHFastFindAssignmentC0 &source)
{
    AssignFastFindIntegers(m_arrays[0], source.m_arrays[0]);
    AssignFastFindIntegers(m_arrays[1], source.m_arrays[1]);
    AssignFastFindIntegers(m_arrays[2], source.m_arrays[2]);
    AssignFastFindPointers(m_arrays[3], source.m_arrays[3]);
    AssignFastFindPointers(m_arrays[4], source.m_arrays[4]);
    AssignFastFindPlain(m_arrays[5], source.m_arrays[5]);
    return *this;
}

// FUNCTION: GAME 0x004fedb0
RHFastFindAssignmentA0 &RHFastFindAssignmentA0::FUN_004fedb0(const RHFastFindAssignmentA0 &source)
{
    AssignFastFindIntegers(m_arrays[0], source.m_arrays[0]);
    AssignFastFindIntegers(m_arrays[1], source.m_arrays[1]);
    AssignFastFindPointers(m_arrays[2], source.m_arrays[2]);
    AssignFastFindPointers(m_arrays[3], source.m_arrays[3]);
    if (&source.m_arrays[4] != &m_arrays[4])
    {
        RHFastFindPointerArray &array = m_arrays[4];
        typedef std::vector<void *> Values;
        ((Values *)&array)->erase(array.begin(), array.end());
        ((SBResourceSurfaceArray *)&array)->Assign(*(const SBResourceSurfaceArray *)&source.m_arrays[4], 0);
    }
    return *this;
}

inline void AssignClearedFastFindArray(RHFastFindPointerArray &destination,
    const RHFastFindPointerArray &source)
{
    if (&source != &destination)
    {
        ((RHCampaignArrayOps *)&destination)->FUN_0044ea70();
        ((SBResourceSurfaceArray *)&destination)->Assign((const SBResourceSurfaceArray &)source, 0);
    }
}

template <class T>
inline T *CopyClearedFastFindRecords(T *first, T *last, T *destination)
{
    for (; first != last; ++destination, ++first)
    {
        RHFastFindPointerArray *output = (RHFastFindPointerArray *)destination;
        const RHFastFindPointerArray *input = (const RHFastFindPointerArray *)first;
        AssignClearedFastFindArray(output[0], input[0]);
        AssignClearedFastFindArray(output[1], input[1]);
        AssignClearedFastFindArray(output[2], input[2]);
        output[3].FUN_004ff0a0(input[3]);
        output[4].FUN_004ff0a0(input[4]);
        if (sizeof(T) == 0xc0)
            output[5].FUN_004ff0a0(input[5]);
    }
    return destination;
}

// FUNCTION: GAME 0x004feec0
void RHUnk004fe200::FUN_004feec0()
{
    RHUnk004fd7f0 *destination = CopyClearedFastFindRecords(m_8, m_8, m_4);
    RHUnk004fd7f0 *last = m_8;
    for (RHUnk004fd7f0 *destroyed = destination; destroyed != last; ++destroyed)
        destroyed->~RHUnk004fd7f0();
    m_8 = destination;
}

// FUNCTION: GAME 0x004fefb0
void RHUnk004fe260::FUN_004fefb0()
{
    RHUnk004fda20 *destination = CopyClearedFastFindRecords(m_8, m_8, m_4);
    RHUnk004fda20 *last = m_8;
    for (RHUnk004fda20 *destroyed = destination; destroyed != last; ++destroyed)
        destroyed->~RHUnk004fda20();
    m_8 = destination;
}

#include "RHUnk0055b830Values.h"
#include "RHCampaignPointerArray.h"

// FUNCTION: GAME 0x004ff0a0
RHFastFindPointerArray &RHFastFindPointerArray::FUN_004ff0a0(const RHFastFindPointerArray &source)
{
    if (&source != this)
    {
        RHCampaignPointerArray<unsigned long> &values = *(RHCampaignPointerArray<unsigned long> *)this;
        values.erase(values.begin(), values.end());
        if (size() == 0)
        {
            unsigned position = ((RHFastFindGateArray *)this)->FUN_0059fbc0();
            int index = 0;
            int count = ((RHFastFindGateArray *)&source)->FUN_0059fbc0();
            unsigned added = ((RHFastFindGateArray *)&source)->FUN_0059fbc0();
            ((RHUnk0055b830Values *)this)->Resize(((RHFastFindGateArray *)this)->FUN_0059fbc0() + added);
            for (; index < count; ++index)
                m_first[position + index] = source.m_first[index];
            m_changed = true;
            return *this;
        }
        else
        {
            int last = ((RHFastFindGateArray *)this)->FUN_0059fbc0() - 1;
            int shifted = source.size();
            shifted += ((RHFastFindGateArray *)this)->FUN_0059fbc0();
            unsigned total = size() + source.size();
            float zero = 0;
            ((RHUnk004ff7b0 *)this)->FUN_004ff7b0(total, zero);
            m_changed = true;
            for (int destination = shifted - 1; last >= 0; --last, --destination)
                m_first[destination] = m_first[last];
            int index = 0;
            if (source.m_first != 0)
            {
                int count = source.m_last - source.m_first;
                for (; index < count; ++index)
                    m_first[index] = source.m_first[index];
            }
        }
        m_changed = true;
    }
    return *this;
}

// Parked: indexed insertion has different size caching and shift-loop register allocation.
// STUB: GAME 0x004ff400
void SBResourceSurfaceArray::Assign(const SBResourceSurfaceArray &other, unsigned position)
{
    RHFastFindPointerArray &destination = *(RHFastFindPointerArray *)this;
    const RHFastFindPointerArray &source = *(const RHFastFindPointerArray *)&other;
    int count = 0;
    if (position == destination.size())
    {
        position = ((RHFastFindGateArray *)this)->FUN_0059fbc0();
        int index = 0;
        count = ((RHFastFindGateArray *)&source)->FUN_0059fbc0();
        unsigned added = ((RHFastFindGateArray *)&source)->FUN_0059fbc0();
        unsigned total = ((RHFastFindGateArray *)this)->FUN_0059fbc0() + added;
        {
            float zero = 0;
            ((RHUnk004ff7b0 *)this)->FUN_004ff7b0(total, zero);
        }
        destination.m_changed = true;
        for (; index < count; ++index)
            destination.m_first[position + index] = source.m_first[index];
    }
    else
    {
        int oldCount = destination.size();
        int last = oldCount - 1;
        int previous = destination.size();
        count = source.size();
        unsigned total = destination.size() + source.size();
        {
            float zero = 0;
            ((RHUnk004ff7b0 *)this)->FUN_004ff7b0(total, zero);
        }
        destination.m_changed = true;
        for (; last >= (int)position; --last)
            destination.m_first[count - oldCount + previous + last] = destination.m_first[last];
        int sourceCount = source.size();
        for (int index = 0; index < sourceCount; ++index)
            destination.m_first[position + index] = source.m_first[index];
    }
    destination.m_changed = true;
}

class RHEngine;
extern RHEngine *g_pEngine;

class RHFastFindScriptSectorStorage : public RHSeqList
{
public:
    RHFastFindScriptSectorStorage(const char &allocator) : RHSeqList(allocator) {}
    ~RHFastFindScriptSectorStorage()
    {
        Clear();
        operator delete(m_head);
    }
    void Clear()
    {
        RHSectorActorIter current((RHSectorActorNode *)m_head->m_next);
        RHSectorActorNode *last = (RHSectorActorNode *)m_head;
        while (current.m_p != last)
            ((RHUnk0046eb30 *)this)->erase(RHScriptIter((RHScriptNode *)(current++).m_p));
    }
};

class RHFastFindScriptSectorList : public RHFastFindScriptSectorStorage
{
public:
    RHFastFindScriptSectorList(const char &allocator) : RHFastFindScriptSectorStorage(allocator)
    {
        m_valid = true;
    }
    ~RHFastFindScriptSectorList()
    {
        Clear();
    }
};

DECOMP_SIZE_ASSERT(RHFastFindScriptSectorList, 0x18)

// Parked at 0.4320: actor/sector traversal complete; local slots, registers and cleanup scheduling differ.
// STUB: GAME 0x004fc660
void RHFastFindGrid::FUN_004fc660()
{
    RHFastFindGrid &grid = *this;
    char allocator;
    RHFastFindScriptSectorList sectors(allocator);
    SBGeoPoint2D point;
    RHFastFindPointerArray &actors = *(RHFastFindPointerArray *)((char *)g_pEngine + 0x4918);
    unsigned short actorCount = actors.size();
    if (actorCount > 0)
    {
        unsigned offset = 0;
        unsigned count = actorCount;
        do
        {
            RHElementActor *actor = *(RHElementActor **)((char *)((RHFastFindPointerArray *)((char *)g_pEngine + 0x4918))->m_first + offset);
            char *position = *(char **)((char *)actor + 0x50);
            point = *(SBGeoPoint2D *)(position + 0x24);
            if (((SBGeoBoundingBox2D *)((char *)&grid + 0x3e84))->FUN_00608400(point))
            {
                unsigned layer = *(unsigned short *)(*(char **)((char *)actor + 0x50) + 0xde);
                int cell = (grid.m_height * layer + ((short)point.m_y >> 6)) * grid.m_width + ((short)point.m_x >> 6);
                ((RHElementGrid *)&grid)->FUN_004e89d0(&sectors, cell, 8);
                unsigned short size = sectors.m_count;
                if (size > 0)
                {
                    unsigned index = 0;
                    unsigned sectorCount = size;
                    do
                    {
                        ((RHPathQueryCalls *)&sectors)->FUN_005c8e40(index);
                        RHSectorScript *sector = (RHSectorScript *)sectors.m_current->m_data;
                        if (sector->FUN_0057ff00(actor))
                            ((RHFastFindUniqueList *)((char *)sector + 0xcc))->InsertLast(actor);
                        ++index;
                    } while (--sectorCount != 0);
                }
            }
            offset += 4;
        } while (--count != 0);
    }
}

void EmitFastFindRecordAssignments(RHFastFindRecordC0 *large, RHFastFindRecordA0 *small,
    RHFastFindAssignmentC0 *largeAssignment, RHFastFindAssignmentA0 *smallAssignment)
{
    RHFastFindRecordArray::FUN_004fe480(large, large, *large);
    RHFastFindRecordArray::FUN_004fe5e0(large, large, large);
    RHFastFindRecordArray::FUN_004fe750(small, small, *small);
    RHFastFindRecordArray::FUN_004fe880(small, small, small);
    largeAssignment->FUN_004fec70(*largeAssignment);
    smallAssignment->FUN_004fedb0(*smallAssignment);
}

// FUNCTION: GAME 0x004ff7b0
void RHUnk004ff7b0::FUN_004ff7b0(unsigned int count, const float &value)
{
    std::vector<unsigned long> &values = *(std::vector<unsigned long> *)this;
    if (values.size() < count)
        values.insert(values.end(), count - values.size(), *(const unsigned long *)&value);
    else if (count < values.size())
        values.erase(values.begin() + count, values.end());
}

// FUNCTION: GAME 0x0051aa00
RHUnk0051aa00::RHUnk0051aa00()
{
    *(int *)((char *)this + 4) = 1;
    *((char *)this + 8) = 1;
    m_8c[0] = 0;
    m_8c[1] = 0;
    m_8c[2] = 0;
    m_8c[3] = 0;
    m_b0 = 0;
    *(int *)((char *)this + 0xac) = 0;
    m_b4[0] = 0;
    *(short *)((char *)this + 0xb6) = 0;
    *(short *)((char *)this + 0xb8) = 0;
}

// FUNCTION: GAME 0x0051e1e0
RHUnk0051e1e0::RHUnk0051e1e0()
{
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::RHUnk0051f0f0();
    *(unsigned long *)this = 0x006790c0;
    *(int *)((char *)this + 0x14) = 0x400;
    *((char *)this + 0x39) = 0;
}

// FUNCTION: GAME 0x0051e200
void *RHUnk0051e1e0::FUN_0051e200(unsigned flags)
{
    this->~RHUnk0051e1e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051e220
RHUnk0051e1e0::~RHUnk0051e1e0()
{
    *(unsigned long *)this = 0x006790c0;
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::~RHUnk0051f0f0();
}

void EmitRHUnk0051e1e0(void *storage)
{
    ((RHUnk0051e1e0 *)storage)->RHUnk0051e1e0::~RHUnk0051e1e0();
}

DECOMP_SIZE_ASSERT(RHUnk0051f0f0, 0x20)

// FUNCTION: GAME 0x0051f0f0
RHUnk0051f0f0::RHUnk0051f0f0()
    : SBGeoSegment2D(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f))
{
    *(unsigned *)this = 0x6790e0;
    m_14 = 0;
    m_18 = true;
    m_1c = 0;
}

// FUNCTION: GAME 0x0051f190
void *RHUnk0051f0f0::FUN_0051f190(unsigned flags)
{
    this->RHUnk0051f0f0::~RHUnk0051f0f0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051f1b0
RHUnk0051f0f0::~RHUnk0051f0f0()
{
    *(unsigned *)this = 0x6790e0;
}

// FUNCTION: GAME 0x0051f4d0
RHFastFindLine::RHFastFindLine()
{
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::RHUnk0051f0f0();
    *(unsigned *)this = 0x6790e8;
    *(unsigned *)((char *)this + 0x24) = 0;
    *(unsigned *)((char *)this + 0x28) = 0;
    *(unsigned short *)((char *)this + 0x20) = 0;
    *(unsigned *)((char *)this + 0x14) = 0xc;
}

// FUNCTION: GAME 0x0051f500
void *RHFastFindLine::FUN_0051f500(unsigned flags)
{
    this->~RHFastFindLine();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051f520
RHFastFindLine::~RHFastFindLine()
{
    *(unsigned *)this = 0x6790e8;
    ((RHUnk0051f0f0 *)this)->RHUnk0051f0f0::~RHUnk0051f0f0();
}

void EmitRHFastFindLine(void *storage)
{
    ((RHFastFindLine *)storage)->RHFastFindLine::~RHFastFindLine();
}

// FUNCTION: GAME 0x0051e5e0
RHUnk0051e5e0::RHUnk0051e5e0()
{
    ((RHSector *)this)->RHSector::RHSector();
    char firstAllocator;
    char secondAllocator;
    m_lines.Initialize(firstAllocator);
    (*(RHFastFindPointerArray *)((char *)this + 0x78)).Initialize(secondAllocator);
    *(unsigned long *)this = 0x006790c8;
    *(int *)((char *)this + 0x30) = 0x8040;
}

// FUNCTION: GAME 0x0051e700
int RHUnk0051e5e0::Unk0051e700(SBFile &file)
{
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    ((RHSector *)this)->RHSector::Unk0057cd60(file, false);
    unsigned short sector;
    file.Access(&sector, 2);
    *(void **)((char *)this + 0x98) = RHFastFindLookup(sector);
    file.Access(&m_layer, 2);
    file.Access((char *)this + 0x9c, 1);
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}

// Parked: actor and virtual-argument live ranges select different registers and cleanup tails.
// STUB: GAME 0x0051e7b0
bool RHUnk0051e5e0::FUN_0051e7b0(unsigned int index, RHElementActor *actor, bool mode)
{
    RHUnk0051e1e0 *line = (RHUnk0051e1e0 *)m_lines.m_first[index];
    if (line->m_owner == *(void **)((char *)*(void **)((char *)actor + 0x50) + 0xe0))
    {
        RHUnk0051b6e0 *gate = (RHUnk0051b6e0 *)line->m_gate;
        if (gate->FUN_0051abe0(line == gate->m_8c, actor, mode, true, false))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0051e800
void RHUnk0051e5e0::Unk0051e800()
{
    unsigned int count = m_lines.size();
    float zero = 0;
    {
        RHUnk004ff7b0 &distances = *(RHUnk004ff7b0 *)((char *)this + 0x78);
        distances.FUN_004ff7b0(count, zero);
        *((char *)&distances + 0x14) = 1;
    }
    for (unsigned int i = 0; i < count; ++i)
    {
        RHUnk0051e1e0 *line = (RHUnk0051e1e0 *)m_lines.m_first[i];
        float height = *(float *)((char *)line->m_other + 0x30);
        float *destination = (*(RHUnk004ff7b0 *)((char *)this + 0x78)).m_first;
        float distance = height - *(float *)((char *)line + 0x30);
        destination[i] = distance;
        if (distance < (-40.0f) && (*((char *)this + 0x9c) || *((char *)line->m_other->m_sector + 0x9c)))
            *((char *)line + 0x39) = 1;
    }
}

// FUNCTION: GAME 0x0051e890
float RHUnk0051e5e0::FUN_0051e890(RHUnk0051e1e0 *line)
{
    unsigned int count = m_lines.size();
    for (unsigned int index = 0; index < count; ++index)
        if (m_lines.m_first[index] == line)
            return (*(RHUnk004ff7b0 *)((char *)this + 0x78)).m_first[index];
    return 0.0f;
}

// FUNCTION: GAME 0x0051faf0
int RHFastFindLine::FUN_0051faf0(SBFile &file, RHFastFindPointerArray &sectors)
{
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    ((float *)m_00)[1] = x;
    ((float *)m_00)[2] = y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    ((float *)m_00)[3] = x;
    ((float *)m_00)[4] = y;
    unsigned short index;
    file.Access(&index, 2);
    if (index == 0xffff)
        *(void **)(m_00 + 0x24) = 0;
    else
        *(void **)(m_00 + 0x24) = sectors.m_first[index];
    file.Access(&index, 2);
    if (index == 0xffff)
        *(void **)(m_00 + 0x28) = 0;
    else
        *(void **)(m_00 + 0x28) = sectors.m_first[index];
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}

// FUNCTION: GAME 0x00520ae0
RHUnk00520ae0::RHUnk00520ae0() : RHUnk005209d0(6)
{
    m_35 = true;
    m_36 = true;
    m_37 = true;
    m_38 = true;
    m_id = g_unk0x006c0bcc;
    ++g_unk0x006c0bcc;
}

// FUNCTION: GAME 0x00520b60
RHUnk00520ae0::RHUnk00520ae0(const SBGeoPoint2D &point, float first, float second) : RHUnk005209d0(point, 6)
{
    ((RHMobileUnk00520c50 *)this)->FUN_00520c50(first, second);
}

// SYNTHETIC: GAME 0x004fdc50
// RHUnk00520ae0::`scalar deleting destructor'
// FUNCTION: GAME 0x004fdc70
void *RHUnk005209d0::FUN_004fdc70(unsigned flags)
{
    this->RHUnk005209d0::~RHUnk005209d0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00520bf0
RHUnk00520ae0::~RHUnk00520ae0()
{
}

// FUNCTION: GAME 0x00520c80
void RHUnk00520ae0::FUN_00520c80(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    m_0c &= ~4;
    m_14.FUN_005fc430(first);
    m_1c.FUN_005fc430(second);
    m_34 = ((const RHUnk005fc3b0 &)first).FUN_005fc680((const RHUnk005fc3b0 &)second, 1.0f) < 0.0f;
}

// FUNCTION: GAME 0x005224d0
void RHUnk00522470::Unk005224d0(SBFile &file)
{
    FUN_00520a90(file);
    unsigned short sector;
    file.Access(&sector, 2);
    file.Access(&m_layer, 2);
    void *value;
    if (sector == 0xffff)
        value = g_unk0x6c0a9c->m_4184;
    else
        value = g_unk0x6c0a9c->m_4064[sector];
    *((char *)this + 0x14) = 0;
    *(void **)((char *)this + 0x24) = value;
}

// LIBRARY: GAME 0x0059fbc0 FOLDED
// ?size@?$vector@HV?$allocator@H@std@@@std@@QBEIXZ

// LIBRARY: GAME 0x0059fbc0 FOLDED
// ?size@?$vector@KV?$allocator@K@std@@@std@@QBEIXZ

// FUNCTION: GAME 0x005df860
void RHUnk005df860::Unk005df860(const SBGeoPoint3D &first, const SBGeoPoint3D &second, const SBGeoPoint3D &third)
{
    *(SBGeoPoint3D *)this = first;
    *(SBGeoPoint3D *)((char *)this + 0xc) = second;
    *(SBGeoPoint3D *)((char *)this + 0x18) = third;
}

// FUNCTION: GAME 0x005dfa00
void RHUnk005df860::Unk005dfa00()
{
    FUN_005df8b0();
    FUN_005df900();
    FUN_005df9a0();
    FUN_005df9c0();
}

void RHFastFindGrid::Emit(SBFile &file, void *&value)
{
    FUN_004fc660();
    ((RHActorGridCalls *)this)->FUN_004f9a80(value, (RHElementActor *)value, *(SBGeoPoint2D *)value, value, 0, *(SBGeoPoint2D *)value, value, 0, 0);
    FUN_004fa080(*(RHFastFindUniqueList *)value, (RHElementActor *)value, *(SBGeoPoint2D *)value, value, 0, (RHFastFindPathGate *)value, 0);
    FUN_004ec240(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004ec450(*(RHFastFindUniqueList *)value, 0, 0);
    FUN_004ec560(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004ec700(*(RHFastFindUniqueList *)value, 0, *(RHMalignitySegment *)value, 0);
    ((RHScriptBatchCalls *)this)->Unk004ec910(value, 0, 0, 0);
    FUN_004ecb50(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004ecc60(*(RHFastFindUniqueList *)value, *(RHFastFindUniqueList *)value, *(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value);
    FUN_004ed070(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004ed370(*(RHFastFindUniqueList *)value, 0, *(RHMalignitySegment *)value, 0);
    FUN_004ed9b0(file);
    FUN_004eda80(value, 0, false);
    FUN_004edcf0(*(RHFastFindUniqueList *)value, 0, 0);
    FUN_004ede00(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, value);
    FUN_004ee120(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, value, 0);
    FUN_004ee470(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value);
    FUN_004ee770(*(RHFastFindUniqueList *)value, 0, 0);
    FUN_004ee880(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004eea50(*(RHFastFindUniqueList *)value, 0, *(RHMalignitySegment *)value, 0);
    FUN_004eec20(*(RHFastFindUniqueList *)value, 0, *(SBGeoBoundingBox2D *)value, 0);
    FUN_004eef30(*(RHFastFindUniqueList *)value, 0, *(RHMalignitySegment *)value, 0);
    FUN_004efd10(value, 0, false);
    FUN_004efe40(*(SBGeoPoint3D *)value, *(SBGeoPoint3D *)value, *(float *)value, *(float *)value);
    InitializeLiftsFromProtoStream(file);
    InitializeBuildingsFromProtoStream(file);
    InitializeSightObstaclesFromProtoStream(file);
    Serialize(file);
    DeleteStaticRepulsivePoint(0);
    InitializeTacticalInfosFromMissionStream(file);
    InitializeJumpStuffFromProtoStream(file);
    InitializeScriptStuffFromMissionStream(file);
    SerializeLinePointer(file, value);
    RHUnk005df860 plane;
    SBGeoPoint3D point(0, 0, 0);
    plane.Unk005df860(point, point, point);
    plane.Unk005dfa00();
    ((RHUnk0051e5e0 *)value)->FUN_0051e890((RHUnk0051e1e0 *)value);
    ((RHUnk0051e5e0 *)value)->FUN_0051e7b0(0, (RHElementActor *)value, false);
    m_repulsivePoints.begin()->operator=(*m_repulsivePoints.begin());
    RHUnk00520ae0 repulsive;
}
