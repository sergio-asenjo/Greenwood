#include "SBNullstr.h"
#include "avitoolbox.h"
#include <string.h>
#include "RHSoundCore.h"

// GLOBAL: GAME 0x006772d0
void (__stdcall *g_unk0x006772d0)(RHUnkBink *);
// GLOBAL: GAME 0x006772d4
void (__stdcall *g_unk0x006772d4)(RHUnkBink *, void *, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// GLOBAL: GAME 0x006772d8
void (__stdcall *g_unk0x006772d8)(RHUnkBink *);
// GLOBAL: GAME 0x006772dc
int (__stdcall *g_unk0x006772dc)(RHUnkBink *);
// GLOBAL: GAME 0x006772e0
void (__stdcall *g_unk0x006772e0)(RHUnkBink *, void *);
// GLOBAL: GAME 0x006772e4
RHUnkBink *(__stdcall *g_unk0x006772e4)(const char *, unsigned long);
// GLOBAL: GAME 0x006772e8
const char *(__stdcall *g_unk0x006772e8)();
// GLOBAL: GAME 0x006772ec
void (__stdcall *g_unk0x006772ec)(void *, void *);
// GLOBAL: GAME 0x006772f0
void *g_unk0x006772f0;
// GLOBAL: GAME 0x006772f4
void (__stdcall *g_unk0x006772f4)(RHUnkBink *);

// FUNCTION: GAME 0x00401130
bool FUN_00401130(const char *name)
{
    bool redraw;
    bool cancelled;
    redraw = false;
    RHUnk00613e90 viewport;
    ToolboxMouseState mouse;
    memset(&mouse, 0, sizeof(mouse));
    unsigned char keys[256];
    memset(keys, 0, sizeof(keys));
    char summary[124];
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    g_unk0x006772ec(g_unk0x006772f0, ((RHSound *)g_unk0x006c1070)->FUN_005a6f90());
    const char *(__stdcall *getError)() = g_unk0x006772e8;
    getError();
    RHUnkBink *movie = g_unk0x006772e4(name, 0);
    getError();
    g_unk0x006772e0(movie, summary);
    unsigned long y = (480 - *(unsigned long *)(summary + 4)) / 2;
    unsigned short depth = draw->m_10c;
    unsigned long format = 9 + (depth == 16);
    draw->FUN_005e61e0(0, 0, 0, 0);
    draw->FUN_005e5260();
    draw->FUN_005e61e0(0, 0, 0, 0);
    if (movie)
    {
        int (__stdcall *wait)(RHUnkBink *) = g_unk0x006772dc;
        cancelled = false;
        for (;;)
        {
            while (FUN_005f0ce0() > 0)
            {
                FUN_005f1150(mouse, keys);
                if ((unsigned char)mouse.m_buttons == 1 || keys[1])
                    cancelled = true;
            }
            FUN_005e17a0(keys);
            if (g_unk0x006a6d27 == 1)
            {
                g_unk0x006772f4(movie);
                if (redraw == true)
                    draw->FUN_005e61e0(0, 0, 0, 0);
                if (draw->Unk005e5a00(0, viewport, 0))
                {
                    g_unk0x006772d4(movie, viewport.m_10, viewport.m_08, viewport.m_06, 0, y, format | 0x80000000);
                    draw->Unk005e5ea0(viewport);
                    draw->FUN_005e5260();
                    FUN_005e1380();
                    while (wait(movie)) {}
                    if (movie->m_0c == movie->m_08 - 1)
                        break;
                    g_unk0x006772d0(movie);
                }
            }
            else
            {
                redraw = true;
                FUN_005e1400();
            }
            if (cancelled)
                break;
        }
        g_unk0x006772d8(movie);
        return true;
    }
    SBAssert(0,
        // STRING: GAME 0x006a6b30
        "P:\\Robin Hood\\AviToolbox.cpp", 0xf4,
        // STRING: GAME 0x006a6b50
        "Unable to play cinematic %s", name);
    return false;
}

bool FUN_005f6400(const std::string &name);
int FUN_005f5a80(std::string &name, bool retry);

// FUNCTION: GAME 0x004013a0
void FUN_004013a0(const std::string &name)
{
    if (FUN_005f6400(name) || FUN_005f5a80(const_cast<std::string &>(name), false) == 0)
        FUN_00401130(name.c_str());
}
