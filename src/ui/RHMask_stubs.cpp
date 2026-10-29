#include "SBNullstr.h"
#include "RHMask.h"

void RHMaskPointArray::InsertLast(const SBGeoPoint2D &) {}

// TEMPLATE: GAME 0x005008e0 FOLDED
// ?Destroy@RHMaskObstacleStorage@@QAEXPAPAX0@Z
void RHMaskObstacleStorage::Destroy(void **, void **) {}

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?Ucopy@RHMaskObstacleArray@@QAEPAPAXPBQAX0PAPAX@Z
void **RHMaskObstacleArray::Ucopy(void *const *first, void *const *last, void **dest)
{
    for (; first != last; ++dest, ++first)
        if (dest)
            *dest = *first;
    return dest;
}
