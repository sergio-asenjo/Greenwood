#include <stdio.h>
#include "RHLoadingScreen.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x18)
DECOMP_SIZE_ASSERT(RHUnkFXDraw, 0x10e)
DECOMP_SIZE_ASSERT(RHUnk006114c0, 0x38)
DECOMP_SIZE_ASSERT(RHMissionProfile, 0x14)
DECOMP_SIZE_ASSERT(RHLoadingScreen, 0x24)

// STRING: GAME 0x006b0764
#define g_loadingFile "P:\\Robin Hood\\RHloadingscreen.cpp"
// STRING: GAME 0x006b0788
#define g_loadingDepth "Unsupported bit depth for loading screen !"
// STRING: GAME 0x006b07b4
#define g_loadingPicture "Unable to load picture from pak file"
// STRING: GAME 0x006b07ec
#define g_loadingSandDepth "Invalid surface depth !"
// STRING: GAME 0x006b0810
#define g_loadingPathFile "P:\\Robin Hood\\RHloadingscreen.cpp"
// STRING: GAME 0x006b0834
#define g_loadingPathError "Loading screen : Unable to find a loading screen data file."
// STRING: GAME 0x006b0870
#define g_loadingDefault "\\Loading.pak"
// STRING: GAME 0x006b0880
#define g_loadingExtension ".pak"
// STRING: GAME 0x006b0888
#define g_loadingFormat "%02i"
#define g_loadingSeparator "\\"

// GLOBAL: GAME 0x006c0bd4
unsigned char *g_unk0x006c0bd4;
// GLOBAL: GAME 0x00679148
float g_unk0x00679148 = 255.0f;
// GLOBAL: GAME 0x006c05f0
std::string g_unk0x006c05f0;
// GLOBAL: GAME 0x006c0650
std::string g_unk0x006c0650;

class RHUnk005223e0
{
public:
    RHUnk005223e0 *FUN_005229a0();
    void FUN_005223e0();
    void FUN_005229e0();
};

struct RHUnk005223a0Source
{
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
};

class RHUnk005223a0
{
public:
    RHUnk005223a0(const RHUnk005223a0Source &source, short value);
};

// FUNCTION: GAME 0x005223a0
RHUnk005223a0::RHUnk005223a0(const RHUnk005223a0Source &source, short value)
{
    *(unsigned *)this = 0x679138;
    *(RHUnk005223a0Source *)((char *)this + 4) = source;
    *(short *)((char *)this + 0x14) = value;
    *(int *)((char *)this + 0x18) = 0;
}

// FUNCTION: GAME 0x005223e0
void RHUnk005223e0::FUN_005223e0()
{
    *(unsigned *)this = 0x679138;
}

class RHUnk005224c0
{
public:
    ~RHUnk005224c0();
    void FUN_00520a70();
};

// FUNCTION: GAME 0x005224c0
RHUnk005224c0::~RHUnk005224c0()
{
    *(unsigned *)this = 0x67913c;
    FUN_00520a70();
}

void RHUnk005224c0::FUN_00520a70() {}

// FUNCTION: GAME 0x005229a0
RHUnk005223e0 *RHUnk005223e0::FUN_005229a0()
{
    int zero = 0;
    *(int *)((char *)this + 0xc) = zero;
    *(int *)((char *)this + 0x10) = zero;
    *(int *)((char *)this + 0x14) = zero;
    *(int *)((char *)this + 0x1c) = zero;
    *(int *)((char *)this + 0x20) = zero;
    *(unsigned *)this = 0x679144;
    g_unk0x006c0bd4 = (unsigned char *)zero;
    return this;
}

// FUNCTION: GAME 0x005229e0
void RHUnk005223e0::FUN_005229e0()
{
    *(unsigned *)this = 0x679144;
}

void EmitRHUnk005223e0(RHUnk005223e0 *a)
{
    a->FUN_005223e0();
    a->FUN_005229a0();
    a->FUN_005229e0();
}

