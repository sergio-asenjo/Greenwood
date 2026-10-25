#ifndef RHSECTORACTORLIST_H
#define RHSECTORACTORLIST_H

#include "RHSectorActorIterator.h"
#include "SBListCursor.h"

class RHElementActor;

struct RHSectorActorNode
{
    RHSectorActorNode *m_next;
    RHSectorActorNode *m_prev;
    RHElementActor *m_data;
};

struct RHSectorActorAccess
{
    static RHSectorActorNode *&Next(RHSectorActorNode *p) { return p->m_next; }
    static RHElementActor *&Value(RHSectorActorNode *p) { return p->m_data; }
};

inline RHElementActor *&RHSectorActorIter::operator*() const { return RHSectorActorAccess::Value(m_p); }
inline RHSectorActorIter &RHSectorActorIter::operator++() { m_p = m_p->m_next; return *this; }
inline RHSectorActorIter &RHSectorActorIter::operator--() { m_p = m_p->m_prev; return *this; }

class RHSectorActorList
{
public:
    char m_pad0[4];
    RHSectorActorNode *m_head;
    int m_count;
    RHSectorActorIter m_cur;
    char m_valid;
    char m_pad11[3];
    int m_index;
    char m_searchValid;
    char m_pad19[3];
    int m_searchIndex;
    RHElementActor *m_searchValue;

    int Unk004b8f80(RHElementActor *const &actor, bool mode);
    RHSectorActorIter insert(RHSectorActorIter pos, RHElementActor *const &actor);
    RHSectorActorIter erase(RHSectorActorIter pos);
    __forceinline void Unk005c8e40(int index)
    {
        ((RHProfileListCursor *)this)->GoTo(index);
    }
    int FindValue(RHElementActor *actor) { return Unk004b8f80(actor, true); }
    RHSectorActorIter begin() { return RHSectorActorIter(RHSectorActorAccess::Next(m_head)); }
    RHSectorActorIter Current() const { return m_cur; }
    RHElementActor *CurrentValue() const { return *m_cur; }
    int Find(RHElementActor *actor)
    {
        int count = m_count;
        m_searchValue = actor;
        m_searchValid = 1;
        m_cur = begin();
        int index = 0;
        for (; index < count; ++index, m_cur++)
        {
            if (CurrentValue() == m_searchValue)
                break;
        }
        if (index < count)
        {
            m_searchIndex = index;
            m_valid = 0;
            m_index = index;
        }
        else
        {
            m_valid = 1;
            m_searchIndex = -1;
        }
        return m_searchIndex;
    }
};

#endif
