#include "SBNullstr.h"
#include "RHSightObstacle.h"
#include "SBGeoPolyLine2DList.h"
#include "SBGeoVector2D.h"
#include "RHUnk00613e90.h"
#include "RHPlaneCalls.h"
#include "RHScriptListCore.h"
#include "RHUnk005fc3b0.h"
#include "RHFastFindGrid.h"
#include "SBFilePosition.h"

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &offset);
};

#include "RHUnk0053bf20.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHUnkSectorPoints, 0x2c)
DECOMP_SIZE_ASSERT(RHUnk005df860, 0x58)
DECOMP_SIZE_ASSERT(RHUnk005dfd00, 0x18)
DECOMP_SIZE_ASSERT(RHSightObstacle, 0x15c)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnkSightVertex, 0x10)
DECOMP_SIZE_ASSERT(RHUnkSightVertexNode, 0x18)
DECOMP_SIZE_ASSERT(RHUnkSightVertexIter, 0x04)
DECOMP_SIZE_ASSERT(RHUnkSightVertexList, 0x30)

inline void RHSightInsertVertex(RHUnkSightVertexList &list, const RHUnkSightVertex &value)
{
    RHUnk0046eb30 &storage = (RHUnk0046eb30 &)list;
    storage.Unk0057c950(RHScriptIter(storage.head), (const RHUnk00571160Position &)value);
    list.m_dirty = true;
}

// FUNCTION: GAME 0x005a3ec0
void RHSightObstacle::FUN_005a3ec0()
{
    RHUnkSightVertex first;
    first.m_00 = 0.0f;
    first.m_04 = 0.0f;
    first.m_0c = 1.0f;
    RHSightInsertVertex(m_4c, first);
    m_7c.FUN_0060ceb0(SBGeoPoint2D(first.m_00, first.m_04));
    RHUnkSightVertex second;
    second.m_00 = 0.0f;
    second.m_04 = 1.0f;
    second.m_0c = 1.0f;
    RHSightInsertVertex(m_4c, second);
    m_7c.FUN_0060ceb0(SBGeoPoint2D(second.m_00, second.m_04));
    RHUnkSightVertex third;
    third.m_00 = 1.0f;
    third.m_04 = 1.0f;
    third.m_0c = 1.0f;
    RHSightInsertVertex(m_4c, third);
    m_7c.FUN_0060ceb0(SBGeoPoint2D(third.m_00, third.m_04));
    RHUnkSightVertex fourth;
    fourth.m_00 = 1.0f;
    fourth.m_04 = 0.0f;
    fourth.m_0c = 1.0f;
    RHSightInsertVertex(m_4c, fourth);
    m_7c.FUN_0060ceb0(SBGeoPoint2D(fourth.m_00, fourth.m_04));
    m_158 = 0;
    m_7c.FUN_0060c2e0();
    m_a8.Unk005df860(first.Upper(), second.Upper(), third.Upper());
    m_a8.Unk005dfa00();
    m_100.Unk005df860(first.Lower(), second.Lower(), third.Lower());
    m_100.Unk005dfa00();
    m_00 = 0x11;
}