// FUNCTION: GAME 0x005229f0
unsigned long RHLoadingScreen::CreateSurfaceForPicture(SBFile &file)
{
    RHUnk006114c0 picture;
    if (!picture.Unk00611710(file))
    {
        SBAssert(0, g_loadingFile, 0x48, g_loadingPicture);
        return -1;
    }
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
    // Reuse the shared int-parameter stub with the target's narrow-argument ABI.
    unsigned long surface = (m_draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))((unsigned short)m_width, (unsigned short)m_height, 0, false);
    switch (m_draw->UnkField10c())
    {
    case 15:
        picture.Unk00611e10(2, 0);
        break;
    case 16:
        picture.Unk00611e10(3, 0);
        break;
    default:
        SBAssert(0, g_loadingFile, 0x5a, g_loadingDepth);
        return -1;
    }
    unsigned long width = picture.UnkField20();
    unsigned long height = picture.UnkField22();
    if (width <= m_width && height <= m_height)
        picture.Unk00613530(m_draw, surface);
    else
    {
        unsigned long x = (width - m_width + 1) / 2;
        unsigned long y = (height - m_height + 1) / 2;
        RHUnk006114c0 *cropped = picture.Unk00612ad0(SBGeoPoint2D((float)x, (float)y), SBGeoVector2D((float)m_width, (float)m_height));
        cropped->Unk20(m_draw, surface);
        delete cropped;
    }
    return surface;
}

// FUNCTION: GAME 0x00522e40
void RHLoadingScreen::GenerateSand(SBFile &file)
{
    RHUnk00613e90 viewport;
    unsigned long surface = CreateSurfaceForPicture(file);
    g_unk0x006c0bd4 = new unsigned char[m_width * m_height];
    if (!m_draw->Unk005e5a00(surface, viewport, 0))
        return;
    unsigned long depth = viewport.UnkDepth();
    unsigned long skip = (viewport.UnkPitch() >> 1) - viewport.UnkWidth();
    unsigned short *pixels = viewport.UnkData();
    unsigned char *sand = g_unk0x006c0bd4;
    unsigned long maximum = 0;
    unsigned long minimum = 256;
    unsigned long x;
    unsigned long y;
    switch (depth)
    {
    case 15:
    {
        for (y = 0; y < m_height; ++y)
        {
            for (x = 0; x < m_width; ++x)
            {
                unsigned long pixel = *pixels;
                unsigned long red = (pixel >> 7) & 248;
                unsigned long green = (pixel >> 2) & 248;
                unsigned long blue = (pixel & 31) << 3;
                unsigned long value = (red * 39 + green * 50 + blue * 11) / 100;
                if (value > maximum)
                    maximum = value;
                if (value < minimum)
                    minimum = value;
                *sand++ = (unsigned char)value;
                ++pixels;
            }
            pixels += skip;
        }
        break;
    }
    case 16:
    {
        for (y = 0; y < m_height; ++y)
        {
            for (x = 0; x < m_width; ++x)
            {
                unsigned long pixel = *pixels;
                unsigned long red = (pixel >> 8) & 248;
                unsigned long green = (pixel >> 3) & 252;
                unsigned long blue = (pixel & 31) << 3;
                unsigned long value = (red * 39 + green * 50 + blue * 11) / 100;
                if (value > maximum)
                    maximum = value;
                if (value < minimum)
                    minimum = value;
                *sand++ = (unsigned char)value;
                ++pixels;
            }
            pixels += skip;
        }
        break;
    }
    default:
        SBAssert(1, g_loadingFile, 0x136, g_loadingSandDepth);
        break;
    }
    m_draw->Unk005e5ea0(viewport);
    m_draw->Unk005e5160(surface);
    float scale = g_unk0x00679148 / (maximum - minimum);
    sand = g_unk0x006c0bd4;
    m_height *= m_width;
    for (unsigned long i = 0; i < m_height; ++i)
    {
        *sand = (unsigned char)((*sand - minimum) * scale);
        ++sand;
    }
}

// FUNCTION: GAME 0x005236a0
std::string RHLoadingScreen::GetDataFile(const RHMission *mission, unsigned long number)
{
    std::string path;
    char buffer[512];
    sprintf(buffer, g_loadingFormat, number);
    path = g_unk0x006c05f0;
    path += g_loadingSeparator;
    path += buffer;
    path += g_loadingSeparator;
    path += mission->m_profile->m_name;
    path += g_loadingExtension;
    if (!FUN_005f6400(path))
    {
        path = g_unk0x006c0650;
        path += g_loadingDefault;
        if (!FUN_005f6400(path))
            SBAssert(1, g_loadingPathFile, 0x328, g_loadingPathError);
    }
    return path;
}

// LIBRARY: GAME 0x005239b0
// ?append@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z

void RHLoadingScreen::Emit(SBFile &file, const RHMission *mission)
{
    CreateSurfaceForPicture(file);
    GenerateSand(file);
    GetDataFile(mission, 0);
}
