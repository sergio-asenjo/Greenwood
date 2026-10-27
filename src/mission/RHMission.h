// RHMission — declarations shared by RHMission.cpp (decompiled TU) and
// RHMission_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0054cc40): RHMission::Serialize(SBFile&). See
// src/RHMission.cpp for the evidence chain.
//
// Member offsets are derived from the target instructions of
// RHMission::Serialize (0x0054cc40): the +0x0 slot is a profile pointer
// (read into a local, handed to RHProfileManager::SerializeProfilePointer and
// written back), then two 2-byte fields at +0x4/+0x6 and a 4-byte field at
// +0x8. Every other byte is opaque padding.

#ifndef RHMISSION_H
#define RHMISSION_H

#include <string>
#include "SB.h"

class SBFile;
class RHMissionProfile;
class RHProfileManager;

// Provisional free-function form of the singleton accessor at 0x00436500: it
// lazily constructs and returns the process-wide RHProfileManager (global
// 0x6c0e84). Its own TU is not proven (symbols/tu-attribution.tsv: mixed), so
// the name stays neutral; only its return type is fixed by the call it feeds
// (an RHProfileManager::SerializeProfilePointer receiver).
RHProfileManager *RHUnk00436500GetProfileManager();

class RHMission
{
public:
    bool Serialize(SBFile &file);
    bool AreRequiredMissionStatusValid(bool value) const;

    void Emit(SBFile &file);

    RHMissionProfile *m_profile; // [0x0]
    short m_4;                   // [0x4]
    unsigned short GetM6() const { return m_6; }
    unsigned short m_6;          // [0x6]
    int m_8;                     // [0x8]
    RHMission();
    RHMission(const RHMission &value);
    RHMission(const RHMissionProfile *profile);
    int FUN_0054cbf0();
    int FUN_0054cc20();
    bool FUN_0054c8a0(std::string &reason);
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

#endif
