#ifndef RHFASTFINDRANGEARRAY_H
#define RHFASTFINDRANGEARRAY_H

#include <vector>

class RHFastFindRangeArray : public std::vector<unsigned long>
{
public:
    RHFastFindRangeArray() : m_changed(true) {}
    RHFastFindRangeArray(const RHFastFindRangeArray &other)
    {
        typedef std::vector<unsigned long> Values;
        void (Values::*assignRange)(const unsigned long *, const unsigned long *) = &Values::assign;
        (this->*assignRange)(other.begin(), other.end());
        m_changed = true;
    }
    ~RHFastFindRangeArray() { erase(begin(), end()); }
    unsigned long *m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    unsigned long m_value;
};

#endif
