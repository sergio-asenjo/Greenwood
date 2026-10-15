#include "sbgeo_0060ff30.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHUnk0060fbf0, 0x0c)

// GLOBAL: GAME 0x00677490
double g_unk0x00677490 = 0.0;

// GLOBAL: GAME 0x0067a878
double g_unk0x0067a878 = 9.999999717180685e-10;

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
    m_8 = Unk005fc190(vector);
}

// Target keeps the coincident-line block ahead of the shared return and duplicates the result push per branch; VC6 tail-merges it here.
// STUB: GAME 0x006101c0
RHUnk0060fbf0 RHMobileUnk006100e0::FUN_006101c0(const RHMobileUnk006100e0 &other) const
{
    SBGeoPoint2D point;
    RHUnk0060fbf0 result;
    double dx = m_8.m_x - m_x;
    double otherDx = other.m_8.m_x - other.m_x;
    if (dx != g_unk0x00677490)
    {
        double slope = (m_8.m_y - m_y) / dx;
        double offset = m_y - m_x * slope;
        if (otherDx != g_unk0x00677490)
        {
            double otherSlope = (other.m_8.m_y - other.m_y) / otherDx;
            double otherOffset = other.m_y - other.m_x * otherSlope;
            if (slope != otherSlope)
            {
                double x = (otherOffset - offset) / (slope - otherSlope);
                if (x <= other.m_x + g_unk0x0067a878 && x >= other.m_8.m_x - g_unk0x0067a878 ||
                    x >= other.m_x - g_unk0x0067a878 && x <= other.m_8.m_x + g_unk0x0067a878)
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
            if (y <= other.m_y + g_unk0x0067a878 && y >= other.m_8.m_y - g_unk0x0067a878 ||
                y >= other.m_y - g_unk0x0067a878 && y <= other.m_8.m_y + g_unk0x0067a878)
            {
                point.m_x = other.m_x;
                point.m_y = y;
                result.FUN_0060fdc0(point);
            }
            else
                result.FUN_0060fdb0();
        }
    }
    else if (otherDx != g_unk0x00677490)
    {
        double otherSlope = (other.m_8.m_y - other.m_y) / otherDx;
        double otherOffset = other.m_y - other.m_x * otherSlope;
        if (m_x <= other.m_x + g_unk0x0067a878 && m_x >= other.m_8.m_x - g_unk0x0067a878 ||
            m_x >= other.m_x - g_unk0x0067a878 && m_x <= other.m_8.m_x + g_unk0x0067a878)
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
    float dx = m_8.m_x - m_x;
    if (dx != g_unk0x00677490)
        return dx * (y - m_y) / (m_8.m_y - m_y) + m_x;
    return m_x;
}

// FUNCTION: GAME 0x00610520
float RHMobileUnk006100e0::FUN_00610520(float x)
{
    float dy = m_8.m_y - m_y;
    if (dy != g_unk0x00677490)
        return dy * (x - m_x) / (m_8.m_x - m_x) + m_y;
    return m_y;
}
