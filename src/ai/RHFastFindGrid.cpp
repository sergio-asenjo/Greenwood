#include "SBNullstr.h"
#include "RHFastFindGrid.h"
#include "SBFilePosition.h"

extern float g_unk0x00677488;

// GLOBAL: GAME 0x006c06f0
RHFastFindTacticalArray g_unk0x006c06f0;
// GLOBAL: GAME 0x006c0718
RHFastFindTacticalArray g_unk0x006c0718;

// GLOBAL: GAME 0x006790d8
float g_unk0x006790d8 = -40.0f;

// GLOBAL: GAME 0x006c0bcc
unsigned long g_unk0x006c0bcc;

// GLOBAL: GAME 0x006c0aa8
float g_unk0x006c0aa8[2] = {0.0f, 0.0f};

// FUNCTION: GAME 0x004e5270
RHSeqList::RHSeqList(const char &allocator)
{
    m_00[0] = allocator;
    RHSeqNode *head = (RHSeqNode *)operator new(0xc);
    head->m_next = head;
    head->m_prev = head;
    m_head = head;
    m_count = 0;
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
            void *lift = new RHUnk0057e4d0;
            ((RHUnk0057e4d0 *)lift)->UnkSlot10(file, this);
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
                gate->Unk0051b2a0(file, false);
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

// Residual: target type filtering and nested-node cleanup use a different owner/list layout.
// STUB: GAME 0x004fc590
void RHFastFindGrid::FUN_004fc590()
{
    unsigned long *first = *(unsigned long **)((char *)this + 0x40e4);
    unsigned long *last = *(unsigned long **)((char *)this + 0x40e8);
    for (unsigned long *entry = first; entry && entry != last; ++entry)
    {
        void *object = (void *)*entry;
        if (object && *(int *)((char *)object + 4) == 2)
        {
            char *owner = (char *)object - 0xb8;
            RHFastFindRawNode *head = *(RHFastFindRawNode **)(owner + 0xd0);
            if (!head)
                continue;
            RHFastFindRawNode *node = head->next;
            while (node != head)
            {
                RHFastFindRawNode *next = node->next;
                node->previous->next = next;
                next->previous = node->previous;
                ::operator delete(node);
                node = next;
                --*(int *)(owner + 0xd4);
            }
            *(char *)(owner + 0xdc) = 1;
        }
    }
}

// Residual: the grid-to-cell conversion, actor filtering, and insertion path are not reconstructed.
// STUB: GAME 0x004fc660
void RHFastFindGrid::FUN_004fc660()
{
    unsigned short width = m_width;
    unsigned short height = m_height;
    if (!m_layers || width == 0 || height == 0)
        return;
    for (unsigned short layer = 0; layer < m_layerCount; ++layer)
    {
        RHFastFindLayer &current = m_layers[layer];
        for (unsigned short line = 0; line < current.m_lineCount; ++line)
        {
            void *value = current.m_lines[line];
            if (value)
                current.m_lines[line] = value;
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

// Residual: the target searches nested patch arrays and honors the patch-owned fast path.
// STUB: GAME 0x004fcfd0
bool RHFastFindGrid::FUN_004fcfd0(void *value)
{
    for (void **patch = m_patches.m_first; patch && patch != m_patches.m_last; ++patch)
    {
        void *object = *patch;
        if (!object)
            continue;
        void **first = *(void ***)((char *)object + 0x15c);
        void **last = *(void ***)((char *)object + 0x160);
        if (first)
            for (; first != last; ++first)
                if (*first == value)
                    return true;
    }
    return false;
}

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

struct RHFastFindUniqueNode
{
    RHFastFindUniqueNode *next;
    RHFastFindUniqueNode *previous;
    void *value;

    RHFastFindUniqueNode(RHFastFindUniqueNode *after, RHFastFindUniqueNode *before)
        : next(after ? after : this), previous(before ? before : this) {}
};

class RHFastFindUniqueList
{
public:
    struct Iterator
    {
        RHFastFindUniqueNode *node;
        Iterator(RHFastFindUniqueNode *value) : node(value) {}
    };

    undefined m_00[4];
    RHFastFindUniqueNode *m_head;
    int m_count;
    RHFastFindUniqueNode *m_current;
    bool m_changed;
    undefined m_11[3];
    int m_index;
    bool m_searching;
    undefined m_19[3];
    int m_found;
    void *m_value;

    int GetSize() { return m_count; }

    int Find(void *value)
    {
        RHFastFindUniqueNode *head = *(RHFastFindUniqueNode *volatile *)&m_head;
        m_value = value;
        m_searching = true;
        int count = m_count;
        *(RHFastFindUniqueNode *volatile *)&m_current = head->next;
        int index;
        for (index = 0; index < count; ++index, m_current = (*(RHFastFindUniqueNode *volatile *)&m_current)->next)
        {
            RHFastFindUniqueNode *node = m_current;
            void *value = *(void *volatile *)&m_value;
            void *current = *(void *volatile *)&node->value;
            if (current == value)
                break;
        }
        if (index < count)
        {
            m_found = index;
            m_changed = false;
            m_index = index;
        }
        else
        {
            m_changed = true;
            m_found = -1;
        }
        return m_found;
    }

    void InsertLast(void *value)
    {
        RHFastFindUniqueNode *head = m_head;
        RHFastFindUniqueNode *previous = head->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(head, previous);
        head->previous = node;
        node->previous->next = node;
        if (&node->value)
            node->value = value;
        ++m_count;
        m_changed = true;
    }

    void InsertLastExternal(void *const &value)
    {
        RHFastFindUniqueNode *head = m_head;
        RHFastFindUniqueNode *previous = head->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(head, previous);
        head->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++m_count;
        m_changed = true;
    }

    void InsertLastCall(void *const &value)
    {
        ((RHUnkListSeq *)this)->insert(RHSeqIter(m_head), (RHSequence *const &)value);
        m_changed = true;
    }

    void InsertFirst(void *value)
    {
        RHFastFindUniqueNode *position = m_head->next;
        RHFastFindUniqueNode *previous = position->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(position, previous);
        position->previous = node;
        node->previous->next = node;
        if (&node->value) node->value = value;
        ++m_count;
        m_changed = true;
    }

    void InsertLastAllocator(void *const &value)
    {
        RHFastFindUniqueNode *head = m_head;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)((RHUnk0046eb30 *)this)->Unk0059f720((RHScriptNode *)head, (RHScriptNode *)head->previous);
        head->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++m_count;
        m_changed = true;
    }

    void GoTo(int wanted)
    {
        int count = m_count;
        if (m_changed)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Begin()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
            }
            m_changed = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Begin()), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
                }
                m_index = wanted;
            }
        }
    }

    RHFastFindUniqueNode *&SetCurrent(Iterator iterator)
    {
        m_current = iterator.node;
        return m_current;
    }

    void GoToSegment(int wanted)
    {
        int count = m_count;
        if (m_changed)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Iterator((RHFastFindUniqueNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node)), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
            }
            m_changed = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Iterator((RHFastFindUniqueNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node)), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
                }
                m_index = wanted;
            }
        }
    }

    RHFastFindUniqueNode *&Head()
    {
        return m_head;
    }

    Iterator Begin()
    {
        return Iterator(Head()->next);
    }

    Iterator End()
    {
        return Iterator(Head());
    }

    void Remove(unsigned short index)
    {
        GoTo(index);
        RHFastFindUniqueNode *node = m_current;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --m_count;
        m_changed = true;
    }

};

