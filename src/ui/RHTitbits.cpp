// RHTitbits.cpp — translation unit with __FILE__ evidence at 0x005c3a60
// ("P:\Robin Hood\RHtitbit.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005c3a60 -> RHTitbits::Serialize(SBFile&)):
//   - TU:        rhtitbit.cpp (embedded __FILE__ string 0x006b8bd8).
//   - Class:     RHTitbits (symbols/oracle-correlation.tsv: rhtitbit ->
//                prefix RHTitbits; symbols/mac-RH.txt carries the class).
//   - Method:    RHTitbits::Serialize(SBFile&) — the Mac oracle's rhtitbit.cpp
//                has exactly one serializer (mac-functions-by-file.tsv:
//                0x001e27b0 Serialize).
//   - Signals:
//       * the first act writes the tag "RHTitbits" (string 0x006b8bfc);
//       * the body is the standard field-serialiser idiom
//         (SBFile::Access 0x005f52b0 / GetError 0x005f5f30 and the
//         "Serialize failed reason is %s" assert pattern);
//       * it drives the intrusive list embedded at this+0x20 (resize on load,
//         cursor seek per element) and reads the engine singleton at
//         0x006c0a88 for two nested-object serialisers — the shape of a
//         collection serializer.
//
// STATUS: BLOCKED — not a byte match. The binding is solid (tag + TU + Mac
// method), and every serialised field / call site is reproduced, but the
// function cannot be made byte-identical: the target frame is 0x38 with the
// 48-byte element local at [esp+0x18] and a 4-byte hole at [esp+0x14]; VC6
// consistently packs the element at [esp+0x14] (frame 0x34), shifting every
// stack-relative displacement by 4. Marked STUB so reccmp does not count it.
// The reconstruction is kept for reference.

#include "RHTitbits.h"

// STUB: GAME 0x005c3a60
bool RHTitbits::Serialize(SBFile &file)
{
    unsigned int count;
    unsigned int i;
    RHTitbit elem;

    // STRING: GAME 0x6b8bfc
    RHSerializeName(file, "RHTitbits");

    if (file.Access(&m_ac, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8bd8
                 "P:\\Robin Hood\\RHtitbit.cpp",
                 621,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.m_bLoading)
    {
        m_list.Clear((void *)&elem, m_list.m_head->m_next, m_list.m_head);
        m_list.m_valid = 1;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 631, "Serialize failed reason is %s", reason);
            return false;
        }
        m_list.Resize(count);
        m_a4 = 0xf;
        m_a8 = 10.0f;
    }
    else
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 626, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    RHTitbitNode *node;
    for (i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            m_list.At(i);
            node = m_list.m_cur;
            elem = node->m_data;
        }

        if (file.Access(&elem.m_00, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 647, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_0a, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 648, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_08, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 649, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_06, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 650, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_04, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 651, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 652, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 653, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_u14.m_14s, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 654, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_28, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 655, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_2c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 656, "Serialize failed reason is %s", reason);
            return false;
        }

        g_pEngine->SerializeNestedA(file, &elem.m_0c);
        g_pEngine->SerializeNestedB(file, &elem.m_10);
        ((RHUnk005df510 *)&elem.m_0c)->Serialize(file);

        if (file.m_bLoading)
        {
            m_list.Seek(i);
            m_list.m_cur->m_data = elem;
        }
    }

    return true;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHTitbits::Serialize in the build.
void RHTitbits::Emit(SBFile &file)
{
    Serialize(file);
}
