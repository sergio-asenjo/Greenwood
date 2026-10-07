#include "RHElementActor.h"

void RHActorScriptContext::FUN_004030a0() {}
void RHElementActor::FUN_0046c8e0(int) {}

void RHActorString::FUN_00402780() {}
bool RHActorString::FUN_00402280(unsigned, bool) { return true; }
void RHActorString::FUN_00402260(unsigned) {}
void RHActorString::FUN_00401ee0(bool) {}
RHActorString &RHActorString::FUN_00402a70(unsigned, unsigned) { return *this; }

// STUB: GAME 0x006416e6
// ?_Xran@std@@YAXXZ

// LIBRARY: GAME 0x00642580
extern "C" void *memmove(void *destination, const void *, size_t) { return destination; }

bool SBGeoPoint2D::operator==(const SBGeoPoint2D &) const { return true; }
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006090d0(const SBGeoVector2D &) const { return *this; }
void RHUnk00613e90::FUN_00467990(float x, float y, float z) { m_0 = x; m_4 = y; m_8 = z; }
RHUnk00613e90 RHUnk00613e90::FUN_005df550(const RHUnk00613e90 &) const { return *this; }
RHScriptIter RHScriptIter::operator++(int) { return RHScriptIter(node); }
int RHSequenceElement::Unk00587160(int) { return 0; }
void RHActorScriptContext::FUN_004033b0(int, int, int) {}
void RHBonusInfo::FUN_005bd650(int, int) {}
void RHBonusInfo::FUN_005bd7b0(int) {}
unsigned short RHActorGridCalls::FUN_004e9800(const SBGeoPoint2D &, void *&, int &) { return 0xffff; }
bool RHActorGridCalls::FUN_004f5e50(SBGeoPoint2D &, const SBGeoPoint2D &, int) { return false; }
void *RHActorAreaCalls::FUN_0057d800(const SBGeoPoint2D &) { return 0; }
void RHElementActor::FUN_0046bcb0(int) {}
const SBGeoPoint2D &RHElementActor::FUN_004679b0() const { return *(SBGeoPoint2D *)((char *)Info() + 0x24); }
bool RHElementActor::FUN_004679c0(SBGeoPoint2D, int) { return false; }
void RHElementActor::FUN_00478c20(RHUnk00613e90 &, bool) {}
void RHElementActor::FUN_00478ae0(RHUnk00613e90 &) {}
void RHElementActor::FUN_00462700(unsigned short) {}
void RHElementActor::FUN_00462730(RHElementActor *, bool) {}
void RHElementActor::FUN_00464630() {}
void RHActorPositionCalls::FUN_00464530(const SBGeoPoint2D &) {}
