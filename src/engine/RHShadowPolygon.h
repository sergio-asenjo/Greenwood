#ifndef RHSHADOWPOLYGON_H
#define RHSHADOWPOLYGON_H

#include "SB.h"
#include "Decomp.h"
#include <iterator>

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    void Set(float x, float y)
    {
        m_x = x;
        m_y = y;
    }
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &);
    void FUN_005fc7c0(float);
    RHUnk005fc3b0 FUN_005fc9e0(float, float);
    float FUN_005fc680(const RHUnk005fc3b0 &, float) const;
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
    float m_c; // 0x0c
    bool m_10; // 0x10
    float Value0() const { return m_0; }
    float Value4() const { return m_4; }
    float Value8() const { return m_8; }
    float ValueC() const { return m_c; }
    const SBGeoPoint2D &Min() const { return *(const SBGeoPoint2D *)&m_0; }
    const SBGeoPoint2D &Max() const { return *(const SBGeoPoint2D *)&m_8; }
    void FUN_00607d90();
    void Unk00607dc0(const SBGeoPoint2D &);
    void SetValue0(float value) { m_10 = true; m_0 = value; }
    void SetValue4(float value) { m_10 = true; m_4 = value; }
    void SetValue8(float value) { m_10 = true; m_8 = value; }
    void SetValueC(float value) { m_10 = true; m_c = value; }
};

// SIZE 0x0c
class SBGeoPoint3D
{
public:
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
};

// SIZE 0x0c
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &other) const;
    float FUN_005df5f0(const RHUnk00613e90 &other) const;
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
};

class RHUnkSightPlane
{
public:
    void *FUN_005df990();
};

class RHUnk0059df10Object
{
public:
    undefined *m_0; // 0x00
};

// SIZE 0x30
class RHShadowUnk0060c260
{
public:
    undefined m_0[0x30]; // 0x00
    void FUN_0060c260(const SBGeoPoint2D &);
    void FUN_0060c280();
    const SBGeoPoint2D &FUN_0060c2b0(unsigned short);
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

SBGeoVector2D operator*(float, const SBGeoVector2D &);
class RHElementActor;
class RHviewParameters;
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
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

class RHShadowUnk0044e8b0
{
public:
    RHScriptIter FUN_0044e8b0(RHScriptIter, RHScriptIter);
};

// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    undefined m_00[0x14]; // 0x00
};

// SIZE 0x14
class RHShadowAreaBox
{
public:
    SBGeoPoint2D m_min; // 0x00
    SBGeoPoint2D m_max; // 0x08
    bool m_10; // 0x10
};

// SIZE 0x0c
class RHShadowPointListBase
{
public:
    undefined m_0; // 0x00
    RHScriptNode *m_head; // 0x04
    int m_count; // 0x08

    RHScriptIter FUN_0044e850(RHScriptIter, RHScriptIter);
};

class RHShadowPointStdList : public RHShadowPointListBase
{
public:
    ~RHShadowPointStdList()
    {
        FUN_0044e850(((RHUnk0046eb30 *)this)->FUN_0046eb80(), RHScriptIter(m_head));
        operator delete(m_head);
        m_head = 0;
        m_count = 0;
    }
};

class RHShadowVectorStdList : public RHShadowPointListBase
{
public:
    ~RHShadowVectorStdList();
};

// SIZE 0x30
template<class List>
class RHShadowPointList
{
public:
    List m_list; // 0x00
    RHScriptNode *m_current; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    bool m_18; // 0x18
    int m_1c; // 0x1c
    SBGeoPoint2D m_20; // 0x20
    undefined m_pad28[0x08]; // 0x28

    ~RHShadowPointList()
    {
        m_list.FUN_0044e850(((RHUnk0046eb30 *)&m_list)->FUN_0046eb80(), RHScriptIter(m_list.m_head));
    }
};

// SIZE 0x10
struct RHShadowVertex
{
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
};

class RHUnk00597a70
{
public:
    undefined *m_0; // 0x00
    RHShadowAreaBox m_4; // 0x04
    RHShadowAreaBox m_18; // 0x18
    RHShadowAreaBox m_2c; // 0x2c
    RHShadowPointList<RHShadowPointStdList> m_40; // 0x40
    RHShadowPointList<RHShadowVectorStdList> m_70; // 0x70
    ~RHUnk00597a70();
};

