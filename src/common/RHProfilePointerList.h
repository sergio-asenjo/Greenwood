#ifndef RHPROFILEPOINTERLIST_H
#define RHPROFILEPOINTERLIST_H

#include <list>

class RHPlayerProfile;

typedef std::list<RHPlayerProfile *> RHProfilePointerList;

class RHPlayerProfileListStorage : public RHProfilePointerList
{
public:
    typedef _Node Node;

    __forceinline iterator Erase(iterator position, volatile bool &dirty)
    {
        _Nodeptr node = (position++)._Mynode();
        _Acc::_Next(_Acc::_Prev(node)) = _Acc::_Next(node);
        _Acc::_Prev(_Acc::_Next(node)) = _Acc::_Prev(node);
        allocator.destroy(&_Acc::_Value(node));
        _Freenode(node);
        size_type count = _Size - 1;
        dirty = true;
        _Size = count;
        return position;
    }
};

void RHAdvanceProfileCursor(RHProfilePointerList::iterator &current, int distance,
                            std::bidirectional_iterator_tag category);

#endif
