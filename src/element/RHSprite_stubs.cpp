#include "RHSprite.h"
#include <math.h>

void RHSpriteList::FUN_005c8e40(int) {}
RHSpriteListIterator RHSpriteList::erase(RHSpriteListIterator value) { return value; }
RHSpriteListIterator RHSpriteList::begin() { return RHSpriteListIterator(head->next); }
RHSpriteListIterator RHSpriteListIterator::operator++(int) { return RHSpriteListIterator(node); }
bool RHSpritePositionCalls::FUN_00561040(void *, float, unsigned short &, bool) { return false; }
RHOrder::~RHOrder() {}
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb80() { return RHSpriteOrderIterator(head->next); }
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb30(RHSpriteOrderIterator value) { return value; }
void SBGeoBoundingBox2D::FUN_00607d90() {}
unsigned short RHSprite::FUN_005bdcd0(unsigned short) { return 0; }
unsigned short RHSprite::FUN_005bdcf0(unsigned short) { return 0; }

void RHSpriteFrameCalls::FUN_00505940(unsigned) {}
void RHSpriteOrderNode::CopyData(RHOrder **destination, RHOrder *const *source) { *destination = *source; }
SBGeoVector2D RHSpritePositionCalls::FUN_004a4a10() { return SBGeoVector2D(0.0f, 0.0f); }
float SBGeoVector2D::FUN_005fc660(const SBGeoPoint2D &) const { return 0.0f; }

double FUN_006433ab(double value) throw() { return floor(value); }
