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
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
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
    float FUN_005fc7c0(float);
    RHUnk005fc3b0 FUN_005fc9e0(float, float);
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
    void FUN_00607d90();
    void Unk00607dc0(const SBGeoPoint2D &);
};

// SIZE 0x0c
class SBGeoPoint3D
{
public:
    float m_0; // 0x00
    float m_4; // 0x04
    float m_8; // 0x08
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
    ~SBGeoVector2D() {}
};

SBGeoVector2D operator*(float, const SBGeoVector2D &);
class RHElementActor;
class RHviewParameters;
class RHUnk00597a70
{
public:
    undefined *m_0; // 0x00
    undefined m_pad4[0x28]; // 0x04
    SBGeoBoundingBox2D m_2c; // 0x2c
    ~RHUnk00597a70();
};

class RHShadowUnk005df9e0
{
public:
    float FUN_005df9e0(float, float);
};

class RHUnk00564020
{
public:
    ~RHUnk00564020();
};

class RHUnk0059f000
{
public:
    void FUN_0059f000();
};

class RHUnk0059ec90
{
public:
    void FUN_0059ec90();
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
    RHUnk005c9010Iterator FUN_0046eb80();

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

// SIZE 0x18
class RHShadowPolygonList
{
public:
    RHUnk0058e7f0List m_list; // +0: allocator, +4: head, +8: signed count
    RHUnk005c9010Iterator m_current; // +0xc
    bool m_dirty; // +0x10
    int m_index; // +0x14

    void FUN_005c8e40(int);

    void ClearNodes()
    {
        m_list.FUN_0044e8b0(RHUnk005c9010Iterator(m_list.m_head->m_next), RHUnk005c9010Iterator(m_list.m_head));
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
extern float g_unk0x00677488;
extern float g_unk0x0067749c;
extern float g_unk0x006774c8;

template<class T>
inline T &RHShadowField(void *object, unsigned offset)
{
    return *(T *)((undefined *)object + offset);
}

class RHShadowPolygon
{
public:
    undefined m_pad0[0x28]; // 0x00
    unsigned long m_28; // +0x28
    undefined m_pad2c[0x60]; // 0x2c
    float m_8c; // +0x8c; also compared as raw 0x3f800000
    undefined m_pad90[0x8c]; // 0x90
    undefined m_11c[0x18]; // 0x11c
    RHShadowPolygonList m_134; // +0x134; head +0x138, count +0x13c, cache +0x140/+0x144/+0x148
    undefined m_pad14c[0x0c]; // 0x14c
    RHShadowPolygonList m_158; // 0x158
    undefined m_pad170[0x20]; // 0x170
    RHUnk0059f000 *m_190; // 0x190
    RHUnk0059ec90 *m_194; // 0x194
    RHShadowPolygonList m_198; // 0x198
    undefined m_pad1b0[0x0c]; // 0x1b0
    RHShadowPolygonList m_1bc; // 0x1bc
    undefined m_pad1d4[0x0c]; // 0x1d4
    RHShadowPolygonList m_1e0; // 0x1e0

    void DisplayDebug(const SBGeoBoundingBox2D &, float, RHElementActor *, SBGeoPoint3D &, RHviewParameters &, unsigned long);
    void FUN_0058d990();
    void FUN_0058ec60();
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
    void FUN_0059d7f0(RHUnk005977e0 *);
};

#endif
