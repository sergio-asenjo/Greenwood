// RHElementActorSoldier.cpp — translation unit with __FILE__ evidence at
// 0x004a5790 ("P:\Robin Hood\RHelementactorsoldier.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004a5790 -> RHElementActorSoldier::Serialize(SBFile&)):
//   - TU:        rhelementactorsoldier.cpp (embedded __FILE__ string
//                0x006ae880).
//   - Class:     RHElementActorSoldier (symbols/oracle-correlation.tsv:
//                rhelementactorsoldier -> class RHElementActorSoldier,
//                55 methods).
//   - Method:    RHElementActorSoldier::Serialize(SBFile&) — the Mac oracle's
//                rhelementactorsoldier.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x000c5468 Serialize).
//   - Signals:
//       * the function first calls the base 0x0048b5d0 with `this` unchanged
//         and returns false immediately if it fails; 0x0048b5d0 writes the tag
//         "RHElementActorNPC" — i.e. the base RHElementActorNPC::Serialize is
//         invoked first on the same object;
//       * on success it writes the tag "RHElementActorSoldier" (string
//         0x006ae960) via 0x005e1b70 — the name matches the TU's class;
//       * then ONE SBFile::Access 0x005f52b0 on this+0xa3c (size 4) with the
//         "Serialize failed reason is %s" assert pattern (format 0x006a7390,
//         empty fallback 0x006773d0) at line 2518 (0x9d6) — the exact
//         serializer idiom seen in RHElementActorCivilian;
//       * no loop and no `new`.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHElementActorSoldier.h"
#include "RHArtificialMalignity.h"

#define RHSOLDIER_FIELD(type, offset) (*(type *)((char *)this + (offset)))
#define RHSOLDIER_PROFILE(type, offset) (*(type *)(RHSOLDIER_FIELD(char *, 0xa1c) + (offset)))
#define RHSOLDIER_VBASE ((char *)this + 0x49c + (*(int **)((char *)this + 0x49c))[1])

// FUNCTION: GAME 0x004a1cc0
unsigned short RHElementActorSoldier::FUN_004a1cc0()
{
    return ((RHMalignityOwnerCalls *)((char *)this + 0x6e8))->FUN_00438710(RHSOLDIER_PROFILE(unsigned short, 0x3e), 0.5f, 2.0f, 100);
}

// FUNCTION: GAME 0x004a1cf0
unsigned short RHElementActorSoldier::FUN_004a1cf0()
{
    return RHSOLDIER_PROFILE(unsigned short, 0x40);
}

// FUNCTION: GAME 0x004a1d00
unsigned short RHElementActorSoldier::FUN_004a1d00()
{
    return ((RHMalignityOwnerCalls *)((char *)this + 0x6e8))->FUN_00438710(RHSOLDIER_PROFILE(unsigned short, 0x30), 0.5f, 1.5f, 10000);
}

// FUNCTION: GAME 0x004a1d30
bool RHElementActorSoldier::FUN_004a1d30()
{
    return RHSOLDIER_FIELD(void *, 0xa24) || RHSOLDIER_FIELD(void *, 0xa28);
}

// FUNCTION: GAME 0x004a1d50
void *RHElementActorSoldier::FUN_004a1d50()
{
    return RHSOLDIER_FIELD(void *, 0xa24);
}

// FUNCTION: GAME 0x004a1d60
void *RHElementActorSoldier::FUN_004a1d60()
{
    return RHSOLDIER_FIELD(void *, 0xa28);
}

// FUNCTION: GAME 0x004a1d70
void RHElementActorSoldier::FUN_004a1d70(void *neighbour)
{
    RHSOLDIER_FIELD(void *, 0xa24) = neighbour;
}

// FUNCTION: GAME 0x004a1d80
void RHElementActorSoldier::FUN_004a1d80(void *neighbour)
{
    RHSOLDIER_FIELD(void *, 0xa28) = neighbour;
}

// FUNCTION: GAME 0x004a1d90
int RHElementActorSoldier::FUN_004a1d90()
{
    return RHSOLDIER_PROFILE(int, 0x80);
}

// FUNCTION: GAME 0x004a1da0
int RHElementActorSoldier::FUN_004a1da0()
{
    return RHSOLDIER_PROFILE(int, 0x84);
}

// FUNCTION: GAME 0x004a1db0
int RHElementActorSoldier::FUN_004a1db0()
{
    return RHSOLDIER_PROFILE(int, 0x44);
}

