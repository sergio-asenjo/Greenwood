#ifndef RHMENUFOCUSCLASS_H
#define RHMENUFOCUSCLASS_H

#include "Decomp.h"
#include <string>
#include "RHMenuWindowClass.h"

class RHMenuWindowFocus
{
public:
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap);
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap);
    ~RHMenuWindowFocus();
    virtual void V00();
    void FUN_00544b80(bool display, bool modal) { ((RHMenuWindow *)this)->FUN_00544b80(display, modal); }
    void FUN_00544300() { ((RHMenuWindow *)this)->FUN_00544300(); }

    undefined m_04[0xb0];
    RHMenuWindowScreen *m_screen;
    undefined m_b8[0x88];
};

class RHPortraitButton
{
public:
    RHPortraitButton();
    ~RHPortraitButton();
    bool FUN_005d1e30(int mode, const std::wstring &text, int resource);
    void SetEnabled(bool enabled) { m_enabled = enabled; }

    undefined m_00[4];
    bool m_enabled;
    undefined m_05[0xfb];
};

#endif
