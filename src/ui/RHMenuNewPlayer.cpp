// RHMenuNewPlayer.cpp — menu TU (code 0x00537570..). See RHMenuNewPlayer.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuNewPlayer.h"

// FUNCTION: GAME 0x00537570
void RHMenuNewPlayer::FUN_00537570(RHMenuEvent *event)
{
    if (FUN_00537590(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00537590
bool RHMenuNewPlayer::FUN_00537590(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0xc20)
        handled = FUN_00538410(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0xd20)
        handled = FUN_005383f0(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00537770
void *RHMenuNewPlayer::FUN_00537770(unsigned flags)
{
    this->~RHMenuNewPlayer();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00538280
int RHMenuNewPlayer::FUN_00538280() const
{
    for (int index = 0; index != 3; ++index)
    {
        if (m_radios[index].m_selected)
            return index;
    }
    return 0;
}

// FUNCTION: GAME 0x005383e0
bool RHMenuNewPlayer::FUN_005383e0()
{
    return m_ok;
}

// FUNCTION: GAME 0x005383f0
bool RHMenuNewPlayer::FUN_005383f0(int, void *, void *)
{
    m_ok = false;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

// FUNCTION: GAME 0x00538410
bool RHMenuNewPlayer::FUN_00538410(int, void *, void *)
{
    m_ok = true;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

void EmitRHMenuNewPlayerAccessors(RHMenuNewPlayer *menu)
{
    menu->FUN_005383e0();
}
