#include "SBNullstr.h"
#include "SBGeoBoundingBox2DCore.h"
extern float g_unk0x006774e4;
extern float g_unk0x00677564;
#include "RHArtificialMalignity.h"
#include "RHArtificialIntelligenceActor.h"
#include "RHElementActorNPC.h"
#include "RHElementActorHumanCore.h"
#include "RHArtificialIntelligenceActorCalls.h"
#include "RHHumanWeaponCalls.h"
#include "RHUnk0060bd40.h"
#include <stddef.h>
#include <stdlib.h>
#include <new>
#include "RHSectorBuilding.h"
#include "RHPositionInterfaceCore.h"
#include "RHSword.h"
#include "RHSequenceManager.h"


class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityPosition, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityArray, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityNode, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityList, 0x18)
DECOMP_SIZE_ASSERT(RHSectorActorList, 0x24)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHSeekPoint, 0x40)
DECOMP_SIZE_ASSERT(RHMalignityMessage, 0x14)
DECOMP_SIZE_ASSERT(RHMalignityMessageNode, 0x1c)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHMalignitySegment, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityRectangle, 0x50)
DECOMP_SIZE_ASSERT(RHMalignityQueryList, 0x24)
DECOMP_SIZE_ASSERT(RHArtificialIntelligence, 0x38c)
DECOMP_SIZE_ASSERT(RHMalignityTargetList, 0x24)
DECOMP_SIZE_ASSERT(RHArtificialMalignity, 0x6e4)
DECOMP_STATIC_ASSERT(offsetof(RHElementActorHuman, m_260) == 0x260)
DECOMP_STATIC_ASSERT(offsetof(RHHumanList, count) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityList, m_head) == 0x04)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityList, m_count) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityList, m_dirty) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_50) == 0x50)

// GLOBAL: GAME 0x006c0754
bool g_unk0x006c0754 = false;

// GLOBAL: GAME 0x006c0788
bool g_unk0x006c0788 = false;

// GLOBAL: GAME 0x006c08a4
unsigned *g_unk0x006c08a4 = 0;




#define M(type, offset) RHMalignityField<type>(this, offset)
#define B(type, offset) RHMalignityField<type>(&Base(), offset)
#define A(type, offset) RHMalignityField<type>(Base().m_actor, offset)
#define F(type, offset) RHMalignityField<type>(B(void *, 0x1fc), offset)
#define S(type, offset) RHMalignityField<type>(B(void *, 0x200), offset)
#define FA(type, offset) RHMalignityField<type>((char *)B(void *, 0x1fc) + ((int *)F(void *, 0x49c))[1], offset)
#define SA(type, offset) RHMalignityField<type>((char *)B(void *, 0x200) + ((int *)S(void *, 0x49c))[1], offset)
#define AA(type, offset) RHMalignityField<type>((char *)Base().m_actor + ((int *)A(void *, 0x49c))[1], offset)
#define RESET() ((RHArtificialIntelligence *)&Base())->Unk00410010(false)

struct RHMalignityCachedList : public RHMalignityList
{
    void Seek(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_current = ((RHMalignityNode *volatile &)m_head)->next), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_current = (RHMalignityNode *volatile &)m_head), wanted - count, category);
            }
            m_dirty = false;
        }
        else if (wanted != m_index)
        {
            int previous = m_index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)(m_current = (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node), wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
            }
            else if (wanted < (previous + count) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_current = (RHMalignityNode *volatile &)m_head), wanted - count, category);
            }
        }
        m_index = wanted;
    }
};

// Parked: cached-cursor branch layout and iterator-call scheduling remain unmatched.
// STUB: GAME 0x0048c8e0
unsigned char RHMalignityActorCalls::FUN_0048c8e0(void *actor, unsigned mode)
{
    RHMalignityCachedList &list = RHMalignityField<RHMalignityCachedList>(this, 0x504 + mode * 0x34);
    unsigned count = list.m_count;
    for (unsigned index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        list.Seek((unsigned short)index);
        if (((RHMalignityMessageNode *)list.m_current)->value.actor == actor)
            return 1;
    }
    return 0;
}

inline void RHMalignityList::Clear()
{
    RHMalignityNode *head = m_head;
    RHMalignityNode *it = head->next;
    while (it != head)
    {
        RHMalignityNode *node = it;
        it = it->next;
        FUN_0048f170(node);
        node->previous->next = node->next;
        node->next->previous = node->previous;
        ((RHMalignityNodeValue *)&node->value)->FUN_0040eab0(0);
        delete node;
        --m_count;
    }
    m_dirty = true;
}

// FUNCTION: GAME 0x0040cc20
SBGeoPoint2D RHArtificialIntelligence::FUN_0040cc20(void *actor)
{
    return FUN_0040cbf0(FUN_004165e0(actor, true));
}

inline bool RHMalignityBit(unsigned value, int bit)
{
    return (value >> bit) & 1;
}

inline RHMalignityPosition RHMalignityPositionOf(void *object)
{
    RHMalignityPosition position;
    position.x = RHMalignityField<float>(object, 0x20);
    position.y = RHMalignityField<float>(object, 0x24);
    position.area = RHMalignityField<void *>(object, 0x10);
    position.layer = RHMalignityField<unsigned short>(object, 0x16);
    return position;
}

#include "RHGate.h"

// FUNCTION: GAME 0x00414320
const SBGeoPoint2D &RHUnk0051a5e0::FUN_00414320() const
{
    return m_18;
}

class RHMalignityUnk00414330
{
public:
    void *FUN_00414330(void *destination);
};

// FUNCTION: GAME 0x00414330
void *RHMalignityUnk00414330::FUN_00414330(void *destination)
{
    *(RHMalignityPosition *)destination = *(RHMalignityPosition *)((char *)this + 4);
    return destination;
}

void EmitRHMalignityUnk00414330(RHMalignityUnk00414330 *a)
{
    a->FUN_00414330(0);
}

// FUNCTION: GAME 0x00414360
RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode)
{
    SBGeoPoint2D point;
    RHUnk00613e90 result;
    point.m_x = position.x;
    point.m_y = position.y;
    void *projection = 0;
    void *area = position.area;
    if (area && RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 1) &&
        (RHMalignityField<unsigned char>(area, 0x30) & 1))
    {
        if (!RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 13))
            projection = ((RHUnk0057d490 *)area)->FUN_0057d800(point);
        else
        {
            RHMalignityList &list = RHMalignityField<RHMalignityList>(area, 0x5c);
            int count = list.m_count;
            void *found = 0;
            for (unsigned short index = 0; index < (unsigned short)count; ++index)
            {
                ((RHSectorActorList *)&list)->Unk005c8e40(index);
                void *candidate = list.m_current->value;
                RHMalignityPosition location = RHMalignityPositionOf(candidate);
                bool close = FUN_0040ec20(location, position).FUN_005fc700(1.0f) < 20.0f;
                if (close)
                {
                    found = candidate;
                    break;
                }
            }
            if (found)
            {
                RHUnk0057d490 *owner = RHMalignityField<RHUnk0057d490 *>(found, 0x0c);
                projection = owner->FUN_0057d800(RHMalignityField<SBGeoPoint2D>(found, 0x18));
            }
        }
    }
    float height;
    if (!projection)
        height = 0.0f;
    else
        height = (RHMalignityField<float>(projection, 0xf4) * position.x +
                  RHMalignityField<float>(projection, 0xf8) * position.y +
                  RHMalignityField<float>(projection, 0xfc)) /
                 (1.0f - RHMalignityField<float>(projection, 0xf8));
    result.x = position.x;
    result.y = position.y + height;
    result.z = height;
    return result;
}

// FUNCTION: GAME 0x004165e0
RHMalignityPosition RHArtificialIntelligence::FUN_004165e0(void *actor, bool mounted)
{
    RHUnk00571160Position position;
    if (mounted && (RHMalignityField<unsigned char>(actor, 4) & 3) == 0 && (char)((RHElementActor *)actor)->FUN_0046e960())
    {
        void *mount = RHMalignityField<void *>(actor, 0x130);
        if (RHMalignityField<short>(mount, 0x90) != 0)
        {
            RHMalignityPosition seat;
            seat.x = RHMalignityField<float>(RHMalignityField<void *>(mount, 0x7c), 0x20);
            seat.y = RHMalignityField<float>(RHMalignityField<void *>(mount, 0x7c), 0x24);
            seat.layer = RHMalignityField<unsigned short>(RHMalignityField<void *>(mount, 0x7c), 0x16);
            seat.area = RHMalignityField<void *>(RHMalignityField<void *>(mount, 0x7c), 0x10);
            return seat;
        }
        RHMalignityPosition seat;
        seat.x = RHMalignityField<float>(RHMalignityField<void *>(mount, 0x7c), 0x18);
        seat.y = RHMalignityField<float>(RHMalignityField<void *>(mount, 0x7c), 0x1c);
        seat.layer = RHMalignityField<unsigned short>(RHMalignityField<void *>(mount, 0x7c), 0x14);
        seat.area = RHMalignityField<void *>(RHMalignityField<void *>(mount, 0x7c), 0xc);
        return seat;
    }
    if ((RHMalignityField<int>(actor, 4) & 0xf) == 0xc && RHMalignityField<int>(RHMalignityField<void *>(actor, 0x50), 0x8c) == 0x10)
        ((RHPositionInterface *)((char *)RHMalignityField<void *>(RHMalignityField<void *>(actor, 0x254), 0x50) + 4))->GetPosition(position);
    else
        ((RHPositionInterface *)((char *)RHMalignityField<void *>(actor, 0x50) + 4))->GetPosition(position);
    if (position.layer < 0)
        position.layer = 0;
    return *(RHMalignityPosition *)&position;
}

// FUNCTION: GAME 0x00419e10
bool RHArtificialIntelligence::FUN_00419e10(void *actor)
{
    int first = ((RHMalignityActorCalls *)m_actor)->V130();
    int second = ((RHMalignityActorCalls *)actor)->V130();
    return first == second;
}

class RHMalignityUnk0041a2e0
{
public:
    bool FUN_0041a2e0();
};

// FUNCTION: GAME 0x0041a2e0
bool RHMalignityUnk0041a2e0::FUN_0041a2e0()
{
    int value = *(int *)((char *)this + 0x14);
    if (value == 0x5a || value == 0x7b)
        return true;
    return false;
}

void EmitRHMalignityUnk0041a2e0(RHMalignityUnk0041a2e0 *a)
{
    a->FUN_0041a2e0();
}

// FUNCTION: GAME 0x0041a300
void RHArtificialIntelligence::FUN_0041a300(void *actor)
{
    RHMalignityList &list = RHMalignityField<RHMalignityList>(m_actor, 0x5d4);
    list.Clear();
    RHMalignityField<void *>(this, 0x1fc) = actor;
    if (actor)
        ((RHMalignityActorCalls *)m_actor)->FUN_0048c700(actor, 4);
    else
    {
        RHMalignityField<unsigned short>(this, 0xaa) = 0;
        RHMalignityField<RHMalignityList>(m_actor, 0x5d4).Clear();
    }
}

// FUNCTION: GAME 0x0041ab30
void RHArtificialIntelligence::FUN_0041ab30()
{
    RHMalignityList &first = RHMalignityField<RHMalignityList>(this, 0x2b4);
    ((RHAIUnk0044e8b0 *)&first)->FUN_0044e8b0(RHMalignityIterator(first.m_head->next), RHMalignityIterator(first.m_head));
    first.m_dirty = true;
    RHMalignityList &second = RHMalignityField<RHMalignityList>(this, 0x2d8);
    ((RHAIUnk0044e8b0 *)&second)->FUN_0044e8b0(RHMalignityIterator(second.m_head->next), RHMalignityIterator(second.m_head));
    second.m_dirty = true;
    RHMalignityList &third = RHMalignityField<RHMalignityList>(this, 0x2fc);
    int count = RHMalignityField<RHMalignityList>(this, 0x320).m_count;
    ((RHAIUnk0044e8b0 *)&third)->FUN_0044e8b0(RHMalignityIterator(third.m_head->next), RHMalignityIterator(third.m_head));
    third.m_dirty = true;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHMalignityList &indices = RHMalignityField<RHMalignityList>(this, 0x320);
        ((RHSectorActorList *)&indices)->Unk005c8e40(index);
        unsigned short actorIndex = *(unsigned short *)&indices.m_current->value;
        void *value = RHMalignityField<void **>(g_pEngine, 0x4d4c)[actorIndex];
        RHMalignityNode *head = third.m_head;
        RHMalignityNode *previous = head->previous;
        RHMalignityNode *node = (RHMalignityNode *)operator new(12);
        node->next = head ? head : node;
        node->previous = previous ? previous : node;
        head->previous = node;
        node->previous->next = node;
        new (&node->value) void *(value);
        ++third.m_count;
        third.m_dirty = true;
    }
}

// Parked: frame is eight bytes too large; push_back still names a placeholder entity.
// STUB: GAME 0x0041ac50
void RHArtificialIntelligence::Unk0041ac50()
{
    RHArtificialIntelligence &base = *(RHArtificialIntelligence *)this;
    SBGeoPoint2D origin;
    SBGeoPoint2D firstPoint;
    SBGeoPoint2D secondPoint;
    unsigned short accepted = 0;
    RHMalignityList &first = RHMalignityField<RHMalignityList>(this, 0x2b4);
    RHAIUnk0044e8b0 &firstCalls = *(RHAIUnk0044e8b0 *)&first;
    firstCalls.FUN_0044e8b0(((RHUnk0046eb30 *)&first)->FUN_0046eb80(), RHScriptIter((RHScriptNode *)first.m_head));
    first.m_dirty = true;
    RHMalignityList &second = RHMalignityField<RHMalignityList>(this, 0x2d8);
    RHAIUnk0044e8b0 &secondCalls = *(RHAIUnk0044e8b0 *)&second;
    secondCalls.FUN_0044e8b0(((RHUnk0046eb30 *)&second)->FUN_0046eb80(), RHScriptIter((RHScriptNode *)second.m_head));
    second.m_dirty = true;
    RHMalignityList &third = RHMalignityField<RHMalignityList>(this, 0x2fc);
    unsigned short count = third.m_count;
    if (count == 0)
        return;
    for (unsigned short index = 0; index < count; ++index)
    {
        ((RHSectorActorList *)&third)->Unk005c8e40(index);
        void *actor = third.m_current->value;
        float score = base.FUN_0041a010(actor);
        RHMalignityField<float>(actor, 0x204) = score;
        void *actorAI = (char *)actor + (*(int **)RHMalignityField<void *>(actor, 0x49c))[1];
        if (((RHMalignityActorCalls *)base.m_actor)->FUN_0048a130(actor) &&
            RHMalignityField<int>(actorAI, 0x4a8) == 1 &&
            ((unsigned char)(RHMalignityField<unsigned>(actor, 4) & 31) == 4 ||
             ((RHMalignityActorCalls *)actor)->V11c()))
        {
            unsigned short insert;
            for (insert = 0; insert < accepted; ++insert)
            {
                ((RHSectorActorList *)&first)->Unk005c8e40(insert);
                if (!(score > RHMalignityField<float>(first.m_current->value, 0x204)))
                    break;
            }
            if (insert == first.m_count)
                firstCalls.FUN_0045a440(actor);
            else
            {
                ((RHSectorActorList *)&first)->Unk005c8e40(insert);
                firstCalls.FUN_00424410(RHMalignityIterator(first.m_current), actor);
            }
            first.m_dirty = true;
            ++accepted;
            RHMalignityField<void *>(actorAI, 0x74c) = base.m_actor;
        }
        else if (!((RHMalignityActorCalls *)actor)->V48())
        {
            secondCalls.FUN_00424410(RHMalignityIterator(second.m_head), actor);
            second.m_dirty = true;
        }
    }
    origin = base.FUN_0040cc20(base.m_actor);
    for (int pair = 0; pair < accepted - 1; pair += 2)
    {
        ((RHSectorActorList *)&first)->Unk005c8e40(pair);
        firstPoint = base.FUN_0040cc20(first.m_current->value);
        ((RHSectorActorList *)&first)->Unk005c8e40(pair + 1);
        secondPoint = base.FUN_0040cc20(first.m_current->value);
        bool swap = ((RHUnk005fc3b0 *)&secondPoint.Unk005fc110(origin))->FUN_005fc680(
            *(RHUnk005fc3b0 *)&firstPoint.Unk005fc110(origin), 1.0f) < 0.0f;
        if (swap)
        {
            ((RHSectorActorList *)&first)->Unk005c8e40(pair);
            void **value = &first.m_current->value;
            ((RHSectorActorList *)&first)->Unk005c8e40(pair + 1);
            void *saved = first.m_current->value;
            first.m_current->value = *value;
            int size = first.m_count;
            std::bidirectional_iterator_tag category;
            if (first.m_dirty)
            {
                if (pair <= (size + 1) / 2)
                {
                    first.m_current = first.m_head->next;
                    FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair, category);
                }
                else
                {
                    first.m_current = first.m_head;
                    FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair - size, category);
                }
                first.m_dirty = false;
            }
            else if (pair != first.m_index)
            {
                int previous = first.m_index;
                if (pair < previous)
                {
                    if (pair < (previous + 1) / 2)
                    {
                        first.m_current = first.m_head->next;
                        FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair, category);
                    }
                    else
                        FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair - previous, category);
                }
                else if (pair < (previous + size) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair - previous, category);
                else
                {
                    first.m_current = first.m_head;
                    FUN_005c9010((RHUnk005c9010Iterator &)first.m_current, pair - size, category);
                }
            }
            first.m_index = pair;
            first.m_current->value = saved;
        }
    }
}

// Parked: obstacle repair and original geometry/EH frame remain incomplete.
// STUB: GAME 0x00435c80
void RHArtificialMalignity::InitOneAI()
{
    RHMalignityActorCalls *actor = (RHMalignityActorCalls *)Base().m_actor;
    unsigned posture = actor->Vcc();
    M(unsigned char, -0x77) = (unsigned char)posture;
    M(unsigned char, -0x78) = (unsigned char)posture;
    if (A(void *, 0x258) && actor->V130() == 0 &&
        RHMalignityField<unsigned char>(g_pEngine, 0x4aa8) && !actor->Vf4())
        actor->Vec(1, 3);

    M(unsigned short, -0x222) = 50;
    A(unsigned short, 0x4d0) = RHMalignityField<unsigned short>(A(void *, 0x50), 0xd8);
    ((RHMalignityActorCalls *)Base().m_actor)->FUN_0048ebe0();
    Base().FUN_0041ab30();
    Base().Unk0041ac50();

    unsigned count = RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8).size();
    for (unsigned i = 0; i < count; ++i)
    {
        void *other = RHMalignityField<RHMalignityArray>(g_pEngine, 0x48d8).m_first[i];
        unsigned flags = RHMalignityField<unsigned>(other, 4);
        if ((flags & 7) == 4 && !Base().FUN_00419e10(other) &&
            (RHMalignityField<unsigned>(other, 4) & 31) != 4)
            ((RHMalignityActorCalls *)Base().m_actor)->FUN_0048c700(other, false);
    }

    actor = (RHMalignityActorCalls *)Base().m_actor;
    switch (actor->V130())
    {
    case 0:
        g_unk0x006c0754 = true;
        break;
    case 1:
        g_unk0x006c0788 = true;
        if (!actor->Vf8())
        {
            unsigned short value = ((RHMalignityOwnerCalls *)((char *)this - 0x358))->FUN_00438710(actor->Vcc(), 0.5f, 1.5f, 10000);
            ((RHMalignityActorCalls *)Base().m_actor)->Vd4(value, false, false);
        }
        break;
    }

    bool activatePath = ((RHArtificialIntelligence *)&Base())->InitState() &&
        !B(unsigned char, 0x1c4) && B(unsigned char, 0x174) == 0;
    Base().m_npcActor->FUN_0048d050();
    RHPath *path = (RHPath *)&AA(char, 0x4cc);
    path->Unk00550f60(B(unsigned short, 8));
    RHMalignityArray *waypoints = RHMalignityField<RHMalignityArray *>(path, 4);
    if (waypoints && waypoints->size() &&
        !((RHPath *)path)->TestIfPathIsFine((RHElementActor *)Base().m_actor))
        path->Unk00550f60(0xffff);
    waypoints = RHMalignityField<RHMalignityArray *>(path, 4);
    if (waypoints && waypoints->size())
    {
        B(unsigned char, 0x70) = 1;
        B(unsigned, 0x1c) = B(unsigned, 0x14);
        if (activatePath)
        {
            Base().V10(1, 13);
            Base().V00(0);
        }
    }
    else
        B(unsigned char, 0x70) = 0;

    M(unsigned char, -0x50) = 1;
    RHMalignityResetArray &array = M(RHMalignityResetArray, -0x4c);
    array.m_last = array.m_first;
    M(unsigned char, -0x38) = 1;
    unsigned tacticalCount = (unsigned short)g_unk0x006c0718.size();
    RHSaveGame *empty = 0;
    while (tacticalCount != 0)
    {
        array.Insert(array.m_last, 1, empty);
        M(unsigned char, -0x38) = 1;
        --tacticalCount;
    }
    B(unsigned, 0x1c8) = *g_unk0x006c08a4;
}

// Parked: large versioned serializer omitted from the source-file inventory.
// STUB: GAME 0x00436570
bool RHArtificialMalignity::SerializeExactlyThisAI(SBFile &file)
{
    return false;
}

// FUNCTION: GAME 0x00438600
unsigned short RHMalignityOwnerCalls::FUN_00438600()
{
    return FUN_00438710(*(unsigned short *)(*(char **)((char *)this + 0x334) + 0x32),
        0.5f, 2.0f, 100);
}

