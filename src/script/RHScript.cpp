// RHScript.cpp — translation unit with __FILE__ evidence at 0x00570a90
// ("P:\Robin Hood\RHScript.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x00570a90 -> RHScript::IsActorCharacter(void*)):
//   - TU:        rhscript.cpp (embedded __FILE__ string 0x006b2388).
//   - Class:     RHScript (symbols/oracle-correlation.tsv: rhscript -> class
//                RHScript, 294 methods).
//   - Signature: RHScript::IsActorCharacter(void*) (symbols/mac-RH.txt:3618;
//                zeta-robin.txt:3957 IsActorCharacter__8RHScriptPv).
//   - Signals:
//       * the assert string names the method verbatim:
//         "ACHTUNG : Script error (\"IsActorCharacter\") : invalid actor !"
//         (string 0x006b23a4) — a Windows-side per-function signal;
//       * `if (actor == 0) return false;` then 0x005709c0(actor); if that
//         returns false, SBAssert at line 493 (0x1ed) with the string above;
//       * success returns `(*(unsigned int *)((char *)actor + 4) & 3) == 0`
//         (`mov eax,[esi+4]; and al,3; neg al; sbb eax,eax; inc eax`); the
//         low two bits are the actor type, 0 = character — consistent with the
//         adjacent siblings IsActorObject (`& 3 == 3`) and IsActorCart
//         (`& 3 == 2`);
//       * no `this` (arg is `[esp+4]`), plain `ret` at every exit — emitted as
//         a static member.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHScript.h"
#include "RHElementActorNPC.h"
#include "RHElementActorPC.h"
#include "RHSectorBuilding.h"
#include "RHGame.h"
#include "RHEngine.h"
#include "RHScriptLists.h"
#include <list>
#include <string>
#include <new>
#include <math.h>
#include "RHHumanStatus.h"
#include "RHGenericMap.h"
#include "RHMalignityActorCalls.h"
#include "RHConsoleCampaignCalls.h"
#include "RHGameActionCalls.h"
#include "RHCampaignCore.h"

extern unsigned *g_unk0x006c08a4;
class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;
extern RHUnk0048a970 *g_unk0x6c0b3c;

extern RHEngine *g_pEngine;
class RHUnk0051d0e0
{
public:
    unsigned short Find(int value);
};
struct RHUnk579e80State
{
    char padding[4];
    int *first;
    int *end;
    char padding0c[4];
    int *cursor;
    char valid;
    char searchValid;
    char padding16[2];
    int index;
    int value;
};
bool FUN_005edae0(RHUnk005ef320 *, const char *, ...);
class RHMenuPopupScroll
{
public:
    static void FUN_0053a0b0(int id);
};

extern unsigned char g_unk0x006c06ca;
extern unsigned short g_unk0x006c07e2;
extern unsigned short g_unk0x006c07e4;
extern unsigned short g_unk0x006c07e6;
struct RHUnkPathRegistry;
extern RHUnkPathRegistry *g_unk0x6c0b9c;
class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

DECOMP_SIZE_ASSERT(RHScriptStimulusValue, 0x2c)
DECOMP_SIZE_ASSERT(RHScriptStimulusDispatch, 0x04)
DECOMP_SIZE_ASSERT(RHScriptPropertyValue, 0x0c)
DECOMP_SIZE_ASSERT(RHScriptPropertyPair, 0x10)
DECOMP_SIZE_ASSERT(RHScriptPropertyInsertResult, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005866a0, 0x74)
DECOMP_SIZE_ASSERT(RHMalignityPosition, 0x10)
DECOMP_SIZE_ASSERT(RHUnk004169c0, 0x04)
DECOMP_SIZE_ASSERT(RHArtificialIntelligencePathCursor, 0x0c)

// FUNCTION: GAME 0x0040d980
void RHScriptBatchCalls::Unk0040d980(int state)
{
    RHScriptStimulusValue value;
    value.m_20 = state;
    *(unsigned short *)value.m_00 = 0;
    value.m_type = 0;
    ((RHScriptStimulusDispatch *)this)->v09(value);
}

class RHScriptAIStateDispatch
{
public:
    virtual void v00(int value) = 0;
};

// FUNCTION: GAME 0x00410d30
void RHScriptAIStateCalls::FUN_00410d30()
{
    if (*(bool *)((char *)this + 0x16c))
    {
        *(bool *)((char *)this + 0x16c) = false;
        if (g_unk0x006c06ca < 100)
            ((RHScriptBatchCalls *)this)->Unk0040d980(4);
        else if (g_unk0x006c06ca < 111)
            ((RHScriptAIStateDispatch *)this)->v00(0);
    }
    if (*(bool *)((char *)this + 0x16d))
    {
        *(bool *)((char *)this + 0x16d) = false;
        if (g_unk0x006c06ca < 100)
            ((RHScriptBatchCalls *)this)->Unk0040d980(3);
        else if (g_unk0x006c06ca < 111)
            ((RHScriptAIStateDispatch *)this)->v00(0);
    }
    if (*(bool *)((char *)this + 0x16e))
    {
        *(bool *)((char *)this + 0x16e) = false;
        if (g_unk0x006c06ca < 100)
            ((RHScriptBatchCalls *)this)->Unk0040d980(5);
        else if (g_unk0x006c06ca < 111)
            ((RHScriptAIStateDispatch *)this)->v00(0);
    }
    --g_unk0x006c06ca;
}

// FUNCTION: GAME 0x00413640
void RHUnk00413640::Unk(int state, unsigned char flags)
{
    void *actor = *(void **)((char *)this + 4);
    if ((*(unsigned *)((char *)actor + 4) & 0x1f) == 0x14 &&
        state != *(int *)((char *)this + 0x18))
    {
        int previous = g_unk0x006c07e6 ? 2 : (g_unk0x006c07e4 ? 1 : 0);
        switch (*(int *)((char *)this + 0x18))
        {
        case 0: --g_unk0x006c07e2; break;
        case 1: --g_unk0x006c07e4; break;
        case 2: --g_unk0x006c07e6; break;
        }
        switch (state)
        {
        case 0: ++g_unk0x006c07e2; break;
        case 1: ++g_unk0x006c07e4; break;
        case 2: ++g_unk0x006c07e6; break;
        }
        int current = g_unk0x006c07e6 ? 2 : (g_unk0x006c07e4 ? 1 : 0);
        if (current != previous && !*(bool *)((char *)g_unk0x6c0b3c + 0x5a))
        {
            switch (current)
            {
            case 0:
                if (!*(bool *)((char *)g_pEngine + 0x4aa8))
                {
                    if (flags & 1)
                        ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7fb0(0);
                    else
                        ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(0);
                    break;
                }
                if (flags & 1)
                {
                    ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7fb0(1);
                    break;
                }
            case 1:
                ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(1);
                break;
            case 2:
                ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(2);
                break;
            }
        }
    }
    *(int *)((char *)this + 0x18) = state;
    if (!(flags & 2))
    {
        actor = *(void **)((char *)this + 4);
        if ((*(unsigned *)((char *)actor + 4) & 0x1f) == 0x14 &&
            *(bool *)((char *)actor + 0xa2e) && state == 0)
            *(int *)((char *)actor + 0x658) = 1;
        else
            *(int *)((char *)actor + 0x658) = state;
    }
}

// FUNCTION: GAME 0x004169c0
void RHUnk004169c0::Unk(int state, int value)
{
    switch (state)
    {
    case 1:
        if ((unsigned char)value != 0)
            v04(1, 15);
        else
        {
            RHScriptStimulusValue stimulus;
            stimulus.m_20 = 0x15;
            *(unsigned short *)stimulus.m_00 = 0;
            stimulus.m_type = 0;
            ((RHScriptStimulusDispatch *)this)->v09(stimulus);
        }
        break;
    case 3:
    {
        RHScriptStimulusValue stimulus;
        stimulus.m_20 = 0x47;
        *(unsigned short *)stimulus.m_00 = 0;
        stimulus.m_type = 0;
        ((RHScriptAIStateCalls *)this)->FUN_00410620(stimulus);
        ((RHScriptAIStateCalls *)((char *)*(void **)((char *)this + 4) + 0x6e8))->FUN_0043a220(
            ((RHArtificialIntelligence *)this)->FUN_004165e0(*(void **)((char *)this + 4), true), 300, 0, 0x29a);
        ((RHScriptAIStateCalls *)this)->FUN_00410d30();
        break;
    }
    case 6:
    {
        RHScriptStimulusValue stimulus;
        stimulus.m_20 = 0x47;
        *(unsigned short *)stimulus.m_00 = 0;
        stimulus.m_type = 0;
        ((RHScriptAIStateCalls *)this)->FUN_00410620(stimulus);
        ((RHArtificialIntelligence *)this)->FUN_004132d0(7, 0, 2);
        ((RHScriptAIStateCalls *)this)->FUN_00410d30();
        break;
    }
    }
}

static inline unsigned short RHScriptActorHeading(void *ai)
{
    return *(unsigned short *)((char *)*(void **)((char *)*(void **)((char *)ai + 4) + 0x50) + 0xd8);
}

// FUNCTION: GAME 0x004188f0
bool RHScriptBatchCalls::Unk004188f0(void *path)
{
    RHUnk005fc3b0 direction;
    ((RHArtificialIntelligence *)this)->Unk00410600();
    if (path == 0 || path == (void *)-1)
    {
        *(bool *)((char *)this + 0x70) = false;
        ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->Unk00550f60(0xffff);
        RHUnk00571160Position position;
        ((RHUnk00560420 *)((char *)*(void **)((char *)*(void **)((char *)this + 4) + 0x50) + 4))->Unk(&position);
        RHUnk00571160Position *destination = (RHUnk00571160Position *)((char *)*(void **)((char *)this + 4) + 0x4dc);
        *destination = position;
        direction.Unk005fcd40(RHScriptActorHeading(this), 0.5735764503479004f);
        *(SBGeoVector2D *)((char *)*(void **)((char *)this + 4) + 0x4d4) = direction;
        *(bool *)((char *)this + 0x173) = false;
        if (!*(bool *)((char *)this + 0x1c4))
        {
            switch (*(int *)((char *)this + 0xc))
            {
            case 1:
            {
                RHScriptStimulusValue stimulus;
                stimulus.m_20 = 0x15;
                *(unsigned short *)stimulus.m_00 = 0;
                stimulus.m_type = 0;
                ((RHScriptStimulusDispatch *)this)->v09(stimulus);
                break;
            }
            }
        }
        *(bool *)((char *)this + 0x170) = false;
        *(bool *)((char *)this + 0x16f) = path != 0;
    }
    else
    {
        *(bool *)((char *)this + 0x70) = true;
        ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->FUN_00550fa0(path);
        *(bool *)((char *)this + 0x16f) = false;
        if (!*(bool *)((char *)this + 0x1c4))
        {
            switch (*(int *)((char *)this + 0xc))
            {
            case 1:
            {
                RHScriptStimulusValue stimulus;
                stimulus.m_20 = 0x15;
                *(unsigned short *)stimulus.m_00 = 0;
                stimulus.m_type = 0;
                ((RHScriptStimulusDispatch *)this)->v09(stimulus);
                break;
            }
            }
        }
    }
    return true;
}

struct RHScriptActorFacing
{
    undefined m_00[0x4d4];
    RHUnk005fc3b0 m_4d4;
};

static inline RHScriptStimulusDispatch *RHScriptDispatcher(void *ai)
{
    return (RHScriptStimulusDispatch *)ai;
}

static inline RHScriptActorFacing *RHScriptFacingActor(void *ai)
{
    return *(RHScriptActorFacing **)((char *)ai + 4);
}

// FUNCTION: GAME 0x00418a80
bool RHScriptBatchCalls::Unk00418a80(RHUnk00571160Position position, int facing)
{
    RHUnk005fc3b0 direction;
    ((RHArtificialIntelligence *)this)->Unk00410600();
    ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->Unk00550f60(0xffff);
    *(bool *)((char *)this + 0x70) = false;
    *(RHUnk00571160Position *)((char *)*(void **)((char *)this + 4) + 0x4dc) = position;
    direction.Unk005fcd40((unsigned short)facing, 0.5735764503479004f);
    RHScriptFacingActor(this)->m_4d4.FUN_005fc430(direction);
    *(bool *)((char *)this + 0x173) = false;
    *(bool *)((char *)this + 0x70) = false;
    *(bool *)((char *)this + 0x16f) = false;
    *(bool *)((char *)this + 0x170) = false;
    if (!*(bool *)((char *)this + 0x1c4))
    {
        switch (*(int *)((char *)this + 0xc))
        {
        case 1:
        {
            RHScriptStimulusValue stimulus;
            stimulus.m_20 = 0x15;
            *(unsigned short *)stimulus.m_00 = 0;
            stimulus.m_type = 0;
            RHScriptDispatcher(this)->v09(stimulus);
            break;
        }
        }
    }
    return true;
}

// FUNCTION: GAME 0x00418b80
void RHUnk00418b80::Unk(bool value)
{
    *(bool *)((char *)this + 0x1c4) = true;
    *(bool *)((char *)this + 0x1c5) = value;
    if (value)
        *(volatile bool *)((char *)this + 0x1c5) = value;
    void *actor = *(void **)((char *)this + 4);
    if (((RHUnk0046bd20 *)actor)->FUN_0046bd20() != 0x7f)
        ((RHUnk0046bcb0 *)*(void **)((char *)this + 4))->Unk(8);
    ((RHArtificialIntelligence *)this)->Unk00410600();
}

// FUNCTION: GAME 0x00419fd0
void RHScriptBatchCalls::Unk00419fd0(int value, int duration)
{
    Unk00419fb0(value);
    *(unsigned *)((char *)this + 0x264) = *g_unk0x006c08a4 + (unsigned short)duration;
    *(bool *)((char *)this + 0x268) = true;
}

// FUNCTION: GAME 0x004242b0
RHScriptNode *RHScriptPositionList::Unk004242b0(RHScriptNode *next, RHScriptNode *previous)
{
    RHScriptNode *node = (RHScriptNode *)operator new(0x18);
    node->next = next ? next : node;
    node->prev = previous ? previous : node;
    return node;
}

// Parked at 0.6415: unannotated park from the asymmetric-comparator era; residual scheduling/registers.
// STUB: GAME 0x00444440
void RHScriptBatchCalls::Unk00444440(bool attentive)
{
    *(bool *)((char *)this + 0x346) = attentive;
    if (attentive)
    {
        int offset = (*(int **)this)[1];
        ((RHUnk004a5230 *)*(void **)((char *)this + offset + 4))->FUN_004a5230(true, false);
        offset = (*(int **)this)[1];
        RHUnk00413640 *base = (RHUnk00413640 *)((char *)this + offset);
        void *actor = *(void **)((char *)base + 4);
        if (*(int *)((char *)actor + 0x658) == 0 &&
            *(unsigned *)((char *)g_pEngine + 0x4a94) > 1)
            base->Unk(1, false);
    }
}

// LIBRARY: GAME 0x0044f580
// wmemmove

// FUNCTION: GAME 0x00450b60
void RHUnk00450b60::Unk(int property, int amount)
{
    RHScriptBatchCalls *engine = (RHScriptBatchCalls *)g_pEngine;
    *(int *)((char *)this + property * 4 + 0x94) += amount;
    switch (property)
    {
    case 1:
    {
        int &money = *(int *)((char *)engine->Unk004e3cc0() + 4);
        money += amount;
        if (amount > 0 && *(unsigned *)((char *)engine + 0x4a94) > 0)
            (*(RHSound **)((char *)engine + 0x45e0))->PlayJingle(3);
        ((RHScriptBatchCalls *)this)->FUN_00456d20();
        break;
    }
    case 2:
    {
        int &money = *(int *)((char *)engine->Unk004e3cc0() + 0x24);
        money += amount;
        break;
    }
    }
}

// FUNCTION: GAME 0x00450be0
void RHScriptBatchCalls::Unk00450be0(int property, int value)
{
    *(int *)((char *)this + property * 4 + 0x94) -= value;
    if (property == 1)
        FUN_00456d20();
}

// FUNCTION: GAME 0x00452030
int RHUnk00452030::Get(int index)
{
    return *(int *)((char *)this + index * 4 + 0x94);
}

// FUNCTION: GAME 0x004520e0
void RHScriptBatchCalls::Unk004520e0(int index, int value)
{
    if (index == 1 && value > *(int *)((char *)this + 0x98))
    {
        char *engine = (char *)g_pEngine;
        if (*(unsigned *)(engine + 0x4a94) > 0)
            (*(RHSound **)(engine + 0x45e0))->PlayJingle(3);
    }
    *(int *)((char *)this + index * 4 + 0x94) = value;
    if (index == 1)
        FUN_00456d20();
}

// FUNCTION: GAME 0x00456ce0
bool RHScriptBatchCalls::Unk00456ce0(void *type)
{
    void **first = *(void ***)((char *)this + 0x118);
    void **last = *(void ***)((char *)this + 0x11c);
    for (; first != last; ++first)
    {
        if (*(void **)((char *)*first + 0x40) == type && !*(bool *)((char *)*first + 0x44))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0046bcb0
void RHUnk0046bcb0::Unk(int value)
{
    RHUnk0046bcb0Dispatch *order = *(RHUnk0046bcb0Dispatch **)((char *)this + 0x130);
    if (order && order != *(RHUnk0046bcb0Dispatch **)((char *)this + 0x138))
        order->v04(value);
    ((RHScriptBatchCalls *)g_unk0x6c1040)->FUN_0058bbe0(this, value);
}

// FUNCTION: GAME 0x0046bcf0
void RHScriptBatchCalls::Unk0046bcf0(int state, int value)
{
    ((RHUnk00570e70Vtbl *)this)->v17(state);
    *(int *)((char *)this + 0x144) = value;
}

// FUNCTION: GAME 0x0046bd10
void RHScriptBatchCalls::Unk0046bd10(int state)
{
    *(int *)((char *)this + 0x144) = state;
}

// FUNCTION: GAME 0x00485200
void RHScriptBatchCalls::Unk00485200(int index, int amount)
{
    (*(RHHumanStatus **)((char *)this + 0x1c4))->FUN_0051d4e0(index, amount);
}

// FUNCTION: GAME 0x00485220
void RHScriptBatchCalls::Unk00485220(int index, int value)
{
    (*(RHHumanStatus **)((char *)this + 0x1c4))->FUN_0051d540(index, value);
}

// FUNCTION: GAME 0x00486f50
void RHScriptBatchCalls::Unk00486f50(void *, bool)
{
}

// FUNCTION: GAME 0x00489e80
bool RHScriptBatchCalls::Unk00489e80(void *target)
{
    return FUN_00489680(target) > 0.0f;
}

// FUNCTION: GAME 0x0048a970
void RHUnk0048a970::Unk(int)
{
}

// FUNCTION: GAME 0x0049d4f0
bool RHUnk0049d4f0::Unk(int value)
{
    int *entry = *(int **)((char *)this + 0x5fc);
    unsigned int index = 0;
    entry += 0x48 / 4;
    for (; index < 3; ++index, ++entry)
    {
        if (*entry == value)
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0049d560
bool RHScriptBatchCalls::Unk0049d560(int action)
{
    int *entry = *(int **)((char *)this + 0x5fc);
    bool found = false;
    unsigned int index = 0;
    entry += 0x5c / 4;
    for (; index < 4; ++index, ++entry)
    {
        if (*entry == action)
        {
            found = true;
            break;
        }
    }
    return found;
}

// SIZE 0x10
struct RHUnk004af1d0Children
{
    undefined m_00[4]; // 0x00
    void **first; // 0x04
    void **last; // 0x08
    void **end; // 0x0c
    unsigned int size() const { return first == 0 ? 0 : last - first; }
    void *operator[](unsigned int index) { return *(first + index); }
};

// Parked: index/element registers swap (EDX/EAX vs EAX/EDX); effective only.
// STUB: GAME 0x004af1d0
void RHUnk004af1d0::Unk(bool value)
{
    *(bool *)((char *)this + 0x12) = value;
    RHUnk004af1d0Children &children = *(RHUnk004af1d0Children *)((char *)this + 0xac);
    for (unsigned int index = 0; index < children.size(); ++index)
        *(bool *)((char *)children[index] + 0x12) = value;
}

// FUNCTION: GAME 0x004baea0
unsigned int RHScriptBatchCalls::Unk004baea0()
{
    return *(unsigned int *)((char *)this + 0x168);
}

// FUNCTION: GAME 0x004e3220
void RHScriptBatchCalls::Unk004e3220(int value)
{
    *(bool *)((char *)this + 0x4a50) = true;
    *(char *)((char *)this + 0x4a51) = (char)value;
    if ((char)value == 0)
    {
        ((RHGame *)g_unk0x6c0b3c)->FUN_0050eca0(true);
        ((RHGame *)g_unk0x6c0b3c)->FUN_0050eb80(false);
    }
}

// FUNCTION: GAME 0x004e3cc0
RHScriptBatchCalls *RHScriptBatchCalls::Unk004e3cc0()
{
    return (RHScriptBatchCalls *)((char *)this + 0x4a5c);
}

// FUNCTION: GAME 0x004e3e00
void RHScriptBatchCalls::Unk004e3e00(int index, int value)
{
    (*(int **)((char *)this + 0x4c5c))[index] = value;
}

// FUNCTION: GAME 0x004e3e20
int RHScriptBatchCalls::Unk004e3e20(int index)
{
    return (*(int **)((char *)this + 0x4c5c))[index];
}

// FUNCTION: GAME 0x004e3e30
bool RHScriptBatchCalls::Unk004e3e30(int index)
{
    return index >= 0 && index < (*(int **)((char *)this + 0x4c5c) == 0 ? 0 :
        *(int **)((char *)this + 0x4c60) - *(int **)((char *)this + 0x4c5c));
}

// FUNCTION: GAME 0x00560420
void RHUnk00560420::Unk(RHUnk00571160Position *position)
{
    position->x = *(float *)((char *)this + 0x20);
    position->y = *(float *)((char *)this + 0x24);
    position->area = *(void **)((char *)this + 0xdc);
    position->layer = *(short *)((char *)this + 0xda);
}

std::wstring FUN_005e23d0(unsigned long id);

void operator delete(void *pointer) throw();

// The 4-byte global passed to the 0x00585500 callee by AddToSequence (the
// "current sequence" pointer; original 0x006c0f78). PROVISIONAL name.
// GLOBAL: GAME 0x006c0f78
void *g_unk0x6c0f78;

// Singleton object pointer loaded by the campaign-value methods
// (GetCustomCampaignValue 0x00579430, SetCustomCampaignValue 0x005795c0 and
// Fun_00579690) — original 0x006c07fc. PROVISIONAL name; see include/RHScript.h.
// GLOBAL: GAME 0x006c07fc
RHUnk00452030 *g_unk0x6c07fc;

#include "RHTitbitsCore.h"

// GLOBAL: GAME 0x006c0fa4
unsigned short g_unk0x6c0fa4;
// GLOBAL: GAME 0x006c0fa8
char *g_unk0x6c0fa8;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class RHEngine;
extern RHEngine *g_pEngine;
// GLOBAL: GAME 0x006c0f34
void **g_unk0x6c0f34;
// GLOBAL: GAME 0x006c0f38
void **g_unk0x6c0f38;
class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;
// GLOBAL: GAME 0x006c0f50
RHUnk0046eb30 g_unk0x6c0f50;
// GLOBAL: GAME 0x006c0fb0
RHUnk0046eb30 g_unk0x6c0fb0;
// GLOBAL: GAME 0x006c0fe8
RHUnkList g_unk0x6c0fe8;
// GLOBAL: GAME 0x006c10e8
RHTitbits *g_unk0x6c10e8;
// GLOBAL: GAME 0x006c0f7c
void *g_unk0x6c0f7c;
// GLOBAL: GAME 0x006c0b3c
RHUnk0048a970 *g_unk0x6c0b3c;
// GLOBAL: GAME 0x006c0f40
void **g_unk0x6c0f40;
// GLOBAL: GAME 0x006c0f44
bool g_unk0x6c0f44;
// GLOBAL: GAME 0x006c0f45
bool g_unk0x6c0f45;
// GLOBAL: GAME 0x006c0f48
int g_unk0x6c0f48;
// GLOBAL: GAME 0x006c0f4c
void *g_unk0x6c0f4c;

// GLOBAL: GAME 0x006c11d0
RHUnk005ef320 *g_unk0x6c11d0;

// GLOBAL: GAME 0x006c05c4
void *g_unk0x6c05c4;

inline int RHScriptFindActor(void *actor)
{
    g_unk0x6c0f44 = false;
    g_unk0x6c0f4c = actor;
    int count = g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34;
    g_unk0x6c0f45 = true;
    g_unk0x6c0f40 = g_unk0x6c0f34;
    int index = 0;
    for (; index < count; ++index, ++g_unk0x6c0f40)
    {
        if (*g_unk0x6c0f40 == actor)
            break;
    }
    if (index >= count)
        index = -1;
    return index;
}

#define RH_SCRIPT_ACTION_CASES \
    case 0: type = 1; break; \
    case 1: type = 2; break; \
    case 2: type = 3; break; \
    case 3: type = 4; break; \
    case 4: type = 5; break; \
    case 5: type = 6; break; \
    case 6: type = 7; break; \
    case 7: type = 8; break; \
    case 8: type = 9; break; \
    case 9: type = 10; break; \
    case 10: type = 11; break; \
    case 11: type = 12; break; \
    case 12: type = 13; break; \
    case 13: type = 14; break; \
    case 14: type = 15; break; \
    case 15: type = 16; break; \
    case 16: type = 17; break; \
    case 17: type = 18; break; \
    case 18: type = 19; break; \
    case 19: type = 20; break; \
    case 20: type = 21; break; \
    case 21: type = 22; break; \
    case 23: type = 23; break; \
    case 24: type = 24; break; \
    case 25: type = 25; break; \
    case 26: type = 26; break; \
    case 27: type = 27; break; \
    case 28: type = 28; break; \
    case 29: type = 29; break;

struct RHScriptPCArray
{
    char padding[0x493c];
    void **first;
    void **last;
    unsigned char Count() { return first == 0 ? 0 : last - first; }
    void *Get(unsigned char index) { return first[index]; }
};

struct RHScriptActorKind
{
    unsigned value : 5;
};

struct RHScriptNPCArray
{
    char padding[0x495c];
    void **first;
    void **last;
    unsigned Count()
    {
        unsigned result;
        if (first == 0)
            result = 0;
        else
            result = last - first;
        return result;
    }
};

struct RHScriptPCType
{
    char padding[8];
    char *text;
    const char *c_str()
    {
        char *value = *(char *volatile *)&text;
        if (value != 0)
            return value;
        return "";
    }
};

struct RHScriptSectorActors
{
    char padding[0xcc];
    RHScriptIndexedList actors;
};

struct RHScriptSoundArray
{
    int allocator;
    void **first;
    void **last;
    void **end;
    void **cursor;
    bool valid;
    bool searchValid;
    char padding[2];
    int index;
    void *value;
    int Find(void *source)
    {
        valid = false;
        value = source;
        int size = first == 0 ? 0 : last - first;
        cursor = first;
        searchValid = true;
        int i = 0;
        for (; i < size; ++i, ++cursor)
            if (*cursor == source) break;
        index = i < size ? i : -1;
        return index;
    }
};

// GLOBAL: GAME 0x006c0fe0
void *g_unk0x006c0fe0;

// FUNCTION: GAME 0x00570800
RHScript::RHScript()
{
    m_vptr = 0x00679bec;
    g_unk0x006c0fe0 = 0;
    g_unk0x6c0fa4 = 0;
    g_unk0x6c0f78 = 0;
}

// FUNCTION: GAME 0x00570820
void *RHScript::FUN_00570820(unsigned flags)
{
    this->~RHScript();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00570840
RHScript::~RHScript()
{
    m_vptr = 0x00679bec;
}

void EmitRHScriptLifetime(void *storage)
{
    RHScript *script = (RHScript *)storage;
    script->RHScript::RHScript();
    script->FUN_00570820(0);
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00570a30
void FUN_00570a30(int value) { *(int *)(g_unk0x6c0fa8 + 0x4a58) = value; }

// FUNCTION: GAME 0x00570a50
bool FUN_00570a50(int value) { return value == 0; }

// FUNCTION: GAME 0x00570a60
bool FUN_00570a60(int first, int second) { return first == second; }

struct RHScriptKind2 { unsigned value : 2; };

// FUNCTION: GAME 0x00570a70
bool FUN_00570a70(int value)
{
    return value != 0 && ((RHScriptKind2 *)(value + 4))->value == 1;
}
}

// FUNCTION: GAME 0x00570a90
bool RHScript::IsActorCharacter(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 // STRING: GAME 0x6b2388
                 "P:\\Robin Hood\\RHScript.cpp",
                 493,
                 // STRING: GAME 0x6b23a4
                 "ACHTUNG : Script error (\"IsActorCharacter\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 3) == 0;
}

// FUNCTION: GAME 0x00570ae0
bool RHScript::IsActorObject(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 520,
                 // STRING: GAME 0x6b23e4
                 "ACHTUNG : Script error (\"IsActorObject\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 3) == 3;
}

// FUNCTION: GAME 0x00570b30
bool RHScript::IsActorCart(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 547,
                 // STRING: GAME 0x6b2420
                 "ACHTUNG : Script error (\"IsActorCart\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 3) == 2;
}

// FUNCTION: GAME 0x00570b80
bool RHScript::IsActorPC(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 573,
                 // STRING: GAME 0x6b245c
                 "ACHTUNG : Script error (\"IsActorPC\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 0xf) == 0xc;
}

// FUNCTION: GAME 0x00570bd0
bool RHScript::IsActorAnimal(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 595,
                 // STRING: GAME 0x6b2494
                 "ACHTUNG : Script error (\"IsActorAnimal\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 0x7) == 0;
}

// FUNCTION: GAME 0x00570c10
bool RHScript::IsActorNPC(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 622,
                 // STRING: GAME 0x6b24d0
                 "ACHTUNG : Script error (\"IsActorNPC\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 0xf) == 4;
}

// FUNCTION: GAME 0x00570c60
bool RHScript::IsActorSoldier(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 649,
                 // STRING: GAME 0x6b2508
                 "ACHTUNG : Script error (\"IsActorSoldier\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 0x1f) == 0x14;
}

// FUNCTION: GAME 0x00570cb0
bool RHScript::IsActorCivilian(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 676,
                 // STRING: GAME 0x6b2544
                 "ACHTUNG : Script error (\"IsActorCivilian\") : invalid actor !");
        return false;
    }

    return (*(unsigned int *)((char *)actor + 4) & 0x1f) == 4;
}

// FUNCTION: GAME 0x00570d00
char RHScript::IsAnimationActive(void *actor)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 3) != 1))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 698,
                 // STRING: GAME 0x6b2584
                 "ACHTUNG : Script error (\"IsAnimationActive\") : invalid animation !");
        return 0;
    }

    return *(char *)((char *)actor + 0x12);
}

