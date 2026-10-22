#include "SBNullstr.h"
#include "RHMask.h"
#include "RHGame.h"
#include "RHGameMenuCalls.h"
#include "RHMenuCloseCalls.h"

// STRING: GAME 0x006b08ac
static const char *RHMaskFile = "P:\\Robin Hood\\RHmask.cpp";
// STRING: GAME 0x006b08c8
static const char *RHMaskObstacleError = "VERBOTEN : Obstacle-mask with no obstacle associated !";

// FUNCTION: GAME 0x00523b20
RHMask::RHMask()
{
    m_data = 0;
    m_size = 0;
    m_00 = true;
}

// FUNCTION: GAME 0x00523c60
RHMask::~RHMask()
{
    delete[] m_data;
}

// Parked: shared 0x59fb00 stub is thiscall, target is cdecl.
// STUB: GAME 0x00523df0
void RHMask::InitializeFromProtoStream(SBFile &file, RHFastFindGrid *grid)
{
    unsigned long flags;
    char marker;
    unsigned short count;
    short x, y;
    unsigned short obstacleCount;
    unsigned long obstacleIndex;
    file.Access(&flags, 1);
    m_flags = flags & 0xff;
    unsigned int bytes = 1;
    if (m_flags & 1)
    {
        file.Access(&marker, 1);
        file.Access(&count, 2);
        bytes = 3;
        for (unsigned short i = 0; i < count; ++i)
        {
            file.Access(&x, 2);
            file.Access(&y, 2);
            bytes += 4;
            m_points28.InsertLast(SBGeoPoint2D((float)x, (float)y));
            if (i == 0)
                m_1c = (float)y;
            else if ((float)y > m_1c)
                m_1c = (float)y;
        }
        file.Access(&marker, 1);
    }
    if ((m_flags >> 1) & 1)
    {
        file.Access(&marker, 1);
        file.Access(&count, 2);
        bytes += 2;
        for (unsigned short i = 0; i < count; ++i)
        {
            file.Access(&x, 2);
            file.Access(&y, 2);
            bytes += 4;
            m_points4c.InsertLast(SBGeoPoint2D((float)x, (float)y));
            if (i == 0)
                m_1c = (float)y;
            else if ((float)y > m_1c)
                m_1c = (float)y;
        }
        file.Access(&marker, 1);
    }
    file.Access(&x, 2);
    file.Access(&y, 2);
    m_box.UnkSetOrigin(SBGeoPoint2D((float)x, (float)y));
    file.Access(&x, 2);
    file.Access(&y, 2);
    m_box.UnkSetSize(SBGeoVector2D((float)x, (float)y));
    file.Access(&m_size, 2);
    m_data = new unsigned char[m_size];
    file.Access(m_data, m_size);
    if ((m_flags >> 4) & 1)
    {
        file.Access(&obstacleCount, 2);
        if (obstacleCount == 0)
        {
            m_flags &= ~2;
            SBAssert(0, RHMaskFile, 344, RHMaskObstacleError);
        }
        for (unsigned short i = 0; i < obstacleCount; ++i)
        {
            file.Access(&obstacleIndex, 2);
            m_obstacles.InsertLast(grid->m_3ea4->m_entries[obstacleIndex & 0xffff]);
        }
    }
}

