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

#include "RHScript.h"

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
int RHUnk00452030::Get(int index)
{
    return *(int *)((char *)this + index * 4 + 0x94);
}

// Target 0x004ba7a0 — __thiscall, one stack arg, plain `ret 4`: stores the arg
// to [this+0x164] (see include/RHScript.h). PROVISIONAL identity: named by
// address only. Defined once here so the call in RHScript::SetScrollStatus
// resolves to a local entity.
void RHUnk004ba7a0::Set(int status)
{
    (void)status;
}

bool RHUnk005bd5b0::Unk(bool value)
{
    (void)value;
    return true;
}

void RHUnk004af060::Unk(int direction)
{
    (void)direction;
}

void RHUnk0046bcb0::Unk(int value)
{
    (void)value;
}

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

RHScriptIter RHUnk0046eb30::erase(RHScriptIter position)
{
    return position;
}

void RHUnk0058a3d0::Unk(void *context, int value, void *sequence)
{
    (void)context;
    (void)value;
    (void)sequence;
}

RHUnk00522470::RHUnk00522470() {}
RHUnk00522470::~RHUnk00522470() {}
void RHUnk0047ca50::Unk() {}
void RHUnk005c38b0::Unk(void *actor) { (void)actor; }
void RHUnk004e3660::Unk(bool value) { (void)value; }
void RHUnk00418b80::Unk(bool value) { (void)value; }
void RHUnk00464530::Unk(const SBGeoPoint2D &point) { (void)point; }
RHBonusProjection *RHUnk0057d800::Unk(const SBGeoPoint2D &point)
{
    (void)point;
    return 0;
}

bool RHUnk0057ff00::Unk(void *actor) { return actor != 0; }
void RHUnk00450b60::Unk(int property, int amount) { (void)property; (void)amount; }
void RHUnk00419a40::Unk(int index, bool forbidden) { (void)index; (void)forbidden; }

RHUnk005866a0::RHUnk005866a0(unsigned short level, int command, void *actor)
{
    (void)level;
    (void)command;
    (void)actor;
}
RHUnk005866a0::~RHUnk005866a0() {}
void RHUnk005866a0::Unk00586ed0(int property, int value) { (void)property; (void)value; }
void RHUnk005866a0::Unk00586fd0(int property, float value) { (void)property; (void)value; }
void RHUnk005866a0::Unk00587010(int property, const SBGeoPoint2D &value) { (void)property; (void)value; }
void RHUnk005866a0::Unk00586e00(int property, bool value) { (void)property; (void)value; }

RHUnk005fc3b0::RHUnk005fc3b0() {}
float RHUnk005fc3b0::Unk005fc6a0(float value) { return value; }

