#ifndef RHPROFILEPOINTERLIST_H
#define RHPROFILEPOINTERLIST_H

#include <list>

class RHPlayerProfile;

typedef std::list<RHPlayerProfile *> RHProfilePointerList;

class RHPlayerProfileListStorage : public RHProfilePointerList
{
public:
    typedef _Node Node;

};

void RHAdvanceProfileCursor(RHProfilePointerList::iterator &current, int distance,
                            std::bidirectional_iterator_tag category);

#endif
