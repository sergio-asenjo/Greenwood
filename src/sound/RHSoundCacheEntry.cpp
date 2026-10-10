#include "RHSoundCacheEntry.h"
#include "SB.h"

static inline const char *SoundCacheStringData(const std::string &value)
{
    const char *chars = reinterpret_cast<const SBString *>(&value)->m_chars;
    return chars ? chars : "";
}

// FUNCTION: GAME 0x005b1d40
bool RHSoundCacheEntry::UpdateSampleSize()
{
    unsigned int mode = FSOUND_Sample_GetMode(m_sample);
    if (mode & 0x40)
        return false;
    unsigned short bytes = (mode & 0x10) ? 2 : 1;
    m_size = FSOUND_Sample_GetLength(m_sample) * bytes;
    unsigned int frequency;
    if (!FSOUND_Sample_GetDefaults(m_sample, (int *)&frequency, 0, 0, 0))
        SBAssert(1,
            // STRING: GAME 0x006b858c
            "P:\\Robin Hood\\RHsoundcacheentry.cpp", 91,
            // STRING: GAME 0x006b85b0
            "Unable to get defaults for sample !");
    m_duration = FSOUND_Sample_GetLength(m_sample) * 1000 / frequency;
    return true;
}

// FUNCTION: GAME 0x005b1dd0
bool RHSoundCacheEntry::LoadSample(bool spatial, unsigned short stamp)
{
    std::string path;
    path = g_unk0x006c0600 + std::string(
        // STRING: GAME 0x006af384
        "\\") + m_name;
    FUN_005f5a80(path, true);
    if (spatial)
    {
        m_sample = FSOUND_Sample_Load(-1, SoundCacheStringData(path), (m_loop ? 2 : 1) | 0x1030, 0);
        if (m_sample)
            FSOUND_Sample_SetMinMaxDistance(m_sample, 2.0f, 1000.0f);
    }
    else
        m_sample = FSOUND_Sample_Load(-1, SoundCacheStringData(path), (m_loop ? 2 : 1) | 0x2030, 0);
    if (!m_sample)
        return false;
    if (m_size == 0 && !UpdateSampleSize())
    {
        FSOUND_Sample_Free(m_sample);
        m_sample = 0;
        SBAssert(0, "P:\\Robin Hood\\RHsoundcacheentry.cpp", 166,
            // STRING: GAME 0x006b85d4
            "ERROR: Illegal stereo sample \"%s\" detected. Sample not loaded !", SoundCacheStringData(m_name));
    }
    m_stamp = stamp;
    return true;
}

void RHSoundCacheEntry::Emit(bool spatial, unsigned short stamp)
{
    UpdateSampleSize();
    LoadSample(spatial, stamp);
}
