#ifndef RHPOSITIONINTERFACE_H
#define RHPOSITIONINTERFACE_H

#include "RHPositionInterfaceCore.h"
#include "RHUnk005fc3b0.h"
#include "RHPathGeometryCalls.h"

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

inline void RHPositionInterface::AssignBox(const SBGeoBoundingBox2D &box)
{
    ((RHMobileUnk00607da0 *)&m_94)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
}

inline void RHPositionInterface::AssignOffset(const SBGeoVector2D &offset)
{
    m_80 = offset;
}

inline void RHPositionInterface::UpdateBox()
{
    SBGeoVector2D offset(*(SBGeoVector2D *)&m_20);
    ((RHMobileUnk00607da0 *)&m_c0)->FUN_00607da0((const RHMobileUnk00607da0 &)Box().FUN_006090d0(offset));
}

inline void RHPositionInterface::SetPoint(SBGeoPoint2D &point, float x, float y)
{
    point.m_x = x;
    point.m_y = y;
}

inline void RHPositionInterface::MapFrom3D()
{
    SetPoint(m_20, m_c.x, m_c.y - m_c.z);
    UpdateBox();
}

inline void RHPositionInterface::SpriteFromMap()
{
    m_18 = m_20.FUN_005fc200(m_80);
    Floor(m_18.m_x);
    Floor(m_18.m_y);
}

inline void RHPositionInterface::Increment3DFromMap()
{
    m_60.x = m_6c.m_x;
    if (m_ec)
    {
        float horizontal = m_ec->m_4c * m_6c.m_x;
        float slope = m_ec->m_50;
        m_60.z = (horizontal + slope * m_6c.m_y) / (1.0f - m_ec->m_50);
        m_60.y = m_60.z + m_6c.m_y;
    }
    else
    {
        m_60.y = m_6c.m_y;
        m_60.z = 0;
    }
}

inline void RHPositionInterface::Position3DFromMap()
{
    m_c.x = m_20.m_x;
    if (m_ec)
    {
        m_c.z = (m_ec->m_4c * m_20.m_x + m_ec->m_50 * m_20.m_y + m_ec->m_54) / (1.0f - m_ec->m_50);
        m_c.y = m_c.z + m_20.m_y;
    }
    else
    {
        m_c.y = m_20.m_y;
        m_c.z = 0;
    }
}

class RHSpritePositionCalls : public RHPositionInterface
{
public:
    SBGeoVector2D FUN_004a4a10();
    void FUN_0055f550();
    bool FUN_00560460();
    bool WithinTargetRadius(float radius, const SBGeoVector2D &delta)
    {
        return delta.FUN_005fc700(1.0f) < radius + m_118 + 10.0f;
    }
    void FUN_00560780(float distance, unsigned short duration);
    bool FUN_00561040(void *, float, unsigned short &, bool);
    bool FUN_00563e90();
    void FUN_00563ea0();
    bool FUN_00563ed0(const SBGeoPoint2D &point);
};

class RHMobilePosition : public RHPositionInterface
{
public:
    void FUN_004abf20(const SBGeoPoint2D &offset);
    void FUN_0055fc20(bool updateDirection);
    void SetFieldD6(int value) { m_d6 = (unsigned short)value; }
};

#endif
