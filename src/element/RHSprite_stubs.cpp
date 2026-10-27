#include "SBNullstr.h"
#include "RHSprite.h"
#include <math.h>

void RHSprite::Unk005bc920(SBFile &, int) {}
RHSpriteListIterator RHSpriteList::erase(RHSpriteListIterator value)
{
    RHSpriteListNode *node = value.node;
    RHSpriteListIterator next(node->next);
    node->previous->next = node->next;
    node->next->previous = node->previous;
    operator delete(node);
    --count;
    return next;
}
RHSpriteListIterator RHSpriteList::begin() { return RHSpriteListIterator(head->next); }
RHSpriteListIterator RHSpriteList::erase(RHSpriteListIterator first, RHSpriteListIterator last)
{
    while (first.node != last.node)
    {
        RHSpriteListNode *node = first.node;
        first.node = node->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --count;
    }
    return first;
}
RHSpriteListIterator RHSpriteListIterator::operator++(int)
{
    RHSpriteListIterator previous(node);
    node = node->next;
    return previous;
}
bool RHSpritePositionCalls::FUN_00561040(void *, float, unsigned short &, bool) { return false; }
// SYNTHETIC: GAME 0x0054e5c0
// ??_GRHOrder@@UAEPAXI@Z

// FUNCTION: GAME 0x0054e6d0
RHOrder::~RHOrder() {}
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb80() { return RHSpriteOrderIterator(head->next); }
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb30(RHSpriteOrderIterator value) { return value; }

void RHSpriteOrderNode::CopyData(RHOrder **destination, RHOrder *const *source) { *destination = *source; }

double FUN_006433ab(double value) throw() { return floor(value); }
