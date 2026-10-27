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