// FUNCTION: GAME 0x00438620
void RHArtificialMalignity::FUN_00438620(unsigned short value)
{
    float scale = 1.0f;
    if (((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() == 0 &&
        RHMalignityField<bool>(g_pEngine, 0x4aa8) && !((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf4())
    {
        ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(3);
        return;
    }
    if (((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() == 1)
    {
        switch (RHMalignityField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c))
        {
        case 0:
        case 2:
            scale = 2.0f;
            break;
        }
    }
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(
        (unsigned)(value * ((100 - RHMalignityField<unsigned short>(M(void *, 0x334), 0x32)) * 0.01f) * scale + 1.0f));
}

// FUNCTION: GAME 0x00438710
unsigned short RHMalignityOwnerCalls::FUN_00438710(unsigned short value, float low, float high, unsigned short maximum)
{
    void *actor = *(void **)((char *)this + (*(int **)this)[1] + 4);
    if (((RHMalignityActorCalls *)actor)->V130() == 1)
    {
        switch (RHMalignityField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c))
        {
        case 0:
            return (unsigned short)__min(maximum, value * low);
        case 2:
            return (unsigned short)__min(maximum, value * high);
        }
    }
    return value;
}

// FUNCTION: GAME 0x00438aa0
void RHArtificialMalignity::CheckAmbushPoint(RHAmbushPoint *point, bool mode)
{
    RHMalignityPosition position = RHMalignityField<RHMalignityPosition>(point, 4);
    bool side = ((RHUnk005fc3b0 &)((RHElementActor *)VirtualBase().m_actor)->FUN_004135b0()).FUN_005fc680(
        (RHUnk005fc3b0 &)FUN_0040ec20(position, VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)), 1.0f) > 0.0f;
    if (side)
    {
        if (RHMalignityField<int>(&VirtualBase(), 0x14) == 0x4c)
        {
            VirtualBase().V10(3, 0x4e);
            VirtualBase().V04(2);
            return;
        }
        if (!mode)
        {
            VirtualBase().V10(3, 0x4e);
            VirtualBase().V04(1);
            return;
        }
        VirtualBase().V10(3, 0x4d);
        VirtualBase().Unk00416710(3);
    }
    else
    {
        if (RHMalignityField<int>(&VirtualBase(), 0x14) == 0x4d)
        {
            VirtualBase().V10(3, 0x4e);
            VirtualBase().V04(2);
            return;
        }
        if (!mode)
        {
            VirtualBase().V10(3, 0x4e);
            VirtualBase().V04(0);
            return;
        }
        VirtualBase().V10(3, 0x4c);
        VirtualBase().Unk00416710(3);
    }
}

// Parked: register allocation and branch scheduling remain non-exact.
// STUB: GAME 0x00439080
void RHArtificialMalignity::InitializeFriendCheck(unsigned short actor, unsigned short delay, unsigned short waypoint)
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    RHUnk005fc3b0 vector;

    if (actor >= RHMalignityField<RHMalignityArray>(g_pEngine, 0x4d48).size())
    {
        SBAssert(1,
                 // STRING: GAME 0x006ab5e4
                 "P:\\Robin Hood\\RHartificialmalignity.cpp", 11220,
                 // STRING: GAME 0x006ab868
                 "Waypoint command 'CheckFor' at (%u, %u): Illegal ID for guy to check.",
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y);
    }

    void *other = RHMalignityField<RHMalignityArray>(g_pEngine, 0x4d48).m_first[actor];
    if (!other || (unsigned char)(RHMalignityField<unsigned>(other, 4) & 15) != 4)
    {
        SBAssert(1, "P:\\Robin Hood\\RHartificialmalignity.cpp", 11228,
                 // STRING: GAME 0x006ab828
                 "Waypoint command 'CheckFor' at (%u, %u): Can only check NPCs!",
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y);
    }
    Base().FUN_0041a300(other);
    if (B(void *, 0x1fc) == Base().m_actor)
    {
        SBAssert(1, "P:\\Robin Hood\\RHartificialmalignity.cpp", 11237,
                 // STRING: GAME 0x006ab7ec
                 "CheckFor at (%u, %u) applied on yourself? Funny idea... ",
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                 (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y);
    }

    unsigned short count = M(RHMalignityList, -0x32c).m_count;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMalignityList &list = M(RHMalignityList, -0x32c);
        ((RHSectorActorList *)&list)->Unk005c8e40(i);
        if (B(void *, 0x1fc) == list.m_current->value)
        {
            Base().FUN_0041a300(0);
            Base().V10(1, 15);
            RESET();
            return;
        }
    }
    if (M(unsigned, -0xb0) > 0 && *g_unk0x006c08a4 - M(unsigned, -0xb0) < 3000)
    {
        Base().FUN_0041a300(0);
        Base().V10(1, 15);
        RESET();
        return;
    }

    if (delay == 0 && waypoint != 0xffff)
    {
        if (waypoint > 500)
            M(unsigned short, -0x306) = AA(unsigned char, 0x4cc) + waypoint - 1000;
        else
            M(unsigned short, -0x306) = waypoint;
        B(void *, 0x200) = B(void *, 0x1fc);
        Base().FUN_0041a300(0);
        if (SA(int, 0x4a8) != 1 || ((RHMalignityActorCalls *)B(void *, 0x200))->V48())
        {
            Base().V10(1, 15);
            RESET();
            return;
        }

        bool reached = false;
        if (SA(unsigned char, 0x51a))
        {
            if (waypoint < 500)
                reached = SA(unsigned char, 0x4cc) == M(unsigned short, -0x306);
            else if (SA(bool, 0x4ce) != B(bool, 0x32))
                reached = B(bool, 0x32);
            else if (B(bool, 0x32))
                reached = SA(unsigned char, 0x4cc) >= M(unsigned short, -0x306);
            else
                reached = SA(unsigned char, 0x4cc) <= M(unsigned short, -0x306);
        }
        else if (SA(int, 0x4b0) == 13)
        {
            if (waypoint < 500)
                reached = SA(unsigned char, 0x4cd) == M(unsigned short, -0x306);
            else if (SA(bool, 0x4ce) != B(bool, 0x32))
                reached = B(bool, 0x32);
            else if (B(bool, 0x32))
                reached = SA(unsigned char, 0x4cd) >= M(unsigned short, -0x306);
            else
                reached = SA(unsigned char, 0x4cd) <= M(unsigned short, -0x306);
        }
        if (reached)
        {
            Base().V10(1, 15);
            RESET();
            return;
        }

        RHMalignityList &list = SA(RHMalignityList, 0x6a4);
        void *value = Base().m_actor;
        if (((RHSectorActorList *)&list)->Unk004b8f80((RHElementActor *const &)value, true) == -1)
            list.InsertLast(value);
        Base().V10(1, 22);
        return;
    }

    if (!FA(unsigned char, 0x50c))
    {
        RHUnk00613e90 point;
        point = FUN_00414360(F(RHMalignityPosition, 0x4dc), true);
        if (!((RHMalignityActorCalls *)Base().m_actor)->FUN_0048a260(point))
        {
            point.z += g_unk0x006774e4;
            if (!((RHMalignityActorCalls *)Base().m_actor)->FUN_0048a260(point))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialmalignity.cpp", 11387,
                         // STRING: GAME 0x006ab790
                         "Waypoint command 'CheckFor' at (%u, %u): The other guy's post at (%u, %u) is not visible.",
                         (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                         (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y,
                         (unsigned short)F(float, 0x4dc), (unsigned short)F(float, 0x4e0));
            }
        }
        if (waypoint != 0xffff)
        {
            SBAssert(1, "P:\\Robin Hood\\RHartificialmalignity.cpp", 11393,
                     // STRING: GAME 0x006ab714
                     "Waypoint command 'CheckForSynch' at (%u, %u): Hey, Roman, you cannot synchronize with the path pf someone who has no path!",
                     (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                     (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y);
        }
    }
    else
    {
        RHMalignityArray *path = FA(RHMalignityArray *, 0x4d0);
        count = path ? path->size() : 0;
        unsigned short i;
        for (i = 0; i < count; ++i)
        {
            RHMalignityWaypoint *entry = (RHMalignityWaypoint *)FA(RHMalignityArray *, 0x4d0)->m_first[i];
            RHUnk00613e90 point;
            point = FUN_00414360(entry->Position(), true);
            RHUnk00613e90 elevated = point;
            elevated.z = point.z + g_unk0x006774e4;
            if (((RHMalignityActorCalls *)Base().m_actor)->FUN_0048a260(elevated))
                break;
        }
        if (i == count)
        {
            RHMalignityWaypoint *entry = (RHMalignityWaypoint *)FA(RHMalignityArray *, 0x4d0)->m_first[0];
            SBAssert(0, "P:\\Robin Hood\\RHartificialmalignity.cpp", 11415,
                     // STRING: GAME 0x006ab6a0
                     "Waypoint command 'CheckFor' at (%u, %u): No waypoint of the other guy's path is visible. Path begins at (%d, %d).",
                     (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_x,
                     (unsigned short)Base().FUN_0040cc20(Base().m_actor).m_y,
                     (int)entry->x, (int)entry->y);
            Base().V10(1, 15);
            RESET();
            return;
        }
    }

    if (waypoint == 0xffff)
    {
        B(void *, 0x200) = 0;
        M(unsigned short, -0x306) = 0xffff;
    }
    else
    {
        B(void *, 0x200) = B(void *, 0x1fc);
        if (waypoint > 500)
            M(unsigned short, -0x306) = AA(unsigned char, 0x4cc) + waypoint - 1000;
        else
            M(unsigned short, -0x306) = waypoint;
    }
    B(unsigned char, 0x2c) = delay / 10 + 1;
    M(unsigned short, -0x32e) = 1000 / B(unsigned char, 0x2c);
    Base().V10(1, 20);
    Base().V04(2 | (~rand() & 1));
}

class RHMalignityReactionCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, int substate) = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24(RHMalignityStimulus *stimulus) = 0;
    void FUN_0041a3e0();
};

// FUNCTION: GAME 0x0041a3e0
void RHMalignityReactionCalls::FUN_0041a3e0()
{
    if (*(int *)((char *)this + 0x14) >= 0x13 && *(int *)((char *)this + 0x14) <= 0x14)
        ((RHArtificialIntelligence *)this)->FUN_0041a300(0);
    ((RHArtificialIntelligenceActorCalls *)*(void **)((char *)this + 4))->Unk0048d020();
    if (*(int *)((char *)this + 0x14) < 0x13 ||
        (*(int *)((char *)this + 0x14) > 0x14 && *(int *)((char *)this + 0x14) != 0x6c))
        ((RHArtificialIntelligence *)this)->Unk00410600();
}

// Parked: native keeps both 412240 tails and places the 412f40 block last.
// STUB: GAME 0x0041be60
void RHArtificialIntelligence::FUN_0041be60(const RHMalignityPosition &position)
{
    if (!RHMalignityField<void *>(this, 0x2b0))
        return;
    switch (RHMalignityField<int>(this, 0x14))
    {
    case 7: case 8: case 11: case 12: case 13: case 15: case 0xef:
        ((RHMalignityReactionCalls *)this)->FUN_0041a3e0();
    case 0x17: case 0x18: case 0xee:
        break;
    default:
        return;
    }
    SBGeoVector2D target = FUN_0040ec20(position, FUN_004165e0(m_actor, true));
    SBGeoVector2D leader = FUN_0040ec20(FUN_004165e0(RHMalignityField<void *>(this, 0x2b0), true), FUN_004165e0(m_actor, true));
    float length = ((RHUnk005fc3b0 &)target).Unk005fc6a0(1.0f);
    float speed = length * 0.033333335f + 0.3f;
    if (length <= 30.0f && leader.m_x * target.m_x + leader.m_y * target.m_y * 3.0396068f < 0.0f)
    {
        Unk00412f40((RHUnk005fc3b0 *)&leader, 0);
        return;
    }
    if (speed <= 2.0f)
    {
        V10(1, 0x17);
        Unk00412240((const RHUnk00571160Position &)position, RHMalignityField<unsigned short>(this, 0x22c) | 0x2400, speed);
    }
    else
    {
        V10(1, 0xee);
        Unk00412240((const RHUnk00571160Position &)position, 0x2401, 1.0f);
    }
}

void EmitRHArtificialIntelligence0041be60(RHArtificialIntelligence *self, const RHMalignityPosition &position)
{
    self->FUN_0041be60(position);
}

// STUB: GAME 0x00438cb0
bool RHArtificialMalignity::FUN_00438cb0(int command, bool mode)
{
    for (;;)
    {
        int *layout = RHMalignityField<int *volatile>(this, 0);
        RHArtificialIntelligence &base = *(RHArtificialIntelligence *)((char *)this + layout[1]);
        if (RHMalignityField<volatile unsigned char>(&base, 0x24) > 1)
        {
            switch (command)
            {
            case 0: case 2: case 3: case 4: case 5: case 10: case 11:
            case 12: case 13: case 14: case 15:
                return false;
            case 1: case 6: case 7: case 8: case 9:
                return true;
            }
        }
        if (!mode && (!RHMalignityField<unsigned char>(base.m_actor, 0x12) ||
            (RHMalignityField<void *>(RHMalignityField<void *>(base.m_actor, 0x50), 0xe0) &&
                ((unsigned char)(RHMalignityField<unsigned>(RHMalignityField<void *>(RHMalignityField<void *>(base.m_actor, 0x50), 0xe0), 0x30) >> 13) & 1))))
        {
            switch (command)
            {
            case 0: case 1: case 6: case 7: case 8: case 9:
                return false;
            case 2: case 3: case 4:
                return true;
            case 5:
                goto queryActor;
            case 15:
                if (M(unsigned short, 0x14) >= M(unsigned short, 0x10))
                    return true;
                if (RHMalignityField<int>(&VirtualBase(), 0x0c) >= 2 &&
                    RHMalignityField<int>(&VirtualBase(), 0x0c) <= 3)
                    return false;
                return M(unsigned short, 0x12) == 0;
            }
        }
        else
        {
            switch (command)
            {
            case 6:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x50) > 0;
            case 7:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x54) > 0;
            case 9:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x54) > 0;
            case 8:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x52) > 0;
            case 1:
                return M(unsigned char, 0x350) ||
                    (RHMalignityField<unsigned char>(M(void *, 0x334), 0x5c) & 0x10) ||
                    M(unsigned short, 0x338) == 100;
            case 2:
                return !M(unsigned char, 0x351) && M(unsigned short, 0x338) != 100;
            case 3:
                return !(RHMalignityField<unsigned char>(M(void *, 0x334), 0x5c) & 0x10) &&
                    M(unsigned short, 0x338) != 100;
            case 0: case 4:
                return !(RHMalignityField<unsigned char>(M(void *, 0x334), 0x5c) & 0x10) &&
                    M(unsigned short, 0x338) != 100;
            case 5:
            queryActor:
                return ((RHMalignityActorCalls *)VirtualBase().m_actor)->V12c() > (unsigned short)50;
            case 13:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x56) > 0;
            case 14:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x56) > 1 &&
                    M(unsigned short, 0x338) != 100;
            case 15:
                if (M(unsigned short, 0x14) >= M(unsigned short, 0x10))
                    return true;
                if (RHMalignityField<int>(&VirtualBase(), 0x0c) >= 2 &&
                    RHMalignityField<int>(&VirtualBase(), 0x0c) <= 3)
                    return false;
                return M(unsigned short, 0x12) == 0;
            case 10:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x36) >= 50;
            case 11:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x36) >= 50;
            case 12:
                return RHMalignityField<unsigned short>(M(void *, 0x334), 0x36) < 50 ||
                    RHMalignityField<int>(&VirtualBase(), 0x2bc) > 0;
            }
        }
        mode = false;
        command = 1;
    }
}

// FUNCTION: GAME 0x00438f80
void RHArtificialMalignity::FUN_00438f80(const RHMalignityStimulus &stimulus)
{
    switch (stimulus.m_20)
    {
    case 0x27:
        RHMalignityField<unsigned short>(this, 0x14) = 3;
        break;
    case 0x0b:
    case 0x10:
    case 0x12:
        RHMalignityField<unsigned short>(this, 0x14) = 4;
        break;
    case 9:
        RHMalignityField<unsigned short>(this, 0x14) = 6;
        break;
    case 0x0c:
        RHMalignityField<unsigned short>(this, 0x14) = 7;
        break;
    case 0x16:
    case 0x22:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x2b:
        RHMalignityField<unsigned short>(this, 0x14) = 8;
        break;
    case 0:
    case 8:
    case 0x0e:
    case 0x17:
    case 0x19:
    case 0x23:
        RHMalignityField<unsigned short>(this, 0x14) = 10;
        break;
    case 2:
    {
        struct Payload
        {
            unsigned m_00[4];
            unsigned m_10;
            unsigned m_14;
            unsigned m_18;
        };
        Payload payload = *(const Payload *)&stimulus;
        if (payload.m_10 != 13)
        {
            RHMalignityField<unsigned short>(this, 0x14) = 2;
            break;
        }
    }
    case 0x20:
        RHMalignityField<unsigned short>(this, 0x14) = 9;
        break;
    case 10:
        RHMalignityField<unsigned short>(this, 0x14) = 2;
        break;
    }
}

struct RHMalignityPriorityPosition
{
    RHMalignityPosition position;
    int priority;
    void Set(const RHMalignityPosition &value, int level)
    {
        if (priority <= level)
        {
            priority = level;
            position = value;
        }
    }
};

struct RHMalignityAlertPayload
{
    RHMalignityPosition position;
    unsigned unknown;
    void *actor;
};

struct RHArtificialIntelligenceStaticArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void *operator[](unsigned index) { return m_first[index]; }
};

struct RHMalignityTeam
{
    undefined m_00[8];
    RHArtificialIntelligenceStaticArray actors;
    undefined m_14[0xc];
};

// Parked: loop scheduling, virtual-base reloads and x87 temporary lifetimes differ.
// STUB: GAME 0x00439cb0
void RHArtificialMalignity::FUN_00439cb0(const RHMalignityPosition &position, unsigned short radius)
{
    RHMalignityStimulus stimulus;
    RHMalignityAlertPayload payload;
    payload.position = position;
    payload.actor = VirtualBase().m_actor;
    stimulus.m_20 = 0x27;
    RHMalignityField<RHMalignityAlertPayload>(&stimulus, 0) = payload;
    stimulus.m_type = 4;
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    if (count > 0)
    {
    unsigned remaining = count;
    unsigned index = 0;
    do
    {
        void *actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (actor != VirtualBase().m_actor)
        {
            void *base = (char *)actor + RHMalignityField<int *>(actor, 0x49c)[1];
            int state = RHMalignityField<int>(base, 0x4a8);
            if (state > 0 && (state <= 2 || (state == 3 &&
                RHMalignityField<int>(base, 0x4b0) >= 0x52 && RHMalignityField<int>(base, 0x4b0) <= 0x53)))
            {
                const RHUnk00613e90 &own = RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0x10);
                const RHUnk00613e90 &difference = RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(actor, 0x50), 0x10).FUN_005df550(own);
                float z = difference.z;
                float y = difference.y;
                float x = difference.x;
                if (z * z + x * x + y * y < (int)radius * radius)
                    ((RHMalignityReactionCalls *)((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1] + 0x49c))->V24(&stimulus);
            }
        }
        ++index;
    } while (--remaining != 0);
    }
}

#include "RHArtificialBonhomie.h"
#include "RHElementActorCivilianCore.h"

// SIZE 0x1c
struct RHBonhomieStimulusData
{
    undefined m_00[0x1c];
};

inline void RHBonhomieSetPoint(SBGeoPoint2D &point, float x, float y)
{
    point.m_x = x;
    point.m_y = y;
}

