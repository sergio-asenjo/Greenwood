#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"
#include "RHElementActor.h"
#include "RHElementActor_calls.h"
#include "RHElementActorCivilianCore.h"
#include "RHArtificialIntelligenceCore.h"
#include "RHAIStateCalls.h"
#include "RHActorScriptContext.h"
#include "RHUnk0046bd20.h"
#include "RHUnk005fc3b0.h"
#include "RHUnk00571160Position.h"
#include "RHMalignityPosition.h"
#include "RHPositionInterfaceCore.h"
#include "RHPathGeometryCalls.h"
#include "RHFastFindGridCore.h"
#include "RHElementActorNPC.h"
#include "RHSequenceManager.h"
#include <stddef.h>
#include <stdlib.h>

DECOMP_SIZE_ASSERT(RHArtificialBonhomie, 0x3a8)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_active) == 0x04)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_target) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_acceptsOrders) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_serialState) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_14w) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialBonhomie, m_16w) == 0x16)

// GLOBAL: GAME 0x00677428
// RHArtificialBonhomie::`vbtable'

// FUNCTION: GAME 0x0040bf20
RHArtificialBonhomie::RHArtificialBonhomie()
{
    m_0c = 1;
    m_20 = 2;
    m_target = 0;
    m_acceptsOrders = true;
    m_active = true;
    m_14w = 0;
    m_16w = 0;
}

// FUNCTION: GAME 0x0040bfb0
RHArtificialBonhomie::~RHArtificialBonhomie()
{
}

// SYNTHETIC: GAME 0x0040eb40
// RHArtificialBonhomie::`scalar deleting destructor'

void RHArtificialBonhomie::V30(void *, bool)
{
}

// STUB: GAME 0x0040bfd0
bool RHArtificialBonhomie::V24(RHMalignityStimulus *stimulus)
{
    unsigned event = stimulus->m_20;
    Unk00422b70(0, event);
    if (!AcceptStimulus(*stimulus))
    {
        FinishStimulus();
        return true;
    }
    bool handled = false;
    switch (event)
    {
    case 0: case 2: case 8: case 9: case 10: case 0xc: case 0xe: case 0xf:
    case 0x16: case 0x20: case 0x46:
        handled = FUN_0040d150(*stimulus);
        break;
    case 1: case 4: case 0xb: case 0xd: case 0x14: case 0x1e: case 0x2d:
    case 0x31: case 0x32:
        handled = HandleReactionStimulus(*stimulus);
        break;
    case 3: case 5: case 7: case 0x3b: case 0x3c: case 0x3d: case 0x3e:
    case 0x3f: case 0x40:
        handled = HandleStateStimulus(*stimulus);
        break;
    case 0x15:
        static_cast<RHArtificialIntelligence *>(this)->V00(0);
        break;
    }
    FinishStimulus();
    return handled;
}

extern char g_unk0x6c0691;
extern RHElementActor *g_unk0x6c100c;
class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;

SBGeoVector2D FUN_0040ec20(const RHMalignityPosition &first, RHMalignityPosition second);
RHMalignityPosition FUN_0040ece0(const RHMalignityPosition &position, SBGeoPoint2D point);

template <class T>
T &RHBonhomieField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

// FUNCTION: GAME 0x0040d910
void RHArtificialBonhomie::V00(int flags)
{
    m_16w = 0;
    if (m_npcActor->FUN_0046d710())
    {
        V3c(2);
        m_175 = true;
        RHBonhomieInterface(this)->DispatchWorldEvent(21);
    }
    else
        FUN_00411a00(flags);
}

// FUNCTION: GAME 0x0040d9e0
void RHArtificialBonhomie::V18(unsigned char frame)
{
    if (frame & 0x3f)
        return;
    switch (m_14)
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
        if (reinterpret_cast<RHUnk0046bd20 *>(m_npcActor)->FUN_0046bd20() != 0xa1)
            return;
        if (!RHSequenceManager::Instance()->FUN_0058bd70(m_npcActor, 0))
        {
            if (m_38a < 3)
            {
                ++m_38a;
                return;
            }
            if (m_380)
                Unk00412240(*reinterpret_cast<RHUnk00571160Position *>(m_378), m_388, 1.0f);
            else
                RHBonhomieInterface(this)->DispatchWorldEvent(4);
            m_38a = 0;
            return;
        }
        m_38a = 0;
        return;
    default:
        m_38a = 0;
    }
}

