#ifndef SB_GEO_POINT_2D_H
#define SB_GEO_POINT_2D_H

#include "Decomp.h"

class SBFile;

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D() throw();
    SBGeoPoint2D(float x, float y) throw();
    SBGeoPoint2D(const SBGeoPoint2D &other) throw();
    ~SBGeoPoint2D() throw();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc250(const SBGeoPoint2D &other);
    void FUN_005fc270();
    bool Serialize(SBFile &file);
    void FUN_005fc330();
    void Emit(SBFile &file);

    float m_x; // 0x00
    float m_y; // 0x04
};

#endif
