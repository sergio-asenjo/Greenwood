#include "SBNullstr.h"
#include "RHShadowPolygon.h"
#include <math.h>

DECOMP_SIZE_ASSERT(RHUnk005c9010Node, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005c9010Iterator, 0x04)
DECOMP_SIZE_ASSERT(RHUnk0058e7f0List, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowPolygonList, 0x18)
DECOMP_SIZE_ASSERT(RHUnk005977e0, 0x4c)
DECOMP_SIZE_ASSERT(RHShadowPolygonActorPosition, 0x1c)
DECOMP_SIZE_ASSERT(RHUnk004a96a0, 0x54)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBGeoPoint3D, 0x0c)
DECOMP_SIZE_ASSERT(RHShadowUnk0060c260, 0x30)

// GLOBAL: GAME 0x006774c8
float g_unk0x006774c8 = 40.0f;

// GLOBAL: GAME 0x00677504
float g_unk0x00677504 = 0.573576450347900390625f;

// GLOBAL: GAME 0x00677f9c
float g_unk0x00677f9c = 90.0f;

// Coupled park: 0x004c9d20; annotation breaks DisplayDebug.
void RHEngine::FUN_004c9d20(void *box)
{
    unsigned short count = (unsigned short)FUN_004c9d20Size();
    if (count > 0)
    {
        unsigned remaining = count;
        for (unsigned index = 0; remaining != 0; ++index, --remaining)
        {
            RHUnk004a96a0 *actor = m_48dc[index];
            if (actor->m_10 == 0x1001 && actor->m_50->m_18 == g_unk0x00677488)
                actor->FUN_004a96a0(m_48c4, m_475c, box, false);
        }
    }
}

// FUNCTION: GAME 0x0058e7f0
void RHShadowPolygon::DisplayDebug(const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    const float *bounds = (const float *)&box;
    if (bounds[0] < g_unk0x00677488 || bounds[1] < g_unk0x00677488)
        SBAssert(1,
                 // STRING: GAME 0x006b7728
                 "P:\\Robin Hood\\rhshadowpolygon.cpp",
                 3928,
                 // STRING: GAME 0x006b774c
                 "Shadow polygon : unable to zoom in because of too small map !");

    m_28 = flags;
    FUN_00594bf0(box, zoom, actor, point, view);
    FUN_005973f0();
    FUN_0058d990();
    FUN_00595020();
    FUN_005959e0();
    FUN_005971f0();
    FUN_0058ec60();
    g_pEngine->FUN_004c9d20(m_11c);

    for (unsigned short index = 0; index < (int)m_134.m_list.size(); ++index)
    {
        FUN_00597910();
        RHUnk00597a70 *area = m_134[index];
        if (FUN_00597a70(area))
        {
            FUN_0058ffa0(area);
            if (*(unsigned long *)&m_8c == 0x3f800000)
                FUN_00590c90(area);
            else if (m_8c > g_unk0x0067749c)
                FUN_005934b0(area);
            else
                FUN_00592080(area);
        }
    }
}

