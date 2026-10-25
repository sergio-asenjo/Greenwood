#include "SBNullstr.h"
#include "RHSoundSource.h"
#include "RHSoundGeometryCalls.h"
#define SBGEO_POINT2D_VIEW
#include "RHUnk005fc3b0.h"
#include "SBGeoSegment2D.h"
#include "SBGeoIntersection2D.h"
#include "RHUnk00613e90.h"
#include "RHUnk0053bf20.h"
#include "SCQuad.h"
#include <math.h>

extern double g_unk0x00677688;

#define m_08 (*(unsigned int *)((char *)this + 0x08))
#define m_40 (*(unsigned int *)((char *)this + 0x40))
#define m_1c (*(RHUnk005b4700 *)((char *)this + 0x1c))

// STRING: GAME 0x006b869c
#define RH_SOUND_FILE "P:\\Robin Hood\\RHsoundsource.cpp"

#define RH_SOUND_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, RH_SOUND_FILE, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// FUNCTION: GAME 0x005b35e0
void RHUnk005b35e0::FUN_005b35e0(unsigned int count, const SBGeoPoint2D &value)
{
    std::vector<SBGeoPoint2D> &values = *(std::vector<SBGeoPoint2D> *)this;
    if (values.size() < count)
        values.insert(values.end(), count - values.size(), value);
    else if (count < values.size())
        values.erase(values.begin() + count, values.end());
}

// FUNCTION: GAME 0x005b3920
RHSoundSource::~RHSoundSource()
{
}

// FUNCTION: GAME 0x005b39e0
float RHSoundSource::FUN_005b39e0(const SBGeoPoint2D &second, const SBGeoPoint2D &first)
{
    float x = first.m_x - second.m_x;
    float y = (first.m_y - second.m_y) * 1.743446795621098;
    return (float)sqrt(y * y + x * x);
}

// FUNCTION: GAME 0x005b3a10
float RHSoundSource::FUN_005b3a10(SBGeoSegment2D &segment, SBGeoPoint2D &point, bool &visible)
{
    RHUnk005fc3b0 normal;
    RHMobileUnk006100e0 line(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    RHUnk0060fbf0 intersection;
    normal.FUN_005fc430(((RHUnk005fc3b0 &)segment.Second().Unk005fc110(segment.First())).FUN_005fc8f0(true, 1.0f));
    normal.m_y *= g_unk0x00677688;
    normal.FUN_005fc7c0(1.0f);
    (SBGeoPoint2D &)line = point;
    line.Second() = point.Unk005fc190(normal);
    intersection.FUN_0060fca0(segment.FUN_0060ad60(line));
    if (((SCQuadArg *)&intersection)->GetType() != 1)
    {
        visible = false;
        return 0.0f;
    }
    visible = true;
    return FUN_005b39e0(*(SBGeoPoint2D *)((RHUnk0053bf20 *)&intersection)->FUN_0053bf20(), point);
}

// FUNCTION: GAME 0x005b3c20
unsigned short RHSoundSource::FUN_005b3c20(unsigned short index)
{
    unsigned short maximum = *(unsigned short *)((char *)this + 0x16);
    if (*(unsigned char *)((char *)this + 0x10))
        return maximum;
    if ((unsigned short)index > maximum)
        return 0;
    return maximum - index;
}

// Parked: count and loop offset take swapped ebp/edi roles, and the first minimum test uses fcom instead of fld st(0)/fcomp.
// STUB: GAME 0x005b3c40
unsigned short RHSoundSource::FUN_005b3c40(RHUnk00613e90 &position)
{
    bool visible;
    float nearest;
    SBGeoPoint2D unused;
    int count = 0;
    SBGeoPoint2D listener;
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    SBGeoSegment2D segment(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    if (!m_4c)
        return 0;
    listener.m_x = position.x;
    listener.m_y = position.y - position.z;
    if (m_10.m_0c.m_storage.m_first)
        count = m_10.m_0c.m_storage.m_last - m_10.m_0c.m_storage.m_first;
    switch ((unsigned short)count)
    {
    case 0:
        return 0;
    case 1:
        return FUN_005b3c20((unsigned short)FUN_005b39e0(m_10.m_0c.m_storage.m_first[0], listener));
    }
    nearest = 1000000.0f;
    for (unsigned short i = 0; i < (unsigned short)count; ++i)
    {
        float distance = FUN_005b39e0(m_10.m_0c.m_storage.m_first[i], listener);
        if (distance < nearest)
            nearest = distance;
    }
    previous = m_10.m_0c.m_storage.m_first[0];
    for (unsigned short j = 1; j < (unsigned short)count; ++j)
    {
        current = m_10.m_0c.m_storage.m_first[j];
        segment.First() = previous;
        segment.Second() = current;
        float distance = FUN_005b3a10(segment, listener, visible);
        if (visible && distance < nearest)
            nearest = distance;
        previous = current;
    }
    return FUN_005b3c20((unsigned short)nearest);
}

// FUNCTION: GAME 0x005b4210
bool RHSoundSource::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006b86bc
                    "RHSoundSource");
    unsigned int code;
    unsigned int count;
    char scratch;
    if (file.m_bLoading)
    {
        RH_SOUND_ACCESS(code, 1, 359);
        m_08 = code & 0xff;
        RH_SOUND_ACCESS(code, 1, 362);
        m_40 = code & 0xff;
    }
    else
    {
        *(char *)&code = (char)m_08;
        RH_SOUND_ACCESS(code, 1, 368);
        *(char *)&code = (char)m_40;
        RH_SOUND_ACCESS(code, 1, 371);
    }
    RH_SOUND_ACCESS(m_0c, 4, 374);
    RH_SOUND_ACCESS(m_10[0], 1, 375);
    RH_SOUND_ACCESS(m_10[2], 2, 376);
    RH_SOUND_ACCESS(m_10[4], 2, 377);
    RH_SOUND_ACCESS(m_10[6], 2, 378);
    RH_SOUND_ACCESS(m_10[8], 2, 379);
    RH_SOUND_ACCESS(m_10[10], 2, 380);
    RH_SOUND_ACCESS(m_10[0x34], 2, 381);
    RH_SOUND_ACCESS(m_10[0x36], 2, 382);
    RH_SOUND_ACCESS(m_10[0x38], 2, 383);
    RH_SOUND_ACCESS(m_10[0x3a], 2, 384);
    RH_SOUND_ACCESS(m_4c, 1, 385);
    RH_SOUND_ACCESS(m_4c, 1, 386);
    RH_SOUND_ACCESS(scratch, 1, 389);
    if (file.m_bLoading)
    {
        RH_SOUND_ACCESS(count, 2, 393);
        m_1c.FUN_005b4700(count & 0xffff);
    }
    else
    {
        count = m_1c.m_first == 0 ? 0 : m_1c.m_last - m_1c.m_first;
        RH_SOUND_ACCESS(count, 2, 399);
    }
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
        if (!m_1c[index].Serialize(file))
            return false;
    return true;
}

