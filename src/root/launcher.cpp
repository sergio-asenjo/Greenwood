#include "SBNullstr.h"
#include "launcher.h"

// Parked: this is the WinMain/_SDL_main entry point. Its real body calls Win32/User32 imports
// (LoadIconA, MessageBoxA, ShowCursor, SystemParametersInfoA, …) plus many engine helpers; the
// fixed link line (rule 17, no linker changes) cannot resolve user32, so a real body cannot link.
// Reconstructed body and analysis: docs/notes/launcher_0x0040a230_*.
// STUB: GAME 0x0040a230
int __stdcall FUN_0040a230(HINSTANCE, HINSTANCE, char *, int)
{
    return 0;
}
