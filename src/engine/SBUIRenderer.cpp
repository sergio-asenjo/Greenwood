#include "SBNullstr.h"
#include "SBUIRenderer.h"
#include "SBUIRendererListbox.h"
#include "SB.h"

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
// SIZE 0x08
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &) const;
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &) const;
    float m_x; // 0x00
    float m_y; // 0x04
};
#endif

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
};

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    ~RHUnk005fc3b0() {}
};

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#define SBGEO_BOUNDINGBOX2D_VIEW
// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &);
    bool Unk00608f30() const;
    void SetEnd(const SBGeoPoint2D &point) { m_flag = true; m_p1 = point; }
    SBGeoPoint2D m_p0; // 0x00
    SBGeoPoint2D m_p1; // 0x08
    bool m_flag; // 0x10
};
#endif

// SIZE 0x14
class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &);
    undefined m_00[0x14]; // 0x00
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class SBResourceManager
{
public:
    bool GetSurfaceForResource(long, unsigned int, unsigned int &);
    bool FUN_00600920(unsigned long, unsigned long, unsigned long &);
};

#ifndef RHUNK00600820_VIEW
#define RHUNK00600820_VIEW
class RHUnk00600820
{
public:
    bool ResolveSurface(void *surface, unsigned int id, float *value);
};
#endif

class SBDrawManager
{
public:
    void BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned long);
};

#include "RHUnk005cbb80.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHPortraitRenderer0060d470, 0x4c)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHMobileUnk006091b0, 0x14)
DECOMP_SIZE_ASSERT(SBUIUnk0060d530, 0x3c)
DECOMP_SIZE_ASSERT(SBUIUnk0060da20, 0x4c)
DECOMP_SIZE_ASSERT(SBUIUnk0060dae0, 0x50)
DECOMP_SIZE_ASSERT(SBUIUnk0060dd00, 0x7c)

class RHMapResources;
extern RHMapResources *g_unk0x006c1840;

#define m_resource (*(SBResourceManager **)(m_bytes + 0x04))
#define m_box (*(SBGeoBoundingBox2D *)(m_bytes + 0x08))
#define m_draw (*(SBDrawManager **)(m_bytes + 0x1c))
#define m_unk20 (*(unsigned long *)(m_bytes + 0x20))
#define m_resourceId (*(long *)(m_bytes + 0x38))

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnk005e6440
{
public:
    void Blit(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned long);
};

// FUNCTION: GAME 0x0060d420
RHPortraitRenderer0060d470::RHPortraitRenderer0060d470()
{
    m_widgetResource = -1;
    m_3c = 0;
    RHMapResources *resources = g_unk0x006c1840;
    m_drawManager = 0;
    m_40 = 0;
    m_44 = 0;
    m_48 = 0;
    m_resources = resources;
}

// FUNCTION: GAME 0x0060d470
RHPortraitRenderer0060d470::~RHPortraitRenderer0060d470()
{
}

// FUNCTION: GAME 0x0060d500
unsigned int SBUIUnk0060d530::FUN_0060d500(unsigned int id)
{
    ((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&id);
    return id;
}

// FUNCTION: GAME 0x0060d520
void SBUIUnk0060d530::FUN_0060d520()
{
    ((SBUIUnk005fd4a0 *)m_resource)->FUN_005fd4a0(m_resourceId);
}

// FUNCTION: GAME 0x0060d530
void SBUIUnk0060d530::FUN_0060d530(unsigned int surface)
{
    *(RHUnk005ef320 **)(m_bytes + 0x1c) = g_unk0x6c11d0;
    *(unsigned int *)(m_bytes + 0x20) = surface;
}

// STUB: GAME 0x0060d550
bool SBUIUnk0060d530::FUN_0060d550(long resourceId)
{
    RHUnk005fc3b0 size;
    m_resourceId = resourceId;
    SBGeoBoundingBox2D &position = m_box;
    if (!position.Unk00608f30())
        return false;
    if (m_resourceId != -1)
    {
        if (!((SBUIUnk006006f0 *)m_resource)->FUN_006006f0(m_resourceId, size))
        {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0x78,
                "Unable to retrieve the size of a resource");
            return false;
        }
        if (((volatile SBGeoBoundingBox2D &)position).m_p1.m_x - ((volatile SBGeoBoundingBox2D &)position).m_p0.m_x == 0.0f
            || position.m_p1.m_x - position.m_p0.m_x != size.m_x)
            position.SetEnd(position.m_p0.Unk005fc190(size));
    }
    return true;
}