// FUNCTION: GAME 0x00570d40
char RHScript::IsActorActive(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 720,
                 // STRING: GAME 0x6b25c8
                 "ACHTUNG : Script error (\"IsActorActive\") : invalid animation !");
        return 0;
    }

    return *(char *)((char *)actor + 0x12);
}

// FUNCTION: GAME 0x00570d80
bool RHScript::SetAnimationState(void *actor, bool state)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 3) != 1))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 742,
                 // STRING: GAME 0x6b2608
                 "ACHTUNG : Script error (\"SetAnimationState\") : invalid animation !");
        return false;
    }

    *(char *)((char *)actor + 0x12) = (char)state;
    return true;
}

// FUNCTION: GAME 0x00570dd0
bool RHScript::FUN_00570dd0(void *actor)
{
    if (RHUnk005709c0(actor) &&
        ((*(unsigned int *)((char *)actor + 4) & 3) == 1))
    {
        ((RHUnk005bd5b0 *)*(void **)((char *)actor + 0x50))->Unk(0);
        return true;
    }

    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 766,
             "ACHTUNG : Script error (\"SetAnimationState\") : invalid animation !");
    return false;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00570e20
bool FUN_00570e20(int value) { return *(bool *)value; }
}

// FUNCTION: GAME 0x00570e70
bool RHScript::UnBlip(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 844,
                 // STRING: GAME 0x6b264c
                 "ACHTUNG : Script error (\"UnBlip\") : invalid actor !");
        return false;
    }

    if (((RHUnk00570e70Actor *)actor)->m_blip)
    {
        ((RHUnk00570e70Vtbl *)actor)->v13();
        return true;
    }

    return false;
}

// FUNCTION: GAME 0x00570ec0
bool RHScript::IsUnblipped(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 864,
                 // STRING: GAME 0x6b2680
                 "ACHTUNG : Script error (\"IsUnblipped\") : invalid actor !");
        return false;
    }

    return *(unsigned char *)((char *)actor + 8) == 0;
}

// FUNCTION: GAME 0x00570f00
bool RHScript::Start()
{
    if (g_unk0x6c0f78 == 0)
    {
        g_unk0x6c0f78 = new RHUnk00582220;
        g_unk0x6c0fa4 = 1;
        RHScriptNode *head = g_unk0x6c0fb0.head;
        RHScriptNode *node = head->next;
        while (node != head)
        {
            RHScriptNode *removed = node;
            node = node->next;
            removed->prev->next = removed->next;
            removed->next->prev = removed->prev;
            ::operator delete(removed);
            --g_unk0x6c0fb0.count;
        }
        g_unk0x6c0fb0.valid = true;
        head = g_unk0x6c0f50.head;
        node = head->next;
        while (node != head)
        {
            RHScriptNode *removed = node;
            node = node->next;
            removed->prev->next = removed->next;
            removed->next->prev = removed->prev;
            ::operator delete(removed);
            --g_unk0x6c0f50.count;
        }
        g_unk0x6c0f50.valid = true;
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 896,
             // STRING: GAME 0x006b26bc
             "Script error in Start: you cannont start a new record sequence while another is still being recorded.");
    return false;
}

// FUNCTION: GAME 0x00571020
bool RHScript::Thanx()
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 920,
                 // STRING: GAME 0x006b2758
                 "Script Error in Thanx: End a sequence recording without ever started it.");
        return false;
    }
    void *sequence = g_unk0x6c0f78;
    g_unk0x6c0fa4 = 0;
    g_unk0x6c0f78 = 0;
    RHScriptNode *head = g_unk0x6c0fb0.head;
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *removed = node;
        node = node->next;
        g_unk0x6c0fb0.erase(RHScriptIter(removed));
    }
    g_unk0x6c0fb0.valid = true;
    head = g_unk0x6c0f50.head;
    node = head->next;
    while (node != head)
    {
        RHScriptNode *removed = node;
        node = node->next;
        g_unk0x6c0f50.erase(RHScriptIter(removed));
    }
    g_unk0x6c0f50.valid = true;
    if (*(unsigned short *)((char *)sequence + 0x10) > 0)
    {
        ((RHUnk0058a3d0 *)g_unk0x6c1040)->Unk("", 0, sequence);
    }
    else
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 937,
                 // STRING: GAME 0x006b2724
                 "Script Error: Trying to launch an empty sequence.");
        delete (RHScriptSequenceVtable *)sequence;
    }
    return true;
}

// FUNCTION: GAME 0x00571100
int RHScript::Then()
{
    if (g_unk0x6c0fa4 < 1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 961,
                 // STRING: GAME 0x006b27a4
                 "Trying to increment the sequence level without starting a sequence");
        return 0;
    }

    if (*(unsigned short *)((char *)g_unk0x6c0f78 + 0x10) != 0 &&
        *(unsigned short *)(*(char **)(*(char **)(*(char **)((char *)g_unk0x6c0f78 + 0xc) + 4) + 8) + 0x14) == g_unk0x6c0fa4)
    {
        ++g_unk0x6c0fa4;
    }
    return g_unk0x6c0fa4;
}

// FUNCTION: GAME 0x00571160
void RHScript::MakeNoise(void *location, int noise)
{
    unsigned int type;
    switch (noise)
    {
    case 0:
        type = 11;
        break;
    case 1:
        type = 12;
        break;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1004,
                 // STRING: GAME 0x006b2820
                  "Illegal noise ID %u", noise);
        break;
    }

    if (!location)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1012,
                 // STRING: GAME 0x006b27e8
                 "VERBOTEN ! Script error : MakeNoise on NULL-location !");
        return;
    }

    RHUnk00571160Position position;
    position.x = *(float *)((char *)location + 4);
    position.y = *(float *)((char *)location + 8);
    position.area = *(void **)((char *)location + 0x24);
    position.layer = *(short *)((char *)location + 0x20);
    RHUnk0048ce80(type, &position);
}

// FUNCTION: GAME 0x00571200
bool RHScript::SetZoomLevel(float zoom)
{
    if (zoom != 0.5f && zoom != 1.0f && zoom != 2.0f)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1040,
                 // STRING: GAME 0x006b2834
                 "Script Error: Wanted zoom level is incorrect");
        return false;
    }
    *(float *)(g_unk0x6c0fa8 + 0x4764) = zoom;
    return true;
}

// FUNCTION: GAME 0x00571270
bool RHScript::ScrollCameraTo(void *location)
{
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1067,
                 // STRING: GAME 0x006b2864
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    SBGeoPoint2D &point = *(SBGeoPoint2D *)((char *)location + 4);
    *(SBGeoPoint2D *)(g_unk0x6c0fa8 + 0x4750) = point;
    *(SBGeoPoint2D *)(g_unk0x6c0fa8 + 0x4748) = RHUnk005758d0(point);
    *(float *)(g_unk0x6c0fa8 + 0x45b0) = 2.0f;
    return true;
}

// FUNCTION: GAME 0x00571330
bool RHScript::ScrollCameraSlowlyTo(void *location, float speed)
{
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1097,
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    SBGeoPoint2D &point = *(SBGeoPoint2D *)((char *)location + 4);
    *(SBGeoPoint2D *)(g_unk0x6c0fa8 + 0x4750) = point;
    *(SBGeoPoint2D *)(g_unk0x6c0fa8 + 0x4748) = RHUnk005758d0(point);
    *(float *)(g_unk0x6c0fa8 + 0x45b0) = speed;
    return true;
}

// FUNCTION: GAME 0x005713f0
bool RHScript::JumpCameraTo(void *location)
{
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1127,
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    *(SBGeoPoint2D *)(g_unk0x6c0fa8 + 0x4738) = RHUnk005758d0(*(SBGeoPoint2D *)((char *)location + 4));
    *(char *)(g_unk0x6c0fa8 + 0x48d0) = 0;
    return true;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x005714d0
int FUN_005714d0()
{
    void **first = g_unk0x6c0f34;
    return first == 0 ? 0 : g_unk0x6c0f38 - first;
}
}

// FUNCTION: GAME 0x005714f0
void *RHScript::GetLocationScript(int index)
{
    if (index == -1)
    {
        return 0;
    }
    char *location = (*(char ***)(g_unk0x6c0fa8 + 0x4200))[(unsigned short)index];
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1209,
                 // STRING: GAME 0x006b28ac
                 "Script Error: Trying to acces an invalid location ID.");
        return 0;
    }
    switch (*(int *)(location + 4))
    {
    case 0:
        return location - 0x14;
    case 1:
        return location - 0x20;
    case 2:
        return location - 0xb8;
    }
    return location;
}

// FUNCTION: GAME 0x00571550
int RHScript::GetMovementStyle(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1246,
                 // STRING: GAME 0x006b28e4
                 "ACHTUNG : Script error (\"GetMovementStyle\") : invalid actor !");
        return 0;
    }
    return *(int *)((char *)actor + 0x144) == 3;
}

// Parked: narrowing into a separate value adds EDI; count/index register allocation remains different.
// STUB: GAME 0x00571590
void *RHScript::GetActorScript(int index)
{
    void **first = g_unk0x6c0f34;
    int count = first == 0 ? 0 : g_unk0x6c0f38 - first;
    char *engine = (char *)g_pEngine;
    if (index == -1)
    {
        return 0;
    }
    count = (unsigned short)count;
    if (index < count)
    {
        return first[index];
    }
    first = *(void ***)(engine + 0x497c);
    int extra = first == 0 ? 0 : *(void ***)(engine + 0x4980) - first;
    if (index < count + extra)
    {
        return first[index - count];
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1293,
             // STRING: GAME 0x006b2924
             "Script Error: Trying to access an invalid actor ID.");
    return 0;
}

// FUNCTION: GAME 0x00571610
void *RHScript::GetActorForBeamMe(unsigned int index)
{
    char *engine = (char *)g_pEngine;
    if (index >= *(unsigned int *)(engine + 0x4a4c))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1309,
                 // STRING: GAME 0x006b2958
                 "Script Error : Trying to access non existing beam-me !");
        return 0;
    }
    void **first = *(void **volatile *)(engine + 0x493c);
    unsigned int count = (unsigned char)(first == 0 ? 0 : *(void ***)(engine + 0x4940) - first);
    for (unsigned int i = 0; i < count; ++i)
    {
        void *actor = (*(void ***)(engine + 0x493c))[(unsigned char)i];
        if (*(unsigned short *)((char *)actor + 0x4ea) == index)
        {
            return actor;
        }
    }
    return 0;
}

// FUNCTION: GAME 0x005716a0
void *RHScript::GetDoorScript(int index)
{
    void **first = *(void **volatile *)((char *)g_unk0x6c0a9c + 0x4084);
    int count = first == 0 ? 0 : *(void ***)((char *)g_unk0x6c0a9c + 0x4088) - first;
    if (index == -1)
    {
        return 0;
    }
    if (index >= 0 && index < (unsigned short)count)
    {
        return (*(void ***)((char *)g_unk0x6c0a9c + 0x4084))[index];
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1353,
             // STRING: GAME 0x006b2990
             "Script Error: Trying to acces an invalid gate ID.");
    return 0;
}

// FUNCTION: GAME 0x00571700
void *RHScript::GetPatchScript(int index)
{
    void **first = *(void **volatile *)((char *)g_unk0x6c0a9c + 0x40a4);
    int count = first == 0 ? 0 : *(void ***)((char *)g_unk0x6c0a9c + 0x40a8) - first;
    if (index == -1)
    {
        return 0;
    }
    if (index >= 0 && index < (unsigned short)count)
    {
        return (*(void ***)((char *)g_unk0x6c0a9c + 0x40a4))[index];
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1395,
             // STRING: GAME 0x006b29c4
             "Script Error: Trying to acces an invalid Patch ID.");
    return 0;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00571760
int FUN_00571760(int index)
{
    return (*(int **)((char *)g_unk0x6c0a9c + 0x40c4))[index];
}

// FUNCTION: GAME 0x00571780
int FUN_00571780(int index)
{
    if (index == -1)
        return 0;
    return (*(int **)((char *)g_unk0x6c0b9c + 8))[(unsigned short)index];
}
}

// FUNCTION: GAME 0x005717a0
void *RHScript::GetActorLocation(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1461,
                 // STRING: GAME 0x006b29f8
                 "ACHTUNG : Script error (\"GetActorLocation\") : invalid actor !");
        return 0;
    }
    RHUnk00522470 *location = new RHUnk00522470;
    g_unk0x6c0fe8.insert(RHUnkIter(g_unk0x6c0fe8.m_4), (RHOrder *const &)location);
    g_unk0x6c0fe8.m_flag10 = 1;
    SBGeoPoint2D point;
    point = *(SBGeoPoint2D *)(*(char **)((char *)actor + 0x50) + 0x24);
    float x = point.m_x;
    location->x = x;
    float y = point.m_y;
    location->y = y;
    location->SetLayer((*(RHScriptPositionFields **)((char *)actor + 0x50))->layer);
    location->SetArea((*(RHScriptPositionFields **)((char *)actor + 0x50))->area);
    return location;
}

class RHElementActorHuman
{
public:
    void FUN_0047ca50();
};

static inline bool RHScriptAreaBit1(char *area) { return (*(unsigned int *)(area + 0x30) >> 1) & 1; }
static inline bool RHScriptAreaBit0(char *area) { return *(unsigned int *)(area + 0x30) & 1; }

// FUNCTION: GAME 0x005718d0
bool RHScript::SetActorLocation(void *actor, void *location)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1508,
                 // STRING: GAME 0x006b2ac4
                 "Script Error: Trying to set the location of an invalid actor.");
        return false;
    }
    if (location == 0)
    {
        *(char *)((char *)actor + 0x12) = 0;
        *(char *)((char *)actor + 0x88) = 1;
        if ((*(unsigned int *)((char *)actor + 4) & 7) == 4)
        {
            ((RHElementActorHuman *)actor)->FUN_0047ca50();
            g_unk0x6c10e8->RemoveUnconsciousStarsIf((RHElementActor *)actor);
        }
        if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
        {
            if (*(char *)((char *)actor + 0x4e8))
            {
                ((RHEngineWidenedCalls *)actor)->FUN_004e3660(false);
                return true;
            }
        }
        if ((*(unsigned int *)((char *)actor + 4) & 15) == 4)
        {
            if (!*(char *)((char *)actor + *(int *)(*(char **)((char *)actor + 0x49c) + 4) + 0x660))
            {
                ((RHUnk00418b80 *)((char *)actor + *(int *)(*(char **)((char *)actor + 0x49c) + 4) + 0x49c))->Unk(false);
                return true;
            }
        }
    }
    else
    {
        if (*(char *)((char *)actor + 0x88))
        {
            *(char *)((char *)actor + 0x12) = 1;
            *(char *)((char *)actor + 0x88) = 0;
        }
        if (*(int *)((char *)location + 0x18) != 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1541,
                     // STRING: GAME 0x006b2a78
                     "Script Error: Trying to set the actor position using a wrong location type.");
            return false;
        }
        RHUnk00522470 &target = *(RHUnk00522470 *)location;
        SBGeoPoint2D &point = *(SBGeoPoint2D *)&target.x;
        ((RHActorPositionCalls *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00464530(point);
        ((RHScriptActorPositionFields *)actor)->position->layer = target.layer;
        ((RHScriptActorPositionFields *)actor)->position->area = target.area;
        char *area = (char *)target.area;
        if (RHScriptAreaBit1(area) && RHScriptAreaBit0(area))
        {
            RHBonusProjection *projection = ((RHUnk0057d800 *)area)->Unk(point);
            ((RHBonusInfoBase *)(*(char **)((char *)actor + 0x50) + 4))->FUN_0055fa20(projection);
            ((RHBonusInfoBase *)(*(char **)((char *)actor + 0x50) + 4))->FUN_0055f290();
            ((RHBonusInfo *)*(void **)((char *)actor + 0x50))->FUN_005bd560(0, true);
        }
        else
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1552,
                     // STRING: GAME 0x006b2a38
                     "VERBOTEN SCRIPT : Character not lying on motion area (%f,%f) !", point.m_x, target.y);
            return false;
        }
    }
    return true;
}

// FUNCTION: GAME 0x00571a70
int RHScript::GetActorDirection(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1583,
                 // STRING: GAME 0x006b2b04
                 "Script Error: Trying to get the direction of an invalid actor.");
        return 0;
    }
    return *(short *)(*(char **)((char *)actor + 0x50) + 0xd8);
}

// 91.36%, store/return constant CSE.
// STUB: GAME 0x00571ab0
bool RHScript::SetActorDirection(void *actor, int direction)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1607,
                 // STRING: GAME 0x006b2b44
                 "Script Error: Trying to set the direction of an invalid actor.");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) == 2)
    {
        ((RHUnk004af060 *)actor)->Unk(direction);
        return true;
    }
    char *position = *(char **)((char *)actor + 0x50) + 4;
    direction &= 15;
    *(short *)(position + 0xd4) = (short)direction;
    *(short *)(position + 0xd6) = (short)direction;
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 9)
    {
        *(int *)((char *)actor + 0xa8) = 1;
    }
    return true;
}

// FUNCTION: GAME 0x00571b30
bool RHScript::StopActor(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1646,
                 // STRING: GAME 0x006b2bc0
                 "Script Error: Trying to stop an invalid actor.");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1652,
                 // STRING: GAME 0x006b2b84
                 "Script Error: Trying to stop an 'actor' who has no legs.");
        return false;
    }
    ((RHUnk0046bcb0 *)actor)->Unk(6);
    return true;
}

// FUNCTION: GAME 0x00571b80
int RHScript::GetDistance(void *first, void *second)
{
    RHUnk005fc3b0 vector;
    if (first == 0 || *(int *)((char *)first + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1684,
                 // STRING: GAME 0x006b2bf0
                 "GRANDE FOIRE AU POINTEUR NUL ! Script Error : 1st argument of GetDistance is no point");
        return 0;
    }
    if (second == 0 || *(int *)((char *)second + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1690,
                 // STRING: GAME 0x006b2c48
                 "GRANDE FOIRE AU POINTEUR NUL ! Script Error : 2nd argument of GetDistance is no point");
        return 0;
    }
    vector.Set(*(float *)((char *)second + 4) - *(float *)((char *)first + 4),
               *(float *)((char *)second + 8) - *(float *)((char *)first + 8));
    return (int)vector.Unk005fc6a0(1.0f);
}

// FUNCTION: GAME 0x00571c60
void *RHScript::ComputeLocationBetween(void *first, void *second, float ratio)
{
    RHUnk005fc3b0 vector;
    if (*(int *)((char *)first + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1722,
                 // STRING: GAME 0x006b2d40
                 "Script Error: 1st argument of ComputeLocationBetween is no point");
        return 0;
    }
    if (*(int *)((char *)second + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1728,
                 // STRING: GAME 0x006b2cfc
                 "Script Error: 2nd argument of ComputeLocationBetween is no point");
        return 0;
    }
    RHUnk00522470 &a = *(RHUnk00522470 *)first;
    RHUnk00522470 &b = *(RHUnk00522470 *)second;
    if (a.layer == b.layer)
    {
        void *areaA = *(void *volatile *)&a.area;
        void *areaB = *(void *volatile *)&b.area;
        if (areaA == areaB)
        {
            RHUnk00522470 *location = new RHUnk00522470;
            location->x = (b.x - a.x) * ratio + a.x;
            location->y = (b.y - a.y) * ratio + a.y;
            location->SetLayer(a.layer);
            location->SetArea(a.area);
            std::list<RHUnk00522470 *> &locations = *(std::list<RHUnk00522470 *> *)&g_unk0x6c0fe8;
            locations.insert(locations.end(), location);
            g_unk0x6c0fe8.m_flag10 = 1;
            return location;
        }
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1734,
             // STRING: GAME 0x006b2ca0
             "Script Error: 1st and 2nd arguments of ComputeLocationBetween must have same sector / layer");
    return 0;
}

