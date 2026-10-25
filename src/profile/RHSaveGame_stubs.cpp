#include "SBNullstr.h"
#include "RHSaveGame.h"
#include <windows.h>

// FUNCTION: GAME 0x005f4ff0
RHUnk005f4fc0::~RHUnk005f4fc0()
{
    if (*(FILE **)m_pad0 && !m_3c)
        FUN_005f5290();
    if (m_38)
        UnmapViewOfFile((void *)m_38);
    if (m_34 != (unsigned long)-1)
        CloseHandle((HANDLE)m_34);
    if (m_30 != (unsigned long)-1)
        CloseHandle((HANDLE)m_30);
}
