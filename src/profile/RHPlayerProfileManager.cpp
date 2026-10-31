#include "SBNullstr.h"
#include "RHPlayerProfileManager.h"
#include "RHSaveGameManager.h"
#include "RHKeyConfig.h"
#include "RHGraphicConfig.h"
#include "RHPlayerProfile.h"
#include "RHPlayerProfileListDelete.h"
#include "RHSectorActorList.h"
#include <stdio.h>
#include <stddef.h>
#include <windows.h>

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
DECOMP_SIZE_ASSERT(RHPlayerProfileListStorage, 0x0c)
DECOMP_SIZE_ASSERT(RHProfilePointerList::iterator, 0x04)
DECOMP_SIZE_ASSERT(RHPlayerProfileListStorage::Node, 0x0c)
DECOMP_SIZE_ASSERT(RHProfileListCursor, 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileListStorage::Node, _Next) == 0x00)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileListStorage::Node, _Prev) == 0x04)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileListStorage::Node, _Value) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHProfileListCursor, m_current) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHProfileListCursor, m_dirty) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHProfileListCursor, m_index) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileManager, m_profiles) == 0x04)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileManager, m_active) == 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHPlayerProfileManager, m_2c) == 0x2c)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005f4fc0, m_18) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005f4fc0, m_28) == 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005f4fc0, m_30) == 0x30)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005f4fc0, m_3c) == 0x3c)

void RHSerializeName(SBFile &file, const char *name);
std::wstring FUN_005e23d0(unsigned long id);

// GLOBAL: GAME 0x006c05e0
std::string g_unk0x006c05e0;

// FUNCTION: GAME 0x0052ef80
RHGraphicConfig &RHPlayerProfile::FUN_0052ef80()
{
    return m_graphics;
}

extern undefined g_unk0x006c0e48[];

// FUNCTION: GAME 0x0052ef90
RHPlayerProfileManager *RHPlayerProfileManager::FUN_0052ef90()
{
    return (RHPlayerProfileManager *)g_unk0x006c0e48;
}

// FUNCTION: GAME 0x0055c970
RHPlayerProfile::RHPlayerProfile() :
    m_18(0), m_1c(1), m_20(0), m_24(0), m_2c(0), m_30(0),
    m_point(65536.0f, 65536.0f)
{
}

// FUNCTION: GAME 0x0055ca20
RHPlayerProfile::RHPlayerProfile(unsigned long id, const std::wstring &name, unsigned long difficulty) :
    m_18(id), m_1c(difficulty), m_20(0), m_24(100), m_28(0), m_2c(0), m_30(0),
    m_name(name), m_point(65536.0f, 65536.0f)
{
    CreateSaveGameDirectory();
}

// Parked: helper return-object forwarding and switch-arm scheduling differ.
// STUB: GAME 0x0055cc00
std::wstring RHPlayerProfile::ConvertDifficultyLevelToWideString(unsigned long difficulty)
{
    unsigned long id = difficulty;
    switch (difficulty)
    {
    case 0:
        id = 0x22;
        break;
    case 1:
        id = 0x23;
        break;
    case 2:
        id = 0x24;
        break;
    }
    return FUN_005e23d0(id);
}

// FUNCTION: GAME 0x0055cc80
void RHPlayerProfile::CreateSaveGameDirectory() const
{
    CreateDirectoryA(GetSaveGameDirectory().c_str(), 0);
}

// FUNCTION: GAME 0x0055ccd0
void RHPlayerProfile::DeleteSaveGameDirectory() const
{
    std::string directory;
    std::string pattern;
    directory = GetSaveGameDirectory();
    pattern = directory + "\\" +
        // STRING: GAME 0x006b17b8
        "*";
    WIN32_FIND_DATAA data;
    HANDLE handle = FindFirstFileA(pattern.c_str(), &data);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                std::string file = directory + "\\" + data.cFileName;
                DeleteFileA(file.c_str());
            }
        } while (FindNextFileA(handle, &data));
        FindClose(handle);
    }
    RemoveDirectoryA(directory.c_str());
}

// FUNCTION: GAME 0x0055cf40
const std::wstring &RHPlayerProfile::GetName() const
{
    return m_name;
}

// FUNCTION: GAME 0x0055cf50
std::string RHPlayerProfile::GetSaveGameDirectory() const
{
    char path[260];
    sprintf(path,
        // STRING: GAME 0x006b17bc
        "%s\\Profile_%03i", RHPlayerProfileManager::GetProfilesDirectory().c_str(), m_18);
    return std::string(path);
}

// FUNCTION: GAME 0x0055d060
void RHPlayerProfile::SetName(const std::wstring &name)
{
    m_name.assign(name);
}

// FUNCTION: GAME 0x0055d1a0
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
        CreateSaveGameDirectory();
    }
    else
    {
        count = m_name.size();
        file.Access(&count, 4);
        file.Access((void *)m_name.c_str(), count * 2);
    }
    RHSaveGameManager::Serialize(file);
    return true;
}

#include "RHCampaignValueCalls.h"
#include "RHCampaignCore.h"

extern RHUnk00452030 *g_unk0x6c07fc;

// GLOBAL: GAME 0x00677698
double g_unk0x00677698 = 100.0;

