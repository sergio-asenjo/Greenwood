#include "SBNullstr.h"
#include "rhuirenderer_005cadc0.h"
#include "RHPortraitRenderer0060d470.h"

// FUNCTION: GAME 0x0060dab0
RHPortraitRenderer0060dab0::RHPortraitRenderer0060dab0()
{
    ((RHPortraitRenderer0060d470 *)this)->RHPortraitRenderer0060d470::RHPortraitRenderer0060d470();
    *(unsigned *)this = 0x67a610;
    m_4c = 0x1f;
    m_4e = 0x32;
}

// FUNCTION: GAME 0x0060dad0
RHPortraitRenderer0060dab0::~RHPortraitRenderer0060dab0()
{
    *(unsigned *)this = 0x67a610;
    ((RHPortraitRenderer0060d470 *)this)->RHPortraitRenderer0060d470::~RHPortraitRenderer0060d470();
}
