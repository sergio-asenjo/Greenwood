#ifndef RHRENDERERPOINT_H
#define RHRENDERERPOINT_H

class SBGeoVector2D;
#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &other) const;
    float m_x;
    float m_y;
};
#endif

#endif