RHUnk00584d60::RHUnk00584d60(unsigned short level, int command, void *actor)
{
    (void)level;
    (void)command;
    (void)actor;
}
RHUnk00584d60::~RHUnk00584d60() {}
bool RHUnk0049d4f0::Unk(int value) { return value != 0; }
void RHUnk004af1d0::Unk(bool value) { (void)value; }
void RHUnk0048a970::Unk(int index) { (void)index; }
void RHUnk00413640::Unk(int state, bool flag) { (void)state; (void)flag; }
void RHUnk004169c0::Unk(int state, int value) { (void)state; (void)value; }
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
RHUnk005492a0::RHUnk005492a0(int command, void *actor, int action)
{
    (void)command;
    (void)actor;
    (void)action;
}
RHUnk005492a0::~RHUnk005492a0() {}
RHMessenger *RHUnk00546050() { return 0; }
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
SBGeoPoint2D SBGeoPoint2D::Unk005fc110(const SBGeoPoint2D &other) const { return other; }
float SBGeoPoint2D::Unk005fc6d0(float value) const { return value; }
SBGeoPoint2D SBGeoPoint2D::Unk005fc190(const SBGeoPoint2D &other) const { return other; }
RHScriptIter RHUnk0046eb30::Unk0057c950(RHScriptIter position, const RHUnk00571160Position &) { return position; }
RHScriptNode *RHUnk0046eb30::Unk0059f720(RHScriptNode *next, RHScriptNode *) { return next; }
void RHUnk00560420::Unk(RHUnk00571160Position *) {}
void *RHUnk005b5e00::Unk() { return 0; }
SBGeoPoint2D *RHUnk005b5e00::Unk005bdd30(short) { return 0; }
void RHScriptBatchCalls::Unk004188f0(void *) {}
void RHScriptBatchCalls::Unk00418a80(RHUnk00571160Position, int) {}
void RHScriptBatchCalls::Unk00418bc0() {}
void RHScriptBatchCalls::Unk0046fe00() {}
void RHScriptBatchCalls::Unk0046ec50(int) {}
bool RHScriptBatchCalls::Unk004e3e30(int) { return true; }
void RHScriptBatchCalls::Unk004e3e00(int, int) {}
int RHScriptBatchCalls::Unk004e3e20(int) { return 0; }
void RHScriptBatchCalls::Unk00486f50(void *, bool) {}
void RHScriptBatchCalls::Unk00464630() {}
void RHScriptBatchCalls::Unk0046bd10(int) {}
void RHScriptBatchCalls::Unk0040d980(int) {}
void RHScriptBatchCalls::Unk0048cbc0() {}
void RHScriptBatchCalls::Unk0048c4d0() {}
void RHScriptBatchCalls::Unk0046bcf0(int, int) {}
void RHScriptBatchCalls::Unk0057ec80(void *) {}
void RHScriptBatchCalls::Unk005c2ec0(void *, int, int, void *, int, int, int, int) {}
void RHScriptBatchCalls::Unk0058a940(void *, int, void *) {}
RHUnk005861c0::RHUnk005861c0(unsigned short, int, void *, unsigned short, unsigned short) {}
RHUnk005861c0::~RHUnk005861c0() {}
RHUnk005883a0::RHUnk005883a0(unsigned short, int, void *, int, const SBGeoPoint2D &, int, int, int) {}
RHUnk005883a0::~RHUnk005883a0() {}
void RHScriptRecordWorld::Unk004fc8f0(SBGeoPoint2D &, SBGeoPoint2D &, const SBGeoPoint2D *, unsigned short) {}
RHUnk00613e90 RHScriptRecordWorld::Unk004fbdd0(const RHUnk00571160Position &) { return RHUnk00613e90(); }
RHScriptNode *RHScriptPositionList::Unk004242b0(RHScriptNode *next, RHScriptNode *) { return next; }
void RHScriptPositionList::Unk00588190(RHUnk00571160Position *destination, const RHUnk00571160Position *source) { *destination = *source; }
void RHScriptBatchCalls::Unk0041bd20(int) {}
bool RHScriptBatchCalls::Unk00489e80(void *) { return false; }
void RHScriptBatchCalls::Unk0049d6c0() {}
void RHScriptBatchCalls::Unk0057ebd0(void *) {}
void RHScriptBatchCalls::Unk0048ec00(void *) {}
void RHScriptBatchCalls::Unk004d9330(void *, bool) {}
void RHScriptBatchCalls::Unk0057ff70(float) {}
void RHScriptBatchCalls::Unk00444440(bool) {}
void RHScriptBatchCalls::Unk00455400(void *) {}
void RHScriptBatchCalls::Unk00514670() {}
void RHScriptBatchCalls::Unk004555f0(void *) {}
void RHScriptBatchCalls::Unk004520e0(int, int) {}
RHUnk00549250::RHUnk00549250(int, void *) : RHUnk5490f0(0) {}
RHUnk00549250::~RHUnk00549250() {}
unsigned short RHUnk005ef320::Unk(int, int, int) { return 0; }
void RHScriptBatchCalls::Unk004e3220(int) {}
void RHScriptBatchCalls::Unk0050ed40() {}
void RHScriptBatchCalls::Unk00450be0(int, int) {}
int RHScriptBatchCalls::Unk004ec910(void *, float, float, int) { return 0; }
bool RHScriptBatchCalls::Unk00456cb0(int) { return false; }
void RHScriptBatchCalls::Unk004522e0(void *) {}
RHScriptBatchCalls *RHScriptBatchCalls::Unk004e3cc0() { return this; }
void RHScriptBatchCalls::Unk0054cfa0(void *) {}
void RHScriptBatchCalls::Unk00485220(int, int) {}
unsigned int RHScriptBatchCalls::Unk004baea0() { return 0; }
void RHScriptBatchCalls::Unk0046b9e0() {}
bool RHScriptBatchCalls::Unk0049d560(int) { return false; }
bool RHScriptBatchCalls::Unk00456ce0(void *) { return false; }
void RHScriptBatchCalls::Unk00419fb0(int) {}
void RHScriptBatchCalls::Unk00419fd0(int, int) {}
void RHScriptBatchCalls::Unk0041ac50() {}
RHScriptActionCursor RHScriptActionCursor::operator++(int)
{
    RHScriptActionCursor previous = *this;
    node = node->next;
    return previous;
}
void RHScriptFXArray::Unk004fe450(void **, unsigned int, void *const &) {}
void RHScriptFXArray::Unk005008e0(void **, void **) {}
