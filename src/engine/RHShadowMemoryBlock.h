#ifndef RHSHADOWMEMORYBLOCK_H
#define RHSHADOWMEMORYBLOCK_H

class RHShadowMemoryBlock
{
public:
    unsigned char m_data[0x2c];
    void FUN_0059f4e0();
    RHShadowMemoryBlock *FUN_005a0ed0(unsigned flags);
    RHShadowMemoryBlock &FUN_005a0ef0(const RHShadowMemoryBlock &source);
};

#endif
