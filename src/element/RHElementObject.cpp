// RHElementObject.cpp — translation unit with __FILE__ evidence at 0x004b2190
// ("P:\Robin Hood\RHelementobject.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x004b2190 -> RHElementObject::Serialize(SBFile&)):
//   - TU:        rhelementobject.cpp (embedded __FILE__ string 0x006aed04,
//                referenced only by this function at 0x004b2360).
//   - Class:     RHElementObject (symbols/oracle-correlation.tsv:
//                rhelementobject -> class RHElementObject, 23 methods).
//   - Signature: RHElementObject::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * the function writes the type-name tag "RHElementObject" (string
//         0x006aed28) as its very first act via the 0x005e1b70 helper — the
//         name matches the class the TU is known to contain;
//       * every field access goes through SBFile::Access 0x005f52b0 /
//         SBFile::GetError 0x005f5f30 and the "Serialize failed reason is %s"
//         assert pattern (format 0x006a7390, empty fallback 0x006773d0) — the
//         exact serializer idiom seen in RHSword::SerializePointer;
//       * the final act is a direct call to 0x00462330, which itself begins by
//         writing the tag "RHElement" (string 0x006ae088) — i.e. the base
//         RHElement::Serialize is invoked last;
//       * 0x004b2190 occupies vtable slot 0 of the class (vtable 0x006781c4:
//         [0]=0x004b2190, [4]=0x004b23a0 = SetObjectType), so it is the first
//         virtual — consistent with an overridden Serialize;
//       * the same TU's neighbour 0x004b2010 is RHElementObject::Create
//         (Mac signature Create(bool, RHElementObject const&)), which copies
//         into the very offsets (+0xad, +0xb0, +0xb8) this function serialises.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHElementObject.h"

// FUNCTION: GAME 0x004b2190
bool RHElementObject::Serialize(SBFile &file)
{
    // STRING: GAME 0x6aed28
    RHSerializeName(file, "RHElementObject");

    if (file.Access(&m_ac, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // NOTE: the empty string 0x006773d0 and the format
        // "Serialize failed reason is %s" (0x006a7390) are the same original
        // entities used by RHSword::SerializePointer; reccmp allows exactly one
        // marker per original address (parser.codebase.prune_reused_addrs), so
        // those two are annotated once in src/RHSword.cpp. This function's
        // reference resolves to the same pooled entities.
        SBAssert(0,
                 // STRING: GAME 0x6aed04
                 "P:\\Robin Hood\\RHelementobject.cpp",
                 177,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_fe, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 178, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_ae, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 179, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 180, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 181, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_a8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 182, "Serialize failed reason is %s", reason);
        return false;
    }

    m_member.Serialize(file);

    if (file.Access(&m_fc, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 186, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_fd, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 187, "Serialize failed reason is %s", reason);
        return false;
    }

    return RHElement::Serialize(file);
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementObject::Serialize in the build.
void RHElementObject::Emit(SBFile &file)
{
    Serialize(file);
}
