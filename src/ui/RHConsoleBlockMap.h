#ifndef RHCONSOLEBLOCKMAP_H
#define RHCONSOLEBLOCKMAP_H

#include <string.h>

struct RHConsoleBlockMap
{
    char m_00[0x58];
    int m_counts[17];
    unsigned long Counter(unsigned index) const
    {
        unsigned long value;
        memcpy(&value, m_00 + index * sizeof(value), sizeof(value));
        return value;
    }
};

#endif
