// RHMinimap — declarations shared by RHMinimap.cpp (the decompiled TU) and
// RHMinimap_stubs.cpp (external-symbol stubs).
//
// BINDING (0x00549a80): RHMinimap::SerializeHighlightedElement(
// SBFile&, RHMinimap::HighlightedElement&). See src/RHMinimap.cpp for the
// evidence chain.
//
// Layout of RHMinimap::HighlightedElement: the caller 0x00549650 walks a
// vector of 8-byte elements (`add ebx,0x8`, 0x005499a9), passing `&element`
// to this function. The function then hands +0x0 (an RHElement pointer) to
// RHEngine::SerializeElementPointer and serialises a single byte at +0x4.

#include "SB.h"

class RHElement;

struct RHMinimapHighlightedElement
{
    RHElement *m_element; // [0x0] resolved element pointer
    char m_0c;            // [0x4] one serialised byte
};

// The engine singleton's pointer-array serializer. Target 0x004c3a10: a
// non-virtual RHEngine member (`ecx = *(void**)0x006c0a88`) taking
// (SBFile&, T*&). It gates on the load/save flag `[file+4]`, accesses 4 bytes
// and, when reading, resolves an id via the engine array at +0x48d8
// (lookup 0x004622e0: search begin/end at +4/+8, match key [elem+0xc]).
// The Windows binary contains seven byte-identical instantiations of the Mac
// template family `RHEngine::SerializeElementPointer(SBFile&, T*&)`
// (symbols/mac-RH.txt), which are indistinguishable at code level; the base
// instantiation `SerializeElementPointer(SBFile&, RHElement*&)` is used here
// and is PROVISIONAL with respect to the specific element type only.
#include "RHEngine.h"

extern RHEngine *g_pEngine;

class RHMinimap
{
public:
    // Windows codegen hands this NO `this` and returns with a plain `ret`
    // (caller cleans the two stack args, `add esp,0x8` at 0x0054999b), so on
    // this build it is a static member — the same shape as
    // RHOrder::SerializeStaticStuff and RHMenuDialogue::GetDialogue.
    static bool SerializeHighlightedElement(SBFile &file, RHMinimapHighlightedElement &element);
};
