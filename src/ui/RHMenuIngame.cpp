// RHMenuIngame.cpp — menu TU (code 0x0052d3e0..0x0052e080). See RHMenuIngame.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuIngame.h"

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
    : RHMenuWindowFocus(0, screen, 0, false)
{
    m_pause = pause;
    m_pauseToken = 0;
    m_750 = false;
    m_751 = false;
    m_vptr = 0x006794c0;
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

extern RHUnk0048a970 *g_unk0x6c0b3c;

// FUNCTION: GAME 0x0052dc20
void RHMenuIngame::FUN_0052dc20()
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    RHMenuIngame menu(&screen, true);
    menu.FUN_0052d750();
    menu.FUN_00544b80(true, true);
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
    RHMenuResolution resolution(*(SBGeoPoint2D *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
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
