// RHKeyConfig.cpp — translation unit with __FILE__ evidence at 0x0051ec40 and
// 0x0051ece0 ("P:\Robin Hood\RHkeyconfig.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0051ec40 -> RHKeyConfig::Serialize(SBFile&)):
//   - TU:        rhkeyconfig.cpp (embedded __FILE__ string 0x006b06a8).
//   - Class:     RHKeyConfig (symbols/oracle-correlation.tsv:
//                rhkeyconfig -> class RHKeyConfig, 22 methods).
//   - Signature: RHKeyConfig::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * it writes the type-name tag "RHKeyConfig" (string 0x006b06c8) first
//         via the 0x005e1b70 helper;
//       * a straight-line pair of SBFile::Access checks at +0x04 (2 bytes) and
//         through the pointer at +0x00 (0x3a = 58 bytes = 29 shorts) with the
//         "Serialize failed reason is %s" assert idiom (lines 0xd6 / 0xd7);
//       * the Mac oracle's rhkeyconfig.cpp carries exactly one Serialize.
//
// BINDING (0x0051ece0 -> RHKeyConfig::SetToPreset(unsigned short, bool)):
//   - Signature: RHKeyConfig::SetToPreset(unsigned short, bool)
//     (symbols/mac-RH.txt: SetToPreset__11RHKeyConfigUsb).
//   - Signals:
//       * it builds a "data\\configuration\\" + "keyset<N>.cfg" path (strings
//         0x006b06fc / 0x006b06f0 for preset 0, 0x006b0710 for preset 1) keyed
//         on the first argument by a two-case switch;
//       * it loads the file and asserts "Unable to locate file '%s'"
//         (0x006b06d4, line 0xfd) when that fails;
//       * on success it calls this->Serialize and then stores
//         `WORD [this+0x04] = keysRead + 2`;
//       * it is the only caller of 0x0051ec40, fixing the pair.
//
// STATUS OF 0x0051ec40 (Serialize) — DEFERRED, UNANNOTATED (reccmp #534):
//   SetToPreset (matched) calls Serialize, so annotating Serialize would make
//   reccmp resolve the original `call 0x0051ec40` by name while our
//   incremental-link call stays an unnamed ILT placeholder -> the caller drops
//   below 100% (Hard rule 28 / docs/07-link-limitations.md). The real body is
//   kept here with its // FUNCTION: marker omitted until reccmp lands the
//   symmetric-operand fix; then the marker is a one-line flip.
//
// STATUS OF 0x0051ece0 (SetToPreset) — PARKED (frame/EH layout wall):
//   The body is reproduced logically, but the original frame is `sub esp,0xd4`
//   with `this` pinned in edi; every probed source shape yields `sub esp,0xbc`
//   (24 bytes short) with `this` in esi. The shortfall is the original's
//   byte-local copies (`mov al,[esp+3]`) that seed each SBString's value byte,
//   plus an asymmetric per-case inlined string assignment (case 0 uses
//   Reserve+memcpy+SetLength, case 1 an out-of-line Assign) — a VC6 stack-
//   colouring/optimizer artifact not expressible from source (Hard rule 15).
//   Parked until a frame-forcing mechanism exists.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "RHKeyConfig.h"

// deferred: unannotated pending reccmp #534
bool RHKeyConfig::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b06c8
    RHSerializeName(file, "RHKeyConfig");

    if (file.Access(&m_count, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b06a8
                 "P:\\Robin Hood\\RHkeyconfig.cpp",
                 0xd6,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(m_keys, 2 * 29) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHkeyconfig.cpp", 0xd7, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

// STUB: GAME 0x0051ece0
void RHKeyConfig::SetToPreset(unsigned short preset, bool flag)
{
    switch (preset)
    {
    case 0:
    case 1:
        break;
    default:
        return;
    }
}

void RHKeyConfig::Emit(SBFile &file)
{
    Serialize(file);
    SetToPreset(0, false);
}
