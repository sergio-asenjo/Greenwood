// RHMenuIngame.cpp — menu TU (code 0x0052d3e0..0x0052e080). See RHMenuIngame.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuIngame.h"
#include "RHMapBox.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "RHMission.h"

// FUNCTION: GAME 0x0052d3e0
void RHMenuIngame::FUN_0052d3e0(RHMenuEvent *event)
{
    if (FUN_0052d400(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0052d400
bool RHMenuIngame::FUN_0052d400(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x140)
        handled = FUN_0052dcf0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = FUN_0052dd10(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_0052dd80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x540)
        handled = FUN_0052de40(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = FUN_0052de60(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x640)
        handled = FUN_0052ded0(2, event->m_widget, event->m_data);
    return handled;
}

#include "RHEngineAccessors.h"

class RHEngine;
extern RHEngine *g_pEngine;

// FUNCTION: GAME 0x0052d4e0
RHMenuIngame::RHMenuIngame(RHMenuScreenView *screen, bool pause)
    : RHMenuWindowFocus(0, screen, 0, false), m_pause(pause), m_pauseToken(0), m_750(false), m_751(false)
{
    if (pause)
        m_pauseToken = new RHMenuIngamePauseToken(true);
    else
        m_pauseToken = (RHMenuIngamePauseToken *)((RHUnk004e3760 *)g_pEngine)->Get();
}

// FUNCTION: GAME 0x0052d600
void *RHMenuIngame::FUN_0052d600(unsigned flags)
{
    this->~RHMenuIngame();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052d620
RHMenuIngame::~RHMenuIngame()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_continue);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_load);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_save);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_options);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_restart);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_quit);
    m_pauseToken->DestroyWidgets();
    if (m_pause)
        delete m_pauseToken;
}

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);
extern RHUnk00452030 *g_unk0x6c07fc;

inline void RHIngameInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x0052d750
bool RHMenuIngame::FUN_0052d750()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        std::vector<void *> widgets;
        m_continue.FUN_005d1e30((int)m_screen, FUN_005e23d0(9), 0xbe);
        m_load.FUN_005d1e30((int)m_screen, FUN_005e23d0(10), 0xbe);
        m_save.FUN_005d1e30((int)m_screen, FUN_005e23d0(11), 0xbe);
        m_options.FUN_005d1e30((int)m_screen, FUN_005e23d0(12), 0xbe);
        m_restart.FUN_005d1e30((int)m_screen, FUN_005e23d0(13), 0xbe);
        m_quit.FUN_005d1e30((int)m_screen, FUN_005e23d0(14), 0xbe);
        ((RHMenuCampaignMap *)this)->V30(&m_continue);
        ((RHMenuCampaignMap *)this)->V30(&m_load);
        ((RHMenuCampaignMap *)this)->V30(&m_save);
        ((RHMenuCampaignMap *)this)->V30(&m_options);
        ((RHMenuCampaignMap *)this)->V30(&m_restart);
        ((RHMenuCampaignMap *)this)->V30(&m_quit);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_continue, 1);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_continue, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_load, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_save, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_options, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_restart, true);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_quit, true);
        RHIngameInsert(widgets, &m_continue);
        RHIngameInsert(widgets, &m_load);
        RHIngameInsert(widgets, &m_save);
        RHIngameInsert(widgets, &m_options);
        RHIngameInsert(widgets, &m_restart);
        RHIngameInsert(widgets, &m_quit);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        m_pauseToken->CreateWidgets((RHMenuWindow *)this, RHMapBox(2.0f, 2.0f, 440.0f, 480.0f));
        RHMission *mission = *(RHMission **)((char *)g_unk0x6c07fc + 0x178);
        m_restart.SetEnabled(*(int *)((char *)mission->m_profile + 0x3c) != 8);
        return true;
    }
    return false;
}

extern RHUnk0048a970 *g_unk0x6c0b3c;

// FUNCTION: GAME 0x0052dc20
void RHMenuIngame::FUN_0052dc20()
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    RHMenuIngame menu(&screen, true);
    menu.FUN_0052d750();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x0052dce0
RHMenuLoadSaveResult *RHMenuIngame::FUN_0052dce0()
{
    return &m_result;
}

// FUNCTION: GAME 0x0052dcf0
bool RHMenuIngame::FUN_0052dcf0(int, void *, void *)
{
    m_result.m_choice = 0;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0052dd10
bool RHMenuIngame::FUN_0052dd10(int, void *, void *)
{
    m_result = RHMenuLoadSave::FUN_00531110(m_screen->FUN_0053bf30(), true);
    if (m_result.m_choice == 7)
    {
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        return false;
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052dd80
bool RHMenuIngame::FUN_0052dd80(int, void *, void *)
{
    SBGeoVector2D resolution(*(SBGeoVector2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
    if (RHMenuOptions::FUN_00538e80(m_screen->FUN_0053bf30()))
    {
        if (resolution.FUN_005fc0e0(*(SBGeoPoint2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54)))
        {
            m_750 = true;
            ((RHGameMenuCalls *)this)->FUN_00544b30();
        }
        m_751 = true;
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052de40
bool RHMenuIngame::FUN_0052de40(int, void *, void *)
{
    m_result.m_choice = 5;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0052de60
bool RHMenuIngame::FUN_0052de60(int, void *, void *)
{
    m_result = RHMenuLoadSave::FUN_00531110(m_screen->FUN_0053bf30(), false);
    if (m_result.m_choice == 8)
    {
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        return false;
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052ded0
bool RHMenuIngame::FUN_0052ded0(int, void *, void *)
{
    RHMenuYesNo dialog(m_screen, FUN_005e23d0(0x1f));
    dialog.FUN_00545710();
    dialog.FUN_00544b80(true, true);
    dialog.FUN_00544300();
    if (dialog.FUN_00545ad0() == 1)
    {
        m_result.m_choice = 6;
        ((RHGameMenuCalls *)this)->FUN_00544b30();
    }
    else
        ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052dfd0
bool RHMenuIngame::FUN_0052dfd0()
{
    return m_750;
}

void EmitRHMenuIngameAccessors(RHMenuIngame *menu)
{
    menu->FUN_0052dce0();
    menu->FUN_0052dfd0();
}
