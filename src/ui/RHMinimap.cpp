// RHMinimap.cpp — translation unit with __FILE__ evidence at 0x00549a80
// ("P:\\Robin Hood\\RHminimap.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x00549a80 -> RHMinimap::SerializeHighlightedElement(
//                     SBFile&, RHMinimap::HighlightedElement&)):
//   - TU:        rhminimap.cpp (embedded __FILE__ string 0x006b11b8,
//                referenced by this function and its caller 0x00549650).
//   - Class:     RHMinimap (symbols/oracle-correlation.tsv:
//                rhminimap -> class RHMinimap, 30 methods).
//   - Signature: RHMinimap::SerializeHighlightedElement(
//                SBFile&, RHMinimap::HighlightedElement&)
//                (symbols/mac-RH.txt line 3106 and
//                symbols/mac-functions-by-file.tsv line 131).
//   - Signals:
//       * the argument shape is two stack args and NO `this`: the callee
//         loads file from [esp+8] (-> esi, drives Access/GetError) and
//         element from [esp+0xc] (-> edi, advanced by +4). The caller
//         0x00549650 pushes (file, element) with no `mov ecx,this`, so this
//         is a non-`this`-call — the two-arg member serialiser the Mac map
//         names SerializeHighlightedElement;
//       * the first act is `mov ecx,*(void**)0x006c0a88; push &element;
//         push file; call 0x004c3a10` — the RHEngine singleton's
//         SerializeElementPointer (0x004c3a10 lives in rhengine.cpp,
//         symbols/functions-by-file.tsv) called with (SBFile&, RHElement*&),
//         result discarded;
//       * the remaining access is a single 1-byte SBFile::Access on
//         `&element[+4]` (assert line 153 = 0x99), returning true on success
//         and the assert path (empty fallback 0x006773d0, format 0x006a7390)
//         on failure — the exact serializer idiom seen in RHGraphicConfig;
//       * the caller walks an 8-byte vector element (`add ebx,0x8`,
//         0x005499a9) and passes its base as `element`, so +0x0 is an
//         RHElement* and +0x4 is the serialised char — consistent with the
//         macro definition.
//
// The `// STRING:` marker pins this TU's own __FILE__ literal to its original
// Game.exe address: the original is a fixed-base EXE, so its absolute string
// pointers carry no relocation records and reccmp cannot discover them by
// scanning. The shared "" (0x006773d0) and "Serialize failed reason is %s"
// (0x006a7390) are annotated once in src/RHSword.cpp; this function's
// references resolve to the same pooled entities.

#include "SBNullstr.h"
#include "RHMinimap.h"
#include "../engine/SBUIRenderer.h"

bool FUN_0054ae80(const RHMinimapHighlightedElement &element);

extern RHMinimap *g_unk0x6c0c50;
class RHMapResources;
extern RHMapResources *g_unk0x006c1840;

// FUNCTION: GAME 0x005493e0
RHMinimap::RHMinimap() : m_dc(0), m_e0(false)
{
    *(unsigned *)this = 0x00679b70;
    m_120 = false;
    m_124 = 0;
    g_unk0x6c0c50 = this;
    m_128 = 0;
    m_visible = true;
    m_b0 = false;
    m_b1 = false;
    m_122 = false;
    m_e1 = false;
    m_b2 = false;
}

