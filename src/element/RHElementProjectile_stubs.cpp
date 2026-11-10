#include "SBNullstr.h"
#include "RHElementProjectile.h"
#include "SBGeoPoint2D.h"
#include "SBGeoBoundingBox2DCore.h"

#include "RHProjectileSoundCalls.h"

class RHFastFindGrid
{
public:
    bool FUN_004e9570(const SBGeoPoint2D &point, unsigned short layer);
    bool FUN_004f2d10(const RHUnk00613e90 &from, float plane, RHUnk00613e90 &impact,
        const SBGeoBoundingBox2D &box, int type);
};

bool RHFastFindGrid::FUN_004f2d10(const RHUnk00613e90 &from, float plane, RHUnk00613e90 &impact,
    const SBGeoBoundingBox2D &box, int type)
{
    SBGeoPoint2D point;
    point.m_x = from.x;
    point.m_y = from.y;
    impact = from;
    if (!box.FUN_00608400(point))
        return false;
    if (!FUN_004e9570(point, (unsigned short)type))
        return false;
    impact.z = plane;
    return true;
}

bool RHProjectileRefreshCalls::FUN_004b82e0() { return false; }
