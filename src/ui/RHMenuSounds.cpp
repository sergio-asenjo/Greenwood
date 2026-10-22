// RHMenuSounds.cpp — the sound-settings menu TU (code 0x00541370..0x00543dbb).
// See RHMenuSounds.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuCancelCalls.h"
#include "RHMenuSounds.h"

RHMenuSoundsSlider *EmitRHMenuSoundsSliderArray(unsigned count)
{
    return new RHMenuSoundsSlider[count];
}

// SYNTHETIC: GAME 0x00543a90
// ??_ERHMenuSoundsSlider@@QAEPAXI@Z

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
        handled = ((RHMenuCancelCalls *)this)->OnCancel(2, event->m_widget, event->m_data);
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
      m_settings(*(RHMenuSoundsSettings *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x44)),
      m_changed(false)
{
}

// FUNCTION: GAME 0x00541780
void *RHMenuSounds::FUN_00541780(unsigned flags)
{
    this->~RHMenuSounds();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005417a0
RHMenuSounds::~RHMenuSounds()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_b8c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_140);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_240);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_340);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_454);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_568);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_67c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_790);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_85c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_928);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_9f4);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ac0);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_c8c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_d8c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_e8c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_f8c);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_108c);
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

struct RHMenuSoundsChoice
{
    char m_00[0xd4];
    bool m_selected;
    char m_d5[3];
};

static inline unsigned short RHMenuSoundsSelected(RHPortraitGroupLifetime &group)
{
    for (unsigned short index = 0; index < *(unsigned *)((char *)&group + 0x84); ++index)
        if ((*(RHMenuSoundsChoice **)((char *)&group + 0x80))[index].m_selected == true)
            return index;
    return 0xffff;
}

// FUNCTION: GAME 0x00543520
bool RHMenuSounds::FUN_00543520(int, void *widget, void *)
{
    if (widget == &m_340) {
        m_settings.m_a = false;
        m_changed = true;
    } else if (widget == &m_454) {
        m_settings.m_a = true;
        m_changed = true;
    } else if (widget == &m_568) {
        m_settings.m_b = false;
        m_changed = true;
    } else if (widget == &m_67c) {
        m_settings.m_b = true;
        m_changed = true;
    } else if (widget == &m_790) {
        m_settings.m_4 = RHMenuSoundsSelected(m_790);
        m_changed = true;
    } else if (widget == &m_85c) {
        m_settings.m_2 = RHMenuSoundsSelected(m_85c);
        m_changed = true;
    } else if (widget == &m_928) {
        m_settings.m_0 = RHMenuSoundsSelected(m_928);
        m_changed = true;
    } else if (widget == &m_9f4) {
        m_settings.m_6 = RHMenuSoundsSelected(m_9f4);
        m_changed = true;
    } else if (widget == &m_ac0) {
        m_settings.m_8 = RHMenuSoundsSelected(m_ac0);
        m_changed = true;
    }
    return false;
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
RHMenuSoundsSlider::RHMenuSoundsSlider() : m_highlighted(false)
{
}

// SYNTHETIC: GAME 0x00543b50
// ??1RHMenuSoundsSlider@@QAE@XZ

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

#pragma inline_depth(0)
void EmitRHMenuSoundsSlider()
{
    RHMenuSoundsSlider slider;
}
#pragma inline_depth()
