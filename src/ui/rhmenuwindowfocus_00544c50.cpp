#include "rhmenuwindowfocus_00544c50.h"
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHFocusManager, 0x70)
DECOMP_SIZE_ASSERT(RHMenuWindow, 0xc8)
DECOMP_SIZE_ASSERT(RHMenuWindowFocus, 0x140)
DECOMP_STATIC_ASSERT(offsetof(RHMenuWindowFocus, m_focus) == 0xc8)
DECOMP_STATIC_ASSERT(offsetof(RHMenuWindowFocus, m_138) == 0x138)
DECOMP_STATIC_ASSERT(offsetof(RHMenuWindowFocus, m_screen) == 0xb4)
DECOMP_STATIC_ASSERT(offsetof(RHMenuWindowFocus, m_enabled) == 0x5c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuWindowFocus, m_visible) == 0x5d)

// FUNCTION: GAME 0x00544c50
RHMenuWindowFocus::RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap)
    : RHMenuWindow(parent, (RHMenuWindowScreen *)screen, wrap), m_focus(orientation)
{
    *(unsigned *)this = 0x00679a80;
}

// FUNCTION: GAME 0x00544cd0
void *RHMenuWindowFocus::FUN_00544cd0(unsigned flags)
{
    this->RHMenuWindowFocus::~RHMenuWindowFocus();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00544e60
RHMenuWindowFocus::RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap)
    : RHMenuWindow(parent, (RHMenuWindowScreen *)screen, resource, wrap), m_focus(orientation)
{
    *(unsigned *)this = 0x00679a80;
}

// Inlined m_focus teardown calls the folded list iterator++ 0x0057c9c0 for list<RHFocusFocusableView *>, not a registered member.
// STUB: GAME 0x00544ee0
RHMenuWindowFocus::~RHMenuWindowFocus()
{
    *(unsigned *)this = 0x00679a80;
}

// FUNCTION: GAME 0x00545090
void *RHMenuWindowFocus::FUN_00545090(const void *input)
{
    if (m_enabled == true && m_visible == true)
        return m_focus.FUN_005002a0((RHFocusEvent *)RHPortraitRootLifetime::FUN_0061a6e0(input), input,
            m_screen->FUN_0053bf30());
    return 0;
}

// FUNCTION: GAME 0x005450d0
void RHMenuWindowFocus::FUN_005450d0()
{
    m_focus.FUN_00500750();
    RHPortraitRootLifetime::FUN_0061a3a0();
}
