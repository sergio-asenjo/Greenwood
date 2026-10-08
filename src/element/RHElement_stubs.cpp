#include "RHElement.h"

unsigned RHElementAreaShape::FUN_0060ce80() const { return 0; }
const SBGeoPoint2D &RHElementAreaShape::FUN_0060cef0(unsigned) const { return *(const SBGeoPoint2D *)0; }
RHElementAreaListBase::RHElementAreaListBase(const char &) {}
RHElementAreaListBase::~RHElementAreaListBase() {}
void RHElementAreaListBase::Clear() {}
RHElementAreaIter RHElementAreaListBase::begin() { return RHElementAreaIter(m_04->next); }
RHElementAreaIter RHElementAreaListBase::erase(RHElementAreaIter first, RHElementAreaIter) { return first; }
void RHElementAreaList::GoTo(int) {}
void RHUnk0040f060::GoTo(int) {}
RHUnk0040f060::RHUnk0040f060() : RHElementAreaListBase(*(const char *)this) {}
