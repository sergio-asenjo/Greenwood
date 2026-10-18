#include "SBNullstr.h"
#include "RHArtificialMalignity.h"
#include "RHElementActorNPC.h"
#include <stdlib.h>
#include <new>

void FUN_0064158f(void *memory);

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityPosition, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityArray, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityNode, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityList, 0x18)
DECOMP_SIZE_ASSERT(RHSectorActorList, 0x24)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHUnk00521770, 0x3c)
DECOMP_SIZE_ASSERT(RHMalignityMessage, 0x14)
DECOMP_SIZE_ASSERT(RHMalignityMessageNode, 0x1c)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHMalignitySegment, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityRectangle, 0x50)
DECOMP_SIZE_ASSERT(RHMalignityQueryList, 0x24)

// GLOBAL: GAME 0x006c0754
bool g_unk0x006c0754 = false;

// GLOBAL: GAME 0x006c0788
bool g_unk0x006c0788 = false;

// GLOBAL: GAME 0x006c08a4
unsigned *g_unk0x006c08a4 = 0;

// GLOBAL: GAME 0x006774e4
float g_unk0x006774e4 = 15.0f;

// GLOBAL: GAME 0x006c0e48
undefined g_unk0x006c0e48[0x2c] = {0};

// GLOBAL: GAME 0x006787f8
float g_unk0x006787f8 = -0.10000000149011612f;

#define M(type, offset) RHMalignityField<type>(this, offset)
#define B(type, offset) RHMalignityField<type>(&Base(), offset)
#define A(type, offset) RHMalignityField<type>(Base().m_actor, offset)
#define F(type, offset) RHMalignityField<type>(B(void *, 0x1fc), offset)
#define S(type, offset) RHMalignityField<type>(B(void *, 0x200), offset)
#define FA(type, offset) RHMalignityField<type>((char *)B(void *, 0x1fc) + ((int *)F(void *, 0x49c))[1], offset)
#define SA(type, offset) RHMalignityField<type>((char *)B(void *, 0x200) + ((int *)S(void *, 0x49c))[1], offset)
#define AA(type, offset) RHMalignityField<type>((char *)Base().m_actor + ((int *)A(void *, 0x49c))[1], offset)
#define RESET() ((RHArtificialIntelligence *)&Base())->Unk00410010(false)

void RHMalignityList::FUN_005c8e40(int wanted)
{
    if (m_dirty)
    {
        int distance;
        if ((m_count + 1) / 2 < wanted)
        {
            m_current = m_head;
            distance = wanted - m_count;
        }
        else
        {
            m_current = m_head->next;
            distance = wanted;
        }
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)m_current, distance, category);
        m_dirty = false;
    }
    else if (wanted != m_index)
    {
        int previous = m_index;
        int distance;
        if (wanted < previous)
        {
            if (wanted < (previous + 1) / 2)
            {
                m_current = (RHMalignityNode *)
                    ((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                distance = wanted;
            }
            else
                distance = wanted - previous;
        }
        else if (wanted < (previous + m_count) / 2)
            distance = wanted - previous;
        else
        {
            m_current = m_head;
            distance = wanted - m_count;
        }
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)m_current, distance, category);
    }
    m_index = wanted;
}

// Parked: cached-cursor branch layout and iterator-call scheduling remain unmatched.
// STUB: GAME 0x0048c8e0
unsigned char RHMalignityActorCalls::FUN_0048c8e0(void *actor, unsigned mode)
{
    RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x504 + mode * 0x34);
    unsigned short count = (unsigned short)list.m_count;
    unsigned short index = 0;
    while (index < count)
    {
        std::bidirectional_iterator_tag category;
        if (list.m_dirty)
        {
            int distance;
            if ((list.m_count + 1) / 2 < index)
            {
                list.m_current = list.m_head;
                distance = (int)index - list.m_count;
            }
            else
            {
                list.m_current = list.m_head->next;
                distance = index;
            }
            FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, distance, category);
            list.m_dirty = false;
            list.m_index = index;
        }
        else if (index != list.m_index)
        {
            int previous = list.m_index;
            int distance;
            if (index < previous)
            {
                if (index < (previous + 1) / 2)
                {
                    list.m_current = (RHMalignityNode *)
                        ((RHUnk0046eb30 *)&list)->FUN_0046eb80().node;
                    distance = index;
                }
                else
                    distance = (int)index - previous;
            }
            else if (index < (previous + list.m_count) / 2)
                distance = (int)index - previous;
            else
            {
                list.m_current = list.m_head;
                distance = (int)index - list.m_count;
            }
            FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, distance, category);
            list.m_index = index;
        }
        if (((RHMalignityMessageNode *)list.m_current)->value.actor == actor)
            return 1;
        ++index;
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
SBGeoPoint2D RHMalignityBaseView::FUN_0040cc20(void *actor)
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

class RHMalignityUnk00414320
{
public:
    void *FUN_00414320();
};

// FUNCTION: GAME 0x00414320
void *RHMalignityUnk00414320::FUN_00414320()
{
    return (void *)((char *)this + 0x18);
}

