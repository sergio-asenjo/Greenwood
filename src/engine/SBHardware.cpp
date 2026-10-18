#include <windows.h>
#include "SBHardware.h"
#include <string>

class __declspec(novtable) RHUnk0060f8a0
{
public:
    virtual ~RHUnk0060f8a0();
    std::string m_04;
};

// FUNCTION: GAME 0x0060f8a0
RHUnk0060f8a0::~RHUnk0060f8a0()
{
    *(unsigned *)this = 0x67a874;
}

// FUNCTION: GAME 0x0060f8f0
unsigned long SBHardware::GetAmountOfPhysicalMemory()
{
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    return status.dwTotalPhys >> 20;
}

// FUNCTION: GAME 0x0060f910
unsigned long SBHardware::GetAmountOfFreePhysicalMemory()
{
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    return status.dwAvailPhys >> 20;
}

// FUNCTION: GAME 0x0060f930
unsigned long SBHardware::GetAmountOfPageMemory()
{
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    return status.dwTotalPageFile >> 20;
}

// FUNCTION: GAME 0x0060f950
unsigned long SBHardware::GetAmountOfFreePageMemory()
{
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    return status.dwAvailPageFile >> 20;
}

unsigned long SBHardware::Emit()
{
    return GetAmountOfPhysicalMemory() + GetAmountOfFreePhysicalMemory() + GetAmountOfPageMemory() + GetAmountOfFreePageMemory();
}
