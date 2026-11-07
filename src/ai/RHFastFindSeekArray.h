#ifndef RHFASTFINDSEEKARRAY_H
#define RHFASTFINDSEEKARRAY_H

#include "RHSeekPoint.h"

class RHFastFindSeekStorage : public std::vector<RHSeekPoint *>
{
public:
    ~RHFastFindSeekStorage() { clear(); }
};

class RHFastFindSeekArray : public RHFastFindSeekStorage
{
public:
    RHFastFindSeekArray() : m_changed(true) {}
    // FUNCTION: GAME 0x00423e40
    ~RHFastFindSeekArray()
    {
        int count = size();
        for (int i = 0; i < count; ++i)
            delete (*this)[i];
        erase(begin(), end());
    }
    void RemoveAll()
    {
        int count = size();
        for (int i = 0; i < count; ++i)
            delete (*this)[i];
        erase(begin(), end());
        m_changed = true;
    }
    RHSeekPoint **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    RHSeekPoint *m_value;
};

#define g_unk0x006c06f0 RHArtificialIntelligence::marraySeekPoints

#endif
