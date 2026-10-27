// RHMenuMovies.cpp — menu TU (code 0x00536ad0..). See RHMenuMovies.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuMovies.h"
#include "RHMenuCloseCalls.h"
#include "RHMapBox.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "SBUIRenderer.h"
#include "RHGame_calls.h"

std::string FUN_004e4c70(const std::string &first, const char *second);

// GLOBAL: GAME 0x006c0670
std::string g_unk0x006c0670;

// FUNCTION: GAME 0x00536ad0
void RHMenuMovies::FUN_00536ad0(RHMenuEvent *event)
{
    if (FUN_00536af0(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00536af0
bool RHMenuMovies::FUN_00536af0(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = FUN_005372e0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = ((RHMenuCloseCalls *)this)->FUN_0052b520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00537370(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00536b70
RHMenuMovies::RHMenuMovies(RHMenuScreenView *screen) : RHMenuWindowFocus(0, screen, 0, false)
{
}

// FUNCTION: GAME 0x00536c50
RHMenuMovies::~RHMenuMovies()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_intro);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_outro);
}

// FUNCTION: GAME 0x00536c30
void *RHMenuMovies::FUN_00536c30(unsigned flags)
{
    this->~RHMenuMovies();
    if (flags & 1)
        operator delete(this);
    return this;
}

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHMoviesInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// Parked: inline budget differs, so zero stays register-cached and the frame is 8 bytes larger.
// STUB: GAME 0x00536d30
bool RHMenuMovies::FUN_00536d30()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        void *font = m_screen->FUN_0053be80(std::string("MissionTitle"));
        std::vector<void *> widgets;
        m_ok.FUN_005d1e30((int)m_screen, FUN_005e23d0(15), 0xbe);
        ((RHMenuCampaignMap *)this)->V30(&m_ok);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, true);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 1);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x9c);
        RHMoviesInsert(widgets, &m_ok);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        widgets.clear();
        m_intro.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x129);
        m_outro.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x12a);
        ((RHMenuCampaignMap *)this)->V30(&m_intro);
        ((RHMenuCampaignMap *)this)->V30(&m_outro);
        ((RHUnk005d92c0Sub *)&m_intro)->v08(SBGeoPoint2D(110.0f, 80.0f));
        RHMoviesInsert(widgets, &m_intro);
        RHMoviesInsert(widgets, &m_outro);
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 30);
        ((RHMapWidget *)&m_title)->V30(FUN_005e23d0(2), RHMapBox(0.0f, 0.0f, 500.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(font, font, font, font);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        if (*(unsigned *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x2c) < 100)
            ((RHMenuCampaignMap *)this)->V38(&m_outro);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00537220
void RHMenuMovies::FUN_00537220(RHMenuWindowUI *ui)
{
    RHMenuScreenView screen(0, 0xbc, 0, ui);
    RHMenuMovies menu(&screen);
    menu.FUN_00536d30();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x005372e0
bool RHMenuMovies::FUN_005372e0(int, void *, void *)
{
    FUN_00537400(FUN_004e4c70(g_unk0x006c0670,
        // STRING: GAME 0x006b0f40
        "\\Intro.vid"));
    return false;
}

// FUNCTION: GAME 0x00537370
bool RHMenuMovies::FUN_00537370(int, void *, void *)
{
    FUN_00537400(FUN_004e4c70(g_unk0x006c0670,
        // STRING: GAME 0x006b0f4c
        "\\Outro.vid"));
    return false;
}

#include "SBThreadedInput.h"
#include "SBDrawManager.h"
#include "RHGameActionCalls.h"

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
extern SBThreadedInput *g_unk0x6c1340;
extern RHUnk005ef320 *g_unk0x6c11d0;
extern char g_unk0x006c0685;
void FUN_004013a0(const std::string &name);

// Parked at 0.6400: left by the killed batch-105 run before its residual was diagnosed. The
// movie-launch sequence is close but the remaining divergence was never established.
// STUB: GAME 0x00537400
void RHMenuMovies::FUN_00537400(const std::string &path)
{
    if (g_unk0x006c0685)
    {
        RHGameActionCalls *sound = (RHGameActionCalls *)g_unk0x006c1070;
        SBThreadedInput *input = g_unk0x6c1340;
        RHUnk005ef320 *draw = g_unk0x6c11d0;
        sound->FUN_005a7b40(0);
        input->SetMouseEnabled(false);
        draw->FUN_005e4810(0x280, 0x1e0, 0x10);
        FUN_004013a0(path);
        draw->FUN_005e4810((int)*(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54),
            (int)*(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x58), 0x10);
        input->SetMouseEnabled(true);
        sound->FUN_005a7b40(1);
        ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    }
}
