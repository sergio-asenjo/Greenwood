#ifndef RHFASTFINDAMBUSHARRAY_H
#define RHFASTFINDAMBUSHARRAY_H

#include "RHAmbushPoint.h"
#include <vector>

class RHFastFindAmbushStorage : public std::vector<RHUnk00521550 *>
{
public:
    ~RHFastFindAmbushStorage() { clear(); }
};

class RHFastFindAmbushArray : public RHFastFindAmbushStorage
{
public:
    RHFastFindAmbushArray() : m_changed(true) {}
    // FUNCTION: GAME 0x00423d90
    ~RHFastFindAmbushArray()
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
    void InsertLast(RHUnk00521550 *value)
    {
        typedef std::vector<RHUnk00521550 *> Base;
        typedef iterator (Base::*Ucopy)(const_iterator, const_iterator, iterator);
        typedef void (Base::*Ufill)(iterator, unsigned, RHUnk00521550 *const &);
        typedef void (Base::*Destroy)(iterator, iterator);
        typedef void (*Construct)(iterator, RHUnk00521550 *const &);
        Ucopy copy = &RHFastFindAmbushArray::_Ucopy;
        Ufill fill = &RHFastFindAmbushArray::_Ufill;
        Destroy destroy = &RHFastFindAmbushArray::_Destroy;
        Construct construct = std::_Construct;
        iterator position = end();
        if ((unsigned)(_End - _Last) < 1)
        {
            unsigned grow = size() > 1 ? size() : 1;
            int count = size() + grow;
            iterator storage = allocator.allocate(count, (void *)0);
            iterator destination = storage;
            for (iterator source = _First; source != position; ++source, ++destination)
                construct(destination, *source);
            (this->*fill)(destination, 1, value);
            ++destination;
            (this->*copy)(position, _Last, destination);
            (this->*destroy)(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + count;
            _Last = storage + size() + 1;
            _First = storage;
        }
        else if ((unsigned)(_Last - position) < 1)
        {
            (this->*copy)(position, _Last, position + 1);
            (this->*fill)(_Last, 1 - (_Last - position), value);
            std::fill(position, _Last, value);
            ++_Last;
        }
        else
        {
            (this->*copy)(_Last - 1, _Last, _Last);
            std::copy_backward(position, _Last - 1, _Last);
            std::fill(position, position + 1, value);
            ++_Last;
        }
        m_changed = true;
    }
    RHUnk00521550 **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    RHUnk00521550 *m_value;
};

#define g_unk0x006c0718 RHArtificialIntelligence::marrayAmbushPoints

#endif
