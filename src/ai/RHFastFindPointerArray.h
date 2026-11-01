#ifndef RHFASTFINDPOINTERARRAY_H
#define RHFASTFINDPOINTERARRAY_H

struct RHFastFindPointerArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    void **m_end;
    void **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    void *m_value;

    void Initialize(const char &allocator)
    {
        *(char *)&m_grow = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
        m_changed = true;
    }
    int size() const { return m_first == 0 ? 0 : m_last - m_first; }
    void **begin() const { return m_first; }
    void **end() const { return m_last; }
    void InsertLast(void *const &value);
    RHFastFindPointerArray &FUN_004ff0a0(const RHFastFindPointerArray &source);
    long Find(void *const &value)
    {
        m_changed = false;
        m_value = value;
        int count = size();
        m_search = m_first;
        int index = 0;
        m_searching = true;
        for (; index < count; ++index, ++m_search)
            if (*m_search == m_value)
                break;
        m_index = index < count ? index : -1;
        return m_index;
    }
};

#endif
