#ifndef RHMOTIONAREALIST_H
#define RHMOTIONAREALIST_H

#include <list>
#include "SBListCursor.h"

template<class T>
class RHMotionAreaListStorage : public std::list<T>
{
public:
    RHMotionAreaListStorage(const std::allocator<T> &allocator = std::allocator<T>()) : std::list<T>(allocator) {}
    ~RHMotionAreaListStorage() { clear(); }
};

template<class T>
class RHMotionAreaList : public RHMotionAreaListStorage<T>
{
public:
    RHMotionAreaList() : RHMotionAreaListStorage<T>(std::allocator<T>()), m_dirty(true) {}
    void *m_cursor;
    bool m_dirty;
    char m_11[3];
    int m_index;
    char m_18[0xc];
    __forceinline void GoTo(int index)
    {
        ((RHProfileListCursor *)this)->GoTo(index);
    }
    typename std::list<T>::iterator Cursor() const
    {
        typedef typename std::list<T>::_Nodeptr Node;
        typedef typename std::list<T>::iterator Iterator;
        return Iterator((Node)m_cursor);
    }
    T &Current() { return *Cursor(); }
    void InsertLast(const T &value)
    {
        insert(end(), value);
        m_dirty = true;
    }
};

#endif
