#ifndef RHSHADOWPOLYGON_H
#define RHSHADOWPOLYGON_H

#include "SB.h"
#include <iterator>

class SBGeoBoundingBox2D;
class SBGeoPoint3D;
class RHElementActor;
class RHviewParameters;
class RHUnk00597a70;

struct RHUnk005c9010Node
{
    RHUnk005c9010Node *m_next;
    RHUnk005c9010Node *m_prev;
    RHUnk00597a70 *m_data;
};

struct RHUnk005c9010Iterator : std::iterator<std::bidirectional_iterator_tag, RHUnk00597a70 *>
{
    RHUnk005c9010Node *m_node;

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

struct RHUnk0058e7f0List
{
    int m_0;
    RHUnk005c9010Node *m_head;
    int m_count;

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

class RHShadowPolygonList
{
public:
    RHUnk0058e7f0List m_list; // +0: allocator, +4: head, +8: signed count
    RHUnk005c9010Iterator m_current; // +0xc
    bool m_dirty; // +0x10
    int m_index; // +0x14

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

class RHEngine
{
public:
    void FUN_004c9d20(void *);
};

extern RHEngine *g_pEngine;
extern float g_unk0x00677488;
extern float g_unk0x0067749c;

class RHShadowPolygon
{
public:
    char m_pad0[0x28];
    unsigned long m_28; // +0x28
    char m_pad2c[0x60];
    float m_8c; // +0x8c; also compared as raw 0x3f800000
    char m_pad90[0x8c];
    char m_11c[0x18]; // +0x11c: passed by address to 0x004c9d20
    RHShadowPolygonList m_134; // +0x134; head +0x138, count +0x13c, cache +0x140/+0x144/+0x148

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
};

#endif
