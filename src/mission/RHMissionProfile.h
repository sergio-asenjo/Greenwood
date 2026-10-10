#ifndef RHMISSIONPROFILE_H
#define RHMISSIONPROFILE_H

#include "RHCivilianProfile.h"

class RHCharacterProfile;

class RHMissionArrayStorage
{
public:
    void *FUN_004609a0(void *first, void *last);
    void FUN_004e5820(void *position, const unsigned long &value);
};

template <class T>
class RHMissionArray : public RHProfileString
{
public:
    explicit RHMissionArray(const std::allocator<char> &allocator = std::allocator<char>()) : RHProfileString(allocator) {}
    T *begin() { return *(T **)((char *)this + 4); }
    T *end() { return *(T **)((char *)this + 8); }
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
};

class RHMissionProfile
{
public:
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
    RHProfileText m_04; // [0x04]
    RHProfileString m_14; // [0x14]
    RHProfileString m_24; // [0x24]
    int m_34; // [0x34]
    char m_38[0x3c]; // [0x38,0x74)
    RHMissionArray<RHCharacterProfile *> m_74; // [0x74]
    RHMissionArray<unsigned long> m_84; // [0x84]
    RHMissionArray<unsigned long> m_94; // [0x94]
    RHMissionArray<unsigned long> m_a4; // [0xa4]
    RHProfileString m_b4; // [0xb4]
    RHProfileString m_c4; // [0xc4]
    RHProfileString m_d4; // [0xd4]
    RHProfileString m_e4; // [0xe4]
};

#endif
