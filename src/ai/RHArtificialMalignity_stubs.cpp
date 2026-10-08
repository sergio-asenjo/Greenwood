#include "RHArtificialMalignity.h"

bool RHUnk00608f10::FUN_006082a0(void *) { return false; }
void RHMalignityActorCalls::FUN_00478c20(RHUnk00613e90 &, bool) {}
unsigned char RHMalignityActorCalls::FUN_0048c8e0(void *, bool) { return 0; }
bool RHMalignityActorCalls::FUN_0048a130(void *) { return false; }
float RHMalignityBaseView::FUN_0041a010(void *) { return 0.0f; }

RHMalignityPosition RHMalignityBaseView::FUN_004165e0(void *, bool)
{
    RHMalignityPosition position;
    return position;
}

SBGeoPoint2D RHMalignityBaseView::FUN_0040cbf0(const RHMalignityPosition &)
{
    return SBGeoPoint2D();
}

void RHMalignityNodeValue::FUN_0040eab0(int) {}
RHMalignityIterator RHAIUnk0044e8b0::FUN_0044e8b0(RHMalignityIterator, RHMalignityIterator last) { return last; }
RHMalignityIterator RHAIUnk0044e8b0::FUN_0046eb80() { return RHMalignityIterator(0); }
RHMalignityIterator RHAIUnk0044e8b0::FUN_00424410(RHMalignityIterator position, void *const &) { return position; }
void RHAIUnk0044e8b0::FUN_0045a440(void *const &) {}

bool RHMalignityGeometryCalls::FUN_004eff80(const RHUnk00613e90 &, const RHUnk00613e90 &, int) { return false; }
RHUnk00613e90 RHMalignityVectorCalls::FUN_005df550(const RHUnk00613e90 &) { return RHUnk00613e90(); }

SBGeoPoint2D FUN_0040ec20(const RHMalignityPosition &, RHMalignityPosition)
{
    return SBGeoPoint2D();
}

RHMalignitySegment::RHMalignitySegment(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHMalignitySegment::~RHMalignitySegment() {}
RHMalignityRectangle::RHMalignityRectangle() {}
RHMalignityRectangle::~RHMalignityRectangle() {}
void RHMalignityArrayCalls::FUN_0059fba0(const unsigned &) {}
void RHMalignityArrayCalls::FUN_004e60a0(void *, unsigned, const unsigned &) {}
void RHMalignityArrayCalls::FUN_004e62b0(void *, unsigned, const RHMalignitySegment &) {}
RHMalignityQueryList::RHMalignityQueryList() {}
void RHMalignityQueryList::FUN_004e6c10() {}
void RHMalignityQueryList::FUN_004e52a0() {}
void RHMalignityGridCalls::FUN_004ed370(RHMalignityQueryList &, unsigned short, const RHMalignitySegment &, unsigned) {}
void RHMalignityGridCalls::FUN_004ed070(RHMalignityQueryList &, unsigned short, const SBGeoBoundingBox2D &, unsigned) {}
