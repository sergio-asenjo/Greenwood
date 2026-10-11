#include "SBNullstr.h"
#include "RHElementActorHuman.h"
#include <stdlib.h>

extern float g_unk0x0067749c;
extern float g_unk0x00677f7c;
extern char g_unk0x6c0560[4];
extern float g_unk0x00677488;
extern float g_unk0x006774e4;
extern float g_unk0x006774f0;

// GLOBAL: GAME 0x006b793c
int g_unk0x006b793c[16] = { 0, 1, 2, 3, 1, 4, 5, 6, 2, 5, 7, 8, 3, 6, 8, 9 };
// GLOBAL: GAME 0x006b797c
int g_unk0x006b797c[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

DECOMP_SIZE_ASSERT(RHElementActorHuman, 0x49c)
DECOMP_SIZE_ASSERT(RHUnk0046bd20, 0x134)
DECOMP_SIZE_ASSERT(RHUnk005864a0, 0x7c)
DECOMP_SIZE_ASSERT(RHUnk005c1d50, 0x08)
DECOMP_SIZE_ASSERT(RHHumanMapNode, 0x14)
DECOMP_SIZE_ASSERT(RHHumanMapIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanMap, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00586f70, 0x74)
DECOMP_SIZE_ASSERT(RHUnk0058bed0Object, 0x04)
DECOMP_SIZE_ASSERT(RHHumanEngineActorArray, 0x4964)
DECOMP_SIZE_ASSERT(RHHumanOpponent, 0x08)
DECOMP_SIZE_ASSERT(RHHumanOpponentNode, 0x10)
DECOMP_SIZE_ASSERT(RHHumanOpponentIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanList, 0x18)
DECOMP_SIZE_ASSERT(RHHumanVirtualCalls, 0x04)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005866a0, 0x74)
DECOMP_SIZE_ASSERT(RHSoundSettings, 0x18)
DECOMP_SIZE_ASSERT(RHSoundChannelSettings, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0044d400, 0x294)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHHumanFloatNode, 0x0c)
DECOMP_SIZE_ASSERT(RHHumanFloatIterator, 0x04)
DECOMP_SIZE_ASSERT(RHSeqList, 0x0c)
DECOMP_SIZE_ASSERT(RHHumanFloatList, 0x18)

struct RHUnk0047c420Message
{
    void *m_00;
    undefined m_04[0x18];
    int m_1c;
    int m_20;
    int m_24;
    undefined m_28;
    ~RHUnk0047c420Message() {}
};

DECOMP_SIZE_ASSERT(RHUnk0047c420Message, 0x2c)

class RHUnk0046bcb0
{
public:
    void Unk(int value);
};

// Parked: propagation register lifetimes and EH scheduling differ.
// STUB: GAME 0x0044d400
void RHUnk0044d400::FUN_0044d400(int value, bool propagate)
{
    bool shared;
    switch (value)
    {
    case 59: case 60: case 61: case 62: case 63: case 64: case 65:
        shared = false;
        break;
    case 66: case 67:
        shared = true;
        break;
    default:
        return;
    }
    if (propagate && shared)
    {
        int offset = ((RHHumanVirtualCalls *)Actor())->V130() << 5;
        void **first = RHActorField<void **>(g_pEngine, offset + 0x4ccc);
        unsigned short count = first ? RHActorField<void **>(g_pEngine, offset + 0x4cd0) - first : 0;
        SBGeoVector2D radius(400.0f, 400.0f);
        SBGeoPoint2D center(RHActorField<SBGeoPoint2D>(RHActorField<void *>(Actor(), 0x50), 0x24));
        SBGeoBoundingBox2D box(center.FUN_005fc200(radius), center.Unk005fc190(radius));
        for (unsigned short i = 0; i < count; ++i)
        {
            void *actor = RHActorField<void **>(g_pEngine, offset + 0x4ccc)[i];
            if (actor != Actor() && (RHActorField<unsigned>(actor, 4) & 31) == 20)
            {
                int *base = RHActorField<int *>(actor, 0x49c);
                if (RHActorField<int>(actor, base[1] + 0x4a8) == 4 &&
                    ((RHHumanVirtualCalls *)actor)->V124() >= 70 &&
                    box.FUN_00608400(((RHHumanActorCalls *)actor)->FUN_004237d0()))
                    ((RHUnk0044d400 *)((char *)actor + 0x6e8))->FUN_0044d400(value, false);
            }
        }
    }
    if (value != m_288)
    {
        if (value != m_28c)
            m_290 = m_28c;
        m_28c = m_288;
        m_288 = value;
        unsigned short amount = ((RHHumanVirtualCalls *)Actor())->V124();
        if (amount < 50)
            m_28c = 0;
        if (amount < 80)
            m_290 = 0;
    }
}

