#ifndef RHSOLDIERNPCCALLS_H
#define RHSOLDIERNPCCALLS_H

struct RHSoldierSequenceElement
{
    char m_00[0x10];
    int m_10;
    char m_14[0x44];
    int m_58;
    int m_5c;
};

struct RHUnk0048da10;

class RHSoldierNPCCalls
{
public:
    void FUN_0048b510(void *element);
    int FUN_0048d100(RHSoldierSequenceElement *element);
    void FUN_0048d790(RHSoldierSequenceElement *element);
    bool FUN_0048da40(RHUnk0048da10 *value);
};

#endif
