#include "SBNullstr.h"
#include "RHArtificialMalignity.h"
#include <stdlib.h>
#include <new>

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityPosition, 0x10)
DECOMP_SIZE_ASSERT(RHMalignityArray, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityNode, 0x0c)
DECOMP_SIZE_ASSERT(RHMalignityList, 0x18)
DECOMP_SIZE_ASSERT(RHSectorActorList, 0x24)
DECOMP_SIZE_ASSERT(RHMalignityOwnedList, 0x10)
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

// STUB: GAME 0x00414360
RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode)
{
    SBGeoPoint2D point;
    RHUnk00613e90 result;
    point.m_x = position.x;
    point.m_y = position.y;
    void *projection = 0;
    void *area = position.area;
    if (area && ((RHMalignityField<unsigned>(area, 0x30) >> 1) & 1) &&
        (RHMalignityField<unsigned>(area, 0x30) & 1))
    {
        if (!((RHMalignityField<unsigned>(area, 0x30) >> 13) & 1))
            projection = ((RHActorAreaCalls *)area)->FUN_0057d800(point);
        else
        {
            RHMalignityList &list = RHMalignityField<RHMalignityList>(area, 0x5c);
            unsigned short count = list.m_count;
            void *candidate = 0;
            unsigned short index;
            for (index = 0; index < count; ++index)
            {
                ((RHSectorActorList *)&list)->Unk005c8e40(index);
                candidate = list.m_current->value;
                RHMalignityPosition location;
                location.x = RHMalignityField<float>(candidate, 0x20);
                location.y = RHMalignityField<float>(candidate, 0x24);
                location.area = RHMalignityField<void *>(candidate, 0x10);
                location.layer = RHMalignityField<unsigned short>(candidate, 0x16);
                bool close = FUN_0040ec20(location, position).FUN_005fc700(1.0f) < g_unk0x006774a0;
                if (close)
                    break;
            }
            if (index < count && candidate)
                projection = ((RHActorAreaCalls *)RHMalignityField<void *>(candidate, 0x0c))->FUN_0057d800(RHMalignityField<SBGeoPoint2D>(candidate, 0x18));
        }
    }
    float height;
    if (projection)
        height = (RHMalignityField<float>(projection, 0xf4) * position.x +
                  RHMalignityField<float>(projection, 0xf8) * position.y +
                  RHMalignityField<float>(projection, 0xfc)) /
                 (g_unk0x0067749c - RHMalignityField<float>(projection, 0xf8));
    else
        height = g_unk0x00677488;
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

// STUB: GAME 0x0041ab30
void RHMalignityBaseView::FUN_0041ab30()
{
    RHMalignityList &first = RHMalignityField<RHMalignityList>(this, 0x2b4);
    ((RHAIUnk0044e8b0 *)&first)->FUN_0044e8b0(RHMalignityIterator(first.m_head->next), RHMalignityIterator(first.m_head));
    first.m_dirty = true;
    RHMalignityList &second = RHMalignityField<RHMalignityList>(this, 0x2d8);
    ((RHAIUnk0044e8b0 *)&second)->FUN_0044e8b0(RHMalignityIterator(second.m_head->next), RHMalignityIterator(second.m_head));
    second.m_dirty = true;
    RHMalignityList &third = RHMalignityField<RHMalignityList>(this, 0x2fc);
    unsigned short count = RHMalignityField<RHMalignityList>(this, 0x320).m_count;
    ((RHAIUnk0044e8b0 *)&third)->FUN_0044e8b0(RHMalignityIterator(third.m_head->next), RHMalignityIterator(third.m_head));
    third.m_dirty = true;
    RHMalignityList &indices = RHMalignityField<RHMalignityList>(this, 0x320);
    for (unsigned short index = 0; index < count; ++index)
    {
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
    firstCalls.FUN_0044e8b0(firstCalls.FUN_0046eb80(), RHMalignityIterator(first.m_head));
    first.m_dirty = true;
    RHMalignityList &second = RHMalignityField<RHMalignityList>(this, 0x2d8);
    RHAIUnk0044e8b0 &secondCalls = *(RHAIUnk0044e8b0 *)&second;
    secondCalls.FUN_0044e8b0(secondCalls.FUN_0046eb80(), RHMalignityIterator(second.m_head));
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

// STUB: GAME 0x00438710
unsigned short RHMalignityOwnerCalls::FUN_00438710(unsigned short value, float low, float high, unsigned short maximum)
{
    RHMalignityBaseView *base = (RHMalignityBaseView *)((char *)this + (*(int **)this)[1]);
    if (((RHMalignityActorCalls *)base->m_actor)->V130() == 1)
    {
        switch (RHMalignityField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c))
        {
        case 0:
        {
            float scaled = value * low;
            return (unsigned short)(maximum < scaled ? maximum : scaled);
        }
        case 2:
        {
            float scaled = value * high;
            return (unsigned short)(maximum < scaled ? maximum : scaled);
        }
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

// STUB: GAME 0x0048a260
bool RHMalignityActorCalls::FUN_0048a260(const RHUnk00613e90 &point)
{
    RHUnk00613e90 difference;
    RHUnk00613e90 origin;
    RHUnk00613e90 unused;
    void *profile = RHMalignityField<void *>(this, 0x50);
    void *area = RHMalignityField<void *>(profile, 0xe0);
    if ((RHMalignityField<unsigned>(area, 0x30) >> 13) & 1)
        return false;
    FUN_00478c20(origin, false);
    difference = ((RHMalignityVectorCalls *)&point)->FUN_005df550(origin);
    difference.y *= g_unk0x006774ec;
    int range = RHMalignityField<unsigned short>(this, 0x6cc);
    if (range * range < difference.z * difference.z + difference.y * difference.y + difference.x * difference.x)
        return false;
    return ((RHMalignityGeometryCalls *)RHMalignityField<void *>(this, 0x64))->FUN_004eff80(origin, point, 2);
}

// STUB: GAME 0x0048c700
void RHMalignityActorCalls::FUN_0048c700(void *actor, unsigned mode)
{
    RHMalignityMessage message;
    switch (mode)
    {
    case 0:
        if (V130() == 0)
        {
            if ((unsigned char)(RHMalignityField<unsigned>(this, 4) & 31) == 20)
            {
                if ((unsigned char)(RHMalignityField<unsigned>(actor, 4) & 31) != 20 ||
                    ((RHMalignityActorCalls *)actor)->V130() != 1)
                    return;
            }
            else if ((unsigned char)(RHMalignityField<unsigned>(actor, 4) & 15) != 12)
                return;
        }
        else if ((unsigned char)(RHMalignityField<unsigned>(this, 4) & 31) == 20)
        {
            if (((unsigned char)(RHMalignityField<unsigned>(actor, 4) & 31) != 20 ||
                 ((RHMalignityActorCalls *)actor)->V130() != 0) &&
                (unsigned char)(RHMalignityField<unsigned>(actor, 4) & 15) != 12)
                return;
        }
        else if ((unsigned char)(RHMalignityField<unsigned>(actor, 4) & 15) != 12)
            return;
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

// STUB: GAME 0x0048d050
void RHMalignityActorCalls::FUN_0048d050()
{
    SBGeoPoint2D point;
    void *profile = RHMalignityField<void *>(this, 0x50);
    RHMalignityField<RHUnk005fc3b0>(this, 0x4d4).Unk005fcd40(RHMalignityField<unsigned short>(profile, 0xd8), 1.0f);
    point = RHMalignityField<SBGeoPoint2D>(RHMalignityField<void *>(this, 0x50), 0x24);
    RHMalignityField<undefined4>(this, 0x4e0) = RHMalignityField<undefined4>(&point, 4);
    RHMalignityField<undefined4>(this, 0x4dc) = RHMalignityField<undefined4>(&point, 0);
    profile = RHMalignityField<void *>(this, 0x50);
    RHMalignityField<unsigned short>(this, 0x4e8) = RHMalignityField<unsigned short>(profile, 0xde);
    RHMalignityField<void *>(this, 0x4e4) = RHMalignityField<void *>(profile, 0xe0);
}

// FUNCTION: GAME 0x0048ebe0
void RHMalignityActorCalls::FUN_0048ebe0()
{
    unsigned short value = RHMalignityField<unsigned short>(g_pEngine, 0x4cc0);
    RHMalignityField<unsigned short>(this, 0x6c0) = value;
    RHMalignityField<unsigned short>(this, 0x6c2) = value;
}

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
    y = RHMalignityField<float>((void *)&box, 4);
    fourth.m_y = y;
    fourth.m_x = RHMalignityField<float>((void *)&box, 8);
    RHMalignityRectangle *rectangle = new RHMalignityRectangle;
    RHMalignityArrayCalls &indices = *(RHMalignityArrayCalls *)((char *)rectangle + 0x2c);
    unsigned zero = 0;
    indices.FUN_0059fba0(zero);
    RHMalignityField<bool>(&indices, 0x14) = true;
    RHMalignityField<unsigned>(rectangle, 0x4c) = 0;
    RHMalignityArrayCalls &edges = *(RHMalignityArrayCalls *)rectangle;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegment(first, second));
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegment(second, third));
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegment(third, fourth));
    RHMalignityField<bool>(rectangle, 0x14) = true;
    edges.FUN_004e62b0(RHMalignityField<void *>(rectangle, 8), 1, RHMalignitySegment(fourth, first));
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

// TEMPLATE: GAME 0x004e60a0
// ?insert@?$vector@GV?$allocator@G@std@@@std@@QAEXPAGIABG@Z

// STUB: GAME 0x004e65b0
void RHMalignityOwnedList::FUN_004e65b0()
{
    m_current = m_head->next;
    while (m_current != m_head)
    {
        if (m_current->value)
            operator delete(m_current->value);
        m_current = m_current->next;
    }
    RHMalignityNode *head = m_head;
    RHMalignityNode *it = head->next;
    while (it != head)
    {
        RHMalignityNode *node = it;
        it = it->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        delete node;
        --m_count;
    }
}

// STUB: GAME 0x004f5e50
bool RHMalignityGridCalls::FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer)
{
    RHMalignityQueryList lines;
    for (unsigned short attempt = 0; attempt < 50; ++attempt)
    {
        FUN_004ed370(lines, layer, RHMalignitySegment(box.FUN_00608f40(), point), 2);
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
    InitOneAI();
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
