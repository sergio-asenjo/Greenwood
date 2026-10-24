#include "RHSprite_calls.h"
#include "SBGeoVectorRotation.h"
#include "RHMobileUnk006100e0.h"
#include <math.h>

// FUNCTION: GAME 0x005fc3b0
SBGeoVector2D::SBGeoVector2D()
{
}

// FUNCTION: GAME 0x005fc3e0
SBGeoVector2D::SBGeoVector2D(const SBGeoVector2D &other)
{
    FUN_005fc390(other);
}

// FUNCTION: GAME 0x005fc430
SBGeoVector2D &SBGeoVector2D::operator=(const SBGeoVector2D &other)
{
    if (this != &other)
    {
        ((RHMobileUnk006100e0 *)this)->FUN_00578c50();
        FUN_005fc390(other);
    }
    return *this;
}

// FUNCTION: GAME 0x005fc580
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor)
{
    return operator*(factor, point);
}

// FUNCTION: GAME 0x005fc5b0
RHUnk005fc3b0 &RHUnk005fc3b0::FUN_005fc5b0(float factor)
{
    m_x /= factor;
    m_y /= factor;
    return *this;
}

// FUNCTION: GAME 0x005fc660
float SBGeoVector2D::FUN_005fc660(const SBGeoPoint2D &other) const
{
    return other.m_y * m_y + other.m_x * m_x;
}

// FUNCTION: GAME 0x005fc680
float RHUnk005fc3b0::FUN_005fc680(const RHUnk005fc3b0 &other, float value) const
{
    return (other.m_y * m_x - m_y * other.m_x) / value;
}

// FUNCTION: GAME 0x005fc7f0
SBGeoVector2D SBGeoVector2D::GetNormalized(float scale) const
{
    SBGeoVector2D result;
    float length = ((RHUnk005fc3b0 *)this)->Unk005fc6a0(scale);
    result.m_x = m_x / length;
    result.m_y = m_y / length;
    return result;
}


// FUNCTION: GAME 0x005fc880
void SBGeoVector2D::Normal(bool direction, float scale)
{
    if (scale == 1.0f)
    {
        float x = m_x;
        if (direction)
        {
            m_x = -m_y;
            m_y = x;
        }
        else
        {
            m_x = m_y;
            m_y = -x;
        }
    }
    else
    {
        float x = m_x;
        if (direction)
        {
            m_x = -(scale * m_y);
            m_y = x / scale;
        }
        else
        {
            m_x = m_y / scale;
            m_y = -(x * scale);
        }
    }
}

// FUNCTION: GAME 0x005fc8f0
SBGeoVector2D RHUnk005fc3b0::FUN_005fc8f0(bool direction, float scale) const
{
    SBGeoVector2D result;
    if (scale == 1.0f)
    {
        if (direction)
        {
            result.m_x = -(m_y / scale);
            result.m_y = scale * m_x;
        }
        else
        {
            result.m_x = m_y / scale;
            result.m_y = -(scale * m_x);
        }
    }
    else if (direction)
    {
        result.m_x = -(m_y / scale);
        result.m_y = scale * m_x;
    }
    else
    {
        result.m_x = m_y / scale;
        result.m_y = -(scale * m_x);
    }
    return result;
}

// FUNCTION: GAME 0x005fc9a0
void RHEngineCameraRotationCalls::FUN_005fc9a0(float angle, float scale)
{
    m_y /= scale;
    float x = m_x;
    double sine = sin(angle);
    double cosine = cos(angle);
    m_x = m_x * cosine - m_y * sine;
    m_y = x * sine + m_y * cosine;
    m_y *= scale;
}

// FUNCTION: GAME 0x005fc9e0
RHUnk005fc3b0 RHUnk005fc3b0::FUN_005fc9e0(float angle, float scale)
{
    RHUnk005fc3b0 result;
    float y = m_y / scale;
    double cosine = cos(angle);
    double sine = sin(angle);
    result.m_x = m_x * cosine - y * sine;
    float rotatedY = m_x * sine + y * cosine;
    result.m_y = rotatedY * scale;
    return result;
}


// FUNCTION: GAME 0x005fca90
float SBGeoPoint2D::FUN_005fca90(const SBGeoPoint2D &other, float scale) const
{
    SBGeoVector2D first(m_x, m_y / scale);
    SBGeoVector2D second(other.m_x, other.m_y / scale);
    float dot = first.FUN_005fc660(second);
    float cross = ((RHUnk005fc3b0 *)&first)->FUN_005fc680((const RHUnk005fc3b0 &)second, 1.0f);
    if (cross == 0.0f)
        return dot > 0.0f ? 0.0f : 3.1415927410125732421875f;
    float angle = atan(cross / dot);
    if (dot >= 0.0f)
        return angle;
    if (cross > 0.0f) {
        float result = angle;
        result += 3.1415927f;
        return result;
    }
    return angle - 3.1415927f;
}


// Parked: x87 product lifetimes and quadrant-branch layout differ.
// STUB: GAME 0x005fcc50
unsigned char RHUnk005fc3b0::FUN_005fcc50(float scale) const
{
    scale *= m_x;
    float x = scale;
    x *= 0.9807852506637573f;
    float firstY = m_y;
    firstY *= 0.19509032368659973f;
    x -= firstY;
    float y = scale;
    y *= 0.19509032368659973f;
    float secondY = m_y;
    secondY *= 0.9807852506637573f;
    y += secondY;
    bool negativeX;
    bool positiveY;
    bool steep;
    bool narrow;
    if (x < 0.0f)
    {
        x = -x;
        negativeX = true;
    }
    else
        negativeX = false;
    if (y > 0.0f)
        positiveY = true;
    else
    {
        positiveY = false;
        y = -y;
    }
    if (y < x)
    {
        steep = true;
        x *= 0.4142135679721832f;
        narrow = y > x;
    }
    else
    {
        steep = false;
        y *= 0.4142135679721832f;
        narrow = x > y;
    }
    unsigned char sector = 0;
    if (negativeX)
        sector = 8;
    if (negativeX != positiveY)
        sector |= 4;
    if ((negativeX != positiveY) != steep)
        sector |= 2;
    if (((negativeX != positiveY) != steep) != narrow)
        sector |= 1;
    return sector;
}

// FUNCTION: GAME 0x005fcd70
bool SBGeoVector2D::IsBetween(unsigned char first, unsigned char last) const
{
    unsigned char sector = ((const RHUnk005fc3b0 *)this)->FUN_005fcc50(1.0f);
    if (first <= last)
    {
        if (sector < first || sector > last)
            return false;
    }
    else if (sector < first && sector > last)
        return false;
    return true;
}

void EmitSBGeoVector2D(SBGeoVector2D *vector)
{
    vector->GetNormalized(1.0f);
    vector->Normal(true, 1.0f);
    vector->IsBetween(0, 1);
    ((RHEngineCameraRotationCalls *)vector)->FUN_005fc9a0(0.0f, 1.0f);
    vector->FUN_005fca90(*vector, 1.0f);
    FUN_005fc580(*vector, 1.0f);
    ((RHUnk005fc3b0 *)vector)->FUN_005fc8f0(true, 1.0f);
    ((RHUnk005fc3b0 *)vector)->FUN_005fc9e0(0.0f, 1.0f);
}
