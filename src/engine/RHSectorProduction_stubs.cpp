#include "RHSectorProduction.h"

// Target 0x0045a910.
RHSectorProduction::Occupant &RHSectorProduction::Occupant::operator=(const Occupant &)
{
    return *this;
}

// Target 0x00459100.
void RHSectorProduction::Occupants::Destroy(Occupant *, Occupant *) {}

// Target 0x005815f0, not 0x004582d0.
void RHSectorProduction::Occupants::Insert(Occupant *, unsigned, const Occupant &) {}
