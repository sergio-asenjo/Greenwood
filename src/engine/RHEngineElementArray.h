#ifndef RHENGINEELEMENTARRAY_H
#define RHENGINEELEMENTARRAY_H

#include <vector>

template<class T>
class RHEngineElementArray : public std::vector<T *>
{
public:
    __forceinline T **const &First() const { return _First; }
    RHEngineElementArray() : m_changed(true) {}
    ~RHEngineElementArray() { clear(); }
    void Add(T *const &value)
    {
        insert(end(), 1, value);
        m_changed = true;
    }
    __forceinline void Remove(T *const &value)
    {
        T **first = *(T **const volatile *)&_First;
        unsigned count = first == 0 ? 0 : _Last - first;
        for (unsigned index = 0; index < count; ++index)
            if ((*this)[index] == value)
            {
                erase(&at(index));
                m_changed = true;
                break;
            }
    }
    unsigned VolatileSize() const
    {
        T **first = *(T **const volatile *)&_First;
        return first == 0 ? 0 : _Last - first;
    }
    T **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    T *m_value;
};

#endif
