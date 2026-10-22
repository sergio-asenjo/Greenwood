// RHMenuSelectPlayer.cpp — the player-selection menu TU (code 0x0053e480..
// 0x0053fa44). See RHMenuSelectPlayer.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuSelectPlayer.h"

// FUNCTION: GAME 0x0053e480
void RHMenuSelectPlayer::FUN_0053e480(RHMenuEvent *event)
{
    if (FUN_0053e4a0(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0053e4a0
bool RHMenuSelectPlayer::FUN_0053e4a0(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == &m_button440)
        handled = FUN_0053f2a0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button240)
        handled = FUN_0053f410(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button340)
        handled = FUN_0053f620(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_button140)
        handled = FUN_0053f690(2, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[0])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[1])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[2])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[3])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[4])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[5])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[6])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[7])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[8])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == &m_entries[9])
        handled = FUN_0053f6d0(9, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[0])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[1])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[2])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[3])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[4])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[5])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[6])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[7])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[8])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_entries[9])
        handled = FUN_0053f390(7, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x0053e7f0
RHMenuSelectPlayer::RHMenuSelectPlayer(void *screen)
    : RHMenuWindowFocus(0, screen, 0, false), m_profiles((RHMenuSelectPlayerProfiles *)g_unk0x006c0e48)
{
}

// FUNCTION: GAME 0x0053e8b0
void *RHMenuSelectPlayer::FUN_0053e8b0(unsigned flags)
{
    this->~RHMenuSelectPlayer();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0053ede0
void RHMenuSelectPlayer::FUN_0053ede0(void *ui)
{
    RHMenuScreenView screen(0, 0xbc, 0, ui);
    RHMenuSelectPlayer menu(&screen);
    menu.FUN_0053e9e0();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x0053efe0
int RHMenuSelectPlayer::FUN_0053efe0()
{
    unsigned short index;
    for (index = 0; index < 10; ++index)
    {
        if (m_entries[index].IsSelected())
            break;
    }
    return index == 10 ? 0xffff : index;
}

// FUNCTION: GAME 0x0053f690
bool RHMenuSelectPlayer::FUN_0053f690(int, void *, void *)
{
    m_profiles->FUN_0055e410((unsigned short)FUN_0053efe0());
    m_profiles->Save();
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0053f2a0
bool RHMenuSelectPlayer::FUN_0053f2a0(int, void *, void *)
{
    bool confirmed = RHMenuYesNo::AskForConfirmation(m_screen, FUN_005e23d0(0xfe));
    if (confirmed)
    {
        m_profiles->FUN_0055d930((unsigned short)FUN_0053efe0());
        if (m_profiles->m_count > 0)
            m_profiles->FUN_0055e410(0);
        FUN_0053f040();
        FUN_0053f9a0();
        m_profiles->Save();
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0053f390
bool RHMenuSelectPlayer::FUN_0053f390(int, void *widget, void *)
{
    for (unsigned short index = 0; index < 10; ++index)
    {
        RHPortraitEditableWidget *entry = &m_entries[index];
        if (widget == entry && entry->IsSelected())
        {
            m_profiles->FUN_0055e410(index);
            m_profiles->Save();
            ((RHGameMenuCalls *)this)->FUN_00544b30();
            break;
        }
    }
    return false;
}

// FUNCTION: GAME 0x0053f620
bool RHMenuSelectPlayer::FUN_0053f620(int, void *, void *)
{
    RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
    RHPortraitEditableWidget *entry = &m_entries[(unsigned short)FUN_0053efe0()];
    if (entry->m_state != 13)
    {
        ui->m_17f0 = entry;
        entry->m_state = 13;
        ((SBUIInputFieldUnk00621440 *)(entry->m_00 + 0x110))->FUN_0061e340();
        ((SBUIInputFieldTextUnk *)(entry->m_00 + 0x110))->FUN_0061e320(1);
    }
    return false;
}

// FUNCTION: GAME 0x0053f9a0
void RHMenuSelectPlayer::FUN_0053f9a0()
{
    m_button240.SetEnabled(m_profiles->m_count < 10);
    m_button140.SetEnabled(m_profiles->m_count > 0);
    m_button440.SetEnabled(m_profiles->m_count > 0);
    m_button340.SetEnabled(m_profiles->m_count > 0);
}

// FUNCTION: GAME 0x0053f9f0
void RHMenuSelectPlayerWidget::FUN_0053f9f0(RHMenuSelectPlayerWidget *stop)
{
    RHMenuSelectPlayerWidget *widget = this;
    while (stop != widget)
    {
        if (widget->m_state == 2 || widget->m_state == 13)
        {
            ((SBUIInputFieldTextUnk *)widget->m_110)->FUN_0061e320(0);
            widget->m_state = 0;
        }
        widget = widget->m_parent;
        if (!widget)
            break;
    }
}
