#include "SBNullstr.h"
#include "RHArtificialMalignity.h"
#include <math.h>

extern float g_unk0x006774f0;

SBGeoVector2D RHMalignityActorCalls::FUN_004135b0()
{
    RHUnk005fc3b0 direction;
    direction.Unk005fcd40(RHMalignityField<unsigned short>(RHMalignityField<void *>(this, 0x50), 0xd8), 0.57357645f);
    return direction;
}

bool RHArtificialMalignity::FUN_00438cb0(int, bool) { return false; }

#include "RHMalignityVisibilityCalls.h"


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
    void FUN_0041a140(RHMalignityPosition position, unsigned value);
    void FUN_0041a3e0();
};

void RHMalignityReactionCalls::FUN_00412d60(RHMalignityPosition, int, int) {}
void RHMalignityReactionCalls::FUN_0041a140(RHMalignityPosition, unsigned) {}
void RHArtificialMalignity::FUN_0043b1b0(RHMalignityPosition, int) {}
void RHArtificialMalignity::FUN_0043c960(RHMalignityPosition, int) {}

void RHMalignityActorCalls::FUN_00478c20(RHUnk00613e90 &, bool) {}
bool RHMalignityActorCalls::FUN_0048a130(void *) { return false; }

static inline RHUnk00613e90 &RHMalignityScaleHeight(RHUnk00613e90 &vector)
{
    float scaled = vector.y;
    scaled *= g_unk0x006774ec;
    vector.y = scaled;
    return vector;
}

static inline float RHMalignityScaledSquare(RHUnk00613e90 &vector)
{
    RHMalignityScaleHeight(vector);
    return vector.x * vector.x + vector.z * vector.z + vector.y * vector.y;
}

// FUNCTION: GAME 0x0041a010
float RHMalignityBaseView::FUN_0041a010(void *actor)
{
    return RHMalignityScaledSquare(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(actor, 0x50), 0x10).FUN_005df550(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(m_actor, 0x50), 0x10)));
}

// FUNCTION: GAME 0x0041a060
float RHMalignityBaseView::FUN_0041a060(void *actor)
{
    return (float)sqrt(RHMalignityScaledSquare(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(actor, 0x50), 0x10).FUN_005df550(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(m_actor, 0x50), 0x10))));
}

// FUNCTION: GAME 0x0041a0b0
float RHMalignityBaseView::FUN_0041a0b0(void *actor)
{
    return RHMalignityScaleHeight(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(actor, 0x50), 0x10).FUN_005df550(RHMalignityField<RHUnk00613e90>(RHMalignityField<void *>(m_actor, 0x50), 0x10))).FUN_005df680();
}

class RHUnk0041a0f0
{
public:
    int FUN_0041a0f0(int first, int second, int third);
};

// Parked: x87 multiply form; VC6 emits fimul/right-first where the target does
// fild span, fild c, fmul K, fmulp (span*(c*K)). Casts and a named span do not
// change the tree. 0.444444.
// STUB: GAME 0x0041a0f0
int RHUnk0041a0f0::FUN_0041a0f0(int first, int second, int third)
{
    int base = first & 0xffff;
    int span = (second & 0xffff) - base;
    return (int)((float)span * ((third & 0xff) * g_unk0x006774f0) + base);
}
// STUB: GAME 0x00440cf0
short RHArtificialMalignity::FUN_00440cf0(RHUnk00441dd0Record *) { return 0; }

extern unsigned char g_unk0x006c06ca;

// FUNCTION: GAME 0x00412cf0
void RHMalignityBaseView::FUN_00412cf0(const RHMalignityPosition &position, unsigned short heading, int mode)
{
    *(bool *)((char *)this + 0x72) = true;
    *(bool *)((char *)this + 0x73) = ~((unsigned char)mode >> 6) & 1;
    if (g_unk0x006c06ca < 10)
        *(unsigned short *)((char *)this + 0x74) = heading;
    else
        *(unsigned short *)((char *)this + 0x74) = (100 - g_unk0x006c06ca) * heading / 100;
    ((RHArtificialIntelligence *)this)->Unk00412240((const RHUnk00571160Position &)position, mode | 0x80, 1.0f);
}
void RHArtificialMalignity::FUN_00440040(void *, RHMalignityPosition, RHUnk005fc3b0 *, int, void *) {}
// FUNCTION: GAME 0x0040ed40
RHMalignityPosition FUN_0040ed40(const RHMalignityPosition &position, SBGeoVector2D vector)
{
    RHMalignityPosition result = position;
    result.x -= vector.m_x;
    result.y -= vector.m_y;
    return result;
}

// FUNCTION: GAME 0x0040ece0
RHMalignityPosition FUN_0040ece0(const RHMalignityPosition &position, SBGeoPoint2D point)
{
    RHMalignityPosition result = position;
    result.x += point.m_x;
    result.y += point.m_y;
    return result;
}

RHMalignityPosition RHMalignityBaseView::FUN_004165e0(void *, bool)
{
    RHMalignityPosition position;
    return position;
}

// FUNCTION: GAME 0x0040cbf0
SBGeoPoint2D RHMalignityBaseView::FUN_0040cbf0(const RHMalignityPosition &position)
{
    return SBGeoPoint2D(position.x, position.y);
}

// FUNCTION: GAME 0x0040eab0
void *RHMalignityNodeValue::FUN_0040eab0(int mode)
{
    if (mode & 1)
        operator delete(this);
    return this;
}
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

// FUNCTION: GAME 0x0049fbb0
void RHMalignityGuardCalls::FUN_0049fbb0(void *actor)
{
    *(void **)((char *)this + 0x5e8) = actor;
}
void *RHArtificialMalignity::FUN_00445d40() { return 0; }
void RHArtificialMalignity::FUN_004303e0() {}
bool RHMalignityActorCalls::FUN_0048a350(void *) { return false; }

class RHMalignityAreaCalls
{
public:
    bool FUN_0060be00(const void *point);
};

bool RHMalignityAreaCalls::FUN_0060be00(const void *) { return false; }
void RHArtificialMalignity::FUN_00430300(int) {}

void RHArtificialMalignity::FUN_0044a830(void *) {}


class RHMalignityDirection : public RHUnk005fc3b0
{
};


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
    int FUN_005c2130(float value, int first, int second);
};

// FUNCTION: GAME 0x005c1b50
unsigned short RHMalignityAbilityCalls::FUN_005c1b50(int index)
{
    return *(unsigned short *)((char *)*(void **)((char *)this + 4) + index * 2);
}

// FUNCTION: GAME 0x005c2130
int RHMalignityAbilityCalls::FUN_005c2130(float value, int first, int second)
{
    if (FUN_005c1b50(first) < value)
    {
        if (FUN_005c1b50(second) >= value)
            return 1;
    }
    return 0;
}

void EmitRHMalignityAbilityCalls(RHMalignityAbilityCalls *self)
{
    int (RHMalignityAbilityCalls::*f)(float, int, int) = &RHMalignityAbilityCalls::FUN_005c2130;
    (self->*f)(0.0f, 0, 0);
}

RHMalignityOwnedPoint::~RHMalignityOwnedPoint() {}

RHMalignityOwnedRecord::~RHMalignityOwnedRecord() {}
