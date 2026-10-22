#ifndef RHRENDERERGEOMETRY_H
#define RHRENDERERGEOMETRY_H

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

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
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