class RHShadowUnk005df9e0
{
public:
    float FUN_005df9e0(float, float);
    char m_00[0x4c];
    float m_4c;
    float m_50;
    float m_54;
};

class RHUnk00564020
{
public:
    ~RHUnk00564020();
};

// SIZE 0x1c
struct RHShadowIterator
{
    bool m_0; // 0x00
    bool m_1; // 0x01
    bool m_2; // 0x02
    int m_4; // 0x04
    int m_8; // 0x08
    int m_c; // 0x0c
    int m_10; // 0x10
    int m_14; // 0x14
    int m_18; // 0x18
};

// SIZE 0x24
struct RHShadowAlphaIterator : RHShadowIterator
{
    int m_1c; // 0x1c
    int m_20; // 0x20
};

// SIZE 0x14
struct RHShadowEvent
{
    undefined4 m_0; // 0x00
    int m_4; // 0x04
    int m_8; // 0x08
    RHShadowIterator *m_c; // 0x0c
    int m_10; // 0x10
};

class RHUnk0059f000
{
public:
    void FUN_0059f000();
    RHShadowIterator *FUN_0059f1a0();
};

// SIZE 0x14
class RHShadowBox
{
public:
    RHShadowBox();
    ~RHShadowBox() {}
    SBGeoPoint2D m_min; // 0x00
    SBGeoPoint2D m_max; // 0x08
    bool m_10; // 0x10
};

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
};

#include "RHMobileUnk006100e0.h"

class RHUnk0059ec90
{
public:
    void FUN_0059ec90();
    RHShadowEvent *FUN_0059ee30();
};


struct RHSectorActorNode;
class RHSectorActorIter
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorIter(RHSectorActorNode *node) : m_p(node) {}
    RHSectorActorIter operator++(int);
};

// SIZE 0x0c
struct RHUnk005c9010Node
{
    RHUnk005c9010Node *m_next; // 0x00
    RHUnk005c9010Node *m_prev; // 0x04
    RHUnk00597a70 *m_data; // 0x08
};

// SIZE 0x04
struct RHUnk005c9010Iterator : std::iterator<std::bidirectional_iterator_tag, RHUnk00597a70 *>
{
    RHUnk005c9010Node *m_node; // 0x00

    RHUnk005c9010Iterator FUN_0057c9c0(int);

    RHUnk005c9010Iterator(RHUnk005c9010Node *node = 0) : m_node(node) {}
    RHUnk005c9010Iterator &operator=(const RHUnk005c9010Iterator &other)
    {
        m_node = other.m_node;
        return *this;
    }
    RHUnk005c9010Iterator &operator++() { m_node = m_node->m_next; return *this; }
    RHUnk005c9010Iterator &AssignNode(RHUnk005c9010Node *node)
    {
        *(RHUnk005c9010Node *volatile *)&m_node = node;
        return *this;
    }
    RHUnk005c9010Iterator &operator--() { m_node = m_node->m_prev; return *this; }
    RHUnk00597a70 *&operator*() { return m_node->m_data; }
};

void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

// SIZE 0x0c
struct RHUnk0058e7f0List
{
    undefined4 m_0; // 0x00
    RHUnk005c9010Node *m_head; // 0x04
    int m_count; // 0x08

    RHUnk005c9010Iterator FUN_0044e8b0(RHUnk005c9010Iterator, RHUnk005c9010Iterator);
    RHUnk005c9010Iterator FUN_0046eb30(RHUnk005c9010Iterator);
    RHUnk005c9010Iterator FUN_0046eb30(RHSectorActorIter);
    RHUnk005c9010Iterator FUN_0046eb80();
    RHUnk005c9010Iterator FUN_00424410(RHUnk005c9010Iterator, RHUnk00597a70 *const &);

    ~RHUnk0058e7f0List()
    {
        RHUnk005c9010Node *last = m_head;
        RHSectorActorIter current((RHSectorActorNode *)last->m_next);
        while (current.m_p != (RHSectorActorNode *)last)
            FUN_0046eb30(current++);
        delete m_head;
        m_head = 0;
        m_count = 0;
    }
    int size() { return m_count; }
    RHUnk005c9010Iterator begin()
    {
        RHUnk005c9010Node *head = m_head;
        RHUnk005c9010Node *first = *(RHUnk005c9010Node *volatile *)&head->m_next;
        return RHUnk005c9010Iterator(first);
    }
    RHUnk005c9010Iterator end()
    {
        RHUnk005c9010Node *head = *(RHUnk005c9010Node *volatile *)&m_head;
        return RHUnk005c9010Iterator(head);
    }
};