// FUNCTION: GAME 0x00571de0
bool RHScript::IsInside(void *actor, void *sector)
{
    if (sector == 0 || actor == 0)
    {
        return false;
    }
    if (*(int *)((char *)sector + 0xbc) == 2)
    {
        if ((*(unsigned int *)((char *)actor + 4) & 3) == 3 &&
            !*(char *)((char *)actor + 0x12))
        {
            return false;
        }
        return ((RHSectorScript *)sector)->FUN_0057ff00((RHElementActor *)actor);
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1786,
             // STRING: GAME 0x006b2d84
             "Script Error: trying to check if a character is inside a location which is not a sector.");
    return false;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00571e30
bool FUN_00571e30(int sector)
{
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)index);
        if (!RHScript::IsInside(actor, (void *)sector))
            return false;
    }
    return true;
}
}

// FUNCTION: GAME 0x00571ea0
void *RHScript::GetAnyActorInsideBuilding(void *sector)
{
    if (sector == 0)
    {
        return 0;
    }
    if (*(int *)((char *)sector + 0xbc) == 2)
    {
        if (*(int *)((char *)sector + 0xd4))
        {
            RHScriptNode *head = *(RHScriptNode *volatile *)((char *)sector + 0xd0);
            return head->next->data;
        }
    }
    else
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1831,
                 // STRING: GAME 0x006b2de0
                 "Script Error: trying to check if any character is inside a location which is not a sector.");
    }
    return 0;
}

// FUNCTION: GAME 0x00571ef0
bool RHScript::AreAllEnemiesInsideHS(void *sector)
{
    if (sector == 0)
    {
        return false;
    }
    if (*(int *)((char *)sector + 0xbc) != 2)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1862,
                 // STRING: GAME 0x006b2e3c
                 "Script Error: trying to call AreAllEnemiesInsideHS for location which is not a sector.");
        return false;
    }
    int count = *(int *)((char *)sector + 0xd4);
    for (int index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        RHSeqList &list = *(RHSeqList *)((char *)sector + 0xcc);
        list.GoTo((unsigned short)index);
        void *actor = list.cursor->data;
        if ((*(unsigned int *)((char *)actor + 4) & 31) == 20 &&
            *(char *)((char *)actor + 0x12) &&
            ((RHUnk00570e70Vtbl *)actor)->v76() == 1 &&
            !((RHUnk00570e70Vtbl *)actor)->v18() &&
            !*(char *)((char *)actor + 0x1ce) &&
            *(int *)(*(char **)((char *)actor + 0x50) + 0x8c) != 18 &&
            !*(int *)((char *)actor + 0x254))
        {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAME 0x00571fb0
int RHScript::GetPersistentProperty(void *actor, int property)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1914,
                 // STRING: GAME 0x006b31dc
                 "Script Error: Trying to set the property of an invalid actor.");
        return -1;
    }
    switch (property)
    {
    case 0:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1925,
                     // STRING: GAME 0x006b3198
                     "Script Error: Trying to get the property 'arrows' of a non-human.");
            return -1;
        }
        if (!*(int *)((char *)actor + 0x258))
        {
            return 0;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(1);
    case 1:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1941,
                     // STRING: GAME 0x006b3158
                     "Script Error: Trying to get the property 'money' of a non-NPC.");
            return -1;
        }
        return *(int *)((char *)actor + 0x4f0);
    case 2:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1949,
                     // STRING: GAME 0x006b3110
                     "Script Error: Trying to get the property 'life points' of a non-human.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v51();
    case 3:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1957,
                     // STRING: GAME 0x006b30c8
                     "Script Error: Trying to get the property 'concussion' of a non-human.");
            return -1;
        }
        return *(unsigned short *)((char *)actor + 0x1c8);
    case 4:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1965,
                     // STRING: GAME 0x006b3088
                     "Script Error: Trying to get the property 'purses' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(4);
    case 5:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1973,
                     // STRING: GAME 0x006b3048
                     "Script Error: Trying to get the property 'stones' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(5);
    case 6:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1981,
                     // STRING: GAME 0x006b3008
                     "Script Error: Trying to get the property 'apples' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(11);
    case 7:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1989,
                     // STRING: GAME 0x006b2fc8
                     "Script Error: Trying to get the property 'ales' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(12);
    case 8:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 1997,
                     // STRING: GAME 0x006b2f88
                     "Script Error: Trying to get the property 'legs' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(13);
    case 9:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2005,
                     // STRING: GAME 0x006b2f48
                     "Script Error: Trying to get the property 'plants' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(16);
    case 10:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2013,
                     // STRING: GAME 0x006b2f08
                     "Script Error: Trying to get the property 'nets' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(17);
    case 11:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2021,
                     // STRING: GAME 0x006b2ec4
                     "Script Error: Trying to get the property 'wasp nests' of a non-PC.");
            return -1;
        }
        return ((RHUnk00570e70Vtbl *)actor)->v57(19);
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2027,
                 // STRING: GAME 0x006b2e94
                 "Script Error: Trying to get invalid property.");
        return -1;
    }
}

// 77.97%, wstring inlining/helper operands.
// STUB: GAME 0x00572300
bool RHScript::SetPersistentProperty(void *actor, int property, int value)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2053,
                 "Script Error: Trying to set the property of an invalid actor.");
        return false;
    }
    switch (property)
    {
    case 0:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2064,
                     // STRING: GAME 0x006b35a8
                     "Script Error: Trying to set the property 'arrows' of a non-human.");
            return false;
        }
        if (!*(int *)((char *)actor + 0x258))
        {
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(1, value);
        return true;
    case 1:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2081,
                     // STRING: GAME 0x006b3568
                     "Script Error: Trying to set the property 'money' of a non-NPC.");
            return false;
        }
        *(int *)((char *)actor + 0x4f0) = value;
        return true;
    case 2:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2090,
                     // STRING: GAME 0x006b3520
                     "Script Error: Trying to set the property 'life points' of a non-human.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v53(value, 0, false);
        return true;
    case 3:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2099,
                     // STRING: GAME 0x006b34d8
                     "Script Error: Trying to set the property 'concussion' of a non-human.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v55(value, 0, true);
        return true;
    case 4:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2108,
                     // STRING: GAME 0x006b3498
                     "Script Error: Trying to set the property 'purses' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(4, value);
        return true;
    case 5:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2117,
                     // STRING: GAME 0x006b3458
                     "Script Error: Trying to set the property 'stones' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(5, value);
        return true;
    case 6:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2126,
                     // STRING: GAME 0x006b3418
                     "Script Error: Trying to set the property 'apples' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(11, value);
        return true;
    case 7:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2135,
                     // STRING: GAME 0x006b33d8
                     "Script Error: Trying to set the property 'ales' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(12, value);
        return true;
    case 8:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2144,
                     // STRING: GAME 0x006b3398
                     "Script Error: Trying to set the property 'legs' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(13, value);
        return true;
    case 9:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2153,
                     // STRING: GAME 0x006b3358
                     "Script Error: Trying to set the property 'plants' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(16, value);
        return true;
    case 10:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2162,
                     // STRING: GAME 0x006b3318
                     "Script Error: Trying to set the property 'nets' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(17, value);
        return true;
    case 11:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2171,
                     // STRING: GAME 0x006b32d4
                     "Script Error: Trying to set the property 'wasp nests' of a non-PC.");
            return false;
        }
        ((RHUnk00570e70Vtbl *)actor)->v59(19, value);
        return true;
    case 12:
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2180,
                     // STRING: GAME 0x006b3294
                     "Script Error: Trying to set the property 'name' of a non-PC.");
            return false;
        }
        switch (value)
        {
        case 0:
            *(std::wstring *)(*(char **)((char *)actor + 0x600) + 0x2c) = FUN_005e23d0(0xfa);
            return true;
        case 1:
            *(std::wstring *)(*(char **)((char *)actor + 0x600) + 0x2c) = FUN_005e23d0(0xfb);
            return true;
        case 2:
            *(std::wstring *)(*(char **)((char *)actor + 0x600) + 0x2c) = FUN_005e23d0(0xfc);
            return true;
        default:
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2199,
                     // STRING: GAME 0x006b324c
                     "Script Error: Trying to set the property 'name' with invalid name ID.");
            return false;
        }
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2205,
                 // STRING: GAME 0x006b321c
                 "Script Error: Trying to set invalid property.");
        return false;
    }
}

// FUNCTION: GAME 0x005729a0
void RHScript::ConfiscateMoney(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2226,
                 // STRING: GAME 0x006b3624
                 "Script Error: Trying to confiscate money of invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2234,
                 // STRING: GAME 0x006b35ec
                 "Script Error: Trying to confiscate money of non-human.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
    {
        ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(1, *(int *)((char *)actor + 0x4f0));
        *(int *)((char *)actor + 0x4f0) = 0;
    }
}

// FUNCTION: GAME 0x00572ab0
bool RHScript::RecordScrollCameraTo(void *location)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2296,
                 // STRING: GAME 0x006b36c4
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2302,
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2308,
                 // STRING: GAME 0x006b368c
                 "Script Error: Wrong kind of location for this operation");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 6, 0);
    element->Unk00587010(8, *(SBGeoPoint2D *)((char *)location + 4));
    element->Unk00586ed0(10, 0);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3674
                         "RecordScrollCameraTo");
}

// FUNCTION: GAME 0x00572ba0
bool RHScript::RecordJumpCameraTo(void *location)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2339,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2345,
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2351,
                 "Script Error: Wrong kind of location for this operation");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 7, 0);
    element->Unk00587010(8, *(SBGeoPoint2D *)((char *)location + 4));
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b371c
                         "RecordJumpCameraTo");
}

// FUNCTION: GAME 0x00572c70
bool RHScript::RecordMoveCameraTo(void *location, int speed)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2383,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2389,
                 "JETZT GEHT'S LOS ! Script error : Trying to move the camera to NULL !");
        return false;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2395,
                 "Script Error: Wrong kind of location for this operation");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 6, 0);
    element->Unk00587010(8, *(SBGeoPoint2D *)((char *)location + 4));
    element->Unk00586ed0(10, speed);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3730
                         "RecordMoveCameraTo");
}

// FUNCTION: GAME 0x00572d50
bool RHScript::RecordSetZoom(float zoom)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2423,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    if (zoom != 0.5f && zoom != 1.0f && zoom != 2.0f)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2429,
                 // STRING: GAME 0x006b3754
                 "Script Error: Wanted zoom level is incorrect in RecordSetZoom.");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 8, 0);
    element->Unk00586fd0(9, zoom);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3744
                         "RecordSetZoom");
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00572a20
bool FUN_00572a20(int dialog)
{
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 12, 0);
    element->Unk00586ed0(18, dialog);
    element->Unk00586ed0(19, 0);
    return RHScript::AddToSequence((RHSequenceElement *)element,
        // STRING: GAME 0x006b3660
        "RecordPlayDialog");
}
}

// FUNCTION: GAME 0x00572e40
bool RHScript::RecordDisplayMap(bool display)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2456,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 9, 0);
    element->Unk00586e00(22, display);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3794
                         "RecordDisplayMap");
}

// FUNCTION: GAME 0x00572ef0
bool RHScript::RecordSpeak(void *actor, int index)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2485,
                 // STRING: GAME 0x006b3820
                 "Script Error: to declare a speak sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2492,
                 // STRING: GAME 0x006b37e4
                 "Script Error: trying to do a record speak on a non-human.");
        return false;
    }
    if (index >= 120)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2498,
                 // STRING: GAME 0x006b37b4
                 "Script Error: ID for speak is %u, must be < %u.", index, 120);
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0x92, actor);
    element->Unk00586ed0(15, index);
    element->Unk00586ed0(17, 0);
    element->Unk00586ed0(16, 12);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b37a8
                         "RecordSpeak");
}

// FUNCTION: GAME 0x00573010
void RHScript::ForbidNPCRemark(void *actor, int index, bool forbidden)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2525,
                 // STRING: GAME 0x006b38e8
                 "Script Error: trying to forbid NPC remark on an invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2531,
                 // STRING: GAME 0x006b38b0
                 "Script Error: trying to forbid NPC remark to a non-NPC.");
        return;
    }
    if (index >= 120)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2537,
                 // STRING: GAME 0x006b3874
                 "Script Error: ID for ForbidNPCRemark is %u, must be < %u.", index, 120);
        return;
    }
    int offset = *(int *)(*(char **)((char *)actor + 0x49c) + 4);
    ((RHUnk00419a40 *)((char *)actor + offset + 0x49c))->Unk(index, forbidden);
}

// FUNCTION: GAME 0x005730b0
bool RHScript::RecordSpeakPC(void *actor, int index, int variant)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2566,
                 // STRING: GAME 0x006b3974
                 "Script Error: to declare a speak PC sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2573,
                 // STRING: GAME 0x006b3938
                 "Script Error: trying to do a record speak PC on a non-PC.");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0x92, actor);
    element->Unk00586ed0(15, index);
    element->Unk00586ed0(17, variant);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3928
                         "RecordSpeakPC");
}

// FUNCTION: GAME 0x00573190
bool RHScript::RecordPlayAnim(void *actor, int animation)
{
    if (actor == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2602,
                 // STRING: GAME 0x006b3a74
                 "Script error in RecordPlayAnim: trying yto use an invalid actor.");
        return false;
    }
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2608,
                 // STRING: GAME 0x006b3a1c
                 "Script Error: to declare a play anim sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0 &&
        (*(unsigned int *)((char *)actor + 4) & 15) != 9)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2615,
                 // STRING: GAME 0x006b39dc
                 "Script Error: trying to do a play anim on a non actor thing.");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0xa4, actor);
    element->Unk00586ed0(21, animation);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b39cc
                         "RecordPlayAnim");
}

// FUNCTION: GAME 0x00573280
bool RHScript::RecordPlayAnimLoop(void *actor, int animation)
{
    if (actor == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2644,
                 // STRING: GAME 0x006b3acc
                 "Script error in RecordPlayAnimLoop: trying yto use an invalid actor.");
        return false;
    }
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2650,
                 "Script Error: to declare a play anim sequence you must initialize the sequence at first");
        return false;
    }
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2657,
                 "Script Error: trying to do a play anim on a non actor thing.");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0xa5, actor);
    element->Unk00586ed0(21, animation);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3ab8
                         "RecordPlayAnimLoop");
}

// FUNCTION: GAME 0x00573370
bool RHScript::RecordPlayAnimFreeze(void *actor, int animation)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2687,
                 "Script Error: to declare a play anim sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0 &&
        (*(unsigned int *)((char *)actor + 4) & 15) != 9)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2694,
                 // STRING: GAME 0x006b3b2c
                 "Script Error: trying to do a play anim on neither an actor nor a target.");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0xa6, actor);
    element->Unk00586ed0(21, animation);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b3b14
                         "RecordPlayAnimFreeze");
}

// parked: shared-success-tail/constant-hoisting mismatch; 73.71% common-tail, 68.70% per-case; isolated /O2 /GX probes emit immediate 1, not bl.
// STUB: GAME 0x00573450
bool RHScript::RecordAction(void *actor, int action, int argument)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2726,
                 "Script Error: to declare a play anim sequence you must initialize the sequence at first");
        return false;
    }
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2733,
                 // STRING: GAME 0x006b3d20
                 "Script Error: Trying to record action for an invalid actor.");
        return false;
    }
    RHUnk00584d60 *element;
    void *target;
    bool result = true;
    switch (action)
    {
    case 0:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0xa1, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 1:
        {
            RHUnk005866a0 *turn = new RHUnk005866a0(g_unk0x6c0fa4, 0x1a, actor);
            turn->Unk00586ed0(0, argument % 16);
            AddToSequence((RHSequenceElement *)turn,
                          // STRING: GAME 0x006b3d10
                          "RecordAction");
            return result;
        }
    case 2:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x1d, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 3:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x22, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 4:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2765,
                     // STRING: GAME 0x006b3ca8
                     "Script Error: Trying to record shoot action with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0xb2, actor, target);
        element->SetFlag(result);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 5:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2778,
                     // STRING: GAME 0x006b3c44
                     "Script Error: Trying to begin swordfight with illegal argument (must be antagonists actor index).");
            return false;
        }
        {
            void *target = g_unk0x6c0f34[argument];
            RHUnk005866a0 *fight = new RHUnk005866a0(g_unk0x6c0fa4, 0x32, actor);
            fight->Unk00586ed0(33, (int)target);
            fight->Unk00586ed0(24, 0);
            fight->Unk00586e00(34, false);
            *(bool *)((char *)fight + 0x60) = result;
            AddToSequence((RHSequenceElement *)fight, "RecordAction");
            return result;
        }
    case 6:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x33, actor);
        element->SetFlag(result);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 7:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x34, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 8:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2805,
                     // STRING: GAME 0x006b3be0
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x3b, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 9:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2817,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x3c, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 10:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2829,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x3d, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 11:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2841,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x3e, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 12:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2853,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x3f, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 13:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2865,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x40, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 14:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2877,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x41, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 15:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2889,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x42, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 16:
        if (argument < 0 || argument >= (g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2901,
                     "Script Error: Trying to make sword trust with illegal argument (must be antagonists actor index).");
            return false;
        }
        target = g_unk0x6c0f34[argument];
        element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x43, actor, target);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 17:
        if ((*(unsigned int *)((char *)actor + 4) & 31) != 20)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2913,
                     // STRING: GAME 0x006b3ba4
                     "Script Error: Trying to make a non-soldier look sidewards.");
            return false;
        }
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x87, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 18:
        if ((*(unsigned int *)((char *)actor + 4) & 31) != 20)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2923,
                     "Script Error: Trying to make a non-soldier look sidewards.");
            return false;
        }
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x88, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 19:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x20, actor);
        element->SetFlag(result);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    case 20:
        element = new RHUnk00584d60(g_unk0x6c0fa4, 0x4d, actor);
        AddToSequence((RHSequenceElement *)element, "RecordAction");
        return result;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2942,
                 // STRING: GAME 0x006b3b78
                 "Script Error: illegal ID for RecordAction");
        return false;
    }
}

// FUNCTION: GAME 0x00573da0
bool RHScript::RecordSeekActorMessage(void *actor, void *target, int style, float distance, void *recipient, int event)
{
    if (recipient != 0 && (*(unsigned int *)((char *)recipient + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 2991,
                 // STRING: GAME 0x006b3d84
                 "Script Error: Wrong parameters for RecordSeekActorMessage method");
        return false;
    }
    RHUnk00588530 *element = new RHUnk00588530(g_unk0x6c0fa4, 21, actor, style != 0 ? 10 : 6, target, distance, 0);
    if (AddToSequence((RHSequenceElement *)element,
                       // STRING: GAME 0x006b3d6c
                       "RecordSeekActorMessage"))
    {
        RHUnk00582220 *sequence = new RHUnk00582220;
        RHUnk005866a0 *message = new RHUnk005866a0(1, 15, recipient);
        message->Unk00586ed0(3, event);
        message->Unk00586ed0(4, 0);
        message->Unk00586ed0(5, 0);
        ((RHUnk00585500 *)message)->Unk(sequence);
        element->sequence = sequence;
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00573f00
bool RHScript::RecordSeekActorMessageWithArguments(void *actor, void *target, int style, float distance, void *recipient, int event, int first, int second)
{
    if (recipient != 0 && (*(unsigned int *)((char *)recipient + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3024,
                 // STRING: GAME 0x006b3e28
                 "Script Error: Wrong parameters for RecordSeekActorMessageWithArguments method");
        return false;
    }
    if (event < 1000)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3030,
                 // STRING: GAME 0x006b3dec
                 "Script Error: ID for custom event is %u, must be >= 1000.", event);
        return false;
    }
    RHUnk00588530 *element = new RHUnk00588530(g_unk0x6c0fa4, 21, actor, style != 0 ? 10 : 6, target, distance, 0);
    if (AddToSequence((RHSequenceElement *)element,
                       // STRING: GAME 0x006b3dc8
                       "RecordSeekActorMessageWithArguments"))
    {
        RHUnk00582220 *sequence = new RHUnk00582220;
        RHUnk005866a0 *message = new RHUnk005866a0(1, 15, recipient);
        message->Unk00586ed0(3, event);
        message->Unk00586ed0(4, first);
        message->Unk00586ed0(5, second);
        ((RHUnk00585500 *)message)->Unk(sequence);
        element->sequence = sequence;
        return true;
    }
    return false;
}

// Parked: counted begin callee corrected; first/area registers and cached-list scheduling remain non-exact.
// STUB: GAME 0x005740b0
bool RHScript::RecordMove(void *actor, void *location, int style)
{
    SBGeoPoint2D point;
    RHUnk00571160Position start;
    if (actor == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3101,
                 // STRING: GAME 0x006b3ff8
                 "Script error in RecordMove: invalid actor.");
        return false;
    }
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3107,
                 "Script Error: To create a sequence you must initialize the sequence at first");
        return false;
    }
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3113,
                 // STRING: GAME 0x006b3f58
                 "Script Error: You tried to create a move sequence with a location that was NULL");
        return false;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3119,
                 // STRING: GAME 0x006b3f08
                 "Script Error: You tried to create a move sequence with an illegal location type");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3124,
                 // STRING: GAME 0x006b3ec0
                 "Script Error: You tried to create a move sequence with an illegal actor");
        return false;
    }
    RHUnk00574690(actor, &start, location);
    int animation;
    switch (style)
    {
    case 0:
    case 2:
        animation = 6;
        break;
    case 1:
    case 3:
        animation = 10;
        break;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3148,
                 // STRING: GAME 0x006b3e78
                 "Script Error: You tried to create a move sequence with an illegal style");
        return false;
    }
    unsigned short first = *(int *)((char *)g_unk0x6c0f78 + 0x10);
    unsigned short layer = *(unsigned short *)((char *)location + 0x20);
    void *area = *(void **)((char *)location + 0x24);
    ((RHUnk00582640 *)g_unk0x6c0f78)->Unk(g_unk0x6c0fa4, actor, animation,
        SBGeoPoint2D(start.x, start.y), start.area, start.layer,
        *(SBGeoPoint2D *)((char *)location + 4), area,
        layer, 0, 0.0f, 0, 1.0f);
    if (style >= 2 && style <= 3)
    {
        unsigned short last = *(int *)((char *)g_unk0x6c0f78 + 0x10);
        for (unsigned short index = first; index < last; ++index)
            *(int *)((char *)((RHUnk0046eb30 *)((char *)g_unk0x6c0f78 + 8))->Get(index) + 0x5c) = 6;
    }
    --g_unk0x6c0fa4;
    return true;
}

// Parked: 81.29% with a widened first-count local; first/area registers and cached-list scheduling remain non-exact.
// STUB: GAME 0x005743a0
bool RHScript::RecordMoveNear(void *actor, void *location, int style, int distance)
{
    SBGeoPoint2D point;
    RHUnk00571160Position start;
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3204,
                 "Script Error: To create a sequence you must initialize the sequence at first");
        return false;
    }
    if (location == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3210,
                 // STRING: GAME 0x006b40cc
                 "Script Error: You tried to create a move-near sequence with a location that was NULL");
        return false;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3216,
                 // STRING: GAME 0x006b4074
                 "Script Error: You tried to create a move-near sequence with an illegal location type");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3221,
                 // STRING: GAME 0x006b4024
                 "Script Error: You tried to create a move-near sequence with an illegal actor");
        return false;
    }
    RHUnk00574690(actor, &start, location);
    int animation;
    switch (style)
    {
    case 0:
    case 2:
        animation = 6;
        break;
    case 1:
    case 3:
        animation = 10;
        break;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3245,
                 "Script Error: You tried to create a move sequence with an illegal style");
        return false;
    }
    unsigned int first = *(int *)((char *)g_unk0x6c0f78 + 0x10);
    unsigned short layer = *(unsigned short *)((char *)location + 0x20);
    void *area = *(void **)((char *)location + 0x24);
    ((RHUnk00582640 *)g_unk0x6c0f78)->Unk(g_unk0x6c0fa4, actor, animation,
        SBGeoPoint2D(start.x, start.y), start.area, start.layer,
        *(SBGeoPoint2D *)((char *)location + 4), area,
        layer, 0, (float)distance, 0, 1.0f);
    if (style >= 2 && style <= 3)
    {
        unsigned short last = *(int *)((char *)g_unk0x6c0f78 + 0x10);
        for (unsigned short index = first; index < last; ++index)
            *(int *)((char *)((RHUnk0046eb30 *)((char *)g_unk0x6c0f78 + 8))->Get(index) + 0x5c) = 7;
    }
    --g_unk0x6c0fa4;
    return true;
}

