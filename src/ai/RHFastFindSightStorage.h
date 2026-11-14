#ifndef RHFASTFINDSIGHTSTORAGE_H
#define RHFASTFINDSIGHTSTORAGE_H

#include <memory>
#include "RHSpriteListStorage.h"
#include "RHScriptListCore.h"

struct RHFastFindSightVertex
{
    float x;
    float y;
    float upper;
    float lower;
};

template <class T> class RHFastFindSightList
{
public:
    struct Node
    {
        Node *next;
        Node *previous;
        T value;
    };
    RHFastFindSightList(const std::allocator<T> &allocator = std::allocator<T>())
        : m_allocator(allocator)
    {
        Node *node = (Node *)operator new(sizeof(Node));
        node->next = node;
        node->previous = node;
        m_head = node;
        m_count = 0;
        m_dirty = true;
    }
    ~RHFastFindSightList()
    {
        ((RHUnk00564020 *)this)->RHUnk00564020::~RHUnk00564020();
    }
    T &At(int wanted)
    {
        bool dirty = m_dirty;
        int count = m_count;
        if (dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                m_current = m_head->next;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                m_current = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        m_current = (Node *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + count) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                    else
                    {
                        m_current = m_head;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
                    }
                }
                m_index = wanted;
            }
        }
        return m_current->value;
    }
    std::allocator<T> m_allocator;
    Node *m_head;
    int m_count;
    Node *m_current;
    bool m_dirty;
    int m_index;
    bool m_searchDirty;
    int m_searchIndex;
    T m_searchValue;
};

#endif
