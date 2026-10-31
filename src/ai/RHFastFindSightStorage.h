#ifndef RHFASTFINDSIGHTSTORAGE_H
#define RHFASTFINDSIGHTSTORAGE_H

#include <memory>
#include "RHSpriteListStorage.h"

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