void FUN_0059fb00(RHUnk00597a70 **, RHUnk00597a70 *const &);

// SIZE 0x18
class RHShadowPolygonList
{
public:
    RHUnk0058e7f0List m_list; // +0: allocator, +4: head, +8: signed count
    RHUnk005c9010Iterator m_current; // +0xc
    bool m_dirty; // +0x10
    int m_index; // +0x14

    void FUN_005c8e40(int);

    ~RHShadowPolygonList()
    {
        RHUnk005c9010Node *head = m_list.m_head;
        RHUnk005c9010Node *node = head->m_next;
        while (node != head)
        {
            RHUnk005c9010Node *current = node;
            node = node->m_next;
            m_list.FUN_0046eb30(RHSectorActorIter((RHSectorActorNode *)current));
        }
    }

    void ClearAll()
    {
        ((RHShadowUnk0044e8b0 *)&m_list)->FUN_0044e8b0(((RHUnk0046eb30 *)&m_list)->FUN_0046eb80(), RHScriptIter((RHScriptNode *)m_list.m_head));
        m_dirty = true;
    }

    void EraseAll()
    {
        RHUnk005c9010Node *last = m_list.m_head;
        RHSectorActorIter current((RHSectorActorNode *)last->m_next);
        while (current.m_p != (RHSectorActorNode *)last)
            m_list.FUN_0046eb30(current++);
        m_dirty = true;
    }

    RHUnk00597a70 *GetAt(int index)
    {
        FUN_005c8e40(index);
        return m_current.m_node->m_data;
    }

    void RemoveAt(int index)
    {
        Locate(index);
        RHUnk005c9010Node *node = m_current.m_node;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        operator delete(node);
        --m_list.m_count;
        m_dirty = true;
    }

    void InsertLastCopy(RHUnk00597a70 *const &value)
    {
        RHUnk005c9010Node *head = m_list.m_head;
        RHUnk005c9010Node *previous = head->m_prev;
        RHUnk005c9010Node *node = (RHUnk005c9010Node *)operator new(0xc);
        node->m_next = head ? head : node;
        node->m_prev = previous ? previous : node;
        head->m_prev = node;
        node->m_prev->m_next = node;
        FUN_0059fb00(&node->m_data, value);
        ++m_list.m_count;
        m_dirty = true;
    }

    void InsertLast(RHUnk00597a70 *const &value)
    {
        RHUnk005c9010Node *head = m_list.m_head;
        RHUnk005c9010Node *previous = head->m_prev;
        RHUnk005c9010Node *node = (RHUnk005c9010Node *)operator new(0xc);
        node->m_next = head ? head : node;
        node->m_prev = previous ? previous : node;
        head->m_prev = node;
        node->m_prev->m_next = node;
        if (&node->m_data)
            node->m_data = value;
        ++m_list.m_count;
        m_dirty = true;
    }

    void InsertBefore(RHUnk005c9010Node *next, RHUnk00597a70 *const &value)
    {
        RHUnk005c9010Node *node = (RHUnk005c9010Node *)((RHUnk0046eb30 *)&m_list)->Unk0059f720((RHScriptNode *)next, (RHScriptNode *)next->m_prev);
        next->m_prev = node;
        node->m_prev->m_next = node;
        FUN_0059fb00(&node->m_data, value);
        ++m_list.m_count;
    }

    void InsertNode(RHUnk005c9010Node *next, RHUnk00597a70 *const &value)
    {
        InsertBefore(next, value);
        m_dirty = true;
    }

    void InsertAtCurrent(int index, RHUnk00597a70 *const &value)
    {
        if (index == m_list.m_count)
            m_list.FUN_00424410(m_list.end(), value);
        else
        {
            FUN_005c8e40(index);
            m_list.FUN_00424410(m_current, value);
        }
        m_dirty = true;
    }

