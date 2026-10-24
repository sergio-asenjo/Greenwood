// RHGraphicConfig — declarations shared by RHGraphicConfig.cpp (decompiled TU)
// and RHGraphicConfig_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0051ba00): RHGraphicConfig::Serialize(SBFile&). See
// src/RHGraphicConfig.cpp for the evidence chain.
//
// Member offsets are derived from the target instructions of
// RHGraphicConfig::Serialize (0x0051ba00): four single-byte fields at +0x0,
// +0x1, +0x2, +0x3, then an embedded SBGeoPoint2D at +0x4. The class has no
// vptr — the first serialised field is at +0x0.

#ifndef RHGRAPHICCONFIG_H
#define RHGRAPHICCONFIG_H

#include "RHSprite_calls.h"

#include "RHGraphicConfigClass.h"

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

#endif