// Parked: actor V130 is called before the target team; forcing target first loses the shared constant register.
// STUB: GAME 0x0040d150
bool RHArtificialBonhomie::FUN_0040d150(const RHMalignityStimulus &stimulus)
{
    unsigned type = stimulus.m_20;
    RHBonhomieStimulusData data = *(const RHBonhomieStimulusData *)&stimulus;
    switch (type)
    {
    case 0x00:
        switch (*(int *)(((char *)this + (*(int **)this)[1]) + 0xc))
        {
        case 1:
        case 2:
            FUN_0040d440(*(RHElementActorHuman **)&data);
            return false;
        case 3:
        {
            RHMalignityActorCalls *target = ((RHMalignityActorCalls *)*(void **)&data);
            RHMalignityActorCalls *actor = ((RHMalignityActorCalls *)*(void **)(((char *)this + (*(int **)this)[1]) + 4));
            if (target->V130() != actor->V130())
            {
                ((RHMalignityPriorityPosition *)(((char *)this + (*(int **)this)[1]) + 0x26c))->Set(((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_004165e0(*(void **)&data, true), 5);
                return false;
            }
            break;
        }
        case 6:
        {
            RHMalignityActorCalls *actor = ((RHMalignityActorCalls *)*(void **)(((char *)this + (*(int **)this)[1]) + 4));
            int team = ((RHMalignityActorCalls *)*(void **)&data)->V130();
            if (actor->V130() == team && !*(void **)((char *)*(void **)&data + 0x268))
                break;
            if (*(int *)(((char *)this + (*(int **)this)[1]) + 0x14) != 0xde && *(unsigned short *)((char *)this + 0x16) >= 7)
                break;
            ++*(unsigned short *)((char *)this + 0x16);
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(0x53, 1);
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_00413240(((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0040cc20(*(void **)&data), 8, 2);
            return false;
        }
        }
        break;
    case 0x09:
    {
        int state = *(int *)(((char *)this + (*(int **)this)[1]) + 0xc);
        if (state > 0 && state <= 2)
        {
            FUN_0040d800(*(void **)&data);
            return false;
        }
        break;
    }
    case 0x02:
    {
        int state = *(int *)(((char *)this + (*(int **)this)[1]) + 0xc);
        if (state >= 0 && state <= 3)
        {
            FUN_0040d690(*(const RHMalignityStimulus *)&data);
            return false;
        }
        break;
    }
    case 0x16:
    {
        RHBonhomieSetPoint(*(SBGeoPoint2D *)(((char *)this + (*(int **)this)[1]) + 0xf4), *(float *)&data, *(float *)((char *)&data + 4));
        ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_00413240(*(SBGeoPoint2D *)(((char *)this + (*(int **)this)[1]) + 0xf4), 8, 2);
        return false;
    }
    case 0x46:
        if (*(int *)(((char *)this + (*(int **)this)[1]) + 0xc))
        {
            ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->FUN_0041a3e0();
            ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->V10(3, 0xfc);
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00416710(100);
        }
        break;
    }
    return false;
}

struct RHBonhomieActorBase
{
    RHArtificialIntelligence *base;
    void *actor;
};

inline RHBonhomieActorBase RHArtificialBonhomie::ActorBase()
{
    RHBonhomieActorBase result;
    result.base = (RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]);
    result.actor = *(void **)((char *)this + (*(int **)this)[1] + 4);
    return result;
}

// FUNCTION: GAME 0x0040d440
void RHArtificialBonhomie::FUN_0040d440(RHElementActorHuman *target)
{
    if (target->m_260.count)
    {
        ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_00413240(((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0040cc20(target), 8, 2);
        return;
    }
    if (((RHMalignityActorCalls *)*(void **)(((char *)this + (*(int **)this)[1]) + 4))->V130() == ((RHMalignityActorCalls *)target)->V130())
    {
        int state = *(int *)(((char *)this + (*(int **)this)[1]) + 0xc);
        if (state > 0 && state <= 2)
        {
            ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->V10(2, 0x3b);
            if ((RHMalignityField<int>(target, 4) & 0xf) == 0xc && ((RHMalignityActorCalls *)target)->V168())
                ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(0x52, 0);
            ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->FUN_0041a3e0();
            RHArtificialIntelligence &base = *(RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]);
            base.FUN_00412d60(base.FUN_004165e0(target, true),
                (int)RHMalignityField<float>(RHMalignityField<void *>(target, 0x50), 0x18), 0);
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00416710(0x3c);
        }
        return;
    }
    RHBonhomieActorBase owner = ActorBase();
    void *area = RHMalignityField<void *>(RHMalignityField<void *>(owner.actor, 0x50), 0xe0);
    if (RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 13) && area)
    {
        owner.base->Unk00418c40(0x53, 1);
        ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_004132d0(8, 0, 2);
        return;
    }
    RHMalignityField<void *>(owner.base, 0x80) = target;
    *(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0) = ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_004165e0(target, true);
    ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->V10(2, 0x3c);
    ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->FUN_0041a3e0();
    ((RHMalignityPriorityPosition *)(((char *)this + (*(int **)this)[1]) + 0x26c))->Set(*(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0), 5);
    RHBonhomieInterface(this)->FUN_00412d60(RHBonhomieInterface(this)->m_reactionPosition, -1, 0);
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00416710(0x1e);
}

// FUNCTION: GAME 0x0040d690
void RHArtificialBonhomie::FUN_0040d690(const RHMalignityStimulus &stimulus)
{
    switch (RHMalignityField<int>((void *)&stimulus, 0x10))
    {
    case 10:
        if (((RHElementActorCivilian *)*(void **)(((char *)this + (*(int **)this)[1]) + 4))->FUN_00470cc0())
        {
            RHBonhomieInterface(this)->SetReactionState(2);
            ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->V10(2, 0x43);
            *(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0) = RHMalignityField<RHMalignityPosition>((void *)&stimulus, 0);
            RHBonhomieInterface(this)->FUN_00412d60(RHBonhomieInterface(this)->m_reactionPosition, -1, 0);
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00416710(0x46);
        }
        break;
    case 7:
        *(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0) = RHMalignityField<RHMalignityPosition>((void *)&stimulus, 0);
        if (!((RHMalignityActorCalls *)*(void **)(((char *)this + (*(int **)this)[1]) + 4))->V130() || !FUN_0040e290(*(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0), 0))
            ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_00413240(((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_0040cbf0(*(RHMalignityPosition *)(((char *)this + (*(int **)this)[1]) + 0xd0)), 8, 2);
        break;
    }
}

// FUNCTION: GAME 0x0040d800
void RHArtificialBonhomie::FUN_0040d800(void *actor)
{
    *(RHMalignityPosition *)((char *)this + (*(int **)this)[1] + 0xd0) =
        ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_004165e0(actor, true);
    ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->V10(2, 0x3d);
    ((RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]))->FUN_0041a3e0();
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00418c40(0x4e, 0);
    ((RHMalignityPriorityPosition *)((char *)this + (*(int **)this)[1] + 0x26c))->Set(
        ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->FUN_004165e0(actor, true), 2);
    RHBonhomieInterface(this)->FUN_00412d60(
        *(RHMalignityPosition *)((char *)this + (*(int **)this)[1] + 0xd0), -1, 0);
    ((RHArtificialIntelligence *)((char *)this + (*(int **)this)[1]))->Unk00416710(0x3c);
}

// FUNCTION: GAME 0x00439e70
void RHArtificialMalignity::FUN_00439e70(void *, const RHMalignityPosition &position)
{
    if (((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() != 0 ||
        !RHMalignityField<bool>(g_pEngine, 0x4aa8) || ((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf4())
        ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fd0(2, 10);
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_0041a3e0();
    VirtualBase().V10(2, 0x1d);
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487ad0(position);
    VirtualBase().FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(100);
}

// FUNCTION: GAME 0x00439f60
void RHArtificialMalignity::FUN_00439f60(const RHMalignityStimulus &stimulus)
{
    const RHMalignityPosition &position = RHMalignityField<RHMalignityPosition>((void *)&stimulus, 0);
    ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fd0(2, 10);
    RHMalignityField<RHMalignityPriorityPosition>(&VirtualBase(), 0x26c).Set(position, 5);
    if (RHMalignityField<int>(M(void *, 0x334), 0x58) == 2)
        VirtualBase().V10(3, 0x54);
    else
        VirtualBase().V10(2, 0x39);
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487ad0(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0));
    void *actor = RHMalignityField<void *>((void *)&stimulus, 0x14);
    RHArtificialIntelligence &base = VirtualBase();
    base.FUN_00412d60(base.FUN_004165e0(actor, true),
        (int)RHMalignityField<float>(RHMalignityField<void *>(actor, 0x50), 0x18), 0);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(100);
}

// FUNCTION: GAME 0x0043a080
void RHArtificialMalignity::FUN_0043a080(const RHMalignityPosition &position)
{
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    RHMalignityField<RHMalignityPriorityPosition>(&VirtualBase(), 0x26c).Set(position, 5);
    switch (RHMalignityField<int>(M(void *, 0x334), 0x58))
    {
    case 0:
        FUN_0043c960(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), 0);
        M(unsigned short, 0x10) = 11;
        break;
    case 1:
        FUN_0043b1b0(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), 0);
        break;
    }
}

// FUNCTION: GAME 0x0043a170
void RHArtificialMalignity::FUN_0043a170(const RHMalignityPosition &position)
{
    ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fd0(2, 10);
    VirtualBase().V10(3, 0x8c);
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487ad0(position);
    VirtualBase().FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    FUN_00438620(50);
}

#include "RHGate.h"
#include "RHFastFindGridCore.h"

class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;

DECOMP_SIZE_ASSERT(RHUnk0051aa00, 0xbc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051aa00, m_88) == 0x88)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051aa00, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051aa00, m_16) == 0x16)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051aa00, m_18) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051aa00, m_20) == 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindGrid, m_gates) == 0x4080)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindPointerArray, m_first) == 4)

inline bool RHMalignitySectorFlag(void *sector, unsigned bit)
{
    return (RHMalignityField<unsigned>(sector, 0x30) >> bit) & 1;
}

// STUB: GAME 0x0043afc0
void RHArtificialMalignity::FUN_0043afc0(RHMalignityPosition &position, unsigned short heading)
{
    RHUnk005fc3b0 direction;
    unsigned short nearest = 300;
    RHUnk0051aa00 *selected = 0;
    RHFastFindPointerArray &gates = ((RHFastFindGrid *)g_unk0x6c0a9c)->m_gates;
    unsigned short count = gates.size();
    unsigned index = 0;
    while (count != 0)
    {
        RHUnk0051aa00 *gate = (RHUnk0051aa00 *)gates.m_first[index];
        if (RHMalignityField<unsigned>(gate, 4) == 1)
        {
            direction.FUN_005fc430(FUN_0040ec20(*(const RHMalignityPosition *)&gate->m_18, position));
            if (gate->m_88 == 1)
            {
                RHElementActor *actor = (RHElementActor *)VirtualBase().m_actor;
                void *area = RHMalignityField<void *>(RHMalignityField<void *>(actor, 0x50), 0xe0);
                if (!RHMalignitySectorFlag(area, 13))
                    area = 0;
                if (gate->m_10 != area && gate->FUN_0051abe0(true, actor, false, false, false) &&
                    gate->m_0c == position.area)
                {
                    int turn = (direction.FUN_005fcc50(0.57357645f) - heading) & 15;
                    if (turn >= 0 && (turn <= 1 || turn == 15))
                    {
                        unsigned short distance = direction.FUN_005fc700(1.0f);
                        if (distance < nearest)
                        {
                            nearest = distance;
                            selected = gate;
                        }
                    }
                }
            }
        }
        ++index;
        --count;
    }
    if (selected)
    {
        RHMalignityPosition destination;
        destination.x = selected->m_20.m_x;
        destination.y = selected->m_20.m_y;
        destination.area = selected->m_10;
        destination.layer = selected->m_16;
        position = destination;
    }
}

// FUNCTION: GAME 0x0043d780
void *RHArtificialMalignity::FUN_0043d780(unsigned short flags)
{
    unsigned short best = 0xff98;
    void *result = 0;
    const unsigned short count = (unsigned short)m_targets.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityTargetList &list = m_targets;
        list.GoTo(index);
        RHElementActor *actor = *list.m_current;
        if ((flags & 4) || FUN_0044afa0(actor))
        {
            if (FUN_0041a0b0(actor) <= best)
            {
                unsigned short value = (unsigned short)FUN_0041a060(actor);
                if (flags & 1)
                    value += RHMalignityField<short>(actor, 0x200) * 100;
                else if (flags & 2)
                    value += RHMalignityField<short>(actor, 0x200) * 10000;
                if (value < best)
                {
                    best = value;
                    result = actor;
                }
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x0043f340
bool RHArtificialMalignity::FUN_0043f340(void *actor)
{
    RHUnk005fc3b0 own;
    RHUnk005fc3b0 other;
    RHUnk005fc3b0 offset;
    if ((RHMalignityField<int>(actor, 4) & 0xf) != 0xc && RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == 0)
    {
        own.Unk005fcd40(RHMalignityHeading(VirtualBase().m_actor), 1.0f);
        other.Unk005fcd40(RHMalignityHeading(actor), 1.0f);
        if (((SBGeoVector2D &)own).FUN_005fc660(other) >= 0.0f)
        {
            offset.FUN_005fc430(FUN_0040ec20(((RHArtificialIntelligence *)((char *)this + ((int *)*(void **)this)[1]))->FUN_004165e0(actor, true), VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)));
            float y = offset.m_y;
            y *= 1.7434468269348145f;
            offset.m_y = y;
            return own.FUN_005fc680(offset, 1.0f) < 0.0f;
        }
    }
    return false;
}

// FUNCTION: GAME 0x0043f540
bool RHArtificialMalignity::FUN_0043f540(void *actor)
{
    RHUnk005fc3b0 own;
    RHUnk005fc3b0 other;
    RHUnk005fc3b0 offset;
    if ((RHMalignityField<int>(actor, 4) & 0xf) != 0xc && RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == 0)
    {
        own.Unk005fcd40(RHMalignityHeading(VirtualBase().m_actor), 1.0f);
        other.Unk005fcd40(RHMalignityHeading(actor), 1.0f);
        if (((SBGeoVector2D &)own).FUN_005fc660(other) >= 0.0f)
        {
            offset.FUN_005fc430(FUN_0040ec20(((RHArtificialIntelligence *)((char *)this + ((int *)*(void **)this)[1]))->FUN_004165e0(actor, true), VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)));
            float y = offset.m_y;
            y *= 1.7434468269348145f;
            offset.m_y = y;
            return own.FUN_005fc680(offset, 1.0f) > 0.0f;
        }
    }
    return false;
}

// Parked: VC6 slots the unused third vector after the call temporaries (target: directly above the second vector).
// STUB: GAME 0x0043fa80
void RHArtificialMalignity::FUN_0043fa80(void *target, void *actor)
{
    RHUnk005fc3b0 direction;
    RHUnk005fc3b0 offset;
    RHUnk005fc3b0 unused;
    RHMalignityPosition own;
    RHMalignityPosition other;
    own = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    other = VirtualBase().FUN_004165e0(actor, true);
    if (other.area == own.area)
    {
        direction.Unk005fcd40(RHMalignityHeading(actor), 1.0f);
        offset.FUN_005fc430(FUN_005fc580(direction.FUN_005fc8f0(1, 1.0f), 30.0f));
        float y = direction.m_y;
        y *= 0.573576450347900390625f;
        direction.m_y = y;
        y = offset.m_y;
        y *= 0.573576450347900390625f;
        offset.m_y = y;
        FUN_00440040(target, FUN_0040ed40(other, SBGeoVector2D(offset)), &direction, 0, actor);
    }
}

// Parked: VC6 slots the unused third vector after the call temporaries (target: directly above the second vector).
// STUB: GAME 0x0043fc60
void RHArtificialMalignity::FUN_0043fc60(void *target, void *actor)
{
    RHUnk005fc3b0 direction;
    RHUnk005fc3b0 offset;
    RHUnk005fc3b0 unused;
    RHMalignityPosition own;
    RHMalignityPosition other;
    own = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    other = VirtualBase().FUN_004165e0(actor, true);
    if (other.area == own.area)
    {
        direction.Unk005fcd40(RHMalignityHeading(actor), 1.0f);
        offset.FUN_005fc430(FUN_005fc580(direction.FUN_005fc8f0(1, 1.0f), 30.0f));
        float y = direction.m_y;
        y *= 0.573576450347900390625f;
        direction.m_y = y;
        y = offset.m_y;
        y *= 0.573576450347900390625f;
        offset.m_y = y;
        FUN_00440040(target, FUN_0040ece0(other, SBGeoPoint2D(offset)), &direction, 0, actor);
    }
}

// Parked 28.57%: instruction sequence matches; VC6 assigns the four callee-saved
// registers in the reverse priority order (list ebp/ebx, index esi/edi, cursor edi/esi, size ebx/ebp).
// STUB: GAME 0x00441020
int RHArtificialMalignity::FUN_00441020(RHUnk00441dd0Record *record, RHMalignityList *list)
{
    int total = FUN_00440cf0(record);
    unsigned short count = (unsigned short)list->size();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        std::bidirectional_iterator_tag category;
        do
        {
            int size = list->size();
            if (list->m_dirty)
            {
                if (index <= (size + 1) / 2)
                {
                    list->m_current = list->m_head->next;
                    FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index, category);
                }
                else
                {
                    list->m_current = list->m_head;
                    FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index - size, category);
                }
                list->m_dirty = false;
            }
            else if (index != list->m_index)
            {
                int previous = list->m_index;
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        list->m_current = list->m_head->next;
                        FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index, category);
                    }
                    else
                        FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index - previous, category);
                }
                else if (index < (previous + size) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index - previous, category);
                else
                {
                    list->m_current = list->m_head;
                    FUN_005c9010((RHUnk005c9010Iterator &)list->m_current, index - size, category);
                }
            }
            list->m_index = index;
            RHUnk00441dd0Record *value = (RHUnk00441dd0Record *)list->m_current->value;
            if (value->m_14 == record->m_0)
                total -= FUN_00440cf0(value);
            ++index;
        } while (--remaining != 0);
    }
    return total;
}

// Parked: target keeps three separate position temporaries (frame 0x30) and this in esi; VC6 shares one temporary.
// STUB: GAME 0x00441dd0
RHUnk00441dd0Record *RHArtificialMalignity::FUN_00441dd0()
{
    RHUnk00441dd0Record *record = new RHUnk00441dd0Record;
    record->m_0 = VirtualBase().m_actor;
    RHArtificialIntelligence &base = VirtualBase();
    int state = RHMalignityField<int>(&base, 0x14);
    if (state >= 0xac && state <= 0xad)
    {
        record->m_4 = base.FUN_004165e0(base.m_actor, true);
        void *actor = VirtualBase().m_actor;
        record->m_14 = RHMalignityField<int>(actor, 0x268) ? (*(RHMalignityNode **)RHMalignityField<void *>(actor, 0x264))->value : 0;
        record->m_18 = VirtualBase().FUN_004165e0(record->m_14, true);
        record->m_28 = RHMalignityHeading(record->m_14);
    }
    else
    {
        record->m_4 = RHMalignityField<RHMalignityPosition>(&base, 0xd0);
        record->m_14 = RHMalignityField<void *>(&VirtualBase(), 0x80);
        if (RHMalignityField<void *>(&VirtualBase(), 0x80))
        {
            record->m_18 = VirtualBase().FUN_004165e0(record->m_14, true);
            record->m_28 = RHMalignityHeading(record->m_14);
        }
    }
    return record;
}

// Parked 41.81% (best probed 44.65% with a hoisted local base): the target recomputes the virtual
// base/actor per access and keeps the `first` flag in a callee-saved register; the engine-array
// offset derivation and frame size also differ.
// STUB: GAME 0x00441f20
void RHArtificialMalignity::FUN_00441f20()
{
    int first = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() == 0;
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487aa0(0);
    if (M(unsigned char, 0x351) ||
        (((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() == 0 &&
         RHMalignityField<unsigned char>(g_pEngine, 0x4aa8) &&
         !((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf4()))
        VirtualBase().V00(0);

    RHMalignityTargetList &list = m_targets;
    list.Clear();
    int offset = first << 5;

    void **begin = RHMalignityField<void **>(g_pEngine, 0x4ccc + offset);
    unsigned short count = begin ? (unsigned short)(RHMalignityField<void **>(g_pEngine, 0x4cd0 + offset) - begin) : 0;
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            void *element = RHMalignityField<void **>(g_pEngine, 0x4ccc + offset)[index];
            if (RHMalignityField<unsigned char>(element, 0x1ce) && RHMalignityField<int>(element, 0x254) == 0 &&
                ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(element) && FUN_0044afa0(element))
            {
                if (list.Find((RHElementActor *)element) == -1)
                    list.InsertLast((RHElementActor *)element);
            }
            ++index;
        } while (--remaining != 0);
    }

    void *result = FUN_0043d780(0);
    B(void *, 0x80) = result;
    if (B(void *, 0x80))
    {
        VirtualBase().V10(4, 0xae);
        VirtualBase().FUN_00412cf0(VirtualBase().FUN_004165e0(B(void *, 0x80), true), 0x14, 1);
    }
    else
        VirtualBase().V00(0);
}


// SIZE 0x3c
struct RHUnk004439a0Record
{
    RHMalignityPosition m_position; // 0x00
    int m_score; // 0x10
    RHSectorActorList m_actors; // 0x14
    void *m_target; // 0x38
};

static inline void RaiseThreat(RHUnk004439a0Record &current, int score, const RHMalignityPosition &position)
{
    if (current.m_score <= score)
    {
        current.m_score = score;
        current.m_position = position;
    }
}

// FUNCTION: GAME 0x00443500
bool RHArtificialMalignity::FUN_00443500()
{
    SBGeoVector2D direction = ((RHUnk005fc3b0 &)((RHElementActor *)VirtualBase().m_actor)->FUN_004135b0()).FUN_005fc8f0(false, 0.57357644f);
    short score = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityList>(&VirtualBase(), 0x100).size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(&VirtualBase(), 0x100);
        list.FUN_005c8e40(index);
        void *actor = list.m_current->value;
        if (actor == VirtualBase().m_actor)
            continue;
        if ((RHMalignityField<unsigned>(actor, 4) & 0x1f) != 0x14)
            continue;
        switch (RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0))
        {
        case 0xa7:
        case 0xa8:
        case 0xb0:
        case 0xb1:
        case 0xb2:
        case 0xb3:
        case 0xb4:
        case 0xb7:
        case 0xb8:
        case 0xb9:
        case 0xba:
        case 0xbb:
        case 0xbc:
            short facing = (short)direction.FUN_005fc660(FUN_0040ec20(((RHArtificialIntelligence *)((char *)this + ((int *)*(void **)this)[1]))->FUN_004165e0(actor, true), VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)));
            if (facing > 0)
            {
                if (facing <= 200)
                    score += 200 - facing;
            }
            else if (facing >= -200)
                score += -200 - facing;
            break;
        }
    }
    return score > 0;
}

// SIZE 0x1c
struct RHUnk00443850Record
{
    void *m_actor; // 0x00
    undefined m_04[0x18]; // 0x04
};

// FUNCTION: GAME 0x004436e0
bool RHArtificialMalignity::FUN_004436e0(const RHUnk00443850Record *source, bool mode)
{
    RHUnk00443850Record entry = *source;
    void *actor = entry.m_actor;
    RHUnk004439a0Record *record = &RHMalignityField<RHUnk004439a0Record>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x708);
    int score = RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c).m_score;
    FUN_004439a0(record, 7);
    ((RHArtificialMalignity *)((char *)actor + 0x6e8))->FUN_004439a0(&RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c), 0);
    if (record->m_score <= score || record->m_score <= 2)
        return false;
    if (mode && score != 3)
        return false;
    VirtualBase().V10(3, 0x5a);
    RHMalignityField<void *>(&VirtualBase(), 0x90) = actor;
    void *target = RHMalignityField<void *>(&VirtualBase(), 0x90);
    RHArtificialIntelligence &base = VirtualBase();
    base.FUN_00412d60(base.FUN_004165e0(target, true),
        (int)RHMalignityField<float>(RHMalignityField<void *>(target, 0x50), 0x18), 0);
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = record->m_position;
    int threat = record->m_score;
    RaiseThreat(RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c), threat, RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0));
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(0x1e);
    return true;
}

