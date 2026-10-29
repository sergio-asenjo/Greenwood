#ifndef RHFASTFINDGEOMETRY_H
#define RHFASTFINDGEOMETRY_H

#include "SB.h"

class SBGeoVector2D;
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &);
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    void *FUN_0044e990(unsigned flags);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    bool Serialize(SBFile &file);
    bool operator==(const SBGeoPoint2D &other) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &other) const;
    float FUN_005fc700(float value) const;
    float Unk005fc6d0(float value) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    void FUN_005fc390(const SBGeoPoint2D &other) throw();
    void Set(short x, short y)
    {
        m_x = (float)x;
        m_y = (float)y;
    }
    float X() const { return m_x; }
    float Y() const { return m_y; }
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
    float FUN_005fc660(const SBGeoPoint2D &other) const;
};

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    float Unk005fc6a0(float value);
    void FUN_005fc7c0(float value);
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    unsigned char FUN_005fcc50(float value) const;
    SBGeoVector2D FUN_005fc8f0(bool direction, float value) const;
    SBGeoPoint2D FUN_005fc450() const;
    RHUnk005fc3b0(float x, float y);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float value) const;
};

#endif
