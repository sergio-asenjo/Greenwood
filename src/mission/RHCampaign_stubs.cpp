#include "RHCampaign.h"

extern "C" int __cdecl rand() { return 0; }

int RHUnk00452030::FUN_00453d60(const void *) { return -1; }
void FUN_0045a4f0(RHMission **, RHMission **, bool (*)(RHMission *, RHMission *), int) {}
bool FUN_0054c780(RHMission *, RHMission *) { return false; }
void FUN_0045a940(RHMission **, RHMission **, bool (*)(RHMission *, RHMission *), int) {}
void FUN_004e7210(RHMission **, RHMission **, bool (*)(RHMission *, RHMission *), int) {}

void RHCampaignWideString::Tidy(bool) {}
void RHCampaignWideString::Assign(const RHCampaignWideString &, unsigned, unsigned) {}
void RHCampaignWideStrings::Destroy(RHCampaignWideString *, RHCampaignWideString *) {}
void RHCampaignWideStrings::Insert(RHCampaignWideString *, unsigned, const RHCampaignWideString &) {}

RHSectorProduction::RHSectorProduction(int) {}
RHSectorProduction &RHSectorProduction::operator=(const RHSectorProduction &) { return *this; }
void RHCampaignProductionSectors::Destroy(RHSectorProduction *, RHSectorProduction *) {}
void RHCampaignProductionSectors::Insert(RHSectorProduction *, unsigned, const RHSectorProduction &) {}

RHPCDescription::RHPCDescription() {}
RHPCDescription::RHPCDescription(void *, bool) {}
RHPCDescription::~RHPCDescription() {}
void *RHPCDescription::FUN_00459dd0(unsigned) { return this; }
bool RHPCDescription::FUN_0055bb30(SBFile &) { return false; }
RHMission::RHMission() {}
void RHCampaignArrayOps::FUN_0044ea70() {}
unsigned RHCampaignArrayOps::FUN_004580a0() { return 0; }
void RHCampaignArrayOps::FUN_00457a30(const RHCampaignArrayOps &) {}
void RHCampaignArrayOps::FUN_00570330() {}
void RHCampaignMissionValues::FUN_00507960(RHMission *, RHMission *) {}
void RHCampaignMissionValues::FUN_00457e80(RHMission *, const RHMission &) {}
bool FUN_00453930(SBFile &, RHMission &) { return false; }
bool FUN_00453940(SBFile &, RHMission *&) { return false; }
bool FUN_00456a30(SBFile &, RHSectorProduction &) { return false; }
bool FUN_00456aa0(SBFile &, unsigned long &) { return false; }
void RHCampaign::FUN_004526f0(std::vector<RHMission *> &) {}
void RHCampaign::FUN_00452810(std::vector<RHMission *> &) {}
void RHCampaign::FUN_00452a50(std::vector<RHMission *> &) {}
void RHCampaign::FUN_00452c90(std::vector<RHMission *> &) {}
void RHCampaign::FUN_00455f00(std::vector<RHMission *> &) {}
void RHCampaign::FUN_00456e60() {}
void RHCampaignMissionList::FUN_004e6c10() {}
void RHCampaignMissionList::FUN_0045a440(const RHMission *const &) {}
void RHCampaignMissionList::FUN_005c8e40(unsigned) {}
void RHCampaignText::FUN_004021c0(const char *, unsigned) {}
RHCampaignProfiles::RHCampaignProfiles() {}
RHCampaignProfiles::~RHCampaignProfiles() {}
void *RHCampaignProfiles::FUN_0056d5d0(const RHProfileText &, bool) { return 0; }
int RHCampaignCommandLine::FUN_0045a010(const RHProfileText &) { return 0; }
void RHCampaignCommandLine::FUN_00457be0() {}

// GLOBAL: GAME 0x006c05cc
RHCampaignCommandLine g_unk0x6c05cc;
// GLOBAL: GAME 0x006c0e84
RHCampaignProfiles *g_unk0x6c0e84;

RHbeamMe::RHbeamMe(const RHbeamMe &) {}
RHbeamMe &RHCampaignBeamArray::FUN_00457bc0(unsigned, unsigned) { return *(RHbeamMe *)this; }
bool RHCampaign::FUN_00454c00(RHbeamMe, unsigned short) { return false; }
void RHCampaign::FUN_004552f0(SBArray<RHElement *> &, RHbeamMe, unsigned short) {}
void RHCampaign::FUN_004559f0() {}
void RHCampaignByteArray::FUN_00457cb0(char *, unsigned, const char &) {}
void RHCampaignLoadingProgress::FUN_00523300() {}
void RHEngine::FUN_004e3770(RHElement *) {}
void FUN_0044e940(unsigned short *, const unsigned short *) {}
template<>
RHScriptIter RHCampaignIndexList<false>::FUN_004fe2e0(RHScriptIter position, const unsigned short &) { return position; }

// GLOBAL: GAME 0x00677438
float g_unk0x00677438 = 10.0f;
// GLOBAL: GAME 0x006c0a50
RHCampaignLoadingProgress g_unk0x6c0a50;
