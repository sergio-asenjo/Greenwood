#include "SBNullstr.h"
#include "RHSightObstacle.h"
#include "SBGeoPolyLine2DList.h"
#include "SBGeoVector2D.h"
#include "RHUnk00613e90.h"
#include "RHPlaneCalls.h"
#include "RHScriptListCore.h"
#include "RHUnk005fc3b0.h"

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &offset);
};

#include "RHUnk0053bf20.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHUnkSectorPoints, 0x2c)
DECOMP_SIZE_ASSERT(RHUnkSightPlane, 0x58)
DECOMP_SIZE_ASSERT(RHUnkSightTriple, 0x18)
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
    ((RHUnk005df860 *)&m_a8)->Unk005df860(
        (const SBGeoPoint3D &)first.Upper(),
        (const SBGeoPoint3D &)second.Upper(),
        (const SBGeoPoint3D &)third.Upper());
    ((RHUnk005df860 *)&m_a8)->Unk005dfa00();
    ((RHUnk005df860 *)&m_100)->Unk005df860(
        (const SBGeoPoint3D &)first.Lower(),
        (const SBGeoPoint3D &)second.Lower(),
        (const SBGeoPoint3D &)third.Lower());
    ((RHUnk005df860 *)&m_100)->Unk005dfa00();
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
    ((RHUnk005df860 *)&m_a8)->Unk005df860((const SBGeoPoint3D &)first.Upper(), (const SBGeoPoint3D &)second.Upper(), (const SBGeoPoint3D &)third.Upper());
    ((RHUnk005df860 *)&m_a8)->Unk005dfa00();
    ((RHUnk005df860 *)&m_100)->Unk005df860((const SBGeoPoint3D &)first.Lower(), (const SBGeoPoint3D &)second.Lower(), (const SBGeoPoint3D &)third.Lower());
    ((RHUnk005df860 *)&m_100)->Unk005dfa00();
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
    ((RHUnk005df860 *)&m_a8)->FUN_005dfa20(offset);
    ((RHUnk005df860 *)&m_100)->FUN_005dfa20(offset);
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
void *RHUnkSightPlane::FUN_005df990()
{
    return m_00 + 0x3c;
}

// FUNCTION: GAME 0x005dfc40
void RHUnkSightTriple::FUN_005dfc40(int first, int second, int third)
{
    m_00 = first;
    m_08 = second;
    m_10 = third;
}

// FUNCTION: GAME 0x005dfc60
void RHUnkSightTriple::FUN_005dfc60(int first, int second, int third)
{
    m_04 = first;
    m_0c = second;
    m_14 = third;
}

// FUNCTION: GAME 0x00607dc0
void SBGeoBoundingBox2D::Unk00607dc0(const SBGeoPoint2D &point)
{
    float x = point.m_x;
    float y = point.m_y;
    if (!m_10 || x < m_00) m_00 = x;
    if (!m_10 || x > m_08) m_08 = x;
    if (!m_10 || m_04 > y) m_04 = y;
    if (!m_10 || m_0c < y) m_0c = y;
    m_10 = 1;
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
    *(SBGeoPoint2D *)&m_00 = first;
    *(SBGeoPoint2D *)&m_08 = second;
    m_10 = 1;
    return m_00 <= m_08 && m_04 <= m_0c;
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
    ((RHUnkSightPlane *)&m_a8)->FUN_005df990();
    ((RHUnkSightTriple *)&m_0c)->FUN_005dfc40(1, 2, 3);
    ((RHUnkSightTriple *)&m_0c)->FUN_005dfc60(1, 2, 3);
    SBGeoPoint2D point;
    m_24.Unk00607dc0(point);
    m_24.FUN_00609050(point, point);
    m_7c.FUN_0060ceb0(point);
}
