#include "SBNullstr.h"
#include "../engine/RHGate.h"

void RHGateEmit(RHUnk0051aa00 *gate, SBFile &file)
{
    gate->Serialize(file);
}
