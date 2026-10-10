// RHOrder.cpp — translation unit with __FILE__ evidence at 0x0054e9a0
// ("P:\Robin Hood\RHorder.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0054e750 -> RHOrder::Serialize(SBFile&, RHSequenceElement*)):
//   - TU:        rhorder.cpp (embedded __FILE__ string 0x006b1360).
//   - Class:     RHOrder (symbols/oracle-correlation.tsv: rhorder -> class
//                RHOrder, 14 methods).
//   - Signature: RHOrder::Serialize(SBFile&, RHSequenceElement*)
//                (symbols/mac-RH.txt).
//   - Signals:
//       * the function writes the type-name tag "RHOrder" (string 0x006b137c)
//         via the 0x005e1b70 helper;
//       * a real __thiscall: `mov edi,ecx` at entry, `ret 8` at exit, two stack
//         args (file -> esi, element -> later stored to this+0x38);
//       * a file.m_bLoading block that links `this` into the singleton list at
//         g_unk0x6c1040+0x148 (callee 0x00424410, ecx = that list);
//       * a chain of SBFile::Access checks on fields +0x24/+0x28/+0x2a/+0x2b/
//         +0x2c/+0x29/+0x2d/+0x04/+0x34 with the "Serialize failed reason is %s"
//         assert idiom;
//       * three tail serialisations (+0x14, +0x8, +0x1c) and the engine's
//         SerializeElementPointer on +0x30, then `this+0x38 = element`.
//
// BINDING (0x0054e9a0 -> RHOrder::SerializeStaticStuff(SBFile&)):
//   - Signals:
//       * the function writes the type-name tag "RHOrder::SerializeStaticStuff"
//         (string 0x006b1384) as its first act via the 0x005e1b70 helper;
//       * a single SBFile::Access check on the 4-byte global 0x006c0c6c, then
//         the "Serialize failed reason is %s" assert idiom — a serializer with
//         no loop, no `new`, no base call;
//       * the body never uses ecx as `this` (arg is `[esp+8]`), and the only
//         caller (0x0058a9c0) does not set ecx before the call, so Windows
//         emits it as a static member — declared `static` here.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHOrder.h"

// The global pointer at 0x006c1040 (singleton walking the interpreter's lists).
// GLOBAL: GAME 0x006c1040
RHUnk6c1040 *g_unk0x6c1040;

// The 4-byte global read/written by SerializeStaticStuff (original 0x006c0c6c).
// GLOBAL: GAME 0x006c0c6c
int g_unk0x6c0c6c;

// FUNCTION: GAME 0x0054e750
bool RHOrder::Serialize(SBFile &file, RHSequenceElement *element)
{
    // STRING: GAME 0x6b137c
    RHSerializeName(file, "RHOrder");

    if (file.m_bLoading)
    {
        RHUnkList &list = g_unk0x6c1040->m_148;
        RHUnkIter it = list.insert(list.end(), this);
        list.m_flag10 = 1;
    }

    if (file.Access(&m_24, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 98, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_28, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 99, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2a, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 100, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2b, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 101, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 102, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_29, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 103, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2d, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 104, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 105, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_34, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHorder.cpp", 106, "Serialize failed reason is %s", reason);
        return false;
    }

    m_14.Serialize(file);
    m_8.Serialize(file);
    m_1c.Serialize(file);
    g_pEngine->SerializeElementPointer(file, m_30);

    m_38 = element;
    return true;
}

// FUNCTION: GAME 0x0054e9a0
bool RHOrder::SerializeStaticStuff(SBFile &file)
{
    // STRING: GAME 0x6b1384
    RHSerializeName(file, "RHOrder::SerializeStaticStuff");

    if (file.Access(&g_unk0x6c0c6c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b1360
                 "P:\\Robin Hood\\RHorder.cpp",
                 137,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps both serialisers in the build.
void RHOrder::Emit(SBFile &file)
{
    Serialize(file, 0);
}
