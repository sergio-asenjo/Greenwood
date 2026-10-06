// RHElementActorSoldier — declarations for RHElementActorSoldier.cpp (decompiled
// TU).
//
// BINDING (0x004a5790): RHElementActorSoldier::Serialize(SBFile&). See
// src/RHElementActorSoldier.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementActorSoldier::Serialize (0x004a5790): the base RHElementActorNPC
// occupies [0x00, 0xa3c) (vptr + its own fields), and RHElementActorSoldier's
// own 4-byte field sits at +0xa3c. Only the bytes the matched function touches
// are laid out; every other byte is opaque padding. The base class's
// Serialize definition is shared with src/RHElementActorCivilian_stubs.cpp and
// is not redefined here.

#include "SB.h"

class RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0xa38]; // [0x04, 0xa3c): RHElementActorNPC-owned, untouched here
};

class RHElementActorSoldier : public RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

private:
    int m_unkA3c; // [0xa3c]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHMissionStat.h and include/RHHumanStatus.h; no TU includes more than
// one of those headers.
void RHSerializeName(SBFile &file, const char *name);