    void InsertAtIndex(int index, RHUnk00597a70 *const &value)
    {
        if (index == m_list.m_count)
            m_list.FUN_00424410(m_list.end(), value);
        else
        {
            FUN_005c8e40(index);
            InsertBefore(m_current.m_node, value);
        }
        m_dirty = true;
    }

    void ClearNodes()
    {
        ((RHShadowUnk0044e8b0 *)&m_list)->FUN_0044e8b0(RHScriptIter((RHScriptNode *)m_list.m_head->m_next), RHScriptIter((RHScriptNode *)m_list.m_head));
        m_dirty = true;
    }

    RHUnk00597a70 *&operator[](int index)
    {
        int count = (int)m_list.size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                m_current = m_list.begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current, index, category);
            }
            else
            {
                m_current = m_list.end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current, index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current.AssignNode(
                            *(RHUnk005c9010Node *volatile *)&m_list.m_head->m_next), index, category);
                    }
                    else
                    {
                        int distance = index - previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current, distance, category);
                    }
                }
                else
                {
                    if (index < (previous + count) / 2)
                        std::advance(m_current, index - previous);
                    else
                    {
                        m_current = m_list.end();
                        std::advance(m_current, index - count);
                    }
                }
                m_index = index;
            }
        }
        return *m_current;
    }

    void Locate(int index)
    {
        int count = (int)m_list.size();
        if (m_dirty)
        {
            RHUnk005c9010Node *head = m_list.m_head;
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = RHUnk005c9010Iterator(head->m_next), index, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = RHUnk005c9010Iterator(head), index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current = m_list.begin(), index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current, index - previous, category);
                    }
                }
                else if (index < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010(m_current, index - previous, category);
                }
                else
                {
                    m_current = m_list.end();
                    std::advance(m_current, index - count);
                }
                m_index = index;
            }
        }
    }
};

// SIZE 0x18
class RHShadowVertexList
{
public:
    undefined m_00[4]; // 0x00
    RHUnk005c9010Node *m_head; // 0x04
    int m_count; // 0x08
    RHUnk005c9010Iterator m_current; // 0x0c
    bool m_dirty; // 0x10
    undefined m_11[3]; // 0x11
    int m_index; // 0x14
    int size() { return m_count; }
    RHUnk005c9010Iterator begin()
    {
        RHUnk005c9010Node *head = m_head;
        RHUnk005c9010Node *first = *(RHUnk005c9010Node *volatile *)&head->m_next;
        return RHUnk005c9010Iterator(first);
    }
    RHUnk005c9010Iterator end() { return RHUnk005c9010Iterator(*(RHUnk005c9010Node *volatile *)&m_head); }

    void Locate(int index)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = begin(), index, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = end(), index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current.AssignNode(m_head->m_next), index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current, index - previous, category);
                    }
                }
                else if (index < (previous + count) / 2)
                {
                    int distance = index - previous;
                    for (; 0 < distance; --distance)
                        ++m_current;
                    for (; distance < 0; ++distance)
                        --m_current;
                }
                else
                {
                    m_current = RHUnk005c9010Iterator(m_head);
                    int distance = index - count;
                    for (; 0 < distance; --distance)
                        ++m_current;
                    for (; distance < 0; ++distance)
                        --m_current;
                }
                m_index = index;
            }
        }
    }
};

// SIZE 0x64 (accessed prefix; vertex list at +0x4c)
class RHShadowSight
{
public:
    undefined m_00[0x4c]; // 0x00
    RHShadowVertexList m_4c; // 0x4c
};

struct RHShadowUnk00594800Item
{
    undefined m_pad0[0x14]; // 0x00
    int m_14; // 0x14
    int m_18; // 0x18
};

// SIZE 0x24
class RHShadowPolygonFindList : public RHShadowPolygonList
{
public:
    bool m_18; // 0x18
    int m_1c; // 0x1c
    RHUnk00597a70 *m_20; // 0x20

    int Find(RHUnk00597a70 *value)
    {
        int count = m_list.size();
        m_20 = value;
        m_18 = true;
        m_current = RHUnk005c9010Iterator(m_list.m_head->m_next);
        int index;
        for (index = 0; index < count; ++index)
        {
            if (*m_current == m_20)
                break;
            ++m_current;
        }
        if (index < count)
        {
            m_1c = index;
            m_dirty = false;
            m_index = index;
        }
        else
        {
            m_dirty = true;
            m_1c = -1;
        }
        return m_1c;
    }

