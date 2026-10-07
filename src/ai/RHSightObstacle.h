#include "sb3dstuff.h"
#include <iterator>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};

class SBGeoBoundingBox2D
{
public:
    bool FUN_00607c70(SBFile &file);
    char m_00[0x14];
};

class RHUnkSectorPoints
{
public:
    SBGeoPoint2D &Unk0060cef0(unsigned index);
    void Unk0060ced0(const SBGeoPoint2D &point, unsigned index);
    char m_00[0x2c];
};

struct RHUnkSightVertex
{
    float m_00;
    float m_04;
    float m_08;
    float m_0c;
};

struct RHUnkSightVertexNode
{
    RHUnkSightVertexNode *next;
    RHUnkSightVertexNode *prev;
    RHUnkSightVertex data;
};

struct RHUnkSightVertexIter
{
    RHUnkSightVertexNode *node;
    RHUnkSightVertexIter(RHUnkSightVertexNode *value = 0) : node(value) {}
    RHUnkSightVertexIter &operator++() { node = node->next; return *this; }
    RHUnkSightVertexIter &operator--() { node = node->prev; return *this; }
};

void FUN_005c9010(RHUnkSightVertexIter &position, int distance, std::bidirectional_iterator_tag category);

class RHUnkSightVertexList
{
public:
    void GoTo(int index);
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
    char m_00[4];
    RHUnkSightVertexNode *m_head;
    int m_count;
    RHUnkSightVertexIter m_current;
    bool m_dirty;
    char m_11[3];
    int m_index;
    char m_18[0x18];
};

class RHSightObstacle
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    unsigned m_00;
    char m_04[8];
    RHUnk005dfd00 m_0c;
    SBGeoBoundingBox2D m_24;
    SBGeoBoundingBox2D m_38;
    RHUnkSightVertexList m_4c;
    RHUnkSectorPoints m_7c;
    RHUnk005dfb00 m_a8;
    RHUnk005dfb00 m_100;
    char m_158;
};
