#include "SBNullstr.h"
#include "launcher.h"
#include "SBInput.h"
#include "SBDrawManager.h"
#include "RHGameInputTranslator.h"
#include "RHGameActionCalls.h"
#include "RHUnk005ef320WindowView.h"
#include "Decomp.h"

DECOMP_SIZE_ASSERT(RHUnk00408f50, 0x100)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00408f50, m_versionMode) == 0x0a)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00408f50, m_versionText) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00408f50, m_60) == 0x60)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00408f50, m_f0) == 0xf0)

// GLOBAL: GAME 0x006c0580
RHUnk00408f50 g_unk0x006c0580;

// FUNCTION: GAME 0x00408d60
RHUnk00408f50::~RHUnk00408f50()
{
}

// FUNCTION: GAME 0x00408f50
RHUnk00408f50::RHUnk00408f50()
{
}

class RHEngine;
class RHArtificialIntelligenceSoundCalls;
extern RHEngine *g_pEngine;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
extern RHUnk005ef320 *g_unk0x6c11d0;
extern unsigned char g_unk0x006a6d27;

// GLOBAL: GAME 0x006c06ac
unsigned char g_launcherQuitRequested = 0;

// FUNCTION: GAME 0x004094f0
LRESULT CALLBACK FUN_004094f0(HWND window, UINT message, WPARAM first, LPARAM second)
{
    SBInputUnk005fb730 *input = SBInputUnk005fb730::mpInput;
    RHUnk005ef320 *draw = g_unk0x6c11d0;
    PAINTSTRUCT paint;
    switch (message)
    {
    case WM_PAINT:
        BeginPaint(window, &paint);
        EndPaint(window, &paint);
        return 0;
    case WM_DESTROY:
        g_launcherQuitRequested = 1;
        PostQuitMessage(0);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_ACTIVATEAPP:
        if (input && draw)
        {
            if ((short)first == 0)
            {
                g_unk0x006a6d27 = 0;
                input->FUN_005f9ea0(0);
                ShowCursor(1);
                if (g_unk0x006c1070)
                    ((RHGameActionCalls *)g_unk0x006c1070)->FUN_005a7b40(0);
            }
            else if (g_unk0x006a6d27 == 0 || IsIconic(((RHUnk005ef320WindowView *)draw)->GetWindow()))
            {
                g_unk0x006a6d27 = 1;
                ShowWindow(((RHUnk005ef320WindowView *)draw)->GetWindow(), 9);
                while (IsIconic(((RHUnk005ef320WindowView *)draw)->GetWindow())) {}
                draw->FUN_005e3f70();
                if (g_pEngine)
                    *(unsigned char *)((char *)g_pEngine + 0x48d1) = 0;
                input->FUN_005f9ea0(g_unk0x006a6d27);
                if (RHGameInputTranslator::mpInstance)
                    RHGameInputTranslator::mpInstance->ResetState();
                if (g_unk0x006c1070)
                    ((RHGameActionCalls *)g_unk0x006c1070)->FUN_005a7b40(1);
                while (ShowCursor(0) >= 0) {}
            }
        }
        return 0;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
        return 0;
    }
    return DefWindowProcA(window, message, first, second);
}

#include "RHUnk005f4fc0.h"
#include <stdio.h>
#include <string.h>

// FUNCTION: GAME 0x004096b0
void FUN_004096b0()
{
    RHUnk005f4fc0 file;
    char buffer[132];
    {
        std::string name(
            // STRING: GAME 0x006a6f90
            "hunk.cfg");
        file.FUN_005f5090(name, 2);
    }
    sprintf(buffer,
        // STRING: GAME 0x006a6f80
        "Mask[ %d, %d ]\n", 0x46414345, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f6c
        "Motion[ %d, %d ]\n", 0x53544154, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f54
        "Animation[ %d, %d ]\n", 0x464c494d, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f40
        "Sight[ %d, %d ]\n", 0x574f4157, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f24
        "Miscellaneous[ %d, %d ]\n", 0x53504f4b, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f14
        "Bond[ %d, %d ]\n", 0x30303720, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6f00
        "Patch[ %d, %d ]\n", 0x5455504f, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6eec
        "Sound[ %d, %d ]\n", 0x4c4f5544, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6ed8
        "Material[ %d, %d ]\n", 0x54455854, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6ec8
        "Lift[ %d, %d ]\n", 0x20415a20, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6eb4
        "Building[ %d, %d ]\n", 0x4641524d, 4);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6ea0
        "Light[ %d, %d ]\n", 0x4441524b, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e90
        "Jump[ %d, %d ]\n", 0x50505050, 4);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e7c
        "Header[ %d, %d ]\n", 0x464f4f54, 4);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e68
        "Actor[ %d, %d ]\n", 0x424f595a, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e54
        "Tactic[ %d, %d ]\n", 0x4849524e, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e40
        "Mobile[ %d, %d ]\n", 0x54494e47, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e30
        "Path[ %d, %d ]\n", 0x5241494c, 3);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e1c
        "Scroll[ %d, %d ]\n", 0x534b524f, 4);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6e08
        "Bonus[ %d, %d ]\n", 0x5a4f5247, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6df4
        "Script[ %d, %d ]\n", 0x47554c50, 2);
    file.Access(buffer, strlen(buffer));
    sprintf(buffer,
        // STRING: GAME 0x006a6de0
        "Tenant[ %d, %d ]\n", 0x43415645, 3);
    file.Access(buffer, strlen(buffer));
    file.FUN_005f5290();
}

