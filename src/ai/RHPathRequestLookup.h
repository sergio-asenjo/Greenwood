#ifndef RHPATHREQUESTLOOKUP_H
#define RHPATHREQUESTLOOKUP_H

#include "RHPathFinderCore.h"
#include "RHTitbitsCore.h"

inline RHpathRequest *&RHPathRequestList::operator[](int wanted)
{
    ((RHTitbitList *)this)->At(wanted);
    return cursor->request;
}

#endif
