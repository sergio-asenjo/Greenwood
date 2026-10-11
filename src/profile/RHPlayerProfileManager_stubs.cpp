#include "SBNullstr.h"
#include "RHPlayerProfileManager.h"

RHSaveGameManager::RHSaveGameManager() {}
RHSaveGameManager::~RHSaveGameManager() {}
RHKeyConfig::RHKeyConfig() {}
RHKeyConfig::~RHKeyConfig() { operator delete(m_keys); }
RHSoundConfig::RHSoundConfig() {}
RHGraphicConfig::RHGraphicConfig() : m_point(800.0f, 600.0f) {}
std::string RHPlayerProfile::GetSaveGameDirectory() const { return std::string(); }
void RHPlayerProfile::FUN_0055cc80() {}
// Import-blocked: CreateDirectoryA.
// STUB: GAME 0x0055d830
bool RHPlayerProfileManager::FUN_0055d830() { return true; }
