#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"
#include "RHMalignityPosition.h"
#include "RHArtificialMalignity.h"
#include "RHElementActorHumanCore.h"
#include "RHActorGridCalls.h"
#include "RHElementActorCivilianCore.h"
#include "RHElementActorNPC.h"
#include "RHUnk00571160Position.h"
#include "RHUnk005fc3b0.h"
#include <stdlib.h>
#include <list>

class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;

inline RHPath *RHBonhomieActorPath(void *actor)
{
    return (RHPath *)((char *)actor + (*(int **)((char *)actor + 0x49c))[1] + 0x4cc);
}

// FUNCTION: GAME 0x0040de30
void RHArtificialBonhomie::V14()
{
    void *actor = m_npcActor;
    RHMalignityField<unsigned short>(actor, 0x4d0) = RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xd8);
    reinterpret_cast<RHMalignityActorCalls *>(m_npcActor)->FUN_0048ebe0();
    reinterpret_cast<RHMalignityActorCalls *>(m_npcActor)->Vd4(100, false, false);
    RHMalignityArray &actors = RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8);
    unsigned short count = actors.m_first == 0 ? 0 : actors.m_last - actors.m_first;
    for (unsigned index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *other = (RHMalignityActorCalls *)RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8).m_first[index];
        unsigned flags = RHMalignityField<unsigned>(other, 4);
        if ((flags & 7) == 4 && ((flags & 0xf) == 0xc ||
            (flags & 0x1f) == 0x14 && other->V130() == 0 &&
            reinterpret_cast<RHMalignityActorCalls *>(m_npcActor)->V130() == 1))
            reinterpret_cast<RHMalignityActorCalls *>(m_npcActor)->FUN_0048c700(other, 0);
    }
    bool activate = InitState() && !m_1c4 && !(m_174 > 0);
    actor = m_npcActor;
    RHBonhomieActorPath(actor)->Unk00550f60(m_08);
    m_active = false;
    m_npcActor->FUN_0048d050();
    if (static_cast<RHElementActorCivilian *>(m_npcActor)->FUN_00470ca0())
        V3c(1);
    if (!(m_174 > 0) && RHBonhomieActorPath(m_npcActor)->GetWaypointCount() > 0)
    {
        RHBonhomieActorPath(m_npcActor)->TestIfPathIsFine(m_npcActor);
        m_hasWaypoints = true;
        m_1c = m_14;
        if (activate)
            V00(0);
    }
    else
    {
        m_hasWaypoints = false;
        if (activate)
        {
            int delay = rand() % 40 + 20;
            Unk00416710(delay);
            V10(1, 0xb);
            m_1c = m_14;
        }
    }
    m_1c8 = *g_unk0x006c08a4;
}

struct RHBonhomieSectorList : public std::list<void *>
{
    RHBonhomieSectorList() : m_dirty(true) {}
    void *m_current;
    bool m_dirty;
    int m_index;
};

DECOMP_SIZE_ASSERT(RHBonhomieSectorList, 0x18)

inline void RHBonhomieClearMessages(void *actor)
{
    RHMalignityList &list = RHMalignityField<RHMalignityList>(actor, 0x5a0);
    RHMalignityNode *head = list.m_head;
    RHMalignityNode *current = head->next;
    while (current != head)
    {
        RHMalignityNode *node = current;
        current = current->next;
        FUN_0048f170(node);
        node->previous->next = node->next;
        node->next->previous = node->previous;
        ((RHMalignityNodeValue *)&node->value)->FUN_0040eab0(0);
        delete node;
        --list.m_count;
    }
    list.m_dirty = true;
}

static RHUnk00571160Position PathPosition(const RHMalignityPosition &position)
{
    RHUnk00571160Position result = {position.x, position.y, position.area, (short)position.layer};
    return result;
}

static bool SendReaction(RHElementActorNPC &target, RHElementActorNPC *source, unsigned event)
{
    RHMalignityStimulus reaction;
    reaction.m_actor = source;
    reaction.m_type = 3;
    reaction.m_20 = event;
    return target.Intelligence().V24(&reaction);
}