// parked: 65.02% assignment call, 69.01% field copies; doors base, x87 copy and success/cleanup placement differ.
// STUB: GAME 0x00574860
bool RHScript::RecordMoveIntoBuilding(void *actor, void *location, int style)
{
    SBGeoPoint2D point;
    RHUnk00522470 destination;
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3358,
                 // STRING: GAME 0x006b4190
                 "Script Error: Trying to walk into a building using a wrong location type.");
    }
    else
    {
        point.m_x = *(float *)((char *)location + 4);
        float y = *(float *)((char *)location + 8);
        point.m_y = y;
        void *door = 0;
        unsigned int closest = 90000;
        char *world = (char *)g_unk0x6c0a9c;
        void ***doors = (void ***)(world + 0x4084);
        unsigned short count = *doors == 0 ? 0 : *(void ***)(world + 0x4088) - *doors;
        for (unsigned short index = 0; index < count; ++index)
        {
            char *candidate = (char *)(*doors)[index];
            if (*(int *)(candidate + 4) == 1)
            {
                unsigned int distance = (unsigned int)((SBGeoPoint2D *)(candidate + 0x94))->Unk005fc110(point).Unk005fc6d0(1.0f);
                if (distance < closest)
                {
                    closest = distance;
                    door = candidate;
                }
            }
        }
        if (door != 0)
        {
            destination.x = *(float *)((char *)door + 0x20);
            destination.y = *(float *)((char *)door + 0x24);
            destination.SetLayer(*(unsigned short *)((char *)door + 0x16));
            destination.SetArea(*(void **)((char *)door + 0x10));
            return RecordMove(actor, &destination, style);
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3387,
                 // STRING: GAME 0x006b4124
                 "Script Error: Trying to walk into a building, but no door found in a radius of 300 points around (%u, %u)",
                 (unsigned short)point.m_x, (unsigned short)point.m_y);
    }
    return false;
}

// Parked: 82.30% with function-scope destination; iterator temporary slot and point-call scheduling still differ.
// STUB: GAME 0x00574a70
bool RHScript::RecordTakeCorpse(void *actor, void *corpse, int style)
{
    RHUnk00571160Position start;
    RHUnk00571160Position destination;
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3426,
                 "Script Error: to declare a play anim sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12 ||
        (!((RHUnk0049d4f0 *)actor)->Unk(25) && !((RHUnk0049d4f0 *)actor)->Unk(26)))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3432,
                 // STRING: GAME 0x006b41dc
                 "Script Error: In RecordTakeCorpse, the taker is not a valid actor");
        return false;
    }
    if ((*(unsigned int *)((char *)corpse + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3438,
                 // STRING: GAME 0x006b4234
                 "Script Error: In RecordTakeCorpse, the corpse is not valid");
        return false;
    }
    int count = g_unk0x6c0f50.count;
    unsigned int index;
    for (index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        ((RHSeqList *)&g_unk0x6c0f50)->GoTo((unsigned short)index);
        if (g_unk0x6c0f50.cursor->data == actor)
            break;
    }
    if ((unsigned short)index < (unsigned short)count)
    {
        ((RHSeqList *)&g_unk0x6c0fb0)->GoTo((unsigned short)index);
        start = *(RHUnk00571160Position *)&g_unk0x6c0fb0.cursor->data;
    }
    else
    {
        ((RHUnk00560420 *)(*(char **)((char *)actor + 0x50) + 4))->Unk(&start);
        char *sprite = *(char **)((char *)corpse + 0x50);
        destination.x = *(float *)(sprite + 0x24);
        destination.y = *(float *)(sprite + 0x28);
        destination.area = *(void **)(sprite + 0xe0);
        destination.layer = *(short *)(sprite + 0xde);
        g_unk0x6c0fb0.Unk0057c950(RHScriptIter(g_unk0x6c0fb0.head), destination);
        g_unk0x6c0fb0.valid = true;
        RHScriptNode *head = g_unk0x6c0f50.head;
        RHSequenceElement *value = (RHSequenceElement *)actor;
        RHScriptNode *node = g_unk0x6c0f50.Unk0059f720(head, head->prev);
        head->prev = node;
        node->prev->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->data, &value);
        ++g_unk0x6c0f50.count;
        g_unk0x6c0f50.valid = true;
    }
    float distance;
    {
        char *sprite = *(char **)((char *)actor + 0x50);
        SBGeoVector2D vector(*(SBGeoPoint2D *)(sprite + 0x1c));
        short frame = *(short *)(sprite + 0xd8);
        void *holder = ((RHUnk005b5e00 *)sprite)->Unk();
        short offset = *(short *)(*(char **)((char *)holder + 4) + 0x172);
        SBGeoPoint2D *point = ((RHUnk005b5e00 *)sprite)->Unk005bdd30(offset + frame);
        distance = ((RHUnk005fc3b0 *)&point->Unk005fc190(vector).Unk005fc110(*(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
    }
    char *sprite = *(char **)((char *)corpse + 0x50);
    unsigned short layer = *(unsigned short *)(sprite + 0xde);
    void *area = *(void **)(sprite + 0xe0);
    ((RHUnk00582640 *)g_unk0x6c0f78)->Unk(g_unk0x6c0fa4, actor, style != 0 ? 10 : 6,
        SBGeoPoint2D(start.x, start.y), start.area, start.layer,
        *(SBGeoPoint2D *)(*(char **)((char *)corpse + 0x50) + 0x24), area, layer,
        0, distance, 0, 1.0f);
    RHUnk00585ea0 *element = new RHUnk00585ea0(g_unk0x6c0fa4, 0x65, actor, corpse);
    --g_unk0x6c0fa4;
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b4220
                         "RecordTakeCorpse");
}

// FUNCTION: GAME 0x00574db0
bool RHScript::RecordLeaveCorpse(void *actor)
{
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 12 &&
        (((RHUnk0049d4f0 *)actor)->Unk(25) || ((RHUnk0049d4f0 *)actor)->Unk(26)))
    {
        RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x66, actor);
        return AddToSequence((RHSequenceElement *)element,
                             // STRING: GAME 0x006b42b4
                             "RecordLeaveCorpse");
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3503,
             // STRING: GAME 0x006b4270
             "Script Error: In RecordLeaveCorpse, the taker is not a valid actor");
    return false;
}

// FUNCTION: GAME 0x00574e70
bool RHScript::RecordTurnTo(void *actor, void *location)
{
    SBGeoPoint2D point;
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        if (location != 0 && *(int *)((char *)location + 0x18) == 0)
        {
            RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0x1a, actor);
            element->Unk00587010(8, *(SBGeoPoint2D *)((char *)location + 4));
            return AddToSequence((RHSequenceElement *)element,
                                 // STRING: GAME 0x006b4344
                                 "RecordTurnTo");
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3539,
                 // STRING: GAME 0x006b4304
                 "ACHTUNG : Script error in \"RecordTurnTo\" : invalid location !");
    }
    else
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3532,
                 // STRING: GAME 0x006b42c8
                 "ACHTUNG : Script error (\"RecordTurnTo\") : invalid actor !");
    }
    return false;
}

// FUNCTION: GAME 0x00574f80
bool RHScript::RecordReplaceAnim(void *actor, int oldAnimation, int newAnimation)
{
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0xaa, actor);
        element->Unk00586ed0(37, oldAnimation);
        element->Unk00586ed0(38, newAnimation);
        return AddToSequence((RHSequenceElement *)element,
                             // STRING: GAME 0x006b43a4
                             "RecordReplaceAnim");
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3568,
             // STRING: GAME 0x006b4354
             "Script Error: You tried to create a replace-anim sequence with an illegal actor");
    return false;
}

// FUNCTION: GAME 0x00575050
bool RHScript::RecordRestoreAnim(void *actor, int animation)
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3599,
                 // STRING: GAME 0x006b3fa8
                 "Script Error: To create a sequence you must initialize the sequence at first");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3605,
                 // STRING: GAME 0x006b43cc
                 "Script Error: You tried to create a restore-anim sequence with an illegal actor");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0xab, actor);
    element->Unk00586ed0(37, animation);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b43b8
                         "RecordRestoreAnim");
}

// FUNCTION: GAME 0x00575120
bool RHScript::RecordLockAI(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x7f, actor);
        return AddToSequence((RHSequenceElement *)element,
                             // STRING: GAME 0x006b4450
                             "RecordLockAI");
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3634,
             // STRING: GAME 0x006b441c
             "Script Error: Wrong parameters for lock AI method");
    return false;
}

// FUNCTION: GAME 0x005751d0
bool RHScript::RecordUnlockAI(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x80, actor);
        return AddToSequence((RHSequenceElement *)element,
                             // STRING: GAME 0x006b4494
                             "RecordUnlockAI");
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3660,
             // STRING: GAME 0x006b4460
             "Script Error: Wrong parameters for unlock AI method");
    return false;
}

// FUNCTION: GAME 0x00575290
bool RHScript::RecordUnBlip(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x81, actor);
        return AddToSequence((RHSequenceElement *)element,
                             // STRING: GAME 0x006b44dc
                             "RecordUnBlip");
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3686,
             // STRING: GAME 0x006b44a4
             "Script Error: Wrong parameter for RecordUnBlip method");
    return false;
}

// FUNCTION: GAME 0x005753d0
bool RHScript::RecordLockUser()
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3734,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 4, 0);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b44f8
                         "RecordLockUser");
}

// FUNCTION: GAME 0x00575470
bool RHScript::RecordUnLockUser()
{
    if (g_unk0x6c0fa4 == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3760,
                 "Script Error: to declare a fire at sequence you must initialize the sequence at first");
        return false;
    }
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 5, 0);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b4508
                         "RecordUnLockUser");
}

// FUNCTION: GAME 0x005755f0
void *RHScript::GetSoundSourceScript(int index)
{
    char *context = *(char **)(g_unk0x6c0fa8 + 0x45e0);
    if (*(char *)(context + 0x20a))
    {
        g_unk0x6c0f7c = (*(RHSoundSourceManager **)(context + 0x200))->GetSoundSource(index);
        if (g_unk0x6c0f7c == 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3894,
                     // STRING: GAME 0x006b451c
                     "Trying to get a sound source that has already been destroyed !");
            return 0;
        }
        return g_unk0x6c0f7c;
    }
    return g_unk0x6c0f7c;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00573d10
bool FUN_00573d10(int actor, int target, int style, int distance)
{
    RHUnk00588530 *element = new RHUnk00588530(g_unk0x6c0fa4, 21, (void *)actor,
        style == 1 ? 6 : 10, (void *)target, *(float *)&distance, 0);
    return RHScript::AddToSequence((RHSequenceElement *)element,
        // STRING: GAME 0x006b3d5c
        "RecordSeekActor");
}

// FUNCTION: GAME 0x00575350
bool FUN_00575350(int value)
{
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 11, 0);
    element->Unk00586ed0(2, value);
    return RHScript::AddToSequence((RHSequenceElement *)element,
        // STRING: GAME 0x006b44ec
        "RecordTimer");
}

// FUNCTION: GAME 0x00577df0
void FUN_00577df0(bool value)
{
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 17, 0);
    element->Unk00586e00(39, value);
    RHScript::AddToSequence((RHSequenceElement *)element,
        // STRING: GAME 0x006b55f0
        "RecordFreezeAll");
}

// FUNCTION: GAME 0x00578830
void FUN_00578830(bool value)
{
    RHMessenger *messenger = RHUnk00546050();
    if (*((bool *)messenger + 0x17) != value)
        messenger->RHUnk005460c0(RHUnk5490f0(39));
}

// Parked: the fallback search uses different count/index registers and return-tail sharing.
// STUB: GAME 0x00579bd0
int FUN_00579bd0(int value)
{
    RHUnk579e80State *state = (RHUnk579e80State *)((char *)g_pEngine + 0x4978);
    if ((g_unk0x6c0f48 = RHScriptFindActor((void *)value)) != -1)
        return g_unk0x6c0f48;
    state->valid = 0;
    state->value = value;
    int *first = state->first;
    int count = first == 0 ? 0 : state->end - first;
    state->cursor = first;
    state->searchValid = 1;
    int index = 0;
    while (index < count)
    {
        if (*state->cursor == value)
            break;
        ++index;
        ++state->cursor;
    }
    if (index >= count)
        index = -1;
    state->index = index;
    return index;
}

// FUNCTION: GAME 0x00579c90
int FUN_00579c90(int value)
{
    RHUnk579e80State *state = (RHUnk579e80State *)((char *)g_unk0x6c0a9c + 0x4080);
    state->valid = 0;
    state->value = value;
    int *first = state->first;
    int count = first == 0 ? 0 : state->end - first;
    state->cursor = first;
    state->searchValid = 1;
    int index = 0;
    while (index < count)
    {
        if (*state->cursor == value)
            break;
        ++index;
        ++state->cursor;
    }
    if (index >= count)
        index = -1;
    state->index = index;
    return index;
}

// FUNCTION: GAME 0x00579d00
int FUN_00579d00(int value)
{
    RHUnk579e80State *state = (RHUnk579e80State *)((char *)g_unk0x6c0a9c + 0x40a0);
    state->valid = 0;
    state->value = value;
    int *first = state->first;
    int count = first == 0 ? 0 : state->end - first;
    state->cursor = first;
    state->searchValid = 1;
    int index = 0;
    while (index < count)
    {
        if (*state->cursor == value)
            break;
        ++index;
        ++state->cursor;
    }
    if (index >= count)
        index = -1;
    state->index = index;
    return index;
}

// FUNCTION: GAME 0x00579d70
int FUN_00579d70(int value)
{
    RHUnk579e80State *state = (RHUnk579e80State *)((char *)g_unk0x6c0a9c + 0x40e0);
    state->valid = 0;
    state->value = value;
    int *first = state->first;
    int count = first == 0 ? 0 : state->end - first;
    state->cursor = first;
    state->searchValid = 1;
    int index = 0;
    while (index < count)
    {
        if (*state->cursor == value)
            break;
        ++index;
        ++state->cursor;
    }
    if (index >= count)
        index = -1;
    state->index = index;
    return index;
}

// FUNCTION: GAME 0x0057a950
int FUN_0057a950(int type)
{
    int kind;
    switch (type)
    {
    case 0: kind = 26; break;
    case 1: kind = 27; break;
    case 2: kind = 28; break;
    case 3: kind = 29; break;
    case 4: kind = 30; break;
    case 5: kind = 31; break;
    case 6: kind = 32; break;
    default: return 0;
    }
    void **first = *(void **volatile *)((char *)g_pEngine + 0x48dc);
    unsigned short count = first == 0 ? 0 : *(void ***)((char *)g_pEngine + 0x48e0) - first;
    for (unsigned short index = 0; index < count; ++index)
    {
        char *actor = (char *)(*(void ***)((char *)g_pEngine + 0x48dc))[index];
        if (actor && (*(unsigned *)(actor + 4) & 3) == 3 && actor[0x12] && *(int *)(actor + 0xb0) == kind)
            return (int)actor;
    }
    return 0;
}

// FUNCTION: GAME 0x0057ae60
void FUN_0057ae60(int value)
{
    *(unsigned short *)((char *)g_pEngine + 0x4cc0) = value;
    unsigned count = (unsigned short)((RHScriptNPCArray *)g_pEngine)->Count();
    for (unsigned index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (RHMalignityActorCalls *)((RHScriptNPCArray *)g_pEngine)->first[(unsigned short)index];
        actor->FUN_0048ebe0();
    }
}

// FUNCTION: GAME 0x0057b2b0
void FUN_0057b2b0(int index, int first, int second)
{
    RHHumanStatus *status = (RHHumanStatus *)((RHConsoleCampaignCalls *)g_unk0x6c07fc)->FUN_004524b0(index - 1);
    status->FUN_0051d540(0, first);
    status->FUN_0051d540(1, second);
}

// FUNCTION: GAME 0x0057b3d0
bool FUN_0057b3d0(int sector)
{
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)index);
        if (!((RHUnk00570e70Vtbl *)actor)->v18() && !RHScript::IsInside(actor, (void *)sector))
            return false;
    }
    return true;
}

}

// FUNCTION: GAME 0x00579e80
int RHScript::RHUnk579e80(int value)
{
    RHUnk579e80State *state = (RHUnk579e80State *)((char *)g_unk0x6c0a9c + 0x40c0);
    state->valid = 0;
    state->value = value;
    int *first = state->first;
    int count = first == 0 ? 0 : state->end - first;
    state->cursor = first;
    state->searchValid = 1;
    int index = 0;
    while (index < count)
    {
        if (*state->cursor == value)
            break;
        ++index;
        ++state->cursor;
    }
    if (index >= count)
        index = -1;
    state->index = index;
    return index;
}

// FUNCTION: GAME 0x00579ef0
int RHScript::RHUnk579ef0(int value)
{
    return ((RHUnk0051d0e0 *)g_unk0x6c0b9c)->Find(value);
}

// FUNCTION: GAME 0x00579f10
void RHScript::RHUnk579f10(int value)
{
    FUN_005edae0(g_unk0x6c11d0,
        // STRING: GAME 0x006b652c
        "%d\n", value);
}

// FUNCTION: GAME 0x00579f30
void RHScript::RHUnk579f30(int value)
{
    RHMenuPopupScroll::FUN_0053a0b0(value);
    RHUnk00546050()->RHUnk005460c0(RHUnk5490f0(0x2e, 0));
}

// FUNCTION: GAME 0x00575510
char RHScript::RHUnk575510()
{
    RHSound *sound = (RHSound *)*(void **)(g_unk0x6c0fa8 + 0x45e0);
    if (*(char *)((char *)sound + 0x20a))
        sound->FUN_005a8780();
    return 1;
}

// FUNCTION: GAME 0x00575530
char RHScript::RHUnk575530()
{
    char *base = g_unk0x6c0fa8;
    RHSound *sound = (RHSound *)*(void **)(base + 0x45e0);
    if (*(char *)((char *)sound + 0x20a))
        sound->FUN_005a8700(base + 0x4738, *(void **)(base + 0x475c));
    return 1;
}

// FUNCTION: GAME 0x00575560
char RHScript::RHUnk575560(void *value)
{
    if (value != 0)
    {
        RHSound *sound = (RHSound *)*(void **)(g_unk0x6c0fa8 + 0x45e0);
        if (*(char *)((char *)sound + 0x20a))
            sound->FUN_005a87f0((RHSoundSource *)value);
    }
    return 1;
}

// FUNCTION: GAME 0x00575590
char RHScript::RHUnk575590(void *value)
{
    RHSound *sound = (RHSound *)*(void **)(g_unk0x6c0fa8 + 0x45e0);
    if (*(char *)((char *)sound + 0x20a))
        sound->FUN_005a8810(value);
    return 1;
}

// FUNCTION: GAME 0x005755c0
char RHScript::RHUnk5755c0(void *value)
{
    RHSound *sound = (RHSound *)*(void **)(g_unk0x6c0fa8 + 0x45e0);
    if (*(char *)((char *)sound + 0x20a))
        sound->FUN_005a88a0(value);
    return 1;
}

// FUNCTION: GAME 0x00579fa0
void RHScript::RecordDisplayPopupText(int value)
{
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 0x10, 0);
    element->Unk00586ed0(0x14, value);
    AddToSequence((RHSequenceElement *)element,
        // STRING: GAME 0x006b6530
        "RecordDisplayPopupText");
}

// FUNCTION: GAME 0x00575640
bool RHScript::Deactivate(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3919,
                 // STRING: GAME 0x006b455c
                 "Script Error: You tried to deactivate an illegal actor");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) == 2)
    {
        ((RHUnk004af1d0 *)actor)->Unk(false);
        return true;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
    {
        ((RHEngineWidenedCalls *)actor)->FUN_004e3660(false);
        for (int index = 0; index < 3; ++index)
            ((RHUnk00570e70Vtbl *)actor)->v92(0, 0, index, -1);
        g_unk0x6c0b3c->Unk(0);
        g_unk0x6c0b3c->Unk(1);
        g_unk0x6c0b3c->Unk(2);
        return true;
    }
    *(char *)((char *)actor + 0x12) = 0;
    return true;
}

// FUNCTION: GAME 0x005756f0
bool RHScript::Activate(void *actor)
{
    if (actor != 0 && RHUnk005709c0(actor))
    {
        if ((*(unsigned int *)((char *)actor + 4) & 3) == 2)
        {
            ((RHUnk004af1d0 *)actor)->Unk(true);
            return true;
        }
        if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
        {
            ((RHEngineWidenedCalls *)actor)->FUN_004e3660(true);
            return true;
        }
        *(char *)((char *)actor + 0x12) = 1;
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 3965,
             // STRING: GAME 0x006b4594
             "Script Error \"Activate\" : illegal actor");
    return false;
}

// FUNCTION: GAME 0x00575760
bool RHScript::SetActionAvailable(void *actor, int action, bool available)
{
    if (!IsActorPC(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4007,
                 "Script Error: Trying to set the availability of an actor who is not a playable one");
        return false;
    }
    if (action < 0 || action > 5)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4012,
                 // STRING: GAME 0x006b45bc
                 "Script Error: Trying to set the availability of an action that doesn't exist");
        return false;
    }
    if (available)
    {
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(29, actor, action));
        return true;
    }
    else
    {
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(28, actor, action));
        return true;
    }
}

// FUNCTION: GAME 0x00575870
bool RHScript::IsActionAvailable(void *actor, int action)
{
    if (!IsActorPC(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4047,
                 // STRING: GAME 0x006b460c
                 "Script Error: Trying to set the availability of an actor who is not a playable one");
        return 0;
    }
    char *entry = (char *)actor + (unsigned short)action;
    return *(char *)(entry + 0x508) == 0 && *(char *)(entry + 0x50b) == 0;
}

static inline void RHSetCameraCorner(SBGeoPoint2D &corner, float x, float y)
{
    corner.m_x = x;
    corner.m_y = y;
}

static inline void RHSetCameraCornerTruncated(SBGeoPoint2D &corner, float x, float y)
{
    float truncatedY = (float)(int)y;
    float truncatedX = (float)(int)x;
    RHSetCameraCorner(corner, truncatedX, truncatedY);
}

static inline float RHCameraValue(const char *engine, unsigned offset)
{
    return *(const float *)(engine + offset);
}

// FUNCTION: GAME 0x005758d0
SBGeoPoint2D RHUnk005758d0(const SBGeoPoint2D &point)
{
    SBGeoPoint2D corner;
    char *engine = g_unk0x6c0fa8;
    bool clampY = false;
    bool clampX = false;
    float &zoom = *(float *)(engine + 0x475c);
    RHSetCameraCornerTruncated(corner, point.m_x - RHCameraValue(engine, 0x4728) / (zoom + zoom),
                               point.m_y - RHCameraValue(engine, 0x472c) / (zoom + zoom));
    if (corner.m_x < 0.0f)
    {
        corner.m_x = 0;
        clampX = true;
    }
    if (corner.m_y < 0.0f)
    {
        corner.m_y = 0;
        clampY = true;
    }
    if (RHCameraValue(engine, 0x4728) / zoom + corner.m_x > RHCameraValue(engine, 0x4730))
    {
        if (clampX == true)
        {
            zoom = 1.0f;
            return SBGeoPoint2D(0.0f, 0.0f);
        }
        corner.m_x = RHCameraValue(engine, 0x4730) - RHCameraValue(engine, 0x4728) / zoom;
    }
    if ((RHCameraValue(engine, 0x472c) - 80.0f) / zoom + corner.m_y > RHCameraValue(engine, 0x4734))
    {
        if (clampY == true)
        {
            zoom = 1.0f;
            return SBGeoPoint2D(0.0f, 0.0f);
        }
        corner.m_y = RHCameraValue(engine, 0x4734) - (RHCameraValue(engine, 0x472c) - 80.0f) / zoom;
    }
    if (zoom == 0.5f)
    {
        if ((int)corner.m_x & 1)
            corner.m_x -= 1.0f;
        if ((int)corner.m_y & 1)
            corner.m_y -= 1.0f;
    }
    return corner;
}

