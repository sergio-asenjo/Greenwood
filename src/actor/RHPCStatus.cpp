#include "RHPCStatus.h"
#include <cstring>

void RHPCStatus::Emit(SBFile &file, const RHCharacterProfile &profile)
{
    GenerateName(profile);
    Serialize(file);
}

// FUNCTION: GAME 0x0055bf00
std::wstring RHPCStatus::GenerateName(const RHCharacterProfile &profile)
{
    std::wstring name;
    if (profile.m_35 == 1)
    {
        const char *names[] = {
            // STRING: GAME 0x006ab9a0
            "Robin des bois",
            // STRING: GAME 0x006abb98
            "Robin des villes",
            // STRING: GAME 0x006ab970
            "Will Ecarlate",
            // STRING: GAME 0x006ab994
            "Petit Jean",
            // STRING: GAME 0x006ab988
            "Frere Tuck",
            // STRING: GAME 0x006ab960
            "Lady Marianne",
            // STRING: GAME 0x006ab980
            "Stutely"
        };
        unsigned int i;
        for (i = 0; i < sizeof(names); ++i)
        {
            if (_stricmp(names[i], profile.m_18 ? profile.m_18 : "") == 0)
            {
                name = FUN_005e23d0(i + 0x90);
                break;
            }
        }
        if (i == sizeof(names))
        {
            SBAssert(0,
                // STRING: GAME 0x006b1744
                "P:\\Robin Hood\\RHPCStatus.cpp", 0xd4,
                // STRING: GAME 0x006b1764
                "RHPCStatus : unable to retrive the right VIP name for the profile '%s'",
                profile.m_18 ? profile.m_18 : "");
            // STRING: GAME 0x006b1728
            name = L"Super Star !";
        }
    }
    else
    {
        RHUnk00452030 *campaign = g_unk0x6c07fc;
        int remaining = 10;
        while (remaining != 0)
        {
            name = FUN_0055bdf0(100, 22);
            // STRING: GAME 0x006b1724
            name += L" " + FUN_0055bdf0(122, 22);
            if (!campaign->FUN_004565c0(name))
            {
                campaign->FUN_00456670(name);
                break;
            }
            --remaining;
        }
        if (remaining == 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0xf9,
                // STRING: GAME 0x006b16f8
                "PCStatus : unable to build a new PC name.");
            // STRING: GAME 0x006b16e0
            name = L"Misteryman";
        }
    }
    return name;
}

// deferred: unannotated pending reccmp #534 — the sole residual when annotated is the
// `call RHHumanStatus::Serialize` (0x51d5d0, already matched) routing through the ILT; body
// is otherwise byte-exact (99.57% annotated, differing only in that operand).
bool RHPCStatus::Serialize(SBFile &file)
{
    if (!RHHumanStatus::Serialize(file))
        return false;
    // STRING: GAME 0x006b17ac
    RHSerializeName(file, "RHPCStatus");
    if (file.Access(&m_14, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
            // STRING: GAME 0x006b16c0
            "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b0, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_16, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b1, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_18, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b2, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b3, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b4, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_24, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_26, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_28, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b7, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1e, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b8, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_20, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b9, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_22, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1ba, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_3c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1bb, "Serialize failed reason is %s", reason);
        return false;
    }
    FUN_005e0ea0(file, m_2c);
    return true;
}
