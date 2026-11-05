#ifndef SBRESOURCETEXTARRAYLIFETIME_H
#define SBRESOURCETEXTARRAYLIFETIME_H

#include "SBResourceManager.h"

// FUNCTION: GAME 0x0057c820
template<> inline SBResourceTextArray<char>::~SBResourceTextArray()
{
    Destroy();
}

// FUNCTION: GAME 0x00605bd0
template<> inline SBResourceTextArray<wchar_t>::~SBResourceTextArray()
{
    Destroy();
}

#endif
