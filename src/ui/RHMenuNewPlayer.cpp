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

// FUNCTION: GAME 0x005375f0
RHMenuNewPlayer::RHMenuNewPlayer(RHMenuScreenView *screen)
    : RHMenuWindowFocus(0, screen, 0x93, 1, false), m_ok(false)
{
}

// FUNCTION: GAME 0x00537770
void *RHMenuNewPlayer::FUN_00537770(unsigned flags)
{
    this->~RHMenuNewPlayer();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00537790
RHMenuNewPlayer::~RHMenuNewPlayer()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_cancelButton);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_okButton);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_nameLabel);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_difficultyLabel);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_name);
    for (int i = 0; i < 3; i++)
    {
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_radios[i]);
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_radioLabels[i]);
    }
}

#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHSaveGameManager.h"
#include "RHPortraitUnk005d3880.h"
#include "RHButtonSelection.h"

extern wchar_t g_unk0x006c0b50[1];

inline void RHNewPlayerInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// STUB: GAME 0x00537960
bool RHMenuNewPlayer::Create()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 496.0f, 463.0f), 0))
    {
        std::vector<void *> widgets;
        void *title = m_screen->FUN_0053be80(std::string("MissionTitle"));
        void *normal = m_screen->FUN_0053be80(std::string("PopupScroll"));
        ((RHMapWidget *)&m_title)->V30(FUN_005e23d0(0x1e), RHMapBox(0.0f, 45.0f, 496.0f, 100.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(title, title, title, title);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        ((RHMapWidget *)&m_nameLabel)->V30(FUN_005e23d0(0x3d), RHMapBox(0.0f, 100.0f, 496.0f, 300.0f), 0, unsigned(-1));
        ((RHMapWidget *)&m_difficultyLabel)->V30(FUN_005e23d0(0x43), RHMapBox(0.0f, 200.0f, 496.0f, 300.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_nameLabel.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((SBUIUnk0060dd00 *)&m_difficultyLabel.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((RHMenuCampaignMap *)this)->V30(&m_nameLabel);
        ((RHMenuCampaignMap *)this)->V30(&m_difficultyLabel);
        m_name.FUN_005d2810(SBGeoPoint2D(35.0f, 130.0f), m_screen);
        m_name.SetMaximum(30);
        ((RHMenuCampaignMap *)this)->V30(&m_name);
        for (unsigned long i = 0; i != 3; ++i)
        {
            RHPortraitLinkedLifetime *radio = &m_radios[i];
            ((RHPortraitUnk005d3880 *)radio)->FUN_005d4bb0((int)m_screen, g_unk0x006c0b50, SBGeoPoint2D(0.0f, 250.0f), 0xd3);
            unsigned long next = (i + 1) % 3;
            ((RHPortraitUnk005d3880 *)radio)->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_radios[next]);
            ((RHMenuCampaignMap *)this)->V30(radio);
            RHNewPlayerInsert(widgets, radio);
            ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70(radio ? (RHFocusGroupableView *)((char *)radio + 0xdc) : 0, true);
        }
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 25);
        widgets.clear();
        ((RHUnk0052d2c0 *)&m_radios[1])->SetEnable(true);
        RHPortraitLinkedLifetime *radio = m_radios;
        int j = 0;
        RHGameLifetime00525560 *label = m_radioLabels;
        for (; j != 3; ++j, ++radio, ++label)
        {
            ((RHMapWidget *)label)->V30(FUN_005e23d0(j + 0x22), RHMapBox(0.0f, 0.0f, 100.0f, 50.0f), 0, unsigned(-1));
            ((SBUIUnk0060dd00 *)&label->m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
            label->m_renderer.SetM60(2);
            ((RHMenuCampaignMap *)this)->V30(label);
            RHNewPlayerInsert(widgets, radio);
            RHNewPlayerInsert(widgets, label);
            ((RHMenuWindow *)this)->FUN_00544800(widgets, 5);
            widgets.erase(widgets.begin(), widgets.end());
        }
        m_cancelButton.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x92);
        m_okButton.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x91);
        ((RHUnk005d92c0Sub *)&m_okButton)->v08(SBGeoPoint2D(0.0f, 370.0f));
        ((RHMenuCampaignMap *)this)->V30(&m_cancelButton);
        ((RHMenuCampaignMap *)this)->V30(&m_okButton);
        RHNewPlayerInsert(widgets, &m_okButton);
        RHNewPlayerInsert(widgets, &m_cancelButton);
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 20);
        RHPortraitEditableWidget *name = &m_name;
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc20(name ? (RHFocusFocusableView *)((char *)&m_name + 0x180) : 0);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_okButton, false);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancelButton, false);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_okButton, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_okButton, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancelButton, 1);
        name->Activate(m_screen->FUN_0053bf30());
        return true;
    }
    return false;
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

// FUNCTION: GAME 0x005382a0
std::wstring RHMenuNewPlayer::GetName() const
{
    std::wstring name;
    name = m_name.GetText();
    if (name.empty())
        name = FUN_005e23d0(0x3e);
    return name;
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

// SYNTHETIC: GAME 0x00538430
// ??0RHGameLifetime00525560@@QAE@XZ

void EmitRHMenuNewPlayerAccessors(RHMenuNewPlayer *menu)
{
    menu->Create();
    menu->FUN_005383e0();
    menu->GetName();
}
