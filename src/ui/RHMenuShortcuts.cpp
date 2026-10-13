// RHMenuShortcuts.cpp — the keyboard-shortcut menu TU (code 0x0053fae0..
// 0x005406ab). See RHMenuShortcuts.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuShortcuts.h"

// FUNCTION: GAME 0x0053fae0
void RHMenuShortcuts::FUN_0053fae0(RHMenuEvent *event)
{
    if (FUN_0053fb00(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0053fb00
bool RHMenuShortcuts::FUN_0053fb00(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == &m_button540)
        handled = FUN_0052ce80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button240)
        handled = FUN_00540540(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button340)
        handled = FUN_00540590(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button140)
        handled = FUN_005405e0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button440)
        handled = FUN_00540650(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x0053fbc0
RHMenuShortcuts::RHMenuShortcuts(void *screen)
    : RHMenuWindowFocus(0, screen, 0, false),
      m_keys(*(RHKeyConfig *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x34))
{
    m_profile = (RHMenuShortcutsProfile *)((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    m_vptr = 0x006798e8;
}

// FUNCTION: GAME 0x0053fca0
void *RHMenuShortcuts::FUN_0053fca0(unsigned flags)
{
    this->~RHMenuShortcuts();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00540480
void RHMenuShortcuts::FUN_00540480(void *ui)
{
    RHMenuScreenView screen(0, 0xbd, 0, ui);
    RHMenuShortcuts menu(&screen);
    menu.FUN_0053fdd0();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x00540540
bool RHMenuShortcuts::FUN_00540540(int, void *, void *)
{
    if (m_userDefined)
        m_profile->m_keys3c.FUN_0051ebf0(m_keys);
    m_keys.SetToPreset(0, g_unk0x6c069c);
    m_list.FUN_005ced90();
    return false;
}

// FUNCTION: GAME 0x00540590
bool RHMenuShortcuts::FUN_00540590(int, void *, void *)
{
    if (m_userDefined)
        m_profile->m_keys3c.FUN_0051ebf0(m_keys);
    m_keys.SetToPreset(1, g_unk0x6c069c);
    m_list.FUN_005ced90();
    return false;
}

// FUNCTION: GAME 0x005405e0
bool RHMenuShortcuts::FUN_005405e0(int, void *, void *)
{
    if (m_userDefined)
        m_profile->m_keys3c.FUN_0051ebf0(m_keys);
    m_profile->m_keys34.FUN_0051ebf0(m_keys);
    ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
    if (RHGameInputTranslator::mpInstance)
    {
        RHGameInputTranslator::mpInstance->ReflectActiveKeyConfig();
        ((RHGame *)g_unk0x6c0b3c)->FUN_00510750();
    }
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x00540650
bool RHMenuShortcuts::FUN_00540650(int, void *, void *)
{
    m_keys.FUN_0051ebf0(*(RHKeyConfig *)&m_profile->m_keys3c);
    m_list.FUN_005ced90();
    return false;
}
