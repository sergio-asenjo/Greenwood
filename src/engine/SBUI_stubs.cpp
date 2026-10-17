#include "SBUI.h"

void SBUIWindowTooltip::FUN_00627ee0(unsigned long) {}

void SBThreadedInput::FUN_005f1700() {}

void SBUI::FUN_006189e0(unsigned long) {}
// Parked: VC6 folds the sub-object pointer back to [ecx+0xb0]; the target
// re-bases ecx (add ecx,0xb0) before the three stores. Probed int*/char*/
// struct-pointer locals and member assignments all fold.
// STUB: GAME 0x00628500
void SBUIWindowTooltip::FUN_00628500() {}



SBUI::~SBUI() {}

// FUNCTION: GAME 0x006287e0
SBUIUnkSurfaceBase::~SBUIUnkSurfaceBase()
{
    m_vptr = 0x0067ae04;
}
SBUIUnkSurface::~SBUIUnkSurface() {}
