#ifndef RHFASTFINDSEEKARRAY_H
#define RHFASTFINDSEEKARRAY_H

#include "RHSeekPoint.h"
#include "RHFastFindArrayOps.h"

class RHUnk00597a70;
void FUN_0059fb00(RHUnk00597a70 **destination, RHUnk00597a70 *const &value);

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
    void InsertLast(RHSeekPoint *const &value)
    {
        RHScriptFXArray *ops = (RHScriptFXArray *)this;
        iterator position = end();
        if ((unsigned)(_End - _Last) < 1) {
            unsigned grow = size() > 1 ? size() : 1;
            int count = size() + grow;
            iterator storage = allocator.allocate(count, (void *)0);
            iterator destination = storage;
            for (iterator source = _First; source != position; ++source, ++destination)
                FUN_0059fb00((RHUnk00597a70 **)destination, (RHUnk00597a70 *const &)*source);
            ops->Unk004fe450((void **)destination, 1, *(void *const *)&value);
            ++destination;
            ops->Unk004fe420((void **)position, (void **)_Last, (void **)destination);
            ops->Unk005008e0((void **)_First, (void **)_Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + count;
            _Last = storage + ((RHFastFindGateArray *)this)->FUN_0059fbc0() + 1;
            _First = storage;
        } else if ((unsigned)(_Last - position) < 1) {
            ops->Unk004fe420((void **)position, (void **)_Last, (void **)(position + 1));
            ops->Unk004fe450((void **)_Last, 1 - (_Last - position), *(void *const *)&value);
            std::fill(position, _Last, value);
            ++_Last;
        } else {
            ops->Unk004fe420((void **)(_Last - 1), (void **)_Last, (void **)_Last);
            std::copy_backward(position, _Last - 1, _Last);
            std::fill(position, position + 1, value);
            ++_Last;
        }
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
