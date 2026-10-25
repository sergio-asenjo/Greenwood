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
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "RHSoundGeometryCalls.h"
#include "RHUnk004ff7b0.h"
#include <vector>

// Altitude classifications for a sound source, used by GetVolumeForAltitude.
// The Windows target tests the raw integer values 0..3; only these are used.
enum RHsoundSourceAltitude
{
    RH_ALTITUDE_0 = 0,
    RH_ALTITUDE_1 = 1,
    RH_ALTITUDE_2 = 2,
    RH_ALTITUDE_3 = 3
};

template <class T>
class RHUnk005b35e0Array : public std::vector<T>
{
public:
    RHUnk005b35e0Array() : m_changed(true) {}
    int GetSize() const { return begin() == 0 ? 0 : end() - begin(); }
    void SetSize(unsigned int count)
    {
        RHUnk005b35e0Resize(this, count, T());
        m_changed = true;
    }

    T *m_search;     // 0x10
    bool m_changed;  // 0x14
    bool m_searching; // 0x15
    int m_index;     // 0x18
    T m_value;       // 0x1c
};

inline void RHUnk005b35e0Resize(RHUnk005b35e0Array<SBGeoPoint2D> *array, unsigned int count, const SBGeoPoint2D &value)
{
    ((RHUnk005b35e0 *)array)->FUN_005b35e0(count, value);
}

inline void RHUnk005b35e0Resize(RHUnk005b35e0Array<float> *array, unsigned int count, const float &value)
{
    ((RHUnk004ff7b0 *)array)->FUN_004ff7b0(count, value);
}

class RHSoundGeometry
{
public:
    RHSoundGeometry();

    float FUN_005b2510(float, const RHUnk005b2410 &);
    float FUN_005b2560(const SBGeoPoint2D &, const RHUnk005b2410 &);
    float FUN_005b25e0(const RHUnk005b2410 &);
    float FUN_005b27e0(const RHUnk005b2410 &);
    void FUN_005b2a30(RHUnk005a7220 *, RHUnk005b2410 &);
    float Weight(const SBGeoPoint2D &point, float distance, const RHUnk005b2410 &range)
    {
        float volume = FUN_005b2510(distance, range);
        return FUN_005b2560(point, range) * volume;
    }

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

    SBGeoPoint2D m_0;   // [0x00]
    float m_8;          // [0x08]
    float m_c;          // [0x0c]
    float m_10;         // [0x10]
    int m_14;           // [0x14]
    int m_18;           // [0x18]
    int m_1c;           // [0x1c]
    unsigned short m_20; // [0x20]
    RHUnk005b35e0Array<SBGeoPoint2D> m_24; // [0x24]
    RHUnk005b35e0Array<float> m_48; // [0x48]
    RHUnk005b35e0Array<float> m_68; // [0x68]
    RHUnk005b35e0Array<SBGeoPoint2D> m_88; // [0x88]
    SBGeoPoint2D m_ac;  // [0xac]
    float m_b4;
    float m_b8;
    float m_bc;
    float m_c0;
    float m_c4;
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);
