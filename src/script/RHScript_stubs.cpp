// Stub definitions for the external symbols RHScript.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the call in RHScript::IsActorCharacter is a direct `call rel32`
// (matching the original shape) instead of an unresolved external. They live in
// a separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBAssert is already defined once, in RHSword_stubs.cpp; this TU just declares
// it (include/SB.h).

#include "SBNullstr.h"
#include "RHScript.h"

void FUN_0053a0b0(int value)
{
    (void)value;
}

RHUnk005490a0Message::RHUnk005490a0Message(int command, int value)
{
    (void)command;
    (void)value;
}

RHUnk005490a0Message::~RHUnk005490a0Message() {}

void RHSound::FUN_005a88a0(void *) {}

class RHUnk0051d0e0
{
public:
    unsigned short Find(int value);
};

unsigned short RHUnk0051d0e0::Find(int value)
{
    (void)value;
    return 0;
}

void FUN_005edae0(RHUnk005ef320 *object, const char *format, int value)
{
    (void)object;
    (void)format;
    (void)value;
}

class RHUnk0057c710
{
public:
    void Ensure();
};

void RHUnk0057c710::Ensure()
{
}

class RHUnk005793e0
{
public:
    void *GetValue();
};

void *RHUnk005793e0::GetValue()
{
    return 0;
}

// FUNCTION: GAME 0x005fc030
SBGeoPoint2D::SBGeoPoint2D()
{
    m_x = 0.0f;
    m_y = 0.0f;
}

// FUNCTION: GAME 0x005fc060
SBGeoPoint2D::SBGeoPoint2D(float x, float y)
{
    m_x = x;
    m_y = y;
}

// Target 0x005709c0 — cdecl, takes void* and returns bool. PROVISIONAL
// identity: named by address only. It stores the actor to the global 0x006c0f4c
// and linearly searches the global pointer array at 0x006c0f34/0x006c0f38 for
// it, publishing index/cursor state to 0x006c0f40/0x006c0f44/0x006c0f45/
// 0x006c0f48. No Windows-side __FILE__/tag/string names it, and no
// function-pointer literal in Game.exe references it, so no Windows-side signal
// binds a name (see include/RHScript.h). Defined once here.
bool RHUnk005709c0(void *actor)
{
    return actor != 0;
}

// Target 0x00585500 — __thiscall, one stack arg, plain `ret 4` (see
// include/RHScript.h). PROVISIONAL identity: named by address only. Defined once
// here so the call in RHScript::AddToSequence resolves to a local entity.
void RHUnk00585500::Unk(void *sequence)
{
    (void)sequence;
}

// Target 0x0041b0e0 — __thiscall, no stack args, plain `ret` (see
// include/RHScript.h). PROVISIONAL identity: named by address only. Defined once
// here so the call in RHScript::RemoveAllSubordinates resolves to a local entity.
void RHUnk0041b0e0::Clear()
{
}

// Target 0x0044cae0 — __thiscall, no stack args, plain `ret` (see
// include/RHScript.h). PROVISIONAL identity: named by address only. Defined once
// here so the call in RHScript::SwitchToAlertPath resolves to a local entity.
void RHUnk0044cae0::Switch()
{
}

// Target 0x004b9f30 — __thiscall getter, no stack args, plain `ret`: returns
// the dword at [this+0x164] (see include/RHScript.h). PROVISIONAL identity:
// named by address only. Defined once here so the tail jump in
// RHScript::GetScrollStatus resolves to a local entity.
// FUNCTION: GAME 0x004b9f30
int RHUnk004b9f30::Get()
{
    return *(int *)((char *)this + 0x164);
}

// Target 0x00452030 — __thiscall, one stack arg, plain `ret 4`: a 6-byte index
// getter reading [this + index*4 + 0x94] (see include/RHScript.h). PROVISIONAL
// identity: named by address only. Defined once here so the call in
// RHScript::GetCustomCampaignValue resolves to a local entity.




void RHUnk0048ce80(int noise, RHUnk00571160Position *position)
{
    (void)noise;
    (void)position;
}

