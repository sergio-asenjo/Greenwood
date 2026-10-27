// RHMenuIntro.cpp — menu TU (code 0x0052e090..0x00530170). See RHMenuIntro.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuIntro.h"

// FUNCTION: GAME 0x0052e090
void RHMenuIntro::FUN_0052e090(RHMenuEvent *event)
{
    if (FUN_0052e0b0(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0052e0b0
bool RHMenuIntro::FUN_0052e0b0(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x540)
        handled = FUN_0052ec60(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x640)
        handled = FUN_0052ecb0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = FUN_0052ed80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_0052edf0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = FUN_0052ee20(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x140)
        handled = FUN_0052efa0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x740)
        handled = FUN_0052efc0(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x0052e1b0
RHMenuIntro::RHMenuIntro(RHMenuScreenView *screen)
    : RHMenuWindowFocus(0, screen, 0, false), m_choice(0)
{
}

// FUNCTION: GAME 0x0052e300
void *RHMenuIntro::FUN_0052e300(unsigned flags)
{
    this->~RHMenuIntro();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052e320
RHMenuIntro::~RHMenuIntro()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_140);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_240);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_340);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_740);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_440);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_540);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_640);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_940);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_840);
}

#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHSaveGameManager.h"

extern wchar_t g_unk0x006c0b50[1];

inline void RHIntroInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// STUB: GAME 0x0052e4b0
bool RHMenuIntro::Create()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(
        // STRING: GAME 0x006b0db0
        L"Intro", RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        std::vector<void *> widgets;
        void *normal = m_screen->FUN_0053be80(std::string(
            // STRING: GAME 0x006b0da4
            "MenuText"));
        void *edit = m_screen->FUN_0053be80(std::string("EditField"));
        m_140.FUN_005d1e30((int)m_screen, FUN_005e23d0(0), 0xbe);
        m_240.FUN_005d1e30((int)m_screen, FUN_005e23d0(0xa), 0xbe);
        m_340.FUN_005d1e30((int)m_screen, FUN_005e23d0(1), 0xbe);
        m_440.FUN_005d1e30((int)m_screen, FUN_005e23d0(2), 0xbe);
        m_540.FUN_005d1e30((int)m_screen, FUN_005e23d0(3), 0xbe);
        m_640.FUN_005d1e30((int)m_screen, FUN_005e23d0(4), 0xbe);
        m_740.FUN_005d1e30((int)m_screen, FUN_005e23d0(0xc), 0xbe);
        ((RHMapWidget *)&m_840)->V30(g_unk0x006c0b50, RHMapBox(0.0f, 100.0f, 480.0f, 480.0f), 0, unsigned(-1));
        {
            std::wstring text(g_unk0x006c0b50);
            ((RHMapWidget *)&m_940)->V30(text, RHMapBox(0.0f, 125.0f, 480.0f, 480.0f), 0, unsigned(-1));
        }
        ((SBUIUnk0060dd00 *)&m_840.m_renderer)->FUN_0060e0d0(edit, edit, edit, edit);
        ((SBUIUnk0060dd00 *)&m_940.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((RHMenuCampaignMap *)this)->V30(&m_140);
        ((RHMenuCampaignMap *)this)->V30(&m_240);
        ((RHMenuCampaignMap *)this)->V30(&m_340);
        ((RHMenuCampaignMap *)this)->V30(&m_740);
        ((RHMenuCampaignMap *)this)->V30(&m_440);
        ((RHMenuCampaignMap *)this)->V30(&m_540);
        ((RHMenuCampaignMap *)this)->V30(&m_640);
        ((RHMenuCampaignMap *)this)->V30(&m_840);
        ((RHMenuCampaignMap *)this)->V30(&m_940);
        RHIntroInsert(widgets, &m_140);
        RHIntroInsert(widgets, &m_240);
        RHIntroInsert(widgets, &m_340);
        RHIntroInsert(widgets, &m_740);
        RHIntroInsert(widgets, &m_440);
        RHIntroInsert(widgets, &m_540);
        RHIntroInsert(widgets, &m_640);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_140, true);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_240, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_340, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_740, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_440, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_540, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_640, true);
        UpdatePlayerProfile();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0052ec40
int RHMenuIntro::FUN_0052ec40()
{
    return m_choice;
}

// FUNCTION: GAME 0x0052ec50
void *RHMenuIntro::FUN_0052ec50()
{
    return (void *)m_result.m_slot;
}

// FUNCTION: GAME 0x0052ec60
bool RHMenuIntro::FUN_0052ec60(int, void *, void *)
{
    if (g_unk0x006c0685)
    {
        SBThreadedInput *input = g_unk0x6c1340;
        input->SetMouseEnabled(false);
        FUN_0052f540();
        input->SetMouseEnabled(true);
        ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    }
    return false;
}

