#include "RHFrameHolder.h"

template <>
std::map<unsigned short, unsigned short>::_Pairib
std::map<unsigned short, unsigned short>::insert(const value_type &value)
{
    return _Tr.insert(value);
}

unsigned short RHEngine::FUN_004d2340(int) { return 0; }
int RHUnk005f4fc0::FUN_005f5d60(const std::string &, int) { return 0; }
unsigned long RHFrameHolder::FUN_00505980(unsigned long, unsigned long &, unsigned short &, unsigned short &, long &, long &) { return 0; }
unsigned short RHFrameHolder::FUN_005051a0(unsigned short, SBFile &) { return 0; }
void RHFrameHolder::FUN_00504b10(unsigned long, unsigned long, unsigned short) {}
void SBArray<RHFrameHolderRecord>::Insert(RHFrameHolderRecord *, unsigned int, const RHFrameHolderRecord &) {}
void SBArray<RHFrameHolderRecord>::Remove(RHFrameHolderRecord *, RHFrameHolderRecord *) {}
void SBArray<SBGeoVector2D>::Insert(SBGeoVector2D *, unsigned int, const SBGeoVector2D &) {}
void SBArray<SBGeoVector2D>::Remove(SBGeoVector2D *, SBGeoVector2D *) {}
unsigned int SBArray<RHFrameHolderRecord>::GetSize() const { return Size(); }
RHFrameHolderRowMap::Iterator RHFrameHolderRowMap::Find(const unsigned long &) { Iterator result; result.m_node = m_head; return result; }
RHFrameHolderRowMap::Pair RHFrameHolderRowMap::Insert(const Value &) { Pair result; result.first.m_node = m_head; result.second = false; return result; }
RHFrameHolderRowMap::Pair RHFrameHolderRowMap::InsertTree(const Value &) { Pair result; result.first.m_node = m_head; result.second = false; return result; }
