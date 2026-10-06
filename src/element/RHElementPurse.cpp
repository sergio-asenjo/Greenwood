// RHElementPurse.cpp — translation unit with __FILE__ evidence at 0x004b9830
// ("P:\Robin Hood\RHElementPurse.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x004b9830 -> RHElementPurse::Serialize(SBFile&)):
//   - TU:        rhelementpurse.cpp (embedded __FILE__ string 0x006aed9c).
//   - Class:     RHElementPurse (symbols/oracle-correlation.tsv:
//                rhelementpurse -> class RHElementPurse, 14 methods).
//   - Method:    RHElementPurse::Serialize(SBFile&) — the Mac oracle's
//                rhelementpurse.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x000d8ca4 Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHElementPurse" (string
//         0x006aedc0) via 0x005e1b70 — the name matches the TU's class;
//       * SBFile::Access 0x005f52b0 on this+0x168 (size 2) with the
//         "Serialize failed reason is %s" assert pattern (format 0x006a7390,
//         empty fallback 0x006773d0) — the exact serializer idiom seen in
//         RHSword::SerializePointer;
//       * the tail is a direct call to 0x004b7500 with `this` unchanged, and
//         0x004b7500 is the rhelementprojectile.cpp function that first writes
//         the tag "RHElementProjectile" (string 0x006aed88) — i.e. the base
//         RHElementProjectile::Serialize is invoked last on the same object.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities. The
// base's tag 0x006aed88 / __FILE__ belong to rhelementprojectile.cpp and are
// deliberately not annotated here.)

#include "RHElementPurse.h"

// FUNCTION: GAME 0x004b9830
bool RHElementPurse::Serialize(SBFile &file)
{
    // STRING: GAME 0x6aedc0
    RHSerializeName(file, "RHElementPurse");

    if (file.Access(&m_unk168, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6aed9c
                 "P:\\Robin Hood\\RHElementPurse.cpp",
                 240,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return RHElementProjectile::Serialize(file);
}

// Force emission: RHSword-style serializers are pulled in only when
// referenced; this non-inlinable out-of-line call keeps Serialize in the build.
void RHElementPurse::Emit(SBFile &file)
{
    Serialize(file);
}
