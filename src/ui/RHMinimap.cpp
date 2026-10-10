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

// Force emission: a non-inline static member defined here is emitted into the
// object; this out-of-line call keeps RHMinimap::SerializeHighlightedElement in
// the build.
void RHMinimapEmit(SBFile &file, RHMinimapHighlightedElement &element)
{
    RHMinimap::SerializeHighlightedElement(file, element);
}