// FUNCTION: GAME 0x0046bd20
int RHUnk0046bd20::FUN_0046bd20()
{
    if (!m_130)
        return 0xa1;
    return m_130->m_10;
}

#define RH_HUMAN_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, sourceFile, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// TEMPLATE: GAME 0x00471440
// ?_Ucopy@?$vector@GV?$allocator@G@std@@@std@@IAEPAGPBG0PAG@Z

// TEMPLATE: GAME 0x00471470
// ?_Ufill@?$vector@GV?$allocator@G@std@@@std@@IAEXPAGIABG@Z

// Parked: posture/combat dispatch and original EH states remain incomplete.
// STUB: GAME 0x00472070
void RHElementActorHuman::Translate(RHSequenceElement *element, RHcommand command)
{
    RHUnk005fc3b0 point;
    int selected = command ? command : element->m_10;
    RHActorTranslationSequenceCalls *sequence = (RHActorTranslationSequenceCalls *)element;
    int orderCode;
    bool target = true;
    switch (selected)
    {
    case 60: orderCode = 0x44; break;
    case 61: orderCode = 0x4b; break;
    case 62: orderCode = 0x46; break;
    case 63: orderCode = 0x45; break;
    case 64: orderCode = 0x4a; break;
    case 65: orderCode = 0x49; break;
    case 66: orderCode = 0x48; break;
    case 67: orderCode = 0x47; break;
    case 68:
        orderCode = 0x65;
        target = false;
        break;
    case 69: orderCode = 0x64; break;
    case 70:
        orderCode = 0x60;
        target = false;
        break;
    case 71:
    {
        int action = command ? RHActorField<int>(element, 0x40) : RHActorField<int>(this, 0x144);
        orderCode = action >= 4 && action <= 6 ? 0x75 :
            ((action >= 7 && action <= 11) || action == 15) ? 0x6e : 0x31;
        target = false;
        break;
    }
    case 85:
        orderCode = RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c) == 10 ? 0x11a : 0x17a;
        break;
    case 110:
        if (RHActorField<int>(this, 0x144) == 12)
        {
            sequence->V0c(0, true);
            return;
        }
        orderCode = 0xaa;
        target = false;
        break;
    case 111:
        orderCode = 0xad;
        target = false;
        break;
    case 112:
        orderCode = 0xac;
        target = false;
        break;
    case 29:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 74:
    case 75:
    case 76:
    case 84:
    case 86:
    case 160:
    case 161:
    case 169:
    case 176:
    case 178:
        return;
    default:
        ((RHElementActor *)this)->Translate(element, command);
        return;
    }
    RHOrder *order = new RHOrder;
    order->m_24 = orderCode;
    order->m_2a = 0;
    if (target)
        order->m_30 = RHActorField<void *>(element, 0x64);
    sequence->FUN_00585970(order);
}

