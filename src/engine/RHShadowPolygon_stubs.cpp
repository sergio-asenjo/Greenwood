#include "SBNullstr.h"
#include "RHShadowPolygon.h"

void RHShadowPolygon::FUN_0058d990() {}
void RHShadowPolygon::FUN_0058ec60() {}
void RHShadowPolygon::FUN_0058ffa0(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00590c90(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00592080(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_005934b0(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00595020() {}
void RHShadowPolygon::FUN_005959e0() {}

void RHUnk004a96a0::FUN_004a96a0(void *, void *, void *, bool) {}
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0044e8b0(RHUnk005c9010Iterator, RHUnk005c9010Iterator last) { return last; }

// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?FUN_0044e8b0@RHShadowUnk0044e8b0@@QAE?AURHScriptIter@@U2@0@Z
RHScriptIter RHShadowUnk0044e8b0::FUN_0044e8b0(RHScriptIter first, RHScriptIter last)
{
    RHScriptNode *node = first.node;
    while (node != last.node)
    {
        RHScriptNode *erased = node;
        node = node->next;
        erased->prev->next = erased->next;
        erased->next->prev = erased->prev;
        operator delete(erased);
        --*(unsigned *)((char *)this + 8);
    }
    return RHScriptIter(node);
}


// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?FUN_0046eb30@RHUnk0058e7f0List@@QAE?AURHUnk005c9010Iterator@@U2@@Z
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb30(RHUnk005c9010Iterator position)
{
    RHUnk005c9010Iterator erased = position;
    position.m_node = position.m_node->m_next;
    RHUnk005c9010Node *node = erased.m_node;
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    operator delete(node);
    --m_count;
    return position;
}

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?FUN_0046eb30@RHUnk0058e7f0List@@QAE?AURHUnk005c9010Iterator@@VRHSectorActorIter@@@Z
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb30(RHSectorActorIter position)
{
    RHSectorActorIter erased = position;
    position.m_p = position.m_p->m_next;
    RHSectorActorNode *node = erased.m_p;
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    operator delete(node);
    --m_count;
    return RHUnk005c9010Iterator((RHUnk005c9010Node *)position.m_p);
}

RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb80() { return RHUnk005c9010Iterator(m_head->m_next); }

// TEMPLATE: GAME 0x00424410 FOLDED
// ?FUN_00424410@RHUnk0058e7f0List@@QAE?AURHUnk005c9010Iterator@@U2@ABQAVRHUnk00597a70@@@Z
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_00424410(RHUnk005c9010Iterator position, RHUnk00597a70 *const &value)
{
    RHUnk005c9010Node *next = position.m_node;
    RHUnk005c9010Node *previous = next->m_prev;
    RHUnk005c9010Node *node = (RHUnk005c9010Node *)operator new(sizeof(RHUnk005c9010Node));
    node->m_next = next ? next : node;
    node->m_prev = previous ? previous : node;
    next->m_prev = node;
    node->m_prev->m_next = node;
    new (&node->m_data) RHUnk00597a70 *(value);
    ++m_count;
    return RHUnk005c9010Iterator(node);
}

RHUnk005c9010Iterator RHUnk005c9010Iterator::FUN_0057c9c0(int)
{
    RHUnk005c9010Iterator previous = *this;
    ++*this;
    return previous;
}
void RHShadowUnk0060c260::FUN_0060c260(const SBGeoPoint2D &) {}
void RHShadowUnk0060c260::FUN_0060c280() {}
const SBGeoPoint2D &RHShadowUnk0060c260::FUN_0060c2b0(unsigned short) { return *(const SBGeoPoint2D *)m_0; }
bool RHShadowPolygon::FUN_00598230(RHUnk005977e0 *, RHShadowUnk005df9e0 *, bool) { return false; }
bool RHShadowPolygon::FUN_00598b90(RHUnk005977e0 *, RHShadowUnk005df9e0 *) { return false; }
void RHShadowPolygon::FUN_0059b850(RHUnk005977e0 *, RHShadowUnk005df9e0 *) {}
void RHShadowPolygon::FUN_0059bfb0(RHUnk005977e0 *, RHShadowUnk005df9e0 *) {}
void RHShadowPolygon::FUN_0059c720(RHUnk005977e0 *, RHShadowUnk005df9e0 *) {}
void RHShadowPolygon::FUN_0059d7f0(RHUnk005977e0 *) {}
// TEMPLATE: GAME 0x00613e90 FOLDED
// ??0RHShadowViewport@@QAE@XZ
RHShadowViewport::RHShadowViewport() {}
RHShadowPointNodeList::~RHShadowPointNodeList() {}
// FUNCTION: GAME 0x004243e0
RHShadowPointNode *RHShadowPointNodeList::FUN_004243e0(RHShadowPointNode *next, RHShadowPointNode *previous)
{
    RHShadowPointNode *node = (RHShadowPointNode *)operator new(sizeof(RHShadowPointNode));
    node->m_next = next ? next : node;
    node->m_prev = previous ? previous : node;
    return node;
}

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHPCDescription@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAHABH@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHReceiverInterface@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHUnk0051aa00@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHMission@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHPlayerProfile@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHSaveGame@@ABQAV2@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAUValue@RHUnk005074d0@@ABU23@@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?FUN_0059fb00@@YAXPAPAVRHUnk00597a70@@ABQAV1@@Z
void FUN_0059fb00(RHUnk00597a70 **destination, RHUnk00597a70 *const &value)
{
    if (destination)
        *destination = value;
}
// FUNCTION: GAME 0x0059fb20
void FUN_0059fb20(RHUnk00613e90 *destination, const RHUnk00613e90 &value)
{
    if (destination)
        *destination = value;
}
RHShadowViewport::~RHShadowViewport() {}

// TEMPLATE: GAME 0x005c9010 FOLDED
// ?FUN_005c9010@@YAXAAURHUnk005c9010Iterator@@HUbidirectional_iterator_tag@std@@@Z
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category)
{
    std::_Advance((RHProfilePointerList::iterator &)current, distance, category);
}

// TEMPLATE: GAME 0x005c9010 FOLDED
// ?RHAdvanceProfileCursor@@YAXAAViterator@?$list@PAVRHPlayerProfile@@V?$allocator@PAVRHPlayerProfile@@@std@@@std@@HUbidirectional_iterator_tag@3@@Z
void RHAdvanceProfileCursor(RHProfilePointerList::iterator &current, int distance,
                            std::bidirectional_iterator_tag category)
{
    std::_Advance(current, distance, category);
}
