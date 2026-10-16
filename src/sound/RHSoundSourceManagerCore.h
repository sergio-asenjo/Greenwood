#ifndef RHSOUNDSOURCEMANAGERCORE_H
#define RHSOUNDSOURCEMANAGERCORE_H

#include "Decomp.h"

class RHSoundSource;
class RHSoundCache;
class SBFile;

// SIZE 0x20
class RHSoundSourceArray
{
public:
    RHSoundSourceArray()
    {
        undefined allocator;
        *(undefined *)&m_grow = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
        m_changed = true;
    }
    ~RHSoundSourceArray();
    int m_grow; // 0x00
    RHSoundSource **m_first; // 0x04
    RHSoundSource **m_last; // 0x08
    RHSoundSource **m_end; // 0x0c
    RHSoundSource **m_search; // 0x10
    bool m_changed; // 0x14
    bool m_searching; // 0x15
    int m_index; // 0x18
    RHSoundSource *m_value; // 0x1c

    int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    RHSoundSource *operator[](unsigned short index) { return m_first[index]; }
    RHSoundSource **begin() { return m_first; }
    RHSoundSource **end() { return m_last; }
    void RemoveAll();
    void InsertLast(RHSoundSource *const &value);
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

// SIZE 0x24
class RHSoundSourceManager
{
public:
    RHSoundSourceManager(RHSoundCache *cache);
    ~RHSoundSourceManager();
    RHSoundSource *GetSoundSource(unsigned short id);
    RHSoundSource *FUN_005b4e00(unsigned short id);
    bool AddSoundSource(RHSoundSource *source);
    bool Serialize(SBFile &file);
    void RHUnk005b4ae0();
    void FUN_005b4b50(void *, void *, void *);
    void FUN_005b4db0();
    bool FUN_005b4f00(RHSoundSource *source);
    void Emit(SBFile &file, RHSoundSource *source, unsigned short id);

    undefined m_00[4]; // 0x00
    RHSoundSourceArray m_sources; // 0x04
};

#endif
