#ifndef RHELEMENTFX_H
#define RHELEMENTFX_H

#include "RHElementObject.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHSpriteCore.h"
#include "sbgeo_00610600.h"

#include "SBDrawManagerCore.h"

#include "RHFastFindGridCore.h"

class RHUnkFXEngine
{
public:
    char m_00[0x48c4];
    unsigned long m_48c4;
};

class RHEngine;
class RHFastFindGrid;
extern RHEngine *g_pEngine;
extern RHFastFindGrid *g_unk0x6c0a9c;

#include "RHElementFXCore.h"

#define fx_sprite (*(RHSprite **)((char *)this + 0x50))
#define fx_draw (*(SBDrawManager **)((char *)this + 0x60))
#define fx_clip (*(SBGeoBoundingBox2D *)((char *)(*(void **)((char *)this + 0x64)) + 0x3e84))

#endif
