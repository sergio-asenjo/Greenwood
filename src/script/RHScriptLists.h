#ifndef RHSCRIPT_LISTS_H
#define RHSCRIPT_LISTS_H

#include <iterator>

struct RHScriptListNode
{
    RHScriptListNode *next;
    RHScriptListNode *previous;
    void *value;
};

struct RHScriptListIterator : std::iterator<std::bidirectional_iterator_tag, void *>
{
    RHScriptListNode *node;
    RHScriptListIterator(RHScriptListNode *value = 0) : node(value) {}
    RHScriptListIterator &operator=(const RHScriptListIterator &other)
    {
        node = other.node;
        return *this;
    }
    RHScriptListIterator &AssignNode(RHScriptListNode *value)
    {
        *(RHScriptListNode *volatile *)&node = value;
        return *this;
    }
    RHScriptListIterator &operator++() { node = node->next; return *this; }
    RHScriptListIterator &operator--() { node = node->previous; return *this; }
    void *&operator*() { return node->value; }
};

struct RHScriptIndexedList
{
    int allocator;
    RHScriptListNode *head;
    int count;
    RHScriptListIterator cursor;
    bool dirty;
    int index;

    RHScriptListIterator begin()
    {
        RHScriptListNode *sentinel = head;
        RHScriptListNode *first = *(RHScriptListNode *volatile *)&sentinel->next;
        return RHScriptListIterator(first);
    }
    RHScriptListIterator end()
    {
        RHScriptListNode *sentinel = *(RHScriptListNode *volatile *)&head;
        return RHScriptListIterator(sentinel);
    }

    void *&operator[](int wanted)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                cursor = begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
            }
            else
            {
                cursor = end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
            }
            dirty = false;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor.AssignNode(
                            *(RHScriptListNode *volatile *)&head->next), wanted, category);
                    }
                    else
                    {
                        int distance = wanted - previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, distance, category);
                    }
                }
                else
                {
                    if (wanted < (previous + size) / 2)
                        std::advance(cursor, wanted - previous);
                    else
                    {
                        cursor = end();
                        std::advance(cursor, wanted - size);
                    }
                }
                index = wanted;
            }
        }
        return *cursor;
    }
};

struct RHScriptSelectionEngine
{
    char padding[0x49f8];
    RHScriptZoneList selection;
};

#endif
