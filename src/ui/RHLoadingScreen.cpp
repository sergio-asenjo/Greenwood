#include "SBNullstr.h"
#include <stdio.h>
#include "RHLoadingScreen.h"
#include "SBPicture.h"
#include "SBUIBase.h"
#include "SBUIUnkSurface.h"
#include "RHFontManager.h"
#include "SBFont.h"
#include "RHUnk005f4fc0.h"
#include "SBUIRendererInputField.h"
#include "RHMapResources.h"
#include "ToolboxWideString.h"
#include "launcher.h"

extern unsigned char g_unk0x006a6d27;
extern RHMapResources *g_unk0x006c1840;
extern RHUnk00408f50 g_unk0x006c0580;
void FUN_005e1380();
void FUN_005e1400();

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBDrawViewport, 0x18)
DECOMP_SIZE_ASSERT(SBDrawManager, 0x150)
DECOMP_SIZE_ASSERT(RHUnk006114c0, 0x38)
DECOMP_SIZE_ASSERT(RHMissionProfile, 0x14)
DECOMP_SIZE_ASSERT(RHLoadingScreen, 0x30)
DECOMP_SIZE_ASSERT(SBUIUnkSurface, 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_duration) == 0x04)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_elapsed) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_font) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_versionFont) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_context) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_draw) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_width) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_height) == 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_picture) == 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_sandPicture) == 0x28)
DECOMP_STATIC_ASSERT(offsetof(RHLoadingScreen, m_status) == 0x2c)

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
// STRING: GAME 0x006b07e4
#define g_loadingFont "Loading"
// STRING: GAME 0x006b07dc
#define g_loadingVersionFont "Version"
// STRING: GAME 0x006b0804
#define g_loadingVersionFormat "v%d.%d %s"

// GLOBAL: GAME 0x006c0bd4
unsigned char *g_unk0x006c0bd4;
// GLOBAL: GAME 0x006c05f0
std::string g_unk0x006c05f0;
// GLOBAL: GAME 0x006c0650
std::string g_unk0x006c0650;

