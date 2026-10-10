// RHSoundConfig.cpp — translation unit with __FILE__ evidence at 0x005b2190
// ("P:\Robin Hood\RHsoundconfig.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005b2190 -> RHSoundConfig::Serialize(SBFile&)):
//   - TU:        rhsoundconfig.cpp (embedded __FILE__ string 0x006b8614,
//                referenced only by this function).
//   - Class:     RHSoundConfig (symbols/oracle-correlation.tsv:
//                rhsoundconfig -> class RHSoundConfig, 7 methods).
//   - Signature: RHSoundConfig::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * the function writes the type-name tag "RHSoundConfig" (string
//         0x006b8634) as its very first act via the 0x005e1b70 helper — the
//         name matches the class the TU is known to contain;
//       * a straight-line sequence of seven SBFile::Access checks (no loop, no
//         base-class call, no `new`) at offsets +0x0a, +0x0b, +0x02, +0x06,
//         +0x04, +0x00, +0x08 with the "Serialize failed reason is %s" assert
//         idiom — the exact serializer pattern seen in RHElementObject;
//       * the only RHSoundConfig method in the Mac map for this TU is
//         Serialize, so the per-method binding is unambiguous.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHSoundConfig.h"

// FUNCTION: GAME 0x005b2190
bool RHSoundConfig::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b8634
    RHSerializeName(file, "RHSoundConfig");

    if (file.Access(&m_a, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // NOTE: the empty string 0x006773d0 and the format
        // "Serialize failed reason is %s" (0x006a7390) are the same original
        // entities used by RHSword::SerializePointer; reccmp allows exactly one
        // marker per original address, so those two are annotated once in
        // src/RHSword.cpp. This function's reference resolves to the same
        // pooled entities.
        SBAssert(0,
                 // STRING: GAME 0x6b8614
                 "P:\\Robin Hood\\RHsoundconfig.cpp",
                 64,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_b, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 65, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_2, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 67, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 68, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 69, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_0, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 70, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundconfig.cpp", 71, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHSoundConfig::Serialize in the build.
void RHSoundConfig::Emit(SBFile &file)
{
    Serialize(file);
}
