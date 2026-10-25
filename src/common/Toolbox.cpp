#include "SBNullstr.h"
#include "Toolbox.h"
#include <vector>
#include <math.h>
#include <windows.h>
#include "SBPicture.h"
#include "SBInput.h"
#include "SBThreadedInput.h"
#include "RHUnk005ef320WindowView.h"
#include "RHMapResources.h"
#include "RHMapWideText.h"
#include "SBDrawManager.h"

DECOMP_SIZE_ASSERT(ToolboxChunk, 0x08)
DECOMP_SIZE_ASSERT(ToolboxChunkIterator, 0x10)
DECOMP_SIZE_ASSERT(RHProfileText, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00423b10, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnkFXDraw, 0x10e)
DECOMP_SIZE_ASSERT(RHUnk006114c0, 0x38)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x18)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_SIZE_ASSERT(MD5, 0x6c)
DECOMP_SIZE_ASSERT(ToolboxMouseState, 0x0a)

// STRING: GAME 0x006b8f98
#define g_toolboxFile "P:\\Robin Hood\\Toolbox.cpp"
// STRING: GAME 0x006b9108
#define g_toolboxStreamFile "P:\\Robin Hood\\Toolbox.cpp"

// GLOBAL: GAME 0x006c1178
ToolboxChunks g_unk0x006c1178;
// GLOBAL: GAME 0x006a6d27
unsigned char g_unk0x006a6d27 = 1;
// GLOBAL: GAME 0x006b8fb2
unsigned char g_toolboxInputActive = 1;
// GLOBAL: GAME 0x0067a664
float g_unk0x0067a664 = 0.001f;

// SYNTHETIC: GAME 0x00401910
// ??0RHProfileString@@QAE@ABV0@@Z


// LIBRARY: GAME 0x00401c80
// ??1?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAE@XZ

// LIBRARY: GAME 0x00401ce0
// ?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z

// LIBRARY: GAME 0x00401f30
// ?insert@?$vector@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@V?$allocator@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator6451574f

// LIBRARY: GAME 0x004021c0
// ?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z

// LIBRARY: GAME 0x00402660
// ?max_size@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEIXZ

// LIBRARY: GAME 0x00402670
// ?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAEXI@Z

// LIBRARY: GAME 0x00402850
// ?_Destroy@std@@YAXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z

// LIBRARY: GAME 0x00402890
// ?_Construct@std@@YAXPAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@1@ABV21@@Z

// LIBRARY: GAME 0x00402b90
// ?_Construct@std@@YAXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@ABV21@@Z

// LIBRARY: GAME 0x00402d00
// ??_G?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEPAXI@Z

// LIBRARY: GAME 0x00402de0
// ??4?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEAAV01@ABV01@@Z

// LIBRARY: GAME 0x00423800
// ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@PBDABV?$allocator@D@1@@Z

// LIBRARY: GAME 0x00423910
// ?assign@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEAAV12@PBGI@Z

// LIBRARY: GAME 0x004239c0
// ?_Eos@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@AAEXI@Z

// LIBRARY: GAME 0x004239e0
// ?_Grow@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@AAE_NI_N@Z

// LIBRARY: GAME 0x00423b10
// ?_Copy@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@AAEXI@Z

void RHUnk00423b10::FUN_00423b10(unsigned int count)
{
    unsigned int capacity = count | 31;
    if (capacity > 0x7ffffffd)
        capacity = count;
    unsigned short *storage;
    try {
        storage = std::allocator<unsigned short>().allocate(capacity + 2, 0);
    } catch (...) {
        capacity = count;
        storage = std::allocator<unsigned short>().allocate(capacity + 2, 0);
    }
    if (m_size > 0) {
        unsigned int remaining = m_size > capacity ? capacity : m_size;
        unsigned short *source = m_chars;
        unsigned short *destination = storage + 1;
        while (remaining > 0) {
            *destination++ = *source++;
            --remaining;
        }
    }
    unsigned int oldSize = m_size;
    if (m_chars) {
        unsigned char &references = ((unsigned char *)m_chars)[-1];
        if (references == 0 || references == 255)
            operator delete(m_chars - 1);
        else
            --references;
    }
    m_chars = 0;
    m_size = 0;
    m_capacity = 0;
    m_chars = storage + 1;
    ((unsigned char *)m_chars)[-1] = 0;
    m_capacity = capacity;
    m_size = oldSize > capacity ? capacity : oldSize;
    m_chars[m_size] = 0;
}

