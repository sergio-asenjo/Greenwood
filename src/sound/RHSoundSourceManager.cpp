#include "SBNullstr.h"
#include "RHSoundSourceManager.h"
#include "RHSoundCacheCore.h"
#include "RHSoundCacheEntry.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHSoundSourcePointStorage, 0x10)
DECOMP_SIZE_ASSERT(RHSoundSourcePoints, 0x24)
DECOMP_SIZE_ASSERT(RHSoundSourceFields, 0x3c)
DECOMP_SIZE_ASSERT(RHSoundSource, 0x50)
DECOMP_SIZE_ASSERT(RHSoundSourceArray, 0x20)
DECOMP_SIZE_ASSERT(RHSoundSourceIterator, 0x04)
DECOMP_SIZE_ASSERT(RHSoundSourceManager, 0x24)

// SIZE 0x10
struct RHSoundSourceSerializationState
{
    unsigned int index; // 0x00
    RHSoundSource *source; // 0x04
    int id; // 0x08
    int resource; // 0x0c
};

DECOMP_SIZE_ASSERT(RHSoundSourceSerializationState, 0x10)

// FUNCTION: GAME 0x005b3880
RHSoundSource::RHSoundSource() : m_04(0), m_08(1), m_0c(-1), m_4c(false)
{
}

// FUNCTION: GAME 0x005b49d0
RHSoundSourceManager::RHSoundSourceManager(RHSoundCache *cache)
{
    *(RHSoundCache **)m_00 = cache;
}

// FUNCTION: GAME 0x005b4a00
RHSoundSourceManager::~RHSoundSourceManager()
{
    unsigned short count = m_sources.GetSize();
    unsigned int index = 0;
    if (count > 0)
    {
        unsigned int remaining = count;
        do
        {
            RHSoundSource *source = m_sources.m_first[index];
            if (source)
            {
                source->RHSoundSource::~RHSoundSource();
                operator delete(source);
            }
            ++index;
            --remaining;
        }
        while (remaining);
    }
    m_sources.RemoveAll();
}

// FUNCTION: GAME 0x005b4ae0
void RHSoundSourceManager::RHUnk005b4ae0()
{
    for (short index = m_sources.GetSize() - 1; index >= 0; --index)
        FUN_005b4f00(m_sources.m_first[index]);
    m_sources.RemoveAll();
}

// FUNCTION: GAME 0x005b4db0
void RHSoundSourceManager::FUN_005b4db0()
{
    unsigned int count = m_sources.GetSize();
    for (unsigned int index = 0; index < count; ++index)
    {
        RHSoundSource *source = m_sources.m_first[index];
        if (source)
        {
            unsigned long id = source->m_0c;
            RHSoundCache *cache = *(RHSoundCache **)m_00;
            RHSoundCacheEntry *entry = cache->GetSourceCacheEntryForID(id);
            entry->m_loop = source->m_08 == 1;
        }
    }
}

// FUNCTION: GAME 0x005b4e00
RHSoundSource *RHSoundSourceManager::GetSoundSource(unsigned short id)
{
    if (id >= m_sources.GetSize())
        SBAssert(1,
                 // STRING: GAME 0x006b86cc
                 "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0xa4,
                 // STRING: GAME 0x006b86f4
                 "Invalid sound source ID !");
    return m_sources[id];
}

// FUNCTION: GAME 0x005b4e60
bool RHSoundSourceManager::AddSoundSource(RHSoundSource *source)
{
    RHSoundSourceArray &list = m_sources;
    short id = list.Find(source);
    if (id == -1)
    {
        source->m_4c = false;
        list.InsertLast(source);
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0xc2,
             // STRING: GAME 0x006b8710
             "Sound source already managed", source->m_0c);
    return false;
}

// FUNCTION: GAME 0x005b4f00
bool RHSoundSourceManager::FUN_005b4f00(RHSoundSource *source)
{
    bool result = true;
    if (source)
    {
        short index = m_sources.Find(source, result);
        if (index != -1)
        {
            RHSoundSource *owned = m_sources.m_first[index];
            if (owned)
            {
                owned->RHSoundSource::~RHSoundSource();
                operator delete(owned);
            }
            m_sources.m_first[index] = 0;
        }
        else
            result = false;
    }
    return result;
}

// Parked: 91.21%; scratch state is +0x14..+0x20, target +0x10..+0x1c.
// STUB: GAME 0x005b5000
bool RHSoundSourceManager::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b8730
    RHSerializeName(file, "RHSoundSourceManager");
    int count;
    RHSoundSourceSerializationState state;
    if (file.m_bLoading)
    {
        RHUnk005b4ae0();
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x115,
                     "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (state.index = 0; (unsigned short)state.index < (unsigned short)count; ++state.index)
        {
            if (file.Access(&state.id, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x119,
                         "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
            if ((short)state.id != -1)
            {
                state.source = new RHSoundSource;
                state.source->Serialize(file);
                if (file.Access(&state.resource, 4) < 0)
                {
                    SBString *error = file.GetError();
                    SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x120,
                             "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                    return false;
                }
            }
            else
                state.source = 0;
            m_sources.InsertLast(state.source);
        }
    }
    else
    {
        state.id = -1;
        count = m_sources.GetSize();
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x131,
                     "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (state.index = 0; (unsigned short)state.index < (unsigned short)count; ++state.index)
        {
            state.id = (int)m_sources[(unsigned short)state.index];
            if (state.id)
            {
                if (file.Access(&state.source, 2) < 0)
                {
                    SBString *error = file.GetError();
                    SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x139,
                             "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                    return false;
                }
                state.source->Serialize(file);
                state.resource = state.source->m_0c;
                if (file.Access(&state.resource, 4) < 0)
                {
                    SBString *error = file.GetError();
                    SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x13d,
                             "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                    return false;
                }
            }
            else if (file.Access(&state.id, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHsoundsourcemanager.cpp", 0x141,
                         "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
    }
    return true;
}

void RHSoundSourceManager::Emit(SBFile &file, RHSoundSource *source, unsigned short id)
{
    RHSoundSourceManager manager(0);
    GetSoundSource(id);
    AddSoundSource(source);
    Serialize(file);
}
