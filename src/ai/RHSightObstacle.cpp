#include "SBNullstr.h"
#include "RHSightObstacle.h"
#include "SBGeoPolyLine2DList.h"

class RHUnk0053bf20
{
public:
    void *FUN_0053bf20() const;
};

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
    Serialize(file);
    ((RHUnkSightPlane *)&m_a8)->FUN_005df990();
    ((RHUnkSightTriple *)&m_0c)->FUN_005dfc40(1, 2, 3);
    ((RHUnkSightTriple *)&m_0c)->FUN_005dfc60(1, 2, 3);
    SBGeoPoint2D point;
    m_24.Unk00607dc0(point);
    m_24.FUN_00609050(point, point);
    m_7c.FUN_0060ceb0(point);
}
