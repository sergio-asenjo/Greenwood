#include "RHElementObject.h"
#include "RHSequenceElementCalls.h"

// FUNCTION: GAME 0x004b23a0
char RHElementObject::Instruct(RHSequenceElementCalls *element)
{
    element->Slot0c(5, 1);
    return false;
}
