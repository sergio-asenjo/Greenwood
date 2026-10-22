#ifndef RHMENUWINDOWCLASS_H
#define RHMENUWINDOWCLASS_H

#include "RHPortraitRootList.h"

class RHMenuScreenView;
typedef RHMenuScreenView RHMenuWindowScreen;
class RHUnkFXDraw;

// VTABLE: GAME 0x00679a28
// SIZE 0xc8
class RHMenuWindow : public RHPortraitRootList
{
public:
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground);
    ~RHMenuWindow();
    void *FUN_00543f80(unsigned flags);
    void FUN_00544300();
    void FUN_00544b80(bool display, bool modal);

    RHUnkFXDraw *m_draw;
    RHMenuWindowScreen *m_screen;
    RHMenuWindow *m_parent;
    long m_resource;
    unsigned long m_saveSurface;
    bool m_resourceHeld;
};

#endif
