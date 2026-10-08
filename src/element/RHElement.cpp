#include "RHElement.h"
#include <new>

DECOMP_SIZE_ASSERT(RHElement, 0xa8)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHBonusInfoBase, 0xfc)
DECOMP_SIZE_ASSERT(RHUnk005df510, 0x0c)
DECOMP_SIZE_ASSERT(RHElevationLine, 0x2c)
DECOMP_SIZE_ASSERT(RHElementAreaNode, 0x0c)
DECOMP_SIZE_ASSERT(RHElementAreaIter, 0x04)
DECOMP_SIZE_ASSERT(RHElementAreaListBase, 0x0c)
DECOMP_SIZE_ASSERT(RHElementAreaList, 0x18)
DECOMP_SIZE_ASSERT(RHUnk0040f060, 0x24)

// deferred: unannotated pending reccmp #534
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
        RHUnk0040f060 areas;
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 485,
                 // STRING: GAME 0x006ae150
                 "VERBOTEN : Illegal bond crossing : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
        const SBGeoPoint2D &point = *(SBGeoPoint2D *)((char *)m_50 + 0x24);
        RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
        grid->FUN_004e89d0(&areas, point.CellY() * grid->m_3e98 + point.CellX(), 0x20);
        for (unsigned count = (unsigned short)areas.m_08, index = 0; count != 0; ++index, --count)
        {
            areas.GoTo(index);
            RHElementArea *area = areas.m_0c->data;
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
            SBGeoPoint2D point = ((SBGeoPoint2D *)((char *)m_50 + 0x24))->Unk005fc190(FUN_005fc4f0(2.0f, *(SBGeoPoint2D *)((char *)m_50 + 0x70)));
            RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
            grid->FUN_004e89d0(&areas, point.CellY() * grid->m_3e98 + point.CellX(), 0x20);
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
struct RHElementGridListView
{
    undefined m_00[4]; // 0x00
    RHElementAreaNode *m_04; // 0x04
    int m_08; // 0x08
    RHElementAreaNode *m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
    bool m_18; // 0x18
    undefined m_19[3]; // 0x19
    int m_1c; // 0x1c
    RHElementArea *m_20; // 0x20
};

DECOMP_SIZE_ASSERT(RHElementGridListView, 0x24)

// Parked: container cursor scheduling differs.
// STUB: GAME 0x004e89d0
void RHElementGrid::FUN_004e89d0(void *list, int cell, unsigned mask)
{
    undefined *entry = m_403c + cell * 40;
    RHElementArea **area = *(RHElementArea ***)(entry + 0x14);
    unsigned short count = *(unsigned short *)(entry + 0x10);
    RHElementGridListView *output = (RHElementGridListView *)list;
    while (count != 0)
    {
        RHElementArea *value = *area;
        if (*((undefined *)value + 0x34) && (*(unsigned *)((undefined *)value + 0x30) & mask) == mask)
        {
            output->m_20 = value;
            output->m_18 = true;
            output->m_0c = output->m_04->next;
            int index;
            for (index = 0; index < output->m_08; ++index)
            {
                if (output->m_0c->data == output->m_20)
                    break;
                output->m_0c = output->m_0c->next;
            }
            if (index < output->m_08)
            {
                output->m_1c = index;
                output->m_10 = false;
                output->m_14 = index;
            }
            else
            {
                output->m_10 = true;
                output->m_1c = -1;
            }
            if (output->m_1c == -1)
            {
                RHElementAreaNode *head = output->m_04;
                RHElementAreaNode *previous = head->prev;
                RHElementAreaNode *node = (RHElementAreaNode *)::operator new(sizeof(RHElementAreaNode));
                node->RHElementAreaNode::RHElementAreaNode(head, previous);
                head->prev = node;
                node->prev->next = node;
                if (&node->data)
                    node->data = value;
                ++output->m_08;
                output->m_10 = true;
            }
        }
        ++area;
        --count;
    }
}

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

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
        RHUnk0040f060 areas;
        m_ec = 0;
        m_f8 = ((RHElementGrid *)g_unk0x6c0a9c)->m_4188;
        RHElementGrid *grid = (RHElementGrid *)g_unk0x6c0a9c;
        grid->FUN_004e89d0(&areas, (grid->m_3e9a * m_da + m_20.CellY()) * grid->m_3e98 + m_20.CellX(), 0x10);
        unsigned short count = (unsigned short)areas.m_08;
        for (unsigned short index = 0; index < count; ++index)
        {
            areas.GoTo(index);
            RHElementArea *value = areas.m_0c->data;
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
SBGeoPoint2D FUN_005fc4f0(float factor, const SBGeoPoint2D &point)
{
    SBGeoPoint2D result;
    result.m_0 = factor * point.m_0;
    result.m_4 = factor * point.m_4;
    return result;
}

// Parked: crossing products remain live on the x87 stack.
// STUB: GAME 0x0060c660
bool RHElementAreaShape::FUN_0060c660(const SBGeoPoint2D &point) const
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    float x = point.m_0;
    float y = point.m_4;
    bool single = m_24 == 3;
    unsigned count = FUN_0060ce80();
    if (count == 0)
        return false;
    --count;
    previous = FUN_0060cef0(count);
    bool below = previous.m_4 < y;
    bool above = previous.m_4 > y;
    float lastX = previous.m_0;
    float lastY = previous.m_4;
    bool inside = false;
    for (unsigned index = 0; index <= count; ++index)
    {
        current = FUN_0060cef0(index);
        float oldX = lastX;
        float oldY = lastY;
        lastX = current.m_0;
        lastY = current.m_4;
        bool oldRight;
        bool newRight;
        float first;
        float second;
        if (below)
        {
            if (current.m_4 == y)
            {
                below = false;
                if (current.m_0 == x)
                    return true;
            }
            else if (current.m_4 > y)
            {
                oldRight = oldX >= x;
                newRight = current.m_0 >= x;
                if (oldRight && newRight)
                    goto upwardCrossing;
                if (oldRight || newRight)
                {
                    first = (current.m_0 - oldX) * (y - oldY);
                    second = (current.m_4 - oldY) * (x - oldX);
                    if (second <= first)
                    {
upwardCrossing:
                        if (single && inside)
                            return false;
                        inside = !inside;
                    }
                }
                below = false;
                above = true;
                if ((oldX == x && current.m_0 == x) || (oldRight != newRight && first == second))
                    return true;
            }
        }
        else if (above)
        {
            if (current.m_4 == y)
            {
                if (current.m_0 >= x)
                {
                    if (single && inside)
                        return false;
                    inside = !inside;
                }
                above = false;
                if (current.m_0 == x)
                    return true;
            }
            else if (current.m_4 < y)
            {
                oldRight = oldX >= x;
                newRight = current.m_0 >= x;
                if (oldRight && newRight)
                    goto downwardCrossing;
                if (oldRight || newRight)
                {
                    first = (current.m_0 - oldX) * (y - oldY);
                    second = (current.m_4 - oldY) * (x - oldX);
                    if (second >= first)
                    {
downwardCrossing:
                        if (single && inside)
                            return false;
                        inside = !inside;
                    }
                }
                above = false;
                below = true;
                if ((oldX == x && current.m_0 == x) || (oldRight != newRight && first == second))
                    return true;
            }
        }
        else if (current.m_4 > y)
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
        else if (current.m_4 < y)
        {
            above = false;
            below = true;
        }
        else if ((oldX <= x && current.m_0 >= x) || (oldX >= x && current.m_0 <= x))
            return true;
        previous = current;
    }
    return inside;
}

void RHElement::Emit(SBFile &file)
{
    Serialize(file);
    CrossElevationLine(0);
    ((RHElementAreaShape *)this)->FUN_0060c660(m_80);
}