// FUNCTION: GAME 0x00443850
bool RHArtificialMalignity::FUN_00443850(const RHUnk00443850Record *source)
{
    RHUnk00443850Record entry = *source;
    void *actor = entry.m_actor;
    RHUnk004439a0Record *record = &RHMalignityField<RHUnk004439a0Record>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x708);
    int score = RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c).m_score;
    FUN_004439a0(record, 7);
    if (record->m_score <= score || record->m_score < 2)
        return false;
    VirtualBase().V10(3, 0x95);
    RHMalignityField<void *>(&VirtualBase(), 0x90) = actor;
    void *target = RHMalignityField<void *>(&VirtualBase(), 0x90);
    RHArtificialIntelligence &base = VirtualBase();
    base.FUN_00412d60(base.FUN_004165e0(target, true),
        (int)RHMalignityField<float>(RHMalignityField<void *>(target, 0x50), 0x18), 0);
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = record->m_position;
    int threat = record->m_score;
    RaiseThreat(RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c), threat, RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0));
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(0x1e);
    return true;
}

// Parked 83%: the actor-cursor, target-notify and threat-copy loads keep swapped scratch registers.
// STUB: GAME 0x004439a0
void RHArtificialMalignity::FUN_004439a0(RHUnk004439a0Record *record, unsigned char flags)
{
    int count = record->m_actors.m_count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHSectorActorList &actors = record->m_actors;
        actors.Unk005c8e40(index);
        void *actor = actors.m_cur.m_p->m_data;
        RHUnk004439a0Record &own = RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c);
        if (own.m_actors.Unk004b8f80((RHElementActor *)actor, true) == -1)
        {
            if (flags & 1)
            {
                RHSectorActorList &list = RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c).m_actors;
                ((RHAIUnk0044e8b0 *)&list)->FUN_00424410(RHMalignityIterator((RHMalignityNode *)list.m_head), (RHElementActor *)actor);
                list.m_valid = true;
            }
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048ca20(actor, 1);
        }
    }
    if ((flags & 2) && record->m_target)
    {
        RHArtificialIntelligence &base = VirtualBase();
        if (!RHMalignityField<void *>(&base, 0x2a4))
        {
            RHMalignityField<void *>(&base, 0x2a4) = record->m_target;
            RHMalignityField<bool>(&base, 0x2a8) = false;
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048c700(record->m_target, 4);
        }
    }
    if (flags & 4)
    {
        RHMalignityPosition position = record->m_position;
        int score = record->m_score;
        RHUnk004439a0Record &own = RHMalignityField<RHUnk004439a0Record>(&VirtualBase(), 0x26c);
        if (own.m_score <= score)
        {
            own.m_score = score;
            own.m_position = position;
        }
    }
}

// FUNCTION: GAME 0x00443af0
void RHArtificialMalignity::FUN_00443af0(unsigned value)
{
    void *target;
    if (RHMalignityField<RHSectorActorList>(&VirtualBase(), 0x2b4).m_count > 0)
    {
        RHSectorActorList &threats = RHMalignityField<RHSectorActorList>(&VirtualBase(), 0x2b4);
        threats.Unk005c8e40(0);
        target = threats.m_cur.m_p->m_data;
        if ((RHMalignityField<unsigned>(target, 4) & 0x1f) == 0x14 &&
            RHMalignityField<int>(RHMalignityField<void *>(target, 0xa1c), 0x58) == 0 && target)
            goto selected;
    }
    target = FUN_00443e20(((RHMalignityActorCalls *)VirtualBase().m_actor)->V130(), 200, 2, 0);
selected:
    VirtualBase().FUN_0041a140(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), value);
    VirtualBase().V10(3, 0x73);
    if (!target)
        ((RHArtificialIntelligence *)&VirtualBase())->Unk00412f70((RHMalignityField<short>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0xd8) + 5) % 16, 0);
    else
    {
        RHArtificialIntelligence &own = VirtualBase();
        own.FUN_00412d60(own.FUN_004165e0(target, true),
            (int)RHMalignityField<float>(RHMalignityField<void *>(target, 0x50), 0x18), 0);
    }
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(0x14);
}

// FUNCTION: GAME 0x00443c40
void *RHArtificialMalignity::FUN_00443c40(void *value)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (RHMalignityActorCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == 1 && actor->V11c() &&
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(actor) &&
            !RHMalignityField<bool>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x660) &&
            !actor->FUN_0048c8e0(value, 1))
            return actor;
    }
    return 0;
}

bool FUN_0040eda0(const RHMalignityPosition *value, RHMalignityPosition other);

// FUNCTION: GAME 0x00443d10
void *RHArtificialMalignity::FUN_00443d10(const RHMalignityPosition *position)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (RHMalignityActorCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == 1 && actor->V11c() &&
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(actor) &&
            !RHMalignityField<bool>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x660) &&
            FUN_0040eda0(&RHMalignityField<RHMalignityPosition>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x56c), *position))
            return actor;
    }
    return 0;
}

// FUNCTION: GAME 0x00443e20
void *RHArtificialMalignity::FUN_00443e20(int team, unsigned short radius, unsigned char flags, int type)
{
    unsigned best = radius * radius;
    void *result = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (RHMalignityActorCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors.m_first[index];
        bool eligible = (void *)actor != VirtualBase().m_actor;
        eligible &= !actor->V48();
        eligible &= !RHMalignityField<bool>(actor, 0x1ce) & RHMalignityField<bool>(actor, 0x12);
        if ((type == 3 || ((RHMalignityField<unsigned>(actor, 4) & 0x1f) == 0x14 &&
                           RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == type)) &&
            eligible)
        {
            if ((flags & 1) && ((RHMalignityField<unsigned>(actor, 4) & 0xf) != 4 ||
                                RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4a8) != 1))
                continue;
            if (flags & 2)
            {
                if ((RHMalignityField<unsigned>(actor, 4) & 0xf) != 4)
                    continue;
                switch (RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4a8))
                {
                case 1:
                    break;
                case 3:
                    if (RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0) == 0x6d)
                        break;
                default:
                    continue;
                }
            }
            unsigned distance = (unsigned)VirtualBase().FUN_0041a010(actor);
            if (distance <= best)
            {
                best = distance;
                result = actor;
            }
        }
    }
    return result;
}

// Parked: route generation builds nested geometry/list temporaries and requires unresolved helper ABIs.
// STUB: GAME 0x00443fa0
unsigned RHArtificialMalignity::FUN_00443fa0(unsigned, unsigned, unsigned, unsigned)
{
    return 0;
}

#include "RHElementActorSoldierCore.h"

// FUNCTION: GAME 0x00444440
void RHArtificialMalignity::ForceAttentiveMode(bool attentive)
{
    M(bool, 0x346) = attentive;
    if (attentive)
    {
        ((RHElementActorSoldier *)VirtualBase().m_actor)->SetAttentiveMode(true, false);
        void *actor = m_actor;
        int offset = (*(int **)this)[1];
        RHArtificialIntelligence *base = (RHArtificialIntelligence *)((char *)this + offset);
        if (RHMalignityField<int>(actor, 0x658) == 0 &&
            RHMalignityField<unsigned>(g_pEngine, 0x4a94) > 1)
            base->SetMusicState(1, 0);
    }
}

// Parked: AI state transition allocates exception-cleaned path and sector-list objects.
// STUB: GAME 0x004444a0
void RHArtificialMalignity::FUN_004444a0()
{
}

// Parked: the waypoint rebuild uses geometry construction, dynamic allocation and list-node insertion.
// STUB: GAME 0x00444bb0
void RHArtificialMalignity::FUN_00444bb0(void *)
{
}

// FUNCTION: GAME 0x004450a0
void RHArtificialMalignity::FUN_004450a0(void *target)
{
    RHMalignityActorCalls **first = RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x495c);
    unsigned short count;
    if (!first)
        count = 0;
    else
        count = RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x4960) - first;
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x495c)[index];
        if ((RHMalignityField<unsigned>(actor, 4) & 0x1f) == 0x14 && (void *)actor != VirtualBase().m_actor && actor != target &&
            (RHMalignityField<int>(M(void *, 0x334), 0x58) == 1 || actor != RHMalignityField<void *>(&VirtualBase(), 0x90)))
        {
            if (actor->FUN_0048a350(target) || (target != VirtualBase().m_actor && actor->FUN_0048a350(VirtualBase().m_actor)))
                ((RHMalignityAlertCalls *)((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1] + 0x49c))->FUN_0042c890(0x2c, target);
        }
    }
}

// FUNCTION: GAME 0x00445180
void RHArtificialMalignity::FUN_00445180(void *value)
{
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_0041a3e0();
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x23, *(void **)((char *)&VirtualBase() + 4), value);
    RHSequenceManager::Instance()->Unk0058a940("", 0, action);
}

class RHMalignityHeadingPoint : public SBGeoPoint2D
{
public:
    unsigned char FUN_005fcc50(float value) const;
};





// FUNCTION: GAME 0x00445510
bool RHArtificialMalignity::FUN_00445510(RHMalignityPosition position, void *actor)
{
    RHUnk005fc3b0 direction;
    if (M(void *, 0x228))
        return false;
    if (((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() == 0 &&
        RHMalignityField<bool>(g_pEngine, 0x4aa8) && !((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf4())
        return false;
    direction.FUN_005fc430(FUN_0040ec20(position, VirtualBase().FUN_004165e0(actor, true)));
    float distance = direction.Unk005fc6d0(0.57357645f);
    unsigned short heading = RHMalignityHeading(actor);
    float radius;
    unsigned relativeHeading = (direction.FUN_005fcc50(0.57357645f) - heading) & 15;
    switch (relativeHeading)
    {
    case 0:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 3:
        case 9:
            radius = 300.0f;
            break;
        case 2:
        case 8:
        case 14:
            radius = 250.0f;
            break;
        default:
            goto radius100;
        }
        break;
    case 1:
    case 15:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 2:
        case 8:
        case 14:
            goto radius100;
        case 3:
        case 9:
            radius = 250.0f;
            break;
        default:
            radius = 100.0f;
            break;
        }
        break;
    case 2:
    case 14:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 3:
        case 9:
            radius = 180.0f;
            break;
        case 2:
        case 8:
        case 14:
radius100:
            radius = 150.0f;
            break;
        default:
            radius = 100.0f;
            break;
        }
        break;
    case 3:
    case 4:
    case 12:
    case 13:
        radius = 100.0f;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        radius = 80.0f;
        break;
    default:
        radius = distance;
        break;
    }
    return distance < radius * radius;
}

class RHMalignityRemarkCalls
{
public:
    void Unk00418c40(int remark, unsigned flags);
};

// Parked: inline unique-list scheduling and the remark-call view remain unmatched.
// STUB: GAME 0x004457c0
void RHArtificialMalignity::FUN_004457c0(const RHMalignityPosition &position)
{
    if (!FUN_00438cb0(15, 0))
        return;
    M(unsigned short, 0x10) = M(unsigned short, 0x14);
    if (RHMalignityField<void *>(&VirtualBase(), 0x1f8))
    {
        RHSectorActorList &list = RHMalignityField<RHSectorActorList>(&VirtualBase(), 0x1d4);
        if (list.Find((RHElementActor *)RHMalignityField<void *>(&VirtualBase(), 0x1f8)) == -1)
        {
            RHMalignityNode *head = (RHMalignityNode *)list.m_head;
            RHMalignityNode *previous = head->previous;
            RHMalignityNode *node = (RHMalignityNode *)operator new(12);
            node->next = head ? head : node;
            node->previous = previous ? previous : node;
            head->previous = node;
            node->previous->next = node;
            new (&node->value) void *(RHMalignityField<void *>(&VirtualBase(), 0x1f8));
            ++list.m_count;
            list.m_valid = true;
        }
        RHMalignityField<void *>(&VirtualBase(), 0x1f8) = 0;
    }
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_0041a3e0();
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    VirtualBase().V10(2, 0x25);
    ((RHMalignityRemarkCalls *)&VirtualBase())->Unk00418c40(((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf8() ? 0x75 : 0x25, 0);
    VirtualBase().FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    VirtualBase().SetReactionState(2);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(50);
}

template <bool InlineHead>
struct RHMalignityEraseList : public RHMalignityList
{
    RHMalignityNode *At(int wanted)
    {
        FUN_005c8e40(wanted);
        return m_current;
    }
    RHMalignityNode *SeekAt(int wanted)
    {
        SeekErase(wanted);
        return m_current;
    }
    void SeekErase(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                m_current = InlineHead ? m_head->next : (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                m_current = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else if (wanted != m_index)
        {
            int previous = m_index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    m_current = InlineHead ? m_head->next : (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
            }
            else if (wanted < (previous + count) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            }
            else
            {
                m_current = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
            }
            m_index = wanted;
        }
    }
};

// Parked: cached-list erase frame and iterator-assignment scheduling differ.
// STUB: GAME 0x004459b0
void RHArtificialMalignity::FUN_004459b0()
{
    unsigned count = M(RHMalignityList, 0x194).m_count;
    for (unsigned index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        RHMalignityEraseList<false> &list = RHMalignityField<RHMalignityEraseList<false> >(this, 0x194);
        list.FUN_005c8e40((unsigned short)index);
        if (!RHMalignityField<bool>(list.m_current->value, 0x12))
        {
            list.SeekErase((unsigned short)index);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current));
            index += 0xffff;
            count += 0xffff;
            list.m_dirty = true;
        }
    }
    void *&target = RHMalignityField<void *>(&VirtualBase(), 0x8c);
    if (target && !RHMalignityField<bool>(target, 0x12))
        target = 0;
}

// Parked: cached-list iterator temporaries and erase argument scheduling differ.
// STUB: GAME 0x00445b40
void RHArtificialMalignity::FUN_00445b40()
{
    unsigned count = RHMalignityField<RHMalignityList>(VirtualBase().m_actor, 0x56c).m_count;
    for (unsigned index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(VirtualBase().m_actor, 0x56c);
        list.FUN_005c8e40((unsigned short)index);
        void *&value = list.m_current->value;
        if (VirtualBase().FUN_0041a0b0(value) < g_unk0x00677564 && RHMalignityField<int>(value, 0xb0) == 8)
        {
            RHMalignityEraseList<false> &removed = RHMalignityField<RHMalignityEraseList<false> >(VirtualBase().m_actor, 0x56c);
            removed.SeekErase((unsigned short)index);
            ((RHUnk0046eb30 *)&removed)->erase(RHScriptIter((RHScriptNode *)removed.m_current));
            removed.m_dirty = true;
            index += 0xffff;
            count += 0xffff;
        }
    }
    RHMalignityList &list = M(RHMalignityList, 0x194);
    RHMalignityNode *head = list.m_head;
    RHMalignityNode *current = head->next;
    while (current != head)
    {
        RHMalignityNode *removed = current;
        current = current->next;
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        operator delete(removed);
        --list.m_count;
    }
    list.m_dirty = true;
}

class RHMalignityGuardCalls
{
public:
    void FUN_0049fbb0(void *actor);
};

#include "RHFastFindArcheryArray.h"

class RHMalignityTargetCalls
{
public:
    virtual void V000() = 0;
    virtual void V004() = 0;
    virtual void V008() = 0;
    virtual void V00c() = 0;
    virtual void V010() = 0;
    virtual void V014() = 0;
    virtual void V018() = 0;
    virtual void V01c() = 0;
    virtual void V020() = 0;
    virtual void V024() = 0;
    virtual void V028() = 0;
    virtual void V02c() = 0;
    virtual void V030() = 0;
    virtual void V034() = 0;
    virtual void V038() = 0;
    virtual void V03c() = 0;
    virtual void V040() = 0;
    virtual void V044() = 0;
    virtual bool V048() = 0;
    virtual void V04c() = 0;
    virtual void V050() = 0;
    virtual void V054() = 0;
    virtual void V058() = 0;
    virtual void V05c() = 0;
    virtual void V060() = 0;
    virtual void V064() = 0;
    virtual void V068() = 0;
    virtual void V06c() = 0;
    virtual void V070() = 0;
    virtual void V074() = 0;
    virtual void V078() = 0;
    virtual void V07c() = 0;
    virtual void V080() = 0;
    virtual void V084() = 0;
    virtual void V088() = 0;
    virtual void V08c() = 0;
    virtual void V090() = 0;
    virtual void V094() = 0;
    virtual void V098() = 0;
    virtual void V09c() = 0;
    virtual void V0a0() = 0;
    virtual void V0a4() = 0;
    virtual void V0a8() = 0;
    virtual void V0ac() = 0;
    virtual void V0b0() = 0;
    virtual void V0b4() = 0;
    virtual void V0b8() = 0;
    virtual void V0bc() = 0;
    virtual void V0c0() = 0;
    virtual void V0c4() = 0;
    virtual void V0c8() = 0;
    virtual void V0cc() = 0;
    virtual void V0d0() = 0;
    virtual void V0d4() = 0;
    virtual void V0d8() = 0;
    virtual void V0dc() = 0;
    virtual void V0e0() = 0;
    virtual void V0e4() = 0;
    virtual void V0e8() = 0;
    virtual void V0ec() = 0;
    virtual void V0f0() = 0;
    virtual void V0f4() = 0;
    virtual bool V0f8() = 0;
    virtual void V0fc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual bool V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0;
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140() = 0;
    virtual void V144() = 0;
    virtual void V148() = 0;
    virtual void V14c() = 0;
    virtual void V150() = 0;
    virtual void V154() = 0;
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual bool V168() = 0;
    unsigned m_04;
};

// FUNCTION: GAME 0x004460f0
bool RHArtificialMalignity::FUN_004460f0()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
        if (state >= 0x29 && state <= 0x34 && state != 0x29 && VirtualBase().m_actor != actor &&
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a350(actor))
            return true;
    }
    return false;
}

struct RHMalignityFindList : public RHSectorActorList
{
    void FindForward(void *const &value)
    {
        RHSectorActorNode *head = *(RHSectorActorNode *volatile *)&m_head;
        int count = m_count;
        m_searchValue = (RHElementActor *)value;
        m_searchValid = true;
        m_cur.m_p = head->m_next;
        int index;
        for (index = 0; index < count; ++index, m_cur.m_p = m_cur.m_p->m_next)
        {
            RHSectorActorNode *node = m_cur.m_p;
            RHElementActor *wanted = m_searchValue;
            if (*(void *volatile *)&node->m_data == wanted)
                break;
        }
        if (index < count)
        {
            m_searchIndex = index;
            m_valid = false;
            m_index = index;
            return;
        }
        m_valid = true;
        m_searchIndex = -1;
    }
};

// Parked: inline search argument registers, payload loads, and cursor-update order differ.
// STUB: GAME 0x004461a0
void RHArtificialMalignity::FUN_004461a0(void *target, void *actor)
{
    if (!((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a350(actor))
        return;
    if (target != RHMalignityField<void *>(&VirtualBase(), 0x8c))
    {
        M(RHMalignityFindList, 0x194).FindForward(target);
        if (M(RHMalignityFindList, 0x194).m_searchIndex == -1)
            return;
    }
    if (!FUN_00438cb0(9, false))
        return;
    if (!FUN_004468a0())
    {
        RHMalignityList &list = M(RHMalignityList, 0x1dc);
        ((RHAIUnk0044e8b0 *)&list)->FUN_0044e8b0(RHMalignityIterator(list.m_head->next), RHMalignityIterator(list.m_head));
        list.m_dirty = true;
        FUN_004469e0();
        return;
    }
    switch (RHMalignityField<int>(&VirtualBase(), 0x14))
    {
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    {
        ((RHArtificialIntelligence *)&VirtualBase())->Unk00410600();
        RHArtificialIntelligence &base = VirtualBase();
        base.FUN_00412d60(base.FUN_004165e0(actor, true),
            (int)RHMalignityField<float>(RHMalignityField<void *>(actor, 0x50), 0x18), 0);
        VirtualBase().SetReactionState(2);
        VirtualBase().V10(2, 0x2d);
        RHSectorActorList &list = M(RHSectorActorList, 0x1dc);
        if (list.Unk004b8f80((RHElementActor *const &)actor, true) == -1)
        {
            ((RHAIUnk0044e8b0 *)&list)->FUN_00424410(RHMalignityIterator((RHMalignityNode *)list.m_head), actor);
            list.m_valid = true;
        }
        FUN_00438620(0x1e);
        RHMalignityField<void *>(&VirtualBase(), 0x84) = actor;
        return;
    }
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    {
        RHSectorActorList &list = M(RHSectorActorList, 0x1dc);
        if (list.Unk004b8f80((RHElementActor *const &)actor, true) == -1)
            ((RHMalignityList *)&list)->InsertLast(actor);
        return;
    }
    }
}

// Parked: actor-loop zero-test and inline unique-list payload scheduling differ.
// STUB: GAME 0x00446700
void RHArtificialMalignity::FUN_00446700()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    RHSectorActorList &list = M(RHSectorActorList, 0x1dc);
    ((RHAIUnk0044e8b0 *)&list)->FUN_0044e8b0(RHMalignityIterator((RHMalignityNode *)list.m_head->m_next), RHMalignityIterator((RHMalignityNode *)list.m_head));
    list.m_valid = true;
    unsigned remaining = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned offset = 0; remaining != 0; offset += 4, --remaining)
    {
        RHMalignityTargetCalls *actor = *(RHMalignityTargetCalls **)((char *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.m_first + offset);
        if ((void *)actor == VirtualBase().m_actor || RHMalignityField<bool>(actor, 0x1ce) ||
            ((RHMalignityTargetCalls *)actor)->V048() || !((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(actor))
            continue;
        int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
        if (state < 0x29 || state > 0x34)
            continue;
        void *value = actor;
        ((RHMalignityFindList *)&list)->FindForward(value);
        if (list.m_searchIndex == -1)
            ((RHMalignityList *)&list)->InsertLast(value);
    }
}

// FUNCTION: GAME 0x0042ff90
void RHArtificialMalignity::FUN_0042ff90()
{
    if (RHMalignityField<void *>(VirtualBase().m_actor, 0x268))
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x33, VirtualBase().m_actor);
        RHSequenceManager::Instance()->Unk0058a940("", 0, action);
    }
}

// Parked at 0.7739: extra stack slot and list-search register/scheduling residuals.
// STUB: GAME 0x00430020
void RHArtificialMalignity::FUN_00430020()
{
    RHMalignityTargetList &list = m_targets;
    for (RHMalignityTargetList::iterator node = list.begin(); node != list.end();)
        node = list.erase(node);
    list.m_dirty = true;
    unsigned short count = RHMalignityField<RHMalignityList>(VirtualBase().m_actor, 0x504).size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMalignityList &weapons = RHMalignityField<RHMalignityList>(VirtualBase().m_actor, 0x504);
        weapons.FUN_005c8e40(i);
        if (RHMalignityField<bool>(weapons.m_current, 0x12))
        {
            void *value = ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048ee90(i);
            if (!((RHMalignityTargetCalls *)value)->V048())
            {
                if (list.Find((RHElementActor *)value) == -1)
                    list.InsertLast((RHElementActor *)value);
            }
        }
    }
}

