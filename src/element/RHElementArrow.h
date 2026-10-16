// RHElementArrow — declarations for RHElementArrow.cpp (decompiled TU).
//
// BINDING (0x004a6e10): RHElementArrow::Serialize(SBFile&). See
// src/RHElementArrow.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementArrow::Serialize (0x004a6e10): the base RHElementProjectile occupies
// [0x00, 0x15c) (vptr + its own fields), and RHElementArrow's own fields start
// at +0x15c. Only the bytes the matched function touches are laid out; every
// other byte is opaque padding. The base is declared here with the size that
// places the first own member at +0x15c; the base's Serialize definition is
// shared with src/RHElementPurse_stubs.cpp (and RHElementWaspNest.h uses the
// same opaque size) and is not redefined here.

#include "SB.h"
#include "RHBow.h"

class RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0x158]; // [0x04, 0x15c): RHElementProjectile-owned, untouched here
};

class RHElementArrow : public RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);
    char FUN_004a6640();
    void FUN_004a6a70(void *target);
    void FUN_004a6b80(void *target, bool flag);
    int FUN_004a6ff0();

    void Emit(SBFile &file);

private:
    RHBow *m_bow; // [0x15c]
    char m_160;   // [0x160]
    char m_161;   // [0x161]
    char m_162;   // [0x162]
    char m_163;   // [0x163]
    short m_164;  // [0x164]
    char m_166;   // [0x166]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHElementPurse.h and include/RHElementActorSoldier.h; no TU includes
// more than one of those headers.
void RHSerializeName(SBFile &file, const char *name);
