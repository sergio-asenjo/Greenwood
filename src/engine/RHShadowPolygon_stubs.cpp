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
RHScriptIter RHShadowUnk0044e8b0::FUN_0044e8b0(RHScriptIter, RHScriptIter last) { return last; }
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb30(RHUnk005c9010Iterator current) { return current; }
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb30(RHSectorActorIter current) { return RHUnk005c9010Iterator((RHUnk005c9010Node *)current.m_p); }
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_0046eb80() { return RHUnk005c9010Iterator(m_head->m_next); }
RHUnk005c9010Iterator RHUnk0058e7f0List::FUN_00424410(RHUnk005c9010Iterator position, RHUnk00597a70 *const &) { return position; }
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
void RHShadowPolygon::FUN_0059ce90(RHUnk005977e0 *) {}
void RHShadowPolygon::FUN_0059d7f0(RHUnk005977e0 *) {}
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

void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag)
{
    RHAdvanceProfileCursor((RHProfilePointerList::iterator &)current, distance, std::bidirectional_iterator_tag());
}

void RHAdvanceProfileCursor(RHProfilePointerList::iterator &current, int distance,
                            std::bidirectional_iterator_tag category)
{
    std::_Advance(current, distance, category);
}
