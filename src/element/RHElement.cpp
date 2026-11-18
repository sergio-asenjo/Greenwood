#include "SBGeoPoint2D.h"
#include "SBNullstr.h"
#include "RHSpriteCore.h"
#include "RHElement.h"
#include "RHEngine.h"
#include "SBDrawManagerCore.h"
#include <new>
#include <string.h>
#include <stddef.h>

class RHFrameHolder;

extern unsigned g_unk0x006c081c;
extern RHEngine *g_pEngine;
extern RHFrameHolder *g_unk0x006c0b1c;
extern SBDrawManager *g_unk0x6c11d0;

DECOMP_SIZE_ASSERT(RHElement, 0xa8)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHBonusInfoBase, 0xfc)
DECOMP_SIZE_ASSERT(RHUnk005df510, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00613e90, x) == 0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00613e90, y) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00613e90, z) == 8)
DECOMP_SIZE_ASSERT(RHElevationLine, 0x2c)
DECOMP_SIZE_ASSERT(RHElementArea, 0x64)
DECOMP_SIZE_ASSERT(RHElementAreaNode, 0x0c)
DECOMP_SIZE_ASSERT(RHElementAreaIter, 0x04)
DECOMP_SIZE_ASSERT(RHElementAreaListBase, 0x0c)
DECOMP_SIZE_ASSERT(RHElementAreaList, 0x18)
DECOMP_SIZE_ASSERT(RHElementAreaTransientList, 0x24)
DECOMP_SIZE_ASSERT(RHElementAreaTransientList::Node, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk0045aaf0, 0x3c)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_50) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_68) == 0x68)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_74) == 0x74)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_80) == 0x80)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_90) == 0x90)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_a6) == 0xa6)
DECOMP_STATIC_ASSERT(offsetof(RHEngine, m_00dc) == 0xdc)
DECOMP_STATIC_ASSERT(offsetof(RHEngine, m_011c) == 0x11c)
DECOMP_STATIC_ASSERT(offsetof(RHEngine, m_43f8) == 0x43f8)
DECOMP_STATIC_ASSERT(offsetof(RHEngine, m_4aa8) == 0x4aa8)

// FUNCTION: GAME 0x00462010
RHElement::RHElement(int type, char flag) : m_04(type), m_08(flag)
{
    m_0c = g_unk0x006c081c;
    g_unk0x006c081c++;
    m_12 = 1;
    m_8e = 1;
    m_50 = new RHSprite(m_04);
    m_60 = g_pEngine->m_00dc;
    m_64 = g_pEngine->m_011c;
    m_68 = g_unk0x006c0b1c;
    m_5c = g_pEngine->m_43f8;
    m_71 = 0;
    m_70 = 0;
    m_88 = 0;
    m_8a = 0xffff;
    m_58 = -1;
    m_54 = -1;
    m_8c = 1;
    m_90 = g_pEngine->FUN_004d2340(15);
    memset(m_94, 0, sizeof(m_94));
    m_a0 = 0;
    m_a4 = 2;
    m_92 = 0;
    m_08 = m_08 && !g_pEngine->m_4aa8;
    m_a6 = 0;
}

// FUNCTION: GAME 0x00462190
int RHElement::FUN_00462190() const { return 3; }

// FUNCTION: GAME 0x004621a0
SBGeoVector2D RHElement::FUN_004621a0() const
{
    return SBGeoVector2D(0, 0);
}

// FUNCTION: GAME 0x004621c0
float RHElement::FUN_004621c0() const
{
    return m_50->FUN_005bdcb0();
}

// FUNCTION: GAME 0x004621d0
void RHElement::FUN_004621d0(RHUnk005df510 &point) const
{
    point = m_50->m_c;
}

// FUNCTION: GAME 0x004621f0
void RHElement::FUN_004621f0() { m_08 = 0; }

// FUNCTION: GAME 0x00462200
char RHElement::FUN_00462200() const { return 1; }

