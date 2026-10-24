#include "sbgeo_0060ff30.h"
#include <string.h>
#include "SBGeoBoxLine.h"

RHBoxLine00610070::RHBoxLine00610070(const RHMobileUnk006100e0 &segment)
{
    Second().SBGeoPoint2D::SBGeoPoint2D();
    SBGeoPoint2D::operator=(segment);
    Second() = segment.Second();
}

bool RHBoxIntersection00608800::FUN_00608800(const RHBoxLine00610070 &line) const
{
    const float *bounds = (const float *)this;
    if (!((const unsigned char *)this)[16]) return false;
    float dx = line.Second().m_x - line.m_x;
    float dy = line.Second().m_y - line.m_y;
    if (dx == 0 && (line.m_x < bounds[0] || line.m_x > bounds[2])) return false;
    if (dy == 0 && (line.m_y < bounds[1] || line.m_y > bounds[3])) return false;
    float a = dx * (bounds[1] - line.m_y) - dy * (bounds[0] - line.m_x);
    float b = dx * (bounds[1] - line.m_y) - dy * (bounds[2] - line.m_x);
    float c = dx * (bounds[3] - line.m_y) - dy * (bounds[0] - line.m_x);
    float d = dx * (bounds[3] - line.m_y) - dy * (bounds[2] - line.m_x);
    return !((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0));
}

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHUnk0060fbf0, 0x0c)


// GLOBAL: GAME 0x0067a878
double g_unk0x0067a878 = 9.999999717180685e-10;

// FUNCTION: GAME 0x0060ff30
void RHMobileUnk006100e0::FUN_0060ff30(const RHMobileUnk006100e0 &other)
{
    SBGeoPoint2D::operator=(other);
    Second() = other.Second();
}

// FUNCTION: GAME 0x0060ff50
RHMobileUnk006100e0::RHMobileUnk006100e0(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    : SBGeoPoint2D(first)
{
    ((SBGeoPoint2D *)m_8)->SBGeoPoint2D::SBGeoPoint2D(second);
}

// Parked: typed second-point lifetime is exact but regresses the shared destructor EH states.
// STUB: GAME 0x0060ffa0
RHMobileUnk006100e0::RHMobileUnk006100e0(const RHMobileUnk006100e0 &other)
    : SBGeoPoint2D(other)
{
    memcpy(m_8, other.m_8, sizeof(m_8));
}

// FUNCTION: GAME 0x00610140
RHMobileUnk006100e0 &RHMobileUnk006100e0::FUN_00610140(const RHMobileUnk006100e0 &other)
{
    if (&other != this)
    {
        FUN_00578c50();
        FUN_0060ff30(other);
    }
    return *this;
}

// FUNCTION: GAME 0x00610160
void RHMobileUnk006100e0::FUN_00610160(const SBGeoPoint2D &vector)
{
    Second() = Unk005fc190(vector);
}

// Target keeps the coincident-line block ahead of the shared return and duplicates the result push per branch; VC6 tail-merges it here.
// STUB: GAME 0x006101c0
RHUnk0060fbf0 RHMobileUnk006100e0::FUN_006101c0(const RHMobileUnk006100e0 &other) const
{
    SBGeoPoint2D point;
    RHUnk0060fbf0 result;
    double dx = Second().m_x - m_x;
    double otherDx = other.Second().m_x - other.m_x;
    if (dx != 0.0)
    {
        double slope = (Second().m_y - m_y) / dx;
        double offset = m_y - m_x * slope;
        if (otherDx != 0.0)
        {
            double otherSlope = (other.Second().m_y - other.m_y) / otherDx;
            double otherOffset = other.m_y - other.m_x * otherSlope;
            if (slope != otherSlope)
            {
                double x = (otherOffset - offset) / (slope - otherSlope);
                if (x <= other.m_x + g_unk0x0067a878 && x >= other.Second().m_x - g_unk0x0067a878 ||
                    x >= other.m_x - g_unk0x0067a878 && x <= other.Second().m_x + g_unk0x0067a878)
                {
                    point.m_x = x;
                    point.m_y = x * slope + offset;
                    result.FUN_0060fdc0(point);
                }
                else
                    result.FUN_0060fdb0();
                return result;
            }
            else if (offset == otherOffset)
                result.FUN_0060fe20(other);
            else
                result.FUN_0060fdb0();
        }
        else
        {
            double y = other.m_x * slope + offset;
            if (y <= other.m_y + g_unk0x0067a878 && y >= other.Second().m_y - g_unk0x0067a878 ||
                y >= other.m_y - g_unk0x0067a878 && y <= other.Second().m_y + g_unk0x0067a878)
            {
                point.m_x = other.m_x;
                point.m_y = y;
                result.FUN_0060fdc0(point);
            }
            else
                result.FUN_0060fdb0();
        }
    }
    else if (otherDx != 0.0)
    {
        double otherSlope = (other.Second().m_y - other.m_y) / otherDx;
        double otherOffset = other.m_y - other.m_x * otherSlope;
        if (m_x <= other.m_x + g_unk0x0067a878 && m_x >= other.Second().m_x - g_unk0x0067a878 ||
            m_x >= other.m_x - g_unk0x0067a878 && m_x <= other.Second().m_x + g_unk0x0067a878)
        {
            point.m_x = m_x;
            point.m_y = m_x * otherSlope + otherOffset;
            result.FUN_0060fdc0(point);
        }
        else
            result.FUN_0060fdb0();
    }
    else if (m_x == other.m_x)
        result.FUN_0060fe20(other);
    else
        result.FUN_0060fdb0();
    return result;
}

// FUNCTION: GAME 0x006104f0
float RHMobileUnk006100e0::FUN_006104f0(float y)
{
    float dx = Second().m_x - m_x;
    if (dx != 0.0)
        return dx * (y - m_y) / (Second().m_y - m_y) + m_x;
    return m_x;
}

// FUNCTION: GAME 0x00610520
float RHMobileUnk006100e0::FUN_00610520(float x)
{
    float dy = Second().m_y - m_y;
    if (dy != 0.0)
        return dy * (x - m_x) / (Second().m_x - m_x) + m_y;
    return m_y;
}
