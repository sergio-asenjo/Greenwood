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
//     It belongs to RHUnk00520ae0 (ctor 0x00520ae0/dtor 0x00520bf0), the
//     member RHElementObject constructs and serialises at +0xbc.
//
#ifndef RHLINE_H
#define RHLINE_H

#include "SB.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "RHMalignityPosition.h"
#include <vector>

#include "RHRepulsivePoint.h"

#include "RHSeekPoint.h"

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once in
// RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

#endif
