// RHSequence.cpp — translation unit with __FILE__ evidence at 0x00584980
// ("P:\Robin Hood\RHsequence.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005843c0 -> RHSequence::Serialize(SBFile&, bool)):
//   - TU:        rhsequence.cpp (embedded __FILE__ string 0x006b7460).
//   - Class:     RHSequence (symbols/oracle-correlation.tsv: rhsequence -> class
//                RHSequence, 21 methods).
//   - Signature: RHSequence::Serialize(SBFile&, bool)
//                (symbols/mac-RH.txt; the only other serializer in the Mac TU,
//                symbols/mac-functions-by-file.tsv: 0x001a88b0 Serialize).
//   - Signals:
//       * the first act writes the type-name tag "RHSequence" (string 0x006b7484)
//         via the 0x005e1b70 helper;
//       * an EH frame (new below), `sub esp,0x10`, this=esi, file=edi, the bool
//         as the second stack arg;
//       * an `Access` chain on +0x34/+0x2e/+0x30/+0x2c/+0x04 and the
//         "Serialize failed reason is %s" assert idiom;
//       * a dual-path element loop over the SBList at this+0x08: on write it
//         walks with SBList::GoTo (0x005c8e40) and serialises each element; on
//         load it reads a type byte, allocates one of five element types via
//         operator new (0x006428b5) + their ctors, serialises and links it with
//         the inlined SBList insert (0x0059fb00 payload copy);
//       * a trailing reorder pass that re-walks the list and chains each
//         element's +0x4c to the next.
//
// STATUS (0x005843c0): PARKED as STUB — the binding is solid and the logic is
// reproduced, but the target cannot be made byte-exact at this compiler tier.
// The residual is a 4-byte stack-frame / EH-layout difference of the same family
// as RHGroundMark/RHTitbits/RHScript::GetScrollStatus:
//   * target: `sub esp,0x10` with exactly four frame slots at [esp+0x10]
//     (count), [esp+0x14] (type), [esp+0x18] (i), [esp+0x1c] (elem); the five
//     `new` EH trylevels are packed into the pushed-EH-state dword at [esp+0x28].
//   * ours:   `sub esp,0x14` — VC6 reserves a fifth 4-byte slot when the load
//     path contains the five-way `switch` of `new` expressions. Every [esp+N]
//     *and* the register allocation shift with it (e.g. the phase-1 list lands
//     in ebp instead of ebx), so reccmp scores 56.54%.
// * isolate-probe evidence (/O2 /GX): a single `new`
//     the same source shape gives the target's `sub esp,0x10`; removing the
//     switch gives `sub esp,0xc`; every probed five-way form
//     (switch/if-chain, with/without `default`, `elem` hoisted/initialised,
//     `int`/`unsigned char` type, serialize inside/after the cases,
//     virtual/non-virtual element dtor) gives `sub esp,0x14`.
//   * the load path genuinely emits five `operator new` calls (sizes
//     0x64/0x7c/0x74/0x68/0x9c) with five distinct EH states, so the extra slot
//     is VC6's bookkeeping for that switch, not a source-shape artefact we can
//     fold away. Kept as STUB so reccmp does not count it; the reconstruction
//     below is for reference.
//
// BINDING (0x00584980 -> RHSequence::SerializeStaticStuff(SBFile&)):
//   - Signals:
//       * the function writes the type-name tag "RHSequence::SerializeStaticStuff"
//         (string 0x006b7490) as its first act via the 0x005e1b70 helper;
//       * a single SBFile::Access check on the 4-byte global 0x006b7480, then
//         the "Serialize failed reason is %s" assert idiom — a serializer with
//         no loop, no `new`, no base call;
//       * the body never uses ecx as `this` (arg is `[esp+8]`), so Windows
//         emits it as a static member — declared `static` here.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHSequence.h"

// The 4-byte global read/written by SerializeStaticStuff (original 0x006b7480).
// GLOBAL: GAME 0x006b7480
int g_unk0x6b7480;

// STUB: GAME 0x005843c0
bool RHSequence::Serialize(SBFile &file, bool bArg)
{
    // STRING: GAME 0x6b7484
    RHSerializeName(file, "RHSequence");

    if (file.m_bLoading)
    {
        RHUnkListSeq &list = RHSequenceGlobalList();
        list.insert(list.end(), this);
        list.m_flag10 = 1;
    }

    if (file.Access(&m_34, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1234, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2e, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1235, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_30, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1236, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1237, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1238, "Serialize failed reason is %s", reason);
        return false;
    }

    unsigned int count;
    unsigned char type;
    RHSequenceElement *elem;
    if (!file.m_bLoading)
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1244, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1248, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    for (unsigned int i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            m_list.GoTo(i);
            elem = m_list.m_cur->m_data;
            type = *((unsigned char *)elem + 4);
            if (file.Access(&type, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1261, "Serialize failed reason is %s", reason);
                return false;
            }
            elem->Serialize(file, bArg);
        }
        else
        {
            if (file.Access(&type, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1274, "Serialize failed reason is %s", reason);
                return false;
            }

            switch (type & 0xff)
            {
            case 0:
                elem = new RHSequenceElement();
                break;
            case 1:
                elem = new RHUnk586050();
                break;
            case 2:
                elem = new RHUnk5865a0();
                break;
            case 3:
                elem = new RHUnk585e70();
                break;
            case 4:
                elem = new RHUnk588270();
                break;
            default:
                elem = 0;
                break;
            }

            elem->Serialize(file, bArg);

            m_list.insert(m_list.end(), elem);
            m_list.m_count++;
            m_list.m_valid = 1;
            *(RHSequence **)((char *)elem + 0x54) = this;
        }
    }

    if (file.Access(&m_32, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1317, "Serialize failed reason is %s", reason);
        return false;
    }

    if (bArg)
        return true;
    if (!file.m_bLoading)
        return true;
    if (count == 0)
        return true;
    if (count <= 1)
        return true;

    RHSequenceElement *prev = m_list.m_head->m_next->m_data;
    for (unsigned int j = 1; j < count; j++)
    {
        m_list.GoTo(j);
        RHSequenceElement *cur = m_list.m_cur->m_data;
        *(RHSequenceElement **)((char *)prev + 0x4c) = cur;
        prev = cur;
    }

    return true;
}

// FUNCTION: GAME 0x00584980
bool RHSequence::SerializeStaticStuff(SBFile &file)
{
    // STRING: GAME 0x6b7490
    RHSerializeName(file, "RHSequence::SerializeStaticStuff");

    if (file.Access(&g_unk0x6b7480, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b7460
                 "P:\\Robin Hood\\RHsequence.cpp",
                 1353,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps the serialisers in the build.
void RHSequence::Emit(SBFile &file)
{
    Serialize(file, false);
    SerializeStaticStuff(file);
}
