// RHElementActorCivilian.cpp — translation unit with __FILE__ evidence at
// 0x004711c0 ("P:\Robin Hood\rhelementactorcivilian.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004711c0 -> RHElementActorCivilian::Serialize(SBFile&)):
//   - TU:        rhelementactorcivilian.cpp (embedded __FILE__ string
//                0x006ae370).
//   - Class:     RHElementActorCivilian (symbols/oracle-correlation.tsv:
//                rhelementactorcivilian -> class RHElementActorCivilian,
//                35 methods).
//   - Method:    RHElementActorCivilian::Serialize(SBFile&) — the Mac oracle's
//                rhelementactorcivilian.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x00087798 Serialize).
//   - Signals:
//       * the function first calls the base 0x0048b5d0 with `this` unchanged
//         and returns false immediately if it fails; 0x0048b5d0 writes the tag
//         "RHElementActorNPC" (string 0x006ae5cc) — i.e. the base
//         RHElementActorNPC::Serialize is invoked first on the same object;
//       * on success it writes the tag "RHElementActorCivilian" (string
//         0x006ae454) via 0x005e1b70 — the name matches the TU's class;
//       * then ONE SBFile::Access 0x005f52b0 on this+0x704 (size 4) with the
//         "Serialize failed reason is %s" assert pattern (format 0x006a7390,
//         empty fallback 0x006773d0) at line 753 (0x2f1) — the exact serializer
//         idiom seen in RHElementPurse;
//       * no loop and no `new`.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "RHElementActorCivilian.h"

// FUNCTION: GAME 0x004711c0
bool RHElementActorCivilian::Serialize(SBFile &file)
{
    if (!RHElementActorNPC::Serialize(file))
        return false;

    // STRING: GAME 0x6ae454
    RHSerializeName(file, "RHElementActorCivilian");

    if (file.Access(&m_unk704, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6ae370
                 "P:\\Robin Hood\\rhelementactorcivilian.cpp",
                 753,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return true;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementActorCivilian::Serialize in the
// build.
void RHElementActorCivilian::Emit(SBFile &file)
{
    Serialize(file);
}
