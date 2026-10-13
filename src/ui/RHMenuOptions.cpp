// RHMenuOptions.cpp — menu TU (code 0x00538540..). See RHMenuOptions.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuOptions.h"

// GLOBAL: GAME 0x006c0c1a
bool RHMenuOptions::bReDisplay;

// FUNCTION: GAME 0x00538540
void RHMenuOptions::FUN_00538540(RHMenuEvent *event)
{
    if (FUN_00538560(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00538560
bool RHMenuOptions::FUN_00538560(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x640)
        handled = FUN_0052ce80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = FUN_00539250(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x540)
        handled = FUN_005393c0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_005393f0(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00538600
RHMenuOptions::RHMenuOptions(RHMenuScreenView *screen) : RHMenuWindowFocus(0, screen, 0, false), m_changed(false)
{
    m_vptr = 0x006797dc;
}

// FUNCTION: GAME 0x00538710
void *RHMenuOptions::FUN_00538710(unsigned flags)
{
    this->~RHMenuOptions();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00538e80
bool RHMenuOptions::FUN_00538e80(RHMenuWindowUI *ui)
{
    bool changed = false;
    for (;;)
    {
        RHMenuScreenView screen(0, 0xbc, 0, ui);
        RHMenuOptions menu(&screen);
        menu.FUN_00538860();
        menu.FUN_00544b80(true, true);
        changed = changed || menu.m_changed;
        if (!bReDisplay)
            break;
        bReDisplay = false;
    }
    return changed;
}

// FUNCTION: GAME 0x005393c0
bool RHMenuOptions::FUN_005393c0(int, void *, void *)
{
    RHMenuShortcuts::FUN_00540480(m_screen->FUN_0053bf30());
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x005393f0
bool RHMenuOptions::FUN_005393f0(int, void *, void *)
{
    bool changed = RHMenuSounds::FUN_00543460(m_screen->FUN_0053bf30());
    if (changed == true)
    {
        RHSound *sound = (RHSound *)g_unk0x006c1070;
        m_changed = changed;
        sound->ApplySoundSettings();
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}
