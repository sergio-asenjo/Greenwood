#ifndef RHUNK0055B830VALUES_H
#define RHUNK0055B830VALUES_H

#include "RHFastFindArrayOps.h"
#include <vector>

class RHUnk0055b830Values : public std::vector<unsigned long>
{
public:
    unsigned long *m_cursor;
    bool m_dirty;
    bool m_forward;
    int m_index;
    unsigned long m_value;
    void Resize(unsigned count);
    void Insert(unsigned long *position, unsigned count, const unsigned long &value)
    {
        RHFastFindGateArray *sizes = (RHFastFindGateArray *)this;
        if ((unsigned)(_End - _Last) < count)
        {
            unsigned capacity = sizes->FUN_0059fbc0() + (count < size() ? sizes->FUN_0059fbc0() : count);
            unsigned long *storage = allocator.allocate(capacity, 0);
            unsigned long *next = _Ucopy(_First, position, storage);
            _Ufill(next, count, value);
            _Ucopy(position, _Last, next + count);
            _Destroy(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + capacity;
            _Last = storage + sizes->FUN_0059fbc0() + count;
            _First = storage;
        }
        else if ((unsigned)(_Last - position) < count)
        {
            _Ucopy(position, _Last, position + count);
            _Ufill(_Last, count - (_Last - position), value);
            std::fill(position, _Last, value);
            _Last += count;
        }
        else if (0 < count)
        {
            _Ucopy(_Last - count, _Last, _Last);
            std::copy_backward(position, _Last - count, _Last);
            std::fill(position, position + count, value);
            _Last += count;
        }
    }
    void Insert(unsigned long *position, const unsigned long *first, const unsigned long *last)
    {
        unsigned count = 0;
        std::_Distance(first, last, count);
        if ((unsigned)(_End - _Last) < count)
        {
            RHFastFindGateArray *sizes = (RHFastFindGateArray *)this;
            unsigned capacity = sizes->FUN_0059fbc0() + (count < size() ? size() : count);
            unsigned long *storage = allocator.allocate(capacity, 0);
            unsigned long *next = _Ucopy(_First, position, storage);
            next = _Ucopy(first, last, next);
            _Ucopy(position, _Last, next);
            _Destroy(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + capacity;
            _Last = storage + sizes->FUN_0059fbc0() + count;
            _First = storage;
        }
        else if ((unsigned)(_Last - position) < count)
        {
            _Ucopy(position, _Last, position + count);
            _Ucopy(first + (_Last - position), last, _Last);
            std::copy(first, first + (_Last - position), position);
            _Last += count;
        }
        else if (0 < count)
        {
            _Ucopy(_Last - count, _Last, _Last);
            std::copy_backward(position, _Last - count, _Last);
            std::copy(first, last, position);
            _Last += count;
        }
    }
};

#endif
