#include "SBNullstr.h"
#include "RHArtificialMalignity.h"

class RHMalignityReactionCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, int substate) = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24(RHMalignityStimulus *stimulus) = 0;
    void FUN_00412d60(RHMalignityPosition position, int heading, int mode);
    void FUN_0041a3e0();
};

void RHMalignityReactionCalls::FUN_00412d60(RHMalignityPosition, int, int) {}
void RHMalignityReactionCalls::FUN_0041a3e0() {}
void RHMalignityActorCalls::FUN_00487ad0(const RHMalignityPosition &) {}
void RHArtificialMalignity::FUN_00438620(unsigned short) {}
void RHArtificialMalignity::FUN_0043b1b0(RHMalignityPosition, int) {}
void RHArtificialMalignity::FUN_0043c960(RHMalignityPosition, int) {}

void RHMalignityActorCalls::FUN_00478c20(RHUnk00613e90 &, bool) {}
bool RHMalignityActorCalls::FUN_0048a130(void *) { return false; }
float RHMalignityBaseView::FUN_0041a010(void *) { return 0.0f; }
float RHMalignityBaseView::FUN_0041a060(void *) { return 0.0f; }
float RHMalignityBaseView::FUN_0041a0b0(void *) { return 0.0f; }
bool RHArtificialMalignity::FUN_0044afa0(void *) { return false; }
// STUB: GAME 0x00440cf0
short RHArtificialMalignity::FUN_00440cf0(RHUnk00441dd0Record *) { return 0; }
void RHMalignityActorCalls::FUN_00487aa0(int) {}
void RHMalignityBaseView::FUN_00412cf0(const RHMalignityPosition &, unsigned short, int) {}
void RHArtificialMalignity::FUN_00440040(void *, RHMalignityPosition, RHUnk005fc3b0 *, int, void *) {}
SBGeoPoint2D FUN_005fc580(const SBGeoPoint2D &point, float) { return point; }
RHMalignityPosition FUN_0040ed40(const RHMalignityPosition &position, SBGeoVector2D) { return position; }
RHMalignityPosition FUN_0040ece0(const RHMalignityPosition &position, SBGeoPoint2D) { return position; }

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
RHScriptIter RHAIUnk0044e8b0::FUN_0044e8b0(RHScriptIter, RHScriptIter last) { return last; }
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
