#ifndef RHSECTORACTORITERATOR_H
#define RHSECTORACTORITERATOR_H

#include <list>

class RHElementActor;
struct RHSectorActorNode;

class RHSectorActorConstIter
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
        typedef std::list<RHElementActor *>::iterator Native;
        typedef Native (Native::*Increment)(int);
        typedef RHSectorActorIter (RHSectorActorIter::*Forward)(int);
        Increment increment = &Native::operator++;
        return (this->*(Forward)increment)(0);
    }
    RHElementActor *&operator*() const;
};

#endif