// Coupled park: 0x00594bf0; annotation breaks DisplayDebug.
void RHShadowPolygon::FUN_00594bf0(const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view)
{
    RHUnk005fc3b0 temporary;
    RHUnk005fc3b0 initial;
    SBGeoBoundingBox2D &bounds = RHShadowField<SBGeoBoundingBox2D>(this, 0x78);
    bounds.m_10 = true;
    float value = box.m_0;
    bounds.m_0 = value;
    bounds.m_10 = true;
    bounds.m_8 = box.m_8 - g_unk0x0067749c;
    bounds.m_10 = true;
    value = box.m_4;
    bounds.m_4 = value;
    bounds.m_10 = true;
    bounds.m_c = box.m_c - g_unk0x0067749c;
    m_8c = zoom;
    RHShadowField<int>(this, 0x90) = (int)bounds.m_0;
    RHShadowField<int>(this, 0x94) = (int)bounds.m_4;
    RHShadowField<RHElementActor *>(this, 0xbc) = actor;
    RHShadowField<SBGeoPoint3D>(this, 0xa4) = point;
    RHShadowField<float>(this, 0xb0) = point.m_0;
    RHShadowField<float>(this, 0xb4) = point.m_4;
    RHUnk005fc3b0 &direction = RHShadowField<RHUnk005fc3b0>(this, 0x98);
    direction.FUN_005fc430(RHShadowField<SBGeoPoint2D>(&view, 0x48));
    if (direction.m_x == g_unk0x00677488 && direction.m_y == g_unk0x00677488)
    {
        direction.m_x = 1.0f;
        direction.m_y = 0.0f;
    }
    else
        direction.FUN_005fc7c0(1.0f);
    RHShadowField<undefined>(this, 0x61) = RHShadowField<undefined>(&view, 0);
    RHShadowField<float>(this, 0xa0) = (float)RHShadowField<unsigned short>(&view, 0x78);
    float angle = RHShadowField<float>(&view, 0x24);
    float extent = angle + angle;
    RHUnk005fc3b0 &left = RHShadowField<RHUnk005fc3b0>(this, 0xc8);
    left.FUN_005fc430(direction.FUN_005fc9e0(-angle, 1.0f));
    initial.FUN_005fc430(left);
    left.m_y *= g_unk0x00677504;
    RHUnk005fc3b0 &right = RHShadowField<RHUnk005fc3b0>(this, 0xd0);
    right.FUN_005fc430(direction.FUN_005fc9e0(angle, 1.0f));
    right.m_y *= g_unk0x00677504;
    RHShadowUnk0060c260 &field = RHShadowField<RHShadowUnk0060c260>(this, 0xd8);
    field.FUN_0060c280();
    SBGeoBoundingBox2D &fieldBounds = RHShadowField<SBGeoBoundingBox2D>(this, 0x108);
    fieldBounds.FUN_00607d90();
    unsigned short count = (unsigned short)(int)ceil(extent / (g_unk0x00677f9c / RHShadowField<float>(this, 0xa0)));
    float step = extent / (count + 1);
    field.FUN_0060c260(RHShadowField<SBGeoPoint2D>(this, 0xb0));
    field.FUN_0060c260(left);
    float rotation = 0.0f;
    for (unsigned remaining = count; remaining != 0; --remaining)
    {
        rotation += step;
        temporary.FUN_005fc430(initial.FUN_005fc9e0(rotation, 1.0f));
        temporary.m_y *= g_unk0x00677504;
        field.FUN_0060c260(temporary);
    }
    field.FUN_0060c260(right);
    SBGeoPoint2D origin;
    SBGeoPoint2D projected;
    origin = field.FUN_0060c2b0(0);
    fieldBounds.Unk00607dc0(origin);
    for (unsigned short index = 1; index < (int)count + 3; ++index)
    {
        SBGeoPoint2D vector(field.FUN_0060c2b0(index));
        projected = origin.Unk005fc190(operator*(RHShadowField<float>(this, 0xa0), (const SBGeoVector2D &)vector));
        fieldBounds.Unk00607dc0(projected);
    }
}

// Coupled park: 0x005971f0; annotation breaks DisplayDebug.
void RHShadowPolygon::FUN_005971f0()
{
    unsigned count = (unsigned short)m_158.m_list.size();
    if (count > 0)
    {
        int index = 0;
        do
        {
            m_158.FUN_005c8e40(index);
            RHUnk005977e0 *area = (RHUnk005977e0 *)*m_158.m_current;
            undefined *field = area->m_0 + 0x4c;
            unsigned short limit = (unsigned short)area->m_10.m_list.size();
            for (unsigned short item = 0; item < limit; ++item)
            {
                area->m_10.FUN_005c8e40(item);
                RHUnk00564020 *boundary = (RHUnk00564020 *)*area->m_10.m_current;
                if (!FUN_0059e7e0(field, boundary))
                {
                    delete boundary;
                    area->m_10[item];
                    RHUnk005c9010Node *node = area->m_10.m_current.m_node;
                    node->m_prev->m_next = node->m_next;
                    node->m_next->m_prev = node->m_prev;
                    operator delete(node);
                    --area->m_10.m_list.m_count;
                    area->m_10.m_dirty = true;
                    --item;
                    limit = (unsigned short)(index + 0xffff);
                }
            }
            ++index;
        } while (--count != 0);
    }
}

