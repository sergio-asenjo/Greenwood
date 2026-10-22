#ifndef RH_UNK005EF320_WINDOW_VIEW_H
#define RH_UNK005EF320_WINDOW_VIEW_H

#include <windows.h>

struct RHUnk005ef320WindowView
{
    char m_pad0[0x100];
    HWND m_window;
    HWND GetWindow() const { return m_window; }
};

#endif
