#ifndef RHPLAYERPROFILEMANAGER_H
#define RHPLAYERPROFILEMANAGER_H

#include "RHSaveGame.h"
#include <iterator>
#include <list>

class RHElementActor;
class RHUnk00597a70;
struct RHSectorActorNode;

class RHSectorActorConstIter
{
public:
    RHSectorActorNode *m_p;
};

class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter operator++(int);
};

class RHSectorActorList
{
public:
    char m_data[0x24];
    void Unk005c8e40(int);
};

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
    RHUnk005c9010Iterator &operator--() { m_node = m_node->m_prev; return *this; }
    RHUnk00597a70 *&operator*() { return m_node->m_data; }
};

void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **, RHSequenceElement *const *);
};

class RHPlayerProfile
{
public:
    RHPlayerProfile();
    ~RHPlayerProfile();
    bool Serialize(SBFile &file);
    char m_data[0x74]; // [0x00, 0x74): allocation at 0x0055e040
};

class RHPlayerProfileListStorage : public std::list<RHPlayerProfile *>
{
public:
    __forceinline iterator begin() { return iterator(_Head->_Next); }
    __forceinline iterator end() { return iterator(_Head); }
    void FUN_004e6c10();
    __forceinline _Nodeptr BuyNode(_Nodeptr next, _Nodeptr previous)
    {
        _Nodeptr node = (_Nodeptr)allocator._Charalloc(sizeof(_Node));
        _Acc::_Next(node) = next != 0 ? next : node;
        _Acc::_Prev(node) = previous != 0 ? previous : node;
        return node;
    }
    __forceinline iterator insert(iterator position, RHPlayerProfile *const &value)
    {
        _Nodeptr node = position._Mynode();
        _Acc::_Prev(node) = BuyNode(node, _Acc::_Prev(node));
        node = _Acc::_Prev(node);
        _Acc::_Next(_Acc::_Prev(node)) = node;
        RHSeqList::CopyData((RHSequenceElement **)&_Acc::_Value(node), (RHSequenceElement *const *)&value);
        ++_Size;
        return iterator(node);
    }
};

class RHPlayerProfileList
{
public:
    RHPlayerProfileListStorage m_list; // +0x00: allocator, head +0x04, count +0x08
    std::list<RHPlayerProfile *>::iterator m_current; // +0x0c
    bool m_dirty; // +0x10
    int m_index; // +0x14
    char m_18[0xc]; // [0x18, 0x24)

    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    __forceinline std::list<RHPlayerProfile *>::iterator begin() { return m_list.begin(); }
    __forceinline std::list<RHPlayerProfile *>::iterator end() { return m_list.end(); }
    void RemoveAll()
    {
        m_current = begin();
        while (m_current != end())
        {
            delete *m_current;
            (*(RHSectorActorIter *)&m_current)++;
        }
        m_list.FUN_004e6c10();
        m_dirty = true;
    }
    void InsertLast(RHPlayerProfile *const &value)
    {
        m_list.insert(m_list.end(), value);
        m_dirty = true;
    }
    __forceinline RHPlayerProfile *Current() const { return *m_current; }
    __forceinline RHPlayerProfile *&GetProfile(int index)
    {
        GoTo(index);
        return *m_current;
    }
    RHPlayerProfile *operator[](int index)
    {
        int count = m_list.size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                m_current = ((std::list<RHPlayerProfile *> &)m_list).begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010(*(RHUnk005c9010Iterator *)&m_current, index, category);
            }
            else
            {
                m_current = ((std::list<RHPlayerProfile *> &)m_list).end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010(*(RHUnk005c9010Iterator *)&m_current, index - count, category);
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
                        m_current = ((std::list<RHPlayerProfile *> &)m_list).begin();
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(*(RHUnk005c9010Iterator *)&m_current, index, category);
                    }
                    else
                    {
                        int distance = index - previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(*(RHUnk005c9010Iterator *)&m_current, distance, category);
                    }
                }
                else
                {
                    if (index < (previous + count) / 2)
                    {
                        int distance = index;
                        RHUnk005c9010Iterator &current = *(RHUnk005c9010Iterator *)&m_current;
                        distance -= previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010(current, distance, category);
                    }
                    else
                    {
                        m_current = ((std::list<RHPlayerProfile *> &)m_list).end();
                        std::advance(m_current, index - count);
                    }
                }
                m_index = index;
            }
        }
        return Current();
    }
};

class RHPlayerProfileManager
{
public:
    bool Load();
    bool Save() const;
    bool FUN_0055d830();
    static const std::string &GetProfilesDirectory();
    void Emit();

    unsigned long m_00; // +0x00: four-byte archive field
    mutable RHPlayerProfileList m_profiles; // +0x04: head +0x08, count +0x0c, cursor +0x10
    RHPlayerProfile *m_active; // +0x28
};

#endif
