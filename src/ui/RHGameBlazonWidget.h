#ifndef RHGAMEBLAZONWIDGET_H
#define RHGAMEBLAZONWIDGET_H

#include "Decomp.h"
#include "RHPortraitRootList.h"
#include "RHMenuShortMissionBlazons.h"

class RHMission;

// VTABLE: GAME 0x00679ee0
// SIZE 0xb4
class RHGameBlazonWidget : public RHPortraitRootList
{
public:
    RHGameBlazonWidget();
    void *FUN_005cc610(unsigned flags);
    ~RHGameBlazonWidget();
    bool FUN_005cc680(const SBGeoBoundingBox2D &bounds);
    void FUN_005cc7b0(const SBGeoBoundingBox2D &bounds);
    void FUN_005cc840();
    static RHMission *FUN_005cc870();
    SBFrameInputEvent *FUN_005cc8c0(const void *input);
    void FUN_005cc900(int value);
    void FUN_005cc920(int value);
    void FUN_005cc940(const SBGeoBoundingBox2D &bounds);
    RHMenuShortMissionBlazons *m_b0; // 0xb0
};

#endif
