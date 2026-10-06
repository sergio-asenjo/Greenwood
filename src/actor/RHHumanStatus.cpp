// RHHumanStatus.cpp — translation unit with __FILE__ evidence at 0x0051d5d0
// ("P:\Robin Hood\RHHumanStatus.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0051d5d0 -> RHHumanStatus::Serialize(SBFile&)):
//   - TU:        rhhumanstatus.cpp (embedded __FILE__ string 0x006b0678).
//   - Class:     RHHumanStatus (symbols/oracle-correlation.tsv:
//                rhhumanstatus -> class RHHumanStatus, 16 methods).
//   - Method:    RHHumanStatus::Serialize(SBFile&) — the Mac oracle's
//                rhhumanstatus.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x0013a1a0 Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHHumanStatus" (string
//         0x006b0698) via 0x005e1b70 — the name matches the TU's class;
//       * every field goes through SBFile::Access 0x005f52b0 / SBFile::GetError
//         0x005f5f30 and the "Serialize failed reason is %s" assert pattern
//         (format 0x006a7390, empty fallback 0x006773d0) — the exact serializer
//         idiom seen in RHSword::SerializePointer;
//       * the body is a `for (i = 0; i < 2; ++i)` loop over a 2-element array
//         of 8-byte records at this+0x04, calling Access(+4, 4) then
//         Access(+0, 4) per record;
//       * no base-class Serialize is invoked; the function returns true.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "RHHumanStatus.h"

// FUNCTION: GAME 0x0051d5d0
bool RHHumanStatus::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b0698
    RHSerializeName(file, "RHHumanStatus");

    for (unsigned int i = 0; i < 2; ++i)
    {
        if (file.Access(&m_entries[i].m_f4, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x6b0678
                     "P:\\Robin Hood\\RHHumanStatus.cpp",
                     182,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_entries[i].m_f0, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHHumanStatus.cpp", 183, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    return true;
}

// Force emission: RHSword-style serializers are pulled in only when
// referenced; this non-inlinable out-of-line call keeps Serialize in the build.
void RHHumanStatus::Emit(SBFile &file)
{
    Serialize(file);
}
