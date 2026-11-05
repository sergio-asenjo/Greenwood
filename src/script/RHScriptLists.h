#ifndef RHSCRIPT_LISTS_H
#define RHSCRIPT_LISTS_H

#include <iterator>
#include "RHScript.h"
#include "RHScriptIndexedList.h"

struct RHScriptSelectionEngine
{
    char padding[0x49f8];
    RHScriptZoneList selection;
};

#endif