// Parked: sequence-list cursor uses ebx instead of ebp, shifting failure branches.
// STUB: GAME 0x004799e0
bool RHElementActorHuman::Serialize(SBFile &file)
{
    // STRING: GAME 0x006ae46c
    const char *sourceFile = "P:\\Robin Hood\\RHelementactorhuman.cpp";
    // STRING: GAME 0x006ae55c
    RHSerializeName(file, "RHElementActorHuman");
    if (file.m_version >= 21)
    {
        RH_HUMAN_ACCESS(m_23f, 1, 5745);
    }
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1ca), 2, 5748);
    RH_HUMAN_ACCESS(*((char *)this + 0x1ce), 1, 5751);
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1cc), 2, 5752);
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1c8), 2, 5753);
    RH_HUMAN_ACCESS(m_492, 2, 5754);
    RH_HUMAN_ACCESS(m_494, 2, 5755);
    RH_HUMAN_ACCESS(m_496, 1, 5756);
    RH_HUMAN_ACCESS(m_497, 1, 5757);
    RH_HUMAN_ACCESS(m_288, 1, 5758);
    RH_HUMAN_ACCESS(m_289, 1, 5759);
    RH_HUMAN_ACCESS(m_28a, 2, 5760);
    RH_HUMAN_ACCESS(m_23e, 1, 5761);
    unsigned opponentCount;
    RHHumanOpponent opponent;
    if (file.m_bLoading)
    {
        RHHumanList &list = m_260;
        list.Clear();
        RH_HUMAN_ACCESS(opponentCount, 2, 5772);
        for (unsigned short i = 0; i < (unsigned short)opponentCount; ++i)
        {
            g_pEngine->FUN_004c3bd0(file, opponent.m_actor);
            (*(RHFastFindGrid **)((char *)this + 0x64))->SerializeLinePointer(file, opponent.m_line);
            ((RHHumanOpponentListCalls *)&list)->FUN_00486110(RHHumanOpponentIterator((RHHumanOpponentNode *)list.head), opponent);
            list.valid = 1;
        }
    }
    else
    {
        opponentCount = m_260.count;
        RH_HUMAN_ACCESS(opponentCount, 2, 5786);
        for (unsigned short i = 0; i < (unsigned short)opponentCount; ++i)
        {
            RHHumanList &list = m_260;
            ((RHTitbitList *)&list)->At(i);
            opponent = ((RHHumanOpponentNode *)list.cursor)->value;
            g_pEngine->FUN_004c3bd0(file, opponent.m_actor);
            (*(RHFastFindGrid **)((char *)this + 0x64))->SerializeLinePointer(file, opponent.m_line);
        }
    }
    RH_HUMAN_ACCESS(m_490, 1, 5797);
    RH_HUMAN_ACCESS(m_480, 4, 5800);
    RH_HUMAN_ACCESS(m_484, 4, 5801);
    RH_HUMAN_ACCESS(m_488, 2, 5802);
    RH_HUMAN_ACCESS(m_48a, 1, 5803);
    RH_HUMAN_ACCESS(m_48c, 4, 5804);
    RHEngine *engine = g_pEngine;
    engine->SerializeNestedB(file, &m_254);
    ((RHUnk004b2190Member *)m_43c)->Serialize(file);
    RH_HUMAN_ACCESS(m_47c, 1, 5812);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_498);
    RH_HUMAN_ACCESS(m_1d0, 28, 5816);
    ((RHElementActor *)this)->RHElementActor::Serialize(file);
    ((RHSightObstacle *)m_294)->Serialize(file);
    unsigned actorCount;
    void *actor;
    if (file.m_bLoading)
    {
        RHHumanList &list = m_20c;
        list.Clear();
        RH_HUMAN_ACCESS(actorCount, 2, 5832);
        for (unsigned short i = 0; i < (unsigned short)actorCount; ++i)
        {
            g_pEngine->FUN_004c3bd0(file, actor);
            list.Insert(actor);
            list.valid = 1;
        }
    }
    else
    {
        actorCount = m_20c.count;
        RH_HUMAN_ACCESS(actorCount, 2, 5844);
        for (unsigned short i = 0; i < (unsigned short)actorCount; ++i)
        {
            RHHumanList &list = m_20c;
            ((RHTitbitList *)&list)->At(i);
            actor = list.cursor->data;
            g_pEngine->FUN_004c3bd0(file, actor);
        }
    }
    RH_HUMAN_ACCESS(m_230, 4, 5853);
    RH_HUMAN_ACCESS(m_234, 4, 5854);
    RH_HUMAN_ACCESS(m_238, 4, 5855);
    RH_HUMAN_ACCESS(m_23c, 2, 5858);
    for (unsigned i = 0; i < 9; ++i)
    {
        RH_HUMAN_ACCESS(m_240[i], 2, 5863);
    }
    if (file.m_bLoading)
    {
        RHHumanList &list = m_1b8;
        RHScriptNode *sentinel = list.head;
        RHScriptNode *current = sentinel->next;
        while (current != sentinel)
        {
            RHScriptNode *previous = current;
            current = current->next;
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter(previous));
        }
        if (file.m_version >= 28)
        {
            unsigned count;
            RH_HUMAN_ACCESS(count, 4, 5876);
            list.Resize(count, (void *)0);
            for (std::list<RHSequenceElement *>::iterator node = ((std::list<RHSequenceElement *> *)&m_1b8)->begin(); node != ((std::list<RHSequenceElement *> *)&m_1b8)->end(); ++node)
                (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &*node, true);
        }
    }
    else
    {
        unsigned count = m_1b8.count;
        RH_HUMAN_ACCESS(count, 4, 5889);
        for (std::list<RHSequenceElement *>::iterator node = ((std::list<RHSequenceElement *> *)&m_1b8)->begin(); node != ((std::list<RHSequenceElement *> *)&m_1b8)->end(); ++node)
            (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &*node, true);
    }
    if (file.m_version >= 33)
    {
        RH_HUMAN_ACCESS(m_28c, 4, 5899);
        engine->FUN_004c3bd0(file, m_290);
    }
    return true;
}