void EmitRHMalignityUnk00414320(RHMalignityUnk00414320 *a)
{
    a->FUN_00414320();
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
            projection = ((RHActorAreaCalls *)area)->FUN_0057d800(point);
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
                bool close = FUN_0040ec20(location, position).FUN_005fc700(1.0f) < g_unk0x006774a0;
                if (close)
                {
                    found = candidate;
                    break;
                }
            }
            if (found)
            {
                RHActorAreaCalls *owner = RHMalignityField<RHActorAreaCalls *>(found, 0x0c);
                projection = owner->FUN_0057d800(RHMalignityField<SBGeoPoint2D>(found, 0x18));
            }
        }
    }
    float height;
    if (!projection)
        height = g_unk0x00677488;
    else
        height = (RHMalignityField<float>(projection, 0xf4) * position.x +
                  RHMalignityField<float>(projection, 0xf8) * position.y +
                  RHMalignityField<float>(projection, 0xfc)) /
                 (g_unk0x0067749c - RHMalignityField<float>(projection, 0xf8));
    result.x = position.x;
    result.y = position.y + height;
    result.z = height;
    return result;
}

// FUNCTION: GAME 0x00419e10
bool RHMalignityBaseView::FUN_00419e10(void *actor)
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
void RHMalignityBaseView::FUN_0041a300(void *actor)
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
void RHMalignityBaseView::FUN_0041ab30()
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
void RHScriptBatchCalls::Unk0041ac50()
{
    RHMalignityBaseView &base = *(RHMalignityBaseView *)this;
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
            *(RHUnk005fc3b0 *)&firstPoint.Unk005fc110(origin), 1.0f) < g_unk0x00677488;
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
    ((RHScriptBatchCalls *)&Base())->Unk0041ac50();

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
            ((RHMalignityActorCalls *)Base().m_actor)->Vd4(value, 10000, false, false);
        }
        break;
    }

    bool activatePath = ((RHArtificialIntelligence *)&Base())->InitState() &&
        !B(unsigned char, 0x1c4) && B(unsigned char, 0x174) == 0;
    ((RHMalignityActorCalls *)Base().m_actor)->FUN_0048d050();
    RHArtificialIntelligencePathCursor *path = (RHArtificialIntelligencePathCursor *)&AA(char, 0x4cc);
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
    unsigned tacticalCount = g_unk0x006c0718.first ?
        (unsigned short)(g_unk0x006c0718.last - g_unk0x006c0718.first) : 0;
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

// Parked: the target loads the value into dx (edx) and reuses eax for the base
// pointer; VC6 reuses ax (eax) here. Inline, named unsigned-short/unsigned/int
// locals, char*/unsigned short* pointer forms all give ax. 75.00%.
// STUB: GAME 0x00438600
unsigned short RHMalignityOwnerCalls::FUN_00438600()
{
    void *value = *(void **)((char *)this + 0x334);
    return FUN_00438710(*(unsigned short *)((char *)value + 0x32), 0.5f, 2.0f, 100);
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
    void FUN_00412d60(RHMalignityPosition position, int heading, int mode);
    void FUN_0041a3e0();
};

// FUNCTION: GAME 0x0041a3e0
void RHMalignityReactionCalls::FUN_0041a3e0()
{
    if (*(int *)((char *)this + 0x14) >= 0x13 && *(int *)((char *)this + 0x14) <= 0x14)
        ((RHMalignityBaseView *)this)->FUN_0041a300(0);
    ((RHMalignityActorCalls *)*(void **)((char *)this + 4))->Unk0048d020();
    if (*(int *)((char *)this + 0x14) < 0x13 ||
        (*(int *)((char *)this + 0x14) > 0x14 && *(int *)((char *)this + 0x14) != 0x6c))
        ((RHArtificialIntelligence *)this)->Unk00410600();
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
    int offset = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130() << 5;
    unsigned short count = RHMalignityField<RHMalignityArray>(g_pEngine, 0x4d08 + offset).size();
    if (count > 0)
    {
    unsigned remaining = count;
    for (int index = 0; remaining != 0; ++index, --remaining)
    {
        void *actor = RHMalignityField<void **>(g_pEngine, 0x4d0c + offset)[index];
        if (actor == VirtualBase().m_actor)
            continue;
        void *base = (char *)actor + RHMalignityField<int *>(actor, 0x49c)[1];
        int state = RHMalignityField<int>(base, 0x4a8);
        if (state > 0 && (state <= 2 || (state == 3 &&
            RHMalignityField<int>(base, 0x4b0) >= 0x52 && RHMalignityField<int>(base, 0x4b0) <= 0x53)))
        {
            const RHUnk00613e90 &own = RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(VirtualBase().m_actor, 0x50), 0x10);
            RHUnk00613e90 difference = RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(actor, 0x50), 0x10).FUN_005df550(own);
            if (difference.z * difference.z + difference.x * difference.x + difference.y * difference.y < (int)radius * radius)
                ((RHMalignityReactionCalls *)((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1] + 0x49c))->V24(&stimulus);
        }
    }
    }
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
    ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_00487ad0(position);
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(100);
}

