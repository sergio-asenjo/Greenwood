#ifndef RHELEMENTBONUS_H
#define RHELEMENTBONUS_H

#include "SB.h"

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    float m_x; // +0x00
    float m_y; // +0x04
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

class SBGeoBoundingBox2D
{
public:
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D operator+(const SBGeoVector2D &vector) const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_p0; // +0x00
    SBGeoPoint2D m_p1; // +0x08
    bool m_flag; // +0x10
};

#ifndef RHMOBILEUNK00607DA0_VIEW
#define RHMOBILEUNK00607DA0_VIEW
// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14]; // 0x00
};
#endif

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int value);
};

struct RHBonusProjection
{
    unsigned m_0; // +0x00
    unsigned short Flags() const { return (unsigned short)(m_0 >> 2); }
    bool Inside(const SBGeoPoint2D &point) const { return m_38.FUN_00608400(point); }
    char m_pad4[0x34];
    SBGeoBoundingBox2D m_38; // +0x38
};

struct RHBonusTriple
{
    float m_0; // +0x00
    float m_4; // +0x04
    float m_8; // +0x08
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
            ((RHMobileUnk00607da0 *)&m_c0)->FUN_00607da0((const RHMobileUnk00607da0 &)(Box() + vector));
        }
        m_4 = 2;
    }
    void SetFlags(unsigned value)
    {
        m_d4 = value;
        m_d6 = value;
    }
    unsigned m_0; // +0x00
    unsigned m_4; // +0x04
    char m_pad8[4];
    RHBonusTriple m_c; // +0x0c
    char m_pad18[8];
    SBGeoPoint2D m_20; // +0x20
    RHBonusTriple m_28; // +0x28
    char m_pad34[8];
    SBGeoPoint2D m_3c; // +0x3c
    char m_pad44[0x44];
    int m_88; // +0x88
    char m_pad8c[0x34];
    SBGeoBoundingBox2D m_c0; // +0xc0
    unsigned short m_d4; // +0xd4
    unsigned short m_d6; // +0xd6
    unsigned short m_d8; // +0xd8
    unsigned short m_da; // +0xda
};

class RHBonusInfo
{
public:
    short X() const { return (short)m_4.m_20.m_x; }
    short Y() const { return (short)m_4.m_20.m_y; }
    void RestorePoint() { m_4.m_3c = m_4.m_20; }
    void FUN_005bd560(void *value, bool flag);
    unsigned m_0; // +0x00
    RHBonusInfoBase m_4; // +0x04
    void *m_e0; // +0xe0
};

struct RHBonusGlobalView
{
    char m_pad0[0x4064];
    void **m_4064; // +0x4064
    char m_pad4068[0xdc];
    RHBonusProjection **m_4144; // +0x4144
    char m_pad4148[0x3c];
    void *m_4184; // +0x4184
};

struct RHUnkSectorGlobal;
class RHEngine;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
extern RHEngine *g_pEngine;

struct RHBonusEngineView
{
    char m_pad0[0x4aa8];
    bool m_4aa8; // +0x4aa8
    bool Flag() const { return m_4aa8; }
};

class RHElementBonus
{
public:
    enum BonusType { BONUS_UNKNOWN = 0 };
    RHElementBonus(BonusType type, bool flag, unsigned short quantity);
    ~RHElementBonus();
    void ApplyProjection(RHBonusProjection *projection);
    static RHElementBonus *CreateBonusFromMissionStream(SBFile &file);
    char m_pad0[0x50];
    RHBonusInfo *m_50; // +0x50
    char m_pad54[0xac]; // allocation size 0x100
};

#endif