// FUNCTION: GAME 0x00549510
void *RHMinimap::FUN_00549510(unsigned flags)
{
    this->~RHMinimap();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00549530
RHMinimap::~RHMinimap()
{
    *(unsigned *)this = 0x00679b70;
    ((SBUIUnk005fd4a0 *)g_unk0x006c1840)->FUN_005fd4a0(0x3d);
}

// FUNCTION: GAME 0x00549a80
bool RHMinimap::SerializeHighlightedElement(SBFile &file, RHMinimapHighlightedElement &element){
    g_pEngine->SerializeElementPointer(file, element.m_element);

    if (file.Access(&element.m_0c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b11b8
                 "P:\\Robin Hood\\RHminimap.cpp",
                 153,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return true;
}

// FUNCTION: GAME 0x00549ae0
bool FUN_00549ae0(const RHMinimapSortElement *a, const RHMinimapSortElement *b){
    unsigned ka;
    {
        unsigned v = a->m_04;
        bool t2 = (v & 0x3) == 0x3;
        bool t3 = (v & 0xf) == 0xc;
        bool t4 = (v & 7) == 0;
        ka = ((((t2 << 1 | t3) << 1 | (bool)((v & 0x1f) == 0x14)) << 1 |
               (bool)((v & 0x1f) == 0x14))
                  << 2 |
              t4)
             << 11;
    }
    unsigned kb;
    {
        unsigned v = b->m_04;
        bool t2 = (v & 0x3) == 0x3;
        bool t3 = (v & 0xf) == 0xc;
        bool t4 = (v & 7) == 0;
        kb = ((((t2 << 1 | t3) << 1 | (bool)((v & 0x1f) == 0x14)) << 1 |
               (bool)((v & 0x1f) == 0x14))
                  << 2 |
              t4)
             << 11;
    }
    if (ka > kb)
    {
        return false;
    }
    if (ka < kb)
    {
        return true;
    }
    float fa = a->m_50->m_1c4;
    float fb = b->m_50->m_1c4;
    if (fa != fb)
    {
        float ga = a->m_50->m_1c4;
        float gb = b->m_50->m_1c4;
        return ga < gb;
    }
    return a->m_0c < b->m_0c;
}

// Parked: the body is the widget's Create — it calls the unmodelled widget base
// class (vtable slot +0x24, 0x61a1e0/0x61ad20) and its resource/geometry helper
// set, none of which this TU can establish from its own evidence.
// STUB: GAME 0x00549c10
bool RHMinimap::FUN_00549c10(const void *, const void *, unsigned long)
{
    return false;
}

// Parked: same widget base dependency (0x61ad20, 0x600920, virtual +0x24), plus
// an EH frame with three local-object states.
// STUB: GAME 0x00549e00
bool RHMinimap::FUN_00549e00(const void *)
{
    return false;
}

// Parked: same widget base dependency (0x54b150, 0x6090d0/0x609200 geometry and
// the +0x120/+0xe0/+0xe4 members), none of which this TU establishes.
// STUB: GAME 0x00549f50
void RHMinimap::FUN_00549f50()
{
}

// Parked: same widget base dependency (static std::string globals 0x6c0c58 /
// 0x6c0e48 and the 0x5fc0xx/0x608f10 helper family).
// STUB: GAME 0x0054a0f0
void RHMinimap::FUN_0054a0f0(const void *)
{
}

// Parked: VC6 vector-insert specialisation over the 8-byte HighlightedElement
// vector at +0xcc; the _Insert_n branch layout and 0x54ae90 helper differ.
// STUB: GAME 0x0054a440
void RHMinimap::FUN_0054a440(const void *)
{
}

// Parked: same widget base dependency (the +0x90 list, virtual +0x24/+0x44 and
// the 0x60xxxx helper family).
// STUB: GAME 0x0054a640
void RHMinimap::FUN_0054a640(const void *)
{
}

// Parked: same widget base dependency (0x61ad20, 0x54b1f0 and the +0x120/+0xe4/
// +0x10c members); the x87 box scaling cannot be reconstructed without the base.
// STUB: GAME 0x0054a920
void RHMinimap::FUN_0054a920()
{
}

// FUNCTION: GAME 0x0054ae80
bool FUN_0054ae80(const RHMinimapHighlightedElement &element)
{
    return element.m_0c == 0;
}

// FUNCTION: GAME 0x0054ae90
bool RHMinimap::FUN_0054ae90(RHElement *element)
{
    RHMinimapHighlightedElement *entry = *(RHMinimapHighlightedElement **)((char *)this + 0xd0);
    RHMinimapHighlightedElement *end = *(RHMinimapHighlightedElement **)((char *)this + 0xd4);
    for (; entry != end; ++entry)
    {
        if (entry->m_element == element)
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0054b490
void RHMinimap::FUN_0054b490(const RHMinimapHighlightedElement &element)
{
    if (element.m_0c == 1)
    {
        RHMinimapSortElement *entry = (RHMinimapSortElement *)element.m_element;
        g_unk0x6c0c50->FUN_0054b5e0(*(SBGeoPoint2D *)((char *)entry->m_50 + 0x24), 0x12);
    }
}

#include <algorithm>

class RHUnk0054b150
{
public:
    void FUN_0054b150(bool flag, bool immediate);
};

// FUNCTION: GAME 0x0054b4c0
void RHMinimap::FUN_0054b4c0()
{
    if (m_dc == 0 && !m_highlighted.empty())
    {
        RHMinimapHighlightedElement *entry = std::find_if(m_highlighted.begin(), m_highlighted.end(), &FUN_0054ae80);
        if (entry != m_highlighted.end())
        {
            unsigned remaining = m_highlighted.end() - entry - 1;
            entry->m_0c = 1;
            if (remaining >= 1)
                m_dc = 25;
            else if (m_e0 || remaining == 0)
                m_dc = 50;
        }
        else
        {
            m_highlighted.clear();
            if (m_e0)
            {
                m_e0 = false;
                ((RHUnk0054b150 *)this)->FUN_0054b150(false, false);
            }
        }
    }
    if (m_dc != 0)
        --m_dc;
    std::for_each(m_highlighted.begin(), m_highlighted.end(), &RHMinimap::FUN_0054b490);
}

// Force emission: a non-inline static member defined here is emitted into the
// object; this out-of-line call keeps RHMinimap::SerializeHighlightedElement in
// the build.
void RHMinimapEmit(SBFile &file, RHMinimapHighlightedElement &element)
{
    RHMinimap::SerializeHighlightedElement(file, element);
    FUN_0054ae80(element);
}

// Force emission of the element comparator (nothing in this build calls it).
void RHMinimapSortEmit(RHMinimapSortElement *a, RHMinimapSortElement *b)
{
    FUN_00549ae0(a, b);
}

void RHMinimapHighlightEmit(RHMinimap *minimap, RHElement *element)
{
    minimap->FUN_0054ae90(element);
}
