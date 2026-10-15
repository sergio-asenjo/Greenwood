#include "SBNullstr.h"
#include "RHArtificialMalignity.h"

bool RHArtificialMalignity::FUN_00438cb0(int, bool) { return false; }

class RHMalignityVisibilityCalls
{
public:
    bool FUN_004860b0();
};

bool RHMalignityVisibilityCalls::FUN_004860b0() { return false; }

class RHMalignityRemarkCalls
{
public:
    void Unk00418c40(int remark, unsigned flags);
};

void RHMalignityRemarkCalls::Unk00418c40(int, unsigned) {}

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

class RHMalignityGuardCalls
{
public:
    void FUN_0049fbb0(void *actor);
};

void RHMalignityGuardCalls::FUN_0049fbb0(void *) {}
void *RHArtificialMalignity::FUN_00445d40() { return 0; }
void RHArtificialMalignity::FUN_00430020() {}
void RHArtificialMalignity::FUN_004303e0() {}
bool RHMalignityActorCalls::FUN_0048a350(void *) { return false; }

class RHMalignityAreaCalls
{
public:
    bool FUN_0060be00(const void *point);
};

bool RHMalignityAreaCalls::FUN_0060be00(const void *) { return false; }
void RHArtificialMalignity::FUN_00430300(int) {}

class RHMalignityAlertCalls
{
public:
    void FUN_0042c890(int type, void *actor);
};

void RHMalignityAlertCalls::FUN_0042c890(int, void *) {}
void RHArtificialMalignity::FUN_0044a830(void *) {}

class RHMalignityPathGeometry
{
public:
    bool FUN_004f9170(const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned short layer, void *radius);
};


class RHMalignityDirection : public RHUnk005fc3b0
{
public:
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
};

bool RHMalignityPathGeometry::FUN_004f9170(const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short, void *) { return false; }
RHUnk005fc3b0 &RHMalignityDirection::FUN_005fc4d0(float) { return *this; }

class RHMalignityHeadingPoint : public SBGeoPoint2D
{
public:
    unsigned char FUN_005fcc50(float value) const;
};

unsigned char RHMalignityHeadingPoint::FUN_005fcc50(float) const { return 0; }

RHMalignityHeadingPoint FUN_0040ec20(const SBGeoPoint2D &, RHMalignityPosition)
{
    RHMalignityHeadingPoint point;
    return point;
}

class RHMalignityAbilityCalls
{
public:
    unsigned short FUN_005c1b50(int index);
};

unsigned short RHMalignityAbilityCalls::FUN_005c1b50(int) { return 0; }
