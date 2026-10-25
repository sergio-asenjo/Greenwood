#ifndef RHSECTORACTORITERATOR_H
#define RHSECTORACTORITERATOR_H

#include <list>
#include "RHProfilePointerList.h"

class RHElementActor;
struct RHSectorActorNode;

inline std::list<RHElementActor *>::iterator
RHAdvanceActorIterator(std::list<RHElementActor *>::iterator *current)
{
    typedef RHProfilePointerList::iterator Native;
    typedef Native (Native::*Increment)(int);
    typedef std::list<RHElementActor *>::iterator Iterator;
    typedef Iterator (Iterator::*Forward)(int);
    Increment increment = &Native::operator++;
    return (current->*(Forward)increment)(0);
}

template<> inline std::list<RHElementActor *>::~list()
{
    iterator first = begin();
    iterator last = end();
    while (first != last)
    {
        iterator current = first++;
        _Nodeptr node = RHAdvanceActorIterator(&current)._Mynode();
        _Acc::_Next(_Acc::_Prev(node)) = _Acc::_Next(node);
        _Acc::_Prev(_Acc::_Next(node)) = _Acc::_Prev(node);
        allocator.destroy(&_Acc::_Value(node));
        _Freenode(node);
        --_Size;
    }
    _Freenode(_Head);
    _Head = 0;
    _Size = 0;
}

class RHSectorActorConstIter : public std::iterator<std::bidirectional_iterator_tag, RHElementActor *>
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorConstIter(RHSectorActorNode *node) : m_p(node) {}
};

class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter(RHSectorActorNode *node) : RHSectorActorConstIter(node) {}
    RHSectorActorIter operator++(int)
    {
        typedef RHProfilePointerList::iterator Native;
        typedef Native (Native::*Increment)(int);
        typedef RHSectorActorIter (RHSectorActorIter::*Forward)(int);
        Increment increment = &Native::operator++;
        return (this->*(Forward)increment)(0);
    }
    RHElementActor *&operator*() const;
    RHSectorActorIter &operator++();
    RHSectorActorIter &operator--();
};

#endif