// FUNCTION: GAME 0x0052ecb0
bool RHMenuIntro::FUN_0052ecb0(int, void *, void *)
{
    bool confirmed = RHMenuYesNo::AskForConfirmation(m_screen, FUN_005e23d0(0x107)) == true;
    if (confirmed)
    {
        m_choice = 1;
        ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
        ((RHGameMenuCalls *)this)->FUN_00544b30();
    }
    else
        ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052ed80
bool RHMenuIntro::FUN_0052ed80(int, void *, void *)
{
    m_result = RHMenuLoadSave::FUN_00531110(m_screen->FUN_0053bf30(), true);
    if (m_result.m_choice == 7)
    {
        m_choice = 3;
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        return false;
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

#include "RHMenuNewPlayer.h"
#include "RHPlayerProfile.h"

extern "C" int __cdecl wsprintfW(wchar_t *, const wchar_t *, ...);
std::wstring FUN_005e2bf0(int value);

void EmitRHMenuIntroAccessors(RHMenuIntro *menu)
{
    menu->FUN_0052ec40();
    menu->FUN_0052ec50();
}

// FUNCTION: GAME 0x0052edf0
bool RHMenuIntro::FUN_0052edf0(int, void *, void *)
{
    RHMenuMovies::FUN_00537220(m_screen->FUN_0053bf30());
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

#include "RHMenuSelectPlayer.h"
#include "SBDrawManager.h"
#include "RHSoundCore.h"
#include "RHUnk0049b100.h"

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
extern RHUnk005ef320 *g_unk0x6c11d0;

// FUNCTION: GAME 0x0052ee20
bool RHMenuIntro::FUN_0052ee20(int, void *, void *)
{
    SBGeoVector2D resolution(*(SBGeoVector2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
    RHMenuSelectPlayer::FUN_0053ede0(m_screen->FUN_0053bf30());
    ((RHSound *)g_unk0x006c1070)->ApplySoundSettings();
    if (resolution.FUN_005fc0e0(*(SBGeoPoint2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54)))
    {
        float height = *(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x58);
        float width = *(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54);
        g_unk0x6c11d0->FUN_005e4810((int)width, (int)height, 16);
        SBThreadedInput::SetTheClippingBox(RHMapBox(0.0f, 0.0f,
            ((RHUnk0049b100 *)&((RHPlayerProfile *)((RHUnk0055dbb0 *)RHPlayerProfileManager::FUN_0052ef90())->FUN_0055dbb0())->FUN_0052ef80().m_point)->FUN_0049b100(),
            ((RHUnk0049b100 *)&((RHPlayerProfile *)((RHUnk0055dbb0 *)RHPlayerProfileManager::FUN_0052ef90())->FUN_0055dbb0())->FUN_0052ef80().m_point)->FUN_0049b110()));
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        m_choice = 4;
    }
    else
        UpdatePlayerProfile();
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052efa0
bool RHMenuIntro::FUN_0052efa0(int, void *, void *)
{
    m_choice = 2;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0052efc0
bool RHMenuIntro::FUN_0052efc0(int, void *, void *)
{
    SBGeoVector2D resolution(*(SBGeoVector2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
    if (RHMenuOptions::FUN_00538e80(m_screen->FUN_0053bf30()))
    {
        if (resolution.FUN_005fc0e0(*(SBGeoPoint2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54)))
        {
            ((RHGameMenuCalls *)this)->FUN_00544b30();
            m_choice = 4;
        }
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052f070
void RHMenuIntro::UpdatePlayerProfile()
{
    RHPlayerProfileManager &manager = *(RHPlayerProfileManager *)g_unk0x006c0e48;
    if (manager.m_2c)
    {
        RHMenuNewPlayer menu(m_screen);
        menu.Create();
        menu.FUN_00544b80(true, true);
        manager.m_2c = false;
        if (menu.FUN_005383e0())
        {
            manager.FUN_0055d930(0);
            RHPlayerProfile *created = manager.AddProfile(menu.GetName(), menu.FUN_00538280());
            manager.FUN_0055e550(created);
            manager.Save();
        }
    }
    RHPlayerProfile *profile = (RHPlayerProfile *)((RHUnk0055dbb0 *)&manager)->FUN_0055dbb0();
    ((RHGameMenuText *)&m_840)->v11(profile->GetName());
    wchar_t buffer[1024];
    std::wstring rating;
    wsprintfW(buffer, FUN_005e23d0(0x3f).c_str(), profile->GetM24());
    rating = buffer;
    wsprintfW(buffer,
        // STRING: GAME 0x006b0dbc
        L"%s : %s\n%s\n%s : %i\n%s : %i %%\n%s : %i %%\n%s : %s",
        FUN_005e23d0(0x43).c_str(), RHPlayerProfile::ConvertDifficultyLevelToWideString(profile->GetM1c()).c_str(),
        rating.c_str(), FUN_005e23d0(0x40).c_str(), profile->GetM20(),
        FUN_005e23d0(0x41).c_str(), profile->GetM28(),
        FUN_005e23d0(0x42).c_str(), profile->GetM2c(),
        FUN_005e23d0(0x102).c_str(), FUN_005e2bf0(profile->GetM30()).c_str());
    ((RHGameMenuText *)&m_940)->v11(std::wstring(buffer));
}