// FUNCTION: GAME 0x00575af0
bool RHScript::SetAIAlertStatus(void *actor, int state)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4156,
                 // STRING: GAME 0x006b4700
                 "Script Error: Trying to set alert state of an invalid actor element.");
        return false;
    }
    unsigned int type = *(unsigned int *)((char *)actor + 4) & 15;
    if (type == 12)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4162,
                 // STRING: GAME 0x006b46cc
                 "Script Error: Trying to set alert state of a PC.");
        return false;
    }
    if (type != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4168,
                 // STRING: GAME 0x006b4694
                 "Script Error: Trying to set alert state of a non-NPC.");
        return false;
    }
    switch (state)
    {
    case 0:
        ((RHUnk00413640 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(0, false);
        return true;
    case 1:
        ((RHUnk00413640 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(1, false);
        return true;
    case 2:
        ((RHUnk00413640 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(2, false);
        return true;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4205,
                 // STRING: GAME 0x006b4660
                 "Script Error: Trying to set an illegal alert state.");
        return false;
    }
}

// FUNCTION: GAME 0x00575bf0
int RHScript::GetAIAlertStatus(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4225,
                 // STRING: GAME 0x006b4780
                 "Script Error: Trying to get alert state of an invalid actor element.");
        return 0;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4231,
                 // STRING: GAME 0x006b4748
                 "Script Error: Trying to get alert state of a non-NPC.");
        return 0;
    }
    char *object = *(char **)((char *)actor + 0x4a0 + (*(int **)((char *)actor + 0x49c))[1]);
    switch (*(int *)(object + 0x658))
    {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        return 0;
    }
}

// FUNCTION: GAME 0x00575c80
bool RHScript::SetAIState(void *actor, int state)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4276,
                 // STRING: GAME 0x006b491c
                 "Script Error: Trying to set AI state of an invalid actor element.");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4282,
                 // STRING: GAME 0x006b48e8
                 "Script Error: Trying to set AI state of a non-NPC.");
        return false;
    }
    switch (state)
    {
    case 0:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4289,
                 // STRING: GAME 0x006b48b0
                 "Script Error: Sleeping state cannot be set by script.");
        return false;
    case 1:
        ((RHUnk004169c0 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(1, 0);
        return true;
    case 3:
        if ((*(unsigned int *)((char *)actor + 4) & 31) == 20)
        {
            ((RHUnk004169c0 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(3, 0);
            return true;
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4304,
                 // STRING: GAME 0x006b487c
                 "Script Error: Seeking not implemented for civilists");
        return false;
    case 4:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4309,
                 // STRING: GAME 0x006b4834
                 "Script Error: Menacing state cannot be set by script. (Menace whom?)");
        return false;
    case 5:
        ((RHUnk004169c0 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(6, 0);
        return true;
    case 6:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4317,
                 // STRING: GAME 0x006b47ec
                 "Script Error: Attacking state cannot be set by script. (Attack whom?)");
        return false;
    case 7:
        ((RHUnk004169c0 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->v04(1, 14);
        return true;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4325,
                 // STRING: GAME 0x006b47c8
                 "Script Error: Illegal AI substate");
        return false;
    }
}

// FUNCTION: GAME 0x00575e20
int RHScript::GetAIState(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4347,
                 // STRING: GAME 0x006b4994
                 "Script Error: Trying to get AI state of an invalid actor element.");
        return 0;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4353,
                 // STRING: GAME 0x006b4960
                 "Script Error: Trying to get AI state of a non-NPC.");
        return 0;
    }
    switch (*(int *)((char *)actor + 0x4a8 + (*(int **)((char *)actor + 0x49c))[1]))
    {
    case 0: return 0;
    case 1: return 1;
    case 3: return 3;
    case 2: return 2;
    case 5: return 4;
    case 6: return 5;
    case 4: return 6;
    default: return 0;
    }
}

// FUNCTION: GAME 0x00575ee0
bool RHScript::SetAIAttitude(void *actor, int attitude)
{
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4402,
             // STRING: GAME 0x006b49d8
             "Script Error: SetAIAttitude does no more exist! Attitudes are now fix in the profiles and cannot be changed.");
    return false;
}

// FUNCTION: GAME 0x00575f00
int RHScript::GetAIAttitude(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4421,
                 // STRING: GAME 0x006b4a7c
                 "Script Error: Trying to get attitude of an invalid actor element.");
        return 0;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4427,
                 // STRING: GAME 0x006b4a48
                 "Script Error: Trying to get attitude of a non-NPC.");
        return 0;
    }
    switch (((RHUnk00570e70Vtbl *)actor)->v76())
    {
    case 0: return 0;
    case 1: return 1;
    default: return 0;
    }
}

// FUNCTION: GAME 0x00575f70
bool RHScript::SetAILevel(void *actor, int first, int second)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4462,
                 // STRING: GAME 0x006b4af8
                 "Script Error: Trying to set an AI level of an invalid actor element.");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4468,
                 // STRING: GAME 0x006b4ac0
                 "Script Error: Trying to set an AI level of a non-NPC.");
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x00575fc0
void RHScript::StareActor(void *actor, void *target, bool flag)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4496,
                 // STRING: GAME 0x006b4bd4
                 "Script Error: Trying to get stare actor command for an invalid actor element.");
        return;
    }
    if ((g_unk0x6c0f48 = RHScriptFindActor(target)) == -1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4502,
                 // STRING: GAME 0x006b4b7c
                 "Script Error: Trying to get stare actor command for an invalid target actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4508,
                 // STRING: GAME 0x006b4b40
                 "Script Error: Trying to stare actor command for a non-NPC.");
        return;
    }
    ((RHScriptBatchCalls *)actor)->Unk00486f50(target, flag);
}

// FUNCTION: GAME 0x005760b0
void RHScript::StareLocation(void *actor, void *location, bool flag)
{
    RHUnk00571160Position position;
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4533,
                 // STRING: GAME 0x006b4ca4
                 "Script Error: Trying to get stare location command for an invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4539,
                 // STRING: GAME 0x006b4c64
                 "Script Error: Trying to stare location command for a non-NPC.");
        return;
    }
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4546,
                 // STRING: GAME 0x006b4c24
                 "Script Error: You tried to stare at an illegal location type");
        return;
    }
    position.x = *(float *)((char *)location + 4);
    position.y = *(float *)((char *)location + 8);
    position.area = *(void **)((char *)location + 0x24);
    position.layer = *(short *)((char *)location + 0x20);
    ((RHScriptBatchCalls *)actor)->Unk00486f50(&position, true);
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00576170
void FUN_00576170()
{
    RHMessenger *messenger = RHUnk00546050();
    (*(RHUnk005ef320 **)(g_unk0x6c0fa8 + 0xdc))->FUN_005ef380(1);
    (*(RHGameActionCalls **)(g_unk0x6c0fa8 + 0xdc))->FUN_005e5260();
    messenger->RHUnk005460c0(RHUnk5490f0(36));
}

// FUNCTION: GAME 0x005761f0
bool FUN_005761f0()
{
    char *engine = (char *)g_pEngine;
    void **first = *(void ***)(engine + 0x495c);
    unsigned short count = first == 0 ? 0 : *(void ***)(engine + 0x4960) - first;
    for (unsigned int index = 0; (unsigned short)index < count; ++index)
    {
        void *actor = (*(void ***)((char *)g_pEngine + 0x495c))[(unsigned short)index];
        if (((RHUnk00570e70Vtbl *)actor)->v18())
        {
            if (((RHScriptActorKind *)((char *)actor + 4))->value == 4)
                return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00576260
bool FUN_00576260()
{
    char *engine = (char *)g_pEngine;
    void **first = *(void ***)(engine + 0x495c);
    unsigned short count = first == 0 ? 0 : *(void ***)(engine + 0x4960) - first;
    for (unsigned int index = 0; (unsigned short)index < count; ++index)
    {
        void *actor = (*(void ***)((char *)g_pEngine + 0x495c))[(unsigned short)index];
        if (((RHUnk00570e70Vtbl *)actor)->v18())
        {
            if (((RHScriptActorKind *)((char *)actor + 4))->value == 20)
                return true;
        }
    }
    return false;
}
}

// FUNCTION: GAME 0x005762d0
int RHScript::GetActorPosture(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4658,
                 // STRING: GAME 0x006b4d30
                 "Script Error: Trying to get the posture of an invalid actor.");
        return -1;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4666,
                 // STRING: GAME 0x006b4cf8
                 "Script Error: You can only get the posture of a human.");
        return -1;
    }
    switch (*(int *)(*(char **)((char *)actor + 0x50) + 0x8c))
    {
    case 1: return 0;
    case 3: return *(char *)((char *)actor + 0x1ce) ? 17 : 2;
    case 4: return 4;
    case 6: return 5;
    case 7: return ((RHUnk00570e70Vtbl *)actor)->v51() <= 0 ? 15 : 6;
    case 9: return 8;
    case 5: return 9;
    case 11: return 11;
    case 12: return 15;
    case 8: return 16;
    case 10: return 10;
    default: return 666;
    }
}

// FUNCTION: GAME 0x005763e0
void RHScript::SetActorPosture(void *actor, int posture)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4746,
                 // STRING: GAME 0x006b4e0c
                 "Script Error: Trying to set the posture of an invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4754,
                 // STRING: GAME 0x006b4dd4
                 "Script Error: You can only set the posture of a human.");
        return;
    }
    switch (posture)
    {
    case 0:
        if (*(int *)(*(char **)((char *)actor + 0x50) + 0x8c) != 3)
        {
            if (*(int *)(*(char **)((char *)actor + 0x50) + 0x8c) != 11)
            {
                ((RHUnk00570e70Vtbl *)actor)->v17(1);
                ((RHScriptBatchCalls *)actor)->Unk00464630();
                ((RHUnk00570e70Vtbl *)actor)->v55(0, 0, true);
            }
            else
            {
                ((RHUnk00570e70Vtbl *)actor)->v17(1);
                ((RHScriptBatchCalls *)actor)->Unk00464630();
            }
        }
        else
        {
            if ((*(unsigned int *)((char *)actor + 4) & 15) == 4)
                ((RHScriptBatchCalls *)actor)->Unk0048cbc0();
            ((RHUnk00570e70Vtbl *)actor)->v17(1);
            ((RHScriptBatchCalls *)actor)->Unk00464630();
            ((RHUnk00570e70Vtbl *)actor)->v55(0, 0, true);
        }
        return;
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
    case 11:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4794,
                 // STRING: GAME 0x006b4da0
                 "Script Error: Actually you cannot set posture %u", posture);
        return;
    case 2:
        ((RHUnk00570e70Vtbl *)actor)->v17(3);
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        ((RHUnk00570e70Vtbl *)actor)->v55(0, 0, true);
        return;
    case 7:
        if ((*(unsigned int *)((char *)actor + 4) & 15) == 4)
        {
            ((RHScriptBatchCalls *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk0040d980(15);
            ((RHElementActorNPC *)actor)->FUN_0048c4d0();
        }
        ((RHUnk00570e70Vtbl *)actor)->v17(18);
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    case 16:
        ((RHUnk00570e70Vtbl *)actor)->v17(8);
        ((RHUnk00570e70Vtbl *)actor)->v55(0, 0, true);
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    case 17:
        ((RHUnk0046bcb0 *)actor)->Unk(5);
        ((RHUnk00570e70Vtbl *)actor)->v17(3);
        ((RHUnk00570e70Vtbl *)actor)->v55(300, 0, true);
        if ((*(unsigned int *)((char *)actor + 4) & 15) == 4)
        {
            ((RHScriptBatchCalls *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk0040d980(15);
            ((RHElementActorNPC *)actor)->FUN_0048c4d0();
        }
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    case 15:
        ((RHUnk00570e70Vtbl *)actor)->v53(0, 0, true);
        ((RHScriptBatchCalls *)actor)->Unk0046bcf0(12, 0);
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    case 100:
        ((RHScriptBatchCalls *)actor)->Unk0046bcf0(23, 0);
        {
            RHUnk00613e90 effectPosition;
            ((RHScriptBatchCalls *)g_unk0x6c10e8)->Unk005c2ec0(&effectPosition, 0, 15, actor, 0, 0, 0, -1);
        }
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    case 10:
        ((RHScriptBatchCalls *)actor)->Unk0046bcf0(10, 0);
        ((RHScriptBatchCalls *)actor)->Unk00464630();
        return;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4849,
                 // STRING: GAME 0x006b4d70
                 "Script Error: Illegal ID %u for setting posture", posture);
        return;
    }
}

// FUNCTION: GAME 0x005766f0
int RHScript::GetActorActionState(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4863,
                 // STRING: GAME 0x006b4e90
                 "SO NICHT ! Script Error: Trying to get the action state of an invalid actor.");
        return -1;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4871,
                 // STRING: GAME 0x006b4e4c
                 "NEIN ! Script Error: You can only get the action state of a human.");
        return -1;
    }
    switch (*(int *)((char *)actor + 0x144))
    {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10: return 10;
    case 11: return 11;
    case 12: return 12;
    case 13: return 13;
    case 14: return 14;
    case 15: return 15;
    case 16: return 16;
    case 17: return 17;
    default: return 666;
    }
}

// FUNCTION: GAME 0x00576830
void RHScript::SetActorActionState(void *actor, int state)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4948,
                 // STRING: GAME 0x006b4f24
                 "SO NICHT ! Script Error: Trying to set the action state of an invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 4956,
                 // STRING: GAME 0x006b4ee0
                 "NEIN ! Script Error: You can only set the action state of a human.");
        return;
    }
    switch (state)
    {
    case 0: ((RHScriptBatchCalls *)actor)->Unk0046bd10(0); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 1: ((RHScriptBatchCalls *)actor)->Unk0046bd10(1); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 2: ((RHScriptBatchCalls *)actor)->Unk0046bd10(2); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 3: ((RHScriptBatchCalls *)actor)->Unk0046bd10(3); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 4: ((RHScriptBatchCalls *)actor)->Unk0046bd10(4); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 5: ((RHScriptBatchCalls *)actor)->Unk0046bd10(5); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 6: ((RHScriptBatchCalls *)actor)->Unk0046bd10(6); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 7: ((RHScriptBatchCalls *)actor)->Unk0046bd10(7); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 8: ((RHScriptBatchCalls *)actor)->Unk0046bd10(8); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 9: ((RHScriptBatchCalls *)actor)->Unk0046bd10(9); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 10: ((RHScriptBatchCalls *)actor)->Unk0046bd10(10); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 11: ((RHScriptBatchCalls *)actor)->Unk0046bd10(11); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 12: ((RHScriptBatchCalls *)actor)->Unk0046bd10(12); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 13: ((RHScriptBatchCalls *)actor)->Unk0046bd10(13); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 14: ((RHScriptBatchCalls *)actor)->Unk0046bd10(14); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 15: ((RHScriptBatchCalls *)actor)->Unk0046bd10(15); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 16: ((RHScriptBatchCalls *)actor)->Unk0046bd10(16); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    case 17: ((RHScriptBatchCalls *)actor)->Unk0046bd10(17); ((RHScriptBatchCalls *)actor)->Unk00464630(); break;
    }
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00576a30
int FUN_00576a30()
{
    int result = 0;
    unsigned short count = ((RHScriptNPCArray *)g_pEngine)->Count();
    int state;
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = ((RHScriptNPCArray *)g_pEngine)->first[index];
        if (!((RHUnk00570e70Vtbl *)actor)->v18())
        {
            if (((RHScriptActorKind *)((char *)actor + 4))->value == 20)
            {
                char *base = (char *)actor + (*(int **)((char *)actor + 0x49c))[1];
                switch (*(int *)(*(char **)(base + 0x4a0) + 0x658))
                {
                case 0: state = 0; break;
                case 1: state = 1; break;
                case 2: state = 2; break;
                }
                if (state > result)
                    result = state;
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x00576af0
int FUN_00576af0()
{
    int result = 0;
    unsigned short count = ((RHScriptNPCArray *)g_pEngine)->Count();
    int state;
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = ((RHScriptNPCArray *)g_pEngine)->first[index];
        if (!((RHUnk00570e70Vtbl *)actor)->v18())
        {
            if (((RHScriptActorKind *)((char *)actor + 4))->value != 20)
            {
                char *base = (char *)actor + (*(int **)((char *)actor + 0x49c))[1];
                switch (*(int *)(*(char **)(base + 0x4a0) + 0x658))
                {
                case 0: state = 0; break;
                case 1: state = 1; break;
                case 2: state = 2; break;
                }
                if (state > result)
                    result = state;
            }
        }
    }
    return result;
}
}

// FUNCTION: GAME 0x00576bb0
void RHScript::Freeze(void *actor, bool frozen)
{
    if (!RHUnk005709c0(actor))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5192,
                 // STRING: GAME 0x006b4fbc
                 "Script Error: Trying to freeze invalid actor element.");
    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5197,
                 // STRING: GAME 0x006b4f74
                 "Script Error: Trying to freeze a non-human. (Fried chicken not allowed)");
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
        *(char *)((char *)actor + 0x6e4) = frozen;
    else
        *(char *)((char *)actor + 0x58c) = frozen;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00576c30
void FUN_00576c30(bool value)
{
    *(bool *)((char *)g_pEngine + 0x4d84) = value;
}
}

// FUNCTION: GAME 0x00576c50
void RHScript::AssignPath(void *actor, void *path)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5242,
                 // STRING: GAME 0x006b502c
                 "Script Error: Trying to set patrol path for invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5248,
                 // STRING: GAME 0x006b4ff4
                 "Script Error: Trying to set patrol path for non-NPC.");
        return;
    }
    ((RHScriptBatchCalls *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk004188f0(path);
}

// FUNCTION: GAME 0x00576cc0
void RHScript::AssignPost(void *actor, void *location, int direction)
{
    RHUnk00571160Position position;
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5273,
                 // STRING: GAME 0x006b50a0
                 "Script Error: Trying to set post for invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5279,
                 // STRING: GAME 0x006b5070
                 "Script Error: Trying to set post for non-NPC.");
        return;
    }
    position.x = *(float *)((char *)location + 4);
    position.y = *(float *)((char *)location + 8);
    position.area = *(void **)((char *)location + 0x24);
    position.layer = *(short *)((char *)location + 0x20);
    ((RHScriptBatchCalls *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk00418a80(position, direction);
}

// FUNCTION: GAME 0x00576d80
void RHScript::LockAI(void *actor, bool flag)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5304,
                 // STRING: GAME 0x006b510c
                 "Script Error: You tried to lock the AI of an illegal actor");
        return;
    }
    unsigned int type = *(unsigned int *)((char *)actor + 4);
    if ((type & 15) == 4)
    {
        ((RHUnk00418b80 *)((char *)actor + 0x49c + (*(int **)((char *)actor + 0x49c))[1]))->Unk(flag);
        return;
    }
    if ((type & 7) == 0)
    {
        *(char *)((char *)actor + 0x1c5) = 1;
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5318,
             // STRING: GAME 0x006b50dc
             "Script Error: You tried to lock the AI of a PC.");
}

// FUNCTION: GAME 0x00576e00
void RHScript::UnlockAI(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5339,
                 // STRING: GAME 0x006b51c0
                 "Script Error: You tried to unlock the AI of an illegal actor");
        return;
    }
    unsigned int type = *(unsigned int *)((char *)actor + 4);
    if ((type & 15) == 4)
    {
        char *base = (char *)actor + (*(int **)((char *)actor + 0x49c))[1];
        if (*(char *)(base + 0x660))
        {
            ((RHScriptBatchCalls *)(base + 0x49c))->Unk00418bc0();
            return;
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5351,
                 // STRING: GAME 0x006b517c
                 "Script Error: You tried to unlock the AI a NPC which is not locked.");
        return;
    }
    if ((type & 7) == 0)
    {
        *(char *)((char *)actor + 0x1c5) = 0;
        ((RHElementActorAnimal *)actor)->ThisIsYourNewHome();
        ((RHElementActorAnimal *)actor)->Think((RHanimalStimulusType)3);
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5361,
             // STRING: GAME 0x006b5148
             "Script Error: You tried to unlock the AI of a PC.");
}

// FUNCTION: GAME 0x00576eb0
void RHScript::ForceBattleDecision(void *actor, int decision)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5386,
                 // STRING: GAME 0x006b5280
                 "Script Error: You tried to force battle decision of an illegal actor");
        return;
    }
    bool persistent;
    if (decision >= 100)
    {
        persistent = true;
        decision -= 100;
    }
    else
        persistent = false;
    if ((*(unsigned int *)((char *)actor + 4) & 31) == 20)
    {
        int state;
        switch (decision)
        {
        case 0: state = 3; break;
        case 1: state = 4; break;
        case 2: state = 5; break;
        case 3: state = 6; break;
        case 4: state = 7; break;
        case 5: state = 8; break;
        case 6: state = 9; break;
        case 7: state = 10; break;
        case 8: state = 11; break;
        case 9: state = 12; break;
        case 10: state = 13; break;
        case 11: state = 14; break;
        case 12: state = 15; break;
        case 13: state = 16; break;
        case 14: state = 17; break;
        case 15: state = 18; break;
        case 16: state = 19; break;
        case 99: state = 0; break;
        default:
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5478,
                     // STRING: GAME 0x006b5244
                     "Script Error: Illegal identifier %u for battle decision.", decision);
            return;
        }
        *(int *)((char *)actor + 0xa14) = state;
        *(bool *)((char *)actor + 0xa18) = !persistent;
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5486,
             // STRING: GAME 0x006b5200
             "Script Error: You tried to force battle decisions of a non-Soldier.");
}

// FUNCTION: GAME 0x005770b0
void RHScript::SetGlobal(int index, int value)
{
    if (!((RHScriptBatchCalls *)g_pEngine)->Unk004e3e30(index))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5522,
                 // STRING: GAME 0x006b52c8
                 "Script Error: Non-valid ID for script global");
        return;
    }
    ((RHScriptBatchCalls *)g_pEngine)->Unk004e3e00(index, value);
}

// FUNCTION: GAME 0x00577100
int RHScript::GetGlobal(int index)
{
    if (!((RHScriptBatchCalls *)g_pEngine)->Unk004e3e30(index))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5544,
                 "Script Error: Non-valid ID for script global");
        return -1;
    }
    return ((RHScriptBatchCalls *)g_pEngine)->Unk004e3e20(index);
}

// FUNCTION: GAME 0x00577150
bool RHScript::CleanFromHisBuildingBeforeTeleport(void *actor)
{
    if ((g_unk0x6c0f48 = RHScriptFindActor(actor)) != -1 &&
        (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        char *area = *(char **)(*(char **)((char *)actor + 0x50) + 0xe0);
        unsigned short flags = *(unsigned int *)(area + 0x30) >> 13;
        if (!(flags & 1))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5577,
                     // STRING: GAME 0x006b533c
                     "Script Error: You tried to clean an actor from a building who was on open air");
            return false;
        }
        ((RHSectorBuilding *)area)->Leave((RHElementActor *)actor);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5569,
             // STRING: GAME 0x006b52f8
             "Script Error: You tried to clean an illegal actor from a building");
    return false;
}

// FUNCTION: GAME 0x00577220
bool RHScript::CleanFromScriptZoneBeforeTeleport(void *actor, void *zone)
{
    if (zone != 0)
    {
        if (*(int *)((char *)zone + 0xbc) != 2)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5613,
                     // STRING: GAME 0x006b5424
                     "Script Error: You tried to clean an actor from an illegal script zone");
            return false;
        }
        if ((g_unk0x6c0f48 = RHScriptFindActor(actor)) != -1 &&
            (*(unsigned int *)((char *)actor + 4) & 3) == 0)
        {
            if (((RHScriptZoneList *)((char *)zone + 0xcc))->Find(actor) == -1)
            {
                SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5627,
                         // STRING: GAME 0x006b53d4
                         "Script Error: You tried to clean an actor from a script zone who wasn't inside");
                return false;
            }
            ((RHSectorScript *)zone)->Leave((RHElementActor *)actor);
            return true;
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5619,
                 // STRING: GAME 0x006b538c
                 "Script Error: You tried to clean an illegal actor from a script zone");
    }
    return false;
}

// FUNCTION: GAME 0x00577390
bool RHScript::AddToScriptZoneAfterTeleport(void *actor, void *zone)
{
    if (zone != 0)
    {
        if (*(int *)((char *)zone + 0xbc) != 2)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5663,
                     // STRING: GAME 0x006b54fc
                     "Script Error: You tried to add an actor to an illegal script zone");
            return false;
        }
        if ((g_unk0x6c0f48 = RHScriptFindActor(actor)) != -1 &&
            (*(unsigned int *)((char *)actor + 4) & 3) == 0)
        {
            if (((RHScriptZoneList *)((char *)zone + 0xcc))->Find(actor) == -1)
            {
                SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5677,
                         // STRING: GAME 0x006b54b0
                         "Script Error: You tried to add an actor to a script zone who wasn't inside");
                return false;
            }
            ((RHSectorScript *)zone)->Enter((RHElementActor *)actor);
            return true;
        }
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5669,
                 // STRING: GAME 0x006b546c
                 "Script Error: You tried to add an illegal actor to a script zone");
    }
    return false;
}

// FUNCTION: GAME 0x00577500
bool RHScript::InflictPain(void *actor, int amount, bool flag)
{
    if ((g_unk0x6c0f48 = RHScriptFindActor(actor)) != -1 &&
        (*(unsigned int *)((char *)actor + 4) & 3) == 0)
    {
        RHUnk005861c0 *element;
        if (flag)
            element = new RHUnk005861c0(1, 38, actor, amount, 100);
        else
            element = new RHUnk005861c0(1, 38, actor, amount, 0);
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5707,
             // STRING: GAME 0x006b5540
             "Script Error: You can only inflict pain to actor");
    return false;
}

