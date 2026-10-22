#include "RHElementObject.h"

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &FUN_005fc250(const SBGeoPoint2D &other);
    float m_x;
    float m_y;
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
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &vector) const;
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &other) const;
    SBGeoBoundingBox2D &operator-=(const SBGeoVector2D &vector);
    bool Unk00608f30() const;
    SBGeoPoint2D m_p0;
    SBGeoPoint2D m_p1;
    bool m_flag;
};

class RHUnkFXSprite
{
public:
    SBGeoBoundingBox2D Unk005bd970();
    char m_00[0x1c];
    SBGeoPoint2D m_1c;
    float m_24;
    float m_28;
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
};

class RHUnk005e6440
{
public:
    void Blit(unsigned long, SBGeoBoundingBox2D *, unsigned long, SBGeoBoundingBox2D *, unsigned long);
};

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
extern float g_unk0x00677488;

class RHElementFX : public RHElement
{
public:
    void InitializeBackgroundRestoration();
    virtual bool Serialize(SBFile &file);
    bool FUN_004aa2f0();
    int FUN_004aa930();
    void Emit(SBFile &file);

    char m_a8[4];                 // +0xa8
    void *m_ac;                   // +0xac
    char m_b0[4];                 // +0xb0
    SBGeoBoundingBox2D m_b4;      // +0xb4; points +0xb4/+0xbc, flag +0xc4
    char m_c8;                    // +0xc8
    char m_c9[3];                 // +0xc9
    unsigned long m_cc;           // +0xcc
    char m_d0;                    // +0xd0
};

#define fx_sprite (*(RHUnkFXSprite **)((char *)this + 0x50))
#define fx_draw (*(RHUnkFXDraw **)((char *)this + 0x60))
#define fx_clip (*(SBGeoBoundingBox2D *)((char *)(*(void **)((char *)this + 0x64)) + 0x3e84))