DECOMP_SIZE_ASSERT(RHFastFindUniqueList, 0x24)

class SBUIInputFieldBoxCalls
{
public:
    bool FUN_00608450(const SBGeoBoundingBox2D &);
};

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
};

class RHUnk00608650
{
public:
    bool FUN_00608650(const RHMalignitySegment &segment);
};

class RHEngine;
extern RHEngine *g_pEngine;

class RHMobileUnk00520b60
{
public:
    RHMobileUnk00520b60(const SBGeoPoint2D &, float, float);
    ~RHMobileUnk00520b60();
    undefined m_00[0x40];
};

struct RHFastFindRepulsiveStorage
{
    undefined m_00[0x40];
    RHFastFindRepulsiveStorage(const SBGeoPoint2D &point, float radius, float strength)
    {
        ((RHMobileUnk00520b60 *)this)->RHMobileUnk00520b60::RHMobileUnk00520b60(point, radius, strength);
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

class RHUnk004fd0c0
{
public:
    char m_00[4];
    RHFastFindRepulsive *m_first;
    RHFastFindRepulsive *m_last;
    RHFastFindRepulsive *m_end;
    void Insert(unsigned index, unsigned count, const RHFastFindRepulsive &value);
};

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

// Parked: frame is 0x28 rather than 0x24; owner/output registers and uniqueness-search scheduling differ.
// STUB: GAME 0x004ec240
void RHFastFindGrid::FUN_004ec240(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    void ***owners = (void ***)((char *)g_pEngine + 0x497c);
    void ***last = (void ***)((char *)g_pEngine + 0x4980);
    unsigned short count = *owners == 0 ? 0 : *last - *owners;
    if (count > 0) {
        for (unsigned short i = 0; i < count; ++i) {
            char *owner = (char *)(*owners)[i];
            if (*(unsigned short *)(*(char **)(owner + 0x50) + 0xde) != layer) continue;
            if (!(unsigned char)((RHUnk00608f10 *)(owner + 0x1ac))->FUN_00608f10((void *)&box)) continue;
            unsigned short lineCount = *(void ***)(owner + 0x168) == 0 ? 0 : *(void ***)(owner + 0x16c) - *(void ***)(owner + 0x168);
            if (lineCount > 0) {
                for (unsigned short j = 0; j < lineCount; ++j) {
                    void *value = (*(void ***)(owner + 0x168))[j];
                    bool intersects = ((SBUIInputFieldBoxCalls *)&box)->FUN_00608450((const SBGeoBoundingBox2D &)RHMobileUnk006100e0(*(RHMobileUnk006100e0 *)(value ? (char *)value + 4 : 0)));
                    if (intersects) {
                        void *copy = value;
                        if (output.Find(copy) == -1) output.InsertLastExternal(copy);
                    }
                }
            }
        }
    }
}

// Parked: cell-pointer spill precedes the zero-count test; unique-list search loads and back-edge differ.
// STUB: GAME 0x004ec450
void RHFastFindGrid::FUN_004ec450(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **values = entry.m_localPoints;
    unsigned short count = entry.m_localPointCount;
    while (count > 0) {
        void *value = *values;
        if (*(bool *)((char *)value + 0x10) && (*(unsigned long *)((char *)value + 0xc) & mask) == mask)
            if (output.Find(value) == -1) output.InsertLast(value);
        ++values;
        --count;
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
    void ***owners = (void ***)((char *)g_pEngine + 0x497c);
    void ***last = (void ***)((char *)g_pEngine + 0x4980);
    unsigned short count = *owners == 0 ? 0 : *last - *owners;
    if (count > 0) {
        for (unsigned short i = 0; i < count; ++i) {
            char *owner = (char *)(*owners)[i];
            if (*(unsigned short *)(*(char **)(owner + 0x50) + 0xde) != layer) continue;
            if (!(unsigned char)((RHUnk00608f10 *)(owner + 0x128))->FUN_00608f10((void *)&segment)) continue;
            unsigned short lineCount = *(void ***)(owner + 0x168) == 0 ? 0 : *(void ***)(owner + 0x16c) - *(void ***)(owner + 0x168);
            if (lineCount > 0) {
                for (unsigned short j = 0; j < lineCount; ++j) {
                    void *value = (*(void ***)(owner + 0x168))[j];
                    bool intersects = ((RHUnk00608650 *)&segment)->FUN_00608650((const RHMalignitySegment &)RHMobileUnk006100e0(*(RHMobileUnk006100e0 *)(value ? (char *)value + 4 : 0)));
                    if (intersects) {
                        void *copy = value;
                        if (output.Find(copy) == -1) output.InsertLastExternal(copy);
                    }
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
    ((RHUnk004fd0c0 *)&grid->m_repulsivePoints)->Insert((unsigned)grid->m_repulsivePoints.end(), 1, *(RHFastFindRepulsive *)&value);
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
            bool intersects = ((RHUnk00608650 *)&box)->FUN_00608650((const RHMalignitySegment &)RHMobileUnk006100e0(*(RHMobileUnk006100e0 *)(line ? (char *)line + 4 : 0)));
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

// Parked: values spills before the zero-count branch and volatile list-search loads change registers/back-edge scheduling.
// STUB: GAME 0x004ecf60
void RHFastFindGrid::FUN_004ecf60(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **values = entry.m_lines;
    unsigned short count = entry.m_lineCount;
    while (count > 0) {
        void *value = *values;
        if (*(bool *)((char *)value + 0x18) && (*(unsigned long *)((char *)value + 0x14) & mask) == mask) {
            if (output.Find(value) == -1) output.InsertLast(value);
        }
        --count;
        ++values;
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
        void *value = output.m_current->value;
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
        void *value = output.m_current->value;
        if (!((RHFastFindSegmentCalls *)((char *)value + 4))->FUN_0060a990(segment)) {
            ((RHSeqList *)&output)->GoTo(i);
            RHFastFindUniqueNode *node = output.m_current;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            operator delete(node);
            --output.m_count;
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

// Parked: cell-pointer spill and unique-list search loads differ.
// STUB: GAME 0x004edcf0
void RHFastFindGrid::FUN_004edcf0(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **values = entry.m_points;
    unsigned short count = entry.m_pointCount;
    while (count > 0)
    {
        void *value = *values;
        if (*(bool *)value && (*(unsigned long *)((char *)value + 4) & mask) == mask)
        {
            if (output.Find(value) == -1)
                output.InsertLast(value);
        }
        ++values;
        --count;
    }
}

class RHUnk005243a0
{
public:
    bool FUN_005243a0(void *point);
    bool FUN_005246c0(void *point, undefined4 mode);
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
            void *value = output.m_current->value;
            if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box) ||
                !((RHUnk005243a0 *)value)->FUN_005243a0(point))
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
            void *value = output.m_current->value;
            if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box) ||
                !((RHUnk005243a0 *)value)->FUN_005246c0(point, mode))
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
        void *value = output.m_current->value;
        if (!(unsigned char)((RHUnk00608f10 *)((char *)value + 8))->FUN_00608f10((void *)&box))
        {
            output.Remove(i);
            --i;
            --count;
        }
    }
}

// Parked: cell-pointer spill and unique-list search loads differ.
// STUB: GAME 0x004ee770
void RHFastFindGrid::FUN_004ee770(RHFastFindUniqueList &output, unsigned long cell, unsigned long mask)
{
    RHFastFindCell &entry = m_cells[cell];
    void **values = entry.m_obstacles;
    unsigned short count = entry.m_obstacleCount;
    while (count > 0)
    {
        void *value = *values;
        if (*(bool *)((char *)value + 8) && (*(unsigned long *)value & mask) == mask)
        {
            if (output.Find(value) == -1)
                output.InsertLast(value);
        }
        ++values;
        --count;
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
};

class RHEngine;
extern RHEngine *g_pEngine;

// Parked: mobile-array count/value stack slots and unique-list search loads differ.
// STUB: GAME 0x004ee880
void RHFastFindGrid::FUN_004ee880(RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask)
{
    RHFastFindMobileArray &owners = *(RHFastFindMobileArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.Size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHFastFindMobileOwner *owner = owners.m_first[i];
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

// Parked: mobile-array count/value stack slots and unique-list search loads differ.
// STUB: GAME 0x004eea50
void RHFastFindGrid::FUN_004eea50(RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask)
{
    RHFastFindMobileArray &owners = *(RHFastFindMobileArray *)((char *)g_pEngine + 0x497c);
    unsigned short count = owners.Size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHFastFindMobileOwner *owner = owners.m_first[i];
        if (*(unsigned short *)(owner->m_position + 0xde) == layer &&
            ((RHUnk00608650 *)&owner->m_bounds)->FUN_00608650(segment))
        {
            unsigned short obstacleCount = owner->m_first == 0 ? 0 : owner->m_last - owner->m_first;
            for (unsigned short j = 0; j < obstacleCount; ++j)
            {
                void *value = owner->m_first[j];
                if (((RHUnk00608650 *)((char *)value + 0x24))->FUN_00608650(segment))
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
        void *value = output.m_current->value;
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
        void *value = output.m_current->value;
        if (!((RHUnk00608650 *)((char *)value + 0x24))->FUN_00608650(segment))
        {
            output.GoToSegment(i);
            ((RHUnk0046eb30 *)&output)->erase(RHScriptIter((RHScriptNode *)output.m_current));
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
        FUN_004e8bd0(list->m_current->value, layer, true);
    }
    list = &((RHFastFindPatchView *)patch)->m_points;
    count = list->GetSize();
    for (unsigned short j = 0; j < count; ++j)
    {
        ((RHSeqList *)list)->GoTo(j);
        FUN_004e8bd0(list->m_current->value, layer, true);
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

// Parked: best probe 42.11%. Target fuses dx>0/dy>0 tests, then splits a dx>0&dy>0
// dominant-axis block from a shared tail (two useDx sites + one merged useDy);
// the source shape behind that FP compare/fuse/schedule is not reproduced.
// STUB: GAME 0x004efe40
bool RHFastFindGrid::FUN_004efe40(const SBGeoPoint3D &first, const SBGeoPoint3D &second, float &slope, float &intercept)
{
    RHUnk005fc3b0 direction;
    direction.m_x = second.m_x - first.m_x;
    direction.m_y = second.m_y - first.m_y;
    float dx = second.m_x - first.m_x;
    float dy = second.m_y - first.m_y;
    if (dx > 0)
    {
        if (dy > 0)
        {
            if (dx > dy)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
        }
        else
        {
            if (dx > -dy)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
        }
    }
    else
    {
        if (dy > 0)
        {
            if (-dx > dy)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
        }
        else
        {
            if (dx < dy)
            {
                slope = (second.m_z - first.m_z) / dx;
                intercept = first.m_z - slope * first.m_x;
                return true;
            }
        }
    }
    slope = (second.m_z - first.m_z) / dy;
    intercept = first.m_z - slope * first.m_y;
    return false;
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

class RHActorGridCalls
{
public:
    bool FUN_004f9a80(void *, RHElementActor *, const SBGeoPoint2D &, void *, unsigned short, const SBGeoPoint2D &, void *, unsigned, int);
};

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
        bool direction = *(bool *)&directions->m_current->value;
        RHFastFindUniqueList *gates = (RHFastFindUniqueList *)((char *)startArea + 0x5c);
        ((RHSeqList *)gates)->GoTo(i);
        RHFastFindPathGate *gate = (RHFastFindPathGate *)gates->m_current->value;
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
            RHFastFindPathEdge *edge = (RHFastFindPathEdge *)edges->m_current->value;
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
        bool direction = *(bool *)&directions->m_current->value;
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
            RHFastFindPathEdge *edge = (RHFastFindPathEdge *)edges->m_current->value;
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
    RHFastFindUniqueNode *head = open.m_head;
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
    ((RHUnk004b1520List *)&list)->FUN_00424410(RHScriptIter((RHScriptNode *)list.m_current), value);
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
        RHFastFindUniqueNode *position = open.m_head->next;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)((RHUnk0046eb30 *)&open)->Unk0059f720((RHScriptNode *)position, (RHScriptNode *)position->previous);
        position->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++open.m_count;
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
RHFastFindRepulsive &RHFastFindRepulsive::FUN_004fdb90(const RHFastFindRepulsive &other)
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

class RHUnk004fd680
{
public:
    char m_data[0x40];
    RHUnk004fd680(const RHUnk004fd680 &other);
};

// Residual: constructor subobject/vtable setup and source argument placement differ from the target.
// STUB: GAME 0x004fd680
RHUnk004fd680::RHUnk004fd680(const RHUnk004fd680 &other)
{
    const char *source = other.m_data;
    char *destination = m_data;
    for (unsigned index = 0; index < sizeof(m_data); ++index)
        destination[index] = source[index];
}

class RHUnk004fd070Item
{
public:
    void Unk(int value);
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

// Residual: the target's end-pointer loop and object destructor dispatch need ABI-level matching.
// STUB: GAME 0x004fd070
RHUnk004fd070::~RHUnk004fd070()
{
    for (RHUnk004fd070Item *item = m_first; item != m_last;
        item = (RHUnk004fd070Item *)((char *)item + 0x40))
    {
        union { unsigned long address; void (RHUnk004fd070Item::*destroy)(int); } destroyCall;
        destroyCall.address = *(unsigned long *)item;
        (item->*destroyCall.destroy)(0);
    }
    ::operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// Residual: the target performs capacity-aware 0x40-byte insertion with allocator/copy helper calls.
// STUB: GAME 0x004fd0c0
void RHUnk004fd0c0::Insert(unsigned index, unsigned count, const RHFastFindRepulsive &value)
{
    unsigned size = m_first ? (unsigned)(m_last - m_first) : 0;
    unsigned capacity = m_first ? (unsigned)(m_end - m_first) : 0;
    if (index > size)
        index = size;
    if (count == 0)
        return;
    unsigned newSize = size + count;
    if (newSize > capacity)
    {
        unsigned newCapacity = capacity ? capacity : 1;
        while (newCapacity < newSize)
            newCapacity *= 2;
        RHFastFindRepulsive *storage = (RHFastFindRepulsive *)::operator new(newCapacity * sizeof(RHFastFindRepulsive));
        unsigned offset = 0;
        for (; offset < index; ++offset)
            for (unsigned byte = 0; byte < sizeof(RHFastFindRepulsive); ++byte)
                ((char *)&storage[offset])[byte] = ((char *)&m_first[offset])[byte];
        for (unsigned inserted = 0; inserted < count; ++inserted, ++offset)
            for (unsigned byte = 0; byte < sizeof(RHFastFindRepulsive); ++byte)
                ((char *)&storage[offset])[byte] = ((const char *)&value)[byte];
        for (unsigned oldIndex = index; oldIndex < size; ++oldIndex, ++offset)
            for (unsigned byte = 0; byte < sizeof(RHFastFindRepulsive); ++byte)
                ((char *)&storage[offset])[byte] = ((char *)&m_first[oldIndex])[byte];
        ::operator delete(m_first);
        m_first = storage;
        m_last = storage + newSize;
        m_end = storage + newCapacity;
        return;
    }
    for (unsigned old = size; old > index; --old)
        m_first[old + count - 1] = m_first[old - 1];
    for (unsigned inserted = 0; inserted < count; ++inserted)
        m_first[index + inserted] = value;
    m_last += count;
}

class RHUnk004fd3d0
{
public:
    char m_00[4];
    char *m_first;
    char *m_last;
    char *m_end;
    char m_10[0x10];
    ~RHUnk004fd3d0();
};

// Residual: nested 0xc0-byte element destruction and member reset order remain incomplete.
// STUB: GAME 0x004fd3d0
RHUnk004fd3d0::~RHUnk004fd3d0()
{
    for (char *item = m_first; item && item != m_last; item += 0xc0)
        ::operator delete(*(void **)(item + 0x14));
    ::operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
    for (unsigned offset = 0x1c; offset <= 0xa0; offset += 0x20)
    {
        void **array = (void **)((char *)this + offset + 4);
        ::operator delete(*array);
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
}

class RHUnk004fd530
{
public:
    char m_00[4];
    char *m_first;
    char *m_last;
    char *m_end;
    char m_10[0x10];
    ~RHUnk004fd530();
};

// Residual: nested 0xa0-byte element destruction and member reset order remain incomplete.
// STUB: GAME 0x004fd530
RHUnk004fd530::~RHUnk004fd530()
{
    for (char *item = m_first; item && item != m_last; item += 0xa0)
        ::operator delete(*(void **)(item + 0x24));
    ::operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
    for (unsigned offset = 0x1c; offset <= 0x80; offset += 0x20)
    {
        void **array = (void **)((char *)this + offset + 4);
        ::operator delete(*array);
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
}

class RHUnk004fd750
{
public:
    char m_data[0xb8];
    RHUnk004fd750(char mode);
};

// Residual: constructor argument propagation and the target's repeated member initialization differ.
// STUB: GAME 0x004fd750
RHUnk004fd750::RHUnk004fd750(char mode)
{
    char *base = (char *)this;
    *(char *)(base + 0x00) = mode;
    *(void **)(base + 0x04) = 0;
    *(void **)(base + 0x08) = 0;
    *(void **)(base + 0x0c) = 0;
    *(char *)(base + 0x14) = 1;
    *(char *)(base + 0x20) = mode;
    *(void **)(base + 0x24) = 0;
    *(void **)(base + 0x28) = 0;
    *(void **)(base + 0x2c) = 0;
    *(char *)(base + 0x34) = 1;
    *(char *)(base + 0x40) = mode;
    *(void **)(base + 0x44) = 0;
    *(void **)(base + 0x48) = 0;
    *(void **)(base + 0x4c) = 0;
    *(char *)(base + 0x54) = 1;
    *(char *)(base + 0x60) = mode;
    *(void **)(base + 0x64) = 0;
    *(void **)(base + 0x68) = 0;
    *(void **)(base + 0x6c) = 0;
    *(char *)(base + 0x74) = 1;
    *(char *)(base + 0x80) = mode;
    *(void **)(base + 0x84) = 0;
    *(void **)(base + 0x88) = 0;
    *(void **)(base + 0x8c) = 0;
    *(char *)(base + 0x94) = 1;
    *(void **)(base + 0xa4) = 0;
    *(void **)(base + 0xa8) = 0;
    *(void **)(base + 0xac) = 0;
    *(char *)(base + 0xb4) = 1;
}

class RHUnk004fd7f0
{
public:
    char m_data[0xc0];
    ~RHUnk004fd7f0();
};

// Residual: five nested arrays and their pairwise helper cleanup calls are not reproduced.
// STUB: GAME 0x004fd7f0
RHUnk004fd7f0::~RHUnk004fd7f0()
{
    for (unsigned offset = 0x20; offset <= 0xa0; offset += 0x20)
    {
        void **array = (void **)((char *)this + offset + 4);
        ::operator delete(*array);
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
}

class RHUnk004fd9a0
{
public:
    char m_data[0x98];
    RHUnk004fd9a0(char mode);
};

// Residual: constructor argument propagation and repeated member initialization remain different.
// STUB: GAME 0x004fd9a0
RHUnk004fd9a0::RHUnk004fd9a0(char mode)
{
    char *base = (char *)this;
    *(char *)(base + 0x00) = mode;
    *(void **)(base + 0x04) = 0;
    *(void **)(base + 0x08) = 0;
    *(void **)(base + 0x0c) = 0;
    *(char *)(base + 0x14) = 1;
    *(char *)(base + 0x20) = mode;
    *(void **)(base + 0x24) = 0;
    *(void **)(base + 0x28) = 0;
    *(void **)(base + 0x2c) = 0;
    *(char *)(base + 0x34) = 1;
    *(char *)(base + 0x40) = mode;
    *(void **)(base + 0x44) = 0;
    *(void **)(base + 0x48) = 0;
    *(void **)(base + 0x4c) = 0;
    *(char *)(base + 0x54) = 1;
    *(char *)(base + 0x60) = mode;
    *(void **)(base + 0x64) = 0;
    *(void **)(base + 0x68) = 0;
    *(void **)(base + 0x6c) = 0;
    *(char *)(base + 0x74) = 1;
    *(char *)(base + 0x80) = mode;
    *(void **)(base + 0x84) = 0;
    *(void **)(base + 0x88) = 0;
    *(void **)(base + 0x8c) = 0;
    *(char *)(base + 0x94) = 1;
}

class RHUnk004fda20
{
public:
    char m_data[0xa0];
    ~RHUnk004fda20();
};

// Residual: the target releases and clears four nested arrays in a different register schedule.
// STUB: GAME 0x004fda20
RHUnk004fda20::~RHUnk004fda20()
{
    for (unsigned offset = 0x20; offset <= 0x80; offset += 0x20)
    {
        void **array = (void **)((char *)this + offset + 4);
        ::operator delete(*array);
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
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

#include "SBResourceManager.h"

void **FUN_004598e0(void **first, void **last, void **destination);

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

// SIZE 0xa0
struct RHFastFindRecordA0
{
    char m_data[0xa0];
};

void FUN_004fe9d0(RHFastFindRecordC0 *destination, const RHFastFindRecordC0 &value);
void FUN_004feb10(RHFastFindRecordA0 *destination, const RHFastFindRecordA0 &value);

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

// deferred: unannotated pending reccmp #534
void **RHScriptFXArray::Unk004fe420(void **first, void **last, void **destination)
{
    for (; first != last; ++first, ++destination)
        if (destination)
            *destination = *first;
    return destination;
}

// deferred: 0x004fe450, exact body; unannotated pending reccmp #534.
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

// SIZE 0xc0
class RHFastFindAssignmentC0
{
public:
    RHFastFindAssignmentC0 &FUN_004fec70(const RHFastFindAssignmentC0 &source);
    RHFastFindPointerArray m_arrays[6];
};

// SIZE 0xa0
class RHFastFindAssignmentA0
{
public:
    RHFastFindAssignmentA0 &FUN_004fedb0(const RHFastFindAssignmentA0 &source);
    RHFastFindPointerArray m_arrays[5];
};

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
    FUN_0051f0f0();
    *(unsigned long *)this = 0x006790c0;
    *(int *)((char *)this + 0x14) = 0x400;
    *((char *)this + 0x39) = 0;
}

void FUN_0051f1b0();

// FUNCTION: GAME 0x0051e220
RHUnk0051e1e0::~RHUnk0051e1e0()
{
    *(unsigned long *)this = 0x006790c0;
    FUN_0051f1b0();
}

void EmitRHUnk0051e1e0(void *storage)
{
    ((RHUnk0051e1e0 *)storage)->RHUnk0051e1e0::~RHUnk0051e1e0();
}

void FUN_0051f0f0();
void FUN_0051f1b0();

// FUNCTION: GAME 0x0051f4d0
RHFastFindLine::RHFastFindLine()
{
    FUN_0051f0f0();
    *(unsigned *)this = 0x6790e8;
    *(unsigned *)((char *)this + 0x24) = 0;
    *(unsigned *)((char *)this + 0x28) = 0;
    *(unsigned short *)((char *)this + 0x20) = 0;
    *(unsigned *)((char *)this + 0x14) = 0xc;
}

// FUNCTION: GAME 0x0051f520
RHFastFindLine::~RHFastFindLine()
{
    *(unsigned *)this = 0x6790e8;
    FUN_0051f1b0();
}

void EmitRHFastFindLine(void *storage)
{
    ((RHFastFindLine *)storage)->RHFastFindLine::~RHFastFindLine();
}

// FUNCTION: GAME 0x0051e5e0
RHUnk0051e5e0::RHUnk0051e5e0()
{
    FUN_0057ca80();
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
    ((RHSector *)this)->Unk0057cd60(file, false);
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
        RHUnk0051a5e0 *gate = (RHUnk0051a5e0 *)line->m_gate;
        if (gate->FUN_0051abe0(line == *(RHUnk0051e1e0 **)gate->m_8c, actor, mode, true, false))
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
        if (distance < g_unk0x006790d8 && (*((char *)this + 0x9c) || *((char *)line->m_other->m_sector + 0x9c)))
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
    return g_unk0x00677488;
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

// SYNTHETIC: GAME 0x004fdc50
// RHUnk00520ae0::`scalar deleting destructor'
// FUNCTION: GAME 0x00520bf0
RHUnk00520ae0::~RHUnk00520ae0()
{
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

// LIBRARY: GAME 0x0059fbc0
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
    m_repulsivePoints.begin()->FUN_004fdb90(*m_repulsivePoints.begin());
    RHUnk00520ae0 repulsive;
}
