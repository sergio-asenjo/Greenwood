// RHLine.cpp — translation unit with __FILE__ evidence at 0x00521210 / 0x00521810
// / 0x005218e0 ("P:\Robin Hood\RHline.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005218e0 -> RHSeekPoint::SerializeAllData(SBFile&)):
//   - its first act writes the tag "RHSeekPoint::SerializeAllData" (0x006b0744)
//     via RHSerializeName (0x005e1b70);
//   - its final act is a call to 0x00521810; the Mac oracle's
//     RHSeekPoint::SerializeAllData ends by calling RHSeekPoint::SerializeStatus.
//
// BINDING (0x00521810 -> RHSeekPoint::SerializeStatus(SBFile&)):
//   - it writes the tag "RHSeekPoint" (0x006b0738);
//   - its field sequence (+0x14 dword, +0x38 byte, +0x39 byte) matches the Mac
//     RHSeekPoint::SerializeStatus (symbols/mac-functions-by-file.tsv);
//   - it is the tail callee of 0x005218e0, fixing it as the status serialiser.
//
// BINDING (0x00521210 -> RHUnk004b2190Member::Serialize(SBFile&)) — provisional:
//   - it writes NO tag and its leading field sequence (+0x04, +0x08, +0x34, two
//     embedded SBGeoPoint2D, four dwords, byte flags) matches the Mac
//     RHRepulsivePoint::Serialize; no Windows-side tag exists, so the class keeps
//     the neutral name RHElementObject.h already declares for its +0xbc member.
//   - it is called from RHElementObject::Serialize at +0xbc (0x004b22f4), plus
//     three not-yet-decompiled call sites.
//
// STATUS OF 0x00521210 — BLOCKED (cannot carry a // FUNCTION: marker):
//   reccmp resolves a `call` operand by name lookup in the ORIG entity db.
//   A // FUNCTION: annotation creates a named ORIG entity at 0x521210, so the
//   original `call 0x521210` at 0x004b22f4 renders as
//   `call RHUnk004b2190Member::Serialize (FUNCTION)`, while our incremental
//   (/DEBUG) link routes the same call through the unnamed ILT stub and reccmp
//   renders it `<OFFSET7>`. The operands differ and RHElementObject::Serialize
//   drops to 99.38%. /INCREMENTAL:NO is the only known way to emit a direct call
//   and is forbidden (Hard rule 17 — it regresses RHWidgetPortrait and other
//   call-heavy matches). Verified with a scratch /INCREMENTAL:NO build:
//   RHElementObject 88.12%, RHOrder 87.98%, RHWidgetPortrait 89.47%. The body is
//   kept here, unannotated, so the empty stub in RHElementObject_stubs.cpp is
//   retired and RHElementObject/RHOrder stay 100%.

#include "RHLine.h"

bool RHUnk004b2190Member::Serialize(SBFile &file)
{
    if (file.Access(&m_4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b071c
                 "P:\\Robin Hood\\RHline.cpp",
                 0x5c5,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    if (file.Access(&m_8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5c6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_34, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5c8, "Serialize failed reason is %s", reason);
        return false;
    }

    m_14.Serialize(file);
    m_1c.Serialize(file);

    if (file.Access(&m_24, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5cd, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_28, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5ce, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5cf, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_30, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d0, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_3c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d2, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_35, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d4, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_36, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_37, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_38, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d7, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

void RHUnk004b2190Member::Emit(SBFile &file)
{
    Serialize(file);
}

// FUNCTION: GAME 0x00521810
bool RHSeekPoint::SerializeStatus(SBFile &file)
{
    // STRING: GAME 0x6b0738
    RHSerializeName(file, "RHSeekPoint");

    if (file.Access(&m_14, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_38, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_39, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e7, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// BLOCKED: the target 0x005218e0 ends with a plain `call 0x00521810` (its result
// feeds a `setne`), and 0x00521810 is the matched RHSeekPoint::SerializeStatus
// above. That call operand cannot resolve on both sides under the incremental
// link (same mechanism as 0x00521210): the original names it, ours is the unnamed
// ILT placeholder. The full body is an inlined SBArray<unsigned short> load/store
// path; parked until the calling operand can be resolved.
// STUB: GAME 0x005218e0
bool RHSeekPoint::SerializeAllData(SBFile &file)
{
    // STRING: GAME 0x6b0744
    RHSerializeName(file, "RHSeekPoint::SerializeAllData");
    return SerializeStatus(file);
}

void RHSeekPoint::Emit(SBFile &file)
{
    SerializeStatus(file);
    SerializeAllData(file);
}
