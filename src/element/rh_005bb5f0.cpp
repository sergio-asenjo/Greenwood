#include "RHSprite.h"

// FUNCTION: GAME 0x005bb5f0
unsigned short RHSprite::FUN_005bb5f0()
{
    if (m_188 != 0)
    {
        m_18a = 0;
        return 0;
    }
    unsigned short frame = FUN_005bdc50(m_184, m_186);
    if (frame == m_18a)
        return 0;
    m_18a = frame;
    return frame;
}
