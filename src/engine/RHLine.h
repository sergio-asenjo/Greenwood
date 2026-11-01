// RHLine.h — declarations for the RHline.cpp translation unit.
//
// TU evidence: the embedded __FILE__ string "P:\Robin Hood\RHline.cpp"
// (0x006b071c) is referenced by the three functions 0x00521210, 0x00521810 and
// 0x005218e0 (symbols/functions-by-file.tsv). The Mac oracle attributes the same
// file's serialisers to RHRepulsivePoint::Serialize, RHSeekPoint::SerializeStatus
// and RHSeekPoint::SerializeAllData (symbols/mac-functions-by-file.tsv), which is
// the class set reconstructed here.
//
// Method bindings (tags read from the binary, then shape):
//   - 0x00521810 writes the tag "RHSeekPoint" (0x006b0738) and its field sequence
//     (+0x14 dword, +0x38 byte, +0x39 byte) matches the Mac
//     RHSeekPoint::SerializeStatus, whose caller below is the deciding signal:
//   - 0x005218e0 writes the tag "RHSeekPoint::SerializeAllData" (0x006b0744) and
//     its final act is a tail call to 0x00521810 — exactly as the Mac
//     RHSeekPoint::SerializeAllData ends by calling RHSeekPoint::SerializeStatus.
//   - 0x00521210 writes no tag; its leading field sequence (+0x04 dword, +0x08
//     dword, +0x34 byte, two embedded SBGeoPoint2D at +0x14/+0x1c, four dwords
//     +0x24..+0x30, then byte flags) matches the Mac RHRepulsivePoint::Serialize.
//     It is the member RHElementObject serialises at +0xbc; identity is kept
//     provisional (no tag, cross-binary shape only), so the class keeps a neutral
//     name and the declaration RHElementObject.h already uses.
//
#ifndef RHLINE_H
#define RHLINE_H

#include "SB.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "RHMalignityPosition.h"
#include <vector>

// The serialiser RHElementObject embeds at +0xbc (target 0x00521210). It has no
// type tag, so the class stays provisionally named; the shape matches the Mac
// RHRepulsivePoint::Serialize (see the file header). Layout is 0x40 bytes so the
// following RHElementObject member stays at +0xfc — the size the caller's
// declaration in include/RHElementObject.h reserves.
class RHUnk004b2190Member
{
public:
    bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    char m_pad0[4];    // [0x00] opaque (vptr/base)
    int m_4;           // [0x04] serialised dword (Mac: float)
    int m_8;           // [0x08] serialised dword (Mac: float)
    char m_padc[8];    // [0x0c, 0x14) opaque
    SBGeoPoint2D m_14; // [0x14]
    SBGeoPoint2D m_1c; // [0x1c]
    int m_24;          // [0x24] serialised dword (Mac: float)
    int m_28;          // [0x28] serialised dword (Mac: float)
    int m_2c;          // [0x2c] serialised dword (Mac: float)
    int m_30;          // [0x30] serialised dword (Mac: float)
    char m_34;         // [0x34]
    char m_35;         // [0x35]
    char m_36;         // [0x36]
    char m_37;         // [0x37]
    char m_38;         // [0x38]
    char m_pad39[3];   // [0x39, 0x3c) opaque
    int m_3c;          // [0x3c] serialised dword
};

#include "RHSeekPoint.h"

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once in
// RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

#endif
