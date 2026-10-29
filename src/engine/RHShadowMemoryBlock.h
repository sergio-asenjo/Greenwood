#ifndef RHSHADOWMEMORYBLOCK_H
#define RHSHADOWMEMORYBLOCK_H

#include <list>

struct RHShadowMemoryRange
{
    unsigned long m_first;
    unsigned long m_last;
};

struct RHShadowMemoryNode;

class RHShadowMemoryBlockRanges
{
public:
    RHShadowMemoryBlockRanges() : m_dirty(true) {}
    ~RHShadowMemoryBlockRanges();
    std::list<RHShadowMemoryRange> m_list;
    RHShadowMemoryNode *m_current;
    bool m_dirty;
    unsigned char m_unknown[23];
};

class RHShadowMemoryBlock
{
public:
    ~RHShadowMemoryBlock() {}
    unsigned long m_tag;
    RHShadowMemoryBlockRanges m_ranges;
    void FUN_0059f4e0();
    RHShadowMemoryBlock *FUN_005a0ed0(unsigned flags);
    RHShadowMemoryBlock &FUN_005a0ef0(const RHShadowMemoryBlock &source);
};

struct RHShadowIteratorMemoryRange
{
    unsigned long m_first;
    unsigned long m_last;
};

class RHShadowIteratorMemoryBlockRanges
{
public:
    RHShadowIteratorMemoryBlockRanges() : m_dirty(true) {}
    ~RHShadowIteratorMemoryBlockRanges();
    std::list<RHShadowIteratorMemoryRange> m_list;
    RHShadowMemoryNode *m_current;
    bool m_dirty;
    unsigned char m_unknown[23];
};

class RHShadowIteratorMemoryBlock
{
public:
    ~RHShadowIteratorMemoryBlock() {}
    unsigned long m_tag;
    RHShadowIteratorMemoryBlockRanges m_ranges;
};

#endif
