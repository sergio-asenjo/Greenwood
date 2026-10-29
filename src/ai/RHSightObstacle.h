#include "sb3dstuff.h"
#include "RHSectorActorList.h"
#include "Decomp.h"
#include <iterator>

#include "SBGeoPoint2D.h"

#include "RHUnk00613e90.h"

class SBGeoPolyLine2DList;
class SBGeoVector2D;

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    bool Serialize(SBFile &file);
    void FUN_00607d90();
    void Unk00607dc0(const SBGeoPoint2D &point);
    void FUN_00607e50(SBGeoPolyLine2DList *list);
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
    undefined m_10; // 0x10
    undefined m_11[3]; // 0x11
};

class RHUnkTargetPoints
{
public:
    void FUN_00611100(const SBGeoPoint2D &point);
};

// SIZE 0x2c
#include "RHUnkSectorPoints.h"

// SIZE 0x10
struct RHUnkSightVertex
{
    __forceinline RHUnk00613e90 Upper() const
    {
        float x = m_00;
        float y = m_04;
        float z = m_08;
        return RHUnk00613e90(x, y, z);
    }
    __forceinline RHUnk00613e90 Lower() const
    {
        float x = m_00;
        float y = m_04;
        float z = m_0c;
        return RHUnk00613e90(x, y, z);
    }
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
};

// SIZE 0x18
struct RHUnkSightVertexNode
{
    RHUnkSightVertexNode *next; // 0x00
    RHUnkSightVertexNode *prev; // 0x04
    RHUnkSightVertex data; // 0x08
};

// SIZE 0x04
struct RHUnkSightVertexIter
{
    RHUnkSightVertexNode *node; // 0x00
    RHUnkSightVertexIter(RHUnkSightVertexNode *value = 0) : node(value) {}
    RHUnkSightVertexIter &operator++() { node = node->next; return *this; }
    RHUnkSightVertexIter &operator--() { node = node->prev; return *this; }
};

void FUN_005c9010(RHUnkSightVertexIter &position, int distance, std::bidirectional_iterator_tag category);

// SIZE 0x30
class RHUnkSightVertexList
{
public:
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    RHUnkSightVertex &operator[](int index)
    {
        GoTo(index);
        return m_current.node->data;
    }
    RHUnkSightVertex &At(int index, std::bidirectional_iterator_tag category)
    {
        if (m_dirty)
        {
            if (index <= (m_count + 1) / 2)
            {
                m_current = RHUnkSightVertexIter(m_head->next);
                FUN_005c9010(m_current, index, category);
            }
            else
            {
                m_current = RHUnkSightVertexIter(m_head);
                FUN_005c9010(m_current, index - m_count, category);
            }
            m_dirty = false;
        }
        else
        {
            if (index == m_index)
                return m_current.node->data;
            if (index < m_index)
            {
                if (index < (m_index + 1) / 2)
                {
                    m_current = RHUnkSightVertexIter(m_head->next);
                    FUN_005c9010(m_current, index, category);
                }
                else
                    FUN_005c9010(m_current, index - m_index, category);
            }
            else
            {
                if (index < (m_index + m_count) / 2)
                    FUN_005c9010(m_current, index - m_index, category);
                else
                {
                    m_current = RHUnkSightVertexIter(m_head);
                    int distance = index - m_count;
                    while (distance > 0) { ++m_current; --distance; }
                    while (distance < 0) { --m_current; ++distance; }
                }
            }
        }
        m_index = index;
        return m_current.node->data;
    }
    undefined m_00[4]; // 0x00
    RHUnkSightVertexNode *m_head; // 0x04
    int m_count; // 0x08
    RHUnkSightVertexIter m_current; // 0x0c
    bool m_dirty; // 0x10
    undefined m_11[3]; // 0x11
    int m_index; // 0x14
    undefined m_18[0x18]; // 0x18
};

// SIZE 0x58
class RHUnkSightPlane
{
public:
    void *FUN_005df990();
    undefined m_00[0x58]; // 0x00
};

// SIZE 0x18
class RHUnkSightTriple
{
public:
    void FUN_005dfc40(int first, int second, int third);
    void FUN_005dfc60(int first, int second, int third);
    int m_00; // 0x00
    int m_04; // 0x04
    int m_08; // 0x08
    int m_0c; // 0x0c
    int m_10; // 0x10
    int m_14; // 0x14
};

// SIZE 0x15c
class RHSightObstacle
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void Translate(const RHUnk00613e90 &offset);
    void FUN_005a3ec0();
    void UpdateBox(const RHUnk00613e90 &position, const SBGeoVector2D &direction, const RHUnk00613e90 &size);
    void UpdateVertex(int index, const RHUnkSightVertex &vertex);
    void UpdatePlanes(const RHUnkSightVertex &first, const RHUnkSightVertex &second, const RHUnkSightVertex &third);
    undefined4 m_00; // 0x00
    undefined m_04[8]; // 0x04
    RHUnk005dfd00 m_0c; // 0x0c
    SBGeoBoundingBox2D m_24; // 0x24
    SBGeoBoundingBox2D m_38; // 0x38
    RHUnkSightVertexList m_4c; // 0x4c
    RHUnkSectorPoints m_7c; // 0x7c
    RHUnk005dfb00 m_a8; // 0xa8
    RHUnk005dfb00 m_100; // 0x100
    char m_158; // 0x158
};