// Parked: stimulus/base register allocation and the shared timer call differ.
// STUB: GAME 0x00439f60
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
    ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_00487ad0(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0));
    RHMalignityBaseView &base = VirtualBase();
    void *actor = RHMalignityField<void *>((void *)&stimulus, 0x14);
    ((RHMalignityReactionCalls *)&base)->FUN_00412d60(base.FUN_004165e0(actor, true),
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
    ((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_00487ad0(position);
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    FUN_00438620(50);
}

// Parked 98.8%: VC6 schedules the hoisted `flags & 4` after the loop-counter setup (target: right after the flags load).
// STUB: GAME 0x0043d780
void *RHArtificialMalignity::FUN_0043d780(unsigned short flags)
{
    unsigned short best = 0xff98;
    void *result = 0;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityList>(this, 0x2e4).size();
    if (count > 0)
    {
        RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x2e4);
        int index = 0;
        unsigned remaining = count;
        do
        {
            list.FUN_005c8e40(index);
            void *actor = list.m_current->value;
            if ((flags & 4) || FUN_0044afa0(actor))
            {
                if (VirtualBase().FUN_0041a0b0(actor) <= best)
                {
                    unsigned short value = (unsigned short)VirtualBase().FUN_0041a060(actor);
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
            ++index;
        } while (--remaining != 0);
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
        if (((SBGeoVector2D &)own).FUN_005fc660(other) >= g_unk0x00677488)
        {
            offset.FUN_005fc430(FUN_0040ec20(((RHMalignityBaseView *)((char *)this + ((int *)*(void **)this)[1]))->FUN_004165e0(actor, true), VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)));
            float y = offset.m_y;
            y *= g_unk0x006774ec;
            offset.m_y = y;
            return own.FUN_005fc680(offset, 1.0f) < g_unk0x00677488;
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
        if (((SBGeoVector2D &)own).FUN_005fc660(other) >= g_unk0x00677488)
        {
            offset.FUN_005fc430(FUN_0040ec20(((RHMalignityBaseView *)((char *)this + ((int *)*(void **)this)[1]))->FUN_004165e0(actor, true), VirtualBase().FUN_004165e0(VirtualBase().m_actor, true)));
            float y = offset.m_y;
            y *= g_unk0x006774ec;
            offset.m_y = y;
            return own.FUN_005fc680(offset, 1.0f) > g_unk0x00677488;
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
        y *= g_unk0x00677504;
        direction.m_y = y;
        y = offset.m_y;
        y *= g_unk0x00677504;
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
        y *= g_unk0x00677504;
        direction.m_y = y;
        y = offset.m_y;
        y *= g_unk0x00677504;
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
    RHMalignityBaseView &base = VirtualBase();
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

    RHMalignityList &list = M(RHMalignityList, 0x2e4);
    ((RHAIUnk0044e8b0 *)&list)->FUN_0044e8b0(RHMalignityIterator(list.m_head->next), RHMalignityIterator(list.m_head));
    int offset = first << 5;
    list.m_dirty = true;

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
                if (((RHSectorActorList *)&list)->Unk004b8f80((RHElementActor *const &)element, true) == -1)
                    list.InsertLast(element);
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

// Parked: engine actor selection and action dispatch rely on unresolved out-of-run helpers.
// STUB: GAME 0x004436e0
unsigned RHArtificialMalignity::FUN_004436e0(void *, char)
{
    return 0;
}

// Parked: the sibling action requires the same unresolved actor-array and UI dispatch helpers.
// STUB: GAME 0x00443850
unsigned RHArtificialMalignity::FUN_00443850(void *)
{
    return 0;
}

// Parked: state updates span a script list, actor references and multiple manager helpers.
// STUB: GAME 0x004439a0
void RHArtificialMalignity::FUN_004439a0(void *, unsigned char)
{
}

// Parked: threat selection, actor allocation and movement notification depend on out-of-run helpers.
// STUB: GAME 0x00443af0
void RHArtificialMalignity::FUN_00443af0(unsigned)
{
}

// Parked: actor-array filtering depends on engine globals and multiple external virtual/helper bindings.
// STUB: GAME 0x00443c40
void *RHArtificialMalignity::FUN_00443c40(void *)
{
    return 0;
}

// Parked: the sibling actor-array filter adds geometry and script comparisons through external helpers.
// STUB: GAME 0x00443d10
void *RHArtificialMalignity::FUN_00443d10(void *)
{
    return 0;
}

// Parked: nearest-actor selection depends on engine arrays, geometry conversion and virtual filters.
// STUB: GAME 0x00443e20
void *RHArtificialMalignity::FUN_00443e20(unsigned, unsigned, unsigned, int)
{
    return 0;
}

// Parked: route generation builds nested geometry/list temporaries and requires unresolved helper ABIs.
// STUB: GAME 0x00443fa0
unsigned RHArtificialMalignity::FUN_00443fa0(unsigned, unsigned, unsigned, unsigned)
{
    return 0;
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

// Parked: path initialization depends on a separate set of engine and actor-manager bindings.
// STUB: GAME 0x004450a0
void RHArtificialMalignity::FUN_004450a0()
{
}

// Parked: this short helper's ownership/signature and member-field binding remain unverified.
// STUB: GAME 0x00445180
void RHArtificialMalignity::FUN_00445180()
{
}

// Parked: path-state processing uses out-of-run actor callbacks and global engine data.
// STUB: GAME 0x00445210
unsigned FUN_00445210(float, unsigned, unsigned, unsigned, float, unsigned, void *, unsigned)
{
    return 0;
}

class RHMalignityHeadingPoint : public SBGeoPoint2D
{
public:
    unsigned char FUN_005fcc50(float value) const;
};

extern float g_rhuirendererportrait_percent;
extern float g_unk0x00677430;

// GLOBAL: GAME 0x0067759c
float g_unk0x0067759c = 180.0f;

// GLOBAL: GAME 0x006775a0
float g_unk0x006775a0 = 250.0f;

// GLOBAL: GAME 0x006775a4
float g_unk0x006775a4 = 300.0f;

// Parked: range-case block placement differs; the shared 80-float entity has a conflicting initializer.
// STUB: GAME 0x00445510
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
    unsigned relativeHeading = (((RHMalignityHeadingPoint *)&direction)->FUN_005fcc50(0.57357645f) - heading) & 15;
    switch (relativeHeading)
    {
    case 0:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 3:
        case 9:
            radius = g_unk0x006775a4;
            break;
        case 2:
        case 8:
        case 14:
            radius = g_unk0x006775a0;
            break;
        default:
            radius = g_unk0x00677430;
            break;
        }
        break;
    case 1:
    case 15:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 2:
        case 8:
        case 14:
            radius = g_unk0x00677430;
            break;
        case 3:
        case 9:
            radius = g_unk0x006775a0;
            break;
        default:
            radius = g_rhuirendererportrait_percent;
            break;
        }
        break;
    case 2:
    case 14:
        switch (RHMalignityField<int>(actor, 0x144))
        {
        case 2:
        case 8:
        case 14:
            radius = g_unk0x00677430;
            break;
        case 3:
        case 9:
            radius = g_unk0x0067759c;
            break;
        default:
            radius = g_rhuirendererportrait_percent;
            break;
        }
        break;
    case 3:
    case 4:
    case 12:
    case 13:
        radius = g_rhuirendererportrait_percent;
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
        int count = list.m_count;
        list.m_value = (RHElementActor *)RHMalignityField<void *>(&VirtualBase(), 0x1f8);
        list.m_forward = true;
        list.m_current = list.m_head->next;
        int index = 0;
        while (index < count)
        {
            if (list.m_current->value == list.m_value)
                break;
            ++index;
            list.m_current = list.m_current->next;
        }
        if (index < count)
        {
            list.m_result = index;
            list.m_dirty = false;
            list.m_index = index;
        }
        else
        {
            list.m_dirty = true;
            list.m_result = -1;
        }
        if (list.m_result == -1)
        {
            RHMalignityNode *head = list.m_head;
            RHMalignityNode *previous = head->previous;
            RHMalignityNode *node = (RHMalignityNode *)operator new(12);
            node->next = head ? head : node;
            node->previous = previous ? previous : node;
            head->previous = node;
            node->previous->next = node;
            new (&node->value) void *(RHMalignityField<void *>(&VirtualBase(), 0x1f8));
            ++list.m_count;
            list.m_dirty = true;
        }
        RHMalignityField<void *>(&VirtualBase(), 0x1f8) = 0;
    }
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_0041a3e0();
    RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0) = position;
    VirtualBase().V10(2, 0x25);
    ((RHMalignityRemarkCalls *)&VirtualBase())->Unk00418c40(((RHMalignityActorCalls *)VirtualBase().m_actor)->Vf8() ? 0x75 : 0x25, 0);
    ((RHMalignityReactionCalls *)&VirtualBase())->FUN_00412d60(RHMalignityField<RHMalignityPosition>(&VirtualBase(), 0xd0), -1, 0);
    ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fb0(2);
    ((RHArtificialIntelligence *)&VirtualBase())->Unk00416710(50);
}

// Parked: cached-list erase frame and iterator-assignment scheduling differ.
// STUB: GAME 0x004459b0
void RHArtificialMalignity::FUN_004459b0()
{
    unsigned short count = (unsigned short)M(RHMalignityList, 0x194).m_count;
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityList &list = M(RHMalignityList, 0x194);
        list.FUN_005c8e40(index);
        if (!RHMalignityField<bool>(list.m_current->value, 0x12))
        {
            list.Seek(index);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current));
            --index;
            --count;
            list.m_dirty = true;
        }
    }
    void *&target = RHMalignityField<void *>(&VirtualBase(), 0x8c);
    if (target && !RHMalignityField<bool>(target, 0x12))
        target = 0;
}

