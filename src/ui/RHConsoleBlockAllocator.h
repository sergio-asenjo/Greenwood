#ifndef RHCONSOLEBLOCKALLOCATOR_H
#define RHCONSOLEBLOCKALLOCATOR_H

struct RHConsoleBlockMap
{
    char m_00[0x58];
    int m_counts[17];
};

class RHConsoleBlockAllocator
{
public:
    bool FUN_00506070(RHConsoleBlockMap *);
    int FUN_00506620();
};

#endif
