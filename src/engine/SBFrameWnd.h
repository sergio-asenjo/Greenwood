#ifndef SBFRAMEWND_H
#define SBFRAMEWND_H

#include "Decomp.h"
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

#ifndef SBGEOVECTOR2D_H
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

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

struct SBFrameEvent
{
    undefined m_00[0x1c];
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

class SBFrameWnd : public SBFrameWidgetView
{
public:
    void FUN_0061a350(unsigned long display);
    void FUN_0061a3a0();
    void FUN_0061a430(SBGeoBoundingBox2D &bounds);
    void FUN_0061a570();
    SBFrameEvent *FUN_0061a610(const void *input);
    bool FUN_0061ab10(SBFrameWidgetView *widget);
    void FUN_0061ac80(const SBGeoPoint2D &position);
    void FUN_0061ad20(const SBGeoBoundingBox2D &bounds);

    undefined m_04[4];
    SBFrameWidgetView **m_first;
    SBFrameWidgetView **m_last;
    undefined m_10[0x24];
    unsigned long m_flags;
    SBFrameWidgetFindList m_excluded;
    bool m_enabled;
    bool m_visible;
    undefined m_5e[0x12];
    SBGeoBoundingBox2D m_bounds;
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    void *m_resource;
    SBFrameInputEvent m_input;

    int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
};

#endif