// GLOBAL: GAME 0x00677564
float g_unk0x00677564 = 500.0f;

template <bool InlineHead>
struct RHMalignityEraseList : public RHMalignityList
{
    void SeekErase(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                m_current = InlineHead ? m_head->next : (RHMalignityNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, std::bidirectional_iterator_tag());
            }
            else
            {
                m_current = m_head;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, std::bidirectional_iterator_tag());
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
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, std::bidirectional_iterator_tag());
                }
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, std::bidirectional_iterator_tag());
            }
            else if (wanted < (previous + count) / 2)
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, std::bidirectional_iterator_tag());
            else
            {
                m_current = m_head;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, std::bidirectional_iterator_tag());
            }
            m_index = wanted;
        }
    }
};

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
        FUN_0064158f(removed);
        --list.m_count;
    }
    list.m_dirty = true;
}

class RHMalignityGuardCalls
{
public:
    void FUN_0049fbb0(void *actor);
};

struct RHArtificialIntelligenceStaticArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void *operator[](unsigned index) { return m_first[index]; }
};

extern RHArtificialIntelligenceStaticArray g_unk0x006c06d0;

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

struct RHMalignityTeam
{
    undefined m_00[8];
    RHArtificialIntelligenceStaticArray actors;
    undefined m_14[0xc];
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
        RHMalignityNode *head = *(RHMalignityNode *volatile *)&m_head;
        int count = m_count;
        m_value = (RHElementActor *)value;
        m_forward = true;
        m_current = head->next;
        int index;
        for (index = 0; index < count; ++index, m_current = m_current->next)
        {
            RHMalignityNode *node = m_current;
            RHElementActor *wanted = m_value;
            if (*(void *volatile *)&node->value == wanted)
                break;
        }
        if (index < count)
        {
            m_result = index;
            m_dirty = false;
            m_index = index;
            return;
        }
        m_dirty = true;
        m_result = -1;
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
        if (M(RHMalignityFindList, 0x194).m_result == -1)
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
        RHMalignityBaseView &base = VirtualBase();
        ((RHMalignityReactionCalls *)&base)->FUN_00412d60(base.FUN_004165e0(actor, true),
            (int)RHMalignityField<float>(RHMalignityField<void *>(actor, 0x50), 0x18), 0);
        ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fb0(2);
        VirtualBase().V10(2, 0x2d);
        RHSectorActorList &list = M(RHSectorActorList, 0x1dc);
        if (list.Unk004b8f80((RHElementActor *const &)actor, true) == -1)
        {
            ((RHAIUnk0044e8b0 *)&list)->FUN_00424410(RHMalignityIterator(list.m_head), actor);
            list.m_dirty = true;
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
    ((RHAIUnk0044e8b0 *)&list)->FUN_0044e8b0(RHMalignityIterator(list.m_head->next), RHMalignityIterator(list.m_head));
    list.m_dirty = true;
    unsigned remaining = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    for (unsigned offset = 0; remaining != 0; offset += 4, --remaining)
    {
        RHMalignityTargetCalls *actor = *(RHMalignityTargetCalls **)((char *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.m_first + offset);
        if (actor == VirtualBase().m_actor || RHMalignityField<bool>(actor, 0x1ce) ||
            ((RHMalignityTargetCalls *)actor)->V048() || !((RHMalignityActorCalls *)VirtualBase().m_actor)->FUN_0048a130(actor))
            continue;
        int state = RHMalignityField<int>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4b0);
        if (state < 0x29 || state > 0x34)
            continue;
        void *value = actor;
        ((RHMalignityFindList *)&list)->FindForward(value);
        if (list.m_result == -1)
            ((RHMalignityList *)&list)->InsertLast(value);
    }
}

class RHMalignityVirtualView : public virtual RHMalignityBaseView
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
        if (actor != VirtualBase().m_actor && !actor->V048() &&
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

inline void RHMalignityList::RemoveFirst()
{
    RHMalignityNode *node = m_head->next;
    node->previous->next = node->next;
    node->next->previous = node->previous;
    FUN_0064158f(node);
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

struct RHMalignitySearchList
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
    if (!RHMalignityField<RHMalignitySearchList>(this, 0x1dc).m_count)
        return;
    RHMalignitySearchList &list = RHMalignityField<RHMalignitySearchList>(this, 0x1dc);
    short found = (short)list.FindForward(actor);
    if (found == -1)
        return;
    list.SeekFound(found);
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

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class RHMalignityPathGeometry
{
public:
    bool FUN_004f9170(const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned short layer, void *radius);
};

class RHUnkPathActorInfoBase
{
public:
    char m_pad0[0x88];
    int m_88;
    void *Unk0055fa10(int value);
    void *Current() { return Unk0055fa10(m_88); }
};

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
    void *radius = ((RHUnkPathActorInfoBase *)((char *)RHMalignityField<void *>(actor, 0x50) + 4))->Current();
    return ((RHMalignityPathGeometry *)g_unk0x6c0a9c)->FUN_004f9170(VirtualBase().FUN_0040cbf0(position),
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

// GLOBAL: GAME 0x00677588
float g_unk0x00677588 = 250000.0f;

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
        if (VirtualBase().FUN_0041a010(actor) < g_unk0x00677588)
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

RHMalignityHeadingPoint FUN_0040ec20(const SBGeoPoint2D &first, RHMalignityPosition second);

// FUNCTION: GAME 0x00449810
bool RHArtificialMalignity::FUN_00449810(const RHMalignityPosition &position, unsigned short heading)
{
    unsigned short count = (unsigned short)M(RHMalignityList, 0x2e4).size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityList &list = M(RHMalignityList, 0x2e4);
        list.FUN_005c8e40(index);
        void *actor = list.m_current->value;
        switch ((heading - FUN_0040ec20(VirtualBase().FUN_0040cc20(actor), position).FUN_005fcc50(0.57357645f)) & 0xf)
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

class RHMalignityAbilityCalls
{
public:
    unsigned short FUN_005c1b50(int index);
};

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
        !(RHMalignityField<RHMalignityAbilityCalls *>(VirtualBase().m_actor, 0x25c)->FUN_005c1b50(2) < distance))
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
        if (actor == VirtualBase().m_actor)
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
    ((RHScriptBatchCalls *)&VirtualBase())->Unk00419fb0(3);
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

// GLOBAL: GAME 0x00677590
float g_unk0x00677590 = 40000.0f;

// GLOBAL: GAME 0x006775bc
float g_unk0x006775bc = 122500.0f;

// Parked: loop-exhaustion branches and alert-tail epilogue placement differ.
// STUB: GAME 0x0044b000
void RHArtificialMalignity::FUN_0044b000()
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    if (RHMalignityField<int>(M(void *, 0x334), 0x58) != 0)
        return;
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors.size();
    void *actor;
    unsigned short index;
    for (index = 0; ; ++index)
    {
        if (index >= count)
            return;
        actor = RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4d00)[team].actors[index];
        if (RHMalignityField<int>(RHMalignityField<void *>(actor, 0xa1c), 0x58) != 1)
            continue;
        char *base = (char *)actor + RHMalignityField<int *>(actor, 0x49c)[1];
        if (RHMalignityField<int>(base, 0x4a8) != 1 && RHMalignityField<int>(base, 0x4b0) != 0x29)
            continue;
        float distance = VirtualBase().FUN_0041a010(actor);
        if (distance < g_unk0x00677590 ||
            (distance < g_unk0x006775bc ? ((RHMalignityActorCalls *)actor)->FUN_0048a350(VirtualBase().m_actor)
                                        : ((RHScriptBatchCalls *)actor)->Unk00489e80(VirtualBase().m_actor)))
            break;
    }
    ((RHMalignityAlertCalls *)((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1] + 0x49c))->FUN_0042c890(0x21, VirtualBase().m_actor);
}

// GLOBAL: GAME 0x00677430
float g_unk0x00677430 = 150.0f;

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
            if (FUN_0040ec20(VirtualBase().FUN_004165e0(actor, true), position).FUN_005fc700(1.0f) < g_unk0x00677430)
                return true;
        }
    }
    return false;
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

