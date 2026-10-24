// RHUIRendererPortrait — declarations for RHUIRendererPortrait.cpp (decompiled TU).
//
// BINDING (0x005cbbe0 -> RHUIRendererPortrait::BlitPicture(SBResourceWidgetID, float)):
//   - TU:     rhuirendererportrait.cpp (embedded __FILE__ 0x006b8ccc,
//             symbols/functions-by-file.tsv:406).
//   - Class:  RHUIRendererPortrait (symbols/oracle-correlation.tsv:88:
//             rhuirendererportrait -> class RHUIRendererPortrait, 7 methods).
//   - Method: the Mac map has exactly one rhuirendererportrait.cpp method,
//             BlitPicture (symbols/mac-functions-by-file.tsv:414), and
//             symbols/mac-RH.txt:4502 gives
//             RHUIRendererPortrait::BlitPicture(SBResourceWidgetID, float).
//   - Signal: `this` arrives in ecx; the function ends in `ret 0x8`, i.e. two
//             stack arguments. The first is a 4-byte widget ID (loaded from
//             [esp+0xc] after the prologue), the second a float (fld [esp+8]).
//             The body scales the float by the .rdata constant 100.0f, converts
//             it to an int via the CRT `_ftol` helper, resolves a surface through
//             a resource manager at this+4 and either blits it directly (100%)
//             or through a draw-manager path — matching the signature above.
//
// Member layout is derived from the target instructions of
// RHUIRendererPortrait::BlitPicture (0x005cbbe0). Everything is opaque padding;
// the touched fields are reached through the offset aliases below, and each
// engine sub-object has its own provisional class so its `__thiscall` call
// shape is reproduced.
//
// The engine sub-object classes stay provisional (no __FILE__, tag or string
// names them) and their method identities are unproven; the class names are the
// addresses of the out-of-line targets in Game.exe.

#include "SB.h"

// Target 0x00600820, __FILE__ 0x006bb368 ("P:\Robin Hood\SBLibNG\SBResourceManager.cpp").
// Called as `mov ecx,[esi+0x4]` with three stack arguments:
//   [esi+0x38] (a surface/handle), the widget ID, and &float (out/in).
// Signature from the target `ret 0xc` (three stack args, __thiscall) and the
// `cmp al,1 / jne` on its return value (bool).
#ifndef RHUNK00600820_VIEW
#define RHUNK00600820_VIEW
class RHUnk00600820
{
public:
    bool ResolveSurface(void *surface, unsigned int id, float *value);
};
#endif

// Target 0x005e6440 and 0x005eaa40, both __FILE__ 0x006b9264
// ("P:\Robin Hood\SBLibNG\SBDrawManager.cpp"). Called as `mov ecx,[esi+0x1c]`;
// BlitFull pushes five stack arguments (target `ret 0x14`) and BlitScaled six
// (target `ret 0x18`), both returning bool in `al`. The float frame value is
// passed by value (target `mov ecx,[esp+0x14]; push ecx`), unlike the resource
// lookup which takes its address. They are two entries of the same draw-manager
// sub-object.
class RHUnk005e6440
{
public:
    bool BlitFull(float f, int a, int b, void *widget, int c);
    bool BlitScaled(float f, int a, int b, void *widget, int frame, int c);
};

class RHUIRendererPortrait
{
public:
    bool BlitPicture(unsigned int id, float f);

    void Emit();

    // Total size is irrelevant: the fields the matched function touches are
    // reached through the offset aliases below.
    char m_bytes[0x40];
};

// Resource manager sub-object pointer (target `mov ecx,[esi+0x4]`).
#define m_resource (*(RHUnk00600820 **)((char *)this + 0x4))

// Renderable sub-object passed by its address (target `lea eax,[esi+0x8]`).
#define m_widget (*(char *)((char *)this + 0x8))

// Draw manager sub-object pointer (target `mov ecx,[esi+0x1c]`).
#define m_draw (*(RHUnk005e6440 **)((char *)this + 0x1c))

// Surface/handle resolved for the portrait (target `mov edx,[esi+0x38]`).
#define m_surface (*(void **)((char *)this + 0x38))

// The .rdata multiplier applied to the float argument (target `fmul ds:0x67755c`,
// a 100.0f constant). It needs named storage or reccmp cannot resolve the operand
// (Hard rule 26). The definition and // GLOBAL: marker live in the .cpp.

// VC6's float->int CRT helper. Defined once, with a // LIBRARY: seed, in
// RHMenuGraphics_stubs.cpp; this TU only declares it (a second definition would
// be a duplicate symbol). The symbol must be `_ftol`, not `__ftol` (Hard rule 7).
extern "C" __int64 _ftol();
