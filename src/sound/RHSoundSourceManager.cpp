#include "RHSoundSourceManager.h"

struct RHSoundSourceSerializationState
{
    unsigned int index;
    RHSoundSource *source;
    int id;
    int resource;
};

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
    GetSoundSource(id);
    AddSoundSource(source);
    Serialize(file);
}
