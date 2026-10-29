// RHMission.cpp — translation unit with __FILE__ evidence at 0x0054cc40
// ("P:\Robin Hood\RHMission.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0054cc40 -> RHMission::Serialize(SBFile&)):
//   - TU:        rhmission.cpp (embedded __FILE__ string 0x006b11e0).
//   - Class:     RHMission (symbols/oracle-correlation.tsv:
//                rhmission -> class RHMission, 19 methods).
//   - Method:    RHMission::Serialize(SBFile&) — the Mac oracle's
//                rhmission.cpp has exactly one Serialize
//                (symbols/mac-functions-by-file.tsv: 0x0016c82c Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHMission" (string
//         0x006b12dc) via 0x005e1b70 — the name matches the TU's class;
//       * three SBFile::Access checks on the object at +0x4/2, +0x6/2, +0x8/4
//         (lines 333..335) and two on a stack local (lines 338/339), all using
//         the "Serialize failed reason is %s" assert idiom (format 0x006a7390,
//         empty fallback 0x006773d0);
//       * the tail is a profile round-trip: the value at +0x0 is read into a
//         local, the singleton at 0x00436500 (RHProfileManager, global
//         0x6c0e84) is obtained, its method 0x0056d2a0 (__FILE__
//         P:\Robin Hood\RHProfileManager.cpp) resolves the profile through the
//         manager's table ([edi+0x54], the index/-1/null convention), and on
//         success the local is written back to +0x0.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHProfileManager.h"
#include "RHMission.h"
#include "RHMissionProfile.h"
#include "RHCampaignMissionStatus.h"

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;

// FUNCTION: GAME 0x0054c6f0
bool RHMission::AreRequiredMissionStatusValid(bool value) const
{
    RHUnk00451f00 *campaign = (RHUnk00451f00 *)g_unk0x6c07fc;
    std::vector<unsigned long> *required = (std::vector<unsigned long> *)(value == true ? &m_profile->m_94 : &m_profile->m_a4);
    for (unsigned index = 0; index < required->size(); ++index)
    {
        bool status = campaign->FUN_00451ff0(required->at(index))->m_8 != 0;
        if (status != value)
            return false;
    }
    return true;
}

#include "RHCampaignValueCalls.h"
#include "RHCampaignCore.h"

// FUNCTION: GAME 0x0054c800
bool RHMission::IsAccessible() const
{
    char *campaign = (char *)g_unk0x6c07fc;
    void **first = *(void ***)(campaign + 0x118);
    unsigned count = first == 0 ? 0 : *(void ***)(campaign + 0x11c) - first;
    char difficulty = *(campaign + 0x100);
    unsigned value = g_unk0x6c07fc->Get(1);
    const char *profile = (const char *)m_profile;
    if (value >= *(const unsigned *)(profile + 0x40) &&
        (*(const unsigned *)(profile + 0x44) >= value || *(const unsigned *)(profile + 0x44) == 200000) &&
        count >= *(const unsigned short *)(profile + 0x48) &&
        *(const unsigned short *)(profile + 0x4a) >= count &&
        (unsigned short)m_4 < *(const unsigned short *)(profile + 0x4c) &&
        (*(profile + 0x54) != 1 || *(profile + 0x55 + difficulty)) &&
        AreRequiredMissionStatusValid(true))
        return AreRequiredMissionStatusValid(false) ? true : false;
    return false;
}

// FUNCTION: GAME 0x0054c8a0
bool RHMission::IsAccessible(std::string &reason) const
{
    char *campaign = (char *)g_unk0x6c07fc;
    unsigned count = ((RHCampaign *)campaign)->m_114.size();
    char difficulty = *(campaign + 0x100);
    unsigned value = g_unk0x6c07fc->Get(1);
    const char *profile = (const char *)m_profile;
    if (value < *(const unsigned *)(profile + 0x40))
    {
        // STRING: GAME 0x006b12c8
        reason.assign("Not enough money");
        return false;
    }
    else if (*(const unsigned *)(profile + 0x44) < value && *(const unsigned *)(profile + 0x44) != 200000)
    {
        // STRING: GAME 0x006b12b8
        reason.assign("Too much money");
        return false;
    }
    else if (count < *(const unsigned short *)(profile + 0x48))
    {
        // STRING: GAME 0x006b12a0
        reason.assign("Not enough gang members");
        return false;
    }
    else if (*(const unsigned short *)(profile + 0x4a) < count)
    {
        // STRING: GAME 0x006b1288
        reason.assign("Too many gang members");
        return false;
    }
    else if ((unsigned short)m_4 >= *(const unsigned short *)(profile + 0x4c))
    {
        // STRING: GAME 0x006b1274
        reason.assign("Age limit exceeded");
        return false;
    }
    else if (*(profile + 0x54) == 1 && !*(profile + 0x55 + difficulty))
    {
        // STRING: GAME 0x006b1254
        reason.assign("Incompatible with ARES state");
        return false;
    }
    else if (!AreRequiredMissionStatusValid(true))
    {
        // STRING: GAME 0x006b122c
        reason.assign("Some missions are required to be played");
        return false;
    }
    else if (!AreRequiredMissionStatusValid(false))
    {
        // STRING: GAME 0x006b1200
        reason.assign("Some missions are required not to be played");
        return false;
    }
    // STRING: GAME 0x006b11fc
    reason.assign("OK");
    return true;
}

// FUNCTION: GAME 0x0054cbf0
int RHMission::FUN_0054cbf0()
{
    unsigned type = m_profile->m_34;
    if (type == 5 || type == 1)
        return 1;
    return 0;
}

// FUNCTION: GAME 0x0054cc20
int RHMission::FUN_0054cc20()
{
    unsigned type = m_profile->m_34;
    if (type == 1 || type == 6)
        return 1;
    return 0;
}

// FUNCTION: GAME 0x0054cc40
bool RHMission::Serialize(SBFile &file)
{
    RHMissionProfile *profile = m_profile;

    // STRING: GAME 0x6b12dc
    RHSerializeName(file, "RHMission");

    if (file.Access(&m_4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b11e0
                 "P:\\Robin Hood\\RHMission.cpp",
                 333,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMission.cpp", 334, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMission.cpp", 335, "Serialize failed reason is %s", reason);
        return false;
    }

    short scratch;
    if (file.Access(&scratch, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMission.cpp", 338, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&scratch, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMission.cpp", 339, "Serialize failed reason is %s", reason);
        return false;
    }

    if (RHUnk00436500GetProfileManager()->SerializeProfilePointer(file, profile))
    {
        m_profile = profile;
    }

    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHMission::Serialize in the build.
void RHMission::Emit(SBFile &file)
{
    AreRequiredMissionStatusValid(true);
    FUN_0054cbf0();
    FUN_0054cc20();
    Serialize(file);
}
