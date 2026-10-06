// RHWidgetPortrait.cpp — translation unit with __FILE__ evidence at 0x005d92c0
// ("P:\Robin Hood\RHWidgetPortrait.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005d92c0 -> RHWidgetPortrait::Serialize(SBFile&)):
//   - TU:        rhwidgetportrait.cpp (embedded __FILE__ string 0x006b8e28).
//   - Class:     RHWidgetPortrait (symbols/oracle-correlation.tsv:
//                rhwidgetportrait -> class RHWidgetPortrait, 51 methods).
//   - Method:    RHWidgetPortrait::Serialize(SBFile&) — the Mac oracle's
//                rhwidgetportrait.cpp has exactly one serializer
//                (mac-functions-by-file.tsv: 0x001f43d0 Serialize).
//   - Signals:
//       * the first act writes the tag "RHWidgetPortrait" (string 0x006b8e90);
//       * every field goes through SBFile::Access 0x005f52b0 / GetError
//         0x005f5f30 and the "Serialize failed reason is %s" assert pattern;
//       * the read/write split is driven by SBFile::m_bLoading (+4) and the
//         format version at SBFile+0x10 (compared against 0xf and 0x2b);
//       * the per-element loop walks three 0x104-byte elements at +0xa50 and
//         dispatches four this-call helpers (0x5d6690 / 0x5d67e0 / 0x5d73d0 /
//         0x5d7530) plus one virtual on the sub-object at +0x7bc.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses. ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp.)
//
// STATUS: 100% — exact byte match. The float member +0x16c is copied through
// an intermediate `float` temp (see `tmp`) so VC6 keeps the value on the x87
// stack (`fld`/`fstp`) exactly as the original does; a direct `m_16c = f10`
// compiles to an integer `mov` pair instead. The temp coalesces into f10's
// stack slot, so the 0x10 frame is unchanged.

#include "RHWidgetPortrait.h"

// FUNCTION: GAME 0x005d92c0
bool RHWidgetPortrait::Serialize(SBFile &file)
{
    char b12;
    char bf;
    float f10;
    float tmp;
    int b14;
    int iArr;
    char bArr;

    // STRING: GAME 0x6b8e90
    RHSerializeName(file, "RHWidgetPortrait");

    if (file.Access(m_e50, 6) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8e28
                 "P:\\Robin Hood\\RHWidgetPortrait.cpp",
                 1207,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_arr[2].m_50, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1209, "Serialize failed reason is %s", reason);
        return false;
    }

    if (FileVersion(file) >= 0xf)
    {
        if (file.Access(&m_arr[2].m_51, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1213, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.m_bLoading)
    {
        if (file.Access(&b12, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1218, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&bf, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1219, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&f10, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1221, "Serialize failed reason is %s", reason);
            return false;
        }
        // Copy through `tmp` so VC6 models the value as an x87 value and emits
        // `fld [esp+0x10]; ...; fstp [edi+0x16c]` (sunk past the next Access's
        // argument setup). A direct `m_16c = f10` in a member function compiles
        // to an integer `mov` pair because eax is free (this is the only reason
        // the original differs here). `tmp` coalesces into f10's slot.
        tmp = f10;
        m_16c = tmp;
        if (file.Access(&b14, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1225, "Serialize failed reason is %s", reason);
            return false;
        }
        m_7bc.v21(b14);
        if (b12)
            Method005d73d0();
        else
            Method005d7530();
        if (bf)
            Method005d6690();
        else
            Method005d67e0();
    }
    else
    {
        if (file.Access(&m_arr[2].m_4f, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1250, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&m_arr[2].m_4e, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1251, "Serialize failed reason is %s", reason);
            return false;
        }
        // Same temp trick as the store path: `tmp = m_16c` makes VC6 hold the
        // member in ST0 and sink `fstp [esp+0x14]` past the Access argument
        // pushes, matching `fld [edi+0x16c]; lea eax,[esp+0x10]; push 4;
        // fstp [esp+0x14]; push eax`. A direct `f10 = m_16c` would use movs.
        tmp = m_16c;
        f10 = tmp;
        if (file.Access(&f10, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1254, "Serialize failed reason is %s", reason);
            return false;
        }
        // b14 is a 4-byte local (the load path passes all 32 bits to v21), but
        // only its low byte is serialised here; the target narrows the store to
        // one byte, so write the byte explicitly.
        *(char *)&b14 = m_7c0;
        if (file.Access(&b14, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1258, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (!file.m_bLoading)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            iArr = m_arr[i].m_00;
            if (file.Access(&iArr, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1270, "Serialize failed reason is %s", reason);
                return false;
            }
            bArr = m_arr[i].m_05;
            if (file.Access(&bArr, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1273, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            if (file.Access(&iArr, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1280, "Serialize failed reason is %s", reason);
                return false;
            }
            if (FileVersion(file) >= 0x2b)
            {
                if (file.Access(&bArr, 1) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1284, "Serialize failed reason is %s", reason);
                    return false;
                }
            }
            else
            {
                bArr = 0;
            }
            m_arr[i].m_00 = iArr;
            m_arr[i].m_05 = bArr;
        }
    }

    return true;
}

// Force emission.
void RHWidgetPortrait::Emit(SBFile &file)
{
    Serialize(file);
}
