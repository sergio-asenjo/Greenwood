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

// Sort view of an element for the minimap's element comparator FUN_00549ae0,
// which the RHEngine element sort calls. The target reads the 4-byte type word
// at +0x4, the creation id at +0xc and the sprite pointer at +0x50, and orders
// by the float weight at +0x1c4 of that sprite. Mirrors RHElement's layout
// (RHElement.h); RHElement itself stays the authoritative declaration.
struct RHMinimapSortWeight
{
    undefined m_00[0x1c4]; // 0x00
    float m_1c4;           // 0x1c4
};

struct RHMinimapSortElement
{
    undefined m_00[4];         // 0x00
    unsigned m_04;             // 0x04
    undefined m_08[4];         // 0x08
    unsigned m_0c;             // 0x0c
    undefined m_10[0x40];      // 0x10
    RHMinimapSortWeight *m_50; // 0x50
};

// Element ordering predicate (target 0x00549ae0): `this`-less, two pointer
// arguments and a plain `ret`, so a free function. Ordering key: a category
// word built from four masked tests of the type word, then the sprite weight,
// then the creation id.
bool FUN_00549ae0(const RHMinimapSortElement *a, const RHMinimapSortElement *b);

class RHMinimap
{
public:
    // Windows codegen hands this NO `this` and returns with a plain `ret`
    // (caller cleans the two stack args, `add esp,0x8` at 0x0054999b), so on
    // this build it is a static member — the same shape as
    // RHOrder::SerializeStaticStuff and RHMenuDialogue::GetDialogue.
    static bool SerializeHighlightedElement(SBFile &file, RHMinimapHighlightedElement &element);

    // Parked at 0x00549ae0's sibling run. Argument counts come from each
    // target's `ret N`; the argument types stay neutral because the owning
    // widget base class is not established (see the parks in RHMinimap.cpp).
    bool FUN_00549c10(const void *name, const void *box, unsigned long flags); // ret 0xc
    bool FUN_00549e00(const void *point);                                      // ret 4
    void FUN_00549f50();                                                       // ret
    void FUN_0054a0f0(const void *arg);                                        // ret 4
    void FUN_0054a440(const void *element);                                    // ret 4
    void FUN_0054a640(const void *arg);                                        // ret 4
    void FUN_0054a920();                                                       // ret
    bool FUN_0054ae90(RHElement *element);
};