// GLOBAL: GAME 0x00677564
float g_unk0x00677564 = 500.0f;

// FUNCTION: GAME 0x00430170
bool RHArtificialMalignity::FUN_00430170(RHMalignityList &list, int team)
{
    ((RHAIUnk0044e8b0 *)&list)->FUN_0044e8b0(RHMalignityIterator(list.m_head->next), RHMalignityIterator(list.m_head));
    list.m_dirty = true;
    bool included;
    if (team == ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130())
    {
        void *actor = VirtualBase().m_actor;
        ((RHAIUnk0044e8b0 *)&list)->FUN_00424410(RHMalignityIterator(list.m_head), actor);
        list.m_dirty = true;
        included = true;
    }
    else
        included = false;
    unsigned count = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors.size();
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        void *actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors[index];
        if (VirtualBase().FUN_0041a0b0(actor) < g_unk0x00677564 &&
            (!included || RHMalignityField<void *>(actor, 0x268)) &&
            actor != VirtualBase().m_actor && ((RHMalignityActorCalls *)actor)->V11c())
        {
            ((std::list<void *> *)&list)->push_back(actor);
            list.m_dirty = true;
        }
    }
    return list.m_count > 0;
}

void EmitRHMalignityTeamList(RHArtificialMalignity &ai, RHMalignityList &list, int team)
{
    ai.FUN_00430170(list, team);
}

// FUNCTION: GAME 0x00432d30
int RHArtificialMalignity::FUN_00432d30()
{
    if (RHMalignityField<void *>(VirtualBase().m_actor, 0x258) &&
        (VirtualBase().m_actor->Ve4(1) == 0 ||
         RHMalignityField<void *>(VirtualBase().m_actor, 0x268)))
        return 2;
    if (VirtualBase().m_0c == 6)
        return 2;

    unsigned short strength = 0;
    bool hasOfficer = false;
    unsigned count = VirtualBase().m_100.size();
    if ((unsigned short)count > 0)
    {
        unsigned index = 0;
        unsigned remaining = (unsigned short)count;
        do
        {
            RHArtificialIntelligenceCachedList<void *> &allies = VirtualBase().m_100;
            allies.GoTo(index);
            RHArtificialIntelligenceActor *actor = static_cast<RHArtificialIntelligenceActor *>(*allies.Current());
            unsigned short value;
            if ((actor->m_flags & 15) == 12)
                value = 100;
            else
            {
                void *profile = RHMalignityField<void *>(actor, 0xa1c);
                value = RHMalignityField<unsigned short>(profile, 0x38) + 100;
                hasOfficer |= actor != VirtualBase().m_actor &&
                              RHMalignityField<int>(profile, 0x58) == 1;
            }
            strength += value;
            ++index;
        } while (--remaining);
    }

    unsigned opponents = 0;
    count = m_targets.size();
    if ((unsigned short)count > 0)
    {
        unsigned index = 0;
        unsigned remaining = (unsigned short)count;
        opponents = static_cast<unsigned short>(count) * 100;
        do
        {
            m_targets.GoTo(index);
            ++index;
        } while (--remaining);
    }

    unsigned short defense = static_cast<unsigned short>(opponents);
    ++defense;
    unsigned short ratio = strength * 100 / defense;
    short confidence;
    if (ratio >= 100)
    {
        confidence = 50 + (ratio - 100) * 50 / 200;
        if (confidence > 100)
            confidence = 100;
    }
    else
    {
        confidence = (ratio - 20) * 50 / 80;
        if (confidence < 0)
            confidence = 0;
    }

    unsigned short capacity = VirtualBase().m_actor->Vd0();
    if (VirtualBase().m_actor->Vcc() < capacity)
        confidence = VirtualBase().m_actor->Vcc() * confidence / capacity;

    void *profile = M(void *, 0x334);
    if (RHMalignityField<int>(profile, 0x58) == 0 && hasOfficer)
        confidence *= 30;
    short courage = RHMalignityField<short>(profile, 0x34);
    int threshold = static_cast<unsigned short>(courage) / 2;
    if (confidence < 50 - threshold)
    {
        int roll = rand();
        if (roll % 100 > static_cast<int>(static_cast<unsigned>(courage) % 65536u))
            return 2;
    }
    return 1;
}

int EmitRHMalignityConfidence(RHArtificialMalignity &ai)
{
    return ai.FUN_00432d30();
}

class RHMalignityVirtualView : public virtual RHArtificialIntelligence
{
};

class RHMalignityBaseData
{
public:
    virtual void V00(int mode) = 0;
    undefined m_04[0xcc];
    RHMalignityPosition m_d0;
};

class RHMalignityDataView : public virtual RHMalignityBaseData
{
};

// FUNCTION: GAME 0x004468a0
bool RHArtificialMalignity::FUN_004468a0()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    if (RHMalignityField<unsigned short>(M(void *, 0x334), 0x54) == 100 || RHMalignityField<unsigned char>(&VirtualBase(), 0x24) > 0)
        return true;
    unsigned short fighters = 1;
    unsigned short helpers = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if ((void *)actor != VirtualBase().m_actor && !actor->V048() &&
            ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(actor))
        {
            int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
            if (state != 2)
            {
                if (state > 0x28 && state <= 0x34)
                    ++fighters;
            }
            else if (RHMalignityField<bool>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x748))
                ++helpers;
        }
    }
    return (unsigned short)(helpers * 100 / (fighters + helpers)) < RHMalignityField<unsigned short>(M(void *, 0x334), 0x54);
}

// FUNCTION: GAME 0x004469e0
void RHArtificialMalignity::FUN_004469e0()
{
    FUN_004459b0();
    void *target = FUN_00445d40();
    RHMalignityField<void *>(&VirtualBase(), 0x8c) = target;
    if (RHMalignityField<void *>(&VirtualBase(), 0x8c))
    {
        VirtualBase().V10(2, 0x2b);
        ((RHMalignityVirtualView *)this)->FUN_00412cf0(VirtualBase().FUN_004165e0(RHMalignityField<void *>(&VirtualBase(), 0x8c), true), 0x14, 0x201);
    }
    else
    {
        VirtualBase().V10(2, 0x32);
        VirtualBase().V04(2);
    }
}

inline void RHMalignityList::Seek(int wanted)
{
    std::bidirectional_iterator_tag category;
    if (m_dirty)
    {
        if (wanted <= (m_count + 1) / 2)
        {
            m_current = m_head->next;
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
        }
        else
        {
            m_current = m_head;
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - m_count, category);
        }
        m_dirty = false;
    }
    else if (wanted != m_index)
    {
        int previous = m_index;
        if (wanted < previous)
        {
            if (wanted < (previous + 1) / 2)
            {
                m_current = (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
        }
        else if (wanted < (previous + m_count) / 2)
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
        else
        {
            m_current = m_head;
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - m_count, category);
        }
    }
    m_index = wanted;
}

// STUB: GAME 0x00446400
RHElementActor *RHArtificialMalignity::FUN_00446400()
{
    SBGeoPoint2D origin;
    unsigned bestDistance = 0xff98;
    RHArtificialIntelligence &base = VirtualBase();
    origin = base.FUN_0040cc20(base.m_actor);
    unsigned short layer = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true).layer;
    RHSectorActorList &candidates = M(RHSectorActorList, 0x1dc);
    unsigned count = candidates.m_count;
    unsigned closest = 0;

    for (unsigned index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        candidates.Unk005c8e40(index);
        RHElementActor *candidate = *candidates.m_cur;
        unsigned distance = (unsigned short)VirtualBase().FUN_0040cc20(candidate)
            .Unk005fc110(origin).FUN_005fc700(1.0f);
        if (RHMalignityField<unsigned short>(candidate->m_50, 0xde) != layer)
            distance += 300;
        if ((unsigned short)distance < (unsigned short)bestDistance)
        {
            bestDistance = distance;
            closest = index;
        }
    }

    if (!(unsigned short)count)
        return 0;

    candidates.Unk005c8e40((unsigned short)closest);
    return *candidates.m_cur;
}

inline void RHMalignityList::RemoveFirst()
{
    RHMalignityNode *node = m_head->next;
    node->previous->next = node->next;
    node->next->previous = node->previous;
    operator delete(node);
    --m_count;
    m_dirty = true;
}

// Parked: cached-list count loads, iterator assignment, and advance scheduling differ.
// STUB: GAME 0x00446d20
void RHArtificialMalignity::FUN_00446d20()
{
    if (RHMalignityField<RHMalignityList>(this, 0x200).m_count > 0)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x200);
        list.Seek(0);
        RHMalignityField<void *>(&VirtualBase(), 0x88) = list.m_current->value;
        list.RemoveFirst();
        VirtualBase().V10(2, 0xf1);
        ((RHMalignityVirtualView *)this)->FUN_00412cf0(VirtualBase().FUN_004165e0(RHMalignityField<void *>(&VirtualBase(), 0x88), true), 0x14, 0);
    }
    else
        VirtualBase().V00(0);
}

struct RHMalignitySearchListSearch
{
    undefined4 m_allocator; // 0x00
    RHMalignityNode *m_head; // 0x04
    int m_count; // 0x08
    RHMalignityNode *volatile m_current; // 0x0c
    bool m_dirty; // 0x10
    undefined m_11[3]; // 0x11
    int m_index; // 0x14
    bool m_forward; // 0x18
    undefined m_19[3]; // 0x19
    volatile int m_result; // 0x1c
    void *volatile m_value; // 0x20

    int FindForward(void *const &value)
    {
        m_value = value;
        int count = m_count;
        m_forward = true;
        m_current = m_head->next;
        int index;
        for (index = 0; index < count; ++index)
        {
            if (*(void *volatile *)&m_current->value == m_value)
                break;
            m_current = m_current->next;
        }
        if (index < count)
        {
            m_result = index;
            m_dirty = false;
            m_index = index;
            return index;
        }
        m_dirty = true;
        m_result = -1;
        return m_result;
    }

    void SeekFound(int wanted)
    {
        std::bidirectional_iterator_tag category;
        if (m_dirty)
        {
            if (wanted <= (m_count + 1) / 2)
            {
                m_current = (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                m_current = m_head;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - m_count, category);
            }
            m_dirty = false;
        }
        else if (wanted != m_index)
        {
            int previous = m_index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    m_current = (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
                }
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            }
            else if (wanted < (previous + m_count) / 2)
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            else
            {
                m_current = m_head;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - m_count, category);
            }
        }
        m_index = wanted;
    }
};

// Parked: inlined search retains a zero register and adds unconditional callee-save pushes.
// STUB: GAME 0x00446eb0
void RHArtificialMalignity::FUN_00446eb0(void *actor)
{
    if (!RHMalignityField<RHMalignitySearchListSearch>(this, 0x1dc).m_count)
        return;
    RHMalignityFindList &search = RHMalignityField<RHMalignityFindList>(this, 0x1dc);
    search.FindForward(actor);
    short found = (short)search.m_searchIndex;
    if (found == -1)
        return;
    RHMalignityEraseList<false> &list = RHMalignityField<RHMalignityEraseList<false> >(this, 0x1dc);
    list.SeekErase(found);
    ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current));
    list.m_dirty = true;
}

// FUNCTION: GAME 0x00447030
void RHArtificialMalignity::FUN_00447030(void *guard)
{
    if (M(RHMalignityGuardCalls *, 0x348))
        M(RHMalignityGuardCalls *, 0x348)->FUN_0049fbb0(0);
    M(void *, 0x348) = guard;
    if (guard)
        ((RHMalignityGuardCalls *)guard)->FUN_0049fbb0(VirtualBase().m_actor);
}

inline bool RHMalignityActorCheck(void *actor)
{
    return RHMalignityField<char>(RHMalignityField<void *>(RHMalignityField<void *>(actor, 0x25c), 4), 0x17) &&
        RHMalignityField<unsigned short>(RHMalignityField<void *>(RHMalignityField<RHUnk005b5e00 *>(actor, 0x50)->Unk(), 4), 0x156) != 0xffff;
}

// FUNCTION: GAME 0x00447420
void RHArtificialMalignity::FUN_00447420(void *target)
{
    if (!RHMalignityField<char>(RHMalignityField<void *>(RHMalignityField<void *>(VirtualBase().m_actor, 0x25c), 4), 0x17))
        return;
    RHUnk005b5e00 *profile = RHMalignityField<RHUnk005b5e00 *>(VirtualBase().m_actor, 0x50);
    if (RHMalignityField<unsigned short>(RHMalignityField<void *>(profile->Unk(), 4), 0x156) == 0xffff)
        return;
    if (target == M(void *, 0x224))
        return;
    if (M(void *, 0x224))
        RHMalignityField<void *>(M(void *, 0x224), 0x910) = 0;
    M(void *, 0x224) = target;
    if (target)
    {
        void *owner = VirtualBase().m_actor;
        RHMalignityField<void *>(target, 0x910) = owner;
    }
}

// FUNCTION: GAME 0x00447490
void RHArtificialMalignity::FUN_00447490(void *target)
{
    if (!RHMalignityField<void *>(VirtualBase().m_actor, 0x258))
        return;
    if (target == M(void *, 0x228))
        return;
    if (M(void *, 0x228))
        RHMalignityField<void *>(M(void *, 0x228), 0x90c) = 0;
    M(void *, 0x228) = target;
    if (target)
        RHMalignityField<void *>(target, 0x90c) = VirtualBase().m_actor;
}

// Parked: own-actor virtual-base and nested profile checks use different scratch registers.
// STUB: GAME 0x004474e0
void *RHArtificialMalignity::FUN_004474e0()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    void *best = 0;
    unsigned short nearest = 500;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (!RHMalignityActorCheck(((RHArtificialMalignity *)((char *)actor + 0x6e8))->VirtualBase().m_actor))
            continue;
        if (!RHMalignityActorCheck(VirtualBase().m_actor) && RHMalignityField<void *>(actor, 0x90c))
            continue;
        int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
        if (state == 0xb7 || (state > 0xba && state <= 0xbc))
        {
            unsigned short distance = (unsigned short)VirtualBase().FUN_0041a0b0(actor);
            if (distance < nearest)
            {
                nearest = distance;
                best = actor;
            }
        }
    }
    return best;
}

class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;

#include "RHPathGeometryCalls.h"

#include "RHPositionInterfaceCore.h"

class RHMalignityDirection : public RHUnk005fc3b0
{
};

// FUNCTION: GAME 0x00447640
bool RHArtificialMalignity::FUN_00447640(RHMalignityPosition &target)
{
    RHMalignityDirection direction;
    if (!RHMalignityField<void *>(&VirtualBase(), 0x80))
        return false;
    RHMalignityPosition position;
    unsigned short heading;
    ((RHArtificialMalignity *)((char *)M(void *, 0x228) + 0x6e8))->FUN_00447da0(position, heading);
    direction.Unk005fcd40(heading, 0.57357645f);
    direction.FUN_005fc4d0(30.0f);
    target = FUN_0040ed40(position, direction);
    void *actor = VirtualBase().m_actor;
    RHPositionInterface *bounds = (RHPositionInterface *)((char *)RHMalignityField<void *>(actor, 0x50) + 4);
    void *radius = bounds->Unk0055fa10(bounds->m_88);
    return g_unk0x6c0a9c->Unk004f9170(VirtualBase().FUN_0040cbf0(position),
        VirtualBase().FUN_0040cbf0(target), target.layer, radius);
}

// FUNCTION: GAME 0x00447da0
void RHArtificialMalignity::FUN_00447da0(RHMalignityPosition &position, unsigned short &heading)
{
    switch (RHMalignityField<int>(&VirtualBase(), 0x14))
    {
    case 0xb7:
    case 0xbb:
        position = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
        heading = RHMalignityField<unsigned short>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0xd8);
        break;
    case 0xbc:
        position = RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0);
        heading = M(unsigned short, 0x22c);
        break;
    default:
        position = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
        heading = RHMalignityField<unsigned short>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0xd8);
        break;
    }
}


