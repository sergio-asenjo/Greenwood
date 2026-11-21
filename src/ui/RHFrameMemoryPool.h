#ifndef RHFRAMEMEMORYPOOL_H
#define RHFRAMEMEMORYPOOL_H

#include <vector>

struct RHFramePoolBlock
{
    void *address;
    unsigned long size;
    unsigned long page;
};

struct RHFramePoolList;

struct RHFramePoolPage
{
    void *address;
    unsigned long index;
};

class RHFrameMemoryPool
{
public:
    RHFrameMemoryPool();
    ~RHFrameMemoryPool();
    void FUN_005062e0();
    unsigned long FUN_00506460(unsigned long size);
    void FUN_005064b0(RHFramePoolList *list, const RHFramePoolBlock &value);
    bool FUN_00506560(RHFramePoolList *list, const RHFramePoolBlock &value);
    unsigned long FUN_005065b0() const;
    unsigned long FUN_005065d0() const;
    int FUN_00506620();
    static bool FUN_00506600(const RHFramePoolBlock &first, const RHFramePoolBlock &second);
    unsigned long Size() const { return m_pages.size(); }

    RHFramePoolList *m_free;
    RHFramePoolList *m_used;
    std::vector<RHFramePoolPage> m_pages;
};

#endif