class RHMalignityAreaCalls
{
public:
    bool FUN_0060be00(const void *point);
};

// FUNCTION: GAME 0x0044b870
bool RHArtificialMalignity::FUN_0044b870(void *area, unsigned short id)
{
    int team = ((RHMalignityActorCalls *)VirtualBase().m_actor)->V130();
    unsigned short count = (unsigned short)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityTargetCalls *actor = (RHMalignityTargetCalls *)RHMalignityField<RHMalignityTeam[1]>(g_pEngine, 0x4cc0)[team].actors[index];
        if (actor != VirtualBase().m_actor &&
            RHMalignityField<unsigned short>(RHMalignityField<void *>(actor, 0x50), 0xde) == id &&
            !actor->V048() && !RHMalignityField<bool>(actor, 0x1ce) &&
            ((RHMalignityAreaCalls *)area)->FUN_0060be00((char *)RHMalignityField<void *>(actor, 0x50) + 0x24))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0044ca90
void RHArtificialMalignity::FUN_0044ca90()
{
    FUN_00430020();
    if (!M(void *, 0x2ec))
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
        RHMalignityField<RHArtificialIntelligencePathCursor>((char *)actor + RHMalignityField<int *>(actor, 0x49c)[1], 0x4cc)
            .Unk00550f60(RHMalignityField<unsigned short>(&ai->VirtualBase(), 0xa));
        RHMalignityField<bool>(&ai->VirtualBase(), 0x70) = true;
    }
    if (RHMalignityField<int>(&ai->VirtualBase(), 0xc) == 1)
        ai->VirtualBase().V00(0);
}

