#include "SBNullstr.h"
#include "RHGame_calls.h"
#include "RHPortraitRenderer0060d470.h"
#include "RHMission.h"

// GLOBAL: GAME 0x0067bbd8
extern const unsigned g_unk0x0067bbd8 = 0xffffffff;

void RHGame::FUN_00512310() {}

RHGameWidgetLifetimeBase::RHGameWidgetLifetimeBase() {}
RHGameWidgetLifetimeBase::~RHGameWidgetLifetimeBase() {}
void RHGameWidgetLifetimeBase::FUN_0060d290(unsigned long) {}
// FUNCTION: GAME 0x0060d9f0
RHGameRenderer0060da10::RHGameRenderer0060da10()
{
    ((RHPortraitRenderer0060d470 *)this)->RHPortraitRenderer0060d470::RHPortraitRenderer0060d470();
    m_vptr = 0x67a620;
}
// FUNCTION: GAME 0x0060da10
RHGameRenderer0060da10::~RHGameRenderer0060da10()
{
    m_vptr = 0x67a620;
    ((RHPortraitRenderer0060d470 *)this)->RHPortraitRenderer0060d470::~RHPortraitRenderer0060d470();
}
RHGameRenderer0060dab0::RHGameRenderer0060dab0() {}
RHGameRenderer0060dab0::~RHGameRenderer0060dab0() {}
RHGameRenderer005c9270::RHGameRenderer005c9270() {}
RHGameRenderer005c9270::~RHGameRenderer005c9270() {}
void RHGameLifetimeDeleteCalls::FUN_0050a4f0() {}

#include "RHMobileUnk00607da0.h"

// FUNCTION: GAME 0x0060d290
void RHGameWidgetBaseCalls::FUN_0060d290(const SBGeoPoint2D &position)
{
    SBGeoVector2D offset((const SBGeoVector2D &)position);
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    SBGeoVector2D origin((const SBGeoVector2D &)box.m_first);
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(RHMobileUnk00607da0 *)&(box - origin).FUN_006090d0(offset));
}
bool RHGameWidgetRendererCalls::FUN_0060d890(const SBGeoPoint2D &) { return false; }

namespace std
{
    template<> void _Construct(RHUnk00514e10::Value *destination, const RHUnk00514e10::Value &value)
    {
        new ((void *)destination) RHUnk00514e10::Value(value);
    }
}

// FUNCTION: GAME 0x0054c800
bool RHGameMission::FUN_0054c800()
{
    char *campaign = (char *)g_unk0x6c07fc;
    void **first = *(void ***)(campaign + 0x118);
    unsigned count = first == 0 ? 0 : *(void ***)(campaign + 0x11c) - first;
    char difficulty = *(campaign + 0x100);
    unsigned value = g_unk0x6c07fc->Get(1);
    char *profile = (char *)m_profile;
    if (value >= *(unsigned *)(profile + 0x40) &&
        (*(unsigned *)(profile + 0x44) >= value || *(unsigned *)(profile + 0x44) == 200000) &&
        count >= *(unsigned short *)(profile + 0x48) &&
        *(unsigned short *)(profile + 0x4a) >= count &&
        m_04 < *(unsigned short *)(profile + 0x4c) &&
        (*(profile + 0x54) != 1 || *(profile + 0x55 + difficulty)) &&
        ((RHMission *)this)->AreRequiredMissionStatusValid(true))
        return ((RHMission *)this)->AreRequiredMissionStatusValid(false) ? true : false;
    return false;
}
void RHGameMenuOwner::FUN_0053c870(void *) {}
void RHGameBlazonValue::FUN_0044f960(int) {}
struct RHGameBlazonEntry
{
    char m_00[0xd0];
};

void FUN_0044f750(RHGameBlazonEntry *) {}

// Parked: 80.39%; target keeps the clamped count in EDI and recomputes total-visible
// for both range ends; VC6 here keeps it in EAX (param-reuse moves it to EDI but CSEs).
// STUB: GAME 0x0044f8d0
void RHGameBlazonValue::FUN_0044f8d0(int value)
{
    unsigned level = g_unk0x6c07fc->Get(3);
    unsigned visible = *(unsigned short *)(**(char ***)this + 0x6a);
    unsigned total = *(unsigned *)((char *)this + 0xc);
    if (level > total)
        level = total;
    if (level + visible <= total)
    {
        unsigned count = value;
        if (count > visible)
            count = visible;
        *(unsigned *)((char *)this + 0x18) = count;
        if (count != 0)
        {
            RHGameBlazonEntry *entries = *(RHGameBlazonEntry **)((char *)this + 0x8);
            *((char *)this + 0x14) = 1;
            *(int *)((char *)this + 0x10) = 50;
            RHGameBlazonEntry *last = entries + (total - visible + count);
            for (RHGameBlazonEntry *entry = entries + (total - visible); entry != last; ++entry)
                FUN_0044f750(entry);
        }
    }
}

void RHGameSaveCalls::FUN_0056ecc0() {}
bool RHUnk006114c0::FUN_00611960(SBFile &) { return true; }

void RHGameSyncCalls::FUN_00513520(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_005134c0(RHUnk00549250 &) {}
void RHGameSyncCalls::FUN_00513b00(void *) {}
void RHGameSyncCalls::FUN_0050ed40() {}
void RHGameSyncCalls::FUN_00514670() {}
void RHGameSyncCalls::FUN_0048a970(RHUnk00549250 &) {}
bool RHGameEngineCalls::FUN_004c7cd0() { return false; }
bool RHGameEngineCalls::FUN_004c7cf0() { return false; }
// FUNCTION: GAME 0x004936e0
bool RHGameActorView::FUN_004936e0()
{
    return *(bool *)((char *)*(void **)((char *)this + 0x4ec) + 0xca9);
}
void RHGameActionCalls::FUN_005140b0() {}
void RHGameActionCalls::FUN_005f4900(char) {}
void RHGameActionCalls::FUN_005e5260() {}
void RHGameActionCalls::FUN_005104c0() {}
bool RHGameActionCalls::FUN_004d2300(void *, unsigned) { return false; }
void RHGameActionCalls::FUN_005a7b40(int) {}
void RHGamePortraitCalls::FUN_005d6690() {}

// LIBRARY: GAME 0x00642a00
// __chkstk
class SBPicture;

class RHGameScreenshotCalls
{
public:
    void FUN_004da390(SBPicture &picture);
};

void RHGameScreenshotCalls::FUN_004da390(SBPicture &) {}
