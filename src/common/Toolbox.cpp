#include "Toolbox.h"
#include <windows.h>

// STRING: GAME 0x006b8f98
#define g_toolboxFile "P:\\Robin Hood\\Toolbox.cpp"
// STRING: GAME 0x006b9108
#define g_toolboxStreamFile "P:\\Robin Hood\\Toolbox.cpp"

// GLOBAL: GAME 0x006c1178
ToolboxChunks g_unk0x006c1178;
// GLOBAL: GAME 0x006a6d27
unsigned char g_unk0x006a6d27 = 1;
// GLOBAL: GAME 0x0067a664
float g_unk0x0067a664 = 0.001f;

// deferred: unannotated pending reccmp #534
void RHSerializeName(SBFile &file, const char *name)
{
    RHUnk0060e4c0 expected;
    {
        RHUnk0060e4c0 temporary;
        expected = *FUN_005e1b20(&temporary, name);
    }
    if (!file.m_bLoading)
        expected.FUN_0060f1e0(file);
    else
    {
        RHUnk0060e4c0 actual;
        actual.FUN_0060e4c0();
        actual.FUN_0060f1e0(file);
        if (actual.FUN_0060f1c0(expected))
            SBAssert(1, g_toolboxStreamFile, 0x40b,
                // STRING: GAME 0x006b9124
                "Digital signature of readed stream is not valid");
    }
}

// deferred: unannotated pending reccmp #534; map-load registers remain unmatched
void FUN_005e1d50(SBFile &file, unsigned long expected, int version)
{
    unsigned long tag;
    ToolboxChunk chunk;
    unsigned long readVersion;
    file.Access(&tag, 4);
    file.Access(&chunk.m_size, 4);
    file.Access(&readVersion, 4);
    tag = (((tag & 0x00ff0000) | (tag >> 16)) >> 8) | (((tag & 0x0000ff00) | (tag << 16)) << 8);
    if (expected != tag)
    {
        char foundName[5];
        char expectedName[5];
        *(unsigned long *)foundName = tag;
        foundName[4] = 0;
        *(unsigned long *)expectedName = expected;
        expectedName[4] = 0;
        SBAssert(1, g_toolboxStreamFile, 0x44c,
            // STRING: GAME 0x006b9184
            "Expected chunk %s, found %s", expectedName, foundName);
    }
    if ((unsigned long)version != readVersion)
    {
        char versionName[5];
        *(unsigned long *)versionName = tag;
        versionName[4] = 0;
        SBAssert(1, g_toolboxStreamFile, 0x457,
            // STRING: GAME 0x006b9154
            "Chunk version %d does not match %d in chunk %s", readVersion, version, versionName);
    }
    chunk.m_start = ((ToolboxPositionFile *)&file)->FUN_005f5440();
    g_unk0x006c1178.Append(chunk);
}

// deferred: unannotated pending reccmp #534
void FUN_005e20c0(SBFile &file)
{
    ToolboxChunk chunk = g_unk0x006c1178.back();
    unsigned long size = ((ToolboxPositionFile *)&file)->FUN_005f5440() - chunk.m_start + 4;
    if (chunk.m_size != size)
        SBAssert(1, g_toolboxStreamFile, 0x493,
            // STRING: GAME 0x006b91a0
            "Read size %d does not match expected size %d", size, chunk.m_size);
    g_unk0x006c1178.pop_back();
}

