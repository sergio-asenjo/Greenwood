#ifndef RHMAPWINDOWCLASS_H
#define RHMAPWINDOWCLASS_H

#include "Decomp.h"
#include "RHMenuScreenTimer.h"
#include <deque>
#include <vector>
#include <list>

class RHMapWindow
{
public:
    static unsigned long FUN_0053b6b0(unsigned long source, bool colorize, bool pause);
    static void FUN_0053b330(unsigned long surface, unsigned short amount, float factor);
    unsigned FUN_0053baa0(unsigned);
    void FUN_0053bb30(unsigned);
    void FUN_0053bbe0();
    void FUN_0053c7e0();
    typedef RHMenuScreenTimer Timer;
    undefined m_00[0x191c];
    std::deque<std::vector<void *> > m_191c;
    undefined m_194c[0x34];
    std::list<Timer> m_1980;
    unsigned m_198c;
};

#endif