static void FaceReactionTarget(RHArtificialIntelligence &ai)
{
    RHElementActorNPC *target = ai.m_reactionTarget;
    short height = (short)RHMalignityField<float>(target->m_50, 0x18);
    RHMalignityPosition position = ai.FUN_004165e0(target, true);
    ai.FUN_00412d60(position, height, 0);
}

// STUB: GAME 0x0040cc60
bool RHArtificialBonhomie::HandleReactionStimulus(RHMalignityStimulus &stimulus)
{
    switch (stimulus.m_20)
    {
    case 4:
        if (m_14 == 0xe0)
        {
            if (!m_fc)
                m_16w = 0;
            HandleWaypointStimulus(stimulus);
        }
        else
            V00(0);
        break;
    case 0xb:
        if (m_14 == 0x8e)
        {
            m_reactionTarget = static_cast<RHElementActorNPC *>(stimulus.m_actor);
            RHMalignityList &messages = RHMalignityField<RHMalignityList>(m_npcActor, 0x5a0);
            RHMalignityNode *head = messages.m_head;
            while (head->next != head)
            {
                RHMalignityNode *node = head->next;
                head->next = node->next;
                node->next->previous = head;
                operator delete(node);
                --messages.m_count;
            }
            messages.m_dirty = true;
            if (!SendReaction(*m_reactionTarget, m_npcActor, 0x22))
                FUN_004132d0(8, 0, 2);
            else
            {
                V10(3, 0x8f);
                Unk00418c40(0x50, 0);
                RHMalignityPosition destination;
                unsigned short heading;
                m_reactionTarget->FUN_00485a40(&destination, heading);
                FUN_00412cf0(destination, 0x46, 1);
                Unk00416710(0x14);
            }
        }
        break;
    case 0xd:
        m_npcActor->ClearCompletedSequence();
        m_npcActor->FUN_00486f30(1);
        V00(0);
        break;
    case 0x14:
        while (!m_178.empty())
        {
            if (m_174 || m_1c4)
                return false;
            memcpy(&stimulus, &m_178.front(), sizeof(stimulus));
            m_178.pop_front();
            m_178.dirty = true;
            if (stimulus.m_20 != 0x14)
                V24(&stimulus);
        }
        if (m_0c == 1)
        {
            RHPath &path = m_npcActor->ActorPath();
            if (path.m_4)
            {
                path.Unk005505c0();
                V10(1, 0xd);
                Unk00412c80((*path.m_4)[(unsigned char)path.m_0], m_22c);
            }
            else
                V00(0);
        }
        break;
    case 0x1e:
        FUN_00413240(FUN_0040cbf0(m_reactionPosition), 8, 2);
        break;
    case 0x2d:
        FUN_0041be60(stimulus.m_position);
        break;
    case 0x31:
    case 0x32:
    {
        m_reactionTarget = static_cast<RHElementActorNPC *>(stimulus.m_actor);
        RHMalignityPosition destination;
        if (ProposeGoodAppleChaseFleeDestination(destination))
        {
            Unk00412240(PathPosition(destination), 1, 1.0f);
            V10(6, stimulus.m_20 == 0x31 ? 0xe1 : 0xe4);
        }
        else
            FUN_00413240(FUN_0040cc20(m_reactionTarget), 8, 2);
        break;
    }
    }
    return false;
}