    void Seek(int index)
    {
        int count = m_list.size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = RHUnk005c9010Iterator((RHUnk005c9010Node *)((RHUnk0046eb30 *)&m_list)->FUN_0046eb80().node), index, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010(m_current = RHUnk005c9010Iterator(*(RHUnk005c9010Node *volatile *)&m_list.m_head), index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current = RHUnk005c9010Iterator((RHUnk005c9010Node *)((RHUnk0046eb30 *)&m_list)->FUN_0046eb80().node), index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current, index - previous, category);
                    }
                }
                else
                {
                    if (index < (previous + count) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current, index - previous, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(m_current = RHUnk005c9010Iterator(*(RHUnk005c9010Node *volatile *)&m_list.m_head), index - count, category);
                    }
                }
                m_index = index;
            }
        }
    }

    void RemoveAt(unsigned short index)
    {
        Seek(index);
        m_list.FUN_0046eb30(m_current);
        m_dirty = true;
    }

    void InsertAt(unsigned short index, RHUnk00597a70 *const &value)
    {
        if (index == m_list.m_count)
            m_list.FUN_00424410(m_list.end(), value);
        else
        {
            Seek(index);
            m_list.FUN_00424410(m_current, value);
        }
        m_dirty = true;
    }

    void SwapWithNext(unsigned short index)
    {
        FUN_005c8e40(index);
        RHUnk00597a70 *&first = *m_current;
        FUN_005c8e40(index + 1);
        RHUnk00597a70 *second = *m_current;
        *m_current = first;
        FUN_005c8e40(index);
        *m_current = second;
    }

};

// SIZE 0x14
struct RHShadowPointNode
{
    RHShadowPointNode *m_next; // 0x00
    RHShadowPointNode *m_prev; // 0x04
    RHUnk00613e90 m_data; // 0x08
};

void FUN_0059fb20(RHUnk00613e90 *, const RHUnk00613e90 &);

struct RHShadowAllocator
{
};

// SIZE 0x0c
class RHShadowPointNodeList
{
public:
    RHShadowAllocator m_alloc; // 0x00
    RHShadowPointNode *m_head; // 0x04
    int m_count; // 0x08

    RHShadowPointNodeList(const RHShadowAllocator &alloc = RHShadowAllocator()) : m_alloc(alloc), m_head(FUN_004243e0(0, 0)), m_count(0) {}
    ~RHShadowPointNodeList();
    RHShadowPointNode *FUN_004243e0(RHShadowPointNode *, RHShadowPointNode *);
};

// SIZE 0x2c
class RHShadowProjection
{
public:
    RHShadowPointNodeList m_list; // 0x00
    RHShadowPointNode *m_current; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    undefined m_18[0x08]; // 0x18
    RHUnk00613e90 m_20; // 0x20

    RHShadowProjection() : m_dirty(true) {}

    void InsertLast(const RHUnk00613e90 &value)
    {
        RHShadowPointNode *head = m_list.m_head;
        RHShadowPointNode *previous = head->m_prev;
        RHShadowPointNode *node = (RHShadowPointNode *)operator new(0x14);
        node->m_next = head ? head : node;
        node->m_prev = previous ? previous : node;
        head->m_prev = node;
        node->m_prev->m_next = node;
        FUN_0059fb20(&node->m_data, value);
        ++m_list.m_count;
        m_dirty = true;
    }
};

// SIZE 0x04
struct RHShadowEdge
{
    unsigned short m_0; // 0x00
    bool m_2; // 0x02
};

// SIZE 0x0c
struct RHShadowEdgeNode
{
    RHShadowEdgeNode *m_next; // 0x00
    RHShadowEdgeNode *m_prev; // 0x04
    RHShadowEdge m_data; // 0x08
};

// SIZE 0x18 (accessed prefix)
class RHShadowEdgeList
{
public:
    undefined m_00[4]; // 0x00
    RHShadowEdgeNode *m_head; // 0x04
    int m_count; // 0x08
    RHShadowEdgeNode *m_current; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    int size() { return m_count; }
};

