// RHMenuMovies.cpp — menu TU (code 0x00536ad0..). See RHMenuMovies.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuMovies.h"

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
        handled = FUN_0052b520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00537370(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00536b70
RHMenuMovies::RHMenuMovies(RHMenuScreenView *screen) : RHMenuWindowFocus(0, screen, 0, false)
{
    m_vptr = 0x0067972c;
}

// FUNCTION: GAME 0x00536c30
void *RHMenuMovies::FUN_00536c30(unsigned flags)
{
    this->~RHMenuMovies();
    if (flags & 1)
        operator delete(this);
    return this;
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