// parked (96.71%): crop-result register and draw-reload scheduling differ
// STUB: GAME 0x005e24f0
void Toolbox::DisplayPicture(const char *name, bool wait)
{
    RHUnk006114c0 picture;
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    RHUnk005f4fc0 file;
    unsigned long width = draw->FUN_005e56c0(0);
    unsigned long height = draw->FUN_005e5750(0);
    file.FUN_005f5090(RHProfileText(name), 1);
    if (!picture.Unk00611710(file))
    {
        SBAssert(0, g_toolboxFile, 0x4f5, "Unable to load picture from pak file");
        return;
    }
    unsigned long surface = draw->Unk005e4ed0(width, height, 0, 0);
    switch (draw->UnkField10c())
    {
    case 15:
        picture.Unk00611e10(2, 0);
        break;
    case 16:
        picture.Unk00611e10(3, 0);
        break;
    default:
        SBAssert(0, g_toolboxFile, 0x507, "Unsupported bit depth for loading screen !");
        return;
    }
    unsigned long pictureWidth = picture.UnkField20();
    unsigned long pictureHeight = picture.UnkField22();
    if (pictureWidth <= width && pictureHeight <= height)
        picture.Unk00613530(draw, surface);
    else
    {
        unsigned int x = (pictureWidth - width + 1) / 2;
        unsigned int y = (pictureHeight - height + 1) / 2;
        RHUnk006114c0 *cropped = picture.Unk00612ad0(SBGeoPoint2D((float)x, (float)y), SBGeoVector2D((float)width, (float)height));
        cropped->Unk20(*(RHUnkFXDraw *volatile *)&draw, surface);
        delete cropped;
    }
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e6440(surface, 0, 0, 0, 8);
    file.FUN_005f5290();
    if (wait)
    {
        extern void FUN_005f1000();
        FUN_005f1000();
    }
}

// FUNCTION: GAME 0x005e27e0
void Toolbox::PlaySlide(const std::string &name, unsigned short duration)
{
    RHUnk005f4fc0 file;
    RHUnk006114c0 picture;
    bool cancelled;
    bool redraw;
    ToolboxMouseState mouse;
    std::string path;
    cancelled = false;
    redraw = false;
    path = std::string(
        // STRING: GAME 0x006b9228
        "Data\\Interface\\") + name;
    if (file.FUN_005f5090(path, 1) != 0)
        SBAssert(1, g_toolboxFile, 0x55f,
            // STRING: GAME 0x006b91f8
            "Unable to open the specified slide show file");
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    memset(&mouse, 0, sizeof(mouse));
    unsigned char keys[256];
    memset(keys, 0, sizeof(keys));
    draw->FUN_005e61e0(0, 0, 0, 0);
    draw->FUN_005e5260();
    draw->FUN_005e61e0(0, 0, 0, 0);
    while (file.Position() < file.Size() && !cancelled)
    {
        bool advance = false;
        picture.Unk00611710(file);
        typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
        unsigned long surface = (draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(picture.UnkField20(), picture.UnkField22(), 0, false);
        picture.Unk00613530(draw, surface);
        draw->FUN_005e6440(surface, 0, 0, 0, 0);
        draw->FUN_005e5260();
        draw->FUN_005e6440(surface, 0, 0, 0, 0);
        unsigned long start = GetTickCount();
        for (;;)
        {
            while (FUN_005f0ce0() > 0)
                FUN_005f1150(mouse, keys);
            if (FUN_005e17a0(keys) == true)
            {
                redraw = true;
                continue;
            }
            if (keys[1])
            {
                cancelled = true;
                advance = true;
            }
            for (int i = 2; i < 255; ++i)
            {
                if (keys[i])
                    advance = true;
            }
            if ((unsigned char)mouse.m_buttons == 1)
                advance = true;
            if (g_unk0x006a6d27 == 1)
            {
                if (redraw == true)
                {
                    redraw = false;
                    draw->FUN_005e6440(surface, 0, 0, 0, 0);
                    draw->FUN_005e5260();
                    draw->FUN_005e6440(surface, 0, 0, 0, 0);
                }
                FUN_005e1380();
                if ((GetTickCount() - start) * g_unk0x0067a664 > duration)
                    break;
            }
            else
                FUN_005e1400();
            if (advance)
                break;
        }
        draw->Unk005e5160(surface);
    }
    file.FUN_005f5290();
    while (!g_unk0x006a6d27)
        FUN_005e1400();
}

void Toolbox::Emit()
{
    DisplayPicture("", false);
    PlaySlide("", 0);
}