// STUB: GAME 0x0040c140
bool RHArtificialBonhomie::HandleStateStimulus(const RHMalignityStimulus &stimulus)
{
    unsigned event = stimulus.m_20;
    switch (m_14)
    {
    case 0xe0:
        if (!m_fc)
            m_16w = 0;
    case 7: case 8: case 9: case 10: case 0xb: case 0xd: case 0xf: case 0x10:
    case 0xdc: case 0xdd: case 0xde:
        HandleWaypointStimulus(stimulus);
        break;
    case 0x17:
    case 0xee:
        if (event == 3)
        {
            if (m_346 != RHMalignityField<short>(m_npcActor->m_50, 0xd8))
                Unk00412f70(m_346, 0);
            V10(1, 0x18);
        }
        break;
    case 0x18:
        if (event == 7)
        {
            int state = static_cast<RHElementActorNPC *>(m_2b0)->Intelligence().m_0c;
            if (state > 0 && state < 3)
                Unk00416710(200);
            else
                V00(0);
        }
        break;
    case 0x1a: case 0x3b: case 0xe3: case 0xfc:
        if (event == 7)
            V00(0);
        break;
    case 0x3c:
    case 0x3d:
        if (event == 7 && !FUN_0040e290(m_reactionPosition, 0))
        {
            Unk00418c40(0x53, 0);
            FUN_00413240(FUN_0040cbf0(m_reactionPosition), 8, 2);
        }
        break;
    case 0x43:
        if (event == 7)
        {
            Unk00418c40(0x5e, 0);
            V10(2, 0x44);
            FUN_00412cf0(m_reactionPosition, 0x32, 1);
        }
        break;
    case 0x44:
        if (event == 3)
        {
            V10(1, 0x1a);
            Unk00416710(100);
        }
        break;
    case 0x8e:
        if (event == 3)
        {
            if (m_reactionTarget->Intelligence().m_0c == 1)
            {
                RHMalignityPosition own = FUN_004165e0(m_npcActor, true);
                RHMalignityPosition target = FUN_004165e0(m_reactionTarget, true);
                if (FUN_0040ec20(target, own).Unk005fc6d0(1.0f) <= 4900.0f)
                {
                    if (!SendReaction(*m_reactionTarget, m_npcActor, 0x22))
                        FUN_004132d0(8, 0, 2);
                    else
                    {
                        RHBonhomieClearMessages(m_npcActor);
                        V10(3, 0x8f);
                        DispatchWorldEvent(3);
                    }
                }
                else
                {
                    RHMalignityPosition destination;
                    unsigned short heading;
                    m_reactionTarget->FUN_00485a40(&destination, heading);
                    FUN_00412cf0(destination, 0x46, 1);
                }
            }
            else if (!FUN_0040e290(m_reactionPosition, 0))
                V00(0);
        }
        break;
    case 0x8f:
        if (event == 3 || event == 7)
        {
            if (m_reactionTarget->Intelligence().m_14 != 0x93)
                V00(0);
            else if (event == 7)
                Unk00416710(20);
            else
            {
                V10(3, 0x90);
                Unk00416710(10);
            }
        }
        break;
    case 0x90:
        if (event == 7)
        {
            V10(3, 0x91);
            SendReaction(*m_reactionTarget, m_npcActor, 0x29);
            Unk00418c40(0x51, 0);
            FUN_004130b0(m_reactionPosition);
        }
        break;
    case 0x91:
        if (event == 5)
        {
            V10(3, 0x92);
            FaceReactionTarget(*this);
            Unk00416710(30);
        }
        break;
    case 0x92:
        if (event == 7)
            FUN_00413240(FUN_0040cbf0(m_reactionPosition), 8, 2);
        break;
    case 0xe1:
        if (event == 3)
        {
            RHMalignityPosition destination;
            if (!ProposeGoodAppleChaseFleeDestination(destination))
                FUN_00413240(FUN_0040cc20(m_reactionTarget), 8, 2);
            else
            {
                Unk00412240(PathPosition(destination), 0x401, FUN_0041a0b0(m_reactionTarget) < 150.0f ? 1.2f : 1.0f);
                int state = m_reactionTarget->Intelligence().m_14;
                if (state < 0x26 || state > 0x28)
                {
                    m_fc = 1;
                    V10(6, 0xe2);
                }
            }
        }
        else if (event == 0x3e)
            Unk00418c40(0x69, 0);
        break;
    case 0xe2:
        if (event == 3)
        {
            RHMalignityPosition destination;
            if (m_fc && (--m_fc, ProposeGoodAppleChaseFleeDestination(destination)))
            {
                Unk00412240(PathPosition(destination), m_fc ? 0x401 : 1, 1.0f);
                break;
            }
            V10(6, 0xe3);
            FaceReactionTarget(*this);
            Unk00416710(20);
        }
        break;
    case 0xe4:
        if (event == 3)
        {
            FUN_00412d60(FUN_004165e0(m_reactionTarget, true), -1, 0);
            V10(6, 0xe3);
            Unk00416710(50);
        }
        break;
    }
    return false;
}

