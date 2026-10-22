#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"
#include "RHMenuScreenView.h"
#include "RHUnk00527870.h"

void RHMapConstructValue(std::pair<const std::string, void *> *storage, const std::pair<const std::string, void *> &value)
{
    std::_Construct(storage, value);
}

bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
void RHMapCampaign::FUN_004562a0() {}
bool RHMapDescription::FUN_0063cda0(unsigned) { return false; }
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

void RHMapWindow::FUN_0053b330(unsigned long, unsigned short, float) {}

struct RHMapTreeNode;

struct RHMapTreeIterator
{
    RHMapTreeNode *node;
};

class RHMapTree
{
public:
    RHMapTreeIterator FUN_0053d2f0(RHMapTreeIterator first, RHMapTreeIterator last);
};

RHMapTreeIterator RHMapTree::FUN_0053d2f0(RHMapTreeIterator first, RHMapTreeIterator) { return first; }

SBUILifetime::~SBUILifetime() {}

RHMapScreenTree::~RHMapScreenTree() {}

void *RHMenuScreenView::FUN_0053b730(long, unsigned short) { return 0; }
void RHMenuScreenView::FUN_0053c140(unsigned long) {}

class RHMapFocusWidget
{
public:
    void FUN_00541060();
};

void RHMapFocusWidget::FUN_00541060() {}
