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
class RHSequenceElement;
class RHElementActorHuman;
class SBGeoPoint2D;

#include "RHElementActorSoldierCore.h"

struct RHSoldierProfileFlags
{
    unsigned char m_bit0 : 1;
    unsigned char m_bit1 : 1;
    unsigned char m_bit2 : 1;
    unsigned char m_bit3 : 1;
};

struct RHSoldierTransition;

#include "RHSoldierNPCCalls.h"

struct RHMalignityPosition;
struct RHMalignityStimulus;
struct RHSoldierDoorPayload
{
    unsigned short m_00;
    unsigned m_04[4];
    unsigned short m_14;
    void *m_18;
};

class RHSoldierStimulusCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24(RHMalignityStimulus *stimulus) = 0;
    void FUN_004a5dc0(unsigned type, const RHSoldierDoorPayload &payload);
    void FUN_004a64a0(unsigned type, const RHMalignityPosition &position);
};

class RHSoldierActorCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual bool V48() = 0; // vtable+0x48
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c() = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78(void *element, int command) = 0; // vtable+0x78
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88() = 0;
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4(unsigned short value) = 0;
    virtual void Vc8() = 0;
    virtual void Vcc() = 0;
    virtual void Vd0() = 0;
    virtual void Vd4() = 0;
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec() = 0;
    virtual void Vf0() = 0;
    virtual bool Vf4() = 0; // vtable+0xf4
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0; // vtable+0x130
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140(int value) = 0; // vtable+0x140
    virtual void V144(int value) = 0; // vtable+0x144
    virtual void V148(int value) = 0; // vtable+0x148
    virtual void V14c(int value) = 0; // vtable+0x14c
    virtual void V150() = 0;
    virtual void V154() = 0;
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual bool V168() = 0;
};

#include "RHSoldierHumanCalls.h"

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHMissionStat.h and include/RHHumanStatus.h; no TU includes more than
// one of those headers.
void RHSerializeName(SBFile &file, const char *name);
