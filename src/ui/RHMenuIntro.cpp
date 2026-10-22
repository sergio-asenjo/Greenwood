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