// FUNCTION: GAME 0x005243a0
bool RHMask::IsAppliedToPointCharacter(const SBGeoPoint2D &point) const
{
    SBGeoSegment2D segment(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    RHUnkSectorPoints &line = *(RHUnkSectorPoints *)&m_points28;
    unsigned long last = ((RHMobileUnk00611360 &)line).FUN_00610f30();
    if (point.X() >= line.FUN_006112c0(0).X() && point.X() <= line.FUN_006112c0(--last).X())
    {
        unsigned long index = 1;
        while (point.m_x > line.FUN_006112c0(index).m_x)
            ++index;
        segment.Set(line.FUN_006112c0(index - 1), line.FUN_006112c0(index));
        if (segment.FUN_00610520(point.X()) > point.Y())
            return true;
        return false;
    }
    return false;
}

// FUNCTION: GAME 0x00524530
bool RHMask::IsAppliedToPointProjectile(const SBGeoPoint2D &point) const
{
    SBGeoSegment2D segment(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    RHUnkSectorPoints &line = *(RHUnkSectorPoints *)&m_points4c;
    unsigned long last = ((RHMobileUnk00611360 &)line).FUN_00610f30();
    if (point.X() >= line.FUN_006112c0(0).X() && point.X() <= line.FUN_006112c0(--last).X())
    {
        unsigned long index = 1;
        while (point.m_x > line.FUN_006112c0(index).m_x)
            ++index;
        segment.Set(line.FUN_006112c0(index - 1), line.FUN_006112c0(index));
        if (segment.FUN_00610520(point.X()) > point.Y())
            return true;
        return false;
    }
    return false;
}

// Parked at 0.7500: loop index and obstacle count take swapped callee-saved registers (target index edi, count ebp).
// STUB: GAME 0x005246c0
bool RHMask::IsAppliedToPoint(const SBGeoPoint3D &point, bool flag) const
{
    SBGeoPoint2D position(point.m_x, point.m_y);
    if (IsAppliedToPointProjectile(position))
        return true;
    if (m_flags & 0x10)
    {
        unsigned int count = m_obstacles.size();
        for (unsigned int i = 0; i < count; ++i)
        {
            RHMaskObstacle *obstacle = (RHMaskObstacle *)m_obstacles.m_first[i];
            if (obstacle->m_24.FUN_00608400(position) && obstacle->m_7c.FUN_0060c660(position))
            {
                if (flag)
                {
                    if (obstacle->m_100.FUN_005df9e0(position.m_x, position.m_y) > point.m_z)
                        return true;
                }
                else if (obstacle->m_a8.FUN_005df9e0(position.m_x, position.m_y) > point.m_z + 0.1f)
                    return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAME 0x00524800
unsigned char RHMask::FUN_00524800(unsigned long index)
{
    return m_data[index];
}

// FUNCTION: GAME 0x00524840
SBGeoPoint2D *RHMaskPointArray::FUN_00524840(SBGeoPoint2D *first, SBGeoPoint2D *last)
{
    SBGeoPoint2D *stop = m_last;
    SBGeoPoint2D *destination = first;
    for (; last != stop; ++last, ++destination)
        *destination = *last;
    stop = m_last;
    for (SBGeoPoint2D *item = destination; item != stop; ++item)
        item->~SBGeoPoint2D();
    m_last = destination;
    return first;
}

class RHUnk0048a970
{
public:
    void Unk(int);
};

class RHUnk00524910
{
public:
    bool FUN_00524930(int value);
    void FUN_00524910(int value);
};

// FUNCTION: GAME 0x00524910
void RHUnk00524910::FUN_00524910(int value)
{
    if (FUN_00524930(value))
        ((RHUnk0048a970 *)this)->Unk(value);
}

struct RHMaskMenuEvent
{
    int m_type;
    void *m_widget;
    void *m_data;
};

struct RHMaskMenuBlazonProfile
{
    char m_00[0x6e];
    unsigned short m_6e;
};

struct RHMaskMenuBlazon
{
    RHMaskMenuBlazonProfile *m_00;
    unsigned short m_04;
    unsigned short m_06;
};

struct RHMaskMenuDescription
{
    char m_00[0xb8];
    RHMenuCampaignMap *m_b8;
};

class RHMaskMenuCalls
{
public:
    bool FUN_00525040(int message, void *widget, void *data);
    char m_00[0xb8];
    RHMaskMenuDescription *m_b8;
    char m_bc[0x384];
    RHMaskMenuBlazon *m_440;
};

// FUNCTION: GAME 0x00524930
bool RHUnk00524910::FUN_00524930(int value)
{
    RHMaskMenuEvent *event = (RHMaskMenuEvent *)value;
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x140)
        handled = ((RHMaskMenuCalls *)this)->FUN_00525040(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = ((RHMenuCloseCalls *)this)->FUN_0052b520(2, event->m_widget, event->m_data);
    return handled;
}

class RHUnk00452030
{
public:
    int Get(int index);
};

class RHUnk00450b60
{
public:
    void Unk(int property, int amount);
};

class RHScriptBatchCalls
{
public:
    void Unk004520e0(int index, int value);
};

extern RHUnk0048a970 *g_unk0x6c0b3c;
extern RHUnk00452030 *g_unk0x6c07fc;

// FUNCTION: GAME 0x00525040
bool RHMaskMenuCalls::FUN_00525040(int, void *, void *)
{
    RHUnk0048a970 *game = g_unk0x6c0b3c;
    RHUnk00452030 *campaign = g_unk0x6c07fc;
    int money = campaign->Get(1);
    ((RHScriptBatchCalls *)campaign)->Unk004520e0(1, money - m_440->m_06);
    ((RHUnk00450b60 *)campaign)->Unk(3, 1);
    m_440->m_06 += m_440->m_00->m_6e;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    RHMaskMenuDescription *description = m_b8;
    ((RHGame *)game)->UpdateBlazons(description->m_b8, (RHMenuMissionDescription *)description, 0, false);
    return true;
}

void RHMask::Emit(SBFile &file, RHFastFindGrid *grid)
{
    FUN_00524800(0);
    m_points28.FUN_00524840(0, 0);
    InitializeFromProtoStream(file, grid);
}