// SIZE 0x4c
class RHUnk005977e0
{
public:
    undefined *m_0; // 0x00
    undefined m_pad4[0x0c]; // 0x04
    RHShadowPolygonList m_10; // 0x10
    undefined m_pad28[0x0c]; // 0x28
    RHShadowPolygonList m_34; // 0x34
    ~RHUnk005977e0();
};

// SIZE 0x1c
struct RHShadowPolygonActorPosition
{
    undefined m_pad0[0x18]; // 0x00
    float m_18; // 0x18
};

class RHUnk004a96a0
{
public:
    undefined m_pad0[0x10]; // 0x00
    unsigned short m_10; // 0x10
    undefined m_pad12[0x3e]; // 0x12
    RHShadowPolygonActorPosition *m_50; // 0x50
    void FUN_004a96a0(void *, void *, void *, bool);
};

class RHEngine
{
public:
    undefined m_pad0[0x475c]; // 0x00
    void *m_475c; // 0x475c
    undefined m_pad4760[0x164]; // 0x4760
    void *m_48c4; // 0x48c4
    undefined m_pad48c8[0x14]; // 0x48c8
    RHUnk004a96a0 **m_48dc; // 0x48dc
    RHUnk004a96a0 **m_48e0; // 0x48e0
    void FUN_004c9d20(void *);
    unsigned FUN_004c9d20Size()
    {
        if (m_48dc == 0)
            return 0;
        return m_48e0 - m_48dc;
    }
};

extern RHEngine *g_pEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
extern float g_unk0x00677488;
extern float g_unk0x006775d8;
extern float g_unk0x0067749c;
extern float g_unk0x006774c8;
extern float g_rhuirendererportrait_percent;

template<class T>
inline T &RHShadowField(void *object, unsigned offset)
{
    return *(T *)((undefined *)object + offset);
}

class RHMask
{
public:
    undefined m_pad0[0x24]; // 0x00
    unsigned char *m_data; // 0x24
};

// SIZE 0x18
class RHShadowViewport
{
public:
    RHShadowViewport();
    ~RHShadowViewport();
    char m_00[0x18]; // 0x00
};

class RHUnkFXDraw
{
public:
    undefined m_pad0[0x10c]; // 0x00
    unsigned short m_10c; // 0x10c
    unsigned short FUN_005e56c0(unsigned long);
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
};

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class SBDrawViewport;
class RHDrawManager
{
public:
    void DrawEllipse(const SBDrawViewport &, const SBGeoPoint2D &, unsigned short, unsigned short);
    static RHDrawManager *mpDrawManager;
};

extern float g_unk0x00677438;

// SIZE 0x14
class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    ~RHMapBox() {}
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    bool m_10; // 0x10
};

class __single_inheritance RHShadowPolygon;
typedef void (RHShadowPolygon::*RHShadowDrawLine)(unsigned short, int, int, int, int, int);

class RHShadowPolygon
{
public:
    undefined m_pad0[0x04]; // 0x00
    RHUnkFXDraw *m_4; // 0x04
    undefined m_pad8[0x18]; // 0x08
    int m_20; // 0x20
    int m_24; // 0x24
    unsigned long m_28; // +0x28
    undefined m_pad2c[0x18]; // 0x2c
    int m_44; // 0x44
    int m_48; // 0x48
    undefined4 m_4c; // 0x4c
    int m_50; // 0x50
    int m_54; // 0x54
    undefined m_pad58[0x08]; // 0x58
    char m_60; // 0x60
    bool m_61; // 0x61
    undefined m_pad62[0x02]; // 0x62
    RHMobileUnk00607da0 m_64; // 0x64
    undefined m_pad78[0x14]; // 0x78
    float m_8c; // +0x8c; also compared as raw 0x3f800000
    int m_90; // 0x90
    int m_94; // 0x94
    undefined m_pad98[0x08]; // 0x98
    float m_a0; // 0xa0
    SBGeoPoint3D m_a4; // 0xa4
    undefined m_padb0[0x08]; // 0xb0
    float m_b8; // 0xb8
    undefined m_padbc[0x04]; // 0xbc
    unsigned short m_c0; // 0xc0
    unsigned short m_c2; // 0xc2
    unsigned short m_c4; // 0xc4
    unsigned short m_c6; // 0xc6
    undefined m_padc8[0x54]; // 0xc8
    undefined m_11c[0x18]; // 0x11c
    RHShadowPolygonList m_134; // +0x134; head +0x138, count +0x13c, cache +0x140/+0x144/+0x148
    undefined m_pad14c[0x0c]; // 0x14c
    RHShadowPolygonList m_158; // 0x158
    undefined m_pad170[0x0c]; // 0x170
    int m_17c; // 0x17c
    int m_180; // 0x180
    undefined m_pad184[0x0c]; // 0x184
    RHUnk0059f000 *m_190; // 0x190
    RHUnk0059ec90 *m_194; // 0x194
    RHShadowPolygonList m_198; // 0x198
    undefined m_pad1b0[0x0c]; // 0x1b0
    RHShadowPolygonFindList m_1bc; // 0x1bc
    RHShadowPolygonList m_1e0; // 0x1e0
    undefined m_pad1f8[0x0c]; // 0x1f8
    RHShadowIterator *m_204; // 0x204
    RHShadowIterator *m_208; // 0x208
    RHShadowDrawLine m_20c; // 0x20c
    RHShadowDrawLine m_210; // 0x210
    RHShadowDrawLine m_214; // 0x214

