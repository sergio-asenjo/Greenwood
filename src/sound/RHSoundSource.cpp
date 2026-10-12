#include "SBNullstr.h"
#include "RHSoundSource.h"
#include <math.h>

#define m_08 (*(unsigned int *)((char *)this + 0x08))
#define m_40 (*(unsigned int *)((char *)this + 0x40))
#define m_1c (*(RHUnk005b4700 *)((char *)this + 0x1c))

void FUN_0064158f(void *memory);

// STRING: GAME 0x006b869c
#define RH_SOUND_FILE "P:\\Robin Hood\\RHsoundsource.cpp"

#define RH_SOUND_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, RH_SOUND_FILE, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// Parked: per-point destructor and exception-state ordering remain approximate.
// STUB: GAME 0x005b3920
RHSoundSource::~RHSoundSource()
{
    SBGeoPoint2D *first = m_10.m_0c.m_storage.m_first;
    SBGeoPoint2D *last = m_10.m_0c.m_storage.m_last;
    while (first != last)
    {
        first->~SBGeoPoint2D();
        ++first;
    }
    m_10.m_0c.m_storage.m_last = m_10.m_0c.m_storage.m_first;
    FUN_0064158f(m_10.m_0c.m_storage.m_first);
    m_10.m_0c.m_storage.m_first = 0;
    m_10.m_0c.m_storage.m_last = 0;
    m_10.m_0c.m_storage.m_end = 0;
}

// GLOBAL: GAME 0x00679e30
double g_unk0x679e30 = 1.743446795621098;

// Parked: VC6 expression scheduling and the scaled-axis x87 sequence remain unverified.
// STUB: GAME 0x005b39e0
float FUN_005b39e0(const SBGeoPoint2D &second, const SBGeoPoint2D &first)
{
    float x = first.m_x - second.m_x;
    float y = first.m_y - second.m_y;
    return (float)sqrt(x * x + (y * g_unk0x679e30) * (y * g_unk0x679e30));
}

// Parked: the geometry construction and visibility helpers are not reproduced.
// STUB: GAME 0x005b3a10
float RHSoundSource::FUN_005b3a10(
    const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned char &visible)
{
    visible = 1;
    return FUN_005b39e0(first, second);
}

// Parked: source operand scheduling has not been measured.
// STUB: GAME 0x005b3c20
unsigned short RHSoundSource::FUN_005b3c20(unsigned int index)
{
    unsigned short maximum = *(unsigned short *)((char *)this + 0x16);
    if (*(unsigned char *)((char *)this + 0x10))
        goto subtract;
    if ((unsigned short)index > maximum)
        return 0;
subtract:
    return maximum - index;
}

// Parked: temporary geometry lifetimes, visibility testing and minimum-distance scheduling differ.
// STUB: GAME 0x005b3c40
unsigned short RHSoundSource::FUN_005b3c40(const void *point)
{
    if (!m_4c)
        return 0;

    SBGeoPoint2D *first = m_10.m_0c.m_storage.m_first;
    SBGeoPoint2D *last = m_10.m_0c.m_storage.m_last;
    if (!first || first == last)
        return 0;

    const SBGeoPoint2D &center = *(const SBGeoPoint2D *)point;
    float nearest = 102400.0f;
    for (SBGeoPoint2D *current = first; current != last; ++current)
    {
        float distance = FUN_005b39e0(center, *current);
        if (distance < nearest)
            nearest = distance;
    }
    return FUN_005b3c20((unsigned int)nearest);
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

void RHSoundSourceEmit(RHSoundSource *source, SBFile &file)
{
    source->Serialize(file);
}
