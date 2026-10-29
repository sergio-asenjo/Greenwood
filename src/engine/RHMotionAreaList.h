#ifndef RHMOTIONAREALIST_H
#define RHMOTIONAREALIST_H

#include <list>

template<class T>
class RHMotionAreaListStorage : public std::list<T>
{
public:
    ~RHMotionAreaListStorage() { clear(); }
};

template<class T>
class RHMotionAreaList : public RHMotionAreaListStorage<T>
{
public:
    RHMotionAreaList() : m_dirty(true) {}
    void *m_cursor;
    bool m_dirty;
    char m_11[3];
    int m_index;
    char m_18[0xc];
    void InsertLast(const T &value)
    {
        insert(end(), value);
        m_dirty = true;
    }
};

#endif
