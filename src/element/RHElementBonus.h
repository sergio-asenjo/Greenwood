#ifndef RHELEMENTBONUS_H
#define RHELEMENTBONUS_H

#include "SB.h"
#include "RHElementBonusCore.h"

#ifndef RHSPRITE_H
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
    float FUN_005fc700(float scale) const;
    float Unk005fc6d0(float scale) const;
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &other);
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};
#define SBGEO_POINT2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

#define RHBONUSINFO_VECTOR_DEFINED
#include "RHBonusInfo.h"
#undef RHBONUSINFO_VECTOR_DEFINED

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

#endif
