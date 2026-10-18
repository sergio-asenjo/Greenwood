#include "SBNullstr.h"
#include "RHSectorProduction.h"


#include "RHSectorProductionPC.h"

// FUNCTION: GAME 0x0055bb00
bool RHSectorProductionPC::FUN_0055bb00(int value)
{
    int *first = (int *)(*(char **)((char *)this + 0x40) + 0x48);
    int *last = first + 3;
    int *current;
    for (current = first; current != last; ++current)
        if (*current == value)
            break;
    return current != last;
}

class RHSectorProductionBonus
{
public:
    RHSectorProductionBonus(int action, int flags, unsigned short count);
    RHSectorProductionBonus(unsigned long relic, int flags, int count);
};

RHSectorProductionBonus::RHSectorProductionBonus(int, int, unsigned short) {}
RHSectorProductionBonus::RHSectorProductionBonus(unsigned long, int, int) {}

class RHSectorProductionActorList
{
public:
    void GoTo(int index);
};

void RHSectorProductionActorList::GoTo(int) {}
