#ifndef RHMAPDESCRIPTION_H
#define RHMAPDESCRIPTION_H

#include "Decomp.h"

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
        undefined m_00[0x30]; // 0x00
        unsigned m_30; // 0x30
        undefined m_34[4]; // 0x34
        unsigned m_38; // 0x38
        undefined m_3c[0x08]; // 0x3c
        unsigned m_44; // 0x44
    };
    Entry *FUN_0063c9e0(unsigned);
    char m_00[0x1c]; // 0x00
};

#endif
