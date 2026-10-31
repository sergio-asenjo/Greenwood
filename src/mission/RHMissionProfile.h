#ifndef RHMISSIONPROFILE_H
#define RHMISSIONPROFILE_H

#include "RHCivilianProfile.h"
#include <vector>

class RHCharacterProfile;

class RHMissionArrayStorage
{
public:
    void *FUN_004609a0(void *first, void *last)
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        return (((Values *)this)->*erase)((int *)first, (int *)last);
    }
    void FUN_004e5820(void *position, const unsigned long &value)
    {
        typedef std::vector<unsigned long> Values;
        unsigned long *(Values::*insert)(unsigned long *, const unsigned long &) = &Values::insert;
        (((Values *)this)->*insert)((unsigned long *)position, value);
    }
};

template <class T>
class RHMissionArray
{
public:
    explicit RHMissionArray(const std::allocator<T> &allocator = std::allocator<T>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
    ~RHMissionArray()
    {
        Destroy(m_first, m_last);
        m_allocator.deallocate(m_first, m_end - m_first);
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }
    void Destroy(T *first, T *last)
    {
        for (; first != last; ++first)
            m_allocator.destroy(first);
    }
    T *begin() { return m_first; }
    T *end() { return m_last; }
    unsigned int GetSize() { return begin() == 0 ? 0 : end() - begin(); }
    void FUN_004609a0(void *first, void *last)
    {
        ((RHMissionArrayStorage *)this)->FUN_004609a0(first, last);
    }
    void FUN_004e5820(void *position, const unsigned long &value)
    {
        ((RHMissionArrayStorage *)this)->FUN_004e5820(position, value);
    }
    void InsertLast(const T &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)end(), 1, (RHSaveGame *const &)value);
    }
    std::allocator<T> m_allocator;
    T *m_first;
    T *m_last;
    T *m_end;
};

class RHMissionProfile
{
public:
    ~RHMissionProfile();
    RHMissionProfile()
    {
        m_00 = 0;
        m_34 = 7;
        m_38[0] = 0;
        *(int *)(m_38 + 8) = 0;
        *(int *)(m_38 + 12) = 0;
        *(short *)(m_38 + 16) = 0;
        *(short *)(m_38 + 18) = 0;
        *(short *)(m_38 + 20) = 0;
        *(short *)(m_38 + 22) = 0;
        *(short *)(m_38 + 24) = 0;
        *(short *)(m_38 + 26) = 0;
        m_38[28] = 0;
        struct ZeroRun { int first; int second; short third; };
        ZeroRun *run = (ZeroRun *)(m_38 + 29);
        run->first = 0;
        run->second = 0;
        run->third = 0;
        m_38[39] = 0;
        m_38[40] = 0;
        m_38[41] = 0;
        m_38[42] = 0;
        *(short *)(m_38 + 44) = 0;
        *(short *)(m_38 + 46) = 0;
        *(short *)(m_38 + 48) = 0;
        *(short *)(m_38 + 50) = 0;
        *(short *)(m_38 + 52) = 0;
        *(short *)(m_38 + 54) = 0;
        *(short *)(m_38 + 56) = 0;
        *(short *)(m_38 + 58) = 0;
    }

    int m_00; // [0x00]
    std::string m_04; // [0x04]
    std::string m_14; // [0x14]
    std::string m_24; // [0x24]
    int m_34; // [0x34]
    char m_38[0x3c]; // [0x38,0x74)
    RHMissionArray<RHCharacterProfile *> m_74; // [0x74]
    RHMissionArray<unsigned long> m_84; // [0x84]
    RHMissionArray<unsigned long> m_94; // [0x94]
    RHMissionArray<unsigned long> m_a4; // [0xa4]
    RHMissionArray<unsigned long> m_b4; // [0xb4]
    std::string m_c4; // [0xc4]
    std::string m_d4; // [0xd4]
    std::string m_e4; // [0xe4]
};

#endif
