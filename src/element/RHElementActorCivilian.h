// RHElementActorCivilian — declarations shared by RHElementActorCivilian.cpp
// (decompiled TU) and RHElementActorCivilian_stubs.cpp (external-symbol stubs).
//
// BINDING (0x004711c0): RHElementActorCivilian::Serialize(SBFile&). See
// src/RHElementActorCivilian.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementActorCivilian::Serialize (0x004711c0): the base RHElementActorNPC
// occupies [0x00, 0x704) (vptr + its own fields), and RHElementActorCivilian's
// own 4-byte field sits at +0x704. Only the bytes the matched function touches
// are laid out; every other byte is opaque padding.

#include "SB.h"

class RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0x700]; // [0x04, 0x704): RHElementActorNPC-owned, untouched here
};

class RHElementActorCivilian : public RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

private:
    int m_unk704; // [0x704]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHMissionStat.h and include/RHHumanStatus.h; no TU includes more than
// one of those headers.
void RHSerializeName(SBFile &file, const char *name);
