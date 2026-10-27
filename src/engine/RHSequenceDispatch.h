#ifndef RHSEQUENCEDISPATCH_H
#define RHSEQUENCEDISPATCH_H

#include "RHSequenceManager.h"

class RHUnk00582620
{
public:
    bool FUN_00582530();
    void FUN_00582560();
    void FUN_00582620(int arg);
    char m_00[8];
    RHManagerList<RHSequenceElement *> m_list;
    unsigned short m_2c;
    unsigned short m_2e;
    short m_30;
    char m_32[2];
    char m_34;
};

#endif