// Parked: self comparison and subsequent actor virtual-base loads use different scratch registers.
// STUB: GAME 0x00449170
unsigned short RHArtificialMalignity::FUN_00449170()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    int result = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (VirtualBase().FUN_0041a010(actor) < 250000.0f)
        {
            int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4a8);
            if (state >= 2 && state <= 4)
            {
                if (RHMalignityField<void *>(((RHArtificialMalignity *)((char *)actor + 0x6e8))->VirtualBase().m_actor, 0x258) &&
                    !RHMalignityField<void *>(actor, 0x910) && !RHMalignityField<bool>(actor, 0xa38))
                    ++result;
                else if (RHMalignityActorCheck(((RHArtificialMalignity *)((char *)actor + 0x6e8))->VirtualBase().m_actor) &&
                    !RHMalignityField<void *>(actor, 0x90c) && actor != VirtualBase().m_actor)
                {
                    int action = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
                    switch (action)
                    {
                    case 0xb7:
                    case 0xb8:
                    case 0xbb:
                    case 0xbc:
                        --result;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x00449810
bool RHArtificialMalignity::FUN_00449810(const RHMalignityPosition &position, unsigned short heading)
{
    unsigned short count = (unsigned short)m_targets.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityTargetList &list = m_targets;
        list.GoTo(index);
        RHElementActor *actor = *list.m_current;
        switch ((heading - ((RHUnk005fc3b0 *)&FUN_0040ec20(*(const RHMalignityPosition *)&VirtualBase().FUN_0040cc20(actor), position))->FUN_005fcc50(0.57357645f)) & 0xf)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 13:
        case 14:
        case 15:
            break;
        default:
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00449ac0
bool RHArtificialMalignity::FUN_00449ac0()
{
    RHArtificialMalignity *ai = this;
    while (!RHMalignityField<void *>(ai, 0x224))
    {
        void *next = RHMalignityField<void *>(ai, 0x340);
        if (!next)
            return false;
        ai = (RHArtificialMalignity *)((char *)next + 0x6e8);
    }
    return true;
}

// FUNCTION: GAME 0x00449af0
bool RHArtificialMalignity::FUN_00449af0(RHMalignityPosition position, int mode)
{
    RHFastFindPointerArray &gates = ((RHFastFindGrid *)g_unk0x6c0a9c)->m_gates;
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487aa0(0);
    float nearest = (unsigned)-1;
    RHUnk0051aa00 *selected = 0;
    unsigned short count = gates.size();
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    if (count > 0)
    {
        unsigned offset = 0;
        unsigned remaining = count;
        do
        {
            RHUnk0051aa00 *gate = *(RHUnk0051aa00 **)((char *)gates.m_first + *(volatile unsigned *)&offset);
            if (RHMalignityField<unsigned>(gate, 4) == 1)
            {
                unsigned short members = FUN_00449d40(gate);
                if (members >= 3 && gate->FUN_0051abe0(true, (RHElementActor *)VirtualBase().m_actor, false, false, false))
                {
                    float distance = gate->m_18.Unk005fc110(VirtualBase().FUN_0040cc20(VirtualBase().m_actor)).FUN_005fc700(1.0f);
                    if (gate->m_14 != RHMalignityField<unsigned short>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0xde))
                        distance += 1000.0f;
                    distance /= members;
                    if (distance < nearest)
                    {
                        nearest = distance;
                        selected = gate;
                    }
                }
            }
            offset += sizeof(void *);
        } while (--remaining);
        if (selected)
        {
            RHMalignityField<void *>(&VirtualBase(), 0x1d0) = selected;
            VirtualBase().V10(6, 0xe5);
            RHMalignityPosition destination = RHMalignityPositionOf(selected);
            ((RHArtificialIntelligence *)&VirtualBase())->Unk00412240((const RHUnk00571160Position &)destination, 1, 1.0f);
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00449d40
unsigned short RHArtificialMalignity::FUN_00449d40(void *group)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    if (RHMalignityField<int>(group, 0x88) != 1)
        return 0;
    void *members = RHMalignityField<void *>(group, 0x10);
    int result = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityList>(members, 0xf4).size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(members, 0xf4);
        list.FUN_005c8e40(index);
        RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)list.m_current->value;
        if ((actor->m_04 & 0x1f) == 0x14 && actor->V130() == team &&
            !RHMalignityField<void *>(RHMalignityField<void *>(actor, 0xa1c), 0x58) && actor->V120())
            ++result;
    }
    return result;
}

// FUNCTION: GAME 0x0044a730
RHMalignityStimulus::RHMalignityStimulus(unsigned value, const RHMalignityAlertPayload &payload)
{
    m_20 = value;
    RHMalignityField<RHMalignityAlertPayload>(this, 0) = payload;
    m_type = 4;
}

class RHUnk005c1d50
{
public:
    unsigned short FUN_005c1dd0(int index, void *actor);
};

// FUNCTION: GAME 0x00433010
unsigned short RHArtificialMalignity::FUN_00433010()
{
    unsigned short limit = 200 - RHMalignityField<unsigned short>(M(void *, 0x334), 0x34) * 2;
    void *actor = VirtualBase().m_actor;
    unsigned short value = (unsigned short)(RHMalignityField<RHSword *>(actor, 0x25c)->GetRange(1) + 10.0f);
    if (limit < value)
        return value;
    return limit;
}

// STUB: GAME 0x00440cf0
short RHArtificialMalignity::FUN_00440cf0(RHUnk00441dd0Record *record)
{
    RHUnk005fc3b0 direction;
    RHUnk005fc3b0 delta;
    if (record->m_2e == 0x1a0a)
    {
        short result = 0;
        if (record->m_14)
        {
            direction.Unk005fcd40((unsigned char)record->m_28, 1.0f);
            delta.FUN_005fc430(FUN_0040ec20(record->m_18, record->m_4));
            delta.m_y *= 1.7434468269348145f;
            float range = delta.Unk005fc6d0(1.0f);
            bool facing = direction.FUN_005fc660(delta) > 0.0f;
            RHHumanWeaponCalls *weapon = (RHHumanWeaponCalls *)RHMalignityField<void *>(record->m_0, 0x25c);
            unsigned ability = ((RHSword *)weapon)->GetRange(2);
            if ((float)(ability * ability) < range)
            {
                record->m_2e = 0;
                return 0;
            }
            int total = 0;
            for (int index = 0; index < 9; ++index)
            {
                unsigned short minimum = weapon->FUN_005c1e80(index);
                unsigned short maximum = weapon->FUN_005c1ea0(index);
                unsigned short low = minimum * minimum;
                unsigned short high = maximum * maximum;
                if ((float)low < range && range < (float)high)
                {
                    unsigned short damage = ((RHUnk005c1d50 *)weapon)->FUN_005c1dd0(index, record->m_0);
                    RHHumanWeaponCalls *actorWeapon =
                        (RHHumanWeaponCalls *)RHMalignityField<void *>(VirtualBase().m_actor, 0x25c);
                    unsigned value = actorWeapon->FUN_005c1d70(index);
                    RHHumanWeaponCalls *targetWeapon =
                        (RHHumanWeaponCalls *)RHMalignityField<void *>(record->m_14, 0x25c);
                    unsigned short chance = targetWeapon->FUN_005c1b70(record->m_14, record->m_0, value);
                    int first = (int)((float)(100 - chance) * damage * 0.01f);
                    total += first +
                             (int)((float)(100 - RHMalignityField<unsigned short>(
                                                    RHMalignityField<void *>(weapon, 4), 0x12)) *
                                       weapon->FUN_005c1db0(index) * 0.01f);
                }
            }
            total = (unsigned short)total / 9;
            if (facing)
            {
                int ownTeam = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
                int targetTeam = ((RHMalignityActorCalls *)record->m_0)->V130();
                if (targetTeam == ownTeam)
                {
                    if (((RHMalignityOwnerCalls *)this)->FUN_00438600() > 0x46)
                        total += 5000;
                }
                else if (((RHMalignityOwnerCalls *)this)->FUN_00438600() > 0x1e)
                    total += 3000;
            }
            result = (short)total;
        }
        record->m_2e = result;
    }
    return record->m_2e;
}

inline float RHMalignityActorHeight(void *actor)
{
    return RHMalignityField<float>(RHMalignityField<void *>(actor, 0x50), 0x18);
}

// FUNCTION: GAME 0x004334b0
bool RHArtificialMalignity::FUN_004334b0(void *actor)
{
    SBGeoVector2D delta;
    if (RHMalignityField<int>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0x8c) == 0x13)
        return true;
    delta = ((RHElement *)actor)->FUN_004237d0().Unk005fc110(((RHElement *)VirtualBase().m_actor)->FUN_004237d0());
    delta.m_y *= 1.7434468269348145f;
    float height = RHMalignityActorHeight(actor) - RHMalignityActorHeight(VirtualBase().m_actor);
    if (height >= 0.0f)
        return false;
    if (height < -50.0f)
        return true;
    return delta.Unk005fc6d0(1.0f) <= height * height;
}

// STUB: GAME 0x00433680
bool RHArtificialMalignity::FUN_00433680()
{
    void *destination = ((RHArtificialIntelligence *)&VirtualBase())->FUN_00417ed0(0, true);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00418c40(0x49, 0);
    if (!destination)
        return false;
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = RHMalignityField<void *volatile>(&VirtualBase(), 0x80) ?
        VirtualBase().FUN_004165e0(RHMalignityField<void *>(&VirtualBase(), 0x80), true) :
        FUN_004165e0(m_actor, true);
    VirtualBase().V10(6, 0xdf);
    ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fd0(3, 100);
    {
        RHUnk00571160Position position;
        position.y = RHMalignityField<float>(destination, 0x24);
        position.layer = RHMalignityField<unsigned short>(destination, 0x16);
        position.x = RHMalignityField<float>(destination, 0x20);
        position.area = RHMalignityField<void *>(destination, 0x10);
        RHUnk00571160Position next = position;
        ((RHArtificialIntelligence *)&VirtualBase())->Unk00412240(next, 1, 1.0f);
    }
    return true;
}

// FUNCTION: GAME 0x00433790
void RHArtificialMalignity::FUN_00433790(const RHMalignityPosition &position)
{
    RHMalignityReactionCalls *base = (RHMalignityReactionCalls *)((char *)this + (*(int **)this)[1]);
    void *actor = *(void **)((char *)base + 4);
    void *area = *(void **)((char *)*(void *volatile *)((char *)actor + 0x50) + 0xe0);
    if (RHMalignityBit(*(unsigned *)((char *)area + 0x30), 13) && area)
        return;
    if (*(int *)((char *)*(void **)((char *)actor + 0x50) + 0x8c) == 0x13)
        return;
    base->FUN_0041a3e0();
    VirtualBase().V10(1, 0x19);
    VirtualBase().SetMusicState(1, 2);
    VirtualBase().FUN_00412d60(position, -1, 0);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(10);
}

// STUB: GAME 0x00434320
void RHArtificialMalignity::FUN_00434320(void *actor)
{
    RHArtificialIntelligence &base = VirtualBase();
    bool wasAttacking = RHMalignityField<int>(&base, 0xc) == 3 &&
        RHMalignityField<int>(&base, 0x27c) == 3 &&
        RHMalignityField<void *>(&base, 0x2a4) == actor;
    RHMalignityField<RHMalignityList>(&base, 0x280).InsertLast(actor);
    RHMalignityPosition position = base.FUN_004165e0(actor, true);
    if (RHMalignityField<int>(&base, 0x27c) <= 2)
    {
        RHMalignityField<RHMalignityPosition>(&base, 0x26c) = position;
        RHMalignityField<int>(&base, 0x27c) = 2;
    }
    if (((RHMalignityActorCalls *)actor)->V48() &&
        (RHMalignityField<unsigned>(actor, 4) & 0xf) == 4)
    {
        RHSectorActorList &list = M(RHSectorActorList, 0x2c);
        if (list.Unk004b8f80((RHElementActor *const &)actor, true) == -1)
        {
            RHElementActor *value = (RHElementActor *)actor;
            ((RHMalignityTargetList *)&list)->InsertLast(value);
        }
    }
    if (!FUN_00438cb0(15, false))
        return;
    M(unsigned short, 0x10) = M(unsigned short, 0x14);
    if (RHMalignityField<void *>(&base, 0x1f8))
    {
        RHSectorActorList &list = RHMalignityField<RHSectorActorList>(&base, 0x1d4);
        void *pending = RHMalignityField<void *>(&base, 0x1f8);
        if (list.Unk004b8f80((RHElementActor *const &)pending, true) == -1)
        {
            RHElementActor *value = (RHElementActor *)pending;
            ((RHMalignityTargetList *)&list)->InsertLast(value);
        }
        RHMalignityField<void *>(&base, 0x1f8) = 0;
    }
    switch (RHMalignityField<int>(&base, 0x14))
    {
    case 0x49:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x80:
        if (wasAttacking)
            FUN_004450a0(actor);
        FUN_0044a760(actor);
        return;
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x71:
    case 0x72:
        if (actor != RHMalignityField<void *>(&base, 0x88))
        {
            RHMalignityList &list = M(RHMalignityList, 0x54);
            list.InsertLast(actor);
        }
        return;
    default:
        ((RHArtificialIntelligence *)&base)->Unk00418c40(
            RHMalignityField<unsigned short>(actor, 0x23c) ? 0x1b : 0, 0);
        FUN_00439cb0(base.FUN_004165e0(actor, true), 100);
        M(unsigned char, 0xcc) = 0;
        ((RHMalignityReactionCalls *)&base)->FUN_0041a3e0();
        RHMalignityField<RHMalignityPosition>(&base, 0xd0) = base.FUN_004165e0(actor, true);
        RHMalignityField<void *>(&base, 0x88) = actor;
        ((RHElementActorNPC *)base.m_actor)->FUN_00487aa0(actor);
        base.V10(3, 0x6d);
        base.FUN_00412d60(
            RHMalignityField<RHMalignityPosition>(&base, 0xd0), -1, 0);
        base.SetReactionState(2);
        if (wasAttacking)
            FUN_004450a0(actor);
        FUN_00438620(50);
        return;
    }
}

// FUNCTION: GAME 0x00434710
void RHArtificialMalignity::FUN_00434710(void *actor)
{
    switch (RHMalignityField<int>(actor, 0xb0))
    {
    case 7:
    case 8:
        switch (RHMalignityField<int>(&VirtualBase(), 0x14))
        {
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x41:
        case 0xf1:
        case 0xf2:
        {
            RHMalignityList &list = M(RHMalignityList, 0x194);
            RHMalignityNode *head = list.m_head;
            RHMalignityNode *previous = head->previous;
            RHMalignityNode *node = (RHMalignityNode *)::operator new(sizeof(RHMalignityNode));
            node->next = head ? head : node;
            node->previous = previous ? previous : node;
            head->previous = node;
            node->previous->next = node;
            RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&actor);
            ++list.m_count;
            list.m_dirty = true;
            return;
        }
        default:
            ((RHMalignityReactionCalls *)&VirtualBase())->FUN_0041a3e0();
            VirtualBase().Unk00418c40(0x21, 0);
            RHMalignityField<void *>(&VirtualBase(), 0x8c) = actor;
            ((RHArtificialIntelligence *)((char *)this + ((int *)*(void **)this)[1]))->FUN_00412d60(VirtualBase().FUN_004165e0(actor, true), (short)RHMalignityActorHeight(actor), 0);
            VirtualBase().SetReactionState(2);
            VirtualBase().V10(2, 0x29);
            ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487aa0(RHMalignityField<void *>(&VirtualBase(), 0x8c));
            if (RHMalignityField<int>(M(void *, 0x334), 0x58) == 1)
                VirtualBase().Unk00416710(60);
            else
                VirtualBase().Unk00416710(30);
            return;
        }
    case 3:
        if (RHMalignityField<int>(&VirtualBase(), 0x14) >= 0x35 && RHMalignityField<int>(&VirtualBase(), 0x14) <= 0x38)
        {
            RHMalignityList &list = M(RHMalignityList, 0x1b8);
            RHMalignityNode *head = list.m_head;
            RHMalignityNode *previous = head->previous;
            RHMalignityNode *node = (RHMalignityNode *)::operator new(sizeof(RHMalignityNode));
            node->next = head ? head : node;
            node->previous = previous ? previous : node;
            head->previous = node;
            node->previous->next = node;
            void **destination = &node->value;
            if (destination)
                new (destination) void *(actor);
            ++list.m_count;
            list.m_dirty = true;
            return;
        }
        VirtualBase().Unk00410600();
        VirtualBase().Unk00418c40(0x21, 0);
        ((RHArtificialIntelligence *)((char *)this + ((int *)*(void **)this)[1]))->FUN_00412d60(VirtualBase().FUN_004165e0(actor, true), (short)RHMalignityActorHeight(actor), 0);
        VirtualBase().SetReactionState(2);
        RHMalignityField<void *>(&VirtualBase(), 0x8c) = actor;
        ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487aa0(RHMalignityField<void *>(&VirtualBase(), 0x8c));
        VirtualBase().V10(2, 0x35);
        FUN_00438620(60);
        return;
    }
}

// Residual: the state comparison and virtual-base receiver reload across rand differ.
// STUB: GAME 0x00435bd0
bool RHArtificialMalignity::FUN_00435bd0()
{
    char *base = (char *)this + (*(int **)((char *)this - 0x358))[1];
    if (*(int *)(base - 0x344) == 0xb)
    {
        void *order = *(void **)((char *)*(void **)(base - 0x354) + 0x134);
        if (!(order && RHMalignityField<int>(order, 0x24) == 1) &&
            !*(bool *)(base - 0x1e9) && !*(bool *)(base - 0x1e8))
        {
            ((RHArtificialIntelligence *)(base - 0x358))->V10(1, 0xc);
            ((RHMalignityReactionCalls *)&Base())->FUN_0041a3e0();
            Base().V04(rand() & 3);
            return true;
        }
    }
    return false;
}

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

// FUNCTION: GAME 0x00436400
int RHArtificialMalignity::FUN_00436400(SBFile &file)
{
    file.Access((char *)this - 0x7c, 4);
    unsigned count = RHMalignityField<std::vector<void *> >(RHUnk00436500GetProfileManager(), 0x20).size();
    unsigned index = *(unsigned *)((char *)this - 0x7c);
    if (index < count)
        *(void **)((char *)this - 0x24) = RHMalignityField<std::vector<void *> >(RHUnk00436500GetProfileManager(), 0x20)[index];
    else
        *(void **)((char *)this - 0x24) = RHMalignityField<std::vector<void *> >(RHUnk00436500GetProfileManager(), 0x20)[0];
    short unused;
    file.Access(&unused, 2);
    unsigned char mode;
    file.Access(&mode, 1);
    mode &= 0x7f;
    switch (mode)
    {
    case 3:
        RHMalignityField<int>(&Base(), 0x20) = 4;
        break;
    case 2:
        RHMalignityField<int>(&Base(), 0x20) = 2;
        break;
    case 1:
        RHMalignityField<int>(&Base(), 0x20) = 1;
        break;
    }
    file.Access((char *)&Base() + 0x24, 1);
    return 8;
}

// FUNCTION: GAME 0x0044a090
bool RHArtificialMalignity::FUN_0044a090()
{
    if (RHMalignityField<unsigned short>(M(void *, 0x334), 0x38) == 0)
        return false;
    if (RHMalignityField<unsigned char>(&VirtualBase(), 0x24) > 0)
        return false;
    void *target = FUN_0043d780(2);
    RHMalignityField<void *>(&VirtualBase(), 0x80) = target;
    if (!RHMalignityField<void *>(&VirtualBase(), 0x80))
        return false;
    float distance = VirtualBase().FUN_0041a0b0(RHMalignityField<void *>(&VirtualBase(), 0x80));
    if (!RHMalignityField<void *>(RHMalignityField<void *>(&VirtualBase(), 0x80), 0x268) &&
        !(RHMalignityField<RHSword *>(VirtualBase().m_actor, 0x25c)->GetRange(2) < distance))
        return false;
    switch (RHMalignityField<int>(&VirtualBase(), 0x14))
    {
    case 0x99:
    case 0xbe:
        return true;
    }
    if (RHMalignityField<void *>(RHMalignityField<void *>(&VirtualBase(), 0x80), 0x268))
        return true;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityList>(&VirtualBase(), 0x100).size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(&VirtualBase(), 0x100);
        list.FUN_005c8e40(index);
        RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)list.m_current->value;
        if ((void *)actor == VirtualBase().m_actor)
            continue;
        if ((actor->m_04 & 0x1f) != 0x14)
            continue;
        if (!((RHMalignityActorCalls *)actor)->V11c())
            continue;
        if (RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0xa1c), 0x38) >= RHMalignityField<unsigned short>(M(void *, 0x334), 0x38))
            continue;
        switch (RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0))
        {
        case 0x9b:
        case 0x9c:
        case 0x9d:
        case 0xa0:
        case 0xa1:
        case 0xa2:
        case 0xac:
        case 0xad:
        case 0xec:
            if (RHMalignityField<void *>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x51c) == RHMalignityField<void *>(&VirtualBase(), 0x80))
                return true;
            break;
        case 0xa6:
        case 0xa7:
        case 0xa8:
            if (((RHMalignityActorCalls *)actor)->FUN_0048a350(RHMalignityField<void *>(&VirtualBase(), 0x80)))
                return true;
            break;
        }
    }
    return false;
}

// FUNCTION: GAME 0x0044a760
void RHArtificialMalignity::FUN_0044a760(void *actor)
{
    if (RHMalignityField<unsigned short>(actor, 0x23c) != 0)
    {
        FUN_0044a830(actor);
        return;
    }
    RHMalignityField<void *>(&VirtualBase(), 0x88) = actor;
    ((RHMalignityDataView *)this)->m_d0 = VirtualBase().FUN_004165e0(actor, true);
    VirtualBase().SetReactionState(3);
    VirtualBase().V10(3, 0x6e);
    ((RHElementActorNPC *)VirtualBase().m_actor)->FUN_00487aa0(actor);
    VirtualBase().FUN_00412cf0(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), 0x1e, 1);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(10);
}

// FUNCTION: GAME 0x0044afa0
bool RHArtificialMalignity::FUN_0044afa0(void *target)
{
    RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)target;
    if (((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf8() &&
        ((actor->m_04 & 0xf) == 4 || !actor->V168()))
        return false;
    if ((actor->m_04 & 0xf) == 4 && actor->V0f8())
        return false;
    return true;
}



// FUNCTION: GAME 0x0044b000
void RHArtificialMalignity::FUN_0044b000()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    if (RHMalignityField<int>(M(void *, 0x334), 0x58) != 0)
        return;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    void *actor;
    unsigned short index = 0;
    if (index >= count)
        return;
    for (;;)
    {
        actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) == 1)
        {
            char *base = (char *)actor + RHMalignityField<int *>(actor, 0x49c)[1];
            if (RHMalignityField<int>(base, 0x4a8) == 1 || RHMalignityField<int>(base, 0x4b0) == 0x29)
            {
                float distance = VirtualBase().FUN_0041a010(actor);
                if (distance < 40000.0f ||
                    (distance < 122500.0f ? ((RHMalignityActorCalls *)actor)->FUN_0048a350(VirtualBase().m_actor)
                                                : ((RHScriptBatchCalls *)actor)->Unk00489e80(VirtualBase().m_actor)))
                    break;
            }
        }
        if (++index >= count)
            return;
    }
    ((RHMalignityAlertCalls *)((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1] + 0x49c))->FUN_0042c890(0x21, VirtualBase().m_actor);
}


// FUNCTION: GAME 0x0044b120
bool RHArtificialMalignity::FUN_0044b120(const RHMalignityPosition &position)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void **actors = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.m_first;
        void *actor = actors[index];
        int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
        if (state >= 0x3e && state <= 0x40)
        {
            if (FUN_0040ec20(VirtualBase().FUN_004165e0(actor, true), position).FUN_005fc700(1.0f) < 150.0f)
                return true;
        }
    }
    return false;
}

#include "RHSectorArchery.h"
#include "RHArcheryPoint.h"

DECOMP_SIZE_ASSERT(RHSectorArchery, 0x84)
DECOMP_SIZE_ASSERT(RHUnk00522540, 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHSectorArchery, m_58) == 0x58)
DECOMP_STATIC_ASSERT(offsetof(RHSectorArchery, m_7c) == 0x7c)
DECOMP_STATIC_ASSERT(offsetof(RHSectorArchery, m_7e) == 0x7e)
DECOMP_STATIC_ASSERT(offsetof(RHSectorArchery, m_80) == 0x80)
DECOMP_STATIC_ASSERT(offsetof(RHSectorArchery, m_82) == 0x82)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00522540, m_c) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00522540, m_10) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00522540, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00522540, m_18) == 0x18)

// STUB: GAME 0x0044b4e0
bool RHArtificialMalignity::FUN_0044b4e0(const RHUnk00571160Position &position)
{
    bool found = false;
    FUN_0044b810(0);
    unsigned short count = (unsigned short)marrayArcherySectors.size();
    unsigned short sectorIndex = 0;
    RHSectorArchery *sector;
    while (sectorIndex < count && !found)
    {
        sector = marrayArcherySectors[sectorIndex];
        if (sector->m_82 < sector->m_80 && sector->IsInside(position))
            found = true;
        ++sectorIndex;
    }
    --sectorIndex;
    if (!found)
        return false;
    unsigned nearest = 0xffffffff;
    unsigned nearestAvailable = 0xffffffff;
    RHUnk00522540 *selected = 0;
    unsigned short nearestIndex;
    unsigned short availableIndex;
    RHMalignityPosition origin;
    origin = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    unsigned short pointCount = (unsigned short)sector->m_58.size();
    unsigned short index = 0;
    if (pointCount > 0)
    {
        do
        {
            RHUnk00522540 *point = sector->m_58[index];
            RHMalignityPosition target;
            target.x = point->m_x;
            target.y = point->m_y;
            target.layer = point->m_c;
            target.area = point->m_10;
            if (FUN_00445510(target, RHMalignityField<void *>(&VirtualBase(), 0x80)))
                return false;
            RHMalignityPosition destination;
            destination.x = point->m_x;
            destination.y = point->m_y;
            destination.layer = point->m_c;
            destination.area = point->m_10;
            unsigned distance = (unsigned)FUN_0040ec20(origin, destination).Unk005fc6d0(1.0f);
            if (origin.area != point->m_10)
                distance += 10000;
            if (!point->m_14)
            {
                if (nearest > distance)
                {
                    nearest = distance;
                    nearestIndex = index;
                }
            }
            if (point->m_14 && !point->m_18 && nearestAvailable > distance)
            {
                nearestAvailable = distance;
                selected = point;
                availableIndex = index;
            }
            ++index;
        } while (index < pointCount);
    }
    if (!selected)
        return false;
    M(unsigned short, 0x280) = sectorIndex;
    if (nearestIndex < sector->m_7c)
    {
        M(unsigned short, 0x282) = nearestIndex;
        M(char, 0x284) = 1;
    }
    else if (nearestIndex > sector->m_7e)
    {
        M(unsigned short, 0x282) = nearestIndex;
        M(char, 0x284) = -1;
    }
    else
    {
        if (nearestIndex < availableIndex)
        {
            M(char, 0x284) = 1;
            M(unsigned short, 0x282) = availableIndex - 1;
        }
        else
        {
            M(char, 0x284) = -1;
            M(unsigned short, 0x282) = availableIndex + 1;
        }
        FUN_0044b810(selected);
    }
    FUN_0044b840(sector);
    return true;
}

