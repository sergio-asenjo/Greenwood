// RHElementArrow.cpp — translation unit with __FILE__ evidence at
// 0x004a6e10 ("P:\Robin Hood\RHElementArrow.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004a6e10 -> RHElementArrow::Serialize(SBFile&)):
//   - TU:        rhelementarrow.cpp (embedded __FILE__ string 0x006ae978).
//   - Class:     RHElementArrow (symbols/oracle-correlation.tsv:
//                rhelementarrow -> class RHElementArrow, 18 methods).
//   - Method:    RHElementArrow::Serialize(SBFile&) — the Mac oracle's
//                rhelementarrow.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv, symbols/mac-RH.txt:1764).
//   - Signals:
//       * the function first writes the tag "RHElementArrow" (string
//         0x006ae99c) via 0x005e1b70 — the name matches the TU's class;
//       * it then calls the base 0x004b7500 with `this` unchanged and returns
//         false immediately if it fails; 0x004b7500 writes the tag
//         "RHElementProjectile" — i.e. RHElementProjectile::Serialize is
//         invoked on the same object;
//       * on success it calls 0x00450370 on this+0x15c — the RHBow analogue of
//         the already-matched RHSword::SerializePointer (0x00450370's __FILE__
//         is P:\Robin Hood\RHBow.cpp), i.e. a pointer field at +0x15c;
//       * SEVEN SBFile::Access 0x005f52b0 checks: this+0x160/1, +0x161/1,
//         +0x162/1, +0x163/1 at lines 379..382, +0x164/2 at line 383, then the
//         file.m_bLoading gate (mov al,[esi+4]; test; je) selecting +0x166/1 at
//         line 387 (read) or line 391 (write) — the exact serializer idiom seen
//         in RHElementPurse / RHElementWaspNest;
//       * no loop and no `new`.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHElementArrow.h"

// FUNCTION: GAME 0x004a6e10
bool RHElementArrow::Serialize(SBFile &file)
{
    // STRING: GAME 0x6ae99c
    RHSerializeName(file, "RHElementArrow");

    if (RHElementProjectile::Serialize(file))
    {
        RHBow::SerializePointer(file, m_bow);

        if (file.Access(&m_160, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x6ae978
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     379,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_161, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     380,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_162, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     381,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_163, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     382,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_164, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     383,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.m_bLoading)
        {
            if (file.m_version >= 0x10)
            {
                if (file.Access(&m_166, 1) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0,
                             "P:\\Robin Hood\\RHElementArrow.cpp",
                             387,
                             "Serialize failed reason is %s",
                             reason);
                    return false;
                }
                return true;
            }
        }

        if (!file.m_bLoading)
        {
            if (file.Access(&m_166, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHElementArrow.cpp",
                         391,
                         "Serialize failed reason is %s",
                         reason);
                return false;
            }
        }

        return true;
    }

    return false;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementArrow::Serialize in the build.
void RHElementArrow::Emit(SBFile &file)
{
    Serialize(file);
}
