// RHElementWaspNest — declarations for RHElementWaspNest.cpp (decompiled TU).
//
// BINDING (0x004be1e0): RHElementWaspNest::Serialize(SBFile&). See
// src/RHElementWaspNest.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementWaspNest::Serialize (0x004be1e0): the base RHElementProjectile
// occupies [0x00, 0x15c) (vptr + its own fields), and RHElementWaspNest's own
// 4-byte field sits at +0x15c. Only the bytes the matched function touches are
// laid out; every other byte is opaque padding. The base is declared here with
// a different (smaller) opaque size than include/RHElementPurse.h uses; the
// mangled RHElementProjectile::Serialize symbol is unaffected.

#include "SB.h"

class RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0x158]; // [0x04, 0x15c): RHElementProjectile-owned, untouched here
};

class RHElementWaspNest : public RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

private:
    int m_unk15c; // [0x15c]
};
