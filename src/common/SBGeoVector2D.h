#ifndef SBGEOVECTOR2D_H
#define SBGEOVECTOR2D_H

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float, float);
    SBGeoVector2D(const SBGeoPoint2D &);
    SBGeoVector2D(const SBGeoVector2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    float FUN_005fc660(const SBGeoPoint2D &) const;
    SBGeoVector2D GetNormalized(float scale) const;
    void Normal(bool direction, float scale);
    bool IsBetween(unsigned char first, unsigned char last) const;
};
SBGeoVector2D operator*(float, const SBGeoVector2D &);

#endif
