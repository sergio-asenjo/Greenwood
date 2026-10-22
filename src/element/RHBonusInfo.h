#ifndef RHBONUSINFO_H
#define RHBONUSINFO_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#if !defined(SBGEOVECTOR2D_H) && !defined(RHBONUSINFO_VECTOR_DEFINED)
#include "SBGeoVector2D.h"
#endif
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

#ifndef RHMOBILEUNK00607DA0_VIEW
#define RHMOBILEUNK00607DA0_VIEW
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14];
};
#endif

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int value);
};

struct RHBonusProjection
{
    unsigned m_0;
    unsigned short Flags() const { return (unsigned short)(m_0 >> 2); }
    bool Inside(const SBGeoPoint2D &point) const { return m_38.FUN_00608400(point); }
    char m_pad4[0x34];
    SBGeoBoundingBox2D m_38;
};

struct RHBonusTriple
{
    float m_0;
    float m_4;
    float m_8;
};

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
    SBGeoBoundingBox2D &Box()
    {
        return *(SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)this)->Unk0055fa10(m_88);
    }
    void SetPoint(const SBGeoPoint2D &point)
    {
        m_20 = point;
        {
            SBGeoVector2D vector(*(SBGeoVector2D *)&point);
            ((RHMobileUnk00607da0 *)&m_c0)->FUN_00607da0((const RHMobileUnk00607da0 &)Box().FUN_006090d0(vector));
        }
        m_4 = 2;
    }
    void SetFlags(unsigned value)
    {
        m_d4 = value;
        m_d6 = value;
    }
    unsigned m_0;
    unsigned m_4;
    char m_pad8[4];
    RHBonusTriple m_c;
    char m_pad18[8];
    SBGeoPoint2D m_20;
    RHBonusTriple m_28;
    char m_pad34[8];
    SBGeoPoint2D m_3c;
    char m_pad44[0x44];
    int m_88;
    char m_pad8c[0x34];
    SBGeoBoundingBox2D m_c0;
    unsigned short m_d4;
    unsigned short m_d6;
    unsigned short m_d8;
    unsigned short m_da;
};

class RHBonusInfo
{
public:
    short X() const { return (short)m_4.m_20.m_x; }
    short Y() const { return (short)m_4.m_20.m_y; }
    void RestorePoint() { m_4.m_3c = m_4.m_20; }
    void FUN_005bd560(void *value, bool flag);
    unsigned m_0;
    RHBonusInfoBase m_4;
    void *m_e0;
};

#endif
