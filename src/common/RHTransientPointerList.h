#ifndef RHTRANSIENTPOINTERLIST_H
#define RHTRANSIENTPOINTERLIST_H

#include <list>
#include "SBListCursor.h"

template<class T>
class RHTransientPointerList : public std::list<T *>
{
public:
    typedef std::list<T *> Base;
    typedef Base::_Node Node;
    RHTransientPointerList();
    ~RHTransientPointerList() { clear(); }
    unsigned &Count() { return _Size; }
    Node *Head() { return _Head; }
    __forceinline void GoTo(int index) { ((RHProfileListCursor *)this)->GoTo(index); }
    Node *cursor;
    bool dirty;
    char m_11[3];
    int index;
    char m_18[0xc];
};

#endif
