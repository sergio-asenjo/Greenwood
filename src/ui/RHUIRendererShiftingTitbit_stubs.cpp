#include "SBNullstr.h"
#include "RHUIRendererShiftingTitbit.h"

SBGeoPoint2D SBGeoPoint2D::operator+(const SBGeoVector2D &) const { return *this; }
SBGeoBoundingBox2D &SBGeoBoundingBox2D::operator+=(const SBGeoVector2D &) { return *this; }