// FUNCTION: GAME 0x0047b760
int RHElementActorHuman::FUN_0047b760(void *actor, int *value)
{
    int other;
    if ((RHActorField<unsigned>(actor, 4) & 7) == 4)
    {
        if (RHActorField<int>(RHActorField<void *>(actor, 0x50), 0x8c) != 19)
        {
            RHUnk00613e90 point;
            ((RHHumanActorCalls *)actor)->FUN_00479320(point);
            return ((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false);
        }
        else
        {
            RHUnk00613e90 point;
            ((RHHumanActorCalls *)actor)->FUN_00479320(point);
            if (!((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false))
            {
                if (*value == 1)
                {
                    ((RHElementActor *)actor)->FUN_00478c20(point, false);
                    if (((RHHumanActorCalls *)this)->FUN_0047b8a0(point, &other, false) && other == 0)
                        *value = 0;
                }
                return 0;
            }
            ((RHElementActor *)actor)->FUN_00478c20(point, false);
            return ((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false);
        }
    }
    if (RHActorField<undefined>(g_pEngine, 0x4aa8))
        return ((RHHumanActorCalls *)this)->FUN_0047b8a0(RHActorField<RHUnk00613e90>(RHActorField<void *>(actor, 0x50), 0x10), value, true);
    return ((RHHumanActorCalls *)this)->FUN_0047b8a0(RHActorField<RHUnk00613e90>(RHActorField<void *>(actor, 0x50), 0x10), value, false);
}

// Parked: message input loads are hoisted and adjusted-receiver registers differ.
// STUB: GAME 0x0047c420
void RHElementActorHuman::FUN_0047c420(void *value)
{
    if (m_260.count == 0)
    {
        ((RHUnk0046bcb0 *)this)->Unk(7);
        if ((RHActorField<unsigned>(this, 4) & 31) == 20)
        {
            RHUnk0047c420Message message;
            message.m_24 = 0;
            message.m_28 = 0;
            message.m_20 = 23;
            message.m_00 = value;
            message.m_1c = 3;
            int *base = RHActorField<int *>(this, 0x49c);
            ((RHHumanVirtualCalls *)((char *)this + 0x49c + base[1]))->V024(&message);
        }
    }
}

// FUNCTION: GAME 0x0047c4c0
int RHElementActorHuman::FUN_0047c4c0(RHElementActorHuman *actor)
{
    if (((RHHumanVirtualCalls *)this)->V048() || RHActorField<undefined>(this, 0x1ce) || m_23c != 0)
        return 0;
    if (!actor || ((RHHumanVirtualCalls *)actor)->V048() || RHActorField<undefined>(actor, 0x1ce) || actor->m_23c != 0)
        return 0;
    void *first = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    if ((undefined)(RHActorField<unsigned>(first, 0x30) >> 13) & 1)
        return 0;
    void *second = RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0);
    if ((undefined)(RHActorField<unsigned>(second, 0x30) >> 13) & 1)
        return 0;
    if ((RHActorField<unsigned>(this, 4) & 31) == 20 &&
        ((RHHumanVirtualCalls *)this)->V0f8() && !((RHHumanVirtualCalls *)actor)->V168())
        return 0;
    if ((RHActorField<unsigned>(actor, 4) & 31) == 20 &&
        ((RHHumanVirtualCalls *)actor)->V0f8() && !((RHHumanVirtualCalls *)this)->V168())
        return 0;
    first = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    if (((undefined)(RHActorField<unsigned>(first, 0x30) >> 9) & 1) &&
        (RHActorField<int>(first, 0xf0) == 3 || RHActorField<int>(first, 0xf0) == 2))
        return 0;
    second = RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0);
    if (((undefined)(RHActorField<unsigned>(second, 0x30) >> 9) & 1) &&
        (RHActorField<int>(second, 0xf0) == 3 || RHActorField<int>(second, 0xf0) == 2))
        return 0;
    return 1;
}

// deferred: coupled to RHScript::StopActor pending reccmp #534.
void RHUnk0047ca50::Unk()
{
    RHElementActorHuman *actor = (RHElementActorHuman *)this;
    unsigned count = actor->m_260.count;
    for (unsigned i = 0; i < count; ++i)
    {
        ((RHTitbitList *)&actor->m_260)->At(i);
        ((RHHumanActorCalls *)actor->m_260.cursor->data)->FUN_0047d270(this);
    }
    RHHumanList &list = actor->m_260;
    RHScriptNode *sentinel = list.head;
    RHScriptNode *current = sentinel->next;
    while (current != sentinel)
    {
        RHScriptNode *previous = current;
        current = current->next;
        ((RHUnk0046eb30 *)&list)->erase(RHScriptIter(previous));
    }
    list.valid = 1;
    if (!((RHHumanVirtualCalls *)this)->V048())
    {
        unsigned type = RHActorField<unsigned>(this, 4);
        if ((type & 15) == 12)
            ((RHHumanActorCalls *)this)->FUN_0049d780();
        else if ((type & 31) == 20)
        {
            int *base = RHActorField<int *>(this, 0x49c);
            ((RHScriptBatchCalls *)((char *)this + 0x49c + base[1]))->Unk0040d980(24);
        }
    }
}

// Parked: cached-cursor expansion and opponent-swap receiver scheduling differ.
// STUB: GAME 0x0047d920
void RHElementActorHuman::FUN_0047d920(RHElementActorHuman *actor)
{
    unsigned count = m_260.count;
    for (unsigned short i = 0; i < (unsigned short)count; ++i)
    {
        if (RHHumanOpponentAt(m_260, i).m_actor == actor)
        {
            ((RHTitbitList *)&m_260)->At(0);
            RHHumanOpponent &first = ((RHHumanOpponentNode *)m_260.cursor)->value;
            ((RHTitbitList *)&m_260)->At(i);
            RHHumanOpponent &selected = ((RHHumanOpponentNode *)m_260.cursor)->value;
            RHHumanOpponent previous = selected;
            selected = first;
            RHHumanOpponentAt(m_260, 0) = previous;
            ((RHHumanActorCalls *)this)->FUN_0047d4c0();
            return;
        }
    }
    if ((undefined)FUN_0047c4c0(actor))
    {
        RHUnk005866a0 *element = new RHUnk005866a0(1, 50, this);
        element->Unk00586ed0(33, (int)actor);
        element->Unk00586ed0(24, 0);
        element->Unk00586e00(34, false);
        ((RHScriptBatchCalls *)RHActorField<void *>(this, 0x5c))->Unk0058a940(g_unk0x6c0560, 0, element);
    }
}

// Parked: word-result narrowing and zero-result return tails differ.
// STUB: GAME 0x0047e7d0
int RHElementActorHuman::FUN_0047e7d0(RHUnk005864a0 *element)
{
    int result = 0;
    RHUnk005c1d50 *weapon = (RHUnk005c1d50 *)element->FUN_005864b0();
    if (RHActorField<int>(this, 0x144) == 11 || RHActorField<int>(this, 0x144) == 10)
    {
        if ((RHActorField<int>(this, 0x144) == 10 && element->FUN_005864d0() != 12 && element->FUN_005864d0() != 13) ||
            RHActorField<int>(this, 0x144) == 11)
            return 4;
    }
    else if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c))
    {
        unsigned short chance = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(element->FUN_005864d0());
        chance = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1b70(this, (void *)element->FUN_005864a0(), chance);
        if (rand() % 99 + 1 > chance)
        {
            chance = weapon->FUN_005c1dd0(element->FUN_005864d0(), (void *)element->FUN_005864a0());
            if (chance > 0)
            {
                ((RHHumanVirtualCalls *)this)->V0bc(chance, (void *)element->FUN_005864a0());
                if (((RHHumanVirtualCalls *)this)->V048())
                {
                    unsigned count = RHActorField<unsigned>(RHActorField<void *>(this, 0x1c4), 8);
                    unsigned amount = 20;
                    unsigned other = RHActorField<unsigned>(RHActorField<void *>((void *)element->FUN_005864a0(), 0x1c4), 8);
                    if (count > other)
                        amount += count - other;
                    ((RHHumanVirtualCalls *)element->FUN_005864a0())->V0c8(0, amount);
                }
                result = 1;
            }
        }
        chance = RHActorField<unsigned short>(RHActorField<void *>(RHActorField<void *>(this, 0x25c), 4), 0x12);
        if (rand() % 99 + 1 > chance)
        {
            chance = ((RHHumanWeaponCalls *)weapon)->FUN_005c1db0(element->FUN_005864d0());
            if (chance > 0)
            {
                ((RHHumanVirtualCalls *)this)->V0d8(chance, (void *)element->FUN_005864a0());
                return result | 2;
            }
        }
    }
    else
        return 3;
    return result;
}

