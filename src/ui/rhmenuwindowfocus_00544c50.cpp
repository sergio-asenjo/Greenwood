#include "rhmenuwindowfocus_00544c50.h"

DECOMP_SIZE_ASSERT(RHFocusManager, 0x70)
DECOMP_SIZE_ASSERT(RHMenuWindow, 0xc8)
DECOMP_SIZE_ASSERT(RHMenuWindowFocus, 0x140)

// FUNCTION: GAME 0x00544c50
RHMenuWindowFocus::RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap)
    : RHMenuWindow(parent, (RHMenuWindowScreen *)screen, wrap), m_focus(orientation)
{
    m_vptr = 0x00679a80;
}

// FUNCTION: GAME 0x00544cd0
void *RHMenuWindowFocus::FUN_00544cd0(unsigned flags)
{
    this->~RHMenuWindowFocus();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00544e60
RHMenuWindowFocus::RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap)
    : RHMenuWindow(parent, (RHMenuWindowScreen *)screen, resource, wrap), m_focus(orientation)
{
    m_vptr = 0x00679a80;
}

// FUNCTION: GAME 0x00545090
void *RHMenuWindowFocus::FUN_00545090(const void *input)
{
    if (m_5c == true && m_5d == true)
        return m_focus.FUN_005002a0((RHFocusEvent *)((RHPortraitRootLifetime *)this)->FUN_0061a6e0(input), input,
            m_screen->FUN_0053bf30());
    return 0;
}

// FUNCTION: GAME 0x005450d0
void RHMenuWindowFocus::FUN_005450d0()
{
    m_focus.FUN_00500750();
    ((SBFrameWnd *)this)->FUN_0061a3a0();
}
