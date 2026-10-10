#include "SBNullstr.h"
#include "SBSimpleVirtualMachine.h"

void SBSimpleUnk005f9510(void *, const char *, ...)
{
}

// FUNCTION: GAME 0x0063a450
int SBSimpleUnkCodeManager::FUN_0063a450(const char *name)
{
    if (!OpenSCB(name, true))
        return 0;
    int size = ReadSCB();
    CloseSCB();
    return size;
}
