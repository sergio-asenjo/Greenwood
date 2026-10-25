#ifndef RHCOPYPOINTERS_H
#define RHCOPYPOINTERS_H

#include <algorithm>

class RHMission;

inline void **FUN_004598e0(void **first, void **last, void **destination)
{
    typedef RHMission **(*Copy)(RHMission *const *, RHMission *const *, RHMission **);
    Copy copy = &std::copy;
    return (void **)copy((RHMission *const *)first, (RHMission *const *)last, (RHMission **)destination);
}

#endif
