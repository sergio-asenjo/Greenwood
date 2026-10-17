#include "SBNullstr.h"
#include "RHSprite.h"
#include <math.h>

void RHSpriteList::FUN_005c8e40(int) {}
void RHSprite::Unk005bc920(SBFile &, int) {}
RHSpriteListIterator RHSpriteList::erase(RHSpriteListIterator value) { return value; }
RHSpriteListIterator RHSpriteList::begin() { return RHSpriteListIterator(head->next); }
RHSpriteListIterator RHSpriteListIterator::operator++(int) { return RHSpriteListIterator(node); }
bool RHSpritePositionCalls::FUN_00561040(void *, float, unsigned short &, bool) { return false; }
// SYNTHETIC: GAME 0x0054e5c0
// ??_GRHOrder@@UAEPAXI@Z

// FUNCTION: GAME 0x0054e6d0
RHOrder::~RHOrder() {}
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb80() { return RHSpriteOrderIterator(head->next); }
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb30(RHSpriteOrderIterator value) { return value; }
bool SBGeoBoundingBox2D::FUN_00609050(const SBGeoPoint2D &, const SBGeoPoint2D &) { return false; }

void RHSpriteOrderNode::CopyData(RHOrder **destination, RHOrder *const *source) { *destination = *source; }
SBGeoVector2D RHSpritePositionCalls::FUN_004a4a10() { return SBGeoVector2D(0.0f, 0.0f); }

double FUN_006433ab(double value) throw() { return floor(value); }