// FUNCTION: GAME 0x004a2550
void RHElementActorSoldier::FUN_004a2550(void *element)
{
    ((RHSoldierNPCCalls *)this)->FUN_0048b510(element);
    if (((RHSoldierActorCalls *)this)->V130() == 0)
        ++*(int *)((char *)((RHScriptBatchCalls *)g_pEngine)->Unk004e3cc0() + 0x20);
}

// FUNCTION: GAME 0x004a5790
bool RHElementActorSoldier::Serialize(SBFile &file)
{
    if (!RHElementActorNPC::Serialize(file))
        return false;

    // STRING: GAME 0x6ae960
    RHSerializeName(file, "RHElementActorSoldier");

    if (file.Access(&m_unkA3c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6ae880
                 "P:\\Robin Hood\\RHelementactorsoldier.cpp",
                 2518,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return true;
}

// Parked: VC6 duplicates the m_40 reset tail instead of jumping over the sparse-switch cases.
// STUB: GAME 0x004a5340
bool RHElementActorSoldier::FUN_004a5340(unsigned flags, RHSoldierTransition *element)
{
    if ((flags & 0x80) && !RHSOLDIER_FIELD(unsigned char, 0xa2c))
    {
        ((RHSoldierActorCalls *)this)->V78(element, 0x83);
        return true;
    }
    if ((flags & 4) && RHSOLDIER_FIELD(unsigned char, 0xa2c) == 1)
        return true;
    if (flags & 0x200)
    {
        switch (element->m_40)
        {
        case 0:
            ((RHSoldierActorCalls *)this)->V78(element, 0x1d);
        case 4:
        case 5:
            ((RHSoldierActorCalls *)this)->V78(element, 0x24);
        }
        element->m_40 = 5;
        return true;
    }
    return ((RHSoldierHumanCalls *)this)->FUN_00475b00(flags, element);
}

// FUNCTION: GAME 0x004a53d0
bool RHElementActorSoldier::FUN_004a53d0(unsigned flags, RHSoldierTransition *element)
{
    if (RHSOLDIER_FIELD(unsigned char, 0xa2c) == 1 && (flags & 1) && !(flags & 0x80))
        ((RHSoldierActorCalls *)this)->V78(element, 0x84);
    if (RHSOLDIER_FIELD(int, 0x144) != 6)
        return ((RHSoldierHumanCalls *)this)->FUN_00475970(flags, element);
    if ((flags & 1) && !(flags & 0x10000))
    {
        ((RHSoldierActorCalls *)this)->V78(element, 0x25);
        if (!(flags & 8))
        {
            ((RHSoldierActorCalls *)this)->V78(element, 0x20);
            element->m_40 = 0;
            return true;
        }
        element->m_40 = 4;
    }
    return true;
}

// Parked: the two true-return blocks are cross-jumped; the target keeps the case 1-3 block separate.
// STUB: GAME 0x004a5460
bool RHElementActorSoldier::FUN_004a5460()
{
    if (((RHSoldierActorCalls *)this)->V48() || RHSOLDIER_FIELD(unsigned char, 0x1ce) ||
        *(int *)(RHSOLDIER_FIELD(char *, 0x50) + 0x8c) == 0x12 || RHSOLDIER_FIELD(void *, 0x254) ||
        !RHSOLDIER_FIELD(unsigned char, 0x12))
        return false;
    switch (*(int *)(RHSOLDIER_VBASE + 0xc))
    {
    case 0:
        return false;
    case 1:
    case 2:
    case 3:
        return true;
    case 4:
    {
        int type = *(int *)(RHSOLDIER_VBASE + 0x14);
        if (type >= 0xa9 && type <= 0xab)
            return false;
        return true;
    }
    case 5:
    case 6:
        return false;
    }
    return false;
}

// FUNCTION: GAME 0x004a54f0
bool RHElementActorSoldier::FUN_004a54f0()
{
    if (((RHSoldierActorCalls *)this)->V48() || RHSOLDIER_FIELD(unsigned char, 0x1ce))
        return false;
    switch (*(int *)(RHSOLDIER_VBASE + 0xc))
    {
    case 0:
        return false;
    case 1:
    case 2:
        return true;
    case 3:
        switch (*(int *)(RHSOLDIER_VBASE + 0x14))
        {
        case 0x47:
        case 0x5f:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x6d:
        case 0x79:
        case 0x7a:
            return true;
        }
        return false;
    case 4:
    case 5:
    case 6:
        return false;
    }
    return false;
}

// FUNCTION: GAME 0x004a55b0
void RHElementActorSoldier::FUN_004a55b0(RHSoldierActorCalls *neighbour)
{
    if (RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa24))
        RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa24)->V144(0);
    RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa24) = neighbour;
    if (neighbour)
    {
        neighbour->V14c(0);
        RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa24)->V144(*(int *)(RHSOLDIER_VBASE + 0x4));
    }
}

