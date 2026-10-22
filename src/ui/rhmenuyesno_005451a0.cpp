#include "SBNullstr.h"
#include "RHMenuWindow.h"

#define m_choice (*(int *)((char *)this + 0x444))

// FUNCTION: GAME 0x005451a0
void RHMenuYesNo::HandleEvent(RHMenuEvent *event)
{
    if (RouteEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x005451c0
bool RHMenuYesNo::RouteEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x344)
        handled = OnYes(event->m_type, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x244)
        handled = OnNo(event->m_type, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00545590
void *RHMenuYesNo::FUN_00545590(unsigned flags)
{
    this->~RHMenuYesNo();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005455b0
RHMenuYesNo::~RHMenuYesNo()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_144);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_244);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_344);
}

// FUNCTION: GAME 0x00545670
bool RHMenuYesNo::AskForConfirmation(RHMenuWindowScreen *screen, const std::wstring &text)
{
    RHMenuYesNo dialog(screen, text);
    dialog.FUN_00545710();
    dialog.FUN_00544b80(true, true);
    dialog.FUN_00544300();
    return dialog.FUN_00545ad0() == 1;
}

// FUNCTION: GAME 0x00545ad0
int RHMenuYesNo::FUN_00545ad0()
{
    return m_choice;
}

// FUNCTION: GAME 0x00545ae0
bool RHMenuYesNo::OnNo(int, void *, void *)
{
    m_choice = 2;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

// FUNCTION: GAME 0x00545b00
bool RHMenuYesNo::OnYes(int, void *, void *)
{
    m_choice = 1;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}
