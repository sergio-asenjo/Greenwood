#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"
#include "RHMenuScreenView.h"
#include "RHUnk00527870.h"

// FUNCTION: GAME 0x0053e280
void RHMapConstructValue(std::pair<const std::string, SBFontUnk0061e840 *> *storage, const std::pair<const std::string, SBFontUnk0061e840 *> &value)
{
    new ((void *)storage) std::pair<const std::string, SBFontUnk0061e840 *>(value);
}

bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
// FUNCTION: GAME 0x00527cc0
unsigned FUN_00527cc0(unsigned value)
{
    unsigned index = value;
    unsigned result = 0;
    switch (index - 1)
    {
    case 0: result = 5; break;
    case 1:
    case 2: result = 6; break;
    case 3:
    case 4: result = 4; break;
    case 5:
    case 6: result = 9; break;
    case 7: result = 7; break;
    }
    return result;
}

// GLOBAL: GAME 0x006c0660
std::string g_unk0x006c0660;
// GLOBAL: GAME 0x006c1840
RHMapResources *g_unk0x006c1840;