// FUNCTION: GAME 0x0047e9d0
void RHElementActorHuman::FUN_0047e9d0(RHUnk005864a0 *element)
{
    unsigned short value = RHActorField<unsigned short>(element, 0x68);
    ((RHHumanVirtualCalls *)this)->V0bc(value, (void *)element->FUN_005864a0());
    value = RHActorField<unsigned short>(element, 0x6a);
    ((RHHumanVirtualCalls *)this)->V0d8(value, (void *)element->FUN_005864a0());
}

// FUNCTION: GAME 0x004838f0
int RHElementActorHuman::FUN_004838f0(bool alternate)
{
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1:
    case 6:
    case 8:
    case 11:
    case 14:
    case 15:
    case 19:
    case 21:
    case 23:
    case 24:
        switch (RHActorField<unsigned>(this, 0x144))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 12:
        case 14:
        case 16:
        case 17:
            return alternate ? 0x137 : 0x133;
        case 4:
        case 5:
        case 6:
            return alternate ? 0x138 : 0x134;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 15:
            return alternate ? 0x139 : 0x135;
        case 13:
            break;
        }
        return alternate ? 0x137 : 0x133;
    case 10:
    case 20:
    case 22:
        return alternate ? 0x13a : 0x136;
    default:
        return 0x11b;
    }
}

