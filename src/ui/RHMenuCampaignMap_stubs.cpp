#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"
#include "RHMenuScreenView.h"
#include "RHUnk00527870.h"

bool RHMapWideText::Grow(unsigned, bool) { return false; }
void RHMapWideText::End(unsigned) {}
RHMapDescription::RHMapDescription() {}
RHMapDescription::~RHMapDescription() {}
bool RHMapDescription::FUN_0063cda0(unsigned) { return false; }
// Parked: the case bodies and jump table match; VC6 puts the value in eax and
// sinks the `xor eax,eax` to the end, while the target keeps it in ecx and
// hoists the zero (volatile/switch(value-1) do not flip it). 0.415094.
// STUB: GAME 0x00527cc0
unsigned FUN_00527cc0(volatile unsigned value)
{
    switch (value - 1)
    {
    case 0: return 5;
    case 1:
    case 2: return 6;
    case 3:
    case 4: return 4;
    case 5:
    case 6: return 9;
    case 7: return 7;
    }
    return 0;
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

void RHUnk00527870::FUN_00527870() {}
