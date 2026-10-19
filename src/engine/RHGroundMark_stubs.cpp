// Stub definitions for the external symbols RHGroundMark.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHGroundMark::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert are defined once in
// RHSword_stubs.cpp; RHSerializeName once in RHElementObject_stubs.cpp;
// SBGeoPoint2D::Serialize once in RHGraphicConfig_stubs.cpp; operator new once
// in crt_stubs.cpp. This TU only defines the remaining targets.

#include "RHGroundMark.h"

// Target 0x00606040.
RHGroundInfo::RHGroundInfo() {}
RHGroundInfo::RHGroundInfo(const RHGroundInfo &) {}
RHGroundInfo::~RHGroundInfo() {}

// Target 0x005c8e40.
void RHGroundInfoList::GoTo(int) {}
