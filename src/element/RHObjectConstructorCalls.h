#ifndef RHOBJECTCONSTRUCTORCALLS_H
#define RHOBJECTCONSTRUCTORCALLS_H

class RHObjectConstructorCalls
{
public:
    RHObjectConstructorCalls(unsigned long type, bool flag, int action);
    ~RHObjectConstructorCalls();
    unsigned char unknown[0x100];
};

#endif