// 76.03%.
// Scalar height preserves x87 flow; named height changes it. Temporary/EH slots and scheduling remain unresolved.
// STUB: GAME 0x00577650
bool RHScript::RecordEnterGame(void *actor, void *location, int direction, int style)
{
    SBGeoPoint2D point;
    RHUnk00613e90 projection;
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    if (*(int *)((char *)location + 0x18) != 0)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5761,
                 "Script Error: You tried to create a move sequence with an illegal location type");
    else if (actor == 0 || (*(unsigned int *)((char *)actor + 4) & 3) != 0)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5767,
                 "Script Error: You tried to create a move sequence with an illegal actor");
    else if (style != 0 && style != 1)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5773,
                 "Script Error: You tried to create a move sequence with an illegal style");
    else
    {
        unsigned int index = 0;
        int count = g_unk0x6c0f50.count;
        for (; (unsigned short)index < (unsigned short)count; ++index)
        {
            ((RHSeqList *)&g_unk0x6c0f50)->GoTo((unsigned short)index);
            if (actor == g_unk0x6c0f50.cursor->data)
                break;
        }
        const SBGeoPoint2D *destination = (SBGeoPoint2D *)((char *)location + 4);
        RHUnk00571160Position position;
        position.x = *(float *)((char *)location + 4);
        position.y = *(float *)((char *)location + 8);
        position.area = *(void **)((char *)location + 0x24);
        position.layer = *(short *)((char *)location + 0x20);
        if ((unsigned short)index < (unsigned short)count)
        {
            ((RHSeqList *)&g_unk0x6c0fb0)->GoTo((unsigned short)index);
            *(RHUnk00571160Position *)&g_unk0x6c0fb0.cursor->data = position;
        }
        else
        {
            g_unk0x6c0fb0.Unk0057c950(RHScriptIter(g_unk0x6c0fb0.head), position);
            g_unk0x6c0fb0.valid = true;
            RHOrder *value = (RHOrder *)actor;
            ((RHUnkList *)&g_unk0x6c0f50)->insert(RHUnkIter(g_unk0x6c0f50.head), value);
            g_unk0x6c0f50.valid = true;
            unsigned short enterDirection = direction == -1 ? *(unsigned short *)(*(char **)((char *)actor + 0x50) + 0xd8) : direction;
            ((RHScriptRecordWorld *)g_unk0x6c0a9c)->Unk004fc8f0(first, second, location == 0 ? 0 : destination, enterDirection);
            float height = ((RHScriptRecordWorld *)g_unk0x6c0a9c)->Unk004fbdd0(position).z;
            projection.x = second.m_x;
            projection.y = second.m_y + height;
            projection.z = height;
            if (*(char *)((char *)actor + 0x88))
            {
                *(char *)((char *)actor + 0x12) = 1;
                *(char *)((char *)actor + 0x88) = 0;
            }
            char *sprite = *(char **)((char *)actor + 0x50) + 4;
            *(RHUnk00613e90 *)(sprite + 0xc) = projection;
            *(int *)(sprite + 4) = 1;
            sprite = *(char **)((char *)actor + 0x50) + 4;
            *(short *)(sprite + 0xda) = position.layer;
            sprite = *(char **)((char *)actor + 0x50) + 4;
            *(void **)(sprite + 0xdc) = position.area;
            ((RHBonusInfoBase *)(*(char **)((char *)actor + 0x50) + 4))->FUN_0055f290();
        }
        RHUnk005883a0 *element = new RHUnk005883a0(g_unk0x6c0fa4++, 20, actor, style != 0 ? 10 : 6,
            SBGeoPoint2D(*(float *)destination, *(float *)((char *)location + 8)), 0, 0, 2);
        --g_unk0x6c0fa4;
        AddToSequence((RHSequenceElement *)element,
                      // STRING: GAME 0x006b5574
                      "RecordEnterGame");
    }
    return false;
}

// 87.82%.
// Aggregate position copying introduces a 16-byte spill; payload scheduling and branch layout remain unresolved.
// STUB: GAME 0x005779a0
bool RHScript::RecordLeaveGame(void *actor, void *location, int direction, int style)
{
    SBGeoPoint2D point;
    RHUnk00571160Position destinationPosition;
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5877,
                 "Script Error: You tried to create a move sequence with an illegal location type");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5883,
                 "Script Error: You tried to create a move sequence with an illegal actor");
        return false;
    }
    if (style != 0 && style != 1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5889,
                 "Script Error: You tried to create a move sequence with an illegal style");
        return false;
    }
    unsigned int index = 0;
    int count = g_unk0x6c0f50.count;
    RHUnk00571160Position start;
    for (; (unsigned short)index < (unsigned short)count; ++index)
    {
        ((RHSeqList *)&g_unk0x6c0f50)->GoTo((unsigned short)index);
        if (actor == g_unk0x6c0f50.cursor->data)
            break;
    }
    if ((unsigned short)index < (unsigned short)count)
    {
        ((RHSeqList *)&g_unk0x6c0fb0)->GoTo((unsigned short)index);
        start = *(RHUnk00571160Position *)&g_unk0x6c0fb0.cursor->data;
    }
    else
    {
        ((RHUnk00560420 *)(*(char **)((char *)actor + 0x50) + 4))->Unk(&start);
        destinationPosition.x = *(float *)((char *)location + 4);
        destinationPosition.y = *(float *)((char *)location + 8);
        destinationPosition.area = *(void **)((char *)location + 0x24);
        destinationPosition.layer = *(short *)((char *)location + 0x20);
        RHScriptNode *head = g_unk0x6c0fb0.head;
        RHScriptNode *node = ((RHScriptPositionList *)&g_unk0x6c0fb0)->Unk004242b0(head, head->prev);
        head->prev = node;
        node->prev->next = node;
        RHScriptPositionList::Unk00588190((RHUnk00571160Position *)&node->data, &destinationPosition);
        ++g_unk0x6c0fb0.count;
        g_unk0x6c0fb0.valid = true;
        head = g_unk0x6c0f50.head;
        RHSequenceElement *value = (RHSequenceElement *)actor;
        node = g_unk0x6c0f50.Unk0059f720(head, head->prev);
        head->prev = node;
        node->prev->next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->data, &value);
        ++g_unk0x6c0f50.count;
        g_unk0x6c0f50.valid = true;
    }
    const SBGeoPoint2D *destination = location != 0 ? (SBGeoPoint2D *)((char *)location + 4) : 0;
    void *area = *(void **)((char *)location + 0x24);
    unsigned short layer = *(unsigned short *)((char *)location + 0x20);
    ((RHUnk00582640 *)g_unk0x6c0f78)->Unk(g_unk0x6c0fa4, actor, style != 0 ? 10 : 6,
        SBGeoPoint2D(start.x, start.y), start.area, start.layer,
        *destination, area, layer, 0, 0.0f, 0, 1.0f);
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    unsigned short exitDirection = direction == -1 ? *(unsigned short *)(*(char **)((char *)actor + 0x50) + 0xd8) : direction;
    ((RHScriptRecordWorld *)g_unk0x6c0a9c)->Unk004fc8f0(first, second,
        location != 0 ? (SBGeoPoint2D *)((char *)location + 4) : 0, (unsigned char)(exitDirection - 8) & 15);
    RHUnk005883a0 *element = new RHUnk005883a0(g_unk0x6c0fa4++, 20, actor, style != 0 ? 10 : 6, second, 0, 0, 2);
    ((RHUnk00585500 *)element)->Unk(g_unk0x6c0f78);
    --g_unk0x6c0fa4;
    return true;
}

// FUNCTION: GAME 0x00577d30
bool RHScript::RecordActionAvailable(void *actor, int action, bool available)
{
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 5991,
                 // STRING: GAME 0x006b559c
                 "Script Error: You tried to create a action available sequence with an illegal actor");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 79, actor);
    element->Unk00586ed0(11, action);
    element->Unk00586e00(12, available);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b5584
                         "RecordActionAvailable");
}

// FUNCTION: GAME 0x00577e70
bool RHScript::RecordCharacterAvailable(void *actor, bool available)
{
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6031,
                 "Script Error: You tried to create a action available sequence with an illegal actor");
        return false;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 80, actor);
    element->Unk00586e00(13, available);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b5600
                         "RecordCharacterAvailable");
}

// FUNCTION: GAME 0x00577f30
bool RHScript::RecordLockCameraOn(void *actor)
{
    if ((*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6058,
                 "Script Error: You tried to create a move sequence with an illegal actor");
        return false;
    }
    RHUnk00585ea0 *element = new RHUnk00585ea0(g_unk0x6c0fa4, 13, 0, actor);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b561c
                         "RecordLockCameraOn");
}

extern RHElementActor *g_unk0x6c100c;

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00577fe0
bool FUN_00577fe0()
{
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 14, 0);
    return RHScript::AddToSequence((RHSequenceElement *)element,
                                  // STRING: GAME 0x006b5630
                                  "RecordClearCameraLock");
}

// FUNCTION: GAME 0x00578050
int FUN_00578050()
{
    return (int)g_unk0x6c100c;
}
}

// FUNCTION: GAME 0x00578060
int RHScript::GetCurrentAction(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6118,
                 // STRING: GAME 0x006b5680
                 "Script Error: Trying to get animation of an invalid actor element.");
        return 0;
    }
    unsigned int type = *(unsigned int *)((char *)actor + 4) & 3;
    if (type == 3)
        return *(int *)((char *)actor + 0xb4);
    if (type != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6129,
                 // STRING: GAME 0x006b5648
                 "Script Error: GetAction only available for real actors.");
        return 0;
    }
    char *action = *(char **)((char *)actor + 0x134);
    if (action == 0)
        return 283;
    return *(int *)(action + 0x24);
}

// FUNCTION: GAME 0x005780d0
void RHScript::SetPathWalkingStyle(void *actor, int style)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6153,
                 // STRING: GAME 0x006b5704
                 "Script Error: Trying to set path walking style of an invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6159,
                 // STRING: GAME 0x006b56c4
                 "Script Error: Trying to set path walking style of a non-NPC.");
        return;
    }
    int value;
    switch (style)
    {
    case 0: value = 0; break;
    case 1: value = 1; break;
    }
    int offset = *(int *)(*(char **)((char *)actor + 0x49c) + 4);
    ((RHScriptBatchCalls *)((char *)actor + offset + 0x49c))->Unk0041bd20(value);
}

// FUNCTION: GAME 0x00578160
bool RHScript::Sees(void *actor, void *target)
{
    if (!RHUnk005709c0(actor))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6192,
                 // STRING: GAME 0x006b581c
                 "Script Error: Trying to test if an invalid actor element sees another actor.");
    else if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6198,
                 // STRING: GAME 0x006b57d4
                 "Script Error: Trying to test if a non-NPC element sees another actor.");
    else if (!RHUnk005709c0(target))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6204,
                 // STRING: GAME 0x006b578c
                 "Script Error: Trying to test if a NPC sees an invalid actor element.");
    else if ((*(unsigned int *)((char *)target + 4) & 7) != 4)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6210,
                 // STRING: GAME 0x006b5750
                 "Script Error: Trying to test if a NPC sees an non-human.");
    else
        return ((RHScriptBatchCalls *)actor)->Unk00489e80(target);
    return false;
}

// FUNCTION: GAME 0x005781f0
void RHScript::PutActorInBulding(void *actor, void *building)
{
    ((RHSeqList *)((char *)building + 0x80))->GoTo(0);
    RHSeqList *list = (RHSeqList *)((char *)building + 0x5c);
    list->GoTo(0);
    char *location = (char *)list->cursor->data;
    if (actor == 0 || (*(unsigned int *)((char *)actor + 4) & 3) != 0)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6292,
                 // STRING: GAME 0x006b586c
                 "CA VA PAS LA TETE ? Trying to put actor NULL inside a building !");
    RHScriptPositionFields *position = ((RHScriptActorPositionFields *)actor)->position;
    *(char *)((char *)actor + 0x12) = 0;
    position->layer = *(short *)((char *)g_unk0x6c0a9c + 0x3e9c);
    ((RHScriptActorPositionFields *)actor)->position->area = building;
    ((RHActorPositionCalls *)((char *)((RHScriptActorPositionFields *)actor)->position + 4))->FUN_00464530(*(SBGeoPoint2D *)(location + 0x20));
    ((RHBonusInfoBase *)((char *)((RHScriptActorPositionFields *)actor)->position + 4))->FUN_0055f290();
    ((RHSectorBuilding *)building)->Enter((RHElementActor *)actor);
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
        ((RHScriptBatchCalls *)actor)->Unk0049d6c0();
}

// Parked: iterator/cursor register scheduling remains different after three source shapes.
// STUB: GAME 0x005782a0
void FUN_005782a0(void *object, bool value)
{
    *(bool *)((char *)object + 0x34) = value;
    RHUnk0046eb30 *list = (RHUnk0046eb30 *)((char *)object + 0x5c);
    int remaining = (unsigned short)*(int *)((char *)list + 8);
    int index = 0;
    while (remaining != 0)
    {
        *(bool *)((char *)list->Get(index) + 8) = value;
        ++index, --remaining;
    }
}

// FUNCTION: GAME 0x005783b0
bool RHScript::RecordStartMobileElement(int index)
{
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x9c,
        (*(std::vector<void *> *)((char *)g_pEngine + 0x4978))[index]);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b58b0
                         "RecordStartMobileElement");
}

// FUNCTION: GAME 0x00578430
bool RHScript::RecordStopMobileElement(int index)
{
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x9d,
        (*(std::vector<void *> *)((char *)g_pEngine + 0x4978))[index]);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b58cc
                         "RecordStopMobileElement");
}

// FUNCTION: GAME 0x005784b0
bool RHScript::RecordActivateMobileElement(int index)
{
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x9e,
        (*(std::vector<void *> *)((char *)g_pEngine + 0x4978))[index]);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b58e4
                         "RecordActiveMobileElement");
}

// FUNCTION: GAME 0x00578530
bool RHScript::RecordDeactivateMobileElement(int index)
{
    RHUnk00584d60 *element = new RHUnk00584d60(g_unk0x6c0fa4, 0x9f,
        (*(std::vector<void *> *)((char *)g_pEngine + 0x4978))[index]);
    return AddToSequence((RHSequenceElement *)element,
                         // STRING: GAME 0x006b5900
                         "RecordDeactivateMobileElement");
}

// FUNCTION: GAME 0x005785b0
void FUN_005785b0(void *first, void *second)
{
    RHUnk005a2450 *manager =
        (RHUnk005a2450 *)((RHUnk004e3760 *)g_unk0x6c0fa8)->Get();
    manager->FUN_005a2450(first, second);
}

class RHShortBriefings
{
public:
    void DoneShortBriefing(unsigned long id);
};

// FUNCTION: GAME 0x005785d0
void FUN_005785d0(void *value)
{
    RHShortBriefings *manager =
        (RHShortBriefings *)((RHUnk004e3760 *)g_unk0x6c0fa8)->Get();
    manager->DoneShortBriefing((unsigned long)value);
}

// FUNCTION: GAME 0x005785f0
void RHScript::AttachScrollToNPC(void *actor, void *scroll)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 15) == 4)
    {
        if (scroll == 0)
        {
            ((RHScriptBatchCalls *)actor)->Unk0048ec00(scroll);
            return;
        }
        if ((*(unsigned int *)((char *)scroll + 4) & 3) != 3 || *(int *)((char *)scroll + 0xb0) != 12)
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6480,
                     // STRING: GAME 0x006b5958
                     "Script Error: Trying to attach invalid scroll to NPC");
        ((RHScriptBatchCalls *)actor)->Unk0048ec00(scroll);
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6468,
             // STRING: GAME 0x006b5920
             "Script Error: Trying to attach a scroll to invalid NPC");
}

// FUNCTION: GAME 0x005786b0
void RHScript::EnableViewCone(void *actor)
{
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6551,
                 // STRING: GAME 0x006b5990
                 "Script Error: Trying to enable the view cone of an element which is not a NPC.");
    ((RHScriptBatchCalls *)g_pEngine)->Unk004d9330(actor, false);
}

// FUNCTION: GAME 0x00578710
bool RHScript::Select(int code)
{
    if (code == 31)
    {
        RHUnk00546050()->RHUnk005460c0(RHUnk00549250(13, 0));
        return true;
    }
    if (code == 0)
    {
        RHUnk00546050()->RHUnk005460c0(RHUnk00549250(18, 0));
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6608,
             // STRING: GAME 0x006b59e0
             "Script Error: For the method Select, currently only codes 31 (select all) and 0 (select none) are supported.");
    return true;
}

// FUNCTION: GAME 0x005787f0
void RHScript::ActivateDoorMouseSector(bool active, void *door)
{
    if (door != 0)
    {
        *(bool *)(*(char **)((char *)door + 0xac) + 0x34) = active;
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6623,
             // STRING: GAME 0x006b5a50
             "Door for activation not found !");
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00578820
unsigned char FUN_00578820()
{
    return *((unsigned char *)RHUnk00546050() + 0x17);
}
}

// FUNCTION: GAME 0x005788a0
void RHScript::CustomizeMinimapDisplay(void *actor, int code)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6683,
                 // STRING: GAME 0x006b5b04
                 "Script Error: Trying to customize minimap display of invalid actor.");
        return;
    }
    switch (code)
    {
    case 111:
    case 222:
    case 333:
        if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6694,
                     // STRING: GAME 0x006b5ab8
                     "Script Error: Minimap display codes 111, 222, 333 only valid for humans.");
            return;
        }
    case 0:
    case 1:
    case 100:
    case 101:
    case 102:
    case 200:
    case 201:
    case 202:
    case 300:
    case 301:
    case 302:
    case 500:
    case 666:
        *(short *)((char *)actor + 0x8c) = code;
        break;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6714,
                 // STRING: GAME 0x006b5a70
                 "Script Error: Trying to customize minimap display with illegal dot ID.");
        break;
    }
    switch (code)
    {
    case 100:
    case 101:
    case 102:
    case 111:
        *(short *)((char *)actor + 0x94) = g_unk0x6c11d0->Unk(165, 255, 82);
        *(short *)((char *)actor + 0x98) = g_unk0x6c11d0->Unk(165, 255, 82);
        *(short *)((char *)actor + 0x96) = g_unk0x6c11d0->Unk(165, 255, 82);
        break;
    case 200:
    case 201:
    case 202:
    case 222:
        *(short *)((char *)actor + 0x94) = g_unk0x6c11d0->Unk(255, 0, 0);
        *(short *)((char *)actor + 0x98) = g_unk0x6c11d0->Unk(255, 0, 0);
        *(short *)((char *)actor + 0x96) = g_unk0x6c11d0->Unk(255, 0, 0);
        break;
    case 300:
    case 301:
    case 302:
    case 333:
        *(short *)((char *)actor + 0x94) = g_unk0x6c11d0->Unk(0, 190, 255);
        *(short *)((char *)actor + 0x98) = g_unk0x6c11d0->Unk(0, 190, 255);
        *(short *)((char *)actor + 0x96) = g_unk0x6c11d0->Unk(0, 190, 255);
        break;
    }
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00578c60
void FUN_00578c60()
{
    *(g_unk0x6c0fa8 + 0x4a56) = 1;
}
}

// FUNCTION: GAME 0x00578c70
void RHScript::DefineFlatTrajectoryZone(void *sector, int height)
{
    if (sector != 0 && *(char *)((char *)sector + 0xb8) == 0)
    {
        ((RHScriptBatchCalls *)sector)->Unk0057ff70((float)height);
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6808,
             // STRING: GAME 0x006b5b48
             "ESPECE DE PUNK : Trying to force emergency box on a sector that is not a motion area !");
}

// FUNCTION: GAME 0x00578cb0
void RHScript::RecordSendMessage(void *actor, int message)
{
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6828,
                 // STRING: GAME 0x006b5bd0
                 "Script Error : trying to send a message to non actor object.");
        return;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 15, actor);
    element->Unk00586ed0(3, message);
    element->Unk00586ed0(4, 0);
    element->Unk00586ed0(5, 0);
    AddToSequence((RHSequenceElement *)element,
                  // STRING: GAME 0x006b5ba0
                  "RecordSendMessage");
}

// FUNCTION: GAME 0x00578d80
void RHScript::SendMessage(void *actor, int message)
{
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6849,
                 "Script Error : trying to send a message to non actor object.");
        return;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 15, actor);
    element->Unk00586ed0(3, message);
    element->Unk00586ed0(4, 0);
    element->Unk00586ed0(5, 0);
    ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
}

// FUNCTION: GAME 0x00578e50
void RHScript::RecordSendMessageWithArguments(void *actor, int message, int first, int second)
{
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6882,
                 "Script Error : trying to send a message to non actor object.");
        return;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 15, actor);
    element->Unk00586ed0(3, message);
    element->Unk00586ed0(4, first);
    element->Unk00586ed0(5, second);
    AddToSequence((RHSequenceElement *)element,
                  // STRING: GAME 0x006b5c10
                  "RecordSendMessageWithArguments");
}

// FUNCTION: GAME 0x00578f20
void RHScript::SendMessageWithArguments(void *actor, int message, int first, int second)
{
    if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 3) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6903,
                 "Script Error : trying to send a message to non actor object.");
        return;
    }
    RHUnk005866a0 *element = new RHUnk005866a0(g_unk0x6c0fa4, 15, actor);
    element->Unk00586ed0(3, message);
    element->Unk00586ed0(4, first);
    element->Unk00586ed0(5, second);
    ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x00579000
void FUN_00579000(int identifier, int location)
{
    char *engine = (char *)g_pEngine;
    void **first = *(void **volatile *)(engine + 0x493c);
    unsigned count = (unsigned char)(first == 0 ? 0 : *(void ***)(engine + 0x4940) - first);
    for (unsigned index = 0; index < count; ++index)
    {
        void *actor = (*(void ***)(engine + 0x493c))[(unsigned char)index];
        if (*(unsigned short *)((char *)actor + 0x4ea) == identifier)
        {
            ((RHActorPositionCalls *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00464530(
                *(SBGeoPoint2D *)(location ? location + 4 : 0));
            *(unsigned short *)(*(char **)((char *)actor + 0x50) + 0xde) = *(unsigned short *)(location + 0x20);
            *(void **)(*(char **)((char *)actor + 0x50) + 0xe0) = *(void **)(location + 0x24);
            ((RHBonusInfoBase *)(*(char **)((char *)actor + 0x50) + 4))->FUN_0055f290();
            ((RHBonusInfo *)*(void **)((char *)actor + 0x50))->FUN_005bd560(0, true);
            return;
        }
    }
}
}

// FUNCTION: GAME 0x005790b0
void RHScript::SetCompanyNumber(void *actor, short number)
{
    if ((*(unsigned int *)((char *)actor + 4) & 0x1f) != 0x14)
    {
        SBAssert(0,
                 // STRING: GAME 0x6b5bb4
                 "P:\\Robin Hood\\RHScript.cpp",
                 6967,
                 // STRING: GAME 0x6b5c30
                 "Script Error: Trying to set company number of a non-soldier.");
        return;
    }

    *(short *)((char *)actor + 0xa20) = number;
}

// FUNCTION: GAME 0x005790f0
void RHScript::SetAlwaysAttentive(void *actor, bool attentive)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6988,
                 // STRING: GAME 0x006b5cb0
                 "Script Error: SetAlwaysAttentive with invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 31) != 20)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 6994,
                 // STRING: GAME 0x006b5c70
                 "Script Error: Trying to set attentive mode of a non-soldier.");
        return;
    }
    ((RHScriptBatchCalls *)((char *)actor + 0x6e8))->Unk00444440(attentive);
}

// FUNCTION: GAME 0x00579160
void RHScript::DeclareAsCombatTrainer(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7014,
                 // STRING: GAME 0x006b5d20
                 "Script Error: DeclareAsCombatTrainer with invalid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 31) != 20)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7020,
                 // STRING: GAME 0x006b5ce8
                 "Script Error: DeclareAsCombatTrainer with non-soldier.");
        return;
    }
    *(char *)((char *)actor + 0xa39) = 1;
    *(char *)((char *)actor + 0x496) = 1;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x005791d0
int FUN_005791d0()
{
    int *first = *(int **)((char *)g_unk0x6c07fc + 0x1b4);
    if (!first)
        return 0;
    return *(int **)((char *)g_unk0x6c07fc + 0x1b8) - first;
}
}

// FUNCTION: GAME 0x00579210
void RHScript::AddPCToMissionTeam(void *actor)
{
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
    {
        ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk00455400(*(void **)((char *)actor + 0x5f8));
        ((RHScriptBatchCalls *)g_unk0x6c0b3c)->Unk00514670();
        *(char *)((char *)actor + 0x92) = 1;
        *(int *)((char *)actor + 0xa0) = 0;
        *(short *)((char *)actor + 0xa4) = 2;
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7089,
             // STRING: GAME 0x006b5d5c
             "Script Error: Trying to add an element that is not a PC to the team for the next mission.");
}

// FUNCTION: GAME 0x00579280
void RHScript::RemovePCFromMissionTeam(void *actor)
{
    if ((*(unsigned int *)((char *)actor + 4) & 15) == 12)
    {
        ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk004555f0(*(void **)((char *)actor + 0x5f8));
        ((RHScriptBatchCalls *)g_unk0x6c0b3c)->Unk00514670();
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7115,
             // STRING: GAME 0x006b5db8
             "Script Error: Trying to remove an element that is not a PC from the team for the next mission.");
}

namespace VMCoreCustomDependencies
{
struct NativeArray
{
    unsigned allocator;
    int *first;
    int *last;
};

// FUNCTION: GAME 0x005792d0
int FUN_005792d0()
{
    char *owner = **(char ***)((char *)g_unk0x6c07fc + 0x17c);
    NativeArray &array = *(NativeArray *)(owner + 0x74);
    if (!array.first)
        return 0;
    return array.last - array.first;
}
}

// FUNCTION: GAME 0x00579300
int RHScript::GetNumberOfBeamMes()
{
    char *campaign = (char *)g_unk0x6c07fc;
    char *mission = **(char ***)(campaign + 0x178);
    if (*(int *)(mission + 0x3c) != 8)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7142,
                 // STRING: GAME 0x006b5e18
                 "Script error: Trying to call a method of the HQ from a non HQ mission. You are fired !");
        return 0;
    }
    char **next = *(char ***)(campaign + 0x17c);
    if (next == 0)
        return 5;
    return *(unsigned short *)(*next + 0x72);
}

