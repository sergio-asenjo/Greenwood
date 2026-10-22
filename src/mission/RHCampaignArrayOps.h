#ifndef RHCAMPAIGNARRAYOPS_H
#define RHCAMPAIGNARRAYOPS_H

#include <vector>

class RHCampaignArrayOps
{
public:
    char m_allocator[4];
    void **m_first;
    void **m_last;
    void **m_end;
    unsigned size() const { return m_first ? m_last - m_first : 0; }
    unsigned capacity() const { return m_first ? m_end - m_first : 0; }
    static __forceinline void **ConstructCopy(void *const *first, void *const *last, void **destination)
    {
        for (; first != last; ++first, ++destination)
            if (destination)
                *destination = *first;
        return destination;
    }
    void FUN_0044ea70();
    unsigned FUN_004580a0()
    {
        typedef std::vector<int> Values;
        unsigned (Values::*capacity)() const = &Values::capacity;
        return (((const Values *)this)->*capacity)();
    }
    RHCampaignArrayOps &FUN_00457a30(const RHCampaignArrayOps &value)
    {
        typedef std::vector<int> Values;
        Values &(Values::*assign)(const Values &) = &Values::operator=;
        (((Values *)this)->*assign)((const Values &)value);
        return *this;
    }
    void FUN_00570330();
};

#endif
