#include "SBNullstr.h"
#include "RHElement.h"

RHElementAreaListBase::RHElementAreaListBase(const char &) {}
RHElementAreaListBase::~RHElementAreaListBase() {}
void RHElementAreaListBase::Clear() {}
RHElementAreaIter RHElementAreaListBase::begin() { return RHElementAreaIter(m_04->next); }
RHElementAreaIter RHElementAreaListBase::erase(RHElementAreaIter first, RHElementAreaIter) { return first; }
template<class T>
RHTransientPointerList<T>::RHTransientPointerList() : dirty(true) {}

template class RHTransientPointerList<RHElementArea>;
template class RHTransientPointerList<RHElevationLine>;
template class RHTransientPointerList<void>;

// TEMPLATE: GAME 0x0040f060 FOLDED
// ??0?$RHTransientPointerList@VRHElementArea@@@@QAE@XZ

// TEMPLATE: GAME 0x0040f060 FOLDED
// ??0?$RHTransientPointerList@VRHElevationLine@@@@QAE@XZ

// TEMPLATE: GAME 0x0040f060 FOLDED
// ??0?$RHTransientPointerList@X@@QAE@XZ
