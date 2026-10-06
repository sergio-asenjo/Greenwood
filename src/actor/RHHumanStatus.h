// RHHumanStatus — declarations shared by RHHumanStatus.cpp (decompiled TU).
//
// BINDING (0x0051d5d0): RHHumanStatus::Serialize(SBFile&). See
// src/RHHumanStatus.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHHumanStatus::Serialize (0x0051d5d0): the object carries a vptr at +0x00
// (the serialised data starts at +0x04), then a 2-element array of 8-byte
// records at +0x04.

#include "SB.h"

class RHHumanStatusEntry
{
public:
    int m_f0; // [0x00]
    int m_f4; // [0x04]
};

class RHHumanStatus
{
public:
    // Virtual so the object layout carries the vptr at +0x00 the target
    // instructions imply (the first serialised field is at +0x04).
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    RHHumanStatusEntry m_entries[2]; // [0x04]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h and
// include/RHMissionStat.h; no TU includes more than one of those headers.
void RHSerializeName(SBFile &file, const char *name);
