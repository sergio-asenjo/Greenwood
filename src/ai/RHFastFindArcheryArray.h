#ifndef RHFASTFINDARCHERYARRAY_H
#define RHFASTFINDARCHERYARRAY_H

#include <vector>

class RHSectorArchery;

class RHFastFindArcheryStorage : public std::vector<RHSectorArchery *>
{
public:
    ~RHFastFindArcheryStorage() { clear(); }
};

class RHFastFindArcheryArray : public RHFastFindArcheryStorage
{
public:
    RHFastFindArcheryArray() : m_changed(true) {}
    ~RHFastFindArcheryArray();
    void RemoveAll();
    void InsertLast(RHSectorArchery *value);
    RHSectorArchery **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    RHSectorArchery *m_value;
};

#define g_unk0x006c06d0 RHArtificialIntelligence::marrayArcherySectors

#endif
