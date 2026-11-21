#ifndef RHSEQUENCEMANAGERLISTOPS_H
#define RHSEQUENCEMANAGERLISTOPS_H

#include "RHOrder.h"
#include "RHSeqList.h"
#include "RHSequenceManager.h"

template<class T>
inline T &RHManagerList<T>::operator[](int wanted)
{
    ((RHSeqList *)this)->GoTo(wanted);
    return *cursor;
}

template<class T>
inline void RHManagerCopyList<T>::push_back(const T &value)
{
    RHManagerNode<T> *next = Head();
    RHManagerNode<T> *previous = next->previous;
    RHManagerNode<T> *node = (RHManagerNode<T> *)::operator new(sizeof(RHManagerNode<T>));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
    ++_Size;
    valid = 1;
}

class RHSequenceElementCursor : public RHManagerList<RHSequenceElement *>
{
public:
    RHUnkIter end() { return RHUnkIter(Head()); }
    RHUnkIter insert(RHUnkIter pos, RHSequenceElement *const &value);
};

#endif
