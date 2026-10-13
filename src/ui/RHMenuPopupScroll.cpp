// RHMenuPopupScroll.cpp — popup scroll menu TU (code 0x005394e0..). See
// RHMenuPopupScroll.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuPopupScroll.h"

// FUNCTION: GAME 0x005394e0
void RHMenuPopupScroll::FUN_005394e0(RHMenuEvent *event)
{
    if (FUN_00539500(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00539500
bool RHMenuPopupScroll::FUN_00539500(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x144)
        handled = FUN_0053a860(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00539710
void *RHMenuPopupScroll::FUN_00539710(unsigned flags)
{
    this->~RHMenuPopupScroll();
    if (flags & 1)
        operator delete(this);
    return this;
}