// FUNCTION: GAME 0x0055d370
void RHPlayerProfile::SynchronizeWithCampaign()
{
    RHUnk00452030 *campaign = g_unk0x6c07fc;
    m_20 = campaign->Get(2);
    m_24 = campaign->Get(1);
    m_2c = ((RHCampaign *)campaign)->FUN_00456db0();
    m_30 += campaign->Get(6);
    unsigned first = campaign->Get(5);
    unsigned second = campaign->Get(4);
    if (first == 0 && second == 0)
        m_28 = 0;
    else
        m_28 = (unsigned)((double)second * g_unk0x00677698 / (first + second));
}

// FUNCTION: GAME 0x0055d630
RHPlayerProfileManager::RHPlayerProfileManager() : m_00(0)
{
    m_active = 0;
    m_2c = false;
}

#include "RHPortraitDrawCalls.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

// FUNCTION: GAME 0x0055d670
RHPlayerProfile *RHPlayerProfileManager::AddProfile(const std::wstring &name, unsigned long difficulty)
{
    RHPlayerProfile *profile = new RHPlayerProfile(m_00++, name, difficulty);
    RHGraphicConfig graphics;
    if (m_active)
        graphics.m_point = m_active->m_graphics.m_point;
    else
    {
        RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
        if (*(bool *)((char *)draw + 0x115))
            graphics.m_point = SBGeoVector2D(draw->FUN_005e56c0(0), draw->FUN_005e5750(0));
        else
            graphics.m_point = SBGeoVector2D(800.0f, 600.0f);
    }
    profile->m_graphics = graphics;
    m_profiles.InsertLast(profile);
    return profile;
}

// FUNCTION: GAME 0x0055d830
bool RHPlayerProfileManager::FUN_0055d830()
{
    m_active = AddProfile(L"Robin", 1);
    m_2c = true;
    CreateDirectoryA(g_unk0x006c05e0.c_str(), 0);
    return Save();
}

// FUNCTION: GAME 0x0055d930
void RHPlayerProfileManager::FUN_0055d930(unsigned long index)
{
    FUN_0055da70(m_profiles[index]);
}

// FUNCTION: GAME 0x0055da70
bool RHPlayerProfileManager::FUN_0055da70(RHPlayerProfile *profile)
{
    int index = FUN_0055dbc0(profile);
    profile->DeleteSaveGameDirectory();
    m_profiles.DeleteAt(index);
    profile = profile == m_active ? 0 : m_active;
    m_active = profile;
    return true;
}

// FUNCTION: GAME 0x0055dbc0
int RHPlayerProfileManager::FUN_0055dbc0(RHPlayerProfile *profile)
{
    for (int index = 0; index < (int)m_profiles.size(); ++index)
        if (m_profiles[index] == profile)
            return index;
    return -1;
}

// FUNCTION: GAME 0x0055dd10
RHPlayerProfile *RHPlayerProfileManager::FUN_0055dd10(unsigned long index)
{
    if (index < m_profiles.size())
        return m_profiles[index];
    return 0;
}

// FUNCTION: GAME 0x0055de90
const std::string &RHPlayerProfileManager::GetProfilesDirectory()
{
    return g_unk0x006c05e0;
}

inline void RHPlayerProfileList::RemoveAll()
{
    m_current = begin();
    while (m_current != end())
    {
        delete *m_current;
        AdvanceCurrent();
    }
    Clear();
}

// FUNCTION: GAME 0x0055dea0
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
    int active;
    file.Access(&count, 4);
    if (count > 0)
    {
        RHPlayerProfileList &profiles = m_profiles;
        const unsigned long total = count;
        for (unsigned long index = 0; index < total; ++index)
        {
            RHPlayerProfile *profile = new RHPlayerProfile;
            profile->Serialize(file);
            profiles.InsertLast(profile);
        }
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
    unsigned long count = m_profiles.size();
    file.Access(&count, 4);
    for (int i = 0; (unsigned long)i < count; ++i)
    {
        m_profiles.GetProfile(i)->Serialize(file);
        if (m_profiles.At(i) == m_active)
            active = i;
    }
    file.Access(&active, 4);
    file.FUN_005f5290();
    return true;
}

// FUNCTION: GAME 0x0055e410
void RHPlayerProfileManager::FUN_0055e410(unsigned long index)
{
    if (index >= m_profiles.size())
    {
        m_active = 0;
        return;
    }
    FUN_0055e550(m_profiles[index]);
}

// FUNCTION: GAME 0x0055e550
void RHPlayerProfileManager::FUN_0055e550(RHPlayerProfile *profile)
{
    m_active = profile;
}

// SYNTHETIC: GAME 0x0055e560
// ??1RHPlayerProfile@@QAE@XZ

void RHPlayerProfile::Emit(SBFile &file)
{
    SynchronizeWithCampaign();
    FUN_0052ef80();
    Serialize(file);
}

void RHPlayerProfileManager::Emit()
{
    FUN_0052ef90();
    new RHPlayerProfileManager;
    FUN_0055d930(0);
    FUN_0055e410(0);
    FUN_0055e550(0);
    FUN_0055da70(0);
    FUN_0055dbc0(0);
    FUN_0055dd10(0);
    Load();
    Save();
}
