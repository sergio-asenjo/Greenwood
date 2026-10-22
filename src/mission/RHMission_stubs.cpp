// Stub definitions for the external symbols RHMission.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHMission::Serialize are direct `call rel32` (matching
// the original shape) instead of unresolved externals. They live in a separate
// translation unit so VC6 cannot inline them into the matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; RHSerializeName is defined once in
// RHElementObject_stubs.cpp. Both TUs just declare them (include/SB.h,
// include/RHMission.h).

#include "SBNullstr.h"
#include "RHMission.h"
#include "RHCampaignMissionStatus.h"

void RHMissionRequiredBounds::FUN_0054cdd0() {}