#include "RHMalignityVisibilityCalls.h"

// Parked: front-removal iterator temporaries and conditional callee saves differ.
// STUB: GAME 0x0044cf00
bool RHArtificialMalignity::FUN_0044cf00()
{
    while (M(RHMalignityList, 0x54).m_count > 0)
    {
        RHMalignityList &list = M(RHMalignityList, 0x54);
        list.FUN_005c8e40(0);
        if (((RHMalignityVisibilityCalls *)list.m_current->value)->FUN_004860b0())
            break;
        RHSectorActorIter position((RHSectorActorNode *)list.m_head->next);
        RHMalignityNode *removed = (RHMalignityNode *)(position++).m_p;
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        FUN_0064158f(removed);
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
    FUN_0064158f(removed);
    --list.m_count;
    list.m_dirty = true;
    FUN_0044a760(RHMalignityField<void *>(&VirtualBase(), 0x88));
    return true;
}

class RHElementActor
{
public:
    bool FUN_0046d710();
};

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
        ((RHScriptBatchCalls *)&VirtualBase())->Unk0040d980(4);
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
    FUN_00478c20(origin, false);
    difference = point.FUN_005df550(origin);
    float scaled = difference.y;
    scaled *= g_unk0x006774ec;
    difference.y = scaled;
    float z = difference.z;
    int range = RHMalignityField<unsigned short>(this, 0x6cc);
    if (difference.x * difference.x + scaled * scaled + z * z > range * range)
        return false;
    return ((RHMalignityGeometryCalls *)RHMalignityField<void *>(this, 0x64))->FUN_004eff80(origin, point, 2);
}

