#ifndef RHRENDERERGEOMETRY_H
#define RHRENDERERGEOMETRY_H

#include "RHRendererPoint.h"

#if !defined(SBGEO_VECTOR2D_VIEW) && !defined(SBGEOVECTOR2D_H)
#define SBGEO_VECTOR2D_VIEW
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(const SBGeoPoint2D &other);
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};
#endif

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(float, float, float, float);
    SBGeoBoundingBox2D(const SBGeoPoint2D &point);
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~SBGeoBoundingBox2D() {}
    bool FUN_006083b0(const SBGeoPoint2D &point) const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    bool Unk00608f30() const;
    void FUN_00607d90();
    SBGeoBoundingBox2D &FUN_00607da0(const SBGeoBoundingBox2D &other);
    void FUN_00607e90(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &offset) const;
    SBGeoBoundingBox2D operator-(const SBGeoVector2D &offset) const;
    float Width() const { return m_second.m_x - m_first.m_x; }
    float Height() const { return m_second.m_y - m_first.m_y; }
    const SBGeoPoint2D &Max() const { return m_second; }
    void SetMax(const SBGeoPoint2D &point)
    {
        m_10 = true;
        m_second = point;
    }
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
    bool m_10;
};
#endif

#endif