// Parked: cached-cursor reset and advance paths merge differently.
// STUB: GAME 0x00484a70
int RHElementActorHuman::FUN_00484a70(void *value)
{
    unsigned count = m_260.count;
    int result = 0;
    if (count != 0)
    {
        for (int i = 0; i < count; ++i)
        {
            void *actor = RHHumanOpponentAt(m_260, i).m_actor;
            if (RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0) == value)
                ++result;
        }
    }
    return result;
}

// Parked: cached-list expansion, local frame size and x87 scheduling differ.
// STUB: GAME 0x00484bb0
bool RHElementActorHuman::FUN_00484bb0(RHElementActorHuman *actor, SBGeoPoint2D &result, void *line)
{
    unsigned count = actor->m_260.count;
    void *area = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    RHUnk0042fde0 *segment = (RHUnk0042fde0 *)((char *)line + 4);
    SBGeoPoint2D direction = segment->FUN_0042fde0();
    float margin = g_unk0x006774e4 / ((RHUnk005fc3b0 *)&direction)->Unk005fc6a0(1.0f);
    char allocator;
    RHHumanFloatList fractions(allocator);
    float position = segment->FUN_0060ba80(RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24));
    float fraction;
    for (unsigned i = 0; i < count; ++i)
    {
        ((RHTitbitList *)&actor->m_260)->At((unsigned short)i);
        void *opponent = actor->m_260.cursor->data;
        if (opponent != this && RHActorField<void *>(RHActorField<void *>(opponent, 0x50), 0xe0) == area)
        {
            fraction = segment->FUN_0060ba80(RHActorField<SBGeoPoint2D>(RHActorField<void *>(opponent, 0x50), 0x24));
            fractions.FUN_00424410(RHHumanFloatIterator(fractions.m_head), fraction);
            fractions.valid = 1;
        }
    }
    float lower;
    switch (fractions.m_count)
    {
    case 0:
        if (position >= g_unk0x0067749c)
            result = RHActorField<SBGeoPoint2D>(line, 0x0c);
        else if (position <= g_unk0x00677488)
            result = *(SBGeoPoint2D *)segment;
        else
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(position, (const SBGeoVector2D &)direction));
        return true;
    case 1:
        lower = fraction - margin;
        margin += fraction;
        break;
    case 2:
    {
        lower = fractions.m_head->next->value;
        fractions.At(1);
        float other = fractions.cursor->value;
        if (lower > other)
        {
            float temporary = lower;
            lower = other;
            other = temporary;
        }
        lower -= margin;
        margin += other;
        break;
    }
    default:
        return false;
    }
    if (position >= g_unk0x00677488 && position <= g_unk0x0067749c &&
        (position <= lower || position >= margin))
    {
        result = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24);
        return true;
    }
    if (lower >= g_unk0x00677488)
    {
        if (margin <= g_unk0x0067749c)
        {
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(margin, (const SBGeoVector2D &)direction));
            SBGeoPoint2D alternate = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(lower, (const SBGeoVector2D &)direction));
            SBGeoPoint2D &current = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24);
            if (current.Unk005fc110(alternate).Unk005fc6d0(1.0f) < current.Unk005fc110(result).Unk005fc6d0(1.0f))
                result = alternate;
        }
        else
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(lower, (const SBGeoVector2D &)direction));
        fractions.FUN_0044e8b0(fractions.FUN_0046eb80(), RHHumanFloatIterator(fractions.m_head));
        return true;
    }
    if (margin <= g_unk0x0067749c)
    {
        result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(margin, (const SBGeoVector2D &)direction));
        fractions.Release();
        return true;
    }
    fractions.Release();
    return false;
}

