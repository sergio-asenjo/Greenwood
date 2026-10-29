#ifndef RHSEQUENCETIMEDCALLS_H
#define RHSEQUENCETIMEDCALLS_H

#include "RHSequenceGenericCalls.h"

class RHSword;

class __declspec(novtable) RHUnk005861c0 : public RHUnk00584d60
{
public:
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value68, unsigned short value6a);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, void *value78, unsigned short value68);
    RHUnk005861c0(unsigned short level, int command, void *actor, unsigned short amount, unsigned short value);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, unsigned short value6a, int style);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, RHSword *sword, int value74);
    ~RHUnk005861c0();
    void *FUN_00586090(unsigned int flags);
    RHUnk005861c0 *FUN_005862c0();
    void *m_64;
    unsigned short m_68;
    unsigned short m_6a;
    char m_6c;
    char m_6d[3];
    RHSword *m_70;
    int m_74;
    void *m_78;
};

#endif
