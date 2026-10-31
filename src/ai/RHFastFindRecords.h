#ifndef RHFASTFINDRECORDS_H
#define RHFASTFINDRECORDS_H

#include "RHFastFindGrid.h"
#include "SBResourceManager.h"

// SIZE 0xc0
class RHFastFindAssignmentC0
{
public:
    RHFastFindAssignmentC0 &FUN_004fec70(const RHFastFindAssignmentC0 &source);
    RHFastFindPointerArray m_arrays[6];
};

// SIZE 0xa0
class RHFastFindAssignmentA0
{
public:
    RHFastFindAssignmentA0 &FUN_004fedb0(const RHFastFindAssignmentA0 &source);
    RHFastFindPointerArray m_arrays[5];
};

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

class RHFastFindClearedWordRecord : public std::vector<unsigned short>
{
public:
    ~RHFastFindClearedWordRecord()
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)this)->*erase)((int *)begin(), (int *)end());
    }
    char m_10[0x10];
};

class RHFastFindRecordStorage
{
public:
    ~RHFastFindRecordStorage()
    {
        ((RHScriptFXArray *)this)->Unk005008e0(m_first, m_last);
        delete[] m_first;
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }
    char m_00[4];
    void **m_first;
    void **m_last;
    void **m_end;
};

class RHFastFindClearedPointerRecord : public RHFastFindRecordStorage
{
public:
    ~RHFastFindClearedPointerRecord()
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)this)->*erase)((int *)m_first, (int *)m_last);
    }
    char m_10[0x10];
};

class RHUnk004fd7f0
{
public:
    RHFastFindClearedPointerRecord m_00;
    RHFastFindClearedWordRecord m_20;
    RHFastFindClearedPointerRecord m_40;
    RHFastFindClearedPointerRecord m_60;
    RHFastFindClearedPointerRecord m_80;
    RHFastFindClearedPointerRecord m_a0;
    ~RHUnk004fd7f0();
    RHUnk004fd7f0 &operator=(const RHUnk004fd7f0 &other)
    {
        ((RHFastFindAssignmentC0 *)this)->FUN_004fec70((const RHFastFindAssignmentC0 &)other);
        return *this;
    }
};

class RHUnk004fda20
{
public:
    RHUnk004fda20();
    RHFastFindRangeArray m_00;
    RHFastFindRangeArray m_20;
    RHFastFindRangeArray m_40;
    RHFastFindRangeArray m_60;
    SBResourceSurfaceArray m_80;
    ~RHUnk004fda20();
    RHUnk004fda20 &operator=(const RHUnk004fda20 &other)
    {
        ((RHFastFindAssignmentA0 *)this)->FUN_004fedb0((const RHFastFindAssignmentA0 &)other);
        return *this;
    }
};

class RHUnk004fe200
{
public:
    int FUN_004fe220();
    void FUN_004fe250(RHUnk004fd7f0 *first, RHUnk004fd7f0 *last);
    void FUN_004feec0();
    int m_0;
    RHUnk004fd7f0 *m_4;
    RHUnk004fd7f0 *m_8;
    RHUnk004fd7f0 *m_c;
};

class RHUnk004fe260
{
public:
    int FUN_004fe280();
    void FUN_004fe2b0(RHUnk004fda20 *first, RHUnk004fda20 *last);
    void Resize(unsigned count, const RHUnk004fda20 &value);
    void Insert(RHUnk004fda20 *position, unsigned count, const RHUnk004fda20 &value);
    void FUN_004fefb0();
    unsigned Size() const { return m_4 == 0 ? 0 : m_8 - m_4; }
    int m_0;
    RHUnk004fda20 *m_4;
    RHUnk004fda20 *m_8;
    RHUnk004fda20 *m_c;
};

#endif