// FUNCTION: GAME 0x00486110
RHHumanOpponentIterator RHHumanOpponentListCalls::FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value)
{
    RHHumanOpponentNode *next = position.node;
    RHHumanOpponentNode *previous = next->previous;
    RHHumanOpponentNode *node = (RHHumanOpponentNode *)::operator new(sizeof(RHHumanOpponentNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->value) RHHumanOpponent(value);
    ++((RHHumanList *)this)->count;
    return RHHumanOpponentIterator(node);
}

// Parked: count setup and loop scheduling differ.
// STUB: GAME 0x0048c5b0
void FUN_0048c5b0(void *actor, int value)
{
    unsigned short count = ((RHHumanEngineActorArray *)g_pEngine)->Size();
    if (count > 0)
    {
        int remaining = count;
        int offset = 0;
        do
        {
            RHMalignityActorCalls **actors = RHActorField<RHMalignityActorCalls **>(g_pEngine, 0x495c);
            RHActorField<RHMalignityActorCalls *>(actors, offset)->FUN_0048c700(actor, value);
            offset += 4;
        } while (--remaining);
    }
    if (value == 1)
        RHActorField<undefined>(actor, 0x23f) = 1;
}

// FUNCTION: GAME 0x005864a0
undefined4 RHUnk005864a0::FUN_005864a0()
{
    return m_64;
}

// FUNCTION: GAME 0x005864b0
undefined4 RHUnk005864a0::FUN_005864b0()
{
    return m_70;
}

// FUNCTION: GAME 0x005864c0
undefined4 RHUnk005864a0::FUN_005864c0()
{
    return m_78;
}

// FUNCTION: GAME 0x005864d0
undefined4 RHUnk005864a0::FUN_005864d0()
{
    return m_74;
}

// FUNCTION: GAME 0x00586f70
void RHUnk00586f70::FUN_00586f70(int key, undefined value)
{
    *(undefined *)&m_64.find(key)->m_value = value;
}

// FUNCTION: GAME 0x005870c0
undefined RHUnk00586f70::FUN_005870c0(int key)
{
    return *(undefined *)&m_64.find(key)->m_value;
}

// FUNCTION: GAME 0x00587340
undefined4 RHUnk00586f70::FUN_00587340(int key)
{
    RHHumanMapIterator position = m_64.find(key);
    if (position != m_64.end())
        return position->m_value;
    return *(volatile int *)&key;
}

// Parked: cursor reload ordering and unlink registers differ.
// STUB: GAME 0x0058bed0
void RHManagerListCalls::FUN_0058bed0()
{
    RHHumanList &list = *(RHHumanList *)this;
    for (list.cursor = list.head->next; list.cursor != list.head; list.cursor = list.cursor->next)
        delete (RHUnk0058bed0Object *)list.cursor->data;
    RHScriptNode *sentinel = list.head;
    RHScriptNode *current = sentinel->next;
    while (current != sentinel)
    {
        RHScriptNode *previous = current;
        current = current->next;
        previous->previous->next = previous->next;
        previous->next->previous = previous->previous;
        ::operator delete(previous);
        --list.count;
    }
}

// FUNCTION: GAME 0x005a8220
bool RHSound::FUN_005a8220(int first, int second, int third, const SBGeoPoint2D &point)
{
    if (RHActorField<undefined>(this, 0x20b))
    {
        RHSoundSettings sound;
        sound.m_00 = 3;
        *(SBGeoPoint2D *)sound.m_04 = point;
        int variant = (rand() * 2) * g_unk0x00677f7c;
        *(undefined *)sound.m_10 = 0;
        sound.m_0c = (void *)(variant + (g_unk0x006b793c[third + second * 4] + first * 10) * 2);
        RHSoundChannelSettings settings;
        if (((RHSoundGeometryView *)((char *)this + 0x138))->FUN_005b2ff0(sound, false, settings))
            FUN_005a72c0(sound, settings, 0);
        else
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x005a8330
bool RHSound::FUN_005a8330(int first, int second, int third, const SBGeoPoint2D &point)
{
    if (RHActorField<undefined>(this, 0x20b))
    {
        RHSoundSettings sound;
        sound.m_00 = 3;
        *(SBGeoPoint2D *)sound.m_04 = point;
        *(undefined *)sound.m_10 = 0;
        sound.m_0c = (void *)(g_unk0x006b797c[third + second * 3] + first * 12 + 30);
        RHSoundChannelSettings settings;
        if (((RHSoundGeometryView *)((char *)this + 0x138))->FUN_005b2ff0(sound, false, settings))
            FUN_005a72c0(sound, settings, 0);
        else
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x005c1d50
undefined4 RHUnk005c1d50::FUN_005c1d50(int index)
{
    if (index < 10)
        return *(undefined4 *)(m_04 + ((index + 1) << 5));
    return 0;
}

// FUNCTION: GAME 0x005c1dd0
unsigned short RHUnk005c1d50::FUN_005c1dd0(int index, void *actor)
{
    float scale;
    if ((RHActorField<unsigned>(actor, 4) & 31) == 20 &&
        RHActorField<int>(RHActorField<void *>(actor, 0xa1c), 0x58) == 0)
        scale = ((RHHumanVirtualCalls *)actor)->V124() * g_unk0x006774f0 + g_unk0x0067749c;
    else
        scale = g_unk0x0067749c;
    switch (index)
    {
    case 0: case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 8: case 9:
        return RHActorField<unsigned short>(m_04, (index << 5) + 0x2a) * scale;
    case 12: case 13:
        return 1;
    default:
        return 0;
    }
}

void RHElementActorHuman::Emit(SBFile &file, RHSequenceElement *element, RHcommand command)
{
    Translate(element, command);
    ((RHUnk0044d400 *)this)->FUN_0044d400(59, false);
    Serialize(file);
    FUN_004838f0(false);
    FUN_0047c4c0(this);
    FUN_0047b760(this, (int *)element);
    FUN_0047c420(element);
    ((RHUnk0047ca50 *)this)->Unk();
    FUN_0047e7d0((RHUnk005864a0 *)element);
    FUN_0047d920(this);
    FUN_00484a70(element);
    FUN_00484bb0(this, *(SBGeoPoint2D *)element, element);
    ((RHSound *)this)->FUN_005a8220(0, 0, 0, *(SBGeoPoint2D *)element);
    ((RHSound *)this)->FUN_005a8330(0, 0, 0, *(SBGeoPoint2D *)element);
    FUN_0047e9d0((RHUnk005864a0 *)element);
    ((RHUnk0046bd20 *)this)->FUN_0046bd20();
    ((RHUnk005864a0 *)element)->FUN_005864a0();
    ((RHUnk005864a0 *)element)->FUN_005864b0();
    ((RHUnk005864a0 *)element)->FUN_005864c0();
    ((RHUnk005864a0 *)element)->FUN_005864d0();
    ((RHUnk005c1d50 *)this)->FUN_005c1d50(0);
    ((RHUnk005c1d50 *)this)->FUN_005c1dd0(0, this);
    ((RHUnk00586f70 *)element)->FUN_00586f70(0, 0);
    ((RHUnk00586f70 *)element)->FUN_005870c0(0);
    ((RHUnk00586f70 *)element)->FUN_00587340(0);
    ((RHManagerListCalls *)this)->FUN_0058bed0();
}
