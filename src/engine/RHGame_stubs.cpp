#include "SBNullstr.h"
#include "RHGame_calls.h"

void RHGame::FUN_00512310() {}

bool RHGameMission::FUN_0054c800() { return false; }
unsigned short RHGameCampaignView::FUN_00456270() { return 0; }
void RHGameCampaignView::FUN_00456e40(char) {}
void RHGameMenuOwner::FUN_0053c870(void *) {}
void RHGameBlazonValue::FUN_0044f960(int) {}
void RHGameBlazonValue::FUN_0044f8d0(int) {}

void RHGameSaveCalls::FUN_0056ecc0() {}
RHGameConfig::RHGameConfig() {}
RHGameConfig::~RHGameConfig() {}
bool RHGameConfig::FUN_00611960(SBFile &) { return true; }
RHGameDialog::RHGameDialog(int, int, bool, bool, void *) {}
RHGameDialog::~RHGameDialog() {}

RHSaveGame *RHGameContinueCalls::FUN_0056f730(const std::wstring &, const std::string &) { return 0; }
void RHGameContinueCalls::FUN_0056f700(RHSaveGame *, RHSaveGame *, const std::wstring &) {}
RHGamePortraitCalls *RHGameSyncCalls::FUN_0050f140(void *) { return 0; }
void RHGameSyncCalls::FUN_00513520(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_005134c0(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_00513b00(void *) {}
void RHGameSyncCalls::FUN_0050ed40() {}
void RHGameSyncCalls::FUN_00514670() {}
void RHGameSyncCalls::FUN_005146f0() {}
void RHGameSyncCalls::FUN_0048a970(RHUnk005492a0 &) {}
bool RHGameEngineCalls::FUN_004c7cd0() { return false; }
bool RHGameEngineCalls::FUN_004c7cf0() { return false; }
bool RHGameActorView::FUN_004936e0() { return false; }
void RHGameWidgetCalls::FUN_0051df00(void *) {}
int __stdcall RHGameWindowCalls::CloseWindow(void *) { return 0; }
void RHGameActionCalls::FUN_005140b0() {}
void RHGameActionCalls::FUN_0050eff0() {}
void RHGameActionCalls::FUN_005f4900(char) {}
void RHGameActionCalls::FUN_005f0fa0() {}
void RHGameActionCalls::FUN_005ef380(int) {}
void RHGameActionCalls::FUN_005e5260() {}
void RHGameActionCalls::FUN_005104c0() {}
void RHGameActionCalls::FUN_005104d0() {}
void RHGameActionCalls::FUN_00619cc0() {}
bool RHGameActionCalls::FUN_004d2300(void *, unsigned) { return false; }
void RHGameActionCalls::FUN_004da2f0() {}
void RHGameActionCalls::FUN_005a7b40(int) {}
void RHGamePortraitCalls::FUN_005d9b10() {}
void RHGamePortraitCalls::FUN_005d9ae0(unsigned short, bool) {}
void RHGamePortraitCalls::FUN_005d9b70() {}
void RHGamePortraitCalls::FUN_005d9a60(unsigned) {}
void RHGamePortraitCalls::FUN_005d9950(unsigned) {}
void RHGamePortraitCalls::FUN_005d6690() {}
void RHGameNotificationCalls::FUN_0055e7a0(unsigned) {}
void FUN_0053a830() {}

// FUNCTION: GAME 0x00642a00
// __chkstk
