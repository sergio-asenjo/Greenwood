// RHGraphicConfig.cpp — translation unit with __FILE__ evidence at 0x0051ba00
// ("P:\Robin Hood\RHgraphicconfig.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0051ba00 -> RHGraphicConfig::Serialize(SBFile&)):
//   - TU:        rhgraphicconfig.cpp (embedded __FILE__ string 0x006b0604,
//                referenced only by this function).
//   - Class:     RHGraphicConfig (symbols/oracle-correlation.tsv:
//                rhgraphicconfig -> class RHGraphicConfig, 7 methods).
//   - Signature: RHGraphicConfig::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * the function writes the type-name tag "RHGraphicConfig" (string
//         0x006b0628) as its very first act via the 0x005e1b70 helper — the
//         name matches the class the TU is known to contain;
//       * a straight-line sequence of four SBFile::Access checks (no loop, no
//         base-class call, no `new`) at byte offsets +0x0, +0x1, +0x3, +0x2
//         with assert lines 59/60/61/62, using the
//         "Serialize failed reason is %s" idiom — the exact serializer pattern
//         seen in RHElementObject and RHSoundConfig;
//       * the success path calls the embedded point's serializer at +0x4
//         (target 0x005fc2a0, SBGeoPoint2D::Serialize) and discards its bool,
//         then returns true;
//       * the only RHGraphicConfig method in the Mac map for this TU is
//         Serialize, so the per-method binding is unambiguous.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHGraphicConfig.h"

// FUNCTION: GAME 0x0051b9a0
RHGraphicConfig::RHGraphicConfig() : m_0(1), m_1(1), m_2(0), m_3(1), m_point(800.0f, 600.0f)
{
}

// FUNCTION: GAME 0x0051b9d0
RHGraphicConfig::RHGraphicConfig(const RHGraphicConfig &other) :
    m_0(other.m_0), m_1(other.m_1), m_2(other.m_2), m_3(other.m_3),
    m_point((const SBGeoPoint2D &)other.m_point)
{
}

// FUNCTION: GAME 0x0051ba00
bool RHGraphicConfig::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b0628
    RHSerializeName(file, "RHGraphicConfig");

    if (file.Access(&m_0, 1) < 0)
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
                 // STRING: GAME 0x6b0604
                 "P:\\Robin Hood\\RHgraphicconfig.cpp",
                 59,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_1, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHgraphicconfig.cpp", 60, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_3, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHgraphicconfig.cpp", 61, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_2, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHgraphicconfig.cpp", 62, "Serialize failed reason is %s", reason);
        return false;
    }

    m_point.Serialize(file);

    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHGraphicConfig::Serialize in the build.
void RHGraphicConfig::Emit(SBFile &file)
{
    Serialize(file);
    RHGraphicConfig defaults;
    RHGraphicConfig copy(defaults);
}
