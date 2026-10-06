// RHSequenceElement.cpp — translation unit with __FILE__ evidence at 0x005852c0
// ("P:\Robin Hood\RHsequenceelement.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005852c0 -> RHSequenceElement::SerializeStaticStuff(SBFile&)):
//   - TU:        rhsequenceelement.cpp (embedded __FILE__ string 0x006b74b4).
//   - Class:     RHSequenceElement (symbols/oracle-correlation.tsv:
//                rhsequenceelement -> class RHSequenceElement, 36 methods).
//   - Signature: RHSequenceElement::SerializeStaticStuff(SBFile&)
//                (symbols/mac-RH.txt; zeta-robin.txt
//                SerializeStaticStuff__17RHSequenceElementR6SBFile).
//   - Signals:
//       * the function writes the type-name tag
//         "RHSequenceElement::SerializeStaticStuff" (string 0x006b74fc) as its
//         first act via the 0x005e1b70 helper;
//       * a single SBFile::Access check on the 4-byte global 0x006b74d8, then
//         the "Serialize failed reason is %s" assert idiom — a serializer with
//         no loop, no `new`, no base call;
//       * the body never uses ecx as `this` (arg is `[esp+8]`), so Windows
//         emits it as a static member — declared `static` here.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "RHSequenceElement.h"

// The 4-byte global read/written by SerializeStaticStuff (original 0x006b74d8).
// GLOBAL: GAME 0x006b74d8
int g_unk0x6b74d8;

// FUNCTION: GAME 0x005852c0
bool RHSequenceElement::SerializeStaticStuff(SBFile &file)
{
    // STRING: GAME 0x6b74fc
    RHSerializeName(file, "RHSequenceElement::SerializeStaticStuff");

    if (file.Access(&g_unk0x6b74d8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b74b4
                 "P:\\Robin Hood\\RHsequenceelement.cpp",
                 172,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps SerializeStaticStuff in the build.
void RHSequenceElement::Emit(SBFile &file)
{
    SerializeStaticStuff(file);
}
