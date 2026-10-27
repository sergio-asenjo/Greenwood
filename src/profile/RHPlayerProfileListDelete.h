#ifndef RHPLAYERPROFILELISTDELETE_H
#define RHPLAYERPROFILELISTDELETE_H

#include "RHPlayerProfileManager.h"
#include "RHPlayerProfile.h"

__forceinline void RHPlayerProfileList::DeleteAt(int index)
{
    bool dirty = m_dirty;
    int count = size();
    if (dirty)
    {
        if (index <= (count + 1) / 2)
        {
            std::bidirectional_iterator_tag category;
            {
                std::list<RHPlayerProfile *>::iterator first = begin();
                RHAdvanceProfileCursor(SetCurrent(first), index, category);
            }
        }
        else
        {
            std::bidirectional_iterator_tag category;
            {
                std::list<RHPlayerProfile *>::iterator last = end();
                RHAdvanceProfileCursor(SetCurrent(last), index - count, category);
            }
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
                    std::bidirectional_iterator_tag category;
                    {
                        std::list<RHPlayerProfile *>::iterator first = begin();
                        RHAdvanceProfileCursor(SetCurrent(first), index, category);
                    }
                }
                else
                {
                    int distance = index - previous;
                    std::bidirectional_iterator_tag category;
                    RHAdvanceProfileCursor(m_current, distance, category);
                }
            }
            else
            {
                if (index < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    RHAdvanceProfileCursor(m_current, index - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    std::list<RHPlayerProfile *>::iterator last = end();
                    RHAdvanceProfileCursor(SetCurrent(last), index - count, category);
                }
            }
            m_index = index;
        }
    }
    delete Current();
    iterator position = m_current;
    _Nodeptr node = (position++)._Mynode();
    _Acc::_Next(_Acc::_Prev(node)) = _Acc::_Next(node);
    _Acc::_Prev(_Acc::_Next(node)) = _Acc::_Prev(node);
    allocator.destroy(&_Acc::_Value(node));
    _Freenode(node);
    count = _Size - 1;
    m_dirty = true;
    _Size = count;
}

#endif
