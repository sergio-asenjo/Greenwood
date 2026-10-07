#include "RHElement.h"

void RHBonusInfoBase::FUN_0055fa70(void *) {}
bool RHElementAreaShape::FUN_0060c660(const SBGeoPoint2D &) const { return false; }
RHElementAreaListBase::RHElementAreaListBase(const char &) {}
RHElementAreaListBase::~RHElementAreaListBase() {}
void RHElementAreaListBase::Clear() {}
RHElementAreaIter RHElementAreaListBase::begin() { return RHElementAreaIter(m_04->next); }
RHElementAreaIter RHElementAreaListBase::erase(RHElementAreaIter first, RHElementAreaIter) { return first; }
void RHElementAreaList::GoTo(int) {}
void RHUnk0040f060::GoTo(int) {}
RHUnk0040f060::RHUnk0040f060() : RHElementAreaListBase(*(const char *)this) {}
void RHElementGrid::FUN_004e89d0(void *, int, unsigned) {}
SBGeoPoint2D FUN_005fc4f0(float, const SBGeoPoint2D &point) { return point; }