// FUNCTION: GAME 0x00579350
void *RHScript::GetPCFromMissionTeam(unsigned long index)
{
    char *campaign = (char *)g_unk0x6c07fc;
    char *mission = **(char ***)(campaign + 0x17c);
    const std::vector<RHCharacterProfile *> &team = *(const std::vector<RHCharacterProfile *> *)(mission + 0x74);
    return g_pEngine->GetPC(team.at(index));
}

// Parked: splitting the mission lookup and changing the result lifetime still changes prologue and return registers.
// STUB: GAME 0x005793a0
char RHScript::RHUnk5793a0(void *actor)
{
    char *mission = **(char ***)((char *)g_unk0x6c07fc + 0x17c);
    unsigned int *end = *(unsigned int **)(mission + 0x7c);
    unsigned int *cursor = *(unsigned int **)(mission + 0x78);
    unsigned int key = *(unsigned int *)((char *)actor + 0x5fc);
    while (cursor != end && *cursor != key)
        ++cursor;
    return cursor != end;
}

// FUNCTION: GAME 0x005793e0
bool RHScript::RHUnk5793e0()
{
    return ((RHCampaign *)g_unk0x6c07fc)->FUN_00453cd0();
}

// FUNCTION: GAME 0x005793f0
void *RHScript::RHUnk5793f0()
{
    void *array = *(void **)((char *)g_unk0x6c07fc + 0x174);
    return array ? **(void ***)array : 0;
}

// FUNCTION: GAME 0x00579410
void *RHScript::RHUnk579410()
{
    void *array = *(void **)((char *)g_unk0x6c07fc + 0x17c);
    return array ? **(void ***)array : 0;
}

// FUNCTION: GAME 0x00579430
int RHScript::GetCustomCampaignValue(int index)
{
    int value = index + 7;

    if (value < 7 || value > 26)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7227,
                 // STRING: GAME 0x6b5e70
                 "Script error: trying to access an invalid campaign value.");
        return 0;
    }

    return g_unk0x6c07fc->Get(value);
}

// FUNCTION: GAME 0x00579470
void RHScript::SetCustomCampaignValue(int index, int value)
{
    int property = index + 7;
    if (property < 7 || property > 26)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7255,
                 // STRING: GAME 0x006b5eac
                 "Script error: trying to access an invalid campaign custom value.");
        return;
    }
    ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk004520e0(property, value);
}

// FUNCTION: GAME 0x005794b0
int RHScript::GetCustomNPCValue(void *actor, int index)
{
    if (index < 0 || index > 9)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7286,
                 // STRING: GAME 0x006b5ef0
                 "Script error: trying to access an invalid NPC custom value.");
    else if (!RHUnk005709c0(actor))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7293,
                 // STRING: GAME 0x006b5f84
                 "Script error: trying to access a NPC custom value on an object that is not a valid actor.");
    else if (actor != 0 && (*(unsigned int *)((char *)actor + 4) & 15) == 4)
        return *(int *)((char *)actor + index * 4 + 0x4a0);
    else
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7300,
                 // STRING: GAME 0x006b5f2c
                 "Script error: trying to access a NPC custom value on an object that is not a valid NPC.");
    return -1;
}

// FUNCTION: GAME 0x00579520
void RHScript::SetCustomNPCValue(void *actor, int index, int value)
{
    if (index < 0 || index > 9)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7329,
                 "Script error: trying to access an invalid NPC custom value.");
        return;
    }
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7336,
                 "Script error: trying to access a NPC custom value on an object that is not a valid actor.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7343,
                 "Script error: trying to access a NPC custom value on an object that is not a valid NPC.");
        return;
    }
    *(int *)((char *)actor + index * 4 + 0x4a0) = value;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x005795b0
unsigned char FUN_005795b0()
{
    return *((unsigned char *)g_unk0x6c0b3c + 0x57);
}
}

// FUNCTION: GAME 0x005795c0
void RHScript::WinBlazon(void *blazon)
{
    RHUnk00452030 *campaign = g_unk0x6c07fc;
    if (blazon == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7382,
                 // STRING: GAME 0x006b601c
                 "Script Error: the supplied parameters is not a blazon in WinBlazon !");
        return;
    }
    if (!*(char *)((char *)blazon + 0x12))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7388,
                 // STRING: GAME 0x006b5fe0
                 "Script Error: in WinBlazon, the blazon was already won !");
        return;
    }
    *(char *)((char *)blazon + 0x12) = 0;
    char *mission = **(char ***)((char *)g_unk0x6c07fc + 0x178);
    int type = *(int *)(mission + 0x34);
    ((RHUnk00450b60 *)campaign)->Unk(3, *(unsigned short *)((char *)blazon + 0xae));
    if (type == 1 && *(unsigned short *)(mission + 0x68) <= campaign->Get(3))
        ((RHScriptBatchCalls *)g_pEngine)->Unk004e3220(1);
    if (g_unk0x6c05c4 == 0)
    {
        ((RHScriptBatchCalls *)g_unk0x6c0b3c)->Unk0050ed40();
        ((RHGame *)g_unk0x6c0b3c)->UpdateBlazons(0, 0, 0, false);
    }
}

// FUNCTION: GAME 0x005796d0
void RHScript::LoseBlazon(void *blazon)
{
    if (blazon == 0)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7460,
                 // STRING: GAME 0x006b6064
                 "Script Error : in LoseBlazon the blazon pointer was null!");
    if (!*(char *)((char *)blazon + 0x12))
    {
        *(char *)((char *)blazon + 0x12) = 1;
        if (g_unk0x6c05c4 == 0)
        {
            ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk00450be0(3, *(unsigned short *)((char *)blazon + 0xae));
            ((RHScriptBatchCalls *)g_unk0x6c0b3c)->Unk0050ed40();
        }
    }
}

// FUNCTION: GAME 0x00579730
bool RHScript::IsBlazonWon(void *blazon)
{
    if (blazon == 0)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7487,
                 "Script Error : in LoseBlazon the blazon pointer was null!");
    return !*(char *)((char *)blazon + 0x12);
}

// FUNCTION: GAME 0x00579760
void RHScript::SetInvisible(void *actor, bool invisible)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7509,
                 // STRING: GAME 0x6b60e4
                 "Script Error: Trying to HollowMan-ize inexisting actor in SetInvisible!");
        return;
    }

    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7516,
                 // STRING: GAME 0x6b60a0
                 "Script Error: Trying to HollowMan-ize non-human in SetInvisible!");
        return;
    }

    *(char *)((char *)actor + 0x23e) = (char)invisible;
}

// FUNCTION: GAME 0x005797c0
char RHScript::IsInvisible(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7538,
                 // STRING: GAME 0x6b617c
                 "Script Error: Trying to inquire HollowMan status of inexisting actor in IsInvisible!");
        return 0;
    }

    if ((*(unsigned int *)((char *)actor + 4) & 7) != 4)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7545,
                 // STRING: GAME 0x6b612c
                 "Script Error: Trying to inquire HollowMan status of non-human in IsInvisible!");
        return 0;
    }

    return *(char *)((char *)actor + 0x23e);
}

// The eight accessors below form the display-flags byte cluster at object
// +0x8c..+0x8f. Offset -> accessor mapping (verified from Game.exe):
//
//   getter 0x00579810 -> byte [+0x8c]   setter 0x00579850 -> [+0x8c] (dirty)
//   getter 0x00579820 -> byte [+0x8f]   setter 0x00579870 -> [+0x8f] (no dirty)
//   getter 0x00579830 -> byte [+0x8e]   setter 0x00579880 -> [+0x8e] (dirty)
//   getter 0x00579840 -> byte [+0x8d]   setter 0x005798a0 -> [+0x8d] (dirty)
//
// The getters emit a bare `mov al,[+off]` (no normalization), so the return is
// `char`. The setters store the byte argument, then — except the +0x8f one —
// `test al,al; jne` and on a zero value mark the object dirty (`[+8]=1`), so
// they are `void`. Identity is UNPROVEN: no Windows-side signal binds a method
// name (see include/RHScript.h); the Mac oracle's Get/SetOutlineDisplay are
// candidates but cross-binary signature is not evidence (docs/05-naming.md).

// FUNCTION: GAME 0x00579810
char RHScript::RHUnk579810(void *object)
{
    return *(char *)((char *)object + 0x8c);
}

// FUNCTION: GAME 0x00579820
char RHScript::RHUnk579820(void *object)
{
    return *(char *)((char *)object + 0x8f);
}

// FUNCTION: GAME 0x00579830
char RHScript::RHUnk579830(void *object)
{
    return *(char *)((char *)object + 0x8e);
}

// FUNCTION: GAME 0x00579840
char RHScript::RHUnk579840(void *object)
{
    return *(char *)((char *)object + 0x8d);
}

// FUNCTION: GAME 0x00579850
void RHScript::RHUnk579850(void *object, bool value)
{
    *(char *)((char *)object + 0x8c) = (char)value;

    if (!value)
    {
        *(char *)((char *)object + 8) = 1;
    }
}

// FUNCTION: GAME 0x00579870
void RHScript::RHUnk579870(void *object, bool value)
{
    *(char *)((char *)object + 0x8f) = (char)value;
}

// FUNCTION: GAME 0x00579880
void RHScript::RHUnk579880(void *object, bool value)
{
    *(char *)((char *)object + 0x8e) = (char)value;

    if (!value)
    {
        *(char *)((char *)object + 8) = 1;
    }
}

// FUNCTION: GAME 0x005798a0
void RHScript::RHUnk5798a0(void *object, bool value)
{
    *(char *)((char *)object + 0x8d) = (char)value;

    if (!value)
    {
        *(char *)((char *)object + 8) = 1;
    }
}

class RHElementScroll;
extern RHElementScroll *g_scrollExecutingScript;
extern RHElementScroll **g_unk0x6c09dc;

// GLOBAL: GAME 0x006c09e0
RHElementScroll **g_unk0x006c09e0;

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x005798c0
RHElementScroll *FUN_005798c0()
{
    RHElementScroll *scroll = g_scrollExecutingScript;
    if (scroll)
    {
        RHElementScroll **end = g_unk0x006c09e0;
        RHElementScroll **entry = g_unk0x6c09dc;
        while (entry != end && *entry != scroll)
            ++entry;
        return *entry;
    }
    return 0;
}
}

// FUNCTION: GAME 0x005798f0
int RHScript::GetScrollStatus(void *element)
{
    if (element == 0)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7716,
                 // STRING: GAME 0x6b6228
                 "Script error in GetScrollStatus: trying to access a null-element.");
        return 0;
    }

    if ((*(unsigned int *)((char *)element + 4) & 3) != 3 ||
        *(unsigned int *)((char *)element + 0xb0) != 0xc)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7732,
                 // STRING: GAME 0x6b61d4
                 "Script error in GetScrollStatus: trying to access an elemnt that is not a scroll.");
        return 0;
    }

    return ((RHUnk004b9f30 *)element)->Get();
}

// FUNCTION: GAME 0x00579950
void RHScript::SetScrollStatus(void *element, int status)
{
    if (element == 0)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7752,
                 // STRING: GAME 0x6b6304
                 "Script error in SetScrollStatus: trying to access a null-element.");
        return;
    }

    if ((*(unsigned int *)((char *)element + 4) & 3) != 3 ||
        *(unsigned int *)((char *)element + 0xb0) != 0xc)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7777,
                 // STRING: GAME 0x6b626c
                 "Script error in SetScrollStatus: trying to access an element that is not a scroll.");
        return;
    }

    if (status < 0 || status >= 4)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7767,
                 // STRING: GAME 0x6b62c0
                 "Script Error in SetScrollStatus: '%i' is not a valid scroll status.",
                 status);
        return;
    }

    ((RHUnk004ba7a0 *)element)->Set(status);
}

// FUNCTION: GAME 0x00579a30
int RHScript::GetSoldierRank(void *actor)
{
    if (actor == 0 ||
        ((*(unsigned int *)((char *)actor + 4) & 0x1f) != 0x14))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7861,
                 // STRING: GAME 0x6b6348
                 "Script error: Trying to get the rank of an actor which is not a soldier");
        return 0;
    }

    return *(int *)(*(char **)((char *)actor + 0xa1c) + 0x58);
}

// FUNCTION: GAME 0x00579a70
bool RHScript::IsActorDead(void *actor)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 7) != 4))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7874,
                 // STRING: GAME 0x6b6390
                 "Script error: parameter of function IsActorDead is not an actor (at least not an human)");
        return false;
    }

    return ((RHUnk00570e70Vtbl *)actor)->v18();
}

// FUNCTION: GAME 0x00579ac0
char RHScript::IsActorKO(void *actor)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 7) != 4))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7887,
                 // STRING: GAME 0x6b63e8
                 "Script error: parameter of function IsActorKO is not an actor (at least not an human)");
        return 0;
    }

    return *(char *)((char *)actor + 0x1ce);
}

// FUNCTION: GAME 0x00579b10
bool RHScript::IsActorTied(void *actor)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 7) != 4))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7900,
                 // STRING: GAME 0x6b6440
                 "Script error: parameter of function IsActorTied is not an actor (at least not an human)");
        return false;
    }

    return *(int *)(*(char **)((char *)actor + 0x50) + 0x8c) == 0x12;
}

// FUNCTION: GAME 0x00579b60
bool RHScript::IsActorHS(void *actor)
{
    if (!RHUnk005709c0(actor) ||
        ((*(unsigned int *)((char *)actor + 4) & 7) != 4))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 7913,
                 // STRING: GAME 0x6b6498
                 "Script error: parameter of function IsActorHS is not an actor (at least not an human)");
        return false;
    }

    return ((RHUnk00570e70Vtbl *)actor)->v18() ||
           *(int *)(*(char **)((char *)actor + 0x50) + 0x8c) == 0x12 ||
           *(unsigned char *)((char *)actor + 0x1ce);
}

// FUNCTION: GAME 0x00579de0
int RHScript::GetSoundSourceIndex(void *source)
{
    int index = -1;
    char *manager = *(char **)(g_unk0x6c0fa8 + 0x45e0);
    if (*(char *)(manager + 0x20a))
    {
        RHScriptSoundArray *array = (RHScriptSoundArray *)(*(char **)(manager + 0x200) + 4);
        index = array->Find(source);
        if (index == -1)
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 7960,
                     // STRING: GAME 0x006b64f0
                     "ScriptError: unknow sound source in GetSoundSourceIndex !");
    }
    return index;
}

// FUNCTION: GAME 0x0057a020
bool RHScript::AddToSequence(RHSequenceElement *element, const char *where)
{
    if (g_unk0x6c0f78 != 0)
    {
        ((RHUnk00585500 *)element)->Unk(g_unk0x6c0f78);
        return true;
    }

    SBAssert(0,
             "P:\\Robin Hood\\RHScript.cpp",
             8039,
             // STRING: GAME 0x6b6548
             "Script error in %s: trying to record in a sequence without having started one.",
             where);
    return false;
}

// FUNCTION: GAME 0x0057a060
int RHScript::GetNumberOfActorsInSector(void *sector)
{
    if (sector == 0)
    {
        return 0;
    }

    if (*(int *)((char *)sector + 0xbc) != 2)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8071,
                 // STRING: GAME 0x6b6598
                 "Script Error: trying to call GetNumberOfActorsInSector for a non-sector.");
        return 0;
    }

    return *(int *)((char *)sector + 0xd4);
}

// FUNCTION: GAME 0x0057a0a0
void *RHScript::GetActorInSector(void *sector, int index)
{
    if (sector == 0) return 0;
    if (*(int *)((char *)sector + 0xbc) != 2)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8103,
                 // STRING: GAME 0x006b6628
                 "Script Error: trying to call GetActorInSector for a non-sector.");
        return 0;
    }
    if ((unsigned int)index >= *(unsigned int *)((char *)sector + 0xd4))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8109,
                 // STRING: GAME 0x006b65e4
                 "Script Error: trying to call GetActorInSector with invalid index.");
        return 0;
    }
    return ((RHScriptSectorActors *)sector)->actors[index];
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057a280
int FUN_0057a280(int first, int second)
{
    return first & second;
}

// FUNCTION: GAME 0x0057a290
int FUN_0057a290(int first, int second)
{
    return first | second;
}

// FUNCTION: GAME 0x0057a2a0
int FUN_0057a2a0(int first, int second)
{
    return first ^ second;
}
}

// FUNCTION: GAME 0x0057a2b0
bool RHScript::HasPCAction(void *actor, int action)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8179,
                 // STRING: GAME 0x006b66e0
                 "Script Error: Trying to call HasPCAction for invalid actor element.");
        return false;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8185,
                 // STRING: GAME 0x006b66a8
                 "Script Error: Trying to call HasPCAction for non-PC.");
        return false;
    }
    int type;
    switch (action)
    {
        RH_SCRIPT_ACTION_CASES
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8224,
                 // STRING: GAME 0x006b6668
                 "Script Error: Trying to call HasPCAction with bad action ID.");
        return false;
    }
    return ((RHUnk0049d4f0 *)actor)->Unk(type) || ((RHScriptBatchCalls *)actor)->Unk0049d560(type);
}

// FUNCTION: GAME 0x0057a4c0
bool RHScript::HasAnyPCAction(int action)
{
    int type;
    switch (action)
    {
        RH_SCRIPT_ACTION_CASES
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8279,
                 // STRING: GAME 0x006b6724
                 "Script Error: Trying to call HasAnyPCAction with bad action ID.");
        return false;
    }
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned short i = 0; i < count; ++i)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)i);
        if (((RHUnk0049d4f0 *)actor)->Unk(type) || ((RHScriptBatchCalls *)actor)->Unk0049d560(type))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0057a6d0
bool RHScript::HasAnyActivePCAction(int action)
{
    int type;
    switch (action)
    {
        RH_SCRIPT_ACTION_CASES
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8348,
                 "Script Error: Trying to call HasAnyPCAction with bad action ID.");
        return false;
    }
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned short i = 0; i < count; ++i)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)i);
        if (*(char *)((char *)actor + 0x4e8) &&
            (((RHUnk0049d4f0 *)actor)->Unk(type) || ((RHScriptBatchCalls *)actor)->Unk0049d560(type)))
            return true;
    }
    return false;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057a8e0
void *FUN_0057a8e0()
{
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned int index = 0; (unsigned short)index < count; ++index)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)index);
        if (((RHUnk00570e70Vtbl *)actor)->v90())
            return actor;
    }
    return 0;
}
}

// FUNCTION: GAME 0x0057aa20
unsigned FUN_0057aa20()
{
    return ((RHScriptPCArray *)g_pEngine)->Count();
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057aa50
int FUN_0057aa50(int index)
{
    return (int)((RHScriptPCArray *)g_pEngine)->Get((unsigned char)index);
}
}

// 90.44%; virtual-base and list-search register scheduling remain unresolved.
// STUB: GAME 0x0057aa70
void RHScript::AddAsSubordinate(void *chief, void *subordinate)
{
    if (!RHUnk005709c0(subordinate))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8481,
                 // STRING: GAME 0x006b6928
                 "Script Error: Trying to call AddAsSubordinate with invalid subordinate.");
        return;
    }
    if ((*(unsigned int *)((char *)subordinate + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8487,
                 // STRING: GAME 0x006b68e0
                 "Script Error: Trying to AddAsSubordinate with non-NPC as subordinate.");
        return;
    }
    char *base = (char *)subordinate + *(int *)(*(char **)((char *)subordinate + 0x49c) + 4);
    if (*(void **)(base + 0x74c) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8495,
                 // STRING: GAME 0x006b6888
                 "Script Error: Trying to AddAsSubordinate with subordinate who already is in a patrol.");
        return;
    }
    if (*(int *)(base + 0x7a0) > 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8502,
                 // STRING: GAME 0x006b6838
                 "Script Error: Trying to AddAsSubordinate with chief who is himself in a patrol.");
        return;
    }
    if (!RHUnk005709c0(chief))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8511,
                 // STRING: GAME 0x006b67f4
                 "Script Error: Trying to call AddAsSubordinate with invalid chief.");
        return;
    }
    if ((*(unsigned int *)((char *)chief + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8517,
                 // STRING: GAME 0x006b67b4
                 "Script Error: Trying to AddAsSubordinate with non-NPC as chief.");
        return;
    }
    base = (char *)chief + *(int *)(*(char **)((char *)chief + 0x49c) + 4);
    if (*(void **)(base + 0x74c) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8525,
                 "Script Error: Trying to AddAsSubordinate with chief who is himself in a patrol.");
        return;
    }
    if (subordinate == chief)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8531,
                 // STRING: GAME 0x006b6764
                 "Script Error: Trying to add a guy as his own subordinate!!! T'es rigolo toi...");
        return;
    }
    base += 0x49c;
    RHScriptZoneList *list = (RHScriptZoneList *)(base + 0x2fc);
    if (list->Find(subordinate) == -1)
    {
        RHScriptNode *next = list->head;
        RHScriptNode *previous = next->prev;
        RHScriptNode *node = (RHScriptNode *)operator new(12);
        node->next = next ? next : node;
        node->prev = previous ? previous : node;
        next->prev = node;
        node->prev->next = node;
        new (&node->data) void *(subordinate);
        ++list->count;
        list->valid = true;
        ((RHScriptBatchCalls *)base)->Unk0041ac50();
    }
}

// FUNCTION: GAME 0x0057acc0
void RHScript::RemoveAllSubordinates(void *chief)
{
    if (!RHUnk005709c0(chief))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8558,
                 // STRING: GAME 0x6b69b8
                 "Script Error: Trying to call RemoveAllSubordinates with invalid chief.");
        return;
    }

    if ((*(unsigned int *)((char *)chief + 4) & 0xf) != 4)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8564,
                 // STRING: GAME 0x6b6970
                 "Script Error: Trying to RemoveAllSubordinates with non-NPC as chief.");
        return;
    }

    void *p = *(void **)((char *)chief + 0x49c);
    int off = *(int *)((char *)p + 4);
    ((RHUnk0041b0e0 *)((char *)chief + 0x49c + off))->Clear();
}

// FUNCTION: GAME 0x0057ad30
void RHScript::SwitchToAlertPath(void *soldier)
{
    if (!RHUnk005709c0(soldier))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8585,
                 // STRING: GAME 0x6b6a3c
                 "Script Error: Trying to call SwitchToAlertPath with invalid soldier.");
        return;
    }

    if ((*(unsigned int *)((char *)soldier + 4) & 0x1f) != 0x14)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8591,
                 // STRING: GAME 0x6b6a00
                 "Script Error: Trying to SwitchToAlertPath with non-soldier.");
        return;
    }

    ((RHUnk0044cae0 *)((char *)soldier + 0x6e8))->Switch();
}

// FUNCTION: GAME 0x0057ad90
bool RHScript::IsActorRider(void *actor)
{
    if (actor == 0)
    {
        return false;
    }

    if (!RHUnk005709c0(actor))
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHScript.cpp",
                 8616,
                 // STRING: GAME 0x6b6a84
                 "Script Error: Trying to call IsActorRider with invalid actor.");
        return false;
    }

    if ((*(unsigned int *)((char *)actor + 4) & 0x1f) != 0x14)
    {
        return false;
    }

    return ((RHUnk00570e70Vtbl *)actor)->v61();
}

// FUNCTION: GAME 0x0057adf0
int RHScript::AddRepulsivePoint(void *location, float radius, float strength, int value)
{
    if (*(int *)((char *)location + 0x18) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8635,
                 // STRING: GAME 0x006b6ac4
                 "Script Error: you can only create repulsive point with point location.");
        return 0;
    }
    return ((RHScriptBatchCalls *)g_unk0x6c0a9c)->Unk004ec910(location, radius, strength, value);
}

// 76.92%; isolated /O2 /GX probe retains the wrong shared switch-block placement.
// STUB: GAME 0x0057aed0
void RHScript::SetNPCEmoticon(void *actor, int emoticon, int duration)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8691,
                 // STRING: GAME 0x006b6b78
                 "Script Error: Trying to set emoticon of an invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 4)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8697,
                 // STRING: GAME 0x006b6b44
                 "Script Error: Trying to set emoticon of a non-NPC.");
        return;
    }
    int type;
    switch (emoticon)
    {
    case 1:
        type = 2;
    setEmoticon:
        ((RHScriptBatchCalls *)((char *)actor + *(int *)(*(char **)((char *)actor + 0x49c) + 4) + 0x49c))->Unk00419fd0(type, duration);
        return;
    case 2:
        type = 3;
        goto setEmoticon;
    case 3:
        type = 4;
        goto setEmoticon;
    case 4:
        type = 5;
        goto setEmoticon;
    case 5:
        type = 6;
        goto setEmoticon;
    case 6:
        type = 7;
        goto setEmoticon;
    case 7:
        type = 8;
        goto setEmoticon;
    case 0:
        ((RHScriptBatchCalls *)((char *)actor + *(int *)(*(char **)((char *)actor + 0x49c) + 4) + 0x49c))->Unk00419fb0(0);
        return;
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8738,
                 // STRING: GAME 0x006b6b0c
                 "Script Error: Trying to set emoticon with invalid ID.");
        return;
    }
}

#include "RHMissionStatCore.h"

