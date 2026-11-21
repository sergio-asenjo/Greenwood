#ifndef RHFRAMEHOLDERARRAY_H
#define RHFRAMEHOLDERARRAY_H

#include "Decomp.h"

template <class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;
    undefined4 m_10;
    bool m_dirty;

    unsigned int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
    unsigned int GetSize() const;
    T &operator[](unsigned long index) { return m_first[index]; }
    void Insert(T *, unsigned int, const T &);
    void Remove(T *, T *);
    void Resize(unsigned int size)
    {
        if (Size() < size)
        {
            T *position = m_last;
            Insert(position, size - GetSize(), T());
        }
        else if (size < GetSize())
            Remove(m_first + size, m_last);
    }
    void RemoveAll() { Remove(m_first, m_last); m_dirty = true; }
    void InsertLast(const T &value) { Insert(m_last, 1, value); m_dirty = true; }
};

#endif
