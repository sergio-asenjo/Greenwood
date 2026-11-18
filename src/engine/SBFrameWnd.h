#ifndef SBFRAMEWND_H
#define SBFRAMEWND_H

#include "Decomp.h"
#include <string>
#include "RHPortraitRootLifetime.h"

class SBGeoVector2D;
#ifndef SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    ~SBGeoPoint2D();
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float m_x;
    float m_y;
};
#endif

#if !defined(SBGEO_VECTOR2D_VIEW) && !defined(SBGEOVECTOR2D_H)
#define SBGEO_VECTOR2D_VIEW
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};
#endif

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &offset) const;
    bool FUN_006084a0(const SBGeoBoundingBox2D &other);
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
    undefined m_10;
};
#endif

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &offset);
};

#include "RHMobileUnk00607da0.h"

#include "RHUnk00608f10.h"

class SBDrawManager;
extern SBDrawManager *g_unk0x6c11d0;

struct SBFrameEvent
{
    unsigned long type;
    SBGeoBoundingBox2D bounds;
    SBFrameWidgetView *widget;
    SBFrameEvent *next;
};

class SBFrameWidgetView
{
public:
    virtual void V00() = 0;
    virtual void V04(unsigned long display) = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual SBFrameEvent *V14(const void *input) = 0;
    virtual SBFrameInputEvent *V18(const void *input) = 0;
    virtual void V1c(const SBGeoBoundingBox2D &bounds) = 0;
    virtual void V20(const SBGeoPoint2D &position) = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c(const SBGeoBoundingBox2D &bounds) = 0;
};

typedef RHPortraitRootLifetime SBFrameWnd;

#endif