// Parked: complete alert selection/retry procedure; list temporaries and register allocation differ.
// STUB: GAME 0x0040e290
bool RHArtificialBonhomie::FUN_0040e290(RHMalignityPosition position, int mode)
{
    int team = ((RHMalignityActorCalls *)RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4))->V130();
    void *best = 0;
    unsigned nearest = (unsigned)-1;
    unsigned short count = RHMalignityField<RHMalignityArray>(g_pEngine, 0x4d08 + team * 0x20).size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = RHMalignityField<RHMalignityArray>(g_pEngine, 0x4d08 + team * 0x20).m_first[index];
        if (!((RHMalignityActorCalls *)actor)->V11c() ||
            RHMalignityField<unsigned char>(actor, (*(int **)((char *)actor + 0x49c))[1] + 0x660))
            continue;
        if (!(mode & 1))
            ((RHMalignityActorCalls *)RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4))->FUN_0048c700(actor, 3);
        int state = RHMalignityField<int>(actor, (*(int **)((char *)actor + 0x49c))[1] + 0x4a8);
        if (state == 1)
        {
            unsigned distance = (unsigned)(int)((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0041a0b0(actor);
            if (RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xde) !=
                RHMalignityField<unsigned short>(RHMalignityField<void *>(RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4), 0x50), 0xde))
                distance += 1000;
            if (distance < nearest)
            {
                if (mode & 1)
                {
                    RHBonhomieSectorList sectors;
                    void *ownSprite = RHMalignityField<void *>(RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4), 0x50);
                    void *sprite = RHMalignityField<void *>(actor, 0x50);
                    void *area = RHMalignityField<void *>(sprite, 0xe0);
                    if (RHMalignityField<void *>(ownSprite, 0xe0) != area)
                    {
                        unsigned short layer = RHMalignityField<unsigned short>(sprite, 0xde);
                        SBGeoPoint2D targetPoint = ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0040cc20(actor);
                        void *ownActor = RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4);
                        ownSprite = RHMalignityField<void *>(ownActor, 0x50);
                        unsigned short ownLayer = RHMalignityField<unsigned short>(ownSprite, 0xde);
                        void *ownArea = RHMalignityField<void *>(ownSprite, 0xe0);
                        SBGeoPoint2D ownPoint = ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0040cc20(ownActor);
                        if (!((RHActorGridCalls *)g_unk0x6c0a9c)->FUN_004f9a80(&sectors,
                            (RHElementActor *)RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4),
                            ownPoint, ownArea, ownLayer, targetPoint, area, layer, 0))
                            distance = (unsigned)-1;
                    }
                    sectors.clear();
                }
                if (distance < nearest)
                {
                    nearest = distance;
                    best = actor;
                }
            }
        }
        else if (state > 3 && state <= 6 &&
            ((RHMalignityActorCalls *)RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4))->FUN_0048a130(actor))
        {
            RHBonhomieClearMessages(RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4));
            return false;
        }
    }
    if (!best)
    {
        RHBonhomieClearMessages(RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4));
        return false;
    }
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->V10(3, 0x8e);
    RHMalignityField<void *>((char *)this + (*(int **)this)[1], 0x90) = best;
    RHMalignityPosition destination;
    unsigned short heading;
    ((RHElementActorHuman *)RHMalignityField<void *>((char *)this + (*(int **)this)[1], 0x90))->FUN_00485a40(&destination, heading);
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_00412cf0(destination, 0x46, 1);
    if (RHMalignityField<unsigned char>((char *)this + (*(int **)this)[1], 0x16c))
    {
        RHMalignityField<unsigned char>((char *)this + (*(int **)this)[1], 0x16c) = 0;
        if (!(mode & 1))
            return FUN_0040e290(position, 1);
        RHBonhomieClearMessages(RHMalignityField<void *>((char *)this + (*(int **)this)[1], 4));
        return false;
    }
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(0x53, 0);
    return true;
}

// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?erase@?$list@PAXV?$allocator@PAX@std@@@std@@QAE?AViterator@12@V312@0@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAXV?$allocator@PAX@std@@@std@@QAE?AViterator@12@V312@@Z
