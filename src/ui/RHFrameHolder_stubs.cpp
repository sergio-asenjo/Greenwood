#include "SBNullstr.h"
#include "RHFrameHolder.h"


namespace std
{
// Unannotated: binding this _Construct regresses eight counted callers.
template <>
void _Construct(RHUnk005074d0::Value *destination, const RHUnk005074d0::Value &value)
{
    new ((void *)destination) RHUnk005074d0::Value(value);
}
}

template <>
std::map<unsigned short, unsigned short>::_Pairib
std::map<unsigned short, unsigned short>::insert(const value_type &value)
{
    return _Tr.insert(value);
}

void SBArray<RHFrameHolderRecord>::Insert(RHFrameHolderRecord *, unsigned int, const RHFrameHolderRecord &) {}
void SBArray<RHFrameHolderRecord>::Remove(RHFrameHolderRecord *, RHFrameHolderRecord *) {}
void SBArray<SBGeoVector2D>::Insert(SBGeoVector2D *, unsigned int, const SBGeoVector2D &) {}
void SBArray<SBGeoVector2D>::Remove(SBGeoVector2D *, SBGeoVector2D *) {}
unsigned int SBArray<RHFrameHolderRecord>::GetSize() const { return Size(); }
RHFrameHolderRowMap::Node *RHFrameHolderRowMap::FUN_005093e0(const unsigned long &) { return m_head; }
void RHUnk005051a0Array::FUN_00508090(RHUnk005068e0 *, unsigned int, const RHUnk005068e0 &) {}
RHUnk00641782::RHUnk00641782() {}
RHUnk00641782::~RHUnk00641782() {}
