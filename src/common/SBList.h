#ifndef SBLIST_H
#define SBLIST_H

#include <list>
#include "Decomp.h"

template<class T> class SBList : public std::list<T>
{
public:
    SBList() : m_dirty(true) {}
    ~SBList() { clear(); }
    T &Get(int wanted);
    void RemoveAll()
    {
        typedef std::list<T> List;
        typedef typename List::iterator (List::*Erase)(typename List::iterator, typename List::iterator);
        Erase erase = &List::erase;
        (this->*erase)(begin(), end());
        m_dirty = true;
    }
    void InsertLast(const T &value)
    {
        typedef std::list<T> List;
        typedef typename List::iterator (List::*Insert)(typename List::iterator, const T &);
        Insert insert = &List::insert;
        (this->*insert)(end(), value);
        m_dirty = true;
    }
    typename std::list<T>::iterator m_current;
    bool m_dirty;
    int m_index;
    undefined m_18[8];
    T m_20;
};

#endif
