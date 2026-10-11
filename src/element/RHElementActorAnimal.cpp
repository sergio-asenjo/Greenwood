#include "RHElementActorAnimal.h"
#include <stdlib.h>

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHAnimalNoisePosition, 0x10)
DECOMP_SIZE_ASSERT(RHAnimalSprite, 0xe4)
DECOMP_SIZE_ASSERT(RHElementActorAnimal, 0x220)

// GLOBAL: GAME 0x006ae2e4
unsigned short RHElementActorAnimal::marrWalkDistance[9] = {20, 80, 60, 5, 20, 10, 60, 10, 80};
// GLOBAL: GAME 0x006ae2f8
unsigned short RHElementActorAnimal::marrWaitTime[9] = {50, 20, 50, 10, 20, 10, 80, 10, 50};
// GLOBAL: GAME 0x006ae30c
unsigned short RHElementActorAnimal::marrMaxTurnAngle[9] = {2, 4, 1, 8, 3, 7, 1, 6, 2};
// GLOBAL: GAME 0x006ae320
unsigned short RHElementActorAnimal::marrRunProbability[9] = {5, 40, 5, 0, 30, 20, 10, 50, 30};
// GLOBAL: GAME 0x006ae334
unsigned short RHElementActorAnimal::marrTerritoryEdgeLength[9] = {0xffff, 0xffff, 200, 80, 50, 0xffff, 50, 0xffff, 0xffff};
// GLOBAL: GAME 0x006ae348
unsigned short RHElementActorAnimal::marrStartleBoxEdgeLength[9] = {0, 20, 0, 30, 0, 50, 0, 0, 0};
// GLOBAL: GAME 0x006ae35c
unsigned short RHElementActorAnimal::marrRestlessBoxEdgeLength[9] = {0, 200, 0, 200, 50, 50, 0, 0, 0};

// FUNCTION: GAME 0x0046ec50
void RHElementActorAnimal::Think(RHanimalStimulusType stimulus)
{
    if (m_1c5)
        return;
    switch (m_1d4)
    {
    case 0:
        switch (stimulus)
        {
        case 5:
            GetRestless();
            break;
        case 1:
            ThisIsYourNewHome();
            break;
        case 3:
            WalkSomewhere();
            break;
        case 4:
            Startle();
            break;
        }
        break;
    case 1:
        switch (stimulus)
        {
        case 0:
            if (m_21c)
                WalkSomewhere();
            else
                m_1d4 = 0;
            break;
        case 1:
            ThisIsYourNewHome();
            break;
        case 3:
            WalkSomewhere();
            break;
        case 4:
            Startle();
            break;
        case 5:
            GetRestless();
            break;
        }
        break;
    case 2:
        switch (stimulus)
        {
        case 0:
            m_1d4 = 0;
            break;
        case 1:
            ThisIsYourNewHome();
            break;
        case 4:
            Startle();
            break;
        case 5:
            GetRestless();
            break;
        }
        break;
    case 3:
        switch (stimulus)
        {
        case 0:
            m_1d4 = 0;
            break;
        case 1:
            ThisIsYourNewHome();
            break;
        case 4:
            Startle();
            break;
        case 5:
            GetRestless();
            break;
        }
        break;
    case 4:
    case 5:
        switch (stimulus)
        {
        case 0:
            if (m_1d0 != 0 && m_1d0 != 7)
                Flee(false);
            else
                m_1d4 = 0;
            break;
        case 1:
            ThisIsYourNewHome();
            break;
        case 6:
            m_1d4 = 5;
            Flee(false);
            break;
        }
        break;
    }
    if (m_1bc != m_1d4)
        m_1b8 = 0;
}

