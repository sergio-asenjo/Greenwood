#ifndef RHFASTFINDUNIQUELIST_H
#define RHFASTFINDUNIQUELIST_H

#include "Decomp.h"
#include "RHSpriteListStorage.h"
#include "RHSeqList.h"
#include "RHProfilePointerList.h"

void *FUN_0048f170(void *value);

struct RHFastFindUniqueNode
{
    RHFastFindUniqueNode *next;
    RHFastFindUniqueNode *previous;
    void *value;

    RHFastFindUniqueNode(RHFastFindUniqueNode *after, RHFastFindUniqueNode *before)
        : next(after ? after : this), previous(before ? before : this) {}
};

class RHFastFindUniqueRoot : public RHSpriteListRoot
{
public:
    RHFastFindUniqueRoot(const char &allocator) : RHSpriteListRoot(allocator) {}
    ~RHFastFindUniqueRoot()
    {
        typedef RHProfilePointerList::iterator Native;
        typedef Native (Native::*Increment)(int);
        typedef RHScriptIter (RHScriptIter::*Forward)(int);
        Increment increment = &Native::operator++;
        RHSpriteListNode *last = head;
        RHScriptIter current((RHScriptNode *)last->next);
        while (current.node != (RHScriptNode *)last)
        {
            ((RHUnk0046eb30 *)this)->erase((current.*(Forward)increment)(0));
        }
        operator delete(head);
        head = 0;
        count = 0;
    }
};

class RHFastFindUniqueList : public RHFastFindUniqueRoot
{
public:
    struct ConstIterator : public std::iterator<std::bidirectional_iterator_tag, void *>
    {
        RHFastFindUniqueNode *node;
        ConstIterator() {}
        ConstIterator(RHFastFindUniqueNode *value) : node(value) {}
    };

    struct Iterator : public ConstIterator
    {
        Iterator() {}
        Iterator(RHFastFindUniqueNode *value) : ConstIterator(value) {}
        void *&operator*() const { return node->value; }
        Iterator operator++(int)
        {
            Iterator previous = *this;
            node = node->next;
            return previous;
        }
    };

    RHFastFindUniqueList(const char &allocator) : RHFastFindUniqueRoot(allocator), m_changed(true) {}
    ~RHFastFindUniqueList()
    {
        RHFastFindUniqueNode *last = Head();
        RHFastFindUniqueNode *node = last->next;
        while (node != last)
        {
            RHFastFindUniqueNode *removed = node;
            node = ((RHFastFindUniqueNode *)FUN_0048f170(node))->next;
            ((RHUnk0046eb30 *)this)->erase(RHScriptIter((RHScriptNode *)removed));
        }
    }

    Iterator m_current;
    bool m_changed;
    undefined m_11[3];
    int m_index;
    bool m_searching;
    undefined m_19[3];
    int m_found;
    void *m_value;

    int GetSize() { return count; }
    Iterator Current() const { return m_current; }

    int Find(void *const &value)
    {
        void *sought = *(void *const volatile *)&value;
        RHFastFindUniqueNode *head = Head();
        m_value = sought;
        int count = this->count;
        m_searching = true;
        SetCurrent(Iterator(head->next));
        int index;
        for (index = 0; index < count; ++index, m_current++)
        {
            if (*Current() == m_value)
                break;
        }
        if (index < count)
        {
            m_found = index;
            m_changed = false;
            m_index = index;
        }
        else
        {
            m_changed = true;
            m_found = -1;
        }
        return m_found;
    }

    void InsertLast(void *value)
    {
        RHFastFindUniqueNode *head = Head();
        RHFastFindUniqueNode *previous = head->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(head, previous);
        head->previous = node;
        node->previous->next = node;
        if (&node->value)
            node->value = value;
        ++count;
        m_changed = true;
    }

    void InsertLastExternal(void *const &value)
    {
        RHFastFindUniqueNode *head = Head();
        RHFastFindUniqueNode *previous = head->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(head, previous);
        head->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++count;
        m_changed = true;
    }

    void InsertLastCall(void *const &value);

    void InsertFirst(void *value)
    {
        RHFastFindUniqueNode *position = Head()->next;
        RHFastFindUniqueNode *previous = position->previous;
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)operator new(0xc);
        node->RHFastFindUniqueNode::RHFastFindUniqueNode(position, previous);
        position->previous = node;
        node->previous->next = node;
        if (&node->value) node->value = value;
        ++count;
        m_changed = true;
    }

    void InsertLastAllocator(void *const &value)
    {
        RHFastFindUniqueNode *head = Head();
        RHFastFindUniqueNode *node = (RHFastFindUniqueNode *)((RHUnk0046eb30 *)this)->Unk0059f720((RHScriptNode *)head, (RHScriptNode *)head->previous);
        head->previous = node;
        node->previous->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
        ++count;
        m_changed = true;
    }

    void GoTo(int wanted)
    {
        int count = this->count;
        if (m_changed)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Begin()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
            }
            m_changed = false;
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
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(Begin()), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
                }
                m_index = wanted;
            }
        }
    }

    Iterator &SetCurrent(Iterator iterator)
    {
        m_current = iterator;
        return m_current;
    }

    Iterator SegmentBegin()
    {
        typedef RHScriptIter (RHUnk0046eb30::*Native)();
        typedef Iterator (RHFastFindUniqueList::*BeginCall)();
        Native begin = &RHUnk0046eb30::FUN_0046eb80;
        return (this->*(BeginCall)begin)();
    }

    void GoToSegment(int wanted)
    {
        int count = this->count;
        if (m_changed)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(SegmentBegin()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
            }
            m_changed = false;
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
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(SegmentBegin()), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)SetCurrent(End()), wanted - count, category);
                }
                m_index = wanted;
            }
        }
    }

    RHFastFindUniqueNode *&Head()
    {
        return (RHFastFindUniqueNode *&)head;
    }

    Iterator Begin() { return Iterator(Head()->next); }
    Iterator End() { return Iterator(Head()); }

    void Remove(unsigned short index)
    {
        GoTo(index);
        RHFastFindUniqueNode *node = m_current.node;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --count;
        m_changed = true;
    }
};

#endif
