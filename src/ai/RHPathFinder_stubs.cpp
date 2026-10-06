#include "RHPathFinder.h"

SBGeoPoint2D SBGeoBoundingBox2D::FUN_00608f40() const { return first; }
const SBGeoBoundingBox2D &RHPathActorInfo::FUN_00560450() { return *(SBGeoBoundingBox2D *)((char *)this + 0xc0); }
bool RHPathObstacleGrid::FUN_004f5750(SBGeoBoundingBox2D &, unsigned short) { return true; }
bool RHPathObstacleGrid::FUN_004f5890(SBGeoBoundingBox2D &, unsigned short) { return true; }
void RHPathFinder::FUN_00552d50(unsigned char) {}
void RHPathFinder::FUN_00554750() {}
void RHPathFinder::FUN_00556260() {}
RHUnkIter RHPathRequestList::FUN_0046eb80() { return RHUnkIter(head->next); }