// FUNCTION: GAME 0x0040dbe0
void RHArtificialBonhomie::FUN_0040dbe0(bool phase)
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
void RHArtificialBonhomie::V10(int state, int substate)
{
    Unk00422b70(2, substate);
    switch (state)
    {
    case 0:
    case 1:
    case 2:
        SetMusicState(0, 0);
        break;
    case 3:
    case 6:
        SetMusicState(1, 0);
        break;
    }
    RHElementActorNPC *actor = m_npcActor;
    if (RHBonhomieField<unsigned char>(actor, 0x100) && g_unk0x6c0691)
    {
        RHElementActor *saved = g_unk0x6c100c;
        g_unk0x6c100c = actor;
        switch (state)
        {
        case 0:
            actor = m_npcActor;
            actor->m_108.FilterAIEvent(actor, 0x64);
            break;
        case 1:
            actor = m_npcActor;
            actor->m_108.FilterAIEvent(actor, 0x65);
            break;
        case 2:
            actor = m_npcActor;
            actor->m_108.FilterAIEvent(actor, 0x66);
            break;
        case 3:
            actor = m_npcActor;
            actor->m_108.FilterAIEvent(actor, 0x67);
            break;
        case 4:
            m_npcActor->m_108.FilterAIEvent(m_80, 0x68);
            break;
        case 5:
            m_npcActor->m_108.FilterAIEvent(m_80, 0x69);
            break;
        case 6:
            m_npcActor->m_108.FilterAIEvent(m_80, 0x6a);
            break;
        }
        g_unk0x6c100c = saved;
    }
    m_0c = state;
    m_14 = substate;
}

// FUNCTION: GAME 0x0040e0a0
int RHArtificialBonhomie::V0c(SBFile &file)
{
    file.Access(&m_serialState, 4);
    unsigned char mode;
    file.Access(&mode, 1);
    mode &= 0x7f;
    switch (mode)
    {
    case 0:
        m_20 = 0;
        break;
    case 1:
        m_20 = 1;
        break;
    case 2:
        m_20 = 3;
        break;
    case 3:
        m_20 = 4;
        break;
    }
    file.Access(&m_24, 1);
    return 6;
}

// FUNCTION: GAME 0x0040e150
bool RHArtificialBonhomie::V08(SBFile &file)
{
    // STRING: GAME 0x006a73b0
    RHSerializeName(file, "RHArtificialBonhomie");

    if (file.m_version >= 0x22)
    {
        if (file.Access(&m_16w, 2) < 0)
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
        if (file.Access(&m_14w, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                     1449, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.Access(&m_active, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1452, "Serialize failed reason is %s", reason);
        return false;
    }

    if (!FUN_00416b30(m_target, file))
    {
        SBAssert(1,
                 // STRING: GAME 0x006a7350
                 "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1453,
                 // STRING: GAME 0x006a7378
                 "Serialization failed");
        return false;
    }

    if (file.Access(&m_acceptsOrders, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHartificialbonhomie.cpp",
                 1454, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// FUNCTION: GAME 0x0040e7e0
bool RHArtificialBonhomie::ProposeGoodAppleChaseFleeDestination(RHMalignityPosition &destination)
{
    RHUnk005fc3b0 direction;
    RHMalignityPosition origin;
    origin = RHBonhomieInterface(this)->FUN_004165e0(RHBonhomieInterface(this)->m_actor, true);
    direction.FUN_005fc430(FUN_0040ec20(origin, RHBonhomieInterface(this)->FUN_004165e0(
        RHBonhomieField<void *>(RHBonhomieInterface(this), 0x90), true)));
    direction.Unk005fc6a0(0.57357645f);
    unsigned short heading = direction.FUN_005fcc50(0.57357645f);
    heading = (heading + rand() % 5 + 0xe) % 16;
    for (float step = 300.0f; step > 10.0f; step -= 10.0f)
    {
        short offset = 0;
        do
        {
            int value = offset;
            direction.Unk005fcd40((offset + heading) % 15, 0.57357645f);
            direction.FUN_005fc4d0(step);
            destination = FUN_0040ece0(origin, direction);
            void *actor = RHBonhomieInterface(this)->m_actor;
            RHPositionInterface *bounds = (RHPositionInterface *)((char *)RHBonhomieField<void *>(actor, 0x50) + 4);
            void *radius = bounds->Unk0055fa10(bounds->m_88);
            if (g_unk0x6c0a9c->Unk004f9170(
                    RHBonhomieInterface(this)->FUN_0040cbf0(origin),
                    RHBonhomieInterface(this)->FUN_0040cbf0(destination), origin.layer, radius))
                goto found;
            if (offset > 0)
                offset = -value;
            else
                offset = 1 - value;
        } while (offset < 8);
    }
    return false;
found:
    return true;
}

// FUNCTION: GAME 0x0040eb90
void RHArtificialBonhomie::V38(bool enabled)
{
    m_acceptsOrders = !enabled;
}
