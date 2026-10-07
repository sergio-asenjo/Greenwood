#include "RHSprite.h"
#include <math.h>

void RHSpriteList::FUN_005c8e40(int) {}
RHSpriteListIterator RHSpriteList::erase(RHSpriteListIterator value) { return value; }
RHSpriteListIterator RHSpriteList::begin() { return RHSpriteListIterator(head->next); }
void RHSprite::FUN_005b7720(int) {}
void RHSprite::FUN_005b7300(int, int) {}
bool RHSprite::FUN_005b7820(int) { return false; }
void RHSprite::FUN_005bd450() {}
void RHUnk005b5ed0::FUN_005bd8b0() {}
RHSpriteListIterator RHSpriteListIterator::operator++(int) { return RHSpriteListIterator(node); }
SBGeoPoint2D &SBGeoPoint2D::FUN_005fc1e0(const SBGeoPoint2D &) { return *this; }
unsigned short RHSpriteEngineCalls::FUN_004d9090() { return 0; }
void RHSpritePositionCalls::FUN_0055f550() {}
bool RHSpritePositionCalls::FUN_00560460() { return false; }
void RHSpritePositionCalls::FUN_00560780(float, unsigned short) {}
bool RHSpritePositionCalls::FUN_00561040(void *, float, unsigned short &, bool) { return false; }
bool RHSpritePositionCalls::FUN_00563e90() { return false; }
void RHSpritePositionCalls::FUN_00563ea0() {}
RHOrder::RHOrder(RHOrder &) {}
RHOrder::~RHOrder() {}
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb80() { return RHSpriteOrderIterator(head->next); }
RHSpriteOrderIterator RHSpriteOrderList::FUN_0046eb30(RHSpriteOrderIterator value) { return value; }
void RHSpriteSequenceCalls::FUN_005859e0(RHOrder *, unsigned short) {}
unsigned short RHSprite::FUN_005bdbf0(unsigned short, unsigned short) { return 0; }
short RHSprite::FUN_005bdc20(unsigned short, unsigned short) { return 0; }

double FUN_006433ab(double value) throw() { return floor(value); }
