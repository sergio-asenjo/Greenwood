#include "RHDrawManager.h"

// Target 0x0060fc90.
RHUnk0060fbf0::~RHUnk0060fbf0() {}

// Target 0x006092a0.
void SBGeoBoundingBox2D::FUN_006092a0(const SBGeoVector2D &) {}

// Target 0x006092c0.
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006092c0(const SBGeoBoundingBox2D &) const { return *this; }

// Target 0x006093f0.
RHUnk0060fbf0 SBGeoBoundingBox2D::FUN_006093f0(const SBGeoSegment2D &) const { return RHUnk0060fbf0(); }

// Target 0x005e61e0.
void SBDrawManager::FUN_005e61e0(unsigned long, const SBGeoBoundingBox2D &, unsigned short, unsigned long) {}

// Target 0x005ecbd0.
bool SBDrawManager::FUN_005ecbd0(unsigned long, const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short) { return false; }