// LIBRARY: GAME 0x0044fa70
// ?erase@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEAAV12@II@Z

// LIBRARY: GAME 0x0044fbc0
// ?_Split@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@AAEXXZ

// LIBRARY: GAME 0x00457c60
// ?_Destroy@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@IAEXPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@0@Z

// LIBRARY: GAME 0x00458bd0
// ?max_size@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QBEIXZ

// FUNCTION: GAME 0x005e0c90
bool FUN_005e0c90(SBFile &file, std::string &value)
{
    unsigned short length;
    if (!file.m_bLoading) {
        length = value.size();
        if (file.Access(&length, 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0x86, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access((void *)value.c_str(), length) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0x87, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    } else {
        if (file.Access(&length, 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0x8f, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        char *buffer = (char *)operator new(length + 1);
        if (file.Access(buffer, length) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0x94, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        buffer[length] = 0;
        value.assign(buffer);
        operator delete(buffer);
    }
    return true;
}

// FUNCTION: GAME 0x005e0ea0
bool FUN_005e0ea0(SBFile &file, std::wstring &value)
{
    unsigned short length;
    if (!file.m_bLoading) {
        length = value.size();
        if (file.Access(&length, 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0xb6, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access((void *)value.c_str(), length * 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0xb7, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    } else {
        if (file.Access(&length, 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0xbf, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        wchar_t *buffer = (wchar_t *)operator new((length + 1) * 2);
        if (file.Access(buffer, length * 2) < 0) {
            SBString *error = file.GetError();
            SBAssert(0, g_toolboxFile, 0xc4, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        buffer[length] = 0;
        value.assign(buffer);
        operator delete(buffer);
    }
    return true;
}

// FUNCTION: GAME 0x005e10b0
std::wstring Toolbox::Convert(const std::string &text)
{
    wchar_t buffer[256];
    buffer[0] = 0;
    buffer[255] = 0;
    if (text.size() < 63)
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text.c_str(), -1, buffer, 255);
    return std::wstring(buffer);
}

class RHElementActorPC;
class RHEngine;
extern RHEngine *g_pEngine;
extern RHMapResources *g_unk0x006c1840;

// FUNCTION: GAME 0x005e11d0
std::string FUN_005e11d0(const std::wstring &wide)
{
    std::string text;
    for (std::wstring::const_iterator it = wide.begin(); it != wide.end(); ++it)
    {
        char character = (char)*it;
        text.insert(text.end(), character);
    }
    return text;
}

// FUNCTION: GAME 0x005e1380
void FUN_005e1380()
{
    MSG message;
    RHUnk005ef320WindowView *draw = (RHUnk005ef320WindowView *)g_unk0x6c11d0;
    if (IsIconic(draw->GetWindow()) > 0 && g_unk0x006a6d27 == 1)
    {
        g_unk0x006a6d27 = 0;
        SBInputUnk005fb730::mpInput->FUN_005f9ea0(0);
        ShowCursor(1);
    }
    if (PeekMessageA(&message, draw->GetWindow(), 0, 0, 1))
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
}

// FUNCTION: GAME 0x005e1400
void FUN_005e1400()
{
    MSG message;
    GetMessageA(&message, *(HWND *)((char *)g_unk0x6c11d0 + 0x100), 0, 0);
    TranslateMessage(&message);
    DispatchMessageA(&message);
}

// FUNCTION: GAME 0x005e17a0
bool FUN_005e17a0(unsigned char *keys)
{
    bool altTab = keys[0x0f] > 0U && (keys[0x38] > 0U || keys[0xb8] > 0U);
    bool ctrlEscape = keys[0x01] > 0U && (keys[0x1d] > 0U || keys[0x9d] > 0U);
    bool ctrlAltDelete = (keys[0x1d] > 0U || keys[0x9d] > 0U) &&
        (keys[0x38] > 0U || keys[0xb8] > 0U) && (keys[0x53] > 0U || keys[0xd3] > 0U);
    if (altTab || ctrlEscape || ctrlAltDelete)
    {
        keys[0x0f] = 0;
        keys[0x38] = 0;
        keys[0xb8] = 0;
        keys[0x1d] = 0;
        keys[0x9d] = 0;
        keys[0x01] = 0;
        keys[0x53] = 0;
        keys[0xd3] = 0;
        g_unk0x006a6d27 = 0;
        g_toolboxInputActive = 0;
        ShowWindow(*(HWND *)((char *)g_unk0x6c11d0 + 0x100), 6);
    }
    if (g_toolboxInputActive == 1 && g_unk0x006a6d27 == 0)
    {
        g_toolboxInputActive = 0;
        return true;
    }
    return altTab || ctrlEscape;
}

// FUNCTION: GAME 0x005e18a0
bool FUN_005e18a0()
{
    SBInputUnk005fb730 *input = SBInputUnk005fb730::mpInput;
    RHMapResources *resources = g_unk0x006c1840;
    RHUnk005ef320WindowView *draw = (RHUnk005ef320WindowView *)g_unk0x6c11d0;
    RHMapWideText message;
    input->FUN_005f9ea0(0);
    CloseWindow(draw->GetWindow());
    resources->FUN_006009e0(0x25, 0x1f, message);
    ShowCursor(1);
    int answer = MessageBoxA(0, FUN_005e11d0((std::wstring &)message).c_str(), 0, 0x15);
    ShowWindow(draw->GetWindow(), 9);
    ((RHUnk005ef320 *)draw)->FUN_005e3f70();
    if (g_pEngine)
        *(unsigned char *)((char *)g_pEngine + 0x48d1) = 0;
    input->FUN_005f9ea0(1);
    ShowCursor(0);
    return answer == 4;
}

// FUNCTION: GAME 0x005e19e0
RHElementActorPC *FUN_005e19e0(char *text)
{
    unsigned int value = 0;
    while (*text)
    {
        switch (*text++)
        {
        case '0':
            value = value * 16;
            break;
        case '1':
            value = value * 16 + 1;
            break;
        case '2':
            value = value * 16 + 2;
            break;
        case '3':
            value = value * 16 + 3;
            break;
        case '4':
            value = value * 16 + 4;
            break;
        case '5':
            value = value * 16 + 5;
            break;
        case '6':
            value = value * 16 + 6;
            break;
        case '7':
            value = value * 16 + 7;
            break;
        case '8':
            value = value * 16 + 8;
            break;
        case '9':
            value = value * 16 + 9;
            break;
        case 'A':
        case 'a':
            value = value * 16 + 10;
            break;
        case 'B':
        case 'b':
            value = value * 16 + 11;
            break;
        case 'C':
        case 'c':
            value = value * 16 + 12;
            break;
        case 'D':
        case 'd':
            value = value * 16 + 13;
            break;
        case 'E':
        case 'e':
            value = value * 16 + 14;
            break;
        case 'F':
        case 'f':
            value = value * 16 + 15;
            break;
        }
    }
    return (RHElementActorPC *)value;
}

// FUNCTION: GAME 0x005e1b20
MD5 *Toolbox::MD5_string(MD5 *result, unsigned char *name)
{
    MD5 digest;
    digest.update(name, strlen((char *)name));
    digest.finalize();
    *result = digest;
    return result;
}

// FUNCTION: GAME 0x005e1b70
void RHSerializeName(SBFile &file, const char *name)
{
    MD5 expected(MD5::UninitializedStorage);
    {
        MD5 temporary(MD5::UninitializedStorage);
        expected = *Toolbox::MD5_string(&temporary, (unsigned char *)name);
    }
    if (!file.m_bLoading)
        expected.Serialize(file);
    else
    {
        MD5 actual;
        actual.Serialize(file);
        if (actual != expected)
            SBAssert(1, g_toolboxStreamFile, 0x40b,
                // STRING: GAME 0x006b9124
                "Digital signature of readed stream is not valid");
    }
}

// SYNTHETIC: GAME 0x005e1c50
// ??1ToolboxChunks@@QAE@XZ

// FUNCTION: GAME 0x005e1d50
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

// FUNCTION: GAME 0x005e20c0
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

// FUNCTION: GAME 0x005e2340
std::wstring Toolbox::TrimWideString(const std::wstring &text)
{
    unsigned size = text.size();
    int last = size - 1;
    while (last >= 0 && text[last] == L' ')
        --last;
    unsigned first = 0;
    while (first < size && text[first] == L' ')
        ++first;
    return text.substr(first, last >= 0 ? last - first + 1 : 0);
}

// FUNCTION: GAME 0x005e23d0
std::wstring FUN_005e23d0(unsigned long id)
{
    RHMapResources *resources = g_unk0x006c1840;
    std::wstring text;
    if (!resources->FUN_006009e0(0xf443b, id, (RHMapWideText &)text))
        text =
            // STRING: GAME 0x006b91d0
            L"Bad menu text ID...";
    return text;
}

// Parked: crop receiver and draw-argument reload scheduling differ.
// STUB: GAME 0x005e24f0
void Toolbox::DisplayPicture(const char *name, bool wait)
{
    RHUnk006114c0 picture;
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    RHUnk005f4fc0 file;
    unsigned long width = draw->FUN_005e56c0(0);
    unsigned long height = draw->FUN_005e5750(0);
    file.FUN_005f5090((const std::string &)RHProfileText(name), 1);
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
        SBThreadedInput::GetChar();
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
    ((SBDrawManager *)draw)->FUN_005e61e0(0, 0, 0, 0);
    draw->FUN_005e5260();
    ((SBDrawManager *)draw)->FUN_005e61e0(0, 0, 0, 0);
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

// FUNCTION: GAME 0x005e2d10
void Toolbox::HSV_To_RGB(float h, float s, float v, float &r, float &g, float &b)
{
    if (s == 0.0f)
    {
        r = v;
        g = v;
        b = v;
        return;
    }
    h *= 1.0f / 60.0f;
    double i = floor(h);
    float f = h - i;
    float p = v * (1.0f - s);
    float q = v * (1.0f - s * f);
    float t = v * (1.0f - s * (1.0f - f));
    switch ((unsigned short)i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
}

// Parked at 0.2510: unannotated park from the asymmetric-comparator era; residual scheduling/registers.
// STUB: GAME 0x00611710
bool RHUnk006114c0::Unk00611710(SBFile &file)
{
    unsigned long header[3] = {0xcccccccc, 0xcccccccc, 0xcccccccc};
    FUN_00611aa0(file, header);
    SBPicture *picture = (SBPicture *)this;
    picture->m_22 = ((unsigned short *)header)[1];
    picture->m_20 = ((unsigned short *)header)[0];
    picture->m_04 = 3;
    if (picture->m_1c) {
        operator delete(picture->m_14);
        picture->m_14 = 0;
    }
    if (header[1] > 2)
        return false;
    picture->m_14 = (unsigned char *)operator new(picture->m_22 * picture->m_20 * 2);
    switch (header[1]) {
    case 0:
        file.Access(picture->m_14, header[2]);
        picture->m_1c = header[2];
        *(unsigned long *)(m_24 + 0x10) = header[2];
        break;
    case 1:
        {
            void *compressed = operator new(header[2]);
            file.Access(compressed, header[2]);
            picture->m_1c = picture->m_22 * picture->m_20 * 2;
            *(unsigned long *)(m_24 + 0x10) = header[2];
            extern int FUN_006277e0(void *, unsigned int *, const void *, unsigned int);
            FUN_006277e0(picture->m_14, &picture->m_1c, compressed, header[2]);
            operator delete(compressed);
        }
        picture->m_24 = picture->m_20 * 2;
        return true;
    case 2:
        {
            void *compressed = operator new(header[2]);
            file.Access(compressed, header[2]);
            picture->m_1c = picture->m_22 * picture->m_20 * 2;
            *(unsigned long *)(m_24 + 0x10) = header[2];
            extern int __stdcall FUN_006273d0(void *, unsigned int *, const void *, unsigned int, int, int);
            FUN_006273d0(picture->m_14, &picture->m_1c, compressed, header[2], 0, 0);
            operator delete(compressed);
        }
        picture->m_24 = picture->m_20 * 2;
        return true;
    }
    picture->m_24 = picture->m_20 * 2;
    return true;
}

// FUNCTION: GAME 0x006118b0
bool RHUnk006114c0::FUN_006118b0(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 2))
        return false;
    bool saved = Unk1c(file);
    file.FUN_005f5290();
    return saved;
}

// FUNCTION: GAME 0x00613530
bool RHUnk006114c0::Unk00613530(RHUnkFXDraw *draw, unsigned long surface)
{
    RHUnk00613e90 pixels;
    SBPicture *picture = (SBPicture *)this;
    if (draw->FUN_005e56c0(surface) == picture->m_20 &&
        draw->FUN_005e5750(surface) == picture->m_22) {
        if (draw->UnkField10c() == 16)
        {
            unsigned int format = picture->m_04;
            if (format != 3)
                Unk00611e10(3, 0);
        }
        if (draw->UnkField10c() == 15 && picture->m_04 != 2)
            Unk00611e10(2, 0);
        if (draw->Unk005e5a00(surface, pixels, 0)) {
            unsigned int gap = (pixels.m_pitch >> 1) - picture->m_20;
            unsigned short *destination = pixels.m_data;
            unsigned short *source = (unsigned short *)picture->m_14;
            for (unsigned int y = 0; (unsigned short)y < picture->m_22; ++y) {
                for (unsigned int x = 0; (unsigned short)x < picture->m_20; ++x)
                    *destination++ = *source++;
                destination += gap;
            }
            draw->Unk005e5ea0(pixels);
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00624b70
unsigned long Toolbox::HexaAsciiToInteger(const char *text)
{
    unsigned long result = 0;
    while (*text) {
        switch (*text) {
        case '1': result += 1; break;
        case '2': result += 2; break;
        case '3': result += 3; break;
        case '4': result += 4; break;
        case '5': result += 5; break;
        case '6': result += 6; break;
        case '7': result += 7; break;
        case '8': result += 8; break;
        case '9': result += 9; break;
        case 'A': result += 10; break;
        case 'B': result += 11; break;
        case 'C': result += 12; break;
        case 'D': result += 13; break;
        case 'E': result += 14; break;
        case 'F': result += 15; break;
        }
        ++text;
        result <<= 4;
    }
    return result;
}

// Parked: target is hand-written register-preserving assembly with REP MOVSW.
// STUB: GAME 0x005e3730
void FUN_005e3730(const unsigned short *source, unsigned short *destination, long stride,
    unsigned short width, unsigned short rows, unsigned short fill)
{
    do
    {
        unsigned short first = *source++;
        if (first != 0xffff && first != 0)
        {
            unsigned short count = first;
            do
                *destination++ = fill;
            while (--count != 0);
        }
        unsigned short last = *source++;
        bool empty = last == 0xffff;
        unsigned short padding;
        if (last != 0xffff)
        {
            ++last;
            unsigned short count = last - first;
            memcpy(destination, source, count * sizeof(unsigned short));
            destination += count;
            source += count;
            padding = width - last;
        }
        else
            padding = width;
        if (padding != 0 || empty)
            do
                *destination++ = fill;
            while (--padding != 0);
        destination = (unsigned short *)((char *)destination + stride);
    }
    while (--rows != 0);
}

// Parked: target preserves all registers and carries the fill word through BSWAP.
// STUB: GAME 0x005e37c0
void FUN_005e37c0(const unsigned short *source, unsigned short *destination, long stride,
    unsigned short width, unsigned short rows, unsigned short fill, unsigned short key)
{
    do
    {
        unsigned short first = *source++;
        if (first != 0xffff && first != 0)
        {
            unsigned short count = first;
            do
                *destination++ = fill;
            while (--count != 0);
        }
        unsigned short last = *source++;
        bool empty = last == 0xffff;
        unsigned short padding;
        if (last != 0xffff)
        {
            ++last;
            unsigned short count = last - first;
            do
            {
                unsigned short pixel = *source++;
                *destination++ = pixel == key ? 0 : pixel;
            }
            while (--count != 0);
            padding = width - last;
        }
        else
            padding = width;
        if (padding != 0 || empty)
            do
                *destination++ = fill;
            while (--padding != 0);
        destination = (unsigned short *)((char *)destination + stride);
    }
    while (--rows != 0);
}

// FUNCTION: GAME 0x00624a60
RHUnk00624a60::RHUnk00624a60()
{
    m_list.m_dirty = true;
    *(unsigned *)m_00 = 0x67ae70;
}

// FUNCTION: GAME 0x00624aa0
void *RHUnk00624a60::FUN_00624aa0(unsigned flags)
{
    this->RHUnk00624a60::~RHUnk00624a60();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00624ac0
RHUnk00624a60::~RHUnk00624a60()
{
    *(unsigned *)m_00 = 0x67ae70;
    m_list.clear();
}

// Parked: green channel extracted through ah instead of shr edx,8 / mov cl,dl.
// STUB: GAME 0x00624c40
void RHUnk00624a60::FUN_00624c40(const char *text, unsigned int &position, RHTextChunk *chunk)
{
    char tag[256];
    int length = 0;
    while (text[position] != '\0' && text[position] != '>')
        tag[length++] = text[position++];
    tag[length] = '\0';
    ++position;
    // STRING: GAME 0x006bb9f8
    if (strcmp(tag, "BOLD") == 0)
        chunk->m_flags |= 1;
    // STRING: GAME 0x006bb9f0
    if (strcmp(tag, "/BOLD") == 0)
        chunk->m_flags &= ~1;
    // STRING: GAME 0x006bb9e8
    if (strcmp(tag, "ITALIC") == 0)
        chunk->m_flags |= 2;
    // STRING: GAME 0x006bb9e0
    if (strcmp(tag, "/ITALIC") == 0)
        chunk->m_flags &= ~2;
    // STRING: GAME 0x006bb9d4
    if (strcmp(tag, "UNDERLINE") == 0)
        chunk->m_flags |= 4;
    // STRING: GAME 0x006bb9c8
    if (strcmp(tag, "/UNDERLINE") == 0)
        chunk->m_flags &= ~4;
    // STRING: GAME 0x006bb9c0
    if (strncmp(tag, "COLOR=", 6) == 0) {
        unsigned long color = Toolbox::HexaAsciiToInteger(tag + 6);
        chunk->m_color = RGB((BYTE)(color >> 16), (BYTE)(color >> 8), (BYTE)color);
    }
    // STRING: GAME 0x006bb9b8
    if (strncmp(tag, "FONT=", 5) == 0)
        strcpy(chunk->m_font, tag + 5);
    // STRING: GAME 0x006bb9ac
    if (strncmp(tag, "FONTSIZE=", 9) == 0)
        chunk->m_size = atoi(tag + 9);
}

// Parked: target caches byte zero in bl across both inlined cursor walks.
// STUB: GAME 0x00624ed0
const char *RHUnk00624a60::FUN_00624ed0(unsigned short index)
{
    if (m_list.At(index).m_font[0] == '\0')
        // STRING: GAME 0x006bba00
        return "Courrier New";
    return m_list.At(index).m_font;
}

// Parked: target caches zero in ebx (this in ebp) and keeps the first construct out of line.
// STUB: GAME 0x006250d0
unsigned short RHUnk00624a60::FUN_006250d0(const char *text)
{
    unsigned int length = strlen(text);
    RHTextChunk chunk;
    unsigned int position = 0;
    int used = 0;
    chunk.m_text[0] = '\0';
    // STRING: GAME 0x006bba10
    strcpy(chunk.m_font, "Lucida Sans Console");
    chunk.m_flags = 0;
    chunk.m_color = 0xffffff;
    chunk.m_ac = 0;
    chunk.m_size = 12;
    while (position < length) {
        char c = text[position];
        if (c != '<') {
            chunk.m_text[used] = c;
            chunk.m_text[used + 1] = '\0';
            ++position;
            ++used;
        } else {
            ++position;
            if (strlen(chunk.m_text) != 0) {
                m_list.InsertLast(chunk);
                used = 0;
                chunk.m_text[0] = '\0';
            }
            FUN_00624c40(text, position, &chunk);
        }
    }
    m_list.push_back(chunk);
    m_list.m_dirty = true;
    return m_list.size();
}

// FUNCTION: GAME 0x00625270
void FUN_00625270(RHTextChunk *pointer, const RHTextChunk &value)
{
    if (pointer)
        *pointer = value;
}

void Toolbox::Emit()
{
    DisplayPicture("", false);
    PlaySlide("", 0);
    RHUnk00423b10 wide;
    wide.FUN_00423b10(0);
    typedef std::vector<std::string> Strings;
    Strings strings;
    void (*volatile destroy)(std::string *) = std::_Destroy;
    void (*volatile construct)(Strings *, const Strings &) = std::_Construct;
    Strings &(Strings::*volatile assign)(const Strings &) = &Strings::operator=;
    (strings.*assign)(strings);
    std::string &(std::string::*volatile assignString)(const std::string &, unsigned, unsigned) = &std::string::assign;
    typedef std::vector<Strings> NestedStrings;
    void (NestedStrings::*volatile insertStrings)(Strings *, unsigned, const Strings &) = &NestedStrings::insert;
}
