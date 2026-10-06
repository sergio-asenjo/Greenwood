#include "RHMenuCampaignMap.h"

void RHMapWideText::Tidy(bool) {}
bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
unsigned short *FUN_00419940(unsigned short *destination, const unsigned short *, unsigned) { return destination; }
RHMapBox::RHMapBox(float, float, float, float) {}
std::vector<void *> RHMapCampaign::FUN_00528050() { return std::vector<void *>(); }
unsigned RHMapCampaign::FUN_004577a0() { return 0; }
void RHMapCampaign::FUN_004577b0() {}
unsigned RHMapWindow::FUN_0053baa0(unsigned) { return 0; }
void RHMapWindow::FUN_0053bb30(unsigned) {}
void RHMapWindow::FUN_0053bbe0() {}
void RHMapWindow::FUN_0053c7e0() {}
RHMapDescription::RHMapDescription() {}
RHMapDescription::~RHMapDescription() {}
bool RHMapDescription::FUN_0063cda0(unsigned) { return false; }
RHMapDescription::Entry *RHMapDescription::FUN_0063c9e0(unsigned) { return 0; }
bool RHMapResources::FUN_00600fc0(unsigned) { return false; }
bool RHMapResources::FUN_006009e0(unsigned, unsigned, RHMapWideText &) { return false; }
bool RHMenuCampaignMap::FUN_00544b40(const RHMapTitleText &, const RHMapBox &, unsigned) { return false; }
void RHMenuCampaignMap::FUN_00527a70(RHMapByte) {}
void RHMenuCampaignMap::FUN_00527ae0(RHMapByte) {}
void RHMenuCampaignMap::FUN_00527c00(const std::vector<void *> &) {}
void RHMenuCampaignMap::FUN_005284b0() {}
void RHMenuCampaignMap::FUN_00528810() {}
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, unsigned) {}

// GLOBAL: GAME 0x006c0660
std::string g_unk0x006c0660;
// GLOBAL: GAME 0x006c1840
RHMapResources *g_unk0x006c1840;
