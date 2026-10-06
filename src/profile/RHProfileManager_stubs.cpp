#include "RHProfileManager.h"
#include "RHMissionProfile.h"
#include "RHActorProfiles.h"
#include "RHProfileFile.h"
#include <algorithm>

RHProfileString::RHProfileString(const std::allocator<char> &allocator) : std::basic_string<char>(allocator) {}
void RHProfileText::FUN_00401ee0(bool)
{
    m_chars = 0;
    m_size = 0;
    m_capacity = 0;
}
void RHProfileText::FUN_00401ce0(const std::string &, unsigned int, unsigned int) {}
int RHProfileText::FUN_00460900(unsigned int, unsigned int, const char *, unsigned int) const { return 0; }

void FUN_005e0c90(SBFile &, std::string &) {}
void **FUN_004598e0(void **first, void **last, void **destination)
{
    while (first != last)
        *destination++ = *first++;
    return destination;
}

int RHProfileManager::GetProfileIndex(const RHHtHWeaponProfile *profile) const
{
    int index = -1;
    RHHtHWeaponProfile **it = std::find(m_handToHand.m_first, m_handToHand.m_last, profile);
    if (it != m_handToHand.m_last)
        index = it - m_handToHand.m_first;
    return index;
}

int RHProfileManager::GetProfileIndex(const RHMissionProfile *profile) const
{
    int index = -1;
    RHMissionProfile **it = std::find(m_missions.m_first, m_missions.m_last, profile);
    if (it != m_missions.m_last)
        index = it - m_missions.m_first;
    return index;
}

int RHProfileManager::GetProfileIndex(const RHBow::Profile *profile) const
{
    int index = -1;
    RHBow::Profile **it = std::find(m_shoot.m_first, m_shoot.m_last, profile);
    if (it != m_shoot.m_last)
        index = it - m_shoot.m_first;
    return index;
}

int RHProfileManager::GetProfileIndex(const RHCharacterProfile *profile) const
{
    int index = -1;
    RHCharacterProfile **it = std::find(m_characters.m_first, m_characters.m_last, profile);
    if (it != m_characters.m_last)
        index = it - m_characters.m_first;
    return index;
}

void FUN_0056cf40(const RHProfileManager *, const char *, ...) {}

int RHProfileManager::FUN_0056cef0(const RHCharacterProfile *profile) const
{
    int index = 0;
    for (RHCharacterProfile **it = m_characters.m_first; it != m_characters.m_last; ++it, ++index)
    {
        if (*it == profile)
            return index;
    }
    FUN_0056cf40(this,
        // STRING: GAME 0x006b21d0
        "In mission profile : character not recognized (%s) defaulting to none\n",
        profile->m_14.c_str());
    return -1;
}

void RHMissionArrayStorage::FUN_004609a0(void *, void *) {}
void RHMissionArrayStorage::FUN_004e5820(void *, const unsigned long &) {}

bool RHProfileText::FUN_00402280(unsigned int, bool) { return false; }
void RHProfileText::FUN_00402260(unsigned int) {}
RHProfileText operator+(const RHProfileText &, const RHProfileText &) { return RHProfileText(); }
RHProfileFile::RHProfileFile() {}
RHProfileFile::~RHProfileFile() {}
int RHProfileFile::FUN_005f5090(const RHProfileText &, int) { return -1; }
int RHProfileFile::FUN_005f5370(int, int) { return -1; }
unsigned long FUN_005e1d00(SBFile &) { return 0; }
void FUN_005e1d50(SBFile &, unsigned long, int) {}
bool FUN_005e2020(SBFile &, unsigned long, int) { return false; }
void FUN_005e20c0(SBFile &) {}
void FUN_005e2300(SBFile &) {}
