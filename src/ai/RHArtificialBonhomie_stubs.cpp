#include "SBNullstr.h"
#include "RHArtificialBonhomie.h"
#include "RHMalignityPosition.h"
#include "RHArtificialMalignity.h"
#include "RHElementActorHumanCore.h"
#include "RHActorGridCalls.h"
#include "RHElementActorCivilianCore.h"
#include <stdlib.h>
#include <list>

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

inline RHPath *RHBonhomieActorPath(void *actor)
{
    return (RHPath *)((char *)actor + (*(int **)((char *)actor + 0x49c))[1] + 0x4cc);
}

inline bool RHBonhomieHasWaypoints(RHPath *path)
{
    RHMalignityArray *waypoints = RHMalignityField<RHMalignityArray *>(path, 4);
    return waypoints && waypoints->m_first && (unsigned short)(waypoints->m_last - waypoints->m_first) > 0;
}

// Parked: original materializes the actor path pointer before its waypoint load; base register order differs.
// STUB: GAME 0x0040de30
void RHArtificialBonhomie::FUN_0040de30()
{
    void *actor = RHMalignityField<void *>(RHBonhomieBase(this), 4);
    RHMalignityField<unsigned short>(actor, 0x4d0) = RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xd8);
    RHMalignityField<RHMalignityActorCalls *>(RHBonhomieBase(this), 4)->FUN_0048ebe0();
    RHMalignityField<RHMalignityActorCalls *>(RHBonhomieBase(this), 4)->Vd4(100, false, false);
    RHMalignityArray &actors = RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8);
    unsigned short count = actors.m_first == 0 ? 0 : actors.m_last - actors.m_first;
    for (unsigned index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *other = (RHMalignityActorCalls *)RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8).m_first[index];
        unsigned flags = RHMalignityField<unsigned>(other, 4);
        if ((flags & 7) == 4 && ((flags & 0xf) == 0xc ||
            (flags & 0x1f) == 0x14 && other->V130() == 0 &&
            RHMalignityField<RHMalignityActorCalls *>(RHBonhomieBase(this), 4)->V130() == 1))
            RHMalignityField<RHMalignityActorCalls *>(RHBonhomieBase(this), 4)->FUN_0048c700(other, 0);
    }
    bool activate = ((RHArtificialIntelligence *)RHBonhomieBase(this))->InitState() &&
        !RHMalignityField<unsigned char>(RHBonhomieBase(this), 0x1c4) &&
        !(RHMalignityField<unsigned char>(RHBonhomieBase(this), 0x174) > 0);
    actor = RHMalignityField<void *>(RHBonhomieBase(this), 4);
    ((RHArtificialIntelligencePathCursor *)RHBonhomieActorPath(actor))->Unk00550f60(RHMalignityField<unsigned short>(RHBonhomieBase(this), 8));
    *((unsigned char *)this - 0x18) = 0;
    RHMalignityField<RHMalignityActorCalls *>(RHBonhomieBase(this), 4)->FUN_0048d050();
    if (RHMalignityField<RHElementActorCivilian *>(RHBonhomieBase(this), 4)->FUN_00470ca0())
        ((RHArtificialIntelligence *)RHBonhomieBase(this))->V3c(1);
    char *base = RHBonhomieBase(this);
    if (!(RHMalignityField<unsigned char>(base, 0x174) > 0) &&
        RHBonhomieHasWaypoints(RHBonhomieActorPath(RHMalignityField<void *>(base, 4))))
    {
        RHBonhomieActorPath(RHMalignityField<void *>(base, 4))->TestIfPathIsFine(RHMalignityField<RHElementActor *>(base, 4));
        RHMalignityField<unsigned char>(RHBonhomieBase(this), 0x70) = 1;
        RHMalignityField<int>(RHBonhomieBase(this), 0x1c) = RHMalignityField<int>(RHBonhomieBase(this), 0x14);
        if (activate)
            ((RHArtificialIntelligence *)RHBonhomieBase(this))->V00(0);
    }
    else
    {
        RHMalignityField<unsigned char>(base, 0x70) = 0;
        if (activate)
        {
            ((RHArtificialIntelligence *)RHBonhomieBase(this))->Unk00416710(rand() % 40 + 20);
            ((RHArtificialIntelligence *)RHBonhomieBase(this))->V10(1, 0xb);
            RHMalignityField<int>(RHBonhomieBase(this), 0x1c) = RHMalignityField<int>(RHBonhomieBase(this), 0x14);
        }
    }
    RHMalignityField<unsigned>(RHBonhomieBase(this), 0x1c8) = *g_unk0x006c08a4;
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

// Parked: complete alert selection/retry procedure; list temporaries and register allocation differ.
// STUB: GAME 0x0040e290
bool RHBonhomieSpeechReceiver::FUN_0040e290(RHMalignityPosition position, int mode)
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
