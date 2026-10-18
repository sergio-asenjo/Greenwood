// RHMenuSounds.cpp — the sound-settings menu TU (code 0x00541370..0x00543dbb).
// See RHMenuSounds.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuSounds.h"

// FUNCTION: GAME 0x00541370
void RHMenuSounds::FUN_00541370(RHMenuEvent *event)
{
    if (FUN_00541390(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00541390
bool RHMenuSounds::FUN_00541390(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == &m_240)
        handled = FUN_0052ce80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_340)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_454)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_568)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_67c)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_790)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_85c)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_928)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_9f4)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_ac0)
        handled = FUN_00543520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_140)
        handled = FUN_00543750(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00541520
RHMenuSounds::RHMenuSounds(void *screen)
    : RHMenuWindowFocus(0, screen, 0, false),
      m_settings(*(RHMenuSoundsSettings *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x44))
{
    m_changed = false;
    m_vptr = 0x00679998;
}

// FUNCTION: GAME 0x00541780
void *RHMenuSounds::FUN_00541780(unsigned flags)
{
    this->~RHMenuSounds();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00543460
bool RHMenuSounds::FUN_00543460(void *ui)
{
    RHMenuScreenView screen(0, 0xba, 0, ui);
    RHMenuSounds menu(&screen);
    menu.FUN_00541a90();
    menu.FUN_00544b80(true, true);
    return menu.m_changed;
}

// FUNCTION: GAME 0x00543750
bool RHMenuSounds::FUN_00543750(int, void *, void *)
{
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    if (m_changed == true)
    {
        char *profile = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
        *(RHMenuSoundsSettings *)(profile + 0x44) = m_settings;
    }
    return false;
}

// FUNCTION: GAME 0x00543af0
RHMenuSoundsSlider::RHMenuSoundsSlider()
{
    m_highlighted = false;
    m_vptr = 0x006799f0;
}

// Parked: explicit event stores still hoist the event address before state arithmetic.
// STUB: GAME 0x00543bb0
RHMenuSoundsEvent *RHMenuSoundsSlider::FUN_00543bb0(const RHMenuSoundsInput &input)
{
    if (!m_sliderVisible)
        return 0;
    RHMenuSoundsEvent *result;
    switch (m_state)
    {
    case 0:
        result = 0;
        if (m_sliderBox.FUN_006083b0(input))
        {
            m_state = (input.m_buttons & 0x40) ? 3 : 1;
            result = MakeEvent(0);
        }
        return result;
    case 1:
        if (m_sliderBox.FUN_006083b0(input))
        {
            if (input.m_buttons & 0x40)
                m_state = 3;
        }
        else
            m_state = 0;
        return 0;
    case 3:
        result = 0;
        if (m_sliderBox.FUN_006083b0(input))
        {
            if (input.m_buttons & 1)
            {
                m_state = 1;
                m_highlighted = true;
                if (m_parent)
                    m_parent->FUN_00543dc0(this);
                return MakeEvent(2);
            }
        }
        else
            m_state = 0;
        return result;
    case 2:
        if (m_sliderBox.FUN_006083b0(input))
        {
            m_state = 3;
            return 0;
        }
        if (input.m_buttons & 1)
            m_state = 0;
        return 0;
    }
    return result;
}

// FUNCTION: GAME 0x00543d10
int RHMenuSoundsSlider::FUN_00543d10()
{
    if (!m_sliderVisible)
        return 0;
    int result;
    switch (m_state)
    {
    case 1:
    case 2:
        result = m_highlighted ? 5 : 2;
        break;
    case 3:
        result = m_highlighted ? 6 : 3;
        break;
    case 0:
        result = m_highlighted ? 4 : 1;
        break;
    }
    if (result == 1 && !m_sliderEnabled)
        result = 0xff;
    return result;
}
