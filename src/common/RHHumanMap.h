#ifndef RHHUMANMAP_H
#define RHHUMANMAP_H

#include "Decomp.h"

struct RHHumanMapNode
{
    RHHumanMapNode *m_left;
    RHHumanMapNode *m_parent;
    RHHumanMapNode *m_right;
    int m_key;
    unsigned int m_value;
};

struct RHHumanMapIterator
{
    RHHumanMapNode *m_node;
    RHHumanMapIterator(RHHumanMapNode *node) : m_node(node) {}
    RHHumanMapNode &operator*() const { return *m_node; }
    RHHumanMapNode *operator->() const { return &**this; }
    bool operator==(const RHHumanMapIterator &other) const { return m_node == other.m_node; }
    bool operator!=(const RHHumanMapIterator &other) const { return !(*this == other); }
};

class RHHumanMap
{
public:
    RHHumanMapNode *FUN_00588060(const int &key);
    RHHumanMapIterator end() const { return RHHumanMapIterator(m_head); }
    RHHumanMapIterator find(const int &key)
    {
        RHHumanMapIterator position = FUN_00588060(key);
        return position == end() || key < position->m_key ? end() : position;
    }
    undefined m_00[4];
    RHHumanMapNode *m_head;
    unsigned int m_08;
    unsigned int m_0c;
};

#endif
