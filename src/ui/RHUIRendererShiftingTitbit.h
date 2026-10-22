#ifndef RHUIRENDERERSHIFTINGTITBIT_H
#define RHUIRENDERERSHIFTINGTITBIT_H

#include "SB.h"
#include "SBUIRenderer.h"

class SBGeoVector2D;

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D operator+(const SBGeoVector2D &) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    float m_x; // +0x00
    float m_y; // +0x04
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    SBGeoVector2D(const SBGeoPoint2D &);
    ~SBGeoVector2D() {}
    SBGeoVector2D operator-() const;
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

SBGeoVector2D operator*(float, const SBGeoVector2D &);
class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &);
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    SBGeoBoundingBox2D &operator+=(const SBGeoVector2D &);
    void UnkSecondPoint(const SBGeoPoint2D &point)
    {
        m_flag = true;
        m_p1 = point;
    }
    SBGeoPoint2D m_p0; // +0x00
    SBGeoPoint2D m_p1; // +0x08
    bool m_flag; // +0x10; sizeof = 0x14
};

class SBResourceManager
{
public:
    bool GetSurfaceForResource(long, unsigned, unsigned &);
    bool FUN_006006f0(long id, SBGeoVector2D &value)
    {
        return ((SBUIUnk006006f0 *)this)->FUN_006006f0(id, (RHUnk005fc3b0 &)value);
    }
};

#ifndef RHUNK00600820_VIEW
#define RHUNK00600820_VIEW
class RHUnk00600820
{
public:
    bool ResolveSurface(void *surface, unsigned int id, float *value);
};
#endif

class SBDrawManager
{
public:
    void BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
                         SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned long);
};

class RHUnk005ef320
{
public:
    void FUN_005e57e0(unsigned, SBGeoVector2D &);
};

extern RHUnk005ef320 *g_unk0x6c11d0;

#include "RHUIRendererShiftingTitbitClass.h"

#define TitbitResource (*(SBResourceManager **)((char *)this + 0x04))
#define TitbitBox (*(SBGeoBoundingBox2D *)((char *)this + 0x08))
#define TitbitBlitArg (*(unsigned long *)((char *)this + 0x20))
#define TitbitWord4c (*(unsigned short *)((char *)this + 0x4c))
#define TitbitWord4e (*(unsigned short *)((char *)this + 0x4e))
#define TitbitWord50 (*(unsigned short *)((char *)this + 0x50))

#endif
