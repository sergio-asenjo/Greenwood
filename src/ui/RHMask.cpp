#include "SBNullstr.h"
#include "RHMask.h"

// STRING: GAME 0x006b08ac
static const char *RHMaskFile = "P:\\Robin Hood\\RHmask.cpp";
// STRING: GAME 0x006b08c8
static const char *RHMaskObstacleError = "VERBOTEN : Obstacle-mask with no obstacle associated !";

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

// FUNCTION: GAME 0x00524800
unsigned char RHMask::FUN_00524800(unsigned long index)
{
    return m_data[index];
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

bool RHUnk00524910::FUN_00524930(int value)
{
    return false;
}

void RHMask::Emit(SBFile &file, RHFastFindGrid *grid)
{
    FUN_00524800(0);
    InitializeFromProtoStream(file, grid);
}
