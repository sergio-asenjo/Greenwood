#ifndef SBHARDWARE_H
#define SBHARDWARE_H

class SBHardware
{
public:
    static unsigned long GetAmountOfPhysicalMemory();
    static unsigned long GetAmountOfFreePhysicalMemory();
    static unsigned long GetAmountOfPageMemory();
    static unsigned long GetAmountOfFreePageMemory();
    static unsigned long Emit();
};

#endif
