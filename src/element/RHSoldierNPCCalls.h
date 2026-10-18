#ifndef RHSOLDIERNPCCALLS_H
#define RHSOLDIERNPCCALLS_H

struct RHSoldierSequenceElement
{
    char m_00[0x10];
    int m_10;
    char m_14[0x48];
    int m_5c;
};

class RHSoldierNPCCalls
{
public:
    void FUN_0048b510(void *element);
    int FUN_0048d100(RHSoldierSequenceElement *element);
    void FUN_0048d790(RHSoldierSequenceElement *element);
};

#endif
