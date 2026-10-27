// RHMenuSelectPlayer.cpp — the player-selection menu TU (code 0x0053e480..
// 0x0053fa44). See RHMenuSelectPlayer.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuSelectPlayer.h"
#include "RHPlayerProfile.h"
#include "ToolboxWideString.h"
#include "RHMapBox.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "RHPlayerProfileManager.h"
#include <wchar.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHPortraitEditableWidget, 0x1a4)
DECOMP_SIZE_ASSERT(RHMenuSelectPlayerWidget, 0x160)
DECOMP_SIZE_ASSERT(RHMenuSelectPlayer, 0x15ac)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitEditableWidget, m_info) == 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitEditableWidget, m_infoDirty) == 0xe0)

extern wchar_t g_unk0x006c0b50[1];

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
    : RHMenuWindowFocus(0, screen, 0, false), m_profiles((RHPlayerProfileManager *)g_unk0x006c0e48)
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

// FUNCTION: GAME 0x0053e8d0
RHMenuSelectPlayer::~RHMenuSelectPlayer()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_button140);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_button240);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_button340);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_button440);
    for (int i = 0; i < 10; i++)
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_entries[i]);
}

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHSelectPlayerInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x0053e9e0
bool RHMenuSelectPlayer::FUN_0053e9e0()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        std::vector<void *> widgets;
        m_button140.FUN_005d1e30((int)m_screen, FUN_005e23d0(5), 0xbe);
        m_button240.FUN_005d1e30((int)m_screen, FUN_005e23d0(6), 0xbe);
        m_button340.FUN_005d1e30((int)m_screen, FUN_005e23d0(7), 0xbe);
        m_button440.FUN_005d1e30((int)m_screen, FUN_005e23d0(8), 0xbe);
        ((RHMenuCampaignMap *)this)->V30(&m_button140);
        ((RHMenuCampaignMap *)this)->V30(&m_button240);
        ((RHMenuCampaignMap *)this)->V30(&m_button340);
        ((RHMenuCampaignMap *)this)->V30(&m_button440);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_button140, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_button240, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_button340, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_button440, true);
        RHSelectPlayerInsert(widgets, &m_button140);
        RHSelectPlayerInsert(widgets, &m_button240);
        RHSelectPlayerInsert(widgets, &m_button340);
        RHSelectPlayerInsert(widgets, &m_button440);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        for (unsigned long i = 0; i != 10; ++i)
        {
            m_profiles->FUN_0055dd10(i);
            unsigned long next = (i + 1) % 10;
            m_entries[i].FUN_005d2810(SBGeoPoint2D(30.0f, 72.0f), (RHMenuScreenView *)m_screen);
            *(int *)((char *)&m_entries[i] + 0x130) = 30;
            RHSelectPlayerInsert(widgets, &m_entries[i]);
            ((RHMenuCampaignMap *)this)->V30(&m_entries[i]);
            *(RHPortraitEditableWidget **)((char *)&m_entries[i] + 0x158) = &m_entries[next];
        }
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 2);
        FUN_0053f040();
        FUN_0053f9a0();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0053ede0