// STUB: GAME 0x005a41e0
bool RHSightObstacle::Serialize(SBFile &file)
{
    SBGeoPoint2D point;
    int count = m_4c.m_count;
    RHUnkSightVertex vertex;
    if (!file.m_bLoading)
    {
        RHUnkSightVertexList &vertices = m_4c;
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            vertices.GoTo(i);
            vertex = vertices.m_current.node->data;
            point = m_7c.Unk0060cef0(i);
            if (file.Access(&vertex.m_00, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                // STRING: GAME 0x006b7848
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 538, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_04, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 539, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_08, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 540, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_0c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 541, "Serialize failed reason is %s", reason);
                return false;
            }
            point.Serialize(file);
        }
    }
    else
    {
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            if (file.Access(&vertex.m_00, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 550, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_04, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 551, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_08, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 552, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_0c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 553, "Serialize failed reason is %s", reason);
                return false;
            }
            point.Serialize(file);
            m_4c.At(i, std::bidirectional_iterator_tag()) = vertex;
            m_7c.Unk0060ced0(point, i);
        }
    }
    m_a8.FUN_005dfb00(file);
    m_100.FUN_005dfb00(file);
    m_0c.FUN_005dfd00(file);
    m_24.Serialize(file);
    m_38.Serialize(file);
    if (file.Access(&m_158, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 569, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

inline void RHSightObstacle::UpdateVertex(int index, const RHUnkSightVertex &vertex)
{
    m_4c[index] = vertex;
    m_7c.Unk0060ced0(SBGeoPoint2D(vertex.m_00, vertex.m_04), index);
    m_0c.FUN_005dfc80(vertex.Lower());
    m_0c.FUN_005dfc80(vertex.Upper());
    m_38.Unk00607dc0(SBGeoPoint2D(vertex.m_00, vertex.m_04 - vertex.m_08));
    m_38.Unk00607dc0(SBGeoPoint2D(vertex.m_00, vertex.m_04 - vertex.m_0c));
}

inline void RHSightObstacle::UpdatePlanes(const RHUnkSightVertex &first, const RHUnkSightVertex &second, const RHUnkSightVertex &third)
{
    m_158 = 0;
    m_a8.Unk005df860(first.Upper(), second.Upper(), third.Upper());
    m_a8.Unk005dfa00();
    m_100.Unk005df860(first.Lower(), second.Lower(), third.Lower());
    m_100.Unk005dfa00();
}

// STUB: GAME 0x005a4680
void RHSightObstacle::UpdateBox(const RHUnk00613e90 &position, const SBGeoVector2D &direction, const RHUnk00613e90 &size)
{
    SBGeoVector2D forward(direction);
    ((RHUnk005fc3b0 *)&forward)->FUN_005fc7c0(1.0f);
    SBGeoVector2D side(forward);
    side.Normal(true, 1.0f);
    side.m_y *= 0.57357645f;
    forward.m_y *= 0.57357645f;
    RHUnk00613e90 center;
    center.x = forward.m_x * 20.0f + position.x;
    center.y = forward.m_y * 20.0f + position.y;
    center.z = position.z;
    float *bounds = (float *)&m_0c;
    m_0c.Reset();
    m_38.FUN_00607d90();
    RHUnkSightVertex first;
    first.m_00 = center.x - side.m_x * size.x * 0.5f - forward.m_x * size.y * 0.5f;
    first.m_04 = center.y - side.m_y * size.x * 0.5f - forward.m_y * size.y * 0.5f;
    first.m_08 = center.z + size.z;
    first.m_0c = center.z;
    UpdateVertex(0, first);
    RHUnkSightVertex second;
    second.m_00 = center.x - side.m_x * size.x * 0.5f + forward.m_x * size.y * 0.5f;
    second.m_04 = center.y - side.m_y * size.x * 0.5f + forward.m_y * size.y * 0.5f;
    second.m_08 = center.z + size.z;
    second.m_0c = center.z;
    UpdateVertex(1, second);
    RHUnkSightVertex third;
    third.m_00 = center.x + (side.m_x * size.x + forward.m_x * size.y) * 0.5f;
    third.m_04 = center.y + (side.m_y * size.x + forward.m_y * size.y) * 0.5f;
    third.m_08 = center.z + size.z;
    third.m_0c = center.z;
    UpdateVertex(2, third);
    RHUnkSightVertex fourth;
    fourth.m_00 = center.x + side.m_x * size.x * 0.5f - forward.m_x * size.y * 0.5f;
    fourth.m_04 = center.y + side.m_y * size.x * 0.5f - forward.m_y * size.y * 0.5f;
    fourth.m_08 = center.z + size.z;
    fourth.m_0c = center.z;
    UpdateVertex(3, fourth);
    UpdatePlanes(first, second, third);
    RHUnk00613e90 corner;
    corner.x = bounds[0];
    corner.y = bounds[2];
    corner.z = bounds[4];
    m_24.Unk00607dc0(SBGeoPoint2D(corner.x, corner.y));
    corner.x = bounds[1];
    corner.y = bounds[3];
    corner.z = bounds[5];
    m_24.Unk00607dc0(SBGeoPoint2D(corner.x, corner.y));
}

// FUNCTION: GAME 0x005a5af0
void RHSightObstacle::Translate(const RHUnk00613e90 &offset)
{
    unsigned count = m_4c.m_count;
    if ((unsigned short)count > 0)
    {
        int i = 0;
        unsigned remaining = (unsigned short)count;
        do
        {
            m_4c[i].m_00 += offset.x;
            m_4c[i].m_04 += offset.y;
            m_4c[i].m_08 += offset.z;
            m_4c[i].m_0c += offset.z;
            ++i;
        } while (--remaining);
    }
    m_a8.FUN_005dfa20(offset);
    m_100.FUN_005dfa20(offset);
    float *bounds = (float *)&m_0c;
    bounds[0] += offset.x;
    float x1 = bounds[1];
    bounds[1] = x1 + offset.x;
    float y0 = offset.y;
    bounds[2] = y0 + bounds[2];
    float y1 = offset.y;
    bounds[3] = y1 + bounds[3];
    bounds[4] += offset.z;
    bounds[5] += offset.z;
    ((RHMobileUnk006091b0 *)&m_24)->FUN_006091b0(SBGeoVector2D(offset.x, offset.y));
    ((RHMobileUnk006091b0 *)&m_38)->FUN_006091b0(SBGeoVector2D(offset.x, offset.y - offset.z));
}

// FUNCTION: GAME 0x005df990
void *RHUnk005df860::FUN_005df990()
{
    return (char *)this + 0x3c;
}

// FUNCTION: GAME 0x005dfc40
void RHUnk005dfd00::FUN_005dfc40(RHUnk00613e90 point)
{
    m_00 = point.x;
    m_08 = point.y;
    m_10 = point.z;
}

// FUNCTION: GAME 0x005dfc60
void RHUnk005dfd00::FUN_005dfc60(RHUnk00613e90 point)
{
    m_04 = point.x;
    m_0c = point.y;
    m_14 = point.z;
}

// FUNCTION: GAME 0x00607dc0
void SBGeoBoundingBox2D::Unk00607dc0(const SBGeoPoint2D &point)
{
    float x = point.m_x;
    float y = point.m_y;
    if (!m_flag || x < m_p0.m_x) m_p0.m_x = x;
    if (!m_flag || x > m_p1.m_x) m_p1.m_x = x;
    if (!m_flag || m_p0.m_y > y) m_p0.m_y = y;
    if (!m_flag || m_p1.m_y < y) m_p1.m_y = y;
    m_flag = true;
}

// FUNCTION: GAME 0x00607e50
void SBGeoBoundingBox2D::FUN_00607e50(SBGeoPolyLine2DList *list)
{
    unsigned int count = (unsigned int)((RHUnk0053bf20 *)list)->FUN_0053bf20();
    for (unsigned int i = 0; i < count; ++i)
        Unk00607dc0(list->FUN_00610cb0(i));
}

// FUNCTION: GAME 0x00609050
int SBGeoBoundingBox2D::FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    m_p0 = first;
    m_p1 = second;
    m_flag = true;
    return m_p0.m_x <= m_p1.m_x && m_p0.m_y <= m_p1.m_y;
}

// FUNCTION: GAME 0x0060ceb0
void RHUnkSectorPoints::FUN_0060ceb0(const SBGeoPoint2D &point)
{
    m_28 = 0;
    m_29 = 0;
    ((RHUnkTargetPoints *)this)->FUN_00611100(point);
}

void RHSightObstacle::Emit(SBFile &file)
{
    FUN_005a3ec0();
    UpdateBox(RHUnk00613e90(0, 0, 0), SBGeoVector2D(0, 0), RHUnk00613e90(1, 1, 1));
    Translate(RHUnk00613e90(0, 0, 0));
    Serialize(file);
    m_a8.FUN_005df990();
    m_0c.FUN_005dfc40(RHUnk00613e90(1, 2, 3));
    m_0c.FUN_005dfc60(RHUnk00613e90(1, 2, 3));
    SBGeoPoint2D point;
    m_24.Unk00607dc0(point);
    m_24.FUN_00609050(point, point);
    m_7c.FUN_0060ceb0(point);
}

inline void RHFastInsertSightVertex(RHFastFindSightList<RHFastFindSightVertex> &list, const RHFastFindSightVertex &value)
{
    RHUnk0046eb30 &storage = (RHUnk0046eb30 &)list;
    storage.Unk0057c950(RHScriptIter(storage.head), (const RHUnk00571160Position &)value);
    list.m_dirty = true;
}

// STUB: GAME 0x005a3810
int RHUnk005a3450::Unk005a3810(SBFile &file, RHFastFindPointerArray &materials)
{
    unsigned char projectionFlag;
    unsigned char heightFlag;
    unsigned char activeFlag;
    unsigned char enabledFlag;
    unsigned char sectorFlag;
    RHFastFindSightVertex vertex;
    float minimum = 1.0e30f;
    unsigned short count;
    float maximum = -1.0e30f;
    RHUnk00613e90 bottom2;
    RHUnk00613e90 bottom1;
    RHUnk00613e90 bottom0;
    RHUnk00613e90 top1;
    RHUnk00613e90 top2;
    RHUnk00613e90 top0;
    int start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        file.Access(&vertex.x, 4);
        file.Access(&vertex.y, 4);
        file.Access(&vertex.lower, 4);
        if (vertex.lower < 0.1f)
            vertex.lower = 0.0f;
        file.Access(&vertex.upper, 4);
        float height = vertex.y - vertex.upper;
        if (height < minimum)
            minimum = height;
        if (height > maximum)
            maximum = height;
        RHFastInsertSightVertex(m_vertices, vertex);
        m_polygon.FUN_0060ceb0(SBGeoPoint2D(vertex.x, vertex.y));
        if (vertex.lower != 0.0f)
            m_158[0] = 0;
        switch (i)
        {
        case 1:
            bottom2.Set(vertex.x, vertex.y, vertex.upper);
            top1.Set(vertex.x, vertex.y, vertex.lower);
            break;
        case 2:
            bottom1.Set(vertex.x, vertex.y, vertex.upper);
            top2.Set(vertex.x, vertex.y, vertex.lower);
            break;
        case 0:
            bottom0.Set(vertex.x, vertex.y, vertex.upper);
            top0.Set(vertex.x, vertex.y, vertex.lower);
            break;
        }
    }
    m_polygon.FUN_0060c2e0();
    m_firstPlane.Unk005df860(bottom2, bottom1, bottom0);
    m_firstPlane.Unk005dfa00();
    m_secondPlane.Unk005df860(top1, top2, top0);
    m_secondPlane.Unk005dfa00();
    if (*(float *)((char *)m_firstPlane.FUN_005df990() + 8) < 0.0f)
    {
        m_firstPlane.Unk005df860(bottom2, bottom0, bottom1);
        m_firstPlane.Unk005dfa00();
        m_secondPlane.Unk005df860(top1, top0, top2);
        m_secondPlane.Unk005dfa00();
    }
    file.Access(&bottom2.x, 4);
    file.Access(&bottom2.y, 4);
    file.Access(&bottom2.z, 4);
    file.Access(&bottom1.x, 4);
    file.Access(&bottom1.y, 4);
    file.Access(&bottom1.z, 4);
    m_box.FUN_005dfc40(bottom2);
    m_box.FUN_005dfc60(bottom1);
    m_bounds.Unk00607dc0(SBGeoPoint2D(bottom2.x, bottom2.y));
    m_bounds.Unk00607dc0(SBGeoPoint2D(bottom1.x, bottom1.y));
    SBGeoPoint2D upperCorner(bottom1.x, maximum);
    SBGeoPoint2D lowerCorner(bottom2.x, minimum);
    m_otherBounds.FUN_00609050(lowerCorner, upperCorner);
    file.Access(&sectorFlag, 1);
    if (sectorFlag)
    {
        m_flags |= 4;
        file.Access(&m_sector, 2);
        file.Access(&m_layer, 2);
    }
    else
    {
        m_layer = 0xffff;
        m_sector = 0xffff;
    }
    file.Access(&enabledFlag, 1);
    if (enabledFlag)
        m_flags |= 2;
    else
        m_flags &= ~2;
    file.Access(&projectionFlag, 1);
    if (projectionFlag)
        m_flags |= 1;
    else
        m_flags &= ~1;
    file.Access(&activeFlag, 1);
    file.Access(&heightFlag, 1);
    if (heightFlag)
        m_flags |= 0x20;
    if (projectionFlag)
    {
        if (activeFlag)
            m_flags |= 8;
        else
            m_flags &= ~8;
    }
    int materialByte;
    file.Access(&materialByte, 1);
    *(int *)m_168 = materialByte & 0xff;
    RHFastFindGrid *grid = g_unk0x6c0a9c;
    unsigned short materialCount;
    file.Access(&materialCount, 2);
    for (unsigned short j = 0; j < materialCount; ++j)
    {
        unsigned short materialIndex;
        file.Access(&materialIndex, 2);
        if (materialIndex >= materials.size())
            SBAssert(1, "P:\\Robin Hood\\RHsightobstacle.cpp", 0x1c3,
                // STRING: GAME 0x006b786c
                "HALT ! STEHENBLEIBEN ! : Trying to associate non-existing material with sight obstacle !");
        void *material = materials.m_first[materialIndex];
        m_materials.InsertLast(material);
        grid->FUN_004e8bd0(material, m_layer, true);
        grid->FUN_004e99e0(material, m_layer, true);
    }
    return ((ToolboxPositionFile *)&file)->FUN_005f5440() - start;
}
