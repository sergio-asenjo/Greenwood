#include "SBNullstr.h"
#include "RHSoundSource.h"

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

void RHSoundSourceEmit(RHSoundSource *source, SBFile &file)
{
    source->Serialize(file);
}
