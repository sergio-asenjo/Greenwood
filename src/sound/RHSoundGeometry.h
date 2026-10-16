// RHSoundGeometry — declarations for RHSoundGeometry.cpp (decompiled TU).
//
// BINDING (0x005b32e0 -> RHSoundGeometry::GetVolumeForAltitude(float,
// RHsoundSourceAltitude)):
//   - TU:        rhsoundgeometry.cpp (embedded __FILE__ string 0x006b8644).
//   - Class:     RHSoundGeometry (symbols/oracle-correlation.tsv:
//                rhsoundgeometry -> class RHSoundGeometry, 17 methods).
//   - Signature: RHSoundGeometry::GetVolumeForAltitude(float,
//                RHsoundSourceAltitude) (symbols/mac-RH.txt:4250).
//   - Signals:
//       * __thiscall: first act is `mov edx,[esp+8]` (the enum arg), `ecx` is
//         `this`, and it reads `[ecx+0x8]` (the float height);
//       * a three-entry switch on the enum (0 -> m_8*alt*0.5; 3 -> altitude;
//         default -> a height test against 1.0f then nested type dispatch);
//       * the default's unknown-type path calls SBAssert at line 0x291 with
//         the string "Unknown altitude for sound source !" (0x006b8668),
//         whose wording matches this method's purpose;
//       * the Mac map for this TU lists exactly two methods, Serialize
//         (0x005b3510) and GetVolumeForAltitude — the two Windows functions
//         with this __FILE__ — so the per-method binding is unambiguous.
//
// BINDING (0x005b3510 -> RHSoundGeometry::Serialize(SBFile&)):
//   - Signature: RHSoundGeometry::Serialize(SBFile&) (symbols/mac-RH.txt:4256).
//   - Signals:
//       * the function writes the type-name tag "RHSoundGeometry" (string
//         0x006b868c) as its very first act via the 0x005e1b70 helper — the
//         name matches the class the TU is known to contain;
//       * a straight-line sequence of three SBFile::Access 4-byte checks (no
//         loop, no base-class call, no `new`) at offsets +0x0, +0x4, +0x8 with
//         assert lines 805/806/807 (0x325/0x326/0x327), using the
//         "Serialize failed reason is %s" idiom;
//       * after the third Access it calls 0x005b2f30 on `this` with the dword
//         just read at +0x8 as its single float argument, then returns true.
//
// Member offsets are derived from the target instructions of both matched
// functions: three 4-byte fields at +0x00, +0x04, +0x08. Serialize touches all
// three; GetVolumeForAltitude reads +0x08 as a float (`fld DWORD PTR [ecx+8]`,
// `fcomp`/`fsub` against a 1.0f constant), so it is declared float.
// Only the offsets the matched functions touch are laid out.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SB.h"

// Altitude classifications for a sound source, used by GetVolumeForAltitude.
// The Windows target tests the raw integer values 0..3; only these are used.
enum RHsoundSourceAltitude
{
    RH_ALTITUDE_0 = 0,
    RH_ALTITUDE_1 = 1,
    RH_ALTITUDE_2 = 2,
    RH_ALTITUDE_3 = 3
};

class RHSoundGeometry
{
public:
    // 0x005b32e0 — __thiscall(this, float altitude, RHsoundSourceAltitude type)
    float GetVolumeForAltitude(float altitude, RHsoundSourceAltitude type);

    bool Serialize(SBFile &file);

    // Callee 0x005b2f30 — __thiscall(this, float): stores its argument to
    // [+0x08] and recomputes derived geometry floats at [+0xb8..0xc4].
    // PROVISIONAL: named by address only. No Windows-side __FILE__/tag/string
    // binds a method name to it; the Mac/Zeta oracles expose
    // RHSoundGeometry::SetZoomFactor(float) as a single-float-arg candidate,
    // but a cross-binary positional match is not accepted as evidence
    // (docs/05-naming.md).
    void RHUnk005b2f30(float value);

    void Emit(SBFile &file);

    int m_0;     // [0x00]
    int m_4;     // [0x04]
    float m_8;   // [0x08]
    unsigned char m_0c[0xac];
    float m_b8;
    float m_bc;
    float m_c0;
    float m_c4;
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);