SBGeoPoint2D RHUnk005758d0(const SBGeoPoint2D &point)
{
    return point;
}

RHUnk00582220::RHUnk00582220() {}
RHUnk00582220::~RHUnk00582220() {}

void RHUnk0058a3d0::Unk(void *context, int value, void *sequence)
{
    (void)context;
    (void)value;
    (void)sequence;
}

// FUNCTION: GAME 0x00522470
RHUnk00522470::RHUnk00522470()
{
    ((RHScriptBatchCalls *)this)->FUN_005209b0();
    *(unsigned *)this = 0x67913c;
    *(bool *)((char *)this + 0x14) = false;
    *(int *)((char *)this + 0x18) = 0;
    *(int *)((char *)this + 0xc) = 0x40;
}

// Parked: 0x005224c0, 50.00%; ILT tail jump and coupled callers.
RHUnk00522470::~RHUnk00522470()
{
    *(unsigned *)this = 0x67913c;
    ((RHScriptBatchCalls *)this)->FUN_00520a70();
}
void RHUnk005c38b0::Unk(void *actor) { (void)actor; }
void RHUnk004e3660::Unk(bool value) { (void)value; }
RHBonusProjection *RHUnk0057d800::Unk(const SBGeoPoint2D &point)
{
    (void)point;
    return 0;
}

bool RHUnk0057ff00::Unk(void *actor) { return actor != 0; }
void RHUnk00419a40::Unk(int index, bool forbidden) { (void)index; (void)forbidden; }

RHUnk005866a0::RHUnk005866a0(unsigned short level, int command, void *actor)
{
    (void)level;
    (void)command;
    (void)actor;
}
RHUnk005866a0::~RHUnk005866a0() {}

RHUnk005fc3b0::RHUnk005fc3b0() {}

RHUnk00584d60::RHUnk00584d60(unsigned short level, int command, void *actor)
{
    (void)level;
    (void)command;
    (void)actor;
}
RHUnk00584d60::~RHUnk00584d60() {}
void *RHUnk004e3760::Get() { return (char *)this + 0x42f4; }
void RHUnk005a2450::FUN_005a2450(void *, void *) {}
void RHUnk005a2450::FUN_005a2df0(void *) {}
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, int style, void *target, float distance, void *value)
{
    (void)level;
    (void)command;
    (void)actor;
    (void)style;
    (void)target;
    (void)distance;
    (void)value;
}
RHUnk00588530::~RHUnk00588530() {}
// Parked: 0x005492d0, 50.00%; ILT tail jump and coupled callers.
RHUnk005492a0::~RHUnk005492a0()
{
    *(unsigned *)this = 0x679b6c;
    ((RHScriptBatchCalls *)this)->FUN_00549090();
}
RHMessenger *RHUnk00546050() { return 0; }
RHMessenger *__stdcall RHUnk00546050(RHUnk5490f0 *message) { (void)message; return 0; }
RHUnk00585ea0::RHUnk00585ea0(unsigned short level, int command, void *actor, void *target)
    : RHUnk00584d60(level, command, actor)
{
    (void)target;
}
RHUnk00585ea0::~RHUnk00585ea0() {}
RHScriptIter RHUnk0046eb30::begin() { return RHScriptIter(head->next); }
void RHUnk00574690(void *actor, RHUnk00571160Position *position, void *location)
{
    (void)actor;
    (void)position;
    (void)location;
}
void RHUnk00582640::Unk(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned short endLayer, void *element, float distance, unsigned long flags, float scale)
{
    (void)level;
    (void)actor;
    (void)style;
    (void)start;
    (void)startArea;
    (void)startLayer;
    (void)end;
    (void)endArea;
    (void)endLayer;
    (void)element;
    (void)distance;
    (void)flags;
    (void)scale;
}
SBGeoPoint2D SBGeoPoint2D::Unk005fc190(const SBGeoPoint2D &other) const { return other; }
RHScriptIter RHUnk0046eb30::Unk0057c950(RHScriptIter position, const RHUnk00571160Position &) { return position; }
// FUNCTION: GAME 0x005b5de0
void *RHUnk005b5e00::FUN_005b5de0()
{
    if (*(bool *)((char *)this + 0x194))
        return *(void **)((char *)this + 0x158);
    return *(void **)((char *)this + 0x154);
}
void RHScriptBatchCalls::Unk00418bc0() {}
void RHScriptBatchCalls::Unk00464630() {}
void RHScriptBatchCalls::Unk0048c4d0() {}
void RHScriptBatchCalls::Unk0057ec80(void *) {}
void RHScriptBatchCalls::Unk005c2ec0(void *, int, int, void *, int, int, int, int) {}
void RHScriptBatchCalls::Unk0058a940(void *, int, void *) {}
RHUnk005861c0::RHUnk005861c0(unsigned short, int, void *, unsigned short, unsigned short) {}
RHUnk005861c0::~RHUnk005861c0() {}
RHUnk005883a0::RHUnk005883a0(unsigned short, int, void *, int, const SBGeoPoint2D &, int, int, int) {}
RHUnk005883a0::~RHUnk005883a0() {}
void RHScriptRecordWorld::Unk004fc8f0(SBGeoPoint2D &, SBGeoPoint2D &, const SBGeoPoint2D *, unsigned short) {}
RHUnk00613e90 RHScriptRecordWorld::Unk004fbdd0(const RHUnk00571160Position &) { return RHUnk00613e90(); }
void RHScriptBatchCalls::Unk0041bd20(int) {}
void RHScriptBatchCalls::Unk0049d6c0() {}
void RHScriptBatchCalls::Unk0057ebd0(void *) {}
void RHScriptBatchCalls::Unk0048ec00(void *) {}
void RHScriptBatchCalls::Unk004d9330(void *, bool) {}
void RHScriptBatchCalls::Unk00514670() {}
RHUnk00549250::RHUnk00549250(int, void *) : RHUnk5490f0(0) {}
RHUnk00549250::~RHUnk00549250() {}
void RHScriptBatchCalls::Unk0050ed40() {}
int RHScriptBatchCalls::Unk004ec910(void *, float, float, int) { return 0; }
void RHScriptBatchCalls::Unk004522e0(void *) {}
void RHScriptBatchCalls::Unk0054cfa0(void *) {}
void RHScriptBatchCalls::Unk0046b9e0() {}

