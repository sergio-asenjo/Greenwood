#ifndef RHSECTORARCHERY_H
#define RHSECTORARCHERY_H

#include "RHSectorCore.h"
#include <vector>

class RHMissionArrayStorage;

template <class T>
class RHSectorArrayStorage : public std::vector<T>
{
public:
    ~RHSectorArrayStorage() { clear(); }
};

template <class T>
class RHSectorArray : public RHSectorArrayStorage<T>
{
public:
    RHSectorArray() { m_dirty = 1; }
    ~RHSectorArray()
    {
        int count = size();
        for (int i = 0; i < count; ++i)
        {
            if ((*this)[i] != 0)
                delete (*this)[i];
        }
        erase(begin(), end());
    }
    char m_pad10[4];
    char m_dirty;
    char m_pad15[3];
    void Resize(unsigned int count, const T &value = T())
    {
        if (size() < count)
            insert(end(), count - size(), value);
        else if (count < size())
            ((RHMissionArrayStorage *)this)->FUN_004609a0(begin() + count, end());
        m_dirty = 1;
    }
};

class RHUnk00522540;
struct RHUnk00571160Position;

// VTABLE: GAME 0x00679c9c
class RHSectorArchery : public RHSector
{
public:
    RHSectorArchery();
    virtual ~RHSectorArchery();
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    bool IsInside(const RHUnk00571160Position &position);
    void Emit(SBFile &file);
    RHSectorArray<RHUnk00522540 *> m_58;
    char m_pad70[8];
    void *m_78;
    unsigned short m_7c;
    unsigned short m_7e;
    unsigned short m_80;
    unsigned short m_82;
};

#endif
