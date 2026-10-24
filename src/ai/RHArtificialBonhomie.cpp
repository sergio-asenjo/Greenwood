#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"
#include "RHElementActor.h"
#include "RHElementActorCivilianCore.h"
#include "RHArtificialIntelligenceCore.h"
#include "RHAIStateCalls.h"
#include "RHActorScriptContext.h"
#include "RHUnk0046bd20.h"
#include <stdlib.h>

extern char g_unk0x6c0691;
extern RHElementActor *g_unk0x6c100c;
class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

template <class T>
T &RHBonhomieField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

class RHBonhomieCompleteView
{
public:
    void Unk0040d980(int value)
    {
        ((RHScriptBatchCalls *)((char *)this + (*(int **)this)[1]))->Unk0040d980(value);
    }
};

// FUNCTION: GAME 0x0040d910
void RHArtificialBonhomie::FUN_0040d910(unsigned flags)
{
    RHBonhomieCompleteView *complete = (RHBonhomieCompleteView *)((char *)this - 0x1c);
    RHBonhomieField<unsigned short>(this, -6) = 0;
    if (RHBonhomieField<RHElementActor *>(this, (*(int **)complete)[1] - 0x18)->FUN_0046d710())
    {
        ((RHArtificialIntelligence *)RHBonhomieBase(this))->V3c(2);
        RHBonhomieField<unsigned char>(RHBonhomieBase(this), 0x175) = 1;
        complete->Unk0040d980(21);
    }
    else
        ((RHArtificialIntelligence *)RHBonhomieBase(this))->FUN_00411a00(flags);
}

// FUNCTION: GAME 0x0040d9e0
void RHArtificialBonhomie::FUN_0040d9e0(unsigned char frame)
{
    if (frame & 0x3f)
        return;
    switch (RHBonhomieField<int>(RHBonhomieBase(this), 0x14))
    {
    case 0x07:
    case 0x09:
    case 0x0d:
    case 0x17:
    case 0x44:
    case 0x8e:
    case 0x8f:
    case 0xdc:
    case 0xdd:
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe4:
    case 0xee:
        if (RHBonhomieField<RHUnk0046bd20 *>(RHBonhomieBase(this), 0x4)->FUN_0046bd20() != 0xa1)
            return;
        if (!((RHSequenceManager *)g_unk0x6c1040)->FUN_0058bd70(RHBonhomieField<void *>(RHBonhomieBase(this), 0x4), 0))
        {
            if (RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x38a) < 3)
            {
                ++RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x38a);
                return;
            }
            if (RHBonhomieField<void *>(RHBonhomieBase(this), 0x380))
                ((RHArtificialIntelligence *)RHBonhomieBase(this))->Unk00412240(RHBonhomieField<RHUnk00571160Position>(RHBonhomieBase(this), 0x378), RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x388), 1.0f);
            else
                ((RHBonhomieCompleteView *)((char *)this - 0x1c))->Unk0040d980(4);
            RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x38a) = 0;
            return;
        }
        RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x38a) = 0;
        return;
    default:
        RHBonhomieField<unsigned short>(RHBonhomieBase(this), 0x38a) = 0;
    }
}

// FUNCTION: GAME 0x0040dbe0
void RHBonhomieSpeechReceiver::FUN_0040dbe0(bool phase)
{
    if (phase)
        return;
    if (((RHElementActorCivilian *)RHBonhomieField<void *>((char *)this + (*(int **)this)[1], 4))->FUN_00470ca0())
    {
        unsigned short &timer = RHBonhomieField<unsigned short>(this, 0x14);
        if (timer > 0)
            --timer;
        else if (RHBonhomieField<int>((char *)this + (*(int **)this)[1], 0x258) == 0x79 && rand() % 3 == 0)
        {
            switch (rand() % 5)
            {
            case 0:
            case 1:
            case 2:
                ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(98, 0);
                break;
            case 3:
                ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(91, 0);
                break;
            case 4:
                ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(87, 0);
                break;
            }
        }
    }
    int offset = (*(int **)this)[1];
    RHArtificialIntelligence *base = (RHArtificialIntelligence *)((char *)this + offset);
    void *actor = RHBonhomieField<void *>(this, offset + 4);
    void *order = RHBonhomieField<void *>(actor, 0x134);
    if (order && RHBonhomieField<int>(order, 0x24) == 0xfa)
        base->Unk00418c40(87, 0);
}

