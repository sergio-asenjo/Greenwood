#ifndef RHMALIGNITYTARGETLIST_H
#define RHMALIGNITYTARGETLIST_H

#include "SBListCursor.h"

class RHElementActor;

class RHMalignityTargetList : public SBListCursor<std::list<RHElementActor *> >
{
public:
    bool m_searchValid;
    int m_searchIndex;
    RHElementActor *m_searchValue;
    void Clear()
    {
        clear();
        m_dirty = true;
    }
    void InsertLast(RHElementActor *const &actor)
    {
        push_back(actor);
        m_dirty = true;
    }
    int Find(RHElementActor *actor)
    {
        int count = size();
        m_searchValue = actor;
        m_searchValid = true;
        m_current = begin();
        int index = 0;
        while (index < count)
        {
            if (*m_current == m_searchValue)
                break;
            ++m_current;
            ++index;
        }
        if (index < count)
        {
            m_searchIndex = index;
            m_dirty = false;
            m_index = index;
        }
        else
        {
            m_dirty = true;
            m_searchIndex = -1;
        }
        return m_searchIndex;
    }
};

#endif
