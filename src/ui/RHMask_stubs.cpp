#include "SBNullstr.h"
#include "RHMask.h"

void RHMaskPointArray::InsertLast(const SBGeoPoint2D &) {}

void **RHMaskObstacleArray::Ucopy(void *const *first, void *const *last, void **dest)
{
    for (; first != last; ++dest, ++first)
        if (dest)
            *dest = *first;
    return dest;
}
