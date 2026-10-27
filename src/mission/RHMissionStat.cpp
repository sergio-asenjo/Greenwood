// RHMissionStat.cpp — translation unit with __FILE__ evidence at 0x0054e250
// ("P:\Robin Hood\RHMissionStat.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0054e250 -> RHMissionStat::Serialize(SBFile&)):
//   - TU:        rhmissionstat.cpp (embedded __FILE__ string 0x006b1320).
//   - Class:     RHMissionStat (symbols/oracle-correlation.tsv:
//                rhmissionstat -> class RHMissionStat, 16 methods).
//   - Method:    RHMissionStat::Serialize(SBFile&) — the Mac oracle's
//                rhmissionstat.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x0016d690 Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHMissionStat" (string
//         0x006b1350) via 0x005e1b70 — the name matches the TU's class;
//       * every field goes through SBFile::Access 0x005f52b0 / SBFile::GetError
//         0x005f5f30 and the "Serialize failed reason is %s" assert pattern
//         (format 0x006a7390, empty fallback 0x006773d0) — the exact serializer
//         idiom seen in RHSword::SerializePointer;
//       * the tail call is 0x004593f0(file, this+0x28, 0x005e0ea0), a
//         container-serialiser helper that walks [this+0x2c, this+0x30) and
//         invokes the per-element function pointer — the standard list tail
//         of a serializer.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHMissionStat.h"
#include <algorithm>
#include <vector>

extern template class std::basic_string<unsigned short>;

// FUNCTION: GAME 0x0054cfa0
void RHMissionStat::AddNewPC(const RHPCDescription *source)
{
    const std::wstring &value = *(const std::wstring *)((const char *)source + 0x2c);
    ((std::vector<std::wstring> *)&m_list)->push_back(value);
}

// FUNCTION: GAME 0x0054d150
void RHMissionStat::FUN_0054d150(const void *value)
{
    for (std::wstring *it = m_list.m_first; it != m_list.m_last; ++it)
    {
        if (*(const std::wstring *)((const char *)value + 0x2c) == *it)
        {
            ((std::vector<std::wstring> *)&m_list)->erase(it);
            return;
        }
    }
}

// FUNCTION: GAME 0x0054d310
void RHMissionStat::FUN_0054d310(std::wstring &text) const
{
    wchar_t buffer[512];
    wsprintfW(buffer, FUN_005e23d0(0x4d).c_str(), m_f1c);
    text += buffer;
    text += L"\n";
    if (m_f20 != 0)
    {
        wsprintfW(buffer, FUN_005e23d0(0x54).c_str(), m_f20);
        text += buffer;
        text += L"\n";
    }
}

// FUNCTION: GAME 0x0054d550
void RHMissionStat::FUN_0054d550(std::wstring &text) const
{
    wchar_t buffer[128];
    wsprintfW(buffer, FUN_005e23d0(0x50).c_str(), FUN_005e2bf0(g_unk0x6c07fc->Get(6)).c_str());
    text += buffer;
    text += L"\n";
}

// FUNCTION: GAME 0x0054d760
void RHMissionStat::FUN_0054d760(std::wstring &text) const
{
    wchar_t buffer[512];
    if (m_f04 != 0)
    {
        wsprintfW(buffer, FUN_005e23d0(0x49).c_str(), m_f04);
        text += buffer;
        text += L"\n";
    }
    if (m_f08 != 0 || m_f0c != 0)
    {
        int total = m_f0c + m_f08;
        wsprintfW(buffer, FUN_005e23d0(0x55).c_str(), total, m_f08, m_f0c);
        text += buffer;
        text += L"\n";
    }
}

// FUNCTION: GAME 0x0054d9c0
void RHMissionStat::FUN_0054d9c0(std::wstring &text) const
{
    std::wstring separator = FUN_005e23d0(0x4c);
    wchar_t buffer[512];
    for (const std::wstring *it = m_list.m_first; it != m_list.m_last; ++it)
    {
        // STRING: GAME 0x6b1340
        wsprintfW(buffer, L"%s %s\n", it->c_str(), separator.c_str());
        text += buffer;
    }
}

// FUNCTION: GAME 0x0054db50
void RHMissionStat::FUN_0054db50(std::wstring &text) const
{
    wchar_t buffer[128];
    wsprintfW(buffer, FUN_005e23d0(0x4e).c_str(), m_f24);
    text += buffer;
    // STRING: GAME 0x6b0944
    text += L"\n";
}

// FUNCTION: GAME 0x0054dd10
void RHMissionStat::FUN_0054dd10(std::wstring &text) const
{
    wchar_t buffer[512];
    wsprintfW(buffer, FUN_005e23d0(0x4a).c_str(), m_f10, m_f14);
    text += buffer;
    text += L"\n";
}

// FUNCTION: GAME 0x0054dee0
void RHMissionStat::FUN_0054dee0(std::wstring &text) const
{
    wchar_t buffer[512];
    unsigned count = m_list.size();
    wsprintfW(buffer, FUN_005e23d0(0x4b).c_str(), m_f18 + (int)count);
    text += buffer;
    text += L"\n";
}

// FUNCTION: GAME 0x0054e090
std::wstring RHMissionStat::FUN_0054e090() const
{
    std::wstring text;
    FUN_0054d760(text);
    text += L"\n";
    FUN_0054dd10(text);
    FUN_0054dee0(text);
    FUN_0054d9c0(text);
    FUN_0054d310(text);
    text += L"\n";
    FUN_0054db50(text);
    FUN_0054d550(text);
    return text;
}

// FUNCTION: GAME 0x0054e250
bool RHMissionStat::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b1350
    RHSerializeName(file, "RHMissionStat");

    if (file.Access(&m_f04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b1320
                 "P:\\Robin Hood\\RHMissionStat.cpp",
                 309,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_f08, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 310, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f0c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 311, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f10, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 312, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f14, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 313, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f18, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 314, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f1c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 315, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f20, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 316, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_f24, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMissionStat.cpp", 317, "Serialize failed reason is %s", reason);
        return false;
    }

    // The per-element serialiser is passed by value: the original is a
    // fixed-base EXE, so `push offset 0x005e0ea0` carries no relocation and
    // reccmp keeps it as the literal immediate 0x005e0ea0. Emitting the same
    // literal (a numeric constant, not the address of a local symbol) is the
    // only way to reproduce those bytes.
    RHUnk004593f0SerializeList(file, m_list, (void *)0x005e0ea0);
    return true;
}

// Force emission: RHSword-style serializers are pulled in only when
// referenced; this non-inlinable out-of-line call keeps Serialize in the build.
void RHMissionStat::Emit(SBFile &file)
{
    Serialize(file);
}
