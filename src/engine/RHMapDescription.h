#ifndef RHMAPDESCRIPTION_H
#define RHMAPDESCRIPTION_H

#include "Decomp.h"
#include <vector>

class RHUnk0063c8b0
{
public:
    RHUnk0063c8b0();
    // FUNCTION: GAME 0x0063cd70
    ~RHUnk0063c8b0() {}
    unsigned m_0;
    unsigned m_4;
    std::vector<void *> m_8;
};

// SIZE 0x1c
class RHMapDescription
{
public:
    RHMapDescription();
    ~RHMapDescription();
    bool FUN_0063cda0(unsigned);
    // SIZE 0x48
    struct Entry
    {
        // Parked: native vector destruction depth differs from the original.
        // STUB: GAME 0x0063cce0
        ~Entry() {}
        unsigned m_00[2]; // 0x00
        std::vector<RHUnk0063c8b0> m_08; // 0x08
        unsigned m_18; // 0x18
        std::vector<void *> m_1c; // 0x1c
        unsigned m_2c; // 0x2c
        unsigned m_30; // 0x30
        undefined m_34[4]; // 0x34
        unsigned m_38; // 0x38
        undefined m_3c[0x08]; // 0x3c
        unsigned m_44; // 0x44
    };
    Entry *FUN_0063c9e0(unsigned);
    unsigned m_00; // 0x00
    std::vector<Entry> m_04; // 0x04
    const char *m_14; // 0x14
    const char *m_18; // 0x18
};

#endif
