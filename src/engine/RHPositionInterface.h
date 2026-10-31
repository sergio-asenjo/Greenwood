#ifndef RHPOSITIONINTERFACE_H
#define RHPOSITIONINTERFACE_H

#include "SB.h"

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoVector2D;

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    float FUN_005fc700(float scale) const;
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};
#endif
#include "SBGeoVector2D.h"
#include "RHMobileUnk00607da0.h"
#include "RHUnk00613e90.h"
class RHElement;
#include <math.h>

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
    bool Unk004fc180(SBFile &file, void *&value);
    bool Unk004fc2d0(SBFile &file, void *&value);
};

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    bool Serialize(SBFile &file);
    void FUN_00607d90();
    void Unk00607dc0(const SBGeoPoint2D &point);
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &offset) const;
    SBGeoPoint2D m_p0;
    SBGeoPoint2D m_p1;
    bool m_flag;
};
#endif

#ifndef RHUNK005FC3B0_VIEW
#define RHUNK005FC3B0_VIEW
class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    bool IsZero() const { return m_x == 0.0f && m_y == 0.0f; }
    void FUN_005fc7c0(float scale);
    unsigned char FUN_005fcc50(float scale) const;
};
#endif

#ifndef RHBONUSINFO_H
class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int value);
};
#endif

struct RHPositionSlope
{
    char m_pad0[0x4c];
    float m_4c;
    float m_50;
    float m_54;
};

class RHPositionInterface
{
public:
    bool Turn();
    bool TurnFast();
    bool TurnSlow(unsigned char delay);
    bool TurnAntiVibration();
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    RHPositionInterface(unsigned long owner);
    ~RHPositionInterface();
    void ComputePositionMap();
    void ComputePositionSprite();
    void ComputePosition3D();
    SBGeoBoundingBox2D &Box() { return *(SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)this)->Unk0055fa10(m_88); }
    void UpdateBox()
    {
        SBGeoVector2D offset(*(SBGeoVector2D *)&m_20);
        ((RHMobileUnk00607da0 *)&m_c0)->FUN_00607da0((const RHMobileUnk00607da0 &)Box().FUN_006090d0(offset));
    }
    static void Floor(float &value) { value = (float)floor(value); }
    static RHUnk00613e90 Scaled(float scale, const RHUnk00613e90 &vector)
    {
        RHUnk00613e90 result;
        result.x = scale * vector.x;
        result.y = scale * vector.y;
        result.z = scale * vector.z;
        return result;
    }
    static RHUnk00613e90 Divided(const RHUnk00613e90 &vector, float divisor)
    {
        float inverse = 1.0f / divisor;
        RHUnk00613e90 result;
        result.x = vector.x * inverse;
        result.y = vector.y * inverse;
        result.z = vector.z * inverse;
        return result;
    }
    static void SetVector(RHUnk00613e90 &vector, float x, float y, float z)
    {
        vector.x = x;
        vector.y = y;
        vector.z = z;
    }
    static void SetPoint(SBGeoPoint2D &point, float x, float y)
    {
        point.m_x = x;
        point.m_y = y;
    }
    bool Is3DValid() const { return m_4 & 1; }
    bool IsMapValid() const { return (m_4 >> 1) & 1; }
    bool IsSpriteValid() const { return (m_4 >> 2) & 1; }
    void MapFrom3D()
    {
        SetPoint(m_20, m_c.x, m_c.y - m_c.z);
        UpdateBox();
    }
    void SpriteFromMap()
    {
        m_18 = m_20.FUN_005fc200(m_80);
        Floor(m_18.m_x);
        Floor(m_18.m_y);
    }
    bool IncrementMapValid() const { return m_8 & 1; }
    bool Increment3DValid() const { return (m_8 >> 1) & 1; }
    void SetHeading(unsigned short heading) { m_d6 = heading & 15; }
    void Increment3DFromMap()
    {
        m_60.x = m_6c.m_x;
        if (m_ec)
        {
            m_60.z = (m_ec->m_4c * m_6c.m_x + m_ec->m_50 * m_6c.m_y) / (1.0f - m_ec->m_50);
            m_60.y = m_60.z + m_6c.m_y;
        }
        else
        {
            m_60.y = m_6c.m_y;
            m_60.z = 0;
        }
    }
    void Position3DFromMap()
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

    unsigned long m_0; // +0x00
    unsigned m_4; // +0x04
    unsigned m_8; // +0x08
    RHUnk00613e90 m_c; // +0x0c
    SBGeoPoint2D m_18; // +0x18
    SBGeoPoint2D m_20; // +0x20
    RHUnk00613e90 m_28; // +0x28
    SBGeoPoint2D m_34; // +0x34
    SBGeoPoint2D m_3c; // +0x3c
    SBGeoPoint2D m_44; // +0x44
    SBGeoPoint2D m_4c; // +0x4c
    RHUnk00613e90 m_54; // +0x54
    RHUnk00613e90 m_60; // +0x60
    SBGeoVector2D m_6c; // +0x6c
    char m_74; // +0x74
    char m_pad75[3];
    int m_78; // +0x78
    char m_7c; // +0x7c
    char m_pad7d[3];
    SBGeoVector2D m_80; // +0x80
    int m_88; // +0x88
    int m_8c; // +0x8c
    unsigned short m_90; // +0x90
    unsigned short m_92; // +0x92
    SBGeoBoundingBox2D m_94; // +0x94
    SBGeoBoundingBox2D m_a8; // +0xa8
    char m_bc; // +0xbc
    char m_padbd[3];
    SBGeoBoundingBox2D m_c0; // +0xc0
    unsigned short m_d4; // +0xd4
    unsigned short m_d6; // +0xd6
    char m_d8; // +0xd8
    char m_d9; // +0xd9
    unsigned short m_da; // +0xda
    void *m_dc; // +0xdc
    unsigned short m_e0; // +0xe0
    char m_pade2[2];
    void *m_e4; // +0xe4
    void *m_e8; // +0xe8
    RHPositionSlope *m_ec; // +0xec
    void *m_f0; // +0xf0
    char m_f4; // +0xf4
    char m_padf5[3];
    int m_f8; // +0xf8
    char m_fc; // +0xfc
    char m_fd; // +0xfd
    char m_fe; // +0xfe
    char m_padff;
    unsigned short m_100; // +0x100
    char m_pad102[2];
    SBGeoBoundingBox2D m_104; // +0x104
    float m_118; // +0x118
    float m_11c; // +0x11c
    RHElement *m_120; // +0x120
    char m_124; // +0x124
    char m_pad125[3];
    SBGeoVector2D m_128; // +0x128
    int m_130; // +0x130
    RHUnk00613e90 m_134; // +0x134
};

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
};

#endif