    void FUN_0058c590(bool, unsigned short, unsigned short);
    void FUN_0058c630(unsigned short, unsigned short);
    void FUN_0058c6f0(bool);
    void FUN_0058c7a0(unsigned short, int, int, int, int, int);
    void FUN_0058c960(unsigned short, int, int, int, int, int);
    void FUN_0058cb40(unsigned short, int, int, int, int, int);
    void FUN_0058cd00(unsigned short, int, int, int, int, int);
    void FUN_0058cee0(unsigned short, int, int, int, int, int);
    void FUN_0058d0a0(unsigned short, int, int, int, int, int);
    void FUN_0058d290(unsigned short, int, int, int, int, int);
    void FUN_0058d450(unsigned short, int, int, int, int, int);
    void FUN_0058d630(unsigned short, int, int, int, int, int);
    void FUN_0058d7e0(unsigned short, int, int, int, int, int);
    void DisplayDebug(const SBGeoBoundingBox2D &, float, RHElementActor *, SBGeoPoint3D &, RHviewParameters &, unsigned long);
    void FUN_0058d990();
    void FUN_0058ea70();
    void FUN_0058ec60();
    void FUN_0058f200(RHMask *, SBGeoBoundingBox2D &, unsigned short, unsigned short, unsigned char);
    void FUN_0058f6b0(RHMask *, SBGeoBoundingBox2D &, unsigned short, unsigned short, unsigned char);
    void FUN_0058fe30(const SBGeoBoundingBox2D &);
    void FUN_00594800(RHUnk00597a70 *);
    void FUN_005949e0(RHUnk00597a70 *);
    void FUN_00594b40(RHUnk00597a70 *);
    bool FUN_00595630(const SBGeoBoundingBox2D &);
    void FUN_0058ffa0(RHUnk00597a70 *);
    void FUN_00590c90(RHUnk00597a70 *);
    void FUN_00592080(RHUnk00597a70 *);
    void FUN_005934b0(RHUnk00597a70 *);
    void FUN_00594bf0(const SBGeoBoundingBox2D &, float, RHElementActor *, SBGeoPoint3D &, RHviewParameters &);
    void FUN_00595020();
    void FUN_005959e0();
    void FUN_005971f0();
    void FUN_005973f0();
    void FUN_00597910();
    bool FUN_00597a70(RHUnk00597a70 *);
    bool FUN_0059e7e0(undefined *, RHUnk00564020 *);
    bool FUN_00598230(RHUnk005977e0 *, RHShadowUnk005df9e0 *, bool);
    bool FUN_00598b90(RHUnk005977e0 *, RHShadowUnk005df9e0 *);
    bool FUN_0059b1f0(undefined *);
    bool FUN_0059b380(undefined *);
    bool FUN_0059b510(undefined *, RHShadowUnk005df9e0 *);
    bool FUN_0059b6b0(undefined *, RHShadowUnk005df9e0 *);
    void FUN_0059b850(RHUnk005977e0 *, RHShadowUnk005df9e0 *);
    void FUN_0059bfb0(RHUnk005977e0 *, RHShadowUnk005df9e0 *);
    void FUN_0059c720(RHUnk005977e0 *, RHShadowUnk005df9e0 *);
    void FUN_0059ce90(RHUnk005977e0 *);
    void FUN_0059d5b0(RHUnk005977e0 *);
    float FUN_0059df10(RHUnk0059df10Object *);
    void FUN_0059e780(SBGeoPoint2D &, SBGeoPoint2D &, RHShadowUnk005df9e0 *);
    unsigned char FUN_0059e9b0(RHShadowPolygonList *);
    void FUN_0059a770(const SBGeoPoint2D &, const SBGeoPoint2D &);
    void FUN_0059eab0(RHShadowEvent *);
    void FUN_0059ada0(const SBGeoPoint2D &, long, const SBGeoPoint2D &, long);
    unsigned char FUN_0059ec40(SBGeoPoint2D *, SBGeoPoint2D *);
    unsigned char FUN_0059afc0(SBGeoPoint2D &, SBGeoPoint2D &, SBGeoPoint2D &);
    SBGeoBoundingBox2D &Bounds() { return *(SBGeoBoundingBox2D *)(RHShadowField<undefined *>(this, 0x130) + 4); }
    unsigned char FUN_005994f0(const SBGeoPoint3D &, SBGeoPoint2D &, bool, bool);
    void FUN_0059d7f0(RHUnk005977e0 *);
};

