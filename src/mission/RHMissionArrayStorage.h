#ifndef RHMISSIONARRAYSTORAGE_H
#define RHMISSIONARRAYSTORAGE_H

#include <vector>

class RHMissionArrayStorage
{
public:
    void *FUN_004609a0(void *first, void *last)
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        return (((Values *)this)->*erase)((int *)first, (int *)last);
    }
    void FUN_004e5820(void *position, const unsigned long &value)
    {
        typedef std::vector<unsigned long> Values;
        unsigned long *(Values::*insert)(unsigned long *, const unsigned long &) = &Values::insert;
        (((Values *)this)->*insert)((unsigned long *)position, value);
    }
};

#endif
