// RHMissionStat.cpp — translation unit with __FILE__ evidence at 0x0054e250
// ("P:\Robin Hood\RHMissionStat.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0054e250 -> RHMissionStat::Serialize(SBFile&)):
//   - TU:        rhmissionstat.cpp (embedded __FILE__ string 0x006b1320).
//   - Class:     RHMissionStat (symbols/oracle-correlation.tsv:
//                rhmissionstat -> class RHMissionStat, 16 methods).
//   - Method:    RHMissionStat::Serialize(SBFile&) — the Mac oracle's
//                rhmissionstat.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x0016d690 Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHMissionStat" (string
//         0x006b1350) via 0x005e1b70 — the name matches the TU's class;
//       * every field goes through SBFile::Access 0x005f52b0 / SBFile::GetError
//         0x005f5f30 and the "Serialize failed reason is %s" assert pattern
//         (format 0x006a7390, empty fallback 0x006773d0) — the exact serializer
//         idiom seen in RHSword::SerializePointer;
//       * the tail call is 0x004593f0(file, this+0x28, 0x005e0ea0), a
//         container-serialiser helper that walks [this+0x2c, this+0x30) and
//         invokes the per-element function pointer — the standard list tail
//         of a serializer.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHMissionStat.h"

// FUNCTION: GAME 0x0054e250
bool RHMissionStat::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b1350
    RHSerializeName(file, "RHMissionStat");

    if (file.Access(&m_f04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b1320
                 "P:\\Robin Hood\\RHMissionStat.cpp",
                 309,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_f08, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 310, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f0c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 311, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f10, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 312, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f14, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 313, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f18, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 314, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f1c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 315, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f20, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 316, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f24, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 317, "Serialize failed reason is %s", reason);
        return false;
    }

    // The per-element serialiser is passed by value: the original is a
    // fixed-base EXE, so `push offset 0x005e0ea0` carries no relocation and
    // reccmp keeps it as the literal immediate 0x005e0ea0. Emitting the same
    // literal (a numeric constant, not the address of a local symbol) is the
    // only way to reproduce those bytes.
    RHUnk004593f0SerializeList(file, m_list, (void *)0x005e0ea0);
    return true;
}

// Force emission: RHSword-style serializers are pulled in only when
// referenced; this non-inlinable out-of-line call keeps Serialize in the build.
void RHMissionStat::Emit(SBFile &file)
{
    Serialize(file);
}