// FUNCTION: GAME 0x0057afe0
void RHScript::AddPCToGang(void *actor)
{
    RHScriptBatchCalls *engine = (RHScriptBatchCalls *)g_pEngine;
    RHCampaign *campaign = (RHCampaign *)g_unk0x6c07fc;
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8763,
                 // STRING: GAME 0x006b6c10
                 "OULALA ! Script error ! Are you trying to add a background animation to Robin's gang ?");
    RHElementActorPC *pc = (RHElementActorPC *)actor;
    void *value;
    if (((RHUnk00570e70Vtbl *)pc)->IsVIP() && campaign->IsInGang((RHCharacterProfile *)(value = pc->m_5fc)))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8770,
                  // STRING: GAME 0x006b6bbc
                  "OULALA ! Script error ! Are you trying to add a PC a second time to Robin's gang ?");
    value = pc->m_5f8;
    campaign->FUN_004522e0((RHPCDescription *)value);
    value = pc->m_5f8;
    ((RHMissionStat *)engine->Unk004e3cc0())->AddNewPC((RHPCDescription *)value);
}

// FUNCTION: GAME 0x0057b080
bool RHScript::IsBonusItemPickedUp(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 3) == 3)
    {
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 3)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8795,
                     // STRING: GAME 0x006b6cac
                     "Script error: in IsBonusItemPickedUp the supplied item is not a bonus item.");
            return false;
        }
        return *(bool *)((char *)actor + 0xfd);
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8786,
             // STRING: GAME 0x006b6c68
             "Script Error: in IsBonusItemPickedUp the supplied item is invalid.");
    return false;
}

// FUNCTION: GAME 0x0057b0f0
int RHScript::GetRansomMoney()
{
    if (g_unk0x6c07fc == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8811,
                 // STRING: GAME 0x006b6cf8
                 "Script Error: in GetRansomMoney, you are not in campaign mode.");
        return -1;
    }
    return g_unk0x6c07fc->Get(1);
}

// FUNCTION: GAME 0x0057b120
void RHScript::SetRansomMoney(int value)
{
    if (g_unk0x6c07fc == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8824,
                 // STRING: GAME 0x006b6d38
                 "Script Error: in SetRansomMoney, you are not in campaign mode.");
        return;
    }
    ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk004520e0(1, value);
}

extern unsigned char g_unk0x006c0e48[];

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057b150
int FUN_0057b150()
{
    return *(int *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x1c);
}
}

// FUNCTION: GAME 0x0057b2f0
void RHScript::SetExperiences(void *actor, int first, int second)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 15) == 12)
    {
        ((RHScriptBatchCalls *)actor)->Unk00485220(0, first);
        ((RHScriptBatchCalls *)actor)->Unk00485220(1, second);
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8889,
             // STRING: GAME 0x006b6d78
             "Script Error: in SetExperiences the supplied actor is invalid.");
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057b350
void FUN_0057b350(int actor, bool value)
{
    if (actor)
        *(bool *)(*(char **)(actor + 0x18) + 0x12) = value;
}

// FUNCTION: GAME 0x0057b370
int FUN_0057b370()
{
    int result = 0;
    unsigned count = ((RHScriptPCArray *)g_pEngine)->Count();
    while (count)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)(count - 1));
        if (!((RHUnk00570e70Vtbl *)actor)->v18())
            ++result;
        --count;
    }
    return result;
}
}

// FUNCTION: GAME 0x0057b450
void RHScript::TransformHandleTargetToTakeTarget(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 15) == 9)
    {
        if (((RHScriptBatchCalls *)actor)->Unk004baea0() & 0x400)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8996,
                     // STRING: GAME 0x006b6e54
                     "Script Error: The target in TransformHandleTargetToTakeTarget is already takable.");
            return;
        }
        if (!(((RHScriptBatchCalls *)actor)->Unk004baea0() & 4))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9002,
                     // STRING: GAME 0x006b6e04
                     "Script Error: The target in TransformHandleTargetToTakeTarget is not handlable.");
            return;
        }
        *(int *)((char *)actor + 0x168) ^= 0x404;
        return;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 8988,
             // STRING: GAME 0x006b6db8
             "Script Error: The target in TransformHandleTargetToTakeTarget is invalid.");
}

// FUNCTION: GAME 0x0057b4f0
bool RHScript::IsPCSelected(void *actor)
{
    if (RHUnk005709c0(actor) && (*(unsigned int *)((char *)actor + 4) & 15) == 12)
    {
        char *engine = (char *)g_pEngine;
        if (actor != 0)
            return ((RHScriptZoneList *)(engine + 0x49f8))->Find(actor) == -1 ? false : true;
        return *(int *)(engine + 0x4a00) == 0 ? false : true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9024,
             // STRING: GAME 0x006b6ea8
             "Script Error: The Actor in IsPCSelected is invalid.");
    return true;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057b5e0
int FUN_0057b5e0()
{
    return *(int *)((char *)g_pEngine + 0x4a00);
}
}

// FUNCTION: GAME 0x0057b5f0
void *RHScript::GetSelectedPC(int index)
{
    if ((unsigned int)index >= (unsigned int)*(int *)((char *)g_pEngine + 0x4a00))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9066,
                 // STRING: GAME 0x006b6edc
                 "Script Error: The index of GetSelectedPC is out of range.");
        return 0;
    }
    RHScriptIndexedList &list = *(RHScriptIndexedList *)((char *)g_pEngine + 0x49f8);
    return list[(unsigned short)index];
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057b780
void FUN_0057b780()
{
    (*(RHSound **)((char *)g_pEngine + 0x45e0))->PlayJingle(6);
}
}

// FUNCTION: GAME 0x0057b7a0
void RHScript::MakePCCrouched(void *actor)
{
    if (!RHUnk005709c0(actor))
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9099,
                 // STRING: GAME 0x006b6f50
                 "Script Error: Trying to call MakePCCrouched for invalid actor element.");
        return;
    }
    if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9105,
                 // STRING: GAME 0x006b6f18
                 "Script Error: Trying to call MakePCCrouched for non-PC.");
        return;
    }
    ((RHScriptBatchCalls *)actor)->Unk0046b9e0();
}

// FUNCTION: GAME 0x0057b800
bool RHScript::HasAnyPCActionWhoIsInThisLevelOrCouldMaybeComeFromSherwood(int action)
{
    int type;
    switch (action)
    {
        RH_SCRIPT_ACTION_CASES
    default:
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9161,
                 "Script Error: Trying to call HasAnyPCAction with bad action ID.");
        return false;
    }
    unsigned short count = ((RHScriptPCArray *)g_pEngine)->Count();
    for (unsigned short i = 0; i < count; ++i)
    {
        void *actor = ((RHScriptPCArray *)g_pEngine)->Get((unsigned char)i);
        if (((RHUnk0049d4f0 *)actor)->Unk(type) || ((RHScriptBatchCalls *)actor)->Unk0049d560(type))
        {
            if (!((RHUnk00570e70Vtbl *)actor)->v18())
                return true;
            if (!((RHUnk00570e70Vtbl *)actor)->IsVIP())
            {
                char *chief = *(char **)((char *)actor + 0x4ec);
                if (chief != 0 && *(char *)(chief + 0xca9))
                {
                    actor = *(void **)((char *)actor + 0x5fc);
                    if (((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk00456ce0(actor))
                        return true;
                }
            }
        }
    }
    return false;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057ba50
void FUN_0057ba50(int object, bool value)
{
    *(bool *)(object + 0xc) = value;
}
}

// FUNCTION: GAME 0x0057ba60
int RHScript::GetPCType(void *actor)
{
    if (!RHUnk005709c0(actor))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9218,
                 // STRING: GAME 0x006b7054
                 "Script Error: Trying to get the PC type of an invalid actor!");
    else if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9224,
                 // STRING: GAME 0x006b701c
                 "Script Error: Trying to get the PC type of a non-PC!");
    else
    {
        RHScriptPCType *type = (RHScriptPCType *)*(void **)((char *)actor + 0x5fc);
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006ae6c0
                   "RobinTown") == 0 ||
            strcmp(type->c_str(),
                   // STRING: GAME 0x006ae6b4
                   "RobinHood") == 0)
            return 0;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b7010
                   "LittleJohn") == 0) return 1;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b7004
                   "Friar Tuck") == 0) return 2;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6ff8
                   "Stuteley") == 0) return 3;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6fec
                   "WillScarlet") == 0) return 4;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6fe0
                   "LadyMarian") == 0) return 5;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6fd4
                   "MerryManA") == 0) return 6;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6fc8
                   "MerryManB") == 0) return 7;
        if (strcmp(type->c_str(),
                   // STRING: GAME 0x006b6fbc
                   "MerryManC") == 0) return 8;
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9277,
                 // STRING: GAME 0x006b6f98
                 "Script Error: PC with unknown type!");
    }
    return -1;
}

// FUNCTION: GAME 0x0057bdb0
void RHScript::SelectActorPC(void *actor, bool selected)
{
    if (actor == 0)
        RHUnk00546050()->RHUnk005460c0(RHUnk00549250(selected ? 13 : 18, actor));
    else
    {
        if (!RHUnk005709c0(actor))
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9303,
                     // STRING: GAME 0x006b70c0
                     "Script Error: Trying to select an invalid actor!");
            return;
        }
        if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        {
            SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9309,
                     // STRING: GAME 0x006b7094
                     "Script Error: Trying to select a non-PC!");
            return;
        }
        RHUnk00546050()->RHUnk005460c0(RHUnk00549250(selected ? 13 : 18, actor));
    }
}

// FUNCTION: GAME 0x0057bed0
bool RHScript::HasAnyActionSelected(void *actor)
{
    if (!RHUnk005709c0(actor))
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9334,
                 // STRING: GAME 0x006b7134
                 "Script Error: Trying to call HasAnyActionSelected for invalid actor!");
    else if ((*(unsigned int *)((char *)actor + 4) & 15) != 12)
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9340,
                 // STRING: GAME 0x006b70f4
                 "Script Error: Trying to call HasAnyActionSelected for a non-PC!");
    else
    {
        RHScriptSelectionEngine *engine = (RHScriptSelectionEngine *)g_pEngine;
        bool selected;
        if (actor != 0)
        {
            int size = engine->selection.count;
            engine->selection.searchValue = actor;
            engine->selection.searchValid = true;
            RHScriptNode *first = *(RHScriptNode *volatile *)&engine->selection.head->next;
            engine->selection.cursor.node = first;
            int index = 0;
            for (; index < size; ++index, ((RHSectorActorIter &)engine->selection.cursor)++)
                if (engine->selection.cursor.node->data == engine->selection.searchValue) break;
            if (index < size)
            {
                engine->selection.searchIndex = index;
                engine->selection.valid = false;
                engine->selection.index = index;
            }
            else
            {
                engine->selection.valid = true;
                engine->selection.searchIndex = -1;
            }
            selected = engine->selection.searchIndex == -1 ? false : true;
        }
        else selected = engine->selection.count == 0 ? false : true;
        if (!selected) return false;
        return *(unsigned short *)((char *)RHUnk00546050() + 0xa2) != 0;
    }
    return false;
}

// 71.67%; array-insertion frame and argument scheduling remain unresolved.
// STUB: GAME 0x0057c500
void RHScript::LinkTargetToFX(void *target, void *fx)
{
    if ((*(unsigned int *)((char *)target + 4) & 15) != 9)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9490,
                 // STRING: GAME 0x006b71c0
                 "HALT STEHENBLEIBEN ! Script error (LinkTargetToPatch) : Invalid target");
        return;
    }
    if ((*(unsigned int *)((char *)fx + 4) & 3) != 1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHScript.cpp", 9496,
                 // STRING: GAME 0x006b717c
                 "HALT STEHENBLEIBEN ! Script error (LinkTargetToPatch) : Invalid FX");
        return;
    }
    RHScriptFXArray *array = (RHScriptFXArray *)((char *)target + 0x16c);
    void *value = fx;
    void **position = array->last;
    if ((unsigned int)(array->end - array->last) < 1)
    {
        unsigned int grow = array->Size() > 1 ? array->Size() : 1;
        int size = array->Size() + grow;
        void **storage = (void **)operator new((size < 0 ? 0 : size) * 4);
        void **destination = storage;
        for (void **source = array->first; source != position; ++source, ++destination)
            RHSeqList::CopyData((RHSequenceElement **)destination, (RHSequenceElement *const *)source);
        array->Unk004fe450(destination, 1, value);
        ++destination;
        array->Unk004fe420(position, array->last, destination);
        array->Unk005008e0(array->first, array->last);
        operator delete(array->first);
        array->end = storage + size;
        unsigned int previousSize = array->Size();
        array->first = storage;
        array->last = array->first + previousSize + 1;
        array->dirty = true;
    }
    else if ((unsigned int)(array->last - position) < 1)
    {
        array->Unk004fe420(position, array->last, position + 1);
        array->Unk004fe450(array->last, 1 - (array->last - position), value);
        for (void **destination = position; destination != array->last; ++destination)
            *destination = value;
        ++array->last;
        array->dirty = true;
    }
    else
    {
        array->Unk004fe420(array->last - 1, array->last, array->last);
        void **source = array->last - 1;
        void **destination = array->last;
        while (source != position) *--destination = *--source;
        void **last = position + 1;
        for (destination = position; destination != last; ++destination)
            *destination = value;
        ++array->last;
        array->dirty = true;
    }
}

// Force emission: non-inline member functions defined here are emitted into the
// object; these out-of-line calls keep them in the build.
// FUNCTION: GAME 0x0057ff70
void RHScriptBatchCalls::Unk0057ff70(float height)
{
    *(int *)((char *)this + 0x30) = 0x20000;
    *(float *)((char *)this + 0xf0) = height;
}

// FUNCTION: GAME 0x00586e00
void RHUnk005866a0::Unk00586e00(int property, bool value)
{
    RHScriptPropertyValue payload;
    payload.m_bool = value;
    RHScriptPropertyPair pair(property, payload);
    ((RHGenericMap *)((char *)this + 0x64))->FUN_005873a0(*(const RHGenericPair *)&pair);
}

// FUNCTION: GAME 0x00586e90
void RHUnk005866a0::Unk00586e90(int property, unsigned short value)
{
    RHScriptPropertyValue payload;
    payload.m_int = value;
    RHScriptPropertyPair pair(property, payload);
    ((RHGenericMap *)((char *)this + 0x64))->FUN_005873a0(*(const RHGenericPair *)&pair);
}

// FUNCTION: GAME 0x00586ed0
void RHUnk005866a0::Unk00586ed0(int property, int value)
{
    RHScriptPropertyValue payload;
    payload.m_int = value;
    RHScriptPropertyPair pair(property, payload);
    ((RHGenericMap *)((char *)this + 0x64))->FUN_005873a0(*(const RHGenericPair *)&pair);
}

// FUNCTION: GAME 0x00586fd0
void RHUnk005866a0::Unk00586fd0(int property, float value)
{
    RHScriptPropertyValue payload;
    payload.m_float = value;
    RHScriptPropertyPair pair(property, payload);
    ((RHGenericMap *)((char *)this + 0x64))->FUN_005873a0(*(const RHGenericPair *)&pair);
}

// FUNCTION: GAME 0x00587010
void RHUnk005866a0::Unk00587010(int property, const SBGeoPoint2D &value)
{
    RHScriptPropertyValue payload;
    payload.m_point.x = value.m_x;
    payload.m_point.y = value.m_y;
    RHScriptPropertyPair pair(property, payload);
    ((RHGenericMap *)((char *)this + 0x64))->FUN_005873a0(*(const RHGenericPair *)&pair);
}

// FUNCTION: GAME 0x00588190
void RHScriptPositionList::Unk00588190(RHUnk00571160Position *destination, const RHUnk00571160Position *source)
{
    if (destination)
    {
        ((unsigned long *)destination)[0] = ((const unsigned long *)source)[0];
        ((unsigned long *)destination)[1] = ((const unsigned long *)source)[1];
        ((unsigned long *)destination)[2] = ((const unsigned long *)source)[2];
        ((unsigned long *)destination)[3] = ((const unsigned long *)source)[3];
    }
}

// FUNCTION: GAME 0x005bdd30
SBGeoPoint2D *RHUnk005b5e00::Unk005bdd30(short index)
{
    void *bank = FUN_005b5de0();
    char *frames = *(char **)((char *)bank + 4);
    return (SBGeoPoint2D *)(frames + (unsigned short)index * 100 + 8);
}

// FUNCTION: GAME 0x005fc090
SBGeoPoint2D &SBGeoPoint2D::operator=(const SBGeoPoint2D &other)
{
    if (&other != this)
    {
        SBGeoPoint2D::~SBGeoPoint2D();
        FUN_005fc390(other);
    }
    return *this;
}

// FUNCTION: GAME 0x005fc6a0
float RHUnk005fc3b0::Unk005fc6a0(float value)
{
    float y;
    if (value != 1.0f)
        y = m_y / value;
    else
        y = m_y;
    return (float)sqrt(m_x * m_x + y * y);
}

// FUNCTION: GAME 0x005fc6d0
float SBGeoPoint2D::Unk005fc6d0(float value) const
{
    float y;
    if (value != 1.0f)
        y = m_y / value;
    else
        y = m_y;
    return m_x * m_x + y * y;
}

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x0057bfe0
unsigned char FUN_0057bfe0()
{
    return *((unsigned char *)g_unk0x6c07fc + 0x1c0);
}
}

void RHScript::Emit()
{
    IsActorCharacter(0);
    IsActorObject(0);
    IsActorCart(0);
    IsActorPC(0);
    IsActorAnimal(0);
    IsActorNPC(0);
    IsActorSoldier(0);
    IsActorCivilian(0);
    IsAnimationActive(0);
    SetAnimationState(0, false);
    FUN_00570dd0(0);
    IsActorActive(0);
    UnBlip(0);
    IsUnblipped(0);
    Start();
    Thanx();
    Then();
    MakeNoise(0, 0);
    SetZoomLevel(1.0f);
    ScrollCameraTo(0);
    ScrollCameraSlowlyTo(0, 0.0f);
    JumpCameraTo(0);
    GetLocationScript(0);
    GetMovementStyle(0);
    GetActorScript(0);
    GetActorForBeamMe(0);
    GetDoorScript(0);
    GetPatchScript(0);
    GetActorLocation(0);
    SetActorLocation(0, 0);
    GetActorDirection(0);
    SetActorDirection(0, 0);
    StopActor(0);
    GetDistance(0, 0);
    ComputeLocationBetween(0, 0, 0);
    IsInside(0, 0);
    GetAnyActorInsideBuilding(0);
    AreAllEnemiesInsideHS(0);
    GetPersistentProperty(0, 0);
    SetPersistentProperty(0, 0, 0);
    ConfiscateMoney(0);
    RecordScrollCameraTo(0);
    RecordJumpCameraTo(0);
    RecordMoveCameraTo(0, 0);
    RecordSetZoom(0);
    RecordDisplayMap(false);
    RecordSpeak(0, 0);
    ForbidNPCRemark(0, 0, false);
    RecordSpeakPC(0, 0, 0);
    RecordPlayAnim(0, 0);
    RecordPlayAnimLoop(0, 0);
    RecordPlayAnimFreeze(0, 0);
    RecordAction(0, 0, 0);
    RecordSeekActorMessage(0, 0, 0, 0.0f, 0, 0);
    RecordSeekActorMessageWithArguments(0, 0, 0, 0.0f, 0, 0, 0, 0);
    RecordMove(0, 0, 0);
    RecordMoveNear(0, 0, 0, 0);
    RecordMoveIntoBuilding(0, 0, 0);
    RecordTakeCorpse(0, 0, 0);
    RecordLeaveCorpse(0);
    RecordTurnTo(0, 0);
    RecordReplaceAnim(0, 0, 0);
    RecordRestoreAnim(0, 0);
    RecordLockAI(0);
    RecordUnlockAI(0);
    RecordUnBlip(0);
    RecordLockUser();
    RecordUnLockUser();
    GetSoundSourceScript(0);
    Deactivate(0);
    Activate(0);
    SetActionAvailable(0, 0, false);
    IsActionAvailable(0, 0);
    SetAIAlertStatus(0, 0);
    GetAIAlertStatus(0);
    SetAIState(0, 0);
    GetAIState(0);
    SetAIAttitude(0, 0);
    GetAIAttitude(0);
    SetAILevel(0, 0, 0);
    StareActor(0, 0, false);
    StareLocation(0, 0, false);
    GetActorPosture(0);
    SetActorPosture(0, 0);
    GetActorActionState(0);
    SetActorActionState(0, 0);
    Freeze(0, false);
    AssignPath(0, 0);
    AssignPost(0, 0, 0);
    LockAI(0, false);
    UnlockAI(0);
    ForceBattleDecision(0, 0);
    SetGlobal(0, 0);
    GetGlobal(0);
    CleanFromHisBuildingBeforeTeleport(0);
    CleanFromScriptZoneBeforeTeleport(0, 0);
    AddToScriptZoneAfterTeleport(0, 0);
    InflictPain(0, 0, false);
    RecordEnterGame(0, 0, 0, 0);
    RecordLeaveGame(0, 0, 0, 0);
    RecordActionAvailable(0, 0, false);
    RecordCharacterAvailable(0, false);
    RecordLockCameraOn(0);
    GetCurrentAction(0);
    SetPathWalkingStyle(0, 0);
    Sees(0, 0);
    PutActorInBulding(0, 0);
    AttachScrollToNPC(0, 0);
    EnableViewCone(0);
    Select(0);
    ActivateDoorMouseSector(false, 0);
    CustomizeMinimapDisplay(0, 0);
    DefineFlatTrajectoryZone(0, 0);
    RecordSendMessage(0, 0);
    SendMessage(0, 0);
    RecordSendMessageWithArguments(0, 0, 0, 0);
    SendMessageWithArguments(0, 0, 0, 0);
    SetCompanyNumber(0, 0);
    SetAlwaysAttentive(0, false);
    DeclareAsCombatTrainer(0);
    AddPCToMissionTeam(0);
    RemovePCFromMissionTeam(0);
    GetNumberOfBeamMes();
    GetCustomCampaignValue(0);
    SetCustomCampaignValue(0, 0);
    GetCustomNPCValue(0, 0);
    SetInvisible(0, false);
    IsInvisible(0);
    RHUnk579810(0);
    RHUnk579820(0);
    RHUnk579830(0);
    RHUnk579840(0);
    RHUnk579850(0, false);
    RHUnk579870(0, false);
    RHUnk579880(0, false);
    RHUnk5798a0(0, false);
    GetScrollStatus(0);
    SetScrollStatus(0, 0);
    GetSoldierRank(0);
    IsActorDead(0);
    IsActorKO(0);
    IsActorTied(0);
    IsActorHS(0);
    AddToSequence(0, 0);
    GetNumberOfActorsInSector(0);
    RemoveAllSubordinates(0);
    SwitchToAlertPath(0);
    IsActorRider(0);
}

class RHSectorGateCalls
{
public:
    void FUN_0057dea0(RHElementActor *actor, bool mode);
};

class RHUnk0054b150
{
public:
    void FUN_0054b150(bool flag, bool immediate);
};

#include "RHActorScriptContext.h"


class RHUnk00580220
{
public:
    void FUN_00580220(int value);
};


class RHUnk00580330
{
public:
    void FUN_00580330(int first, unsigned short second);
};

class RHPCDescription;
class RHMinimap;
extern RHMinimap *g_unk0x6c0c50;

namespace VMCoreCustomDependencies
{
// FUNCTION: GAME 0x005714b0
bool FUN_005714b0(bool flag)
{
    ((RHUnk0054b150 *)g_unk0x6c0c50)->FUN_0054b150(flag, 0);
    return true;
}

// FUNCTION: GAME 0x00577090
void FUN_00577090(int first, int second)
{
    g_pEngine->FUN_004e3d20(first, second);
}

// FUNCTION: GAME 0x00578690
bool FUN_00578690(int object, int first, int second)
{
    return ((RHActorScriptContext *)((char *)object + 0x108))->FilterAIEvent((void *)first, second) != 0;
}

// FUNCTION: GAME 0x005786f0
void FUN_005786f0(int sector, int actor, bool mode)
{
    ((RHSectorGateCalls *)sector)->FUN_0057dea0((RHElementActor *)actor, mode);
}

// FUNCTION: GAME 0x005791f0
int FUN_005791f0(int index)
{
    void **descriptions = *(void ***)((char *)g_unk0x6c07fc + 0x1b4);
    void *element = descriptions[index];
    return (int)g_pEngine->GetPC((RHPCDescription *)element);
}

// FUNCTION: GAME 0x00579690
bool FUN_00579690()
{
    RHUnk00452030 *campaign = g_unk0x6c07fc;
    if (campaign == 0)
        return false;
    int value = campaign->Get(3);
    return value >= ((RHCampaign *)campaign)->FUN_00455af0();
}

// FUNCTION: GAME 0x005799d0
void FUN_005799d0(int first, int second, int third)
{
    RHSectorProduction *production = ((RHCampaign *)g_unk0x6c07fc)->FUN_00456a10(first);
    ((RHUnk00580330 *)production)->FUN_00580330(second, (unsigned short)third);
}

// FUNCTION: GAME 0x00579a00
void FUN_00579a00(int first, int second)
{
    RHSectorProduction *production = ((RHCampaign *)g_unk0x6c07fc)->FUN_00456a10(first);
    ((RHUnk00580220 *)production)->FUN_00580220(second);
}
}

// TEMPLATE: GAME 0x0057c710
// ?_Xran@?$vector@PAVRHCharacterProfile@@V?$allocator@PAVRHCharacterProfile@@@std@@@std@@IBEXXZ
