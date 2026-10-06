#include "RHPlayerProfileManager.h"

RHPlayerProfile::RHPlayerProfile() {}
RHPlayerProfile::~RHPlayerProfile() {}
bool RHPlayerProfile::Serialize(SBFile &) { return true; }
void RHPlayerProfileListStorage::FUN_004e6c10() {}
bool RHPlayerProfileManager::FUN_0055d830() { return true; }
const std::string &RHPlayerProfileManager::GetProfilesDirectory()
{
    static std::string directory;
    return directory;
}
