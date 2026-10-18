#ifndef RHSEQUENCEGENERICCALLS_H
#define RHSEQUENCEGENERICCALLS_H

class RHUnk00584d60
{
public:
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char data[0x64];
    void SetFlag(bool value) { data[0x60] = value; }
};

#endif