// Parked: case-zero flag masks and shared rejection branches schedule differently.
// STUB: GAME 0x0048c700
void RHMalignityActorCalls::FUN_0048c700(void *actor, unsigned mode)
{
    RHMalignityMessage message;
    switch (mode)
    {
    case 0:
        if (V130() == 0)
        {
            unsigned type = RHMalignityField<volatile unsigned>(this, 4) & 31;
            if ((unsigned char)type == 20)
            {
                if ((unsigned char)(RHMalignityField<volatile unsigned>(actor, 4) & 31) != (unsigned char)type ||
                    ((RHMalignityActorCalls *)actor)->V130() != 1)
                    return;
            }
            else if ((unsigned char)(RHMalignityField<volatile unsigned>(actor, 4) & 15) != 12)
                return;
        }
        else
        {
            unsigned type = RHMalignityField<volatile unsigned>(this, 4) & 31;
            if ((unsigned char)type == 20)
            {
                if (((unsigned char)(RHMalignityField<volatile unsigned>(actor, 4) & 31) != (unsigned char)type ||
                     ((RHMalignityActorCalls *)actor)->V130() != 0) &&
                    (unsigned char)(RHMalignityField<volatile unsigned>(actor, 4) & 15) != 12)
                    return;
            }
            else if ((unsigned char)(RHMalignityField<volatile unsigned>(actor, 4) & 15) != 12)
                return;
        }
        message.type = 0;
        message.actor = actor;
        break;
    case 1:
        message.type = 3;
        message.actor = actor;
        break;
    case 2:
        message.type = 4;
        message.actor = actor;
        break;
    case 3:
        if (RHMalignityField<bool>(actor, 0x23f) && FUN_0048c8e0(actor, true) == 1)
            return;
        message.type = 1;
        message.actor = actor;
        break;
    case 4:
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

// Parked: cached-cursor erase and return-register scheduling still differ.
// STUB: GAME 0x0048ca20
unsigned char RHMalignityActorCalls::FUN_0048ca20(void *actor, unsigned mode)
{
    RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x504 + mode * 0x34);
    unsigned short count = (unsigned short)list.m_count;
    for (unsigned short index = 0; index < count; ++index)
    {
        list.FUN_005c8e40(index);
        RHMalignityMessageNode *node = (RHMalignityMessageNode *)list.m_current;
        if (node->value.actor == actor)
        {
            RHMalignityNode *removed = list.m_current;
            RHMalignityNode *next = removed->next;
            removed->previous->next = next;
            next->previous = removed->previous;
            FUN_0064158f(removed);
            --list.m_count;
            list.m_dirty = true;
            return true;
        }
    }
    return false;
}

// Parked: compiler register assignment and the target's global-pointer access differ.
// STUB: GAME 0x0048cbc0
void RHScriptBatchCalls::Unk0048cbc0()
{
    int *first = RHMalignityField<int *>(g_pEngine, 0x495c);
    int *last = RHMalignityField<int *>(g_pEngine, 0x4960);
    unsigned count = first ? (unsigned)(last - first) : 0;
    if ((short)count != 0)
    {
        unsigned remaining = count & 0xffff;
        int *cursor = first;
        do
        {
            ((RHMalignityActorCalls *)*cursor)->FUN_0048cb90(this);
            ++cursor;
            --remaining;
        } while (remaining != 0);
    }
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
void FUN_0048cc20(void *value)
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
void RHMalignityActorCalls::FUN_0048d050()
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

// Parked: list iteration, tagged geometry, map bounds, EH cleanup, and hazard-dependent radius adjustment are unreconstructed.
// STUB: GAME 0x0048e420
void RHMalignityActorCalls::FUN_0048e420(void *actor)
{
    RHMalignityList &list = RHMalignityField<RHMalignityList>(this, 0x504);
    int count = list.m_count;
    int index = 0;
    if (actor)
    {
        for (; index < count; ++index)
        {
            list.FUN_005c8e40(index);
            if (list.m_current->value == actor)
                break;
        }
    }
    if (list.m_dirty)
    {
        list.m_current = list.m_head->next;
        FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, index, std::bidirectional_iterator_tag());
        list.m_dirty = false;
    }
    else if (index != list.m_index)
    {
        int previous = list.m_index;
        if (index < previous)
        {
            if (index < (previous + 1) / 2)
            {
                list.m_current = list.m_head->next;
                FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, index, std::bidirectional_iterator_tag());
            }
            else
                FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, index - previous, std::bidirectional_iterator_tag());
        }
        else if (index < (previous + count) / 2)
            FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, index - previous, std::bidirectional_iterator_tag());
        else
        {
            list.m_current = list.m_head;
            FUN_005c9010((RHUnk005c9010Iterator &)list.m_current, index - count, std::bidirectional_iterator_tag());
        }
        list.m_index = index;
    }
    if (list.m_current && list.m_current != list.m_head)
        RHMalignityField<unsigned char>(list.m_current->value, 0x12) = 0;
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