class RHUnk005223e0
{
public:
    void *FUN_005229c0(unsigned flags);
    void *FUN_00522380(unsigned flags);
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

// FUNCTION: GAME 0x00522380
void *RHUnk005223e0::FUN_00522380(unsigned flags)
{
    FUN_005223e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005223e0
void RHUnk005223e0::FUN_005223e0()
{
    *(unsigned *)this = 0x679138;
}

class RHUnk005209d0
{
public:
    virtual ~RHUnk005209d0();
};

class RHUnk005224c0
{
public:
    void *FUN_005224a0(unsigned flags);
    ~RHUnk005224c0();
};

// FUNCTION: GAME 0x005224a0
void *RHUnk005224c0::FUN_005224a0(unsigned flags)
{
    this->~RHUnk005224c0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005224c0
RHUnk005224c0::~RHUnk005224c0()
{
    *(unsigned *)this = 0x67913c;
    ((RHUnk005209d0 *)this)->RHUnk005209d0::~RHUnk005209d0();
}

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

// FUNCTION: GAME 0x005229c0
void *RHUnk005223e0::FUN_005229c0(unsigned flags)
{
    FUN_005229e0();
    if (flags & 1)
        operator delete(this);
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
    unsigned long surface = m_draw->Unk005e4ed0((unsigned short)m_width, (unsigned short)m_height, 0, false);
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
        ((SBPicture *)&picture)->SBPicture::Unk00613530(m_draw, surface);
    else
    {
        unsigned long x = (width - m_width + 1) / 2;
        unsigned long y = (height - m_height + 1) / 2;
        SBPicture *cropped = ((SBPicture *)&picture)->Unk00612ad0(SBGeoPoint2D((float)x, (float)y), SBGeoVector2D((float)m_width, (float)m_height));
        cropped->Unk00613530(m_draw, surface);
        if (cropped)
            cropped->FUN_00611be0(1);
    }
    return surface;
}

// FUNCTION: GAME 0x00522bd0
bool RHLoadingScreen::Initialize(const RHMission *mission, unsigned long number, float duration)
{
    RHUnk005f4fc0 file;
    m_duration = duration;
    m_elapsed = 0;
    m_draw = g_unk0x6c11d0;
    m_width = m_draw->FUN_005e56c0(0);
    m_height = m_draw->FUN_005e5750(0);
    m_draw->FUN_005e61e0(0, 0, 0, 0);
    m_draw->FUN_005e5260();
    m_context = new SBUIUnkSurface(0);
    m_font = RHFontManager::FUN_005024f0()->GetFont(std::string(g_loadingFont));
    m_versionFont = RHFontManager::FUN_005024f0()->GetFont(std::string(g_loadingVersionFont));
    m_font->AttachToRenderContext(m_context, false);
    m_versionFont->AttachToRenderContext(m_context, false);
    file.FUN_005f5090(GetDataFile(mission, number), 1);
    m_picture = CreateSurfaceForPicture(file);
    m_sandPicture = CreateSurfaceForPicture(file);
    GenerateSand(file);
    file.FUN_005f5290();
    return true;
}

// FUNCTION: GAME 0x00522e40
void RHLoadingScreen::GenerateSand(SBFile &file)
{
    SBDrawViewport viewport;
    unsigned long surface = CreateSurfaceForPicture(file);
    g_unk0x006c0bd4 = new unsigned char[m_width * m_height];
    if (!m_draw->FUN_005e5a00(surface, viewport, 0))
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
    m_draw->FUN_005e5ea0(viewport);
    m_draw->FUN_005e5160(surface);
    float scale = 255.0f / (maximum - minimum);
    sand = g_unk0x006c0bd4;
    m_height *= m_width;
    for (unsigned long i = 0; i < m_height; ++i)
    {
        *sand = (unsigned char)((*sand - minimum) * scale);
        ++sand;
    }
}

// FUNCTION: GAME 0x00523130
void RHLoadingScreen::RenderSand(volatile unsigned long threshold)
{
    SBDrawViewport screen;
    SBDrawViewport picture;
    SBDrawViewport sandPicture;
    unsigned long width = m_draw->FUN_005e56c0(0);
    unsigned long height = m_draw->FUN_005e5750(0);
    if (!m_draw->FUN_005e5a00(0, screen, 0))
        return;
    unsigned short *destination = screen.UnkData();
    unsigned long screenSkip = (screen.UnkPitch() >> 1) - screen.UnkWidth();
    if (!m_draw->FUN_005e5a00(m_picture, picture, 0))
    {
        m_draw->FUN_005e5ea0(screen);
        return;
    }
    unsigned short *first = picture.UnkData();
    unsigned long skip = (picture.UnkPitch() >> 1) - picture.UnkWidth();
    if (!m_draw->FUN_005e5a00(m_sandPicture, sandPicture, 0))
    {
        m_draw->FUN_005e5ea0(screen);
        m_draw->FUN_005e5ea0(sandPicture);
        return;
    }
    unsigned short *second = sandPicture.UnkData();
    const unsigned char *sand = g_unk0x006c0bd4;
    for (unsigned long y = height; y > 0; --y)
    {
        for (unsigned long x = width; x > 0; --x)
        {
            unsigned long pixel = *sand;
            if (pixel > threshold)
                pixel = *second;
            else
                pixel = *first;
            *destination = (unsigned short)pixel;
            ++first;
            ++second;
            ++destination;
            ++sand;
        }
        first += skip;
        second += skip;
        destination += screenSkip;
    }
    m_draw->FUN_005e5ea0(picture);
    m_draw->FUN_005e5ea0(sandPicture);
    m_draw->FUN_005e5ea0(screen);
}

// FUNCTION: GAME 0x00523300
bool RHLoadingScreen::Refresh()
{
    SBGeoBoundingBox2D bounds;
    SBUIInputFieldDrawUnk renderer;
    std::wstring text;
    if (g_unk0x006a6d27 == 1)
    {
        m_draw->FUN_005e56c0(0);
        m_draw->FUN_005e5750(0);
        m_draw->FUN_005e61e0(0, 0, 0, 0);
        float remaining = 1.0f - m_elapsed / m_duration;
        RenderSand((unsigned long)(remaining * remaining * 256.0f));
        SBGeoBoundingBox2D area(0.0f, 0.0f, (float)m_draw->FUN_005e56c0(0), 100.0f);
        g_unk0x006c1840->FUN_006009e0(0x25, m_status, text);
        char buffer[120];
        sprintf(buffer, g_loadingVersionFormat, g_unk0x006c0580.m_00, g_unk0x006c0580.m_02,
            g_unk0x006c0580.m_versionText.c_str());
        renderer.FUN_00614230(m_versionFont, Toolbox::Convert(std::string(buffer)), area, 8, 0, true);
        m_draw->FUN_005e5260();
        FUN_005e1380();
    }
    else
    {
        while (g_unk0x006a6d27 == 0)
            FUN_005e1400();
    }
    return true;
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
