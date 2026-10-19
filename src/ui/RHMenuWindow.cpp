// RHMenuWindow.cpp — the menu window base TU (code 0x00543e70..0x00544bcb).
// See RHMenuWindow.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuWindow.h"

void RHMenuWindow_Emit(RHMenuWindow *window)
{
    window->FUN_00544300();
}

// FUNCTION: GAME 0x00543e70
RHMenuWindow::RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground)
    : m_draw((RHUnkFXDraw *)g_unk0x6c11d0), m_screen(screen), m_parent(parent), m_resourceHeld(false)
{
    if (saveBackground)
    {
        typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
        m_saveSurface = (m_draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
            m_draw->FUN_005e56c0(0), m_draw->FUN_005e5750(0), 0, false);
        RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
        m_draw->FUN_005e6440(ui->m_17ec, 0, m_saveSurface, 0, 0);
        unsigned long background = m_screen->FUN_0053bf30()->m_17ec;
        m_draw->FUN_005e6440(0, 0, background, 0, 0);
    }
    else
    {
        m_saveSurface = (unsigned long)-1;
    }
}

// FUNCTION: GAME 0x00543f80
void *RHMenuWindow::FUN_00543f80(unsigned flags)
{
    this->~RHMenuWindow();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005442b0
RHMenuWindow::~RHMenuWindow()
{
    FUN_00544300();
}

// FUNCTION: GAME 0x00544300
void RHMenuWindow::FUN_00544300()
{
    if (m_resourceHeld)
    {
        m_resourceOwner->FUN_005fd4a0(m_resource);
        m_resourceHeld = false;
    }
    if (m_saveSurface != (unsigned long)-1)
    {
        RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
        m_draw->FUN_005e6440(m_saveSurface, 0, ui->m_17ec, 0, 0);
        m_draw->Unk005e5160(m_saveSurface);
        m_saveSurface = (unsigned long)-1;
    }
}

class RHBriefingNarrowText;

class RHBriefingParentCalls
{
public:
    void *FUN_00544b60(const RHBriefingNarrowText &name);
};

// FUNCTION: GAME 0x00544b60
void *RHBriefingParentCalls::FUN_00544b60(const RHBriefingNarrowText &name)
{
    return (*(RHPortraitTextResourceCalls **)((char *)this + 0xb4))->FUN_0053be80(*(const std::string *)&name);
}

// FUNCTION: GAME 0x00544b80
void RHMenuWindow::FUN_00544b80(bool display, bool modal)
{
    m_screen->FUN_0053bb80(this, display, modal);
}
