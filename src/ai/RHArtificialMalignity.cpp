#include "RHArtificialMalignity.h"
#include <stdlib.h>

// GLOBAL: GAME 0x006c0754
bool g_unk0x006c0754 = false;

// GLOBAL: GAME 0x006c0788
bool g_unk0x006c0788 = false;

// GLOBAL: GAME 0x006c08a4
unsigned *g_unk0x006c08a4 = 0;

// GLOBAL: GAME 0x006774e4
float g_unk0x006774e4 = 15.0f;

#define M(type, offset) RHMalignityField<type>(this, offset)
#define B(type, offset) RHMalignityField<type>(&Base(), offset)
#define A(type, offset) RHMalignityField<type>(Base().m_actor, offset)
#define F(type, offset) RHMalignityField<type>(B(void *, 0x1fc), offset)
#define S(type, offset) RHMalignityField<type>(B(void *, 0x200), offset)
#define FA(type, offset) RHMalignityField<type>((char *)B(void *, 0x1fc) + ((int *)F(void *, 0x49c))[1], offset)
#define SA(type, offset) RHMalignityField<type>((char *)B(void *, 0x200) + ((int *)S(void *, 0x49c))[1], offset)
#define AA(type, offset) RHMalignityField<type>((char *)Base().m_actor + ((int *)A(void *, 0x49c))[1], offset)
#define RESET() ((RHArtificialIntelligence *)&Base())->Unk00410010(false)

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
            int value = ((RHMalignityOwnerCalls *)((char *)this - 0x358))->FUN_00438710(actor->Vcc());
            ((RHMalignityActorCalls *)Base().m_actor)->Vd4(value, 0.5f, 1.5f, 10000, false, false);
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

void RHArtificialMalignity::Emit(SBFile &file)
{
    InitOneAI();
    SerializeExactlyThisAI(file);
    InitializeFriendCheck(0, 0, 0);
}

bool RHMalignityBaseView::FUN_00419e10(void *) { return false; }
void RHMalignityBaseView::FUN_0041ab30() {}
int RHMalignityOwnerCalls::FUN_00438710(unsigned value) { return value; }
void RHMalignityActorCalls::FUN_0048c700(void *, bool) {}
void RHMalignityActorCalls::FUN_0048d050() {}
void RHMalignityActorCalls::FUN_0048ebe0() {}
