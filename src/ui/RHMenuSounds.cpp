// RHMenuSounds.cpp — the sound-settings menu TU (code 0x00541370..0x00543dbb).
// See RHMenuSounds.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuCancelCalls.h"
#include "RHMenuSounds.h"
#include "RHButtonSelection.h"

DECOMP_SIZE_ASSERT(RHMenuSounds, 0x119c)
DECOMP_SIZE_ASSERT(RHMenuSoundsSlider, 0xd8)
DECOMP_SIZE_ASSERT(RHPortraitGroupLifetime, 0xcc)

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

#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHSaveGameManager.h"
#include "RHPortraitUnk005d3880.h"

extern wchar_t g_unk0x006c0b50[1];
class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
std::wstring FUN_005e23d0(unsigned long);

template<class T>
static inline T &RHSoundsField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

static inline void RHSoundsInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

template<unsigned Offset>
static __forceinline bool RHSoundsCreateGroup(RHMenuSounds &menu, const std::wstring &name, const RHMapBox &box)
{
    bool created = ((RHGameWidgetLifetimeBase *)((char *)&menu + Offset))->Create(name, box, 0);
    unsigned width = 0;
    RHSoundsField<RHMenuSoundsSlider *>(&menu, Offset + 0x80) = new RHMenuSoundsSlider[10];
    RHSoundsField<unsigned>(&menu, Offset + 0x84) = 10;
    RHSoundsField<void **>(&menu, Offset + 0x8c) = new void *[10];
    for (int i = 0; i < 10 && created; ++i)
    {
        created = ((RHMapWidget *)&RHSoundsField<RHMenuSoundsSlider *>(&menu, Offset + 0x80)[i])->V30(name,
            RHMapBox(box.m_first.Unk005fc190(SBGeoVector2D((const SBGeoVector2D &)SBGeoPoint2D((float)width, 0.0f)))), 0, 0xd2);
        RHMenuSoundsSlider *sliders = RHSoundsField<RHMenuSoundsSlider *>(&menu, Offset + 0x80);
        width += RHSoundsField<SBGeoBoundingBox2D>(&sliders[i], 0x30).Width();
        sliders[i].m_parent = &sliders[(unsigned(i) + 1) % 10];
        RHSoundsField<void **>(&menu, Offset + 0x8c)[i] = 0;
    }
    RHSoundsField<SBGeoBoundingBox2D>(&menu, Offset + 0x30).SetMax(RHSoundsField<SBGeoBoundingBox2D>(
        &RHSoundsField<RHMenuSoundsSlider *>(&menu, Offset + 0x80)[RHSoundsField<unsigned>(&menu, Offset + 0x84) - 1], 0x30).Max());
    return created;
}

