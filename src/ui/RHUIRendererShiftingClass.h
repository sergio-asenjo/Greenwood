#ifndef RHUIRENDERERSHIFTINGCLASS_H
#define RHUIRENDERERSHIFTINGCLASS_H

class RHUIRendererShifting
{
public:
    RHUIRendererShifting();
    ~RHUIRendererShifting();
    void *FUN_005cbe30(unsigned flags);
    bool Render(unsigned int id);
    void SetCounter(unsigned short value) { *(unsigned short *)(m_bytes + 0x50) = value; }
    void Emit();
    char m_bytes[0x54];
};

#endif
