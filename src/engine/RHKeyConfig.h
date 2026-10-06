// RHKeyConfig — declarations for RHKeyConfig.cpp (decompiled TU).
//
// BINDING (0x0051ec40 -> RHKeyConfig::Serialize(SBFile&); 0x0051ece0 ->
// RHKeyConfig::SetToPreset(unsigned short, bool)). See src/RHKeyConfig.cpp for
// the evidence chain.
//
// Member offsets are derived from the target instructions:
//   * Serialize (0x0051ec40) serialises a 2-byte field at +0x04 and then the
//     29-key table through the pointer at +0x00 (0x3a = 58 bytes, one
//     SBFile::Access call).
//   * SetToPreset (0x0051ece0) writes `WORD [this+0x04] = keysRead + 2` after
//     reloading the preset, so +0x04 is this configuration's key count.
//
// The class has no vptr — the first member is at +0x00.

#include "SB.h"

class RHKeyConfig
{
public:
    bool Serialize(SBFile &file);

    void SetToPreset(unsigned short preset, bool flag);

    void Emit(SBFile &file);

    short *m_keys; // [0x00]
    short m_count; // [0x04]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);
