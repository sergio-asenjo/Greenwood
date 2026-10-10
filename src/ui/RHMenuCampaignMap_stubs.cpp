#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"

bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
RHMapDescription::RHMapDescription() {}
RHMapDescription::~RHMapDescription() {}
bool RHMapDescription::FUN_0063cda0(unsigned) { return false; }
bool RHMapResources::FUN_006009e0(unsigned, unsigned, RHMapWideText &) { return false; }
bool RHMenuCampaignMap::FUN_0061a1e0(const RHMapTitleText &, const RHMapBox &, unsigned) { return false; }
void RHMapWindowPart::FUN_00618850(void *) {}
bool RHMapWindowPart::FUN_00619ad0(void *) { return false; }
class RHMapMission
{
public:
    bool FUN_0054cc20();
};
bool RHMapMission::FUN_0054cc20() { return false; }
unsigned FUN_00527cc0(unsigned) { return 0; }
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, unsigned) {}

// GLOBAL: GAME 0x006c0660
std::string g_unk0x006c0660;
// GLOBAL: GAME 0x006c1840
RHMapResources *g_unk0x006c1840;
