#include "RHUIRendererShiftingTitbit.h"

SBGeoVector2D::SBGeoVector2D() : SBGeoPoint2D() {}
SBGeoPoint2D SBGeoPoint2D::operator+(const SBGeoVector2D &) const { return *this; }
SBGeoVector2D SBGeoVector2D::operator-() const { return *this; }
SBGeoVector2D operator*(float, const SBGeoVector2D &value) { return value; }
SBGeoBoundingBox2D &SBGeoBoundingBox2D::operator+=(const SBGeoVector2D &) { return *this; }
void SBResourceManager::FUN_006006f0(long, SBGeoVector2D &) {}