// FUNCTION: GAME 0x0060d690
void *SBUIUnk0060d530::FUN_0060d690()
{
    return m_bytes + 8;
}

// STUB: GAME 0x0060d6a0
void SBUIUnk0060d530::FUN_0060d6a0(const SBGeoBoundingBox2D &box)
{
    RHUnk005fc3b0 size;
    SBGeoBoundingBox2D &position = m_box;
    ((RHMobileUnk00607da0 *)&position)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
    if (position.m_p1.m_x - position.m_p0.m_x == 0.0f && m_resourceId != -1)
    {
        if (!((SBUIUnk006006f0 *)m_resource)->FUN_006006f0(m_resourceId, size))
        {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0xac,
                // STRING: GAME 0x006bb580
                "Unable to retrieve the size of a resource");
        }
        else
        {
            SBGeoPoint2D endpoint = (*(SBGeoPoint2D *)(m_bytes + 0x10)).Unk005fc190(size);
            position.m_flag = true;
            *(SBGeoPoint2D *)(m_bytes + 0x10) = endpoint;
        }
    }
}

// FUNCTION: GAME 0x0060d780
void SBUIUnk0060d530::FUN_0060d780(const SBGeoPoint2D &point)
{
    RHUnk005fc3b0 size;
    SBGeoBoundingBox2D &position = m_box;
    ((RHMobileUnk006091b0 *)&position)->FUN_006091b0(point.Unk005fc110(position.m_p0));
    if ((!position.Unk00608f30() || position.m_p1.m_x - position.m_p0.m_x == 0.0f)
        && m_resourceId != -1)
    {
        if (!((SBUIUnk006006f0 *)m_resource)->FUN_006006f0(m_resourceId, size))
        {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0xbf,
                "Unable to retrieve the size of a resource");
        }
        else
        {
            position.SetEnd((*(SBGeoPoint2D *)(m_bytes + 0x10)).Unk005fc190(size));
        }
    }
}

#include "RHGameWidgetRendererCalls.h"

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    unsigned char m_00[0x18];
};

#include "SBDrawViewport.h"

class RHUnkFXDraw
{
public:
    bool Unk005e5a00(unsigned long surface, RHUnk00613e90 &view, unsigned long flags);
    void Unk005e5ea0(RHUnk00613e90 &view);
};

#include "SBDrawUnk005e5ec0.h"