// Reconstructed gates and actor-profile checks; geometry, event allocation and dispatch remain incomplete.
// STUB: GAME 0x0048e670
bool RHMalignityActorCalls::FUN_0048e670(void *actor)
{
    if (RHMalignityField<unsigned char>(this, 0x652))
        return false;
    void *profile = RHMalignityField<void *>(this, 0x50);
    void *base = (char *)this + (*(int **)RHMalignityField<void *>(this, 0x49c))[1];
    if (RHMalignityField<int>(base, 0x4a8) != 1)
        return false;
    if ((RHMalignityField<unsigned>(this, 4) & 31) == 0x14 || RHMalignityField<unsigned>(this, 0x4f0) < 200)
        return false;
    if (RHMalignityField<float>(profile, 0x10) == RHMalignityField<float>(profile, 0x2c) &&
        RHMalignityField<float>(profile, 0x14) == RHMalignityField<float>(profile, 0x30) &&
        RHMalignityField<float>(profile, 0x18) == RHMalignityField<float>(profile, 0x34))
        return false;
    void *otherProfile = RHMalignityField<void *>(actor, 0x50);
    if ((RHMalignityField<unsigned>(actor, 4) & 0xf) == 0xc &&
        RHMalignityField<unsigned char>(base, 0x7e4) == 1)
        return false;
    if (RHMalignityField<void *>(profile, 0xe0) != RHMalignityField<void *>(otherProfile, 0xe0))
        return false;
    RHMalignityPosition own = RHMalignityPositionOf(profile);
    RHMalignityPosition other = RHMalignityPositionOf(otherProfile);
    SBGeoPoint2D displacement = FUN_0040ec20(own, other);
    if (displacement.FUN_005fc700(1.0f) > 70.0f)
        return false;
    unsigned difference = (RHMalignityHeading(actor) - 0x0c) & 0xf;
    return difference < 2 || difference == 0xf;
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
    if (delta.FUN_005fc700(1.0f) >= g_unk0x00677488)
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

// Parked: cursor comparisons merge into memory operands and edi is saved unconditionally.
// STUB: GAME 0x004b8f80
int RHSectorActorList::Unk004b8f80(RHElementActor *const &value, bool mode)
{
    m_value = value;
    int count = m_count;
    if (mode == true)
    {
        m_forward = true;
        m_current = m_head->next;
        int index;
        for (index = 0; index < count; ++index)
        {
            if (m_current->value == m_value)
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
        m_result = -1;
        m_dirty = true;
        return m_result;
    }
    m_forward = false;
    m_current = m_head;
    m_current = m_current->previous;
    while (count > 0)
    {
        if (m_current->value == m_value)
            break;
        m_current = m_current->previous;
        --count;
    }
    if (count > 0)
    {
        --count;
        m_dirty = false;
        m_result = count;
        m_index = count;
        return count;
    }
    m_result = -1;
    m_dirty = true;
    return m_result;
}

class RHMalignitySegmentTemporary
{
public:
    RHMalignitySegmentTemporary(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((RHMobileUnk0060a820 *)this)->FUN_0060a820(first, second);
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

// Parked: frame is sixteen bytes too small; query-list and geometry cleanup layouts differ.
// STUB: GAME 0x004f5e50
bool RHMalignityGridCalls::FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer)
{
    RHMalignityQueryList lines;
    for (unsigned short attempt = 0; attempt < 50; ++attempt)
    {
        FUN_004ed370(lines, layer, RHMalignitySegmentTemporary(box.FUN_00608f40(), point).Value(), 2);
        FUN_004ed070(lines, layer, box, 2);
        unsigned short count = lines.m_count;
        if (count == 0)
            return true;
        for (unsigned short index = 0; index < count; ++index)
        {
            ((RHSectorActorList *)&lines)->Unk005c8e40(index);
            void *line = lines.m_current->value;
            SBGeoPoint2D &anchor = RHMalignityField<SBGeoPoint2D>(line, 4);
            SBGeoVector2D &normal = RHMalignityField<SBGeoVector2D>(line, 0x34);
            if (normal.FUN_005fc660(anchor.Unk005fc110(point)) > g_unk0x00677488)
            {
                float distance = normal.FUN_005fc660(anchor.Unk005fc110(RHMalignityField<SBGeoPoint2D>(&box, 0)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(RHMalignityField<SBGeoPoint2D>(&box, 8)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(SBGeoPoint2D(RHMalignityField<float>(&box, 8), RHMalignityField<float>(&box, 4))));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, normal));
                distance = normal.FUN_005fc660(anchor.Unk005fc110(SBGeoPoint2D(RHMalignityField<float>(&box, 0), RHMalignityField<float>(&box, 0x0c))));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, normal));
            }
        }
        RHMalignityNode *head = lines.m_head;
        RHMalignityNode *it = head->next;
        while (it != head)
        {
            RHMalignityNode *node = it;
            it = it->next;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
            --lines.m_count;
        }
        lines.m_dirty = true;
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

// FUNCTION: GAME 0x00521770
RHUnk00521770 *RHUnk00521770::FUN_00521770()
{
    undefined allocator;
    m_18 = allocator;
    m_1c = 0;
    m_20 = 0;
    m_24 = 0;
    m_2c = true;
    m_vtable = 0x679134;
    m_14 = 0;
    m_0c = 0;
    m_39 = false;
    return this;
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
    FUN_00445b40();
    FUN_004461a0(0, 0);
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
    ((RHMalignityOwnedList *)this)->FUN_004e65b0();
    ((RHCampaignIndexList<false> *)this)->FUN_004fe2e0(RHScriptIter(0), *(unsigned short *)this);
    ((RHUnk00521770 *)this)->FUN_00521770();
    ((RHMalignityEngineCalls *)this)->FUN_004da8d0(*(SBGeoBoundingBox2D *)this);
    ((RHMalignityGridCalls *)this)->FUN_004f5e50(*(SBGeoBoundingBox2D *)this, *(SBGeoPoint2D *)this, 0);
}
