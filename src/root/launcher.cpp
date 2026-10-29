#include "SBNullstr.h"
#include "launcher.h"
#include "SBInput.h"
#include "SBDrawManager.h"
#include "RHGameInputTranslator.h"
#include "RHGameActionCalls.h"
#include "RHUnk005ef320WindowView.h"

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
