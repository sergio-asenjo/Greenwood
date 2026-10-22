#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"
#include "RHElementActor.h"
#include "RHElementActorCivilianCore.h"
#include "RHArtificialIntelligenceCore.h"
#include <stdlib.h>

template <class T>
T &RHBonhomieField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

// Parked: incoming and complete-object pointers occupy opposite saved registers.
// STUB: GAME 0x0040d910
void RHArtificialBonhomie::FUN_0040d910(unsigned flags)
{
    char *complete = (char *)this - 0x1c;
    RHBonhomieField<unsigned short>(this, -6) = 0;
    int *table = *(int *volatile *)complete;
    if (RHBonhomieField<RHElementActor *>(this, table[1] - 0x18)->FUN_0046d710())
    {
        ((RHArtificialIntelligence *)((char *)this + (*(int **)complete)[1] - 0x1c))->V3c(2);
        RHBonhomieField<unsigned char>(this, (*(int **)complete)[1] + 0x159) = 1;
        ((RHScriptBatchCalls *)(complete + (*(int **)complete)[1]))->Unk0040d980(21);
    }
    else
        ((RHArtificialIntelligence *)((char *)this + (*(int **)complete)[1] - 0x1c))->FUN_00411a00(flags);
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

class RHBonhomieAdjustedReceiver
{
public:
    void FUN_0040eb90(bool enabled);
};

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
    ((RHBonhomieSpeechReceiver *)this)->FUN_0040dbe0(false);
    SerializeExactlyThisAI(file);
}