// Parked: point-array allocation and exception cleanup still differ from the target.
// STUB: GAME 0x005b3f30
void RHSoundSource::FUN_005b3f30(SBFile &file)
{
#define RH_SOUND_READ(value, size) file.Access(&(value), size)
    unsigned int code;
    unsigned short count;
    RH_SOUND_READ(m_0c, 4);
    RH_SOUND_READ(m_4c, 1);
    RH_SOUND_READ(code, 1);
    m_08 = code & 0xff;
    if ((m_08 & 0xff) == 2)
    {
        RH_SOUND_READ(m_10[0x34], 2);
        RH_SOUND_READ(m_10[0x36], 2);
        RH_SOUND_READ(m_10[0x38], 2);
        ++m_10.m_38;
    }
    RH_SOUND_READ(m_10[0], 1);
    if (m_10[0] == 0)
    {
        RH_SOUND_READ(m_10[2], 2);
        RH_SOUND_READ(m_10[4], 2);
        RH_SOUND_READ(code, 1);
        RH_SOUND_READ(count, 2);
        ((RHUnk005b4700 *)&m_10.m_0c.m_storage)->FUN_005b4700(count);
        m_10.m_0c.m_changed = true;
        for (unsigned short index = 0; index < count; ++index)
        {
            short x;
            short y;
            RH_SOUND_READ(x, 2);
            RH_SOUND_READ(y, 2);
            m_10.m_0c.m_storage.m_first[index].m_x = (float)x;
            m_10.m_0c.m_storage.m_first[index].m_y = (float)y;
        }
        RH_SOUND_READ(code, 1);
        RH_SOUND_READ(m_10.m_38, 2);
        if (m_10.m_38 > 100)
            m_10.m_38 = 100;
        RH_SOUND_READ(m_10.m_3a, 2);
        if (m_10.m_3a > 100)
            m_10.m_3a = 100;
        RH_SOUND_READ(m_10.m_36, 2);
    }
    RH_SOUND_READ(m_40, 1);
    RH_SOUND_READ(m_04, 4);
#undef RH_SOUND_READ
}

// FUNCTION: GAME 0x005b4700
void RHUnk005b4700::FUN_005b4700(int count)
{
    ((std::vector<SBGeoPoint2D> *)this)->resize(count);
    *(bool *)((char *)this + 0x14) = true;
}

void RHSoundSourceEmit(RHSoundSource *source, SBFile &file)
{
    source->Serialize(file);
}
