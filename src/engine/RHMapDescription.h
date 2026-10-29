#ifndef RHMAPDESCRIPTION_H
#define RHMAPDESCRIPTION_H

#include "Decomp.h"
#include <string>
#include <vector>

class RHUnk0063c8b0
{
public:
    RHUnk0063c8b0();
    // FUNCTION: GAME 0x0063cd70
    ~RHUnk0063c8b0() {}
    unsigned m_0;
    unsigned m_4;
    std::vector<int> m_8;
};

class RHUnk0063e360
{
public:
    RHUnk0063e360();
    // FUNCTION: GAME 0x0063f300
    RHUnk0063e360(const RHUnk0063e360 &source) : m_0(source.m_0), m_4(source.m_4) {}
    unsigned m_0;
    std::vector<int> m_4;
};

class RHUnk0063c840
{
public:
    RHUnk0063c840();
    unsigned m_0;
    unsigned m_4;
};

class RHUnk0063c860
{
public:
    RHUnk0063c860();
    unsigned m_0;
    unsigned m_4;
};

class RHUnk0063c880
{
public:
    RHUnk0063c880();
    unsigned m_0;
    unsigned m_4;
    unsigned m_8;
    unsigned m_c;
};

// SIZE 0x1c
// VTABLE: GAME 0x0067bbd4
class RHMapDescription
{
public:
    RHMapDescription();
    virtual ~RHMapDescription();
    bool FUN_0063cda0(unsigned);
    // SIZE 0x48
    struct Entry
    {
        // Parked: native vector destruction depth differs from the original.
        // STUB: GAME 0x0063cce0
        ~Entry() {}
        RHUnk0063c840 m_00; // 0x00
        std::vector<RHUnk0063c8b0> m_08; // 0x08
        RHUnk0063e360 m_18; // 0x18
        RHUnk0063c880 m_2c; // 0x2c
        RHUnk0063c860 m_3c; // 0x3c
        unsigned m_44; // 0x44
    };
    Entry *FUN_0063c9e0(unsigned);
    void FUN_0063d1a0(std::string &, unsigned);
    std::vector<Entry> m_04; // 0x04
    const char *m_14; // 0x14
    const char *m_18; // 0x18
};

#endif
