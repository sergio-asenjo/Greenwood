#ifndef RHPATHARRAY_H
#define RHPATHARRAY_H

#include <vector>

class RHWaypoint;

class RHPathArray : public std::vector<RHWaypoint *>
{
public:
    unsigned size() { return _First == 0 ? 0 : _Last - _First; }
    unsigned short Count(bool snapshot = false)
    {
        RHWaypoint **first = _First;
        if (!first)
            return 0;
        RHWaypoint **last = snapshot ? *reinterpret_cast<RHWaypoint **volatile *>(&_Last) : _Last;
        return last - first;
    }
    RHWaypoint **const &First() const { return _First; }
};

#endif
