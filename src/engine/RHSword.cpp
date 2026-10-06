// RHSword.cpp — translation unit with __FILE__ evidence at 0x005c1ff0
// ("P:\Robin Hood\RHSword.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005c1ff0):
//   - TU:        RHSword.cpp (embedded __FILE__ string 0x006b8bbc).
//   - Class:     RHSword (symbols/oracle-correlation.tsv: rhsword -> RHSword).
//   - Signature: RHSword::SerializePointer(SBFile&, RHSword*&). Signals:
//       * arg2 is a pointer-to-pointer (dereferenced and stored through);
//       * arg1 drives the file: byte +4 selects read/write, and
//         Access(void*, int) / GetError() are __thiscall on it;
//       * the read path does `new RHSword` (ctor 0x5c1b00, vtable 0x679e48
//         slot 0 = RHSword::Serialize 0x5c1fd0) then calls its virtual
//         Serialize(SBFile&) — exactly a RHSword*&.
//   - Corroboration: 0x00450370 in RHBow.cpp is byte-identical except for the
//     __FILE__/line/ctor, i.e. RHBow::SerializePointer(SBFile&, RHBow*&).
//
// NOTE: RHSword's ctor/dtor/serializer and the file/assert stubs are
// deliberately defined in a separate TU (RHSword_stubs.cpp). VC6 emits the
// `new`-cleanup C++ EH frame only while the destructor body is not visible at
// the call site; defining it here makes VC6 elide the frame.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "RHSword.h"

// FUNCTION: GAME 0x005c1ff0
bool RHSword::SerializePointer(SBFile &file, RHSword *&ptr)
{
    bool exists;

    if (!file.m_bLoading)
    {
        exists = (ptr != 0);
        if (file.Access(&exists, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars
                                     ? err->m_chars
                                     // STRING: GAME 0x6773d0
                                     : "";
            SBAssert(0,
                     // STRING: GAME 0x6b8bbc
                     "P:\\Robin Hood\\RHSword.cpp",
                     365,
                     // STRING: GAME 0x6a7390
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }
        if (exists)
            return ptr->Serialize(file);
        return true;
    }

    if (file.Access(&exists, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSword.cpp", 376, "Serialize failed reason is %s", reason);
        return false;
    }
    if (exists)
    {
        ptr = new RHSword;
        return ptr->Serialize(file);
    }
    return true;
}