// FUNCTION: GAME 0x0044b7b0
void *RHArtificialMalignity::FUN_0044b7b0()
{
    void *path = g_unk0x006c06d0[M(unsigned short, 0x280)];
    if (M(unsigned short, 0x282) < (unsigned short)RHMalignityField<RHArtificialIntelligenceStaticArray>(path, 0x58).size())
        return RHMalignityField<void **>(path, 0x5c)[M(unsigned short, 0x282)];
    return 0;
}

// FUNCTION: GAME 0x0044b800
void RHArtificialMalignity::FUN_0044b800()
{
    M(unsigned short, 0x282) += M(char, 0x284);
}

// FUNCTION: GAME 0x0044b810
void RHArtificialMalignity::FUN_0044b810(void *point)
{
    if (M(void *, 0x278))
        RHMalignityField<void *>(M(void *, 0x278), 0x18) = 0;
    M(void *, 0x278) = point;
    if (point)
        RHMalignityField<void *>(point, 0x18) = VirtualBase().m_actor;
}

// FUNCTION: GAME 0x0044b840
void RHArtificialMalignity::FUN_0044b840(void *point)
{
    if (M(void *, 0x27c))
        --RHMalignityField<unsigned short>(M(void *, 0x27c), 0x82);
    M(void *, 0x27c) = point;
    if (point)
        ++RHMalignityField<unsigned short>(point, 0x82);
}

// FUNCTION: GAME 0x0044b870
bool RHArtificialMalignity::FUN_0044b870(void *area, unsigned short id)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors[index];
        if ((void *)actor != VirtualBase().m_actor &&
            RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xde) == id &&
            !actor->V048() && !RHMalignityField<bool>(actor, 0x1ce) &&
            ((RHUnk0060bd40 *)area)->FUN_0060be00(*(const SBGeoPoint2D *)((char *)RHMalignityField<void *>(actor, 0x50) + 0x24)))
            return true;
    }
    return false;
}

#include "RHPathGeometryCalls.h"

// FUNCTION: GAME 0x0044c850
bool RHArtificialMalignity::FUN_0044c850(RHMalignityPosition &position)
{
    RHUnk005fc3b0 direction;
    RHMalignityPosition origin;
    origin = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    direction.FUN_005fc430(((RHElementActor *)VirtualBase().m_actor)->FUN_004135b0());
    float length = 500.0f;
    unsigned short heading = RHMalignityField<unsigned short>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0xd8);
    while (length > 10.0f)
    {
        short offset = 0;
        do
        {
            int step = offset;
            direction.Unk005fcd40((heading + step) % 15, 0.57357645f);
            direction.FUN_005fc4d0(length);
            position = FUN_0040ece0(origin, direction);
            void *actor = VirtualBase().m_actor;
            RHPositionInterface *bounds = (RHPositionInterface *)((char *)RHMalignityField<void *>(actor, 0x50) + 4);
            void *radius = bounds->Unk0055fa10(bounds->m_88);
            if (g_unk0x6c0a9c->Unk004f9170(
                    FUN_0040cbf0(origin), FUN_0040cbf0(position), origin.layer,
                    radius))
                goto found;
            if (offset > 0)
                offset = -step;
            else
                offset = 1 - step;
        } while (offset < 2);
        length -= 10.0f;
    }
    return false;
found:
    return true;
}

// FUNCTION: GAME 0x00445210
bool RHArtificialMalignity::FUN_00445210(RHMalignityPosition position, unsigned short maxDistance,
    unsigned short minDistance, RHMalignityPosition *out, float scale)
{
    RHUnk005fc3b0 direction;
    RHMalignityPosition origin;
    origin = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    direction.FUN_005fc430(FUN_0040ec20(origin, position));
    float distance = direction.Unk005fc6a0(scale);
    unsigned short heading = direction.FUN_005fcc50(scale);
    if (distance >= maxDistance)
    {
        *out = origin;
        return true;
    }
    float limit = __max(10.0f, minDistance - distance);
    float step = maxDistance - distance;
    if (step > limit)
    {
        do
        {
            short offset = 0;
            do
            {
                int value = offset;
                direction.Unk005fcd40((heading + value) % 15, scale);
                direction.FUN_005fc4d0(step);
                *out = FUN_0040ece0(origin, direction);
                void *actor = VirtualBase().m_actor;
                RHPositionInterface *bounds =
                    (RHPositionInterface *)((char *)RHMalignityField<void *>(actor, 0x50) + 4);
                void *radius = bounds->Unk0055fa10(bounds->m_88);
                if (g_unk0x6c0a9c->Unk004f9170(
                        FUN_0040cbf0(origin), FUN_0040cbf0(*out), origin.layer, radius))
                    goto found;
                if (offset > 0)
                    offset = -value;
                else
                    offset = 1 - value;
            } while (offset < 4);
            step -= 10.0f;
        } while (step > limit);
    }
    return false;
found:
    return true;
}

// FUNCTION: GAME 0x0044ca90
void RHArtificialMalignity::FUN_0044ca90()
{
    FUN_00430020();
    if (!m_targets.size())
    {
        VirtualBase().V10(4, 0xcf);
        ((RHArtificialIntelligence *)&VirtualBase())->Unk00412240(RHMalignityField<RHUnk00571160Position>(&VirtualBase(), 0xd0), 1, 1.0f);
    }
    else
        FUN_004303e0();
}

// FUNCTION: GAME 0x0044cae0
void RHUnk0044cae0::Switch()
{
    RHArtificialMalignity *ai = (RHArtificialMalignity *)this;
    if (RHMalignityField<unsigned short>(&ai->VirtualBase(), 0xa) != 0xffff)
    {
        RHMalignityField<bool>(ai, 0x22f) = true;
        void *actor = ai->VirtualBase().m_actor;
        RHMalignityField<RHPath>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4cc)
            .Unk00550f60(RHMalignityField<unsigned short>(&ai->VirtualBase(), 0xa));
        RHMalignityField<bool>(&ai->VirtualBase(), 0x70) = true;
    }
    if (RHMalignityField<int>(&ai->VirtualBase(), 0xc) == 1)
        ai->VirtualBase().V00(0);
}


// Parked: front-removal iterator temporaries and conditional callee saves differ.
// STUB: GAME 0x0044cf00
bool RHArtificialMalignity::FUN_0044cf00()
{
    while (M(RHMalignityList, 0x54).m_count > 0)
    {
        RHMalignityList &list = M(RHMalignityList, 0x54);
        list.FUN_005c8e40(0);
        if (static_cast<RHElementActorHuman *>(list.m_current->value)->FUN_004860b0())
            break;
        RHSectorActorIter position((RHSectorActorNode *)list.m_head->next);
        RHMalignityNode *removed = (RHMalignityNode *)(position++).m_p;
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        operator delete(removed);
        --list.m_count;
        list.m_dirty = true;
    }
    if (M(RHMalignityList, 0x54).m_count == 0)
        return false;
    RHMalignityList &list = M(RHMalignityList, 0x54);
    list.FUN_005c8e40(0);
    RHMalignityField<void *>(&VirtualBase(), 0x88) = list.m_current->value;
    list.Seek(0);
    RHMalignityNode *removed = list.m_current;
    removed->previous->next = removed->next;
    removed->next->previous = removed->previous;
    operator delete(removed);
    --list.m_count;
    list.m_dirty = true;
    FUN_0044a760(RHMalignityField<void *>(&VirtualBase(), 0x88));
    return true;
}

class RHMalignityStateCalls
{
public:
    virtual void V00(int mode) = 0;
    virtual void V04(int mode) = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, int substate) = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c(int mode) = 0;
};

// Parked: switch case ordering and virtual-call argument scratch registers differ.
// STUB: GAME 0x0044d0b0
void RHArtificialMalignity::FUN_0044d0b0()
{
    if (((RHElementActor *)VirtualBase().m_actor)->FUN_0046d710())
    {
        ((RHMalignityStateCalls *)&VirtualBase())->V3c(2);
        RHMalignityField<bool>(&VirtualBase(), 0x175) = true;
        VirtualBase().DispatchWorldEvent(4);
        return;
    }
    switch (RHMalignityField<int>(&VirtualBase(), 0xc))
    {
    case 0:
        ((RHMalignityStateCalls *)&VirtualBase())->V00(2);
        return;
    case 1:
        ((RHMalignityStateCalls *)&VirtualBase())->V00(2);
        return;
    case 2:
        ((RHMalignityStateCalls *)&VirtualBase())->V00(2);
        return;
    case 5:
        ((RHMalignityStateCalls *)&VirtualBase())->V00(2);
        return;
    case 3:
    {
        void *actor = VirtualBase().m_actor;
        ((RHScriptAIStateCalls *)this)->FUN_0043a220(VirtualBase().FUN_004165e0(actor, true), 0x12c, 0, 0x29a);
        return;
    }
    case 4:
        if (RHMalignityField<void *>(VirtualBase().m_actor, 0x268))
        {
            VirtualBase().V10(4, 0xa0);
            ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(0x14);
        }
        else
            FUN_00430300(0);
        return;
    case 6:
        VirtualBase().V00(2);
        break;
    }
}

// STUB: GAME 0x0044d1d0
bool RHArtificialMalignity::FUN_0044d1d0()
{
    void **first = RHMalignityField<void **>(g_unk0x6c0a9c, 0x4104);
    unsigned count;
    if (!first)
        count = 0;
    else
        count = RHMalignityField<void **>(g_unk0x6c0a9c, 0x4108) - first;
    float nearest = 4294967296.0f;
    RHMalignityPosition origin;
    origin = VirtualBase().FUN_004165e0(VirtualBase().m_actor, true);
    RHMalignityField<void *>(&VirtualBase(), 0x1d0) = 0;
    if ((unsigned short)count > 0)
    {
        unsigned offset = 0;
        unsigned remaining = (unsigned short)count;
        do
        {
            void *point = *(void **)((char *)RHMalignityField<void **>(g_unk0x6c0a9c, 0x4104) + offset);
            RHMalignityPosition position;
            position.y = RHMalignityField<float>(point, 0x24);
            position.x = RHMalignityField<float>(point, 0x20);
            position.layer = RHMalignityField<unsigned short>(point, 0x16);
            position.area = RHMalignityField<void *>(point, 0x10);
            float distance = FUN_0040ec20(origin, position).FUN_005fc700(1.0f);
            if (distance < nearest)
            {
                nearest = distance;
                RHMalignityField<void *>(&VirtualBase(), 0x1d0) = point;
            }
            offset += 4;
            --remaining;
        } while (remaining);
    }
    if (!RHMalignityField<void *>(&VirtualBase(), 0x1d0))
        return false;
    VirtualBase().V10(6, 0xe8);
    void *point = RHMalignityField<void *>(&VirtualBase(), 0x1d0);
    RHUnk00571160Position position;
    position.x = RHMalignityField<float>(point, 0x20);
    position.y = RHMalignityField<float>(point, 0x24);
    position.layer = RHMalignityField<unsigned short>(point, 0x16);
    position.area = RHMalignityField<void *>(point, 0x10);
    RHUnk00571160Position destination = position;
    VirtualBase().Unk00412240(destination, 1, 1.0f);
    VirtualBase().Unk00416710(30);
    if (RHMalignityField<char>(&VirtualBase(), 0x16c))
    {
        RHMalignityField<char>(&VirtualBase(), 0x16c) = 0;
        return false;
    }
    return true;
}

namespace VMCoreCustomDependencies
{
    int FUN_0057b150();
}

// FUNCTION: GAME 0x0044d9c0
void RHArtificialMalignity::FUN_0044d9c0()
{
    if (RHMalignityField<char>(RHMalignityField<void *>(RHMalignityField<void *>(VirtualBase().m_actor, 0x25c), 4), 0x17))
    {
        RHUnk005b5e00 *profile = RHMalignityField<RHUnk005b5e00 *>(VirtualBase().m_actor, 0x50);
        if (RHMalignityField<unsigned short>(RHMalignityField<void *>(profile->Unk(), 4), 0x156) != 0xffff)
        {
            ((RHArtificialIntelligence *)&VirtualBase())->Unk00418c40(0x4a, 8);
            return;
        }
    }
    if (RHMalignityField<int>(&VirtualBase(), 0x258) == 0x79)
    {
        int roll = rand() % 3;
        if (!roll)
            ((RHArtificialIntelligence *)&VirtualBase())->Unk00418c40(0x4a, roll);
    }
}

// FUNCTION: GAME 0x0044da40
void RHArtificialMalignity::FUN_0044da40()
{
    if (!M(volatile unsigned char, 0x351))
    {
        switch (RHMalignityField<int>(&VirtualBase(), 0x14))
        {
        case 0xa6:
        case 0xa7:
            if (*g_unk0x006c08a4 - M(unsigned, 0x2a8) >= 100)
                break;
        case 0x98:
        case 0x99:
        {
            SBGeoVector2D radius(50.0f, 30.0f);
            SBGeoPoint2D center(RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0x24));
            SBGeoBoundingBox2D box(center.FUN_005fc200(radius), center.Unk005fc190(radius));
            unsigned count = m_targets.size();
            if ((unsigned short)count > 0)
            {
                unsigned index = 0;
                RHMalignityTargetList &list = m_targets;
                unsigned remaining = (unsigned short)count;
                do
                {
                    list.GoTo(index);
                    if (box.FUN_00608400(RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(*list.m_current, 0x50), 0x24)))
                    {
                        list.GoTo(index);
                        RHElementActor *actor = *list.m_current;
                        switch (RHMalignityField<int>(RHMalignityField<void *>(actor, 0x50), 0x8c))
                        {
                        case 1:
                        case 10:
                        case 11:
                        case 14:
                        case 15:
                        {
                            VirtualBase().DispatchActorEvent(actor, 0x43);
                            break;
                        }
                        }
                    }
                    ++index;
                    --remaining;
                } while (remaining);
            }
            break;
        }
        }
    }
}

// FUNCTION: GAME 0x0044d6c0
unsigned short RHArtificialMalignity::FUN_0044d6c0()
{
    switch (VMCoreCustomDependencies::FUN_0057b150())
    {
    case 0:
        return 13 - ((RHMalignityActorCalls *)VirtualBase().m_actor)->V124() / 10;
    case 1:
        return 10 - ((RHMalignityActorCalls *)VirtualBase().m_actor)->V124() / 10;
    case 2:
        return 0;
    }
    return 1;
}

// STUB: GAME 0x0044dc80
bool RHArtificialMalignity::FUN_0044dc80(void *actor)
{
    void *guard = RHMalignityField<void *>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x52c);
    void *target = RHMalignityField<void *>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x74c);
    if (target && target != VirtualBase().m_actor)
    {
        if (((RHUnk005fc3b0 &)RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(actor, 0x50), 0x24)
            .Unk005fc110(RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(target, 0x50), 0x24))).FUN_005fc700(1.0f) < 700.0f)
            return false;
    }
    if (guard && guard != VirtualBase().m_actor)
        return false;
    return true;
}

DECOMP_SIZE_ASSERT(RHMalignityPosition, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00441dd0Record, 0x40)
DECOMP_SIZE_ASSERT(RHMalignityStimulus, 0x2c)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityStimulus, m_actor) == 0)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityStimulus, m_type) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityStimulus, m_20) == 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityStimulus, m_24) == 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHMalignityStimulus, m_28) == 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialIntelligence, m_actor) == 4)
DECOMP_SIZE_ASSERT(SBListAutoDelete<RHMalignityPosition *>, 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialMalignity, m_150) == 0x150)
DECOMP_STATIC_ASSERT(offsetof(RHArtificialMalignity, m_targets) == 0x2e4)

template class SBListAutoDelete<RHMalignityPosition *>;
template class SBListAutoDelete<RHUnk00441dd0Record *>;

// TEMPLATE: GAME 0x0044e500
// ??1?$SBListAutoDelete@PAURHMalignityPosition@@@@QAE@XZ

// TEMPLATE: GAME 0x0044e690
// ??1?$SBListAutoDelete@PAURHUnk00441dd0Record@@@@QAE@XZ

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAURHMalignityPosition@@V?$allocator@PAURHMalignityPosition@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAURHUnk00441dd0Record@@V?$allocator@PAURHUnk00441dd0Record@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@PAURHMalignityPosition@@V?$allocator@PAURHMalignityPosition@@@std@@@std@@QAE?AV012@H@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@PAURHUnk00441dd0Record@@V?$allocator@PAURHUnk00441dd0Record@@@std@@@std@@QAE?AV012@H@Z

// TEMPLATE: GAME 0x004e52a0 FOLDED
// ??1?$list@PAURHMalignityPosition@@V?$allocator@PAURHMalignityPosition@@@std@@@std@@QAE@XZ

// TEMPLATE: GAME 0x004e52a0 FOLDED
// ??1?$list@PAURHUnk00441dd0Record@@V?$allocator@PAURHUnk00441dd0Record@@@std@@@std@@QAE@XZ

// STUB: GAME 0x0048a130
bool RHMalignityActorCalls::FUN_0048a130(void *actor)
{
    RHUnk00613e90 difference;
    RHUnk00613e90 origin;
    RHUnk00613e90 target;
    {
        if (!RHMalignityField<bool>(this, 0x12))
            goto rejected;
        void *area = RHMalignityField<void *>(RHMalignityField<void *>(this, 0x50), 0xe0);
        if (area && RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 13))
            goto rejected;
        if (!RHMalignityField<bool>(actor, 0x12))
            goto rejected;
        area = RHMalignityField<void *>(RHMalignityField<void *>(actor, 0x50), 0xe0);
        if (area && RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 13))
            goto rejected;
        ((RHElementActor *)this)->FUN_00478c20(origin, 1);
        ((RHMalignityActorCalls *)actor)->V30(target);
        difference = target.FUN_005df550(origin);
        float scaled = difference.y;
        scaled *= 1.7434468269348145f;
        difference.y = scaled;
        float z = difference.z;
        int range = RHMalignityField<unsigned short>(this, 0x6cc);
        if (z * z + scaled * scaled + difference.x * difference.x > range * range)
            goto rejected;
        return ((RHMalignityGeometryCalls *)RHMalignityField<void *>(this, 0x64))->FUN_004eff80(origin, target, 2);
    }
rejected:
    return false;
}

// Parked: x87 retains both y and z in the target; source retains only scaled y.
// STUB: GAME 0x0048a260
bool RHMalignityActorCalls::FUN_0048a260(const RHUnk00613e90 &point)
{
    RHUnk00613e90 difference;
    RHUnk00613e90 origin;
    RHUnk00613e90 unused;
    void *area = RHMalignityField<void *>(RHMalignityField<void *>(this, 0x50), 0xe0);
    if (RHMalignityBit(RHMalignityField<unsigned>(area, 0x30), 13))
        return false;
    ((RHElementActor *)this)->FUN_00478c20(origin, 0);
    difference = point.FUN_005df550(origin);
    float scaled = difference.y;
    scaled *= 1.7434468269348145f;
    difference.y = scaled;
    float z = difference.z;
    int range = RHMalignityField<unsigned short>(this, 0x6cc);
    if (z * z + scaled * scaled + difference.x * difference.x > range * range)
        return false;
    return ((RHMalignityGeometryCalls *)RHMalignityField<void *>(this, 0x64))->FUN_004eff80(origin, point, 2);
}

// Parked: case-zero flag masks and shared rejection branches schedule differently.
// STUB: GAME 0x0048c700
void RHMalignityActorCalls::FUN_0048c700(void *actor, unsigned mode)
{
    struct Kind4 { unsigned value : 4; };
    struct Kind5 { unsigned value : 5; };
    RHMalignityMessage message;
    switch (mode)
    {
    case 0:
        if (V130() == 0)
        {
            unsigned char type = ((Kind5 *)((char *)this + 4))->value;
            if (type == 20)
            {
                if (((Kind5 *)((char *)actor + 4))->value != type ||
                    ((RHMalignityActorCalls *)actor)->V130() != 1)
                    return;
                goto accepted;
            }
        }
        else
        {
            unsigned char type = ((Kind5 *)((char *)this + 4))->value;
            if (type == 20)
            {
                if ((((Kind5 *)((char *)actor + 4))->value != type ||
                     ((RHMalignityActorCalls *)actor)->V130() != 0) &&
                    ((Kind4 *)((char *)actor + 4))->value != 12)
                    return;
                goto accepted;
            }
        }
        if (((Kind4 *)((char *)actor + 4))->value != 12)
            return;
accepted:
        message.type = 0;
        message.actor = actor;
        break;
    case 3:
        message.type = 3;
        message.actor = actor;
        break;
    case 4:
        message.type = 4;
        message.actor = actor;
        break;
    case 1:
        if (RHMalignityField<bool>(actor, 0x23f) && FUN_0048c8e0(actor, true) == 1)
            return;
        message.type = 1;
        message.actor = actor;
        break;
    case 2:
        message.type = 2;
        message.actor = actor;
        break;
    case 5:
        message.type = 5;
        message.actor = actor;
        break;
    }
    RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x504 + mode * 0x34);
    RHMalignityMessageNode *head = (RHMalignityMessageNode *)list.m_head;
    RHMalignityMessageNode *previous = head->previous;
    RHMalignityMessageNode *node = (RHMalignityMessageNode *)operator new(0x1c);
    node->next = head ? head : node;
    node->previous = previous ? previous : node;
    head->previous = node;
    node->previous->next = node;
    new (&node->value) RHMalignityMessage(message);
    ++list.m_count;
    list.m_dirty = true;
}

