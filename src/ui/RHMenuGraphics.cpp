// RHMenuGraphics.cpp — translation unit with __FILE__ evidence at 0x0052d090
// ("P:\Robin Hood\RHMenuGraphics.cpp", symbols/functions-by-file.tsv:129).
//
// BINDING (0x0052d090 -> RHMenuGraphics::SynchronizeWidgets()):
//   - TU:     rhmenugraphics.cpp (__FILE__ 0x006b0d5c).
//   - Class:  RHMenuGraphics (symbols/oracle-correlation.tsv).
//   - Method: the single rhmenugraphics.cpp method in the Mac map
//             (symbols/mac-functions-by-file.tsv:127 -> SynchronizeWidgets;
//             symbols/mac-RH.txt:2825 RHMenuGraphics::SynchronizeWidgets()).
//   - Signal: `this` in ecx, no stack argument, plain `ret` => __thiscall void.
//             The body converts the screen width at +0xdc0 to int, switches on
//             640/800/1024 (asserting "Warning, unknown screen resolution."
//             otherwise) and re-synchronises seven widget enable states.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.
//
// CODEGEN (why the widget helper is an inline method, not a stub):
//   The five `SetEnable(true)`/bool-flag sites are expanded inline while the
//   last two (m_widgetC/m_widgetD) are emitted as calls to the out-of-line copy
//   at 0x0052d2c0. Defining SetEnable in the class body reproduces exactly that
//   split: VC6 inlines five sites and emits the sixth/seventh as calls, the
//   out-of-line copy landing adjacent to SynchronizeWidgets as in the original.

#include "SBNullstr.h"
#include "RHMenuGraphics.h"

// FUNCTION: GAME 0x0052d090
void RHMenuGraphics::SynchronizeWidgets()
{
    int width = (int)m_screenWidth;

    switch (width)
    {
    case 640:
        m_widget640.SetEnable(true);
        break;

    case 800:
        m_widget800.SetEnable(true);
        break;

    case 1024:
        m_widget1024.SetEnable(true);
        break;

    default:
        SBAssert(0,
                 // STRING: GAME 0x6b0d5c
                 "P:\\Robin Hood\\RHMenuGraphics.cpp",
                 338,
                 // STRING: GAME 0x6b0d80
                 "Warning, unknown screen resolution.");
        break;
    }

    m_widgetA.SetEnable(m_flagDBE == false);
    m_widgetB.SetEnable(m_flagDBD);
    m_widgetC.SetEnable(m_flagDBF);
    m_widgetD.SetEnable(m_flagDBC);
}

// Force emission: an unreferenced non-virtual member is dropped by VC6, so an
// out-of-line call from a global instance keeps SynchronizeWidgets in the build.
void RHMenuGraphics::Emit()
{
    SynchronizeWidgets();
}

RHMenuGraphics g_rhMenuGraphics;

void rh_menugraphics_emit()
{
    g_rhMenuGraphics.Emit();
}
