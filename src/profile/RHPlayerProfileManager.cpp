#include "RHPlayerProfileManager.h"

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

void RHPlayerProfileManager::Emit()
{
    Load();
    Save();
}