// FUNCTION: GAME 0x004a5610
void RHElementActorSoldier::FUN_004a5610(RHSoldierActorCalls *neighbour)
{
    if (RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa28))
        RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa28)->V140(0);
    RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa28) = neighbour;
    if (neighbour)
    {
        neighbour->V148(0);
        RHSOLDIER_FIELD(RHSoldierActorCalls *, 0xa28)->V140(*(int *)(RHSOLDIER_VBASE + 0x4));
    }
}

// FUNCTION: GAME 0x004a5670
bool RHElementActorSoldier::FUN_004a5670()
{
    return RHSOLDIER_PROFILE(RHSoldierProfileFlags, 0x5c).m_bit2;
}

// FUNCTION: GAME 0x004a5680
bool RHElementActorSoldier::FUN_004a5680()
{
    return RHSOLDIER_PROFILE(RHSoldierProfileFlags, 0x5c).m_bit1;
}

// FUNCTION: GAME 0x004a5690
bool RHElementActorSoldier::FUN_004a5690()
{
    return RHSOLDIER_PROFILE(RHSoldierProfileFlags, 0x5c).m_bit3;
}

// FUNCTION: GAME 0x004a56a0
bool RHElementActorSoldier::FUN_004a56a0()
{
    int type = *(int *)(RHSOLDIER_VBASE + 0x14);
    if (type >= 0xa7 && (type <= 0xa8 || type == 0xf9))
        return true;
    return false;
}

// FUNCTION: GAME 0x004a56d0
int RHElementActorSoldier::FUN_004a56d0(RHSoldierSequenceElement *element)
{
    int kind = element->m_5c;
    if (kind == 0xb)
    {
        switch (element->m_10)
        {
        case 0x89:
            return 7;
        case 0x54:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8e:
        case 0x90:
            return 8;
        default:
            return ((RHSoldierNPCCalls *)this)->FUN_0048d100(element);
        }
    }
    return kind;
}

// FUNCTION: GAME 0x004a5770
void RHElementActorSoldier::FUN_004a5770(RHSoldierSequenceElement *element)
{
    if (element->m_10 == 0x89)
        RHSOLDIER_FIELD(unsigned char, 0x4f4) = 0;
    ((RHSoldierNPCCalls *)this)->FUN_0048d790(element);
}

extern RHUnk005c38b0 *g_unk0x6c10e8;

// FUNCTION: GAME 0x004a5810
void RHElementActorSoldier::SetAppleSmell(bool enabled)
{
    if (enabled) {
        if (m_unkA3c == 0) {
            RHUnk00613e90 position;
            ((RHSoldierHumanCalls *)this)->FUN_00478e50(position);
            typedef void (RHScriptBatchCalls::*Effect)(void *, unsigned short, int, void *, int, int, int, int);
            (((RHScriptBatchCalls *)g_unk0x6c10e8)->*(Effect)&RHScriptBatchCalls::Unk005c2ec0)(&position,
                *(unsigned short *)(RHSOLDIER_FIELD(char *, 0x50) + 0xde),
                13, this, 3, 0, 0, -1);
        }
        m_unkA3c = 1500;
    }
    else
        m_unkA3c = 0;
}

// FUNCTION: GAME 0x004a5a00
void RHElementActorSoldier::FUN_004a5a00(void *first, void *second)
{
    if (!((RHSoldierActorCalls *)this)->V48())
    {
        ((RHSoldierHumanCalls *)this)->FUN_0047e9a0(first, second);
        if (((RHSoldierActorCalls *)this)->V130() == 1 && ((RHSoldierActorCalls *)this)->V48())
            ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(2, 0x32);
    }
}

// FUNCTION: GAME 0x004a5b70
void RHElementActorSoldier::FUN_004a5b70(void *actor)
{
    ((RHMalignityAlertCalls *)RHSOLDIER_VBASE)->FUN_0042c890(0x19, actor);
}

