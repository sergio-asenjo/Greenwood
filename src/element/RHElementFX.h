#ifndef RHELEMENTFX_H
#define RHELEMENTFX_H

#include "RHElementObject.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHSpriteCore.h"
#include "sbgeo_00610600.h"

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(unsigned short, unsigned short, unsigned long, bool);
};

#include "SBDrawManagerCore.h"

class RHFastFindGrid
{
public:
    bool Unk004efbb0(SBFile &, void **);
};

class RHUnkFXEngine
{
public:
    char m_00[0x48c4];
    unsigned long m_48c4;
};

class RHEngine;
struct RHUnkSectorGlobal;
extern RHEngine *g_pEngine;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class RHElementFX : public RHElement
{
public:
    void RestoreBackground();
    void InitializeBackgroundRestoration();
    void InitializeFromProtoStream(SBFile &file);
    bool IsElementBehind(RHElement *element);
    virtual bool Serialize(SBFile &file);
    bool FUN_004aa2f0();
    int FUN_004aa930();
    void Emit(SBFile &file);

    int m_a8;
    void *m_ac;                   // +0xac
    char m_b0[4];                 // +0xb0
    SBGeoBoundingBox2D m_b4;      // +0xb4; points +0xb4/+0xbc, flag +0xc4
    char m_c8;                    // +0xc8
    char m_c9[3];                 // +0xc9
    unsigned long m_cc;           // +0xcc
    char m_d0;                    // +0xd0
    char m_d1[3];
    RHUnkTargetPoints m_d4;
    float m_f8;
};

#define fx_sprite (*(RHSprite **)((char *)this + 0x50))
#define fx_draw (*(RHUnkFXDraw **)((char *)this + 0x60))
#define fx_clip (*(SBGeoBoundingBox2D *)((char *)(*(void **)((char *)this + 0x64)) + 0x3e84))

#endif