// STUB: GAME 0x00541a90
bool RHMenuSounds::Create()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        std::vector<void *> widgets;
        void *normal = m_screen->FUN_0053be80(std::string("Default"));
        void *edit = m_screen->FUN_0053be80(std::string("EditField"));
        void *title = m_screen->FUN_0053be80(std::string("MissionTitle"));
        ((RHMapWidget *)&m_b8c)->V30(FUN_005e23d0(0x1d), RHMapBox(0.0f, 0.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_b8c.m_renderer)->FUN_0060e0d0(title, title, title, title);
        ((RHMenuCampaignMap *)this)->V30(&m_b8c);
        m_140.FUN_005d1e30((int)m_screen, FUN_005e23d0(0xf), 0xbe);
        m_240.FUN_005d1e30((int)m_screen, FUN_005e23d0(0x10), 0xbe);
        RHSoundsInsert(widgets, &m_140);
        RHSoundsInsert(widgets, &m_240);
        ((RHMenuCampaignMap *)this)->V30(&m_140);
        ((RHMenuCampaignMap *)this)->V30(&m_240);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_140, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_240, true);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_140, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_140, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_240, 1);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        RHArtificialIntelligenceSoundCalls *sound = g_unk0x006c1070;
        unsigned label = RHSoundsField<bool>(sound, 0x212) ? 0x34 : 0x35;
        ((RHPortraitUnk005d3880 *)&m_340)->FUN_005d4bb0((int)m_screen, FUN_005e23d0(0x33), SBGeoPoint2D(30.0f, 70.0f), 0xbf);
        ((RHPortraitUnk005d3880 *)&m_454)->FUN_005d4bb0((int)m_screen, FUN_005e23d0(label), SBGeoPoint2D(30.0f, 70.0f), 0xbf);
        ((RHPortraitUnk005d3880 *)&m_340)->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_454);
        ((RHPortraitUnk005d3880 *)&m_454)->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_340);
        RHSoundsInsert(widgets, &m_340);
        RHSoundsInsert(widgets, &m_454);
        ((RHMenuCampaignMap *)this)->V30(&m_340);
        ((RHMenuCampaignMap *)this)->V30(&m_454);
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        ((RHMapWidget *)&m_454)->V54(RHSoundsField<bool>(sound, 0x211));
        ((RHPortraitUnk005d3880 *)&m_568)->FUN_005d4bb0((int)m_screen, FUN_005e23d0(0x36), SBGeoPoint2D(30.0f, 170.0f), 0xbf);
        ((RHPortraitUnk005d3880 *)&m_67c)->FUN_005d4bb0((int)m_screen, FUN_005e23d0(0x37), SBGeoPoint2D(30.0f, 170.0f), 0xbf);
        ((RHPortraitUnk005d3880 *)&m_568)->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_67c);
        ((RHPortraitUnk005d3880 *)&m_67c)->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_568);
        RHSoundsInsert(widgets, &m_568);
        RHSoundsInsert(widgets, &m_67c);
        ((RHMenuCampaignMap *)this)->V30(&m_568);
        ((RHMenuCampaignMap *)this)->V30(&m_67c);
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        RHSoundsField<void *>(&m_340, 0xd0) = edit;
        RHSoundsField<void *>(&m_454, 0xd0) = edit;
        RHSoundsField<void *>(&m_568, 0xd0) = edit;
        RHSoundsField<void *>(&m_67c, 0xd0) = edit;
        RHSoundsCreateGroup<0x790>(*this, g_unk0x006c0b50, RHMapBox(30.0f, 290.0f, 30.0f, 290.0f));
        RHSoundsCreateGroup<0x85c>(*this, g_unk0x006c0b50, RHMapBox(30.0f, 330.0f, 30.0f, 330.0f));
        RHSoundsCreateGroup<0x928>(*this, g_unk0x006c0b50, RHMapBox(30.0f, 370.0f, 30.0f, 370.0f));
        RHSoundsCreateGroup<0x9f4>(*this, g_unk0x006c0b50, RHMapBox(30.0f, 410.0f, 30.0f, 410.0f));
        RHSoundsCreateGroup<0xac0>(*this, g_unk0x006c0b50, RHMapBox(30.0f, 450.0f, 30.0f, 450.0f));
        ((RHMenuCampaignMap *)this)->V30(&m_790);
        ((RHMenuCampaignMap *)this)->V30(&m_85c);
        ((RHMenuCampaignMap *)this)->V30(&m_928);
        ((RHMenuCampaignMap *)this)->V30(&m_9f4);
        ((RHMenuCampaignMap *)this)->V30(&m_ac0);
        ((RHMapWidget *)&m_c8c)->V30(FUN_005e23d0(0x38), RHMapBox(30.0f, 270.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((RHMapWidget *)&m_d8c)->V30(FUN_005e23d0(0x39), RHMapBox(30.0f, 310.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((RHMapWidget *)&m_e8c)->V30(FUN_005e23d0(0x3a), RHMapBox(30.0f, 350.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((RHMapWidget *)&m_f8c)->V30(FUN_005e23d0(0x3b), RHMapBox(30.0f, 390.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((RHMapWidget *)&m_108c)->V30(FUN_005e23d0(0x3c), RHMapBox(30.0f, 430.0f, 460.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_c8c.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((SBUIUnk0060dd00 *)&m_d8c.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((SBUIUnk0060dd00 *)&m_e8c.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((SBUIUnk0060dd00 *)&m_f8c.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((SBUIUnk0060dd00 *)&m_108c.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((RHMenuCampaignMap *)this)->V30(&m_c8c);
        ((RHMenuCampaignMap *)this)->V30(&m_d8c);
        ((RHMenuCampaignMap *)this)->V30(&m_e8c);
        ((RHMenuCampaignMap *)this)->V30(&m_f8c);
        ((RHMenuCampaignMap *)this)->V30(&m_108c);
        SynchronizeWidgets();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00543460
bool RHMenuSounds::FUN_00543460(void *ui)
{
    RHMenuScreenView screen(0, 0xba, 0, ui);
    RHMenuSounds menu(&screen);
    menu.Create();
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

static inline RHMenuSoundsSlider &RHMenuSoundsSliderAt(RHPortraitGroupLifetime &group, unsigned short index)
{
    return (*(RHMenuSoundsSlider **)((char *)&group + 0x80))[index];
}

// FUNCTION: GAME 0x00543790
void RHMenuSounds::SynchronizeWidgets()
{
    ((RHUnk0052d2c0 *)&m_340)->SetEnable(m_settings.m_a == false);
    ((RHUnk0052d2c0 *)&m_454)->SetEnable(m_settings.m_a == true);
    ((RHUnk0052d2c0 *)&m_568)->SetEnable(m_settings.m_b == false);
    ((RHUnk0052d2c0 *)&m_67c)->SetEnable(m_settings.m_b == true);
    RHMenuSoundsSliderAt(m_790, m_settings.m_4).Select();
    RHMenuSoundsSliderAt(m_85c, m_settings.m_2).Select();
    RHMenuSoundsSliderAt(m_928, m_settings.m_0).Select();
    RHMenuSoundsSliderAt(m_9f4, m_settings.m_6).Select();
    RHMenuSoundsSliderAt(m_ac0, m_settings.m_8).Select();
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
                    m_parent->Deselect(this);
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

// FUNCTION: GAME 0x00543dc0
void RHMenuSoundsSlider::FUN_00543dc0(RHMenuSoundsSlider *stop)
{
    Deselect(stop);
}

#pragma inline_depth(0)
void EmitRHMenuSoundsSlider()
{
    RHMenuSoundsSlider slider;
}
#pragma inline_depth()
