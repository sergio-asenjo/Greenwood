#include "RHSprite.h"

// FUNCTION: GAME 0x005bd600
unsigned short RHSprite::FUN_005bd600(int animation)
{
    unsigned short frame = ((RHSpriteFrameTable *)((RHUnk005b5e00 *)this)->Unk())->Frame(animation);
    unsigned short total = 0;
    unsigned short count = FUN_005bdcf0(frame);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned short value = FUN_005bdbf0(frame, i);
        total += value + 1;
    }
    return total;
}
