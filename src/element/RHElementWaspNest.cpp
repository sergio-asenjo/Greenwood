// RHElementWaspNest.cpp — translation unit with __FILE__ evidence at
// 0x004be1e0 ("P:\Robin Hood\RHElementWaspNest.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004be1e0 -> RHElementWaspNest::Serialize(SBFile&)):
//   - TU:        rhelementwaspnest.cpp (embedded __FILE__ string 0x006aef5c).
//   - Class:     RHElementWaspNest (symbols/oracle-correlation.tsv:
//                rhelementwaspnest -> class RHElementWaspNest, 11 methods).
//   - Method:    RHElementWaspNest::Serialize(SBFile&) — the Mac oracle's
//                rhelementwaspnest.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x000dced0 Serialize).
//   - Signals:
//       * the function first calls the base 0x004b7500 with `this` unchanged and
//         returns false immediately if it fails; 0x004b7500 writes the tag
//         "RHElementProjectile" — i.e. the base
//         RHElementProjectile::Serialize is invoked first on the same object;
//       * NO type tag is written by this function;
//       * the read path (file.m_bLoading != 0) checks a dword at file+0x10
//         against 0x10 and returns true when below, else ONE
//         SBFile::Access 0x005f52b0 on this+0x15c (size 4) at line 149 (0x95);
//       * the write path (file.m_bLoading == 0) does ONE
//         SBFile::Access 0x005f52b0 on this+0x15c (size 4) at line 153 (0x99);
//       * both use the "Serialize failed reason is %s" assert pattern (format
//         0x006a7390, empty fallback 0x006773d0);
//       * no loop and no `new`.
//
// The `// STRING:` marker pins this TU's __FILE__ literal to its original
// Game.exe address: the original is a fixed-base EXE, so its absolute string
// pointers carry no relocation records and reccmp cannot discover them by
// scanning. ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHElementWaspNest.h"

// FUNCTION: GAME 0x004be1e0
bool RHElementWaspNest::Serialize(SBFile &file)
{
    if (RHElementProjectile::Serialize(file))
    {
        if (file.m_bLoading)
        {
            if (file.m_version >= 0x10)
            {
                if (file.Access(&m_unk15c, 4) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0,
                             // STRING: GAME 0x6aef5c
                             "P:\\Robin Hood\\RHElementWaspNest.cpp",
                             149,
                             "Serialize failed reason is %s",
                             reason);
                    return false;
                }
                return true;
            }
        }

        if (!file.m_bLoading)
        {
            if (file.Access(&m_unk15c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHElementWaspNest.cpp",
                         153,
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
// non-inlinable out-of-line call keeps RHElementWaspNest::Serialize in the
// build.
void RHElementWaspNest::Emit(SBFile &file)
{
    Serialize(file);
}
