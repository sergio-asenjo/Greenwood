#ifndef RHGAMEBLAZONWIDGET_H
#define RHGAMEBLAZONWIDGET_H

#include "Decomp.h"

class RHMission;
struct SBFrameInputEvent;

class RHGameBlazonValue
{
public:
    void FUN_0044f960(int value);
    void FUN_0044f8d0(int value);
};

// SIZE 0xb4
class RHGameBlazonWidget
{
public:
    void FUN_005cc840();
    static RHMission *FUN_005cc870();
    SBFrameInputEvent *FUN_005cc8c0(const void *input);
    void FUN_005cc900(int value);
    void FUN_005cc920(int value);
    undefined m_00[0xb0]; // 0x00
    RHGameBlazonValue *m_b0; // 0xb0
};

#endif