// FUNCTION: GAME 0x0046edd0
bool RHElementActorAnimal::GoTo(const SBGeoPoint2D &destination, unsigned short flags)
{
    if (destination.m_x > g_unk0x00677488 && g_pEngine->m_4730 > destination.m_x &&
        destination.m_y > g_unk0x00677488 && g_pEngine->m_4734 > destination.m_y)
    {
        if (flags & 0x10)
        {
            RHUnkPathActorInfoBase *position = m_50->Position();
            void *box = position->Unk0055fa10(position->m_88);
            if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9170(m_50->m_24, destination, m_50->m_de, box))
                return false;
        }
        int animation;
        if (!(flags & 8) && (flags & 1) &&
            ((RHAnimalConversion *)((RHUnk005b5e00 *)m_50)->Unk())->m_4->m_14 != 0xffff)
            animation = 10;
        else
            animation = 6;
        m_5c->Unk0058a940(g_unk0x6c0560, 0, new RHUnk005883a0(1, 0x14, this, animation, destination, 0, 0.0f, 0));
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0046ef30
void RHElementActorAnimal::WalkSomewhere()
{
    RHUnk005fc3b0 direction;
    unsigned short species = m_1d0;
    if (!m_1e0.FUN_00608400(m_50->m_24))
    {
        GoTo(m_1e0.FUN_00608f40(), 0);
        m_1d4 = 2;
        m_1da = rand() % marrWaitTime[species];
    }
    else
    {
        unsigned char turn = (unsigned char)marrMaxTurnAngle[species] + (unsigned char)m_1dc;
        char delta = rand() % (turn * 2 + 1) - turn;
        unsigned short heading = m_50->m_d8;
        unsigned char sector = (heading + delta) & 0xf;
        unsigned short walk = marrWalkDistance[species];
        unsigned short distance = rand() % walk + walk / 5;
        unsigned short flags;
        if (!m_21c && rand() % 100 >= marrRunProbability[species])
        {
            flags = 0x14;
        }
        else
        {
            flags = 0x15;
            distance += walk;
        }
        direction.Unk005fcd40(sector, 1.0f);
        direction.FUN_005fc4d0(distance);
        if (GoTo(m_50->m_24.Unk005fc190(direction), flags))
        {
            if (m_1d4 == 0)
            {
                m_1d4 = 2;
                m_1da = rand() % marrWaitTime[species];
            }
            else
                m_1dc = 0;
        }
        else if (m_1dc < 8)
        {
            m_1da = 0;
            m_1dc++;
        }
    }
}

// FUNCTION: GAME 0x0046f160
void RHElementActorAnimal::Startle()
{
    RHUnk005fc3b0 direction;
    switch (m_1d0)
    {
    case 1:
    case 3:
    case 5:
        direction.FUN_005fc430(m_50->m_24.Unk005fc110(m_1c8));
        if (direction.m_x != g_unk0x00677488 || direction.m_y != g_unk0x00677488)
        {
            direction.FUN_005fc7c0(1.0f);
            direction.FUN_005fc4d0(marrWalkDistance[m_1d0]);
            GoTo(m_50->m_24.Unk005fc190(direction), 0x15);
            m_1d4 = 3;
        }
        break;
    }
}

// Parked 97.70%: the m_de word copy picks dx where the target reuses cx.
// STUB: GAME 0x0046f290
void RHElementActorAnimal::GetRestless()
{
    bool noise;
    float radius;
    SBGeoPoint2D point;
    point = m_50->m_24;
    RHAnimalNoisePosition position;
    position.m_x = point.m_x;
    position.m_y = point.m_y;
    position.m_8 = m_50->m_e0;
    position.m_c = m_50->m_de;
    int species = m_1d0;
    switch (species)
    {
    case 5:
        radius = m_50->m_18;
        RHElementActorNPC::Noise(5, position, radius, 0);
        noise = true;
        break;
    case 3:
        radius = m_50->m_18;
        RHElementActorNPC::Noise(6, position, radius, 0);
        noise = true;
        break;
    case 1:
        radius = m_50->m_18;
        RHElementActorNPC::Noise(4, position, radius, 0);
        noise = true;
        break;
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
        noise = false;
        break;
    }
    if (noise)
    {
        m_1d4 = 1;
        Think((RHanimalStimulusType)0);
    }
}

// Not attempted: 0x726-byte RHSequence builder with several EH-guarded allocations.
// STUB: GAME 0x0046f3c0
void RHElementActorAnimal::Flee(bool run)
{
}

// Not attempted: std::list local frame and nine-argument path query 0x4f9a80.
// STUB: GAME 0x0046faf0
void *RHElementActorAnimal::GetNearestSeekPoint(unsigned short layer)
{
    return 0;
}

// FUNCTION: GAME 0x0046fe00
void RHElementActorAnimal::ThisIsYourNewHome()
{
    RHUnk005fc3b0 half;
    float length = (unsigned short)(marrTerritoryEdgeLength[m_1d0] >> 1);
    half.FUN_005fc430(SBGeoVector2D(length, length));
    m_1e0.FUN_00607da0(SBGeoBoundingBox2D(m_50->m_24.FUN_005fc200(half), m_50->m_24.Unk005fc190(half)));
}
