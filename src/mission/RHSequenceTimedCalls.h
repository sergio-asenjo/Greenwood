#ifndef RHSEQUENCETIMEDCALLS_H
#define RHSEQUENCETIMEDCALLS_H

class RHSword;

class RHUnk005861c0
{
public:
    RHUnk005861c0(unsigned short level, int command, void *actor, unsigned short amount, unsigned short value);
    RHUnk005861c0(unsigned short level, int command, void *actor, void *target, RHSword *sword, int value74);
    ~RHUnk005861c0();
    char data[0x7c];
};

#endif
