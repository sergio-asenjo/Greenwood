// RHMessenger.cpp — translation unit with __FILE__ evidence at 0x005472d0
// ("P:\Robin Hood\RHMessenger.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005472d0 -> RHMessenger::Serialize(SBFile&)):
//   - TU:        rhmessenger.cpp (embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger (symbols/oracle-correlation.tsv:
//                rhmessenger -> class RHMessenger, 25 methods).
//   - Signature: RHMessenger::Serialize(SBFile&) (symbols/mac-RH.txt:3082).
//   - Signals:
//       * the first act writes the tag "RHMessenger" (string 0x006b11ac) via
//         0x005e1b70 — the name matches the TU's class;
//       * a run of SBFile::Access checks at +0x1a/1 (line 873), +0x28/1 (876),
//         +0x2a/2 (877), +0xa2/2 (880), each with the "Serialize failed reason
//         is %s" idiom;
//       * a `file.m_version >= 0x11` gate: the read path Accesses +0x17/1 at
//         line 884, the below-version path stores 0 into the +0x17 byte;
//       * the file.m_bLoading gate (mov al,[esi+4]; test; je) then calls
//         0x00547560 on `this` in BOTH paths; on the loading path a
//         `file.m_version >= 0x2a` gate guards a final Access of a 1-byte
//         stack local at line 900;
//       * no loop and no `new`.
//
// BINDING (0x00547460 -> RHMessenger::SerializeLockUser(SBFile&)):
//   - TU:        rhmessenger.cpp (same embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger; the Mac map's rhmessenger.cpp lists exactly two
//                methods, Serialize and SerializeLockUser
//                (symbols/mac-functions-by-file.tsv:128-129); Serialize is
//                already bound above, so the remaining __FILE__ function is
//                SerializeLockUser.
//   - Signals:   the body serialises the "lock user" flag at this+0x23; on the
//                loading path a fetched byte that differs from +0x23 dispatches
//                a lock/unlock action carrying the 0x1c/0x1d constant selected
//                by `byte == 0`; on the saving path it writes +0x23 directly.
//                Both Access failures use the "Serialize failed reason is %s"
//                idiom at lines 924 / 935.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "RHMessenger.h"

// FUNCTION: GAME 0x005472d0
bool RHMessenger::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b11ac
    RHSerializeName(file, "RHMessenger");

    if (file.Access(&m_unk1a, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b118c
                 "P:\\Robin Hood\\RHMessenger.cpp",
                 873,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_unk28, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 876, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unk2a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 877, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unka2, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 880, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.m_version >= 0x11)
    {
        if (file.Access(&m_unk17, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 884, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        m_unk17 = 0;
    }

    if (file.m_bLoading)
    {
        Reset();

        if (file.m_version < 0x2a)
        {
            char scratch;
            if (file.Access(&scratch, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 900, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        Reset();
    }

    return true;
}

// FUNCTION: GAME 0x00547460
bool RHMessenger::SerializeLockUser(SBFile &file)
{
    if (file.m_bLoading)
    {
        char loaded;
        if (file.Access(&loaded, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // The __FILE__ literal 0x006b118c is annotated once, in
                     // RHMessenger::Serialize above; this reference resolves to
                     // the same pooled entity. ("" 0x006773d0 and the format
                     // 0x006a7390 are owned by src/RHSword.cpp.)
                     "P:\\Robin Hood\\RHMessenger.cpp",
                     924,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (loaded != m_unk23)
        {
            RHUnk005460c0(RHUnk5490f0(loaded == 0 ? 0x1d : 0x1c));
        }
    }
    else
    {
        if (file.Access(&m_unk23, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 935, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHMessenger::Serialize and
// RHMessenger::SerializeLockUser in the build.
void RHMessenger::Emit(SBFile &file)
{
    Serialize(file);
    SerializeLockUser(file);
}
