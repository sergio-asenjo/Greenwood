// RHSoundConfig — declarations for RHSoundConfig.cpp (decompiled TU).
//
// BINDING (0x005b2190): RHSoundConfig::Serialize(SBFile&). See
// src/RHSoundConfig.cpp for the evidence chain.
//
// Member offsets are derived from the target instructions of
// RHSoundConfig::Serialize (0x005b2190): five shorts at +0x00, +0x02, +0x04,
// +0x06, +0x08 and two chars at +0x0a, +0x0b. Only the offsets the matched
// function touches are laid out; the class is not polymorphic (the target
// accesses +0x00 as a short, so there is no vptr).

#ifndef RHSOUNDCONFIG_H
#define RHSOUNDCONFIG_H

#include "SB.h"

class RHSoundConfig
{
public:
    RHSoundConfig();
    RHSoundConfig(const RHSoundConfig &value);
    bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    short m_0; // [0x00]
    short m_2; // [0x02]
    short m_4; // [0x04]
    short m_6; // [0x06]
    short m_8; // [0x08]
    bool m_a;  // [0x0a]
    char m_b;  // [0x0b]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

#endif
