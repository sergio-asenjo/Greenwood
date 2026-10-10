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

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementActorSoldier::Serialize in the
// build.
void RHElementActorSoldier::Emit(SBFile &file)
{
    Serialize(file);
}