// Parked: the target spills point.m_x through an integer move into the dead argument slot.
// STUB: GAME 0x0060d890
bool RHGameWidgetRendererCalls::FUN_0060d890(const SBGeoPoint2D &point)
{
    RHUnk00613e90 view;
    unsigned long surface;
    char *self = (char *)this;
    if (*(long *)(self + 0x3c) > 0)
        (*(RHUnk00600820 **)(self + 4))->ResolveSurface((void *)*(long *)(self + 0x38), *(long *)(self + 0x3c), (float *)&surface);
    else
        (*(SBResourceManager **)(self + 4))->FUN_00600920(*(long *)(self + 0x38), 0, surface);
    if ((surface
            || ((*(SBResourceManager **)(self + 4))->FUN_00600920(*(long *)(self + 0x38), 1, surface), surface)
            || ((*(SBResourceManager **)(self + 4))->FUN_00600920(*(long *)(self + 0x38), 2, surface), surface)
            || ((*(SBResourceManager **)(self + 4))->FUN_00600920(*(long *)(self + 0x38), 3, surface), surface))
        && (*(RHUnkFXDraw **)(self + 0x1c))->Unk005e5a00(surface, view, 0))
    {
        unsigned short pixel = ((SBDrawViewport *)&view)->GetPixel((unsigned short)point.m_x, (unsigned short)point.m_y);
        (*(RHUnkFXDraw **)(self + 0x1c))->Unk005e5ea0(view);
        if (pixel != (*(SBDrawUnk005e5ec0 **)(self + 0x1c))->FUN_005e5f60(surface))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0060da20
bool SBUIUnk0060da20::FUN_0060da20(unsigned int id)
{
    *(unsigned int *)(m_bytes + 0x3c) = id;
    if (id == 0xff)
    {
        ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = 0;
        return false;
    }
    unsigned int surface;
    if (((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&surface) != true)
    {
        SBAssert(0,
            // STRING: GAME 0x006bb558
            "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0x13e,
            "Unable to retrieve a resource for the bitmap renderer");
        return false;
    }
    ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = surface;
    if (surface)
        ((RHUnk005e6440 *)m_draw)->Blit(surface, 0, m_unk20, &m_box, 1);
    return true;
}

// FUNCTION: GAME 0x0060dae0
bool SBUIUnk0060dae0::FUN_0060dae0(unsigned int id)
{
    *(unsigned int *)(m_bytes + 0x3c) = id;
    if (id != 0xff && m_resourceId != -1)
    {
        unsigned int surface;
        if (((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&surface) != true)
        {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0x173,
                "Unable to retrieve a resource for the bitmap renderer");
            return false;
        }
        ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = surface;
        if (surface)
            m_draw->BlitAlphaKeying(surface, 0, m_unk20, &m_box,
                *(unsigned short *)(m_bytes + 0x4c), *(unsigned short *)(m_bytes + 0x4e), 1);
        return true;
    }
    ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = 0;
    return false;
}

// FUNCTION: GAME 0x0060db80
unsigned int SBUIUnk0060dae0::FUN_0060db80(unsigned int id)
{
    ((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&id);
    if (((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] != id)
        id = -1;
    return id;
}

// FUNCTION: GAME 0x0060dc20
int SBUIUnk0060dd00::FUN_0060dc20(unsigned int id)
{
    int result = 0;
    if (m_bytes[0x78] == 1)
        return -1;
    unsigned int index = id;
    unsigned int value;
    switch (index) {
    case 0: value = *(unsigned int *)(m_bytes + 0x54); break;
    case 1: value = *(unsigned int *)(m_bytes + 0x50); break;
    case 2: value = *(unsigned int *)(m_bytes + 0x58); break;
    case 3: value = *(unsigned int *)(m_bytes + 0x5c); break;
    }
    if (value)
        result = index + 1;
    return result;
}

// FUNCTION: GAME 0x0060dcd0
int SBUIUnk0060dd00::FUN_0060dcd0()
{
    if (*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50)) {
        int value = FUN_0060dda0(*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50), true);
        return (*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50))->FUN_0061e890() * value;
    }
    return 0;
}

// FUNCTION: GAME 0x0060dd00
void *SBUIUnk0060dd00::FUN_0060dd00()
{
    return m_bytes + 0x68;
}

// FUNCTION: GAME 0x0060e0d0
bool SBUIUnk0060dd00::FUN_0060e0d0(void *first, void *second, void *third, void *fourth)
{
    *(void **)(m_bytes + 0x54) = first;
    *(void **)(m_bytes + 0x50) = second;
    *(void **)(m_bytes + 0x58) = third;
    *(void **)(m_bytes + 0x5c) = fourth;
    return true;
}

void RHPortraitRenderer0060d470::FUN_0060d530(unsigned int) {}

void EmitSBUIRenderer(SBUIUnk0060da20 *bitmap, SBUIUnk0060dae0 *alpha,
    SBUIUnk0060d530 *base, SBUIUnk0060dd00 *text)
{
    base->FUN_0060d500(0);
    base->FUN_0060d520();
    base->FUN_0060d530(0);
    base->FUN_0060d550(0);
    base->FUN_0060d690();
    base->FUN_0060d6a0(*(SBGeoBoundingBox2D *)base);
    base->FUN_0060d780(*(SBGeoPoint2D *)base);
    bitmap->FUN_0060da20(0);
    ((RHPortraitRenderer0060d470 *)bitmap)->RHPortraitRenderer0060d470::RHPortraitRenderer0060d470();
    alpha->FUN_0060dae0(0);
    alpha->FUN_0060db80(0);
    text->FUN_0060dc20(0);
    text->FUN_0060dcd0();
    text->FUN_0060dd00();
    text->FUN_0060e0d0(0, 0, 0, 0);
}
