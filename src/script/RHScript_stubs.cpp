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
#include "RHCampaignCore.h"

struct RHUnkPathRegistry;
extern RHUnkPathRegistry *g_unk0x6c0b9c;


class RHUnk0051d0e0
{
public:
    unsigned short Find(int value);
};

// FUNCTION: GAME 0x0051d0e0
unsigned short RHUnk0051d0e0::Find(int value)
{
    int *first = *(int *volatile *)((char *)this + 8);
    unsigned short count = first == 0 ? 0 : *(int **)((char *)this + 0xc) - first;
    for (unsigned short i = 0; i < count; ++i)
        if ((*(int **)((char *)this + 8))[i] == value)
            return i;
    return 0xffff;
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

extern void **g_unk0x6c0f34;
extern void **g_unk0x6c0f38;
extern void **g_unk0x6c0f40;
extern bool g_unk0x6c0f44;
extern bool g_unk0x6c0f45;
extern int g_unk0x6c0f48;
extern void *g_unk0x6c0f4c;

// FUNCTION: GAME 0x005709c0
bool RHUnk005709c0(void *actor)
{
    if (actor == 0)
        return false;
    g_unk0x6c0f44 = false;
    g_unk0x6c0f4c = actor;
    int count = g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34;
    g_unk0x6c0f45 = true;
    g_unk0x6c0f40 = g_unk0x6c0f34;
    int index = 0;
    for (; index < count; ++index, ++g_unk0x6c0f40) {
        if (*g_unk0x6c0f40 == actor)
            break;
    }
    if (index >= count)
        index = -1;
    g_unk0x6c0f48 = index;
    return index != -1;
}

// Target 0x0041b0e0 — __thiscall, no stack args, plain `ret` (see
// include/RHScript.h). PROVISIONAL identity: named by address only. Defined once
// here so the call in RHScript::RemoveAllSubordinates resolves to a local entity.
void RHUnk0041b0e0::Clear()
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
RHBonusProjection *RHUnk0057d800::Unk(const SBGeoPoint2D &point)
{
    (void)point;
    return 0;
}




void RHUnk00584d60::FUN_00584d30() {}
RHMessenger *__stdcall RHUnk00546050(RHUnk5490f0 *message) { (void)message; return 0; }
// TEMPLATE: GAME 0x00585e90 FOLDED
// ??1RHUnk00585ea0@@QAE@XZ
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
#include <new>

struct RHScriptPositionNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
    RHUnk00571160Position value;
};

DECOMP_SIZE_ASSERT(RHScriptPositionNode, 0x18)

// FUNCTION: GAME 0x0057c950
RHScriptIter RHUnk0046eb30::Unk0057c950(RHScriptIter position, const RHUnk00571160Position &value)
{
    RHScriptNode *previous = position.node->prev;
    RHScriptPositionNode *node = (RHScriptPositionNode *)operator new(sizeof(RHScriptPositionNode));
    node->next = position.node ? position.node : (RHScriptNode *)node;
    node->prev = previous ? previous : (RHScriptNode *)node;
    position.node->prev = (RHScriptNode *)node;
    node->prev->next = (RHScriptNode *)node;
    new ((void *)&node->value) RHUnk00571160Position(value);
    ++count;
    return RHScriptIter((RHScriptNode *)node);
}
// FUNCTION: GAME 0x005b5de0
void *RHUnk005b5e00::FUN_005b5de0()
{
    if (*(bool *)((char *)this + 0x194))
        return *(void **)((char *)this + 0x158);
    return *(void **)((char *)this + 0x154);
}
int RHScriptBatchCalls::Unk005c2ec0(void *, int, int, void *, int, int, int, int) { return -1; }
// TEMPLATE: GAME 0x00585e90 FOLDED
// ??1RHUnk005861c0@@QAE@XZ
RHUnk005861c0::~RHUnk005861c0() {}
RHUnk005883a0::RHUnk005883a0(unsigned short, int, void *, int, const SBGeoPoint2D &, int, int, int) {}
RHUnk005883a0::~RHUnk005883a0() {}
void RHScriptRecordWorld::Unk004fc8f0(SBGeoPoint2D &, SBGeoPoint2D &, const SBGeoPoint2D *, unsigned short) {}
RHUnk00613e90 RHScriptRecordWorld::Unk004fbdd0(const RHUnk00571160Position &) { return RHUnk00613e90(); }
void RHScriptBatchCalls::Unk0041bd20(int) {}
void RHScriptBatchCalls::Unk00514670() {}
void RHScriptBatchCalls::Unk0050ed40() {}
void RHCampaign::FUN_004522e0(RHPCDescription *) {}
void RHScriptBatchCalls::Unk0054cfa0(void *) {}

float RHScriptBatchCalls::FUN_00489680(void *) { return 0.0f; }
RHScriptActionCursor RHScriptActionCursor::operator++(int)
{
    RHScriptActionCursor previous = *this;
    node = node->next;
    return previous;
}

struct RHUnk005209b0Layout
{
    unsigned int m_vptr;
    SBGeoPoint2D m_04;
    int m_c;
    unsigned char m_10;
};

// FUNCTION: GAME 0x005209b0
RHScriptBatchCalls *RHScriptBatchCalls::FUN_005209b0()
{
    RHUnk005209b0Layout *self = (RHUnk005209b0Layout *)this;
    ((SBGeoPoint2D *)&self->m_04)->SBGeoPoint2D::SBGeoPoint2D();
    self->m_vptr = 0x678b58;
    self->m_c = 0;
    self->m_10 = 1;
    return this;
}

void RHScriptBatchCalls::FUN_00520a70() {}
void RHScriptBatchCalls::FUN_00549090() {}

bool RHScriptAIStateCalls::FUN_00410620(RHScriptStimulusValue) { return false; }
void RHScriptAIStateCalls::FUN_0043a220(RHMalignityPosition, int, int, int) {}

// FUNCTION: GAME 0x00550fa0
void RHArtificialIntelligencePathCursor::FUN_00550fa0(void *value)
{
    m_id = ((RHUnk0051d0e0 *)g_unk0x6c0b9c)->Find((int)value);
    m_path = (RHAIPathArray *)value;
    if (value)
    {
        m_current = 0;
        m_forward = 1;
    }
}
RHUnkSequenceOrder::~RHUnkSequenceOrder() {}
