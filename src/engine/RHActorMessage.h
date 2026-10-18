#ifndef RHACTORMESSAGE_H
#define RHACTORMESSAGE_H

#include "RHMessage.h"

class RHUnk00549250 : public RHMessage
{
public:
    RHUnk00549250(int command, void *actor);
    ~RHUnk00549250();
    void *FUN_00549280(unsigned flags);
    int m_0c;
    void *m_10;
};

#endif
