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

#include "SB.h"

// Embedded point sub-object at RHGraphicConfig+0x4. Its Serialize is the
// target 0x005fc2a0 (__FILE__ P:\Robin Hood\SBLibNG\SBGeoPoint2D.cpp, two
// 4-byte Access calls at lines 264/265). Only the +0x4 placement matters for
// this TU, so the body stays opaque (two 4-byte fields).
class SBGeoPoint2D
{
public:
    bool Serialize(SBFile &file);

private:
    char m_unk[0x8]; // [0x00, 0x08): opaque; two 4-byte fields
};

class RHGraphicConfig
{
public:
    bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    char m_0;             // [0x0]
    char m_1;             // [0x1]
    char m_2;             // [0x2]
    char m_3;             // [0x3]
    SBGeoPoint2D m_point; // [0x4]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);