struct RHMalignityMessageEraseList : public RHMalignityList
{
    void SeekMessage(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_current = m_head->next), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_current = m_head), wanted - count, category);
            }
            m_dirty = false;
        }
        else if (wanted != m_index)
        {
            int previous = m_index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)(m_current = m_head->next), wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                }
            }
            else if (wanted < (previous + count) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            }
            else
            {
                m_current = m_head;
                int distance = wanted - count;
                while (distance > 0) { m_current = m_current->next; --distance; }
                while (distance < 0) { m_current = m_current->previous; ++distance; }
            }
        }
        m_index = wanted;
    }
};

// Parked: cached-cursor erase and return-register scheduling still differ.
// STUB: GAME 0x0048ca20
unsigned char RHMalignityActorCalls::FUN_0048ca20(void *actor, unsigned mode)
{
    RHMalignityMessageEraseList &list = RHMalignityField<RHMalignityMessageEraseList>(this, 0x504 + mode * 0x34);
    unsigned count = list.m_count;
    for (unsigned index = 0; (unsigned short)index < (unsigned short)count; ++index)
    {
        list.FUN_005c8e40((unsigned short)index);
        RHMalignityMessageNode *node = (RHMalignityMessageNode *)list.m_current;
        if (node->value.actor == actor)
        {
            list.SeekMessage((unsigned short)index);
            RHMalignityNode *removed = list.m_current;
            RHMalignityNode *next = removed->next;
            removed->previous->next = next;
            next->previous = removed->previous;
            operator delete(removed);
            --list.m_count;
            list.m_dirty = true;
            return true;
        }
    }
    return false;
}

inline unsigned short RHMalignityEngineActorCount()
{
    RHMalignityActorCalls **first = RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x495c);
    if (!first)
        return 0;
    return (unsigned short)(RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x4960) - first);
}

// FUNCTION: GAME 0x0048cbc0
void RHElementActorNPC::ClearCompletedSequence()
{
    unsigned short count = RHMalignityEngineActorCount();
    for (unsigned short i = 0; i < count; ++i)
        RHMalignityField<RHMalignityActorCalls **>(g_pEngine, 0x495c)[i]->FUN_0048cb90(this);
}

// FUNCTION: GAME 0x0048cb90
void RHMalignityActorCalls::FUN_0048cb90(void *actor)
{
    int *vbase = RHMalignityField<int *>(this, 0x49c);
    void *current = RHMalignityField<void *>(this, vbase[1] + 0x4a0);
    if (actor != current)
        FUN_0048ca20(actor, 1);
}

// FUNCTION: GAME 0x0048cc20
void FUN_0048cc20(void *value, void *)
{
    unsigned type = RHMalignityField<unsigned>(value, 0x10);
    switch (type)
    {
    case 1:
    case 7:
        RHMalignityField<unsigned short>(value, 0x14) = 70;
        return;
    case 2:
        RHMalignityField<unsigned short>(value, 0x14) = 50;
        return;
    case 5:
    case 6:
    case 8:
    case 9:
        RHMalignityField<unsigned short>(value, 0x14) = 200;
        return;
    case 14:
        RHMalignityField<unsigned short>(value, 0x14) = 0;
        return;
    case 10:
    case 11:
        RHMalignityField<unsigned short>(value, 0x14) = 400;
        return;
    case 4:
    case 12:
        RHMalignityField<unsigned short>(value, 0x14) = 500;
        return;
    case 0:
        RHMalignityField<unsigned short>(value, 0x14) = 300;
        return;
    default:
        return;
    }
}

struct RHUnk00611a40Raw
{
    undefined4 m_00;
    undefined4 m_04;
};

// Parked: WORD argument registers, point-assignment receiver, and EH scheduling differ.
// STUB: GAME 0x0048d050
void RHElementActorNPC::FUN_0048d050()
{
    SBGeoPoint2D point;
    void *profile = RHMalignityField<void *>(this, 0x50);
    RHUnk005fc3b0 &direction = RHMalignityField<RHUnk005fc3b0>(this, 0x4d4);
    unsigned short heading = RHMalignityField<unsigned short>(profile, 0xd8);
    direction.Unk005fcd40(heading, 1.0f);
    const SBGeoPoint2D &position = RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(this, 0x50), 0x24);
    point = position;
    RHMalignityField<float>(this, 0x4e0) = point.m_y;
    RHMalignityField<float>(this, 0x4dc) = point.m_x;
    profile = RHMalignityField<void *>(this, 0x50);
    RHMalignityField<unsigned short>(this, 0x4e8) = RHMalignityField<unsigned short>(profile, 0xde);
    RHMalignityField<void *>(this, 0x4e4) = RHMalignityField<void *>(profile, 0xe0);
}

// Reconstructed the radius calculation and area comparison; polygon probing and hazard attenuation remain incomplete.
// STUB: GAME 0x0048db80
float RHMalignityActorCalls::FUN_0048db80(void *position, void *actor)
{
    if (!actor)
        return 0.0f;
    void *profile = RHMalignityField<void *>(this, 0x50);
    RHMalignityPosition origin = RHMalignityPositionOf(profile);
    RHMalignityPosition target = RHMalignityPositionOf(RHMalignityField<void *>(actor, 0x50));
    if (origin.area != target.area)
        return 0.0f;
    SBGeoPoint2D displacement = FUN_0040ec20(origin, target);
    float range = displacement.FUN_005fc700(1.0f);
    float radius = RHMalignityField<unsigned short>(this, 0x6cc);
    float remainder = radius * radius - range * range;
    if (remainder <= 0.0f)
        return 0.0f;
    if (position && RHMalignityField<void *>(position, 0x08) != origin.area)
        return 0.0f;
    return remainder;
}

// Parked: the inlined GoTo branches swap ecx/edx for the head and tag loads, changing the tail-merge point.
// STUB: GAME 0x0048e420
void RHElementActorNPC::FUN_0048e420(void *actor)
{
    int count = RHMalignityField<RHMalignityList>(this, 0x504).m_count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        if (actor && actor != RHMalignityField<RHMalignityEraseList<false> >(this, 0x504).At(index)->value)
            continue;
        RHMalignityField<bool>(RHMalignityField<RHMalignityEraseList<false> >(this, 0x504).At(index), 0x12) = false;
        RHMalignityField<bool>(RHMalignityField<RHMalignityEraseList<false> >(this, 0x504).SeekAt(index), 0x10) = false;
    }
}

// FUNCTION: GAME 0x0048e610
unsigned short RHMalignityActorCalls::FUN_0048e610()
{
    return RHMalignityField<unsigned short>(this, 0x4c8);
}

// FUNCTION: GAME 0x0048e620
void RHMalignityActorCalls::FUN_0048e620(unsigned short value)
{
    RHMalignityField<unsigned short>(this, 0x4c8) = value;
}

// FUNCTION: GAME 0x0048e630
void RHMalignityActorCalls::FUN_0048e630(unsigned operation, unsigned short value)
{
    switch (operation)
    {
    case 1:
        RHMalignityField<unsigned short>(this, 0x4ca) += value;
        break;
    }
}

// FUNCTION: GAME 0x0048e650
void RHMalignityActorCalls::FUN_0048e650(unsigned operation, unsigned short value)
{
    switch (operation)
    {
    case 1:
        RHMalignityField<unsigned short>(this, 0x4ca) = value;
        break;
    }
}

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);


// Parked: geometry argument scheduling and point-to-vector copy identity differ.
// STUB: GAME 0x0048e670
bool RHMalignityActorCalls::FUN_0048e670(void *actor)
{
    if (RHMalignityField<unsigned char>(this, 0x652))
        return false;
    if (RHMalignityField<int>((char *)this + ((int *)RHMalignityField<void *>(this, 0x49c))[1], 0x4a8) != 1)
        return false;
    if ((RHMalignityField<unsigned>(this, 4) & 31) == 0x14 || RHMalignityField<unsigned>(this, 0x4f0) < 200)
        return false;
    void *profile = RHMalignityField<void *>(this, 0x50);
    if (RHMalignityField<float>(profile, 0x10) == RHMalignityField<float>(profile, 0x2c) &&
        RHMalignityField<float>(profile, 0x14) == RHMalignityField<float>(profile, 0x30) &&
        RHMalignityField<float>(profile, 0x18) == RHMalignityField<float>(profile, 0x34))
        return false;
    if ((RHMalignityField<unsigned>(actor, 4) & 0xf) == 0xc &&
        RHMalignityField<unsigned char>((char *)this + ((int *)RHMalignityField<void *>(this, 0x49c))[1], 0x7e4) == 1)
        return false;
    if (RHMalignityField<void *>(RHMalignityField<void *>(actor, 0x50), 0xe0) != RHMalignityField<void *>(profile, 0xe0))
        return false;
    SBGeoVector2D displacement((const SBGeoVector2D &)RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(this, 0x50), 0x24)
        .Unk005fc110(RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(actor, 0x50), 0x24))
        .Unk005fc190(20.0f * reinterpret_cast<RHElementActor *>(this)->FUN_004135b0()));
    if (displacement.FUN_005fc700(1.0f) > 70.0f)
        return false;
    short heading = RHMalignityField<short>(RHMalignityField<void *>(actor, 0x50), 0xd8);
    int difference = (((RHUnk005fc3b0 *)&displacement)->FUN_005fcc50(0.57357645f) - heading) & 0xf;
    if (difference < 0)
        return false;
    if (difference <= 1 || difference == 0xf)
        return true;
    return false;
}

// Reconstructed point projection and action setup; the target's selection and cleanup paths remain incomplete.
// STUB: GAME 0x0048e870
void RHMalignityActorCalls::FUN_0048e870(void *actor)
{
    void *profile = RHMalignityField<void *>(this, 0x50);
    void *otherProfile = RHMalignityField<void *>(actor, 0x50);
    RHMalignityPosition own = RHMalignityPositionOf(profile);
    RHMalignityPosition other = RHMalignityPositionOf(otherProfile);
    if (own.area != other.area)
        return;
    SBGeoPoint2D delta = FUN_0040ec20(own, other);
    if (delta.FUN_005fc700(1.0f) >= 0.0f)
        return;
    RHMalignityField<unsigned char>(this, 0x652) = 1;
    RHMalignityField<unsigned>(this, 0x4f0) -= RHMalignityField<unsigned>(this, 0x4f0) >= 10 ? 10 : 0;
}

// FUNCTION: GAME 0x0048ebe0
void RHMalignityActorCalls::FUN_0048ebe0()
{
    unsigned short value = RHMalignityField<unsigned short>(g_pEngine, 0x4cc0);
    RHMalignityField<unsigned short>(this, 0x6c0) = value;
    RHMalignityField<unsigned short>(this, 0x6c2) = value;
}

// FUNCTION: GAME 0x004b8f80
int RHSectorActorList::Unk004b8f80(RHElementActor *const &value, bool mode)
{
    return Find(value, mode);
}

class RHMalignitySegmentTemporary
{
public:
    RHMalignitySegmentTemporary(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((SBGeoSegment2D *)this)->SBGeoSegment2D::SBGeoSegment2D(first, second);
    }
    ~RHMalignitySegmentTemporary()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    const RHMalignitySegment &Value() const { return *(const RHMalignitySegment *)this; }
    undefined m_00[0x10];
};

DECOMP_SIZE_ASSERT(RHMalignitySegmentTemporary, 0x10)
DECOMP_SIZE_ASSERT(RHUnk004dab90Rectangle, 0x50)

// Parked: zero-register allocation, segment-return operands, and EH scheduling differ.
// STUB: GAME 0x004da8d0
void RHMalignityEngineCalls::FUN_004da8d0(const SBGeoBoundingBox2D &box)
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    SBGeoPoint2D third;
    SBGeoPoint2D fourth;
    first = RHMalignityField<SBGeoPoint2D>((void *)&box, 0);
    float y = RHMalignityField<float>((void *)&box, 0x0c);
    second.m_y = y;
    second.m_x = RHMalignityField<float>((void *)&box, 0);
    third = RHMalignityField<SBGeoPoint2D>((void *)&box, 8);
    float fourthY = RHMalignityField<float>((void *)&box, 4);
    fourth.m_y = fourthY;
    fourth.m_x = RHMalignityField<float>((void *)&box, 8);
    RHMalignityRectangle *rectangle = new RHUnk004dab90Rectangle;
    RHMalignityArrayCalls &indices = *(RHMalignityArrayCalls *)((char *)rectangle + 0x2c);
    RHMalignityField<unsigned>(rectangle, 0x4c) = 0;
    RHMalignityArrayCalls &edges = *(RHMalignityArrayCalls *)rectangle;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegmentTemporary(first, second).Value());
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegmentTemporary(second, third).Value());
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegmentTemporary(third, fourth).Value());
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegmentTemporary(fourth, first).Value());
    RHMalignityField<bool>(rectangle, 0x14) = true;
    unsigned mask = 0xf000;
    indices.FUN_004e60a0(RHMalignityField<void *>(&indices, 8), 1, mask);
    RHMalignityField<bool>(&indices, 0x14) = true;
    indices.FUN_004e60a0(RHMalignityField<void *>(&indices, 8), 1, mask);
    RHMalignityField<bool>(&indices, 0x14) = true;
    indices.FUN_004e60a0(RHMalignityField<void *>(&indices, 8), 1, mask);
    RHMalignityField<bool>(&indices, 0x14) = true;
    indices.FUN_004e60a0(RHMalignityField<void *>(&indices, 8), 1, mask);
    RHMalignityField<bool>(&indices, 0x14) = true;
    RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x4c9c);
    RHMalignityNode *head = list.m_head;
    RHMalignityNode *previous = head->previous;
    RHMalignityNode *node = (RHMalignityNode *)operator new(12);
    node->next = head ? head : node;
    node->previous = previous ? previous : node;
    head->previous = node;
    node->previous->next = node;
    new (&node->value) RHMalignityRectangle *(rectangle);
    ++list.m_count;
    list.m_dirty = true;
}

// LIBRARY: GAME 0x004e60a0
// ?insert@?$vector@GV?$allocator@G@std@@@std@@QAEXPAGIABG@Z

#include <list>

struct RHMalignityOwnedValue
{
    undefined4 m_00; // 0x00
};

// SIZE 0x10
struct RHMalignityOwnedList
{
    std::list<RHMalignityOwnedValue *> m_list; // 0x00
    std::list<RHMalignityOwnedValue *>::iterator m_current; // 0x0c
    void FUN_004e65b0();
};

DECOMP_SIZE_ASSERT(RHMalignityOwnedList, 0x10)

// SIZE 0x10
struct RHMalignityOwnedPointList
{
    std::list<RHMalignityOwnedPoint *> m_list; // 0x00
    std::list<RHMalignityOwnedPoint *>::iterator m_current; // 0x0c
    void FUN_004e6540();
};

DECOMP_SIZE_ASSERT(RHMalignityOwnedPointList, 0x10)

// SIZE 0x10
struct RHMalignityOwnedRecordList
{
    std::list<RHMalignityOwnedRecord *> m_list; // 0x00
    std::list<RHMalignityOwnedRecord *>::iterator m_current; // 0x0c
    void FUN_004e6620();
};

DECOMP_SIZE_ASSERT(RHMalignityOwnedRecordList, 0x10)

// FUNCTION: GAME 0x004e6540
void RHMalignityOwnedPointList::FUN_004e6540()
{
    std::list<RHMalignityOwnedPoint *>::iterator end;
    for (m_current = m_list.begin(); end = m_list.end(), m_current != end; ++m_current)
    {
        if (*m_current)
            delete *m_current;
    }
    m_list.clear();
}

// FUNCTION: GAME 0x004e65b0
void RHMalignityOwnedList::FUN_004e65b0()
{
    std::list<RHMalignityOwnedValue *>::iterator end;
    for (m_current = m_list.begin(); end = m_list.end(), m_current != end; ++m_current)
    {
        if (*m_current)
            delete *m_current;
    }
    m_list.clear();
}

// FUNCTION: GAME 0x004e6620
void RHMalignityOwnedRecordList::FUN_004e6620()
{
    std::list<RHMalignityOwnedRecord *>::iterator end;
    for (m_current = m_list.begin(); end = m_list.end(), m_current != end; ++m_current)
    {
        if (*m_current)
            delete *m_current;
    }
    m_list.clear();
}

// Parked: frame is sixteen bytes too small; query-list and geometry cleanup layouts differ.
// STUB: GAME 0x004f5e50
bool RHMalignityGridCalls::FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer)
{
    RHMalignityQueryList lines;
    for (unsigned short attempt = 0; attempt < 50; ++attempt)
    {
        FUN_004ed370(lines, layer, RHMalignitySegmentTemporary(box.FUN_00608f40(), point).Value(), 2);
        FUN_004ed070(lines, layer, box, 2);
        unsigned short count = (unsigned short)lines.Count();
        if (count == 0)
            return true;
        for (unsigned short index = 0; index < count; ++index)
        {
            ((RHSectorActorList *)&lines)->Unk005c8e40(index);
            void *line = lines.cursor->_Value;
            SBGeoPoint2D &anchor = RHMalignityField<SBGeoPoint2D>(line, 4);
            SBGeoVector2D &normal = RHMalignityField<SBGeoVector2D>(line, 0x34);
            if (normal.FUN_005fc660(anchor.Unk005fc110(point)) > 0.0f)
            {
                float distance = normal.FUN_005fc660(anchor.Unk005fc110(RHMalignityField<SBGeoPoint2D>(&box, 0)));
                if (distance > (-0.10000000149011612f))
                    box.Translate(operator*(distance + 1.0f, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(RHMalignityField<SBGeoPoint2D>(&box, 8)));
                if (distance > (-0.10000000149011612f))
                    box.Translate(operator*(distance + 1.0f, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(SBGeoPoint2D(RHMalignityField<float>(&box, 8), RHMalignityField<float>(&box, 4))));
                if (distance > (-0.10000000149011612f))
                    box.Translate(operator*(distance + 1.0f, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(SBGeoPoint2D(RHMalignityField<float>(&box, 0), RHMalignityField<float>(&box, 0x0c))));
                if (distance > (-0.10000000149011612f))
                    box.Translate(operator*(distance + 1.0f, normal));
            }
        }
        RHMalignityNode *head = (RHMalignityNode *)lines.Head();
        RHMalignityNode *it = head->next;
        while (it != head)
        {
            RHMalignityNode *node = it;
            it = it->next;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
            --lines.Count();
        }
        lines.dirty = true;
    }
    return false;
}

template<>
// FUNCTION: GAME 0x004fe2e0
RHScriptIter RHCampaignIndexList<false>::FUN_004fe2e0(RHScriptIter position, const unsigned short &value)
{
    RHScriptNode *head = position.node;
    RHScriptNode *previous = head->prev;
    RHScriptNode *node = (RHScriptNode *)operator new(12);
    node->next = head ? head : node;
    node->prev = previous ? previous : node;
    head->prev = node;
    node->prev->next = node;
    new (&node->data) unsigned short(value);
    ++m_count;
    return RHScriptIter(node);
}

// FUNCTION: GAME 0x00560450
const SBGeoBoundingBox2D &RHPathActorInfo::FUN_00560450()
{
    return *(SBGeoBoundingBox2D *)((char *)this + 0xc0);
}

// FUNCTION: GAME 0x00608f10
int RHUnk00608f10::FUN_00608f10(void *value)
{
    return !FUN_006082a0(value);
}

void RHArtificialMalignity::Emit(SBFile &file)
{
    FUN_004334b0(0);
    FUN_00449af0(*(RHMalignityPosition *)this, 0);
    FUN_00434710(0);
    FUN_0043afc0(*(RHMalignityPosition *)this, 0);
    CheckAmbushPoint(0, false);
    FUN_0042ff90();
    FUN_0044d6c0();
    FUN_0044dc80(0);
    FUN_0044d1d0();
    FUN_0044da40();
    FUN_0044b4e0(*(RHUnk00571160Position *)this);
    FUN_0044c850(*(RHMalignityPosition *)this);
    FUN_00438f80(*(RHMalignityStimulus *)this);
    FUN_00445b40();
    FUN_004461a0(0, 0);
    FUN_00446400();
    FUN_00446700();
    FUN_0044cf00();
    InitOneAI();
    FUN_00439cb0(*(RHMalignityPosition *)this, 0);
    FUN_00439e70(0, *(RHMalignityPosition *)this);
    FUN_00439f60(*(RHMalignityStimulus *)this);
    FUN_0043a080(*(RHMalignityPosition *)this);
    FUN_0043a170(*(RHMalignityPosition *)this);
    FUN_0043d780(0);
    FUN_00441020(0, 0);
    FUN_0043f340(0);
    FUN_0043f540(0);
    FUN_0043fa80(0, 0);
    FUN_0043fc60(0, 0);
    FUN_00441dd0();
    FUN_00441f20();
    SerializeExactlyThisAI(file);
    InitializeFriendCheck(0, 0, 0);
    ((RHMalignityActorCalls *)Base().m_actor)->FUN_0048ebe0();
    ((RHPathActorInfo *)this)->FUN_00560450();
    ((RHUnk00608f10 *)this)->FUN_00608f10(0);
    ((RHMalignityOwnedPointList *)this)->FUN_004e6540();
    ((RHMalignityOwnedList *)this)->FUN_004e65b0();
    ((RHMalignityOwnedRecordList *)this)->FUN_004e6620();
    ((RHCampaignIndexList<false> *)this)->FUN_004fe2e0(RHScriptIter(0), *(unsigned short *)this);
    ((RHMalignityEngineCalls *)this)->FUN_004da8d0(*(SBGeoBoundingBox2D *)this);
    ((RHMalignityGridCalls *)this)->FUN_004f5e50(*(SBGeoBoundingBox2D *)this, *(SBGeoPoint2D *)this, 0);
}
