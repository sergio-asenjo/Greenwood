#ifndef RHSOUNDSOURCEMANAGER_H
#define RHSOUNDSOURCEMANAGER_H

#include "RHSaveGameManager.h"

class RHSoundSource
{
public:
    RHSoundSource();
    virtual ~RHSoundSource();
    virtual bool Serialize(SBFile &file);

    char m_04[8];
    int m_0c;
    char m_10[0x3c];
    bool m_4c;
};

class RHSoundSourceArray
{
public:
    int m_grow;                     // +0x00
    RHSoundSource **m_first;         // +0x04
    RHSoundSource **m_last;          // +0x08
    RHSoundSource **m_end;           // +0x0c
    RHSoundSource **m_search;        // +0x10
    bool m_changed;                 // +0x14
    bool m_searching;               // +0x15
    int m_index;                    // +0x18
    RHSoundSource *m_value;          // +0x1c

    int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    RHSoundSource *operator[](unsigned short index) { return m_first[index]; }
    void InsertLast(RHSoundSource *const &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert(
            (RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
        m_changed = true;
    }
    long Find(RHSoundSource *const &value, bool searching = true)
    {
        m_changed = false;
        m_value = value;
        int count = GetSize();
        m_search = m_first;
        int index = 0;
        m_searching = searching;
        for (; index < count; ++index, ++m_search)
            if (*m_search == value)
                break;
        m_index = index < count ? index : -1;
        return m_index;
    }
};

class RHSoundSourceManager
{
public:
    RHSoundSource *GetSoundSource(unsigned short id);
    bool AddSoundSource(RHSoundSource *source);
    bool Serialize(SBFile &file);
    void RHUnk005b4ae0();
    void Emit(SBFile &file, RHSoundSource *source, unsigned short id);

    char m_00[4];                   // +0x00
    RHSoundSourceArray m_sources;    // +0x04
};

#endif
