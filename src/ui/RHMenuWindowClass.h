#ifndef RHMENUWINDOWCLASS_H
#define RHMENUWINDOWCLASS_H

#include "RHPortraitRootList.h"

class RHMenuScreenView;
typedef RHMenuScreenView RHMenuWindowScreen;
class SBDrawManager;

// VTABLE: GAME 0x00679a28
// SIZE 0xc8
class RHMenuWindow : public RHPortraitRootList
{
public:
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground);
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, long resource, bool saveBackground);
    ~RHMenuWindow();
    void *FUN_00543f80(unsigned flags);
    void FUN_00544300();
    void FUN_00544380(const std::vector<void *> &widgets, unsigned spacing);
    void FUN_00544600(const std::vector<void *> &widgets, unsigned spacing);
    unsigned FUN_00544800(const std::vector<void *> &widgets, unsigned spacing);
    void FUN_005449e0(const std::vector<void *> &widgets, unsigned spacing);
    virtual bool FUN_0061a1e0(const std::wstring &title, const RHMapBox &box, unsigned flags);
    void FUN_00544b80(bool display, bool modal);

    SBDrawManager *m_draw;
    RHMenuWindowScreen *m_screen;
    RHMenuWindow *m_parent;
    long m_resource;
    unsigned long m_saveSurface;
    bool m_resourceHeld;
};

#endif