// Coupled park: 0x005973f0; annotation breaks DisplayDebug.
void RHShadowPolygon::FUN_005973f0()
{
    unsigned count = (unsigned short)m_134.m_list.size();
    for (int index = 0; count != 0; ++index, --count)
    {
        m_134.FUN_005c8e40(index);
        delete *m_134.m_current;
    }
    m_134.m_list.FUN_0044e8b0(m_134.m_list.FUN_0046eb80(), m_134.m_list.end());
    m_134.m_dirty = true;

    count = (unsigned short)m_158.m_list.size();
    for (index = 0; count != 0; ++index, --count)
    {
        m_158.FUN_005c8e40(index);
        RHUnk005977e0 *area = (RHUnk005977e0 *)*m_158.m_current;
        unsigned items = (unsigned short)area->m_10.m_list.size();
        for (int item = 0; items != 0; ++item, --items)
        {
            area->m_10.FUN_005c8e40(item);
            delete (RHUnk00564020 *)*area->m_10.m_current;
        }
        area->m_10.m_list.FUN_0044e8b0(area->m_10.m_list.FUN_0046eb80(), area->m_10.m_list.end());
        area->m_10.m_dirty = true;
        items = (unsigned short)area->m_34.m_list.size();
        for (item = 0; items != 0; ++item, --items)
        {
            area->m_34.FUN_005c8e40(item);
            delete (RHUnk00564020 *)*area->m_34.m_current;
        }
        area->m_34.m_list.FUN_0044e8b0(area->m_34.m_list.FUN_0046eb80(), area->m_34.m_list.end());
        area->m_34.m_dirty = true;
        delete area;
    }
    m_158.m_list.FUN_0044e8b0(m_158.m_list.begin(), m_158.m_list.end());
    m_158.m_dirty = true;
    m_190->FUN_0059f000();
    m_198.m_list.FUN_0044e8b0(m_198.m_list.begin(), m_198.m_list.end());
    m_198.m_dirty = true;
    m_1bc.m_list.FUN_0044e8b0(m_1bc.m_list.begin(), m_1bc.m_list.end());
    m_1bc.m_dirty = true;
    m_194->FUN_0059ec90();
    RHUnk005c9010Iterator current = m_1e0.m_list.begin();
    RHUnk005c9010Iterator last = m_1e0.m_list.end();
    while (current.m_node != last.m_node)
    {
        m_1e0.m_list.FUN_0046eb30(current.FUN_0057c9c0(0));
    }
    m_1e0.m_dirty = true;
}

// Coupled park: 0x00597910; annotation breaks DisplayDebug.
void RHShadowPolygon::FUN_00597910()
{
    m_190->FUN_0059f000();
    m_198.ClearNodes();
    m_1bc.ClearNodes();
    m_194->FUN_0059ec90();
    m_1e0.ClearNodes();
    unsigned short count = (unsigned short)m_158.m_list.size();
    if (count > 0)
    {
        RHShadowPolygonList &areas = m_158;
        unsigned remaining = count;
        for (int index = 0; remaining != 0; ++index, --remaining)
        {
            areas.FUN_005c8e40(index);
            RHUnk005977e0 *area = (RHUnk005977e0 *)*areas.m_current;
            unsigned short itemCount = (unsigned short)area->m_34.m_list.size();
            if (itemCount > 0)
            {
                RHShadowPolygonList &boundaries = area->m_34;
                unsigned items = itemCount;
                for (int item = 0; items != 0; ++item, --items)
                {
                    boundaries.FUN_005c8e40(item);
                    delete (RHUnk00564020 *)*boundaries.m_current;
                }
            }
            RHUnk005c9010Node *head = area->m_34.m_list.m_head;
            RHUnk005c9010Node *current = head->m_next;
            while (current != head)
            {
                RHUnk005c9010Node *node = current;
                current = current->m_next;
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
                operator delete(node);
                --area->m_34.m_list.m_count;
            }
            area->m_34.m_dirty = true;
        }
    }
}

