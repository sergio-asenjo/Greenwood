#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"

bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
RHMapDescription::RHMapDescription() {}
RHMapDescription::~RHMapDescription() {}
bool RHMapDescription::FUN_0063cda0(unsigned) { return false; }
class RHMapMission
{
public:
    bool FUN_0054cc20();
};
bool RHMapMission::FUN_0054cc20() { return false; }
unsigned FUN_00527cc0(unsigned) { return 0; }

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

class SBUILifetime
{
public:
    ~SBUILifetime();
};

SBUILifetime::~SBUILifetime() {}

class RHMapScreenTree
{
public:
    ~RHMapScreenTree();
};

RHMapScreenTree::~RHMapScreenTree() {}

class RHMenuScreenView
{
public:
    static void *FUN_0053b730(long background, unsigned short color);
    void FUN_0053c140(unsigned long flags);
};

void *RHMenuScreenView::FUN_0053b730(long, unsigned short) { return 0; }
void RHMenuScreenView::FUN_0053c140(unsigned long) {}

class RHMapFocusScreen
{
public:
    bool FUN_0053c320(void *);
};

class RHMapFocusWidget
{
public:
    void FUN_00541060();
};

bool RHMapFocusScreen::FUN_0053c320(void *) { return false; }
void RHMapFocusWidget::FUN_00541060() {}

void RHMenuCampaignMap::FUN_00527870() {}
