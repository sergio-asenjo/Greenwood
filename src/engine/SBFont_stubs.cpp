#include "SBNullstr.h"
#include "SBFont.h"

SBFontLock::SBFontLock() {}
SBFontLock::~SBFontLock() {}
void FUN_005f8030(int, const char *, int, const char *, ...) {}

void SBFontTree0061fcb0::FUN_00620b70() {}
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620c20(const unsigned short &) { return 0; }
// FUNCTION: GAME 0x00620c70
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620c70(SBFontNode0061fcb0 *parent, int color)
{
    SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
    node->m_04 = parent;
    node->m_10 = color;
    return node;
}
void SBFontTree0061fcb0::FUN_00620960(const SBFontTree0061fcb0 &) {}
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fce0(SBFontIterator0061fe10 first, SBFontIterator0061fe10) { return first; }
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fe30(SBFontNode0061fcb0 *, SBFontNode0061fcb0 *parent, const unsigned short &)
{
    SBFontIterator0061fe10 result;
    result.m_00 = parent;
    return result;
}
void SBFontIterator0061fe10::FUN_00620ca0() {}
void SBFontIterator0061f3e0::FUN_00620e30() {}
SBFontIterator0061f3e0 SBFontTree0061f3e0::FUN_00620130(SBFontNode0061f3e0 *, SBFontNode0061f3e0 *parent, const SBFontValue0061f120 &)
{
    SBFontIterator0061f3e0 result;
    result.m_00 = parent;
    return result;
}
