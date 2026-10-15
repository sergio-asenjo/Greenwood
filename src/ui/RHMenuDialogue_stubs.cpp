// Stub definitions for the external symbols RHMenuDialogue.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHMenuDialogue::GetDialogue are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in
// a separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBAssert is already defined once, in RHSword_stubs.cpp; this TU only
// declares it (include/SB.h).

#include "SBNullstr.h"
#include "RHMenuDialogue.h"

// Target 0x004e35a0 (RHEngine::GetDynResources).
RHDialogueSet *RHEngine::GetDynResources(unsigned long) { return 0; }

// The global entity at 0x006c0a88.
// GLOBAL: GAME 0x006c0a88
RHEngine *g_pEngine = 0;

class RHSound
{
public:
    float GetDialogVolume();
    bool IsDialogFinished();
    void PauseDialog();
};

float RHSound::GetDialogVolume() { return 0.0f; }
bool RHSound::IsDialogFinished() { return true; }
void RHSound::PauseDialog() {}

class RHUnk005cba10
{
public:
    void FUN_005cba10(unsigned);
    void FUN_005cbc80(unsigned);
};

void RHUnk005cba10::FUN_005cba10(unsigned) {}
void RHUnk005cba10::FUN_005cbc80(unsigned) {}

RHMenuDialogue::RHMenuDialogue(RHMenuScreenView *, unsigned long) {}
RHMenuDialogue::~RHMenuDialogue() {}
bool RHMenuDialogue::Create() { return false; }

void RHDialogueWidgetLifetimeCalls::FUN_0052b890() {}
void RHDialogueWidgetLifetimeCalls::FUN_0052bd90() {}
void RHDialogueWidgetLifetimeCalls::FUN_0052be10() {}
void RHDialogueWidgetLifetimeCalls::FUN_0052bf00() {}
