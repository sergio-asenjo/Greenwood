// RHElementPurse — declarations shared by RHElementPurse.cpp (decompiled TU)
// and RHElementPurse_stubs.cpp (external-symbol stubs).
//
// BINDING (0x004b9830): RHElementPurse::Serialize(SBFile&). See
// src/RHElementPurse.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementPurse::Serialize (0x004b9830): the base RHElementProjectile occupies
// [0x00, 0x168) (vptr + its own fields), and RHElementPurse's own 16-bit field
// sits at +0x168. Only the bytes the matched function touches are laid out;
// every other byte is opaque padding.

#include "SB.h"

class RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0x164]; // [0x04, 0x168): RHElementProjectile-owned, untouched here
};

class RHElementPurse : public RHElementProjectile
{
public:
    RHElementPurse(void *victim);
    int FUN_004b9200();
    int FUN_004b9210();
    bool FUN_004b97c0();
    unsigned short FUN_004b98a0();
    void AddChild(class RHElementCoin *coin);
    void FUN_004b9990();
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

private:
    short m_unk168; // [0x168]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHMissionStat.h and include/RHHumanStatus.h; no TU includes more than
// one of those headers.
void RHSerializeName(SBFile &file, const char *name);
