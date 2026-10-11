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
RHUnk005068e0::RHUnk005068e0() {}
RHUnk005068e0::~RHUnk005068e0() {}
void RHUnk005068e0::FUN_005069d0(unsigned short, SBFile &) {}
void RHUnk005051a0Array::FUN_00508090(RHUnk005068e0 *, unsigned int, const RHUnk005068e0 &) {}
RHUnk00641782::RHUnk00641782() {}
RHUnk00641782::~RHUnk00641782() {}
RHUnk00507500::Iterator RHUnk00507500::FUN_00508a80(Iterator value) { return value; }
RHFrameHolderRowMap::Iterator RHFrameHolderRowMap::FUN_005090e0(Node *, Node *, const Value &) { Iterator result; result.m_node = m_head; return result; }
void RHFrameHolder::FUN_00504c50(unsigned long, unsigned short, unsigned short, unsigned long, unsigned short) {}
void RHFrameHolder::FUN_00504bd0(unsigned long, unsigned short, unsigned short, unsigned long, unsigned short) {}
