#ifndef RHSPRITELISTSTORAGE_H
#define RHSPRITELISTSTORAGE_H

#include <memory>
#include "RHScriptListCore.h"

struct RHSpriteListNode
{
    RHSpriteListNode *next;
    RHSpriteListNode *previous;
    int value;
};

struct RHSpriteListIterator
{
    RHSpriteListNode *node;
    RHSpriteListIterator() {}
    RHSpriteListIterator(RHSpriteListNode *value) : node(value) {}
    RHSpriteListIterator(const RHSpriteListIterator &value) : node(value.node) {}
    RHSpriteListIterator &operator=(const RHSpriteListIterator &value) { node = value.node; return *this; }
    RHSpriteListIterator &operator++() { node = node->next; return *this; }
    RHSpriteListIterator operator++(int);
    int &operator*() { return node->value; }
};

class RHUnk00564020
{
public:
    RHUnk00564020(const std::allocator<int> &allocator = std::allocator<int>()) : m_allocator(allocator)
    {
        head = (RHSpriteListNode *)((RHUnk0046eb30 *)this)->Unk0059f720(0, 0);
        count = 0;
        dirty = true;
    }
    ~RHUnk00564020();
    std::allocator<int> m_allocator;
    RHSpriteListNode *head;
    int count;
    RHSpriteListIterator current;
    bool dirty;
    int index;
};

#endif
