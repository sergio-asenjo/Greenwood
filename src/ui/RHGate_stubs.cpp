#include "SBNullstr.h"
#include "RHGate.h"

void RHGate::Emit(SBFile &file)
{
    Serialize(file);
}
