#include "SBNullstr.h"
#include "RHFastFindGrid.h"

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

struct RHFastFindCell
{
    undefined m_00[0x18];
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

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
};

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

class RHUnk00608650
{
public:
    bool FUN_00608650(const RHMalignitySegment &segment);
};

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
        for (unsigned short x = firstX; x <= (unsigned short)lastX; ++x, ++cell)
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

// FUNCTION: GAME 0x004fdc20
RHFastFindRepulsiveBase &RHFastFindRepulsiveBase::Unk004fdc20(const RHFastFindRepulsiveBase &other)
{
    *(SBGeoPoint2D *)((char *)this + 4) = *(const SBGeoPoint2D *)(&other ? (const char *)&other + 4 : 0);
    *(int *)((char *)this + 0xc) = *(const int *)((const char *)&other + 0xc);
    *((char *)this + 0x10) = *((const char *)&other + 0x10);
    return *this;
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
    int start = ((RHUnk005f5440 *)&file)->Unk();
    ((RHSector *)this)->Unk0057cd60(file, false);
    unsigned short sector;
    file.Access(&sector, 2);
    *(void **)((char *)this + 0x98) = RHFastFindLookup(sector);
    file.Access(&m_layer, 2);
    file.Access((char *)this + 0x9c, 1);
    return ((RHUnk005f5440 *)&file)->Unk() - start;
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

// TEMPLATE: GAME 0x0059fbc0
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
    m_repulsivePoints.begin()->FUN_004fdb90(*m_repulsivePoints.begin());
    RHUnk00520ae0 repulsive;
}
