#ifndef RHSCRIPTLISTCORE_H
#define RHSCRIPTLISTCORE_H

#include <iterator>
#include "RHProfilePointerList.h"

struct RHUnk00571160Position;

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
    void *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
    RHScriptIter &operator=(const RHScriptIter &other)
    {
        node = other.node;
        return *this;
    }
    RHScriptIter operator++(int)
    {
        RHScriptIter previous = *this;
        node = node->next;
        return previous;
    }
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

class RHUnk0046eb30
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool valid;
    char padding[3];
    int index;
    RHScriptIter erase(RHScriptIter position);
    void Unk0044e190(int wanted);
    void Unk0044eab0(RHUnk0046eb30 &source);
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter Unk0057c950(RHScriptIter position, const RHUnk00571160Position &value);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
    RHScriptIter InlineBegin()
    {
        RHScriptNode *first = head->next;
        return RHScriptIter(first);
    }
    RHScriptIter InlineEnd()
    {
        return RHScriptIter(head);
    }
    RHScriptNode *&SetCurrent(RHScriptIter position)
    {
        cursor = position.node;
        return cursor;
    }
    void GoToInline(int wanted)
    {
        bool dirty = valid;
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                SetCurrent(InlineBegin());
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted, category);
            }
            else
            {
                SetCurrent(InlineEnd());
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - size, category);
            }
            valid = false;
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
                        SetCurrent(InlineBegin());
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + size) / 2)
                        std::advance((std::list<void *>::iterator &)cursor, wanted - previous);
                    else
                    {
                        SetCurrent(InlineEnd());
                        std::advance((std::list<void *>::iterator &)cursor, wanted - size);
                    }
                }
                index = wanted;
            }
        }
    }
    void *&Get(int wanted)
    {
        bool dirty = valid;
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                SetCurrent(InlineBegin());
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted, category);
            }
            else
            {
                SetCurrent(InlineEnd());
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - size, category);
            }
            valid = false;
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
                        RHScriptIter &current = (RHScriptIter &)cursor;
                        current = FUN_0046eb80();
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + size) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - previous, category);
                    }
                    else
                    {
                        SetCurrent(InlineEnd());
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor((RHProfilePointerList::iterator &)cursor, wanted - size, category);
                    }
                }
                index = wanted;
            }
        }
        return cursor->data;
    }
};

class RHUnk0044e2e0 : public std::list<unsigned long>
{
public:
    void Unk(const unsigned long &value);
    iterator current;
    bool dirty;
    int index;
    bool m_18;
    int searchIndex;
    unsigned long searchValue;
};

#endif
