#ifndef RHSOLDIERHUMANCALLS_H
#define RHSOLDIERHUMANCALLS_H

struct RHSoldierTransition
{
    char m_00[0x40];
    int m_40;
};

class RHSoldierHumanCalls
{
public:
    void FUN_00478e50(class RHUnk00613e90 &position);
};

#endif
