#ifndef RHMENUWIDGETVECTOR_H
#define RHMENUWIDGETVECTOR_H

#include "RHCopyPointers.h"
#include <vector>

class RHMenuWidgetVector : public std::vector<void *>
{
public:
    void Clear()
    {
        iterator last = FUN_004598e0(end(), end(), begin());
        typedef void (RHMenuWidgetVector::*Destroy)(iterator, iterator);
        Destroy destroy = &RHMenuWidgetVector::_Destroy;
        (this->*destroy)(last, end());
        _Last = last;
    }
};

#endif