void RHMenuSelectPlayer::FUN_0053ede0(void *ui)
{
    RHMenuScreenView screen(0, 0xbc, 0, ui);
    RHMenuSelectPlayer menu(&screen);
    menu.FUN_0053e9e0();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x0053eea0
std::wstring RHMenuSelectPlayer::GetProfileInfo(const RHPlayerProfile *profile)
{
    wchar_t text[1024];
    unsigned long completion = profile->m_2c;
    swprintf(text,
        // STRING: GAME 0x006b104c
        L"%s / %i %%", RHPlayerProfile::ConvertDifficultyLevelToWideString(profile->m_1c).c_str(), completion);
    return std::wstring(text);
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

// STUB: GAME 0x0053f040
void RHMenuSelectPlayer::FUN_0053f040()
{
    for (int index = 0; index != 10; ++index)
    {
        RHPlayerProfile *profile = m_profiles->FUN_0055dd10(index);
        RHPortraitEditableWidget &entry = m_entries[index];
        if (profile)
        {
            ((RHGameMenuText *)&entry)->v11(profile->GetName());
            m_entries[index].SetInfo(GetProfileInfo(profile));
            *((bool *)&entry + 4) = true;
            if (profile == (RHPlayerProfile *)((RHUnk0055dbb0 *)m_profiles)->FUN_0055dbb0())
                ((RHMenuSelectPlayerWidget *)&entry)->Select();
        }
        else
        {
            ((RHGameMenuText *)&entry)->v11(std::wstring(g_unk0x006c0b50));
            m_entries[index].SetInfo(std::wstring(g_unk0x006c0b50));
            *((bool *)&entry + 4) = false;
        }
    }
}

// FUNCTION: GAME 0x0053f2a0
bool RHMenuSelectPlayer::FUN_0053f2a0(int, void *, void *)
{
    bool confirmed = RHMenuYesNo::AskForConfirmation(m_screen, FUN_005e23d0(0xfe));
    if (confirmed)
    {
        m_profiles->FUN_0055d930((unsigned short)FUN_0053efe0());
        if (m_profiles->m_profiles.size() > 0)
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

#include "RHMenuNewPlayer.h"

// FUNCTION: GAME 0x0053f410
bool RHMenuSelectPlayer::FUN_0053f410(int, void *, void *)
{
    RHMenuNewPlayer menu(m_screen);
    menu.Create();
    menu.FUN_00544b80(true, true);
    if (menu.FUN_005383e0())
    {
        RHPlayerProfile *profile = m_profiles->AddProfile(menu.GetName(), menu.FUN_00538280());
        unsigned short index = m_profiles->m_profiles.size() - 1;
        ((RHGameMenuText *)&m_entries[index])->v11(profile->GetName());
        m_entries[index].m_info.assign(GetProfileInfo(profile)), m_entries[index].m_infoDirty = true;
        *((bool *)&m_entries[index] + 4) = true;
        ((RHMenuSelectPlayerWidget *)&m_entries[index])->Select();
        FUN_0053f9a0();
    }
    ((RHMenuWindow *)&menu)->FUN_00544300();
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
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

// FUNCTION: GAME 0x0053f690
bool RHMenuSelectPlayer::FUN_0053f690(int, void *, void *)
{
    m_profiles->FUN_0055e410((unsigned short)FUN_0053efe0());
    m_profiles->Save();
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0053f6d0
bool RHMenuSelectPlayer::FUN_0053f6d0(int, void *widget, void *)
{
    std::wstring name;
    unsigned short index = 0;
    while (&m_entries[index] != widget)
        ++index;
    RHPlayerProfile *profile = m_profiles->FUN_0055dd10(index);
    name = Toolbox::TrimWideString(m_entries[index].GetText());
    profile->SetName(name.empty() ?
        // STRING: GAME 0x006b1064
        std::wstring(L"Robin") : name);
    ((RHGameMenuText *)&m_entries[index])->v11(profile->GetName());
    m_entries[index].m_info.assign(GetProfileInfo(profile)), m_entries[index].m_infoDirty = true;
    ((RHMenuSelectPlayerWidget *)&m_entries[index])->Select();
    m_profiles->FUN_0055e410(index);
    m_profiles->Save();
    return false;
}

// FUNCTION: GAME 0x0053f9a0
void RHMenuSelectPlayer::FUN_0053f9a0()
{
    m_button240.SetEnabled(m_profiles->m_profiles.size() < 10);
    m_button140.SetEnabled(m_profiles->m_profiles.size() > 0);
    m_button440.SetEnabled(m_profiles->m_profiles.size() > 0);
    m_button340.SetEnabled(m_profiles->m_profiles.size() > 0);
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
