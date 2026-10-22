#ifndef RH_GAME_PAD_H
#define RH_GAME_PAD_H

#include "Decomp.h"
#include "SBInput.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include <list>

class RHMessenger;
class RHEngine;

// SIZE 0x50
struct SBInputJoystickState
{
    long m_00[0x14]; // 0x00
};

// VTABLE: GAME 0x00679090
// SIZE 0x78
class RHGamePad
{
public:
    RHGamePad();
    virtual ~RHGamePad();
    void ProcessGamepadInput();
    unsigned char GetSelectedIndexPC();
    void FUN_00518b30(SBInputJoystickState &state);
    void FUN_00518ed0(SBInputJoystickState &state);
    void FUN_005191e0(SBInputJoystickState &state);
    void FUN_00519620(SBInputJoystickState &state);
    void FUN_00519840(SBInputJoystickState &state);
    void FUN_00519c70(SBInputJoystickState &state);

    SBInputUnk005fb730 *m_input; // 0x04
    RHMessenger *m_messenger; // 0x08
    RHEngine *m_engine; // 0x0c
    unsigned char m_joystick; // 0x10
    SBInputJoystickState m_previous; // 0x14
    bool m_64; // 0x64
    undefined4 m_68; // 0x68
    std::list<SBGeoPoint2D> m_points; // 0x6c
};

DECOMP_SIZE_ASSERT(RHGamePad, 0x78)

#endif
