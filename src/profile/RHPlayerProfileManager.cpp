#include "RHPlayerProfileManager.h"

DECOMP_SIZE_ASSERT(RHSaveGameManager, 0x18)
DECOMP_SIZE_ASSERT(RHKeyConfig, 0x08)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHSoundConfig, 0x0c)
DECOMP_SIZE_ASSERT(RHGraphicConfig, 0x0c)
DECOMP_SIZE_ASSERT(RHPlayerProfile, 0x74)
DECOMP_SIZE_ASSERT(RHPlayerProfileList, 0x24)
DECOMP_SIZE_ASSERT(RHPlayerProfileManager, 0x30)
DECOMP_SIZE_ASSERT(RHSectorActorConstIter, 0x04)
DECOMP_SIZE_ASSERT(RHSectorActorIter, 0x04)
DECOMP_SIZE_ASSERT(RHSectorActorList, 0x24)
DECOMP_SIZE_ASSERT(RHUnk005c9010Node, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005c9010Iterator, 0x04)
DECOMP_SIZE_ASSERT(RHPlayerProfileListStorage, 0x0c)

void RHSerializeName(SBFile &file, const char *name);

// GLOBAL: GAME 0x006c05e0
std::string g_unk0x006c05e0;

// Unannotated: coupled Save callers; 98.13%, string-limit operand.
std::string FUN_004e4c70(const std::string &first, const char *second)
{
    return std::string(first).append(second);
}

// FUNCTION: GAME 0x0055c970
RHPlayerProfile::RHPlayerProfile() :
    m_18(0), m_1c(1), m_20(0), m_24(0), m_2c(0), m_30(0),
    m_point(65536.0f, 65536.0f)
{
}

// Unannotated: coupled Save caller; 95.35%, call operands and string storage.
bool RHPlayerProfile::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006b17cc
        "RHPlayerProfile");
    file.Access(&m_18, 4);
    file.Access(&m_20, 4);
    file.Access(&m_24, 4);
    file.Access(&m_28, 4);
    file.Access(&m_30, 4);
    file.Access(&m_2c, 4);
    file.Access(&m_1c, 4);
    m_keys1.Serialize(file);
    m_keys2.Serialize(file);
    m_sound.Serialize(file);
    m_graphics.Serialize(file);
    m_point.Serialize(file);
    unsigned long count;
    if (file.m_bLoading)
    {
        file.Access(&count, 4);
        wchar_t *buffer = new wchar_t[count];
        file.Access(buffer, count * 2);
        m_name.assign(buffer, count);
        delete buffer;
        FUN_0055cc80();
        RHSaveGameManager::Serialize(file);
        return true;
    }
    count = m_name.size();
    file.Access(&count, 4);
    file.Access((void *)m_name.c_str(), count * 2);
    RHSaveGameManager::Serialize(file);
    return true;
}

// deferred: 0x0055de90, exact body; unannotated pending reccmp #534.
const std::string &RHPlayerProfileManager::GetProfilesDirectory()
{
    return g_unk0x006c05e0;
}

// Parked at 98.58%: stack coloring and owner reload.
// STUB: GAME 0x0055dea0
bool RHPlayerProfileManager::Load()
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(GetProfilesDirectory() +
        // STRING: GAME 0x006b18dc
        "\\Profiles", 1) != 0)
    {
        SBAssert(0,
            // STRING: GAME 0x006b1860
            "P:\\Robin Hood\\RHplayerprofilemanager.cpp", 0x125,
            // STRING: GAME 0x006b188c
            "Warning : no current player profile archive. Creating default player profiles.");
        return FUN_0055d830();
    }
    unsigned long magic;
    file.Access(&magic, 4);
    if (magic != 0x50524f46)
    {
        SBAssert(0, "P:\\Robin Hood\\RHplayerprofilemanager.cpp", 0x130,
            // STRING: GAME 0x006b1820
            "Warning : invalid profile archive file. Recreating the archive.");
        return FUN_0055d830();
    }
    file.Access(&file.m_version, 4);
    if (file.m_version != 6)
    {
        SBAssert(0, "P:\\Robin Hood\\RHplayerprofilemanager.cpp", 0x13b,
            // STRING: GAME 0x006b17dc
            "Warning : invalid profile archive version. Recreating the archive.");
        return FUN_0055d830();
    }
    m_profiles.RemoveAll();
    file.Access(&m_00, 4);
    unsigned long count;
    file.Access(&count, 4);
    if (count > 0)
    {
        RHPlayerProfileList &profiles = m_profiles;
        unsigned long remaining = count;
        while (remaining != 0)
        {
            RHPlayerProfile *profile = new RHPlayerProfile;
            profile->Serialize(file);
            profiles.InsertLast(profile);
            --remaining;
        }
        int active;
        file.Access(&active, 4);
        m_active = active >= 0 ? m_profiles.GetProfile(active) : 0;
        file.FUN_005f5290();
        return true;
    }
    file.FUN_005f5290();
    return FUN_0055d830();
}

// FUNCTION: GAME 0x0055e160
bool RHPlayerProfileManager::Save() const
{
    RHUnk005f4fc0 file;
    unsigned long magic = 0x50524f46;
    int active = -1;
    if (file.FUN_005f5090(GetProfilesDirectory() + "\\Profiles", 8) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHplayerprofilemanager.cpp", 0x177,
            // STRING: GAME 0x006b18e8
            "Unable to open the profile file");
        return false;
    }
    file.Access(&magic, 4);
    file.m_version = 6;
    file.Access(&file.m_version, 4);
    file.Access((void *)&m_00, 4);
    unsigned long count = m_profiles.m_list.size();
    file.Access(&count, 4);
    for (int i = 0; (unsigned long)i < count; ++i)
    {
        m_profiles.GetProfile(i)->Serialize(file);
        if (m_profiles[i] == m_active)
            active = i;
    }
    file.Access(&active, 4);
    file.FUN_005f5290();
    return true;
}

// Parked at 82.24%: additional destructor vptr store.
// STUB: GAME 0x0055e560
RHPlayerProfile::~RHPlayerProfile()
{
}

void RHPlayerProfile::Emit(SBFile &file)
{
    Serialize(file);
}

void RHPlayerProfileManager::Emit()
{
    Load();
    Save();
}