// FUNCTION: GAME 0x00462210
char RHElement::FUN_00462210(void *value) { return 0; }

// SYNTHETIC: GAME 0x00462220
// RHElement::`scalar deleting destructor'

// FUNCTION: GAME 0x00462240
RHElement::~RHElement()
{
    delete m_50;
    if (m_58 != -1)
        ((SBDrawManager *)g_unk0x6c11d0)->FUN_005e5160(m_58);
    if (m_54 != -1)
        ((SBDrawManager *)g_unk0x6c11d0)->FUN_005e5160(m_54);
}

// FUNCTION: GAME 0x004622d0
void *RHElement::FUN_004622d0() const { return (char *)m_50 + 0x1a0; }

// FUNCTION: GAME 0x00462330
bool RHElement::Serialize(SBFile &file)
{
    // STRING: GAME 0x006ae088
    RHSerializeName(file, "RHElement");
    if (!file.m_bLoading)
    {
        if (file.Access(&m_0c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            // STRING: GAME 0x006ae040
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 174, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        int value;
        if (file.Access(&value, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 179, "Serialize failed reason is %s", reason);
            return false;
        }
        if (value != m_0c)
        {
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 184,
                     // STRING: GAME 0x006ae05c
                     "STRENG VERBOTEN ! Creation order error !");
        }
    }
    if (file.Access(m_94, 10) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 188, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_a0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 189, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_a4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 190, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 192, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_12, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 195, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_71, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 196, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_70, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 197, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_10, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 198, "Serialize failed reason is %s", reason);
        return false;
    }
    m_80.Serialize(file);
    m_74.Serialize(file);
    if (file.Access(&m_88, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 204, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 205, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.m_bLoading && file.m_version < 4)
    {
        short value;
        if (file.Access(&value, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 210, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    if (file.Access(&m_08, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 219, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.m_version >= 24)
    {
        if (file.Access(&m_a6, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 223, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    return m_50->FUN_005b5ed0(file);
}

// FUNCTION: GAME 0x00462940
void RHElement::FUN_00462940(int action)
{
    if (action == 7 || (m_50->m_88 != 12 && m_50->m_88 != 13))
        m_50->FUN_00462970(action);
}

// STUB: GAME 0x00462aa0
void RHElement::CrossElevationLine(RHElevationLine *line)
{
    if (line->m_20 == 0)
        line->m_22 = 64000;
    else
        line->m_22 = 4000;
    line->m_20 = 10;

    if (*(void **)((char *)m_50 + 0xec) == line->m_28)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(line->m_24);
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }
    if (*(void **)((char *)m_50 + 0xec) == line->m_24)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(line->m_28);
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }

    bool failed = true;
    {
        RHElementAreaTransientList areas;
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 485,
                 // STRING: GAME 0x006ae150
                 "VERBOTEN : Illegal bond crossing : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
        const SBGeoPoint2D &point = *(SBGeoPoint2D *)((char *)m_50 + 0x24);
        RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
        grid->FUN_004e89d0(&areas, (short)((short)point.m_y >> 6) * grid->m_3e98 + (short)((short)point.m_x >> 6), 0x20);
        for (unsigned count = (unsigned short)areas.Count(), index = 0; count != 0; ++index, --count)
        {
            areas.GoTo(index);
            RHElementArea *area = areas.cursor->_Value;
            if (*(unsigned short *)(area->m_58 + 0x15a) == *(unsigned short *)((char *)m_50 + 0xde)
                && area->m_3c.FUN_00608400(*(SBGeoPoint2D *)((char *)m_50 + 0x24))
                && (area ? &area->m_04 : 0)->FUN_0060c660(*(SBGeoPoint2D *)((char *)m_50 + 0x24)))
            {
                ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(area->m_58);
                failed = false;
            }
        }
    }

    if (!failed)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }
    if (*(unsigned *)((char *)m_50 + 0xc) & 1)
    {
        char allocator;
        RHElementAreaList areas(allocator);
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 510,
                 // STRING: GAME 0x006ae0f8
                 "STRENG VERBOTEN !: No projection area was found for this bond : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
        {
            SBGeoPoint2D point = ((SBGeoPoint2D *)((char *)m_50 + 0x24))->Unk005fc190(operator*(2.0f, *(SBGeoVector2D *)((char *)m_50 + 0x70)));
            RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
            grid->FUN_004e89d0(&areas, (short)((short)point.m_y >> 6) * grid->m_3e98 + (short)((short)point.m_x >> 6), 0x20);
            for (unsigned count = (unsigned short)areas.m_08, index = 0; count != 0; ++index, --count)
            {
                areas.GoTo(index);
                RHElementArea *area = areas.m_0c->data;
                if (*(unsigned short *)(area->m_58 + 0x15a) == *(unsigned short *)((char *)m_50 + 0xde)
                    && area->m_3c.FUN_00608400(point)
                    && (area ? &area->m_04 : 0)->FUN_0060c660(*(SBGeoPoint2D *)((char *)m_50 + 0x24)))
                {
                    ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(area->m_58);
                    failed = false;
                }
            }
        }
    }
    if (!failed)
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
    else
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 530,
                 // STRING: GAME 0x006ae094
                 "ABSOLUT VERBOTEN !: No projection area was found for this bond at second try : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
}

// SIZE 0x24
struct RHElementGridListView : public std::list<RHElementArea *>
{
    iterator m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
    bool m_18; // 0x18
    undefined m_19[3]; // 0x19
    int m_1c; // 0x1c
    RHElementArea *m_20; // 0x20
    iterator &SetCurrent(iterator position)
    {
        m_0c = position;
        return m_0c;
    }
    int Find(RHElementArea *value)
    {
        int length = _Size;
        m_20 = value;
        m_18 = true;
        SetCurrent(begin());
        int index;
        for (index = 0; index < length; ++index, ++m_0c)
        {
            if (*m_0c == m_20)
                break;
        }
        if (index < length)
        {
            m_1c = index;
            m_10 = false;
            m_14 = index;
        }
        else
        {
            m_10 = true;
            m_1c = -1;
        }
        return m_1c;
    }
    void InsertLast(RHElementArea *value)
    {
        push_back(value);
        m_10 = true;
    }
};

DECOMP_SIZE_ASSERT(RHElementGridListView, 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHElementGridListView, m_0c) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHElementGridListView, m_10) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHElementGridListView, m_20) == 0x20)

struct RHElementGridCellView
{
    undefined m_00[0x10];
    unsigned short count;
    undefined m_12[2];
    RHElementArea **areas;
    undefined m_18[0x10];
};

DECOMP_SIZE_ASSERT(RHElementGridCellView, 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHElementGridCellView, count) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHElementGridCellView, areas) == 0x14)