// Coupled park: 0x00597a70; annotation breaks DisplayDebug.
bool RHShadowPolygon::FUN_00597a70(RHUnk00597a70 *area)
{
    RHShadowField<RHUnk00597a70 *>(this, 0x130) = area;
    int &left = RHShadowField<int>(this, 0x17c);
    int &right = RHShadowField<int>(this, 0x180);
    int &top = RHShadowField<int>(this, 0x184);
    int &bottom = RHShadowField<int>(this, 0x188);
    left = (int)area->m_2c.m_0;
    right = (int)area->m_2c.m_8;
    top = (int)area->m_2c.m_4;
    bottom = (int)area->m_2c.m_c;
    if (*(undefined4 *)&m_8c == 0x3f000000)
    {
        if (left & 1)
            ++left;
        if (top & 1)
            ++top;
        if (right & 1)
            --right;
        if (bottom & 1)
            --bottom;
        if (right < left || bottom < top)
            return false;
    }
    float &height = RHShadowField<float>(this, 0xb8);
    RHShadowUnk005df9e0 *plane;
    if (area->m_0 == 0)
    {
        RHShadowField<unsigned short>(this, 0x18c) = 1;
        RHShadowField<unsigned short>(this, 0x18e) = 1;
        height = RHShadowField<float>(this, 0xac);
        plane = 0;
    }
    else
    {
        RHShadowField<unsigned short>(this, 0x18c) = 2;
        RHShadowField<unsigned short>(this, 0x18e) = 2;
        plane = (RHShadowUnk005df9e0 *)(area->m_0 + 0xa8);
        height = RHShadowField<float>(this, 0xac) - plane->FUN_005df9e0(
            RHShadowField<float>(this, 0xa4), RHShadowField<float>(this, 0xa8));
        plane = (RHShadowUnk005df9e0 *)(RHShadowField<RHUnk00597a70 *>(this, 0x130)->m_0 + 0xa8);
    }
    unsigned short count = (unsigned short)m_158.m_list.size();
    if (height <= g_unk0x00677488)
    {
        height -= g_unk0x006774c8;
        for (unsigned short index = 0; index < count; ++index)
        {
            RHUnk005977e0 *obstacle = (RHUnk005977e0 *)m_158[index];
            undefined *object = obstacle->m_0;
            if (RHShadowField<undefined>(obstacle, 0x0b) && FUN_0059b6b0(object, plane))
            {
                FUN_0059c720(obstacle, plane);
                if (!FUN_00598b90(obstacle, plane))
                    return false;
            }
        }
        return true;
    }
    if (plane == 0)
    {
        for (unsigned short index = 0; index < count; ++index)
        {
            m_158.FUN_005c8e40(index);
            RHUnk005977e0 *obstacle = (RHUnk005977e0 *)*m_158.m_current;
            undefined *object = obstacle->m_0;
            if (RHShadowField<undefined>(obstacle, 0x0a))
            {
                FUN_0059d5b0(obstacle);
                if (!FUN_00598230(obstacle, 0, false))
                    return false;
            }
            height -= g_unk0x006774c8;
            bool above = height > g_unk0x00677488;
            unsigned remaining = (unsigned short)obstacle->m_34.m_list.size();
            while (remaining != 0)
            {
                obstacle->m_34.FUN_005c8e40(0);
                delete (RHUnk00564020 *)*obstacle->m_34.m_current;
                RHUnk005c9010Node *node = obstacle->m_34.m_list.m_head->m_next;
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
                operator delete(node);
                --obstacle->m_34.m_list.m_count;
                obstacle->m_34.m_dirty = true;
                --remaining;
            }
            if (above)
            {
                if (RHShadowField<undefined>(obstacle, 0x0a) && FUN_0059b1f0(object))
                {
                    FUN_0059d7f0(obstacle);
                    if (!FUN_00598230(obstacle, 0, true))
                        return false;
                }
            }
            else if (RHShadowField<undefined>(obstacle, 0x0b) && FUN_0059b380(object))
            {
                FUN_0059ce90(obstacle);
                if (!FUN_00598b90(obstacle, 0))
                    return false;
            }
            height += g_unk0x006774c8;
        }
        return true;
    }
    for (unsigned short index = 0; index < count; ++index)
    {
        m_158.FUN_005c8e40(index);
        RHUnk005977e0 *obstacle = (RHUnk005977e0 *)*m_158.m_current;
        undefined *object = obstacle->m_0;
        if (RHShadowField<undefined>(obstacle, 0x0a) && object != area->m_0)
        {
            FUN_0059b850(obstacle, plane);
            if (!FUN_00598230(obstacle, plane, false))
                return false;
        }
        height -= g_unk0x006774c8;
        bool above = height > g_unk0x00677488;
        unsigned remaining = (unsigned short)obstacle->m_34.m_list.size();
        while (remaining != 0)
        {
            delete (RHUnk00564020 *)obstacle->m_34[0];
            RHUnk005c9010Node *node = obstacle->m_34.m_list.m_head->m_next;
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;
            operator delete(node);
            --obstacle->m_34.m_list.m_count;
            obstacle->m_34.m_dirty = true;
            --remaining;
        }
        if (above)
        {
            if (RHShadowField<undefined>(obstacle, 0x0a) && object != area->m_0 && FUN_0059b510(object, plane))
            {
                FUN_0059bfb0(obstacle, plane);
                if (!FUN_00598230(obstacle, plane, true))
                    return false;
            }
        }
        else if (RHShadowField<undefined>(obstacle, 0x0b) && object != area->m_0 && FUN_0059b6b0(object, plane))
        {
            FUN_0059c720(obstacle, plane);
            if (!FUN_00598b90(obstacle, plane))
                return false;
        }
        height += g_unk0x006774c8;
    }
    return true;
}

void rh_shadowpolygon_emit(RHShadowPolygon *polygon, const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    polygon->DisplayDebug(box, zoom, actor, point, view, flags);
}