// FUNCTION: GAME 0x004a5b90
unsigned short RHElementActorSoldier::FUN_004a5b90()
{
    return RHSOLDIER_PROFILE(unsigned short, 0x7c);
}

extern float g_unk0x006774f0;
extern float g_unk0x0067749c;

// FUNCTION: GAME 0x004a5ba0
unsigned short RHElementActorSoldier::FUN_004a5ba0()
{
    if (!*(unsigned char *)(RHSOLDIER_VBASE + 0x24))
        return ((RHMalignityOwnerCalls *)((char *)this + 0x6e8))->FUN_00438710(
            RHSOLDIER_PROFILE(unsigned short, 0x3c), 0.5f, 2.0f, 100);
    return ((RHMalignityOwnerCalls *)((char *)this + 0x6e8))->FUN_00438710(
        RHSOLDIER_PROFILE(unsigned short, 0x3c), 0.5f, 2.0f, 100) *
        (g_unk0x0067749c - *(unsigned char *)(RHSOLDIER_VBASE + 0x24) * g_unk0x006774f0);
}

// FUNCTION: GAME 0x004a5c30
void RHElementActorSoldier::SetOutlineColors()
{
    if (RHSOLDIER_FIELD(void *, 0xa1c) && RHSOLDIER_PROFILE(RHSoldierProfileFlags, 0x5c).m_bit3) {
        RHSOLDIER_FIELD(unsigned short, 0x98) = g_unk0x6c11d0->Unk(115, 40, 203);
        RHSOLDIER_FIELD(unsigned short, 0x94) = g_unk0x6c11d0->Unk(115, 40, 203);
        RHSOLDIER_FIELD(unsigned short, 0x96) = g_unk0x6c11d0->Unk(115, 40, 203);
    }
    else {
        RHSOLDIER_FIELD(unsigned short, 0x98) = g_unk0x6c11d0->Unk(255, 0, 0);
        RHSOLDIER_FIELD(unsigned short, 0x94) = g_unk0x6c11d0->Unk(255, 0, 0);
        RHSOLDIER_FIELD(unsigned short, 0x96) = g_unk0x6c11d0->Unk(255, 0, 0);
        RHSOLDIER_FIELD(unsigned short, 0x9a) = g_unk0x6c11d0->Unk(255, 255, 0);
        RHSOLDIER_FIELD(unsigned short, 0x9c) = g_unk0x6c11d0->Unk(0, 120, 255);
    }
}

// FUNCTION: GAME 0x004a5d30
int RHElementActorSoldier::FUN_004a5d30()
{
    return RHSOLDIER_PROFILE(RHSoldierProfileFlags, 0x5c).m_bit0 == 1;
}

// FUNCTION: GAME 0x004a5d50
void RHElementActorSoldier::FUN_004a5d50(RHMalignityPosition position, unsigned short first, unsigned short second, void *actor)
{
    RHSoldierDoorPayload payload;
    payload.m_18 = actor;
    *(RHMalignityPosition *)payload.m_04 = position;
    payload.m_00 = second;
    payload.m_14 = first;
    ((RHSoldierStimulusCalls *)RHSOLDIER_VBASE)->FUN_004a5dc0(0x33, payload);
}

// FUNCTION: GAME 0x004a5dc0
void RHSoldierStimulusCalls::FUN_004a5dc0(unsigned type, const RHSoldierDoorPayload &payload)
{
    RHMalignityStimulus stimulus;
    stimulus.m_20 = type;
    *(RHSoldierDoorPayload *)stimulus.m_00 = payload;
    stimulus.m_type = 8;
    V24(&stimulus);
}

// FUNCTION: GAME 0x004a64a0
void RHSoldierStimulusCalls::FUN_004a64a0(unsigned type, const RHMalignityPosition &position)
{
    RHMalignityStimulus stimulus;
    stimulus.m_20 = type;
    *(RHMalignityPosition *)stimulus.m_00 = position;
    stimulus.m_type = 2;
    V24(&stimulus);
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementActorSoldier::Serialize in the
// build.
void RHElementActorSoldier::Emit(SBFile &file)
{
    Serialize(file);
    SetAppleSmell(false);
    FUN_004a5ba0();
    SetOutlineColors();
    RHMalignityPosition position;
    FUN_004a5d50(position, 0, 0, 0);
    ((RHSoldierStimulusCalls *)this)->FUN_004a64a0(0, position);
}
