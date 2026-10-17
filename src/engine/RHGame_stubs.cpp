#include "SBNullstr.h"
#include "RHGame_calls.h"

void RHGame::FUN_00512310() {}

RHGameWidgetLifetimeBase::RHGameWidgetLifetimeBase() {}
RHGameWidgetLifetimeBase::~RHGameWidgetLifetimeBase() {}
RHGameRenderer0060dad0::RHGameRenderer0060dad0() {}
RHGameRenderer0060dad0::~RHGameRenderer0060dad0() {}
RHGameRenderer0060da10::RHGameRenderer0060da10() {}
RHGameRenderer0060da10::~RHGameRenderer0060da10() {}
RHGameRenderer005cb220::~RHGameRenderer005cb220() {}
RHGameRenderer0060dab0::RHGameRenderer0060dab0() {}
RHGameRenderer0060dab0::~RHGameRenderer0060dab0() {}
RHGameRenderer005c9270::RHGameRenderer005c9270() {}
RHGameRenderer005c9270::~RHGameRenderer005c9270() {}
void RHGameLifetimeDeleteCalls::FUN_0050a460() {}
void RHGameLifetimeDeleteCalls::FUN_0050a4f0() {}
void RHGameLifetimeDeleteCalls::FUN_0050a5c0() {}

void RHGameWidgetBaseCalls::FUN_0060d290(unsigned long) {}
bool RHGameWidgetRendererCalls::FUN_0060d890(const SBGeoPoint2D &) { return false; }
bool RHGameWidgetRendererCalls::FUN_005c9320(unsigned) { return false; }
void RHGameWidgetAnimatedCalls::FUN_005d5790(void *, int, bool) {}

namespace std
{
    template<> void _Construct(RHUnk00514e10::Value *destination, const RHUnk00514e10::Value &value)
    {
        new ((void *)destination) RHUnk00514e10::Value(value);
    }
}

bool RHGameMission::FUN_0054c800() { return false; }
void RHGameMenuOwner::FUN_0053c870(void *) {}
void RHGameBlazonValue::FUN_0044f960(int) {}
void RHGameBlazonValue::FUN_0044f8d0(int) {}

void RHGameSaveCalls::FUN_0056ecc0() {}
RHGameConfig::RHGameConfig() {}
RHGameConfig::~RHGameConfig() {}
bool RHGameConfig::FUN_00611960(SBFile &) { return true; }

void RHGameSyncCalls::FUN_00513520(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_005134c0(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_00513b00(void *) {}
void RHGameSyncCalls::FUN_0050ed40() {}
void RHGameSyncCalls::FUN_00514670() {}
void RHGameSyncCalls::FUN_005146f0() {}
void RHGameSyncCalls::FUN_0048a970(RHUnk005492a0 &) {}
bool RHGameEngineCalls::FUN_004c7cd0() { return false; }
bool RHGameEngineCalls::FUN_004c7cf0() { return false; }
// FUNCTION: GAME 0x004936e0
bool RHGameActorView::FUN_004936e0()
{
    return *(bool *)((char *)*(void **)((char *)this + 0x4ec) + 0xca9);
}
void RHGameWidgetCalls::FUN_0051df00(void *) {}
int __stdcall RHGameWindowCalls::CloseWindow(void *) { return 0; }
void RHGameActionCalls::FUN_005140b0() {}
void RHGameActionCalls::FUN_005f4900(char) {}
void RHGameActionCalls::FUN_005e5260() {}
void RHGameActionCalls::FUN_005104c0() {}
bool RHGameActionCalls::FUN_004d2300(void *, unsigned) { return false; }
void RHGameActionCalls::FUN_004da2f0() {}
void RHGameActionCalls::FUN_005a7b40(int) {}
void RHGamePortraitCalls::FUN_005d6690() {}

// LIBRARY: GAME 0x00642a00
// __chkstk