float RHScriptBatchCalls::FUN_00489680(void *) { return 0.0f; }
// FUNCTION: GAME 0x0051d540
void RHScriptBatchCalls::FUN_0051d540(int index, int value)
{
    *(int *)((char *)this + index * 8 + 8) = value;
}
RHScriptActionCursor RHScriptActionCursor::operator++(int)
{
    RHScriptActionCursor previous = *this;
    node = node->next;
    return previous;
}

void RHScriptBatchCalls::FUN_0058bbe0(void *, int) {}
void RHScriptBatchCalls::FUN_0050eb80(bool) {}
void RHScriptBatchCalls::FUN_0050eca0(bool) {}
void RHScriptBatchCalls::FUN_00456d20() {}
void RHScriptBatchCalls::FUN_005209b0() {}
void RHScriptBatchCalls::FUN_00520a70() {}
void RHScriptBatchCalls::FUN_00549090() {}

void RHUnk004a5230::FUN_004a5230(bool, bool) {}

void RHScriptSoundStateCalls::FUN_005a7ef0(int) {}
void RHScriptSoundStateCalls::FUN_005a7fb0(int) {}

bool RHScriptAIStateCalls::FUN_00410620(RHScriptStimulusValue) { return false; }
void RHScriptAIStateCalls::FUN_004132d0(int, int, int) {}
void RHScriptAIStateCalls::FUN_00410d30() {}
void RHScriptAIStateCalls::FUN_0043a220(RHMalignityPosition, int, int, int) {}

void RHArtificialIntelligencePathCursor::FUN_00550fa0(void *) {}

RHScriptPropertyInsertResult RHScriptPropertyMap::FUN_005873a0(const RHScriptPropertyPair &)
{
    RHScriptPropertyInsertResult result;
    result.m_node = 0;
    result.m_inserted = false;
    return result;
}
