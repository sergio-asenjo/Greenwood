#include "RHSprite.h"

// Parked: VC6 masks FUN_005bdbf0's unsigned-short return (and eax,0xffff) when
// the callee is in another TU; the target leaves it unmasked, and allocates
// this=edi/total=ebx where we get this=ebx/total=edi. Named-local and
// reordered-declaration shapes did not flip either.
// STUB: GAME 0x005bd600
unsigned short RHSprite::FUN_005bd600(int animation)
{
    unsigned int total = 0;
    unsigned short frame = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation);
    unsigned short count = FUN_005bdcf0(frame);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned short value = FUN_005bdbf0(frame, i);
        total += value + 1;
    }
    return (unsigned short)total;
}
