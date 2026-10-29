#ifndef RHMENUWINDOWFOCUS_00544C50_H
#define RHMENUWINDOWFOCUS_00544C50_H

#include "Decomp.h"
#include "RHMenuScreenView.h"

class RHMenuWindowUI;
struct RHFocusEvent;

#include "RHFocusManager.h"

#include "RHPortraitRootLifetime.h"

class SBFrameWnd
{
public:
    void FUN_0061a3a0();
};

// SIZE 0xc8
class RHMenuWindow
{
public:
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground);
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, long resource, bool saveBackground);
    ~RHMenuWindow();
    unsigned m_vptr;              // 0x00
    undefined m_04[0x58];         // 0x04
    bool m_5c;                    // 0x5c
    bool m_5d;                    // 0x5d
    undefined m_5e[0x56];         // 0x5e
    RHMenuWindowScreen *m_screen; // 0xb4
    undefined m_b8[0x10];         // 0xb8
};

// SIZE 0x140
class RHMenuWindowFocus : public RHMenuWindow
{
public:
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap);
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap);
    ~RHMenuWindowFocus();
    void *FUN_00544cd0(unsigned flags);
    void *FUN_00545090(const void *input);
    void FUN_005450d0();
    RHFocusManager m_focus; // 0xc8
    SBGeoPoint2D m_138;     // 0x138
};

#endif
