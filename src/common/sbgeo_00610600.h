#ifndef SBGEO_00610600_H
#define SBGEO_00610600_H

#include "Decomp.h"
#include <list>
#include <vector>

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

#include "RHUnk0053bf20.h"

#include "SBGeoSegment2D.h"

#include "SBGeoPolyLine2DList.h"

class RHMobileUnk00611360;

class RHUnkPolyArrayBase : public std::vector<SBGeoPoint2D>
{
public:
    RHUnkPolyArrayBase() : m_dirty(true) {}
    ~RHUnkPolyArrayBase() { Destroy(); }
    void Destroy() { clear(); }
    undefined4 m_10;    // 0x10
    bool m_dirty;       // 0x14
    undefined4 m_18;    // 0x18
    SBGeoPoint2D m_1c;  // 0x1c
};

// SIZE 0x24
class RHMobileUnk00611360 : public RHUnkPolyArrayBase
{
public:
    RHMobileUnk00611360();
    RHMobileUnk00611360(const RHMobileUnk00611360 &other);
    void FUN_00610e20(const RHMobileUnk00611360 &other);
    unsigned long FUN_00610f30() const;
    void FUN_00610f50(const SBGeoPoint2D &point, unsigned long index);
    SBGeoSegment2D FUN_006112d0(unsigned long index) const;
};

class RHUnkTargetPoints : public RHUnkPolyArrayBase
{
public:
    void FUN_00611100(const SBGeoPoint2D &point);
};

#include "RHUnkSectorPoints.h"

#endif
