#include "RHElementActorHuman.h"

#define RH_HUMAN_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, sourceFile, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

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

// Sequence-list cursor allocation and named-call operands remain unmatched.
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

void RHElementActorHuman::Emit(SBFile &file, RHSequenceElement *element, RHcommand command)
{
    Translate(element, command);
    Serialize(file);
}
