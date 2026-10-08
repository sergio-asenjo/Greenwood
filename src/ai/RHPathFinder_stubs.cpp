#include "RHPathFinder.h"

SBGeoPoint2D SBGeoBoundingBox2D::FUN_00608f40() const { return first; }
void RHPathFinder::FUN_00552d50(unsigned char) {}
void RHPathFinder::FUN_00554750() {}
void RHPathFinder::FUN_00555a10(unsigned short, unsigned short, unsigned, RHPathWorkList &) {}
void RHPathQueryCalls::FUN_005c8e40(int) {}
RHUnkIter RHPathRequestList::FUN_0046eb80() { return RHUnkIter(head->next); }

void RHPathPointList::FUN_00610ac0() {}
void RHPathPointList::FUN_00610a00(const SBGeoPoint2D &) {}
void RHPathPointList::FUN_00610a60(const SBGeoPoint2D &) {}
void RHPathPointList::FUN_00610b50(int) {}
const SBGeoPoint2D &RHPathPointList::FUN_00610cb0(int) { return *(SBGeoPoint2D *)this; }
void FUN_005557c0() {}
bool FUN_00558210(const SBGeoPoint2D &) { return false; }
bool FUN_00557e70(const SBGeoPoint2D &, const SBGeoPoint2D &) { return false; }
bool FUN_00556990(SBGeoPoint2D, SBGeoPoint2D) { return false; }
void FUN_00553e60(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHPathSearchNode *FUN_00556490(const SBGeoPoint2D &) { return 0; }
unsigned char FUN_00554b80(RHPathSearchNode *, unsigned char, RHPathPointList &) { return 0; }
void FUN_005553d0(RHPathSearchNode *, unsigned char, unsigned char, RHPathPointList &) {}