// FUNCTION: GAME 0x00409d10
char **FUN_00409d10(char *command, unsigned *count)
{
    unsigned spaces = 0;
    for (unsigned position = 0; command[position]; ++position)
    {
        if (command[position] == ' ')
        {
            ++spaces;
            command[position] = 0;
        }
    }
    unsigned total = spaces + 1;
    *count = total;
    char **arguments = (char **)operator new(total * sizeof(char *));
    unsigned index = 0;
    arguments[0] = command;
    unsigned slot = 1;
    for (--total; total; ++index)
    {
        if (!command[index])
        {
            arguments[slot++] = command + index + 1;
            --total;
        }
    }
    return arguments;
}

#include <stdlib.h>

// LIBRARY: GAME 0x006429f0
// _atoi

extern bool g_unk0x006c0686;

extern char g_unk0x6c0691;
// GLOBAL: GAME 0x006c0696
bool g_unk0x006c0696;
// GLOBAL: GAME 0x006c0697
bool g_unk0x006c0697;
// GLOBAL: GAME 0x006c0698
bool g_unk0x006c0698;
// GLOBAL: GAME 0x006c069a
bool g_unk0x006c069a;
// GLOBAL: GAME 0x006c069e
short g_unk0x006c069e;

// FUNCTION: GAME 0x00409d70
bool FUN_00409d70(char **arguments, unsigned *index, unsigned)
{
    unsigned position = *index;
    const char *argument = arguments[position];
    if (strcmp(argument,
        // STRING: GAME 0x006a7030
        "-NOSCRIPT") == 0)
    {
        g_unk0x6c0691 = 0;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a7020
        "-SOUNDDEVICE") == 0)
    {
        g_unk0x006c069e = atoi(arguments[position + 1]);
        *index += 2;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a7010
        "-CHECKSOUNDDATA") == 0)
    {
        g_unk0x006c0686 = true;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6ffc
        "-GENERATESKIPDATA") == 0)
    {
        g_unk0x006c0696 = true;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6ff4
        "-SETREG") == 0)
        goto setReg;
    if (strcmp(argument,
        // STRING: GAME 0x006a6fe4
        "-GETMAJORVER") == 0)
    {
        g_unk0x006c0580.m_versionMode = 1;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6fd4
        "-GETMINORVER") == 0)
    {
        g_unk0x006c0580.m_versionMode = 2;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6fc4
        "-GETBUILRHER") == 0)
    {
        g_unk0x006c0580.m_versionMode = 3;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6fb8
        "-SIMULATE") == 0)
    {
        g_unk0x006c0698 = true;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6fa8
        "-EXTRACTHUNK") == 0)
    {
        FUN_004096b0();
setReg:
        g_unk0x006c0697 = true;
        ++*index;
        return true;
    }
    if (strcmp(argument,
        // STRING: GAME 0x006a6f9c
        "-GAMEPAD") == 0)
    {
        g_unk0x006c069a = true;
        ++*index;
        return true;
    }
    return false;
}

// Parked: launcher reconstruction still lacks verified engine helpers, switches and slideshow flow.
// Reconstructed body and analysis: docs/notes/launcher_0x0040a230_*.
// STUB: GAME 0x0040a230
int __stdcall FUN_0040a230(HINSTANCE, HINSTANCE, char *, int)
{
    return 0;
}

#include <list>

// FUNCTION: GAME 0x0040bc30
void RHUnk0040bc30::FUN_0040bc30()
{
    typedef std::list<std::string> Strings;
    ((Strings *)this)->~Strings();
}

// TEMPLATE: GAME 0x0040bcc0
// ?clear@?$list@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEXXZ

void EmitLauncherStringList(const std::allocator<std::string> &allocator)
{
    typedef std::list<std::string> Strings;
    Strings *strings = new Strings(allocator);
    void (Strings::*clear)() = &Strings::clear;
    (strings->*clear)();
    delete strings;
}
