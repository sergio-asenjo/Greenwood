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

template<class T> class SBListAutoDeleteStorage : public std::list<T>
{
public:
    SBListAutoDeleteStorage() : m_dirty(true) {}
    ~SBListAutoDeleteStorage() { Clear(); }
    void Clear() { clear(); }
    void *Head() { return _Head; }
    unsigned &Count() { return _Size; }
    void Destroy()
    {
        for (m_current = begin(); m_current != end(); m_current++)
            if (*m_current)
                delete *m_current;
        Clear();
    }
    typename std::list<T>::iterator m_current;
    bool m_dirty;
    int m_index;
};

template<class T> class SBListAutoDelete : public SBListAutoDeleteStorage<T>
{
public:
    SBListAutoDelete() {}
    ~SBListAutoDelete() { Destroy(); }
};

#endif
