#include "rhmenuwindowfocus_00544c50.h"

// SYNTHETIC: GAME 0x00544cf0
// RHFocusManager::~RHFocusManager

RHMenuWindow::RHMenuWindow(RHMenuWindow *, RHMenuWindowScreen *, long, bool) {}

// TEMPLATE: GAME 0x005014a0 FOLDED
// ?BuyNode@RHFocusShortcutTree@@QAEPAURHFocusShortcutNode@@PAU2@H@Z
RHFocusShortcutNode *RHFocusShortcutTree::BuyNode(RHFocusShortcutNode *parent, int color)
{
    RHFocusShortcutNode *node = (RHFocusShortcutNode *)operator new(sizeof(RHFocusShortcutNode));
    node->parent = parent;
    node->color = color;
    return node;
}