// FUNCTION: GAME 0x004e89d0
void RHElementGrid::FUN_004e89d0(void *list, int cell, unsigned mask)
{
    RHElementGridCellView *entry = (RHElementGridCellView *)m_403c + cell;
    RHElementArea **areas = entry->areas;
    unsigned short size = entry->count;
    RHElementGridListView *output = (RHElementGridListView *)list;
    for (unsigned short i = 0; i < size; i++)
    {
        RHElementArea *value = areas[i];
        if (*((undefined *)value + 0x34) && (*(unsigned *)((undefined *)value + 0x30) & mask) == mask)
        {
            if (output->Find(value) == -1)
                output->InsertLast(value);
        }
    }
}

// STUB: GAME 0x004e8fc0
short RHElementGrid::FUN_004e8fc0(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, short layer,
                                  void *&sector)
{
    RHElementAreaTransientList list;
    int cell = (m_3e9a * (layer & 0xffff) + ((int)point.m_y >> 6)) * m_3e98 + ((int)point.m_x >> 6);
    FUN_004e89d0(&list, cell, 0x40);
    int count = list.Count();
    if ((short)count == 0)
        return -2;
    int i;
    for (i = 0; i < count; ++i)
    {
        list.GoTo(i);
        RHElementArea *area = list.cursor->_Value;
        unsigned flags = *(unsigned *)((char *)area + 0x30);
        if (flags & 4)
        {
            if (area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
            {
                sector = area;
                return *(short *)((char *)area + 0x38);
            }
            list.GoTo(i);
            list.erase(list.cursor);
            --i;
            --count;
            list.dirty = true;
        }
        if (*(unsigned *)((char *)area + 0x30) & 0x200)
        {
            if (area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
            {
                sector = area;
                return *(short *)((char *)area + 0x38);
            }
            list.GoTo(i);
            list.erase(list.cursor);
            --i;
            --count;
            list.dirty = true;
        }
        if (*(unsigned *)((char *)area + 0x30) & 0x1000)
        {
            if (area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
            {
                sector = area;
                return *(short *)((char *)area + 0x38);
            }
            list.GoTo(i);
            list.erase(list.cursor);
            --i;
            --count;
            list.dirty = true;
        }
    }
    short found = -2;
    for (i = 0; i < count; ++i)
    {
        list.GoTo(i);
        RHElementArea *area = list.cursor->_Value;
        unsigned flags = *(unsigned *)((char *)area + 0x30);
        if (flags & 2)
        {
            if ((flags & 1) && area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
            {
                sector = area;
                found = *(short *)((char *)area + 0x38);
            }
            if (!(flags & 1) && area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
                return -1;
        }
    }
    if (found < 0)
        return found;
    SBGeoPoint2D center;
    float best = 3.4028235e38f;
    for (i = 0; i < count; ++i)
    {
        list.GoTo(i);
        RHElementArea *area = list.cursor->_Value;
        if (*(unsigned *)((char *)area + 0x30) & 0x8000)
        {
            if (area->m_3c.FUN_00608400(point)
                && ((RHElementAreaShape *)((char *)area + 4))->FUN_0060c660(point))
            {
                float *bounds = *(float **)((char *)area + 0x5c);
                center.m_x = (bounds[3] + bounds[1]) * 0.5f;
                center.m_y = (bounds[4] + bounds[2]) * 0.5f;
                float distance = center.Unk005fc110(origin).Unk005fc6d0(1.0f);
                if (distance < best)
                {
                    sector = area;
                    best = distance;
                }
            }
            list.GoTo(i);
            list.erase(list.cursor);
            --i;
            --count;
            list.dirty = true;
        }
    }
    return *(short *)((char *)*(RHElementArea **)&sector + 0x38);
}

class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;

// Parked: list cleanup frame and receiver scheduling differ.
// STUB: GAME 0x0055fa70
void RHBonusInfoBase::FUN_0055fa70(void *area)
{
    m_e8 = area;
    if (area)
    {
        m_ec = (undefined *)area + 0xa8;
        m_f8 = *(void **)((undefined *)area + 0x168);
    }
    else
    {
        RHElementAreaTransientList areas;
        m_ec = 0;
        m_f8 = ((RHElementGrid *)g_unk0x6c0a9c)->m_4188;
        RHElementGrid *grid = (RHElementGrid *)g_unk0x6c0a9c;
        grid->FUN_004e89d0(&areas, (grid->m_3e9a * m_da + (short)((short)m_20.m_y >> 6)) * grid->m_3e98 + (short)((short)m_20.m_x >> 6), 0x10);
        unsigned short count = (unsigned short)areas.Count();
        for (unsigned short index = 0; index < count; ++index)
        {
            areas.GoTo(index);
            RHElementArea *value = areas.cursor->_Value;
            if (value->m_3c.FUN_00608400(m_20)
                && (value ? &value->m_04 : 0)->FUN_0060c660(m_20))
            {
                m_f8 = value->m_60;
                break;
            }
        }
    }
    m_04 &= ~1;
    m_08 &= ~2;
}

// FUNCTION: GAME 0x005fc4f0
SBGeoVector2D operator*(float factor, const SBGeoVector2D &point)
{
    SBGeoVector2D result;
    result.m_x = factor * point.m_x;
    result.m_y = factor * point.m_y;
    return result;
}

// FUNCTION: GAME 0x0060c650
bool RHElementAreaShape::FUN_0060c650(const SBGeoBoundingBox2D &box) const
{
    return box.FUN_00608d60(*(const RHUnkSectorPoints *)this);
}

// FUNCTION: GAME 0x0060c660
bool RHElementAreaShape::FUN_0060c660(const SBGeoPoint2D &point) const
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    float x = point.m_x;
    float y = point.m_y;
    bool single = m_24 == 3;
    unsigned count = FUN_0060ce80();
    if (count == 0)
        return false;
    --count;
    previous = FUN_0060cef0(count);
    bool below = previous.m_y < y;
    bool above = previous.m_y > y;
    float lastX = previous.m_x;
    float lastY = previous.m_y;
    bool inside = false;
    for (unsigned index = 0; index <= count; ++index)
    {
        current = FUN_0060cef0(index);
        float oldX = lastX;
        float oldY = lastY;
        lastX = current.m_x;
        lastY = current.m_y;
        bool oldRight;
        bool newRight;
        float first;
        float second;
        if (below)
        {
            if (current.m_y == y)
            {
                below = false;
                if (current.m_x == x)
                    return true;
            }
            else if (current.m_y > y)
            {
                oldRight = oldX >= x;
                newRight = current.m_x >= x;
                if (oldRight && newRight)
                    goto upwardCrossing;
                if (oldRight || newRight)
                {
                    first = (current.m_x - oldX) * (y - oldY);
                    second = (current.m_y - oldY) * (x - oldX);
                    if (!((double)first < (double)second))
                    {
upwardCrossing:
                        if (single && inside)
                            return false;
                        inside = !inside;
                    }
                }
                below = false;
                above = true;
                if ((oldX == x && current.m_x == x) || (oldRight != newRight && first == second))
                    return true;
            }
        }
        else if (above)
        {
            if (current.m_y == y)
            {
                if (current.m_x >= x)
                {
                    if (single && inside)
                        return false;
                    inside = !inside;
                }
                above = false;
                if (current.m_x == x)
                    return true;
            }
            else if (current.m_y < y)
            {
                oldRight = oldX >= x;
                newRight = current.m_x >= x;
                if (oldRight && newRight)
                    goto downwardCrossing;
                if (oldRight || newRight)
                {
                    first = (current.m_x - oldX) * (y - oldY);
                    second = (current.m_y - oldY) * (x - oldX);
                    if (!((double)first > (double)second))
                    {
downwardCrossing:
                        if (single && inside)
                            return false;
                        inside = !inside;
                    }
                }
                above = false;
                below = true;
                if ((oldX == x && current.m_x == x) || (oldRight != newRight && first == second))
                    return true;
            }
        }
        else if (current.m_y > y)
        {
            above = true;
            below = false;
            if (oldX >= x)
            {
                if (single && inside)
                    return false;
                inside = !inside;
            }
        }
        else if (current.m_y < y)
        {
            above = false;
            below = true;
        }
        else if ((oldX <= x && current.m_x >= x) || (oldX >= x && current.m_x <= x))
            return true;
        previous = current;
    }
    return inside;
}

void RHElement::Emit(SBFile &file)
{
    FUN_00462190();
    FUN_004621a0();
    RHUnk005df510 point;
    FUN_004621d0(point);
    FUN_004621f0();
    FUN_00462200();
    FUN_00462210(0);
    FUN_004622d0();
    Serialize(file);
    CrossElevationLine(0);
    ((RHElementAreaShape *)this)->FUN_0060c660(m_80);
}