// FUNCTION: GAME 0x0040dcb0
void RHArtificialBonhomie::FUN_0040dcb0(int state, int substate)
{
    ((RHArtificialIntelligence *)(RHBonhomieBase(this)))->Unk00422b70(2, substate);
    switch (state)
    {
    case 0:
    case 1:
    case 2:
        ((RHUnk00413640 *)(RHBonhomieBase(this)))->Unk(0, 0);
        break;
    case 3:
    case 6:
        ((RHUnk00413640 *)(RHBonhomieBase(this)))->Unk(1, 0);
        break;
    }
    RHElementActor *actor = RHBonhomieField<RHElementActor *>(RHBonhomieBase(this), 4);
    if (RHBonhomieField<unsigned char>(actor, 0x100) && g_unk0x6c0691)
    {
        RHElementActor *saved = g_unk0x6c100c;
        g_unk0x6c100c = actor;
        switch (state)
        {
        case 0:
            actor = RHBonhomieField<RHElementActor *>(RHBonhomieBase(this), 4);
            RHBonhomieField<RHActorScriptContext>(actor, 0x108).FilterAIEvent(actor, 0x64);
            break;
        case 1:
            actor = RHBonhomieField<RHElementActor *>(RHBonhomieBase(this), 4);
            RHBonhomieField<RHActorScriptContext>(actor, 0x108).FilterAIEvent(actor, 0x65);
            break;
        case 2:
            actor = RHBonhomieField<RHElementActor *>(RHBonhomieBase(this), 4);
            RHBonhomieField<RHActorScriptContext>(actor, 0x108).FilterAIEvent(actor, 0x66);
            break;
        case 3:
            actor = RHBonhomieField<RHElementActor *>(RHBonhomieBase(this), 4);
            RHBonhomieField<RHActorScriptContext>(actor, 0x108).FilterAIEvent(actor, 0x67);
            break;
        case 4:
            RHBonhomieField<RHActorScriptContext>(RHBonhomieField<void *>(RHBonhomieBase(this), 4), 0x108).FilterAIEvent(RHBonhomieField<void *>(RHBonhomieBase(this), 0x80), 0x68);
            break;
        case 5:
            RHBonhomieField<RHActorScriptContext>(RHBonhomieField<void *>(RHBonhomieBase(this), 4), 0x108).FilterAIEvent(RHBonhomieField<void *>(RHBonhomieBase(this), 0x80), 0x69);
            break;
        case 6:
            RHBonhomieField<RHActorScriptContext>(RHBonhomieField<void *>(RHBonhomieBase(this), 4), 0x108).FilterAIEvent(RHBonhomieField<void *>(RHBonhomieBase(this), 0x80), 0x6a);
            break;
        }
        g_unk0x6c100c = saved;
    }
    RHBonhomieField<int>(RHBonhomieBase(this), 0xc) = state;
    RHBonhomieField<int>(RHBonhomieBase(this), 0x14) = substate;
}

class RHBonhomieAdjustedReceiver
{
public:
    void FUN_0040eb90(bool enabled);
};

// FUNCTION: GAME 0x0040e0a0
int RHArtificialBonhomie::FUN_0040e0a0(SBFile &file)
{
    file.Access((char *)this - 0xc, 4);
    unsigned char mode;
    file.Access(&mode, 1);
    mode &= 0x7f;
    char *complete = (char *)this - 0x1c;
    switch (mode)
    {
    case 0:
        RHBonhomieField<int>(this, (*(int **)complete)[1] + 4) = 0;
        break;
    case 1:
        RHBonhomieField<int>(this, (*(int **)complete)[1] + 4) = 1;
        break;
    case 2:
        RHBonhomieField<int>(this, (*(int **)complete)[1] + 4) = 3;
        break;
    case 3:
        RHBonhomieField<int>(this, (*(int **)complete)[1] + 4) = 4;
        break;
    }
    file.Access((char *)this + (*(int **)complete)[1] + 8, 1);
    return 6;
}

// FUNCTION: GAME 0x0040e150
bool RHArtificialBonhomie::SerializeExactlyThisAI(SBFile &file)
{
    // STRING: GAME 0x006a73b0
    RHSerializeName(file, "RHArtificialBonhomie");

    if (file.m_version >= 0x22)
    {
        if (file.Access((char *)this - 6, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x006a7328
                     "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                     1444, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.m_version > 0x1d)
    {
        if (file.Access((char *)this - 8, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                     1449, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.Access((char *)this - 0x18, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1452, "Serialize failed reason is %s", reason);
        return false;
    }

    if (!FUN_00416b30(*(void **)((char *)this - 0x14), file))
    {
        SBAssert(1,
                 // STRING: GAME 0x006a7350
                 "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1453,
                 // STRING: GAME 0x006a7378
                 "Serialization failed");
        return false;
    }

    if (file.Access((char *)this - 0x10, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1454, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// FUNCTION: GAME 0x0040eb90
void RHBonhomieAdjustedReceiver::FUN_0040eb90(bool enabled)
{
    *(bool *)((char *)this - 0x10) = !enabled;
}

void EmitRHBonhomieAdjustedReceiver(RHBonhomieAdjustedReceiver *receiver, bool enabled)
{
    receiver->FUN_0040eb90(enabled);
}

void RHArtificialBonhomie::Emit(SBFile &file)
{
    FUN_0040d910(0);
    FUN_0040d9e0(0);
    FUN_0040dcb0(0, 0);
    ((RHBonhomieSpeechReceiver *)this)->FUN_0040dbe0(false);
    SerializeExactlyThisAI(file);
}
