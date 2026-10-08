#include "RHElementActor.h"

void RHUnk0060fbf0::FUN_0060fa20() {}
void RHUnk0060fbf0::FUN_0060fa30(const RHUnk0060fbf0 &) {}


void RHActorString::FUN_00402780() {}
bool RHActorString::FUN_00402280(unsigned, bool) { return true; }
void RHActorString::FUN_00402260(unsigned) {}
void RHActorString::FUN_00401ee0(bool) {}
RHActorString &RHActorString::FUN_00402a70(unsigned, unsigned) { return *this; }

// STUB: GAME 0x006416e6
// ?_Xran@std@@YAXXZ

// LIBRARY: GAME 0x00642580
extern "C" void *memmove(void *destination, const void *, size_t) { return destination; }

SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006090d0(const SBGeoVector2D &) const { return *this; }
RHScriptIter RHScriptIter::operator++(int) { return RHScriptIter(node); }
void RHBonusInfo::FUN_005bd650(int, int) {}
void RHBonusInfo::FUN_005bd7b0(int) {}
unsigned short RHActorGridCalls::FUN_004e9800(const SBGeoPoint2D &, void *&, int &) { return 0xffff; }
bool RHActorGridCalls::FUN_004f5e50(SBGeoPoint2D &, const SBGeoPoint2D &, int) { return false; }
void *RHActorAreaCalls::FUN_0057d800(const SBGeoPoint2D &) { return 0; }
void RHElementActor::FUN_0046bcb0(int) {}
void RHElementActor::FUN_00478c20(RHUnk00613e90 &, bool) {}
void RHElementActor::FUN_00478ae0(RHUnk00613e90 &) {}
void RHElementActor::FUN_00462730(RHElementActor *, bool) {}
void RHElementActor::FUN_00464630() {}

bool RHActorCrossingHumanCalls::FUN_004843a0(void *) { return false; }
bool RHActorCrossingHumanCalls::FUN_004843d0(SBGeoPoint2D &, void *, bool) { return false; }
void RHOrder::FUN_0054e730() {}

void SBGeoPoint2D::FUN_005fc390(const SBGeoPoint2D &other) throw()
{
    m_0 = other.m_0;
    m_4 = other.m_4;
}

RHUnk00613e90::RHUnk00613e90(float x, float y, float z)
{
    m_0 = x;
    m_4 = y;
    m_8 = z;
}

SBGeoVector2D RHBonusInfoBase::FUN_00468f10(int) const
{
    return SBGeoVector2D(*(const SBGeoPoint2D *)this);
}