struct RHShadowMemoryRange
{
    unsigned long m_first;
    unsigned long m_last;
};

struct RHShadowMemoryNode
{
    RHShadowMemoryNode *m_next;
    RHShadowMemoryNode *m_previous;
    RHShadowMemoryRange m_value;
};

class RHShadowMemoryList
{
public:
    unsigned char m_allocator;
    RHShadowMemoryNode *m_head;
    unsigned m_count;
    void FUN_0059fbe0(const RHShadowMemoryRange &value);
    RHShadowMemoryNode *FUN_0059fcc0(RHShadowMemoryNode *next, RHShadowMemoryNode *previous);
};

class RHShadowMemoryBlock
{
public:
    unsigned char m_data[0x2c];
    void FUN_0059f4e0();
    RHShadowMemoryBlock *FUN_005a0ed0(unsigned flags);
    RHShadowMemoryBlock &FUN_005a0ef0(const RHShadowMemoryBlock &source);
};

class RHShadowMemoryVector
{
public:
    unsigned char m_allocator;
    RHShadowMemoryBlock *m_first;
    RHShadowMemoryBlock *m_last;
    RHShadowMemoryBlock *m_end;
    void FUN_0059fc40();
    RHShadowMemoryBlock *FUN_0059fcf0(RHShadowMemoryBlock *position, const RHShadowMemoryBlock &value);
    void FUN_0059ff20() const;
    RHShadowMemoryBlock *FUN_005a0000(RHShadowMemoryBlock *position, const RHShadowMemoryBlock &value);
    void FUN_005a0200() const;
    void FUN_005a02e0(RHShadowMemoryBlock *position, unsigned count, const RHShadowMemoryBlock &value);
    void FUN_005a0600(RHShadowMemoryBlock *position, unsigned count, const RHShadowMemoryBlock &value);
    void FUN_0059fef0(RHShadowMemoryBlock *first, RHShadowMemoryBlock *last);
    unsigned FUN_005a0990() const;
    RHShadowMemoryBlock *FUN_005a0920(const RHShadowMemoryBlock *first, const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination);
    void FUN_005a0960(RHShadowMemoryBlock *destination, unsigned count, const RHShadowMemoryBlock &value);
    RHShadowMemoryBlock *FUN_005a09c0(const RHShadowMemoryBlock *first, const RHShadowMemoryBlock *last, RHShadowMemoryBlock *destination);
    void FUN_005a0a00(RHShadowMemoryBlock *destination, unsigned count, const RHShadowMemoryBlock &value);
};

class RHShadowPointerVector
{
public:
    unsigned char m_allocator;
    void **m_first;
    void **m_last;
    void **m_end;
    void **FUN_0059fc80(void **position);
    void Destroy(void **first, void **last)
    {
        for (; first != last; ++first)
            std::_Destroy(first);
    }
};

#endif
