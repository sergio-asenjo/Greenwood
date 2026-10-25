#ifndef SBLISTCURSOR_H
#define SBLISTCURSOR_H

#include "RHProfilePointerList.h"

template<class Storage> class SBListCursorStorage : public Storage
{
public:
    SBListCursorStorage() : m_dirty(true) {}
    typename Storage::iterator m_current;
    bool m_dirty;
    int m_index;
    typename Storage::iterator AdvanceCurrent()
    {
        typedef typename Storage::iterator Iterator;
        Iterator (Iterator::*increment)(int) = &Iterator::operator++;
        return (m_current.*increment)(0);
    }
    void Clear()
    {
        void (Storage::*clear)() = &Storage::clear;
        (this->*clear)();
        m_dirty = true;
    }
    void InsertLast(const typename Storage::value_type &value)
    {
        Storage::insert(Storage::end(), value);
        m_dirty = true;
    }
};

class RHProfileListCursor : public SBListCursorStorage<RHPlayerProfileListStorage>
{
public:
    void GoTo(int wanted);
};

template<class Storage> class SBListCursor : public SBListCursorStorage<Storage>
{
public:
    __forceinline void GoTo(int wanted)
    {
        ((RHProfileListCursor *)this)->GoTo(wanted);
    }
};

#endif
