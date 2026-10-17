#include "RHSaveGame.h"

void RHSerializeName(SBFile &, const char *);
bool FUN_005e0c90(SBFile &, std::string &);
bool FUN_005e0ea0(SBFile &, std::wstring &);

// FUNCTION: GAME 0x0056e6a0
const _SYSTEMTIME &RHSaveGame::GetTime() const
{
    return *(const _SYSTEMTIME *)(m_data + 0x38);
}

// FUNCTION: GAME 0x0056e780
const std::wstring &RHSaveGame::FUN_0056e780() const
{
    return *(const std::wstring *)(m_data + 0x28);
}

// FUNCTION: GAME 0x0056ea20
bool RHSaveGame::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006b22b0
        "RHSaveGame");
    FUN_005e0c90(file, *(std::string *)(m_data + 0x08));
    FUN_005e0c90(file, *(std::string *)(m_data + 0x18));
    FUN_005e0ea0(file, *(std::wstring *)(m_data + 0x28));
    SynchronizeWithFile();
    return true;
}

// FUNCTION: GAME 0x0056ea70
bool RHSaveGame::SerializeHeader(SBFile &file, Header &header)
{
    unsigned &version = file.m_version;
    version = 0x30;
    if (file.Access(&header.m_00, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
            // STRING: GAME 0x006b228c
            "P:\\Robin Hood\\RHsavegame.cpp", 0x101, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&header.m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsavegame.cpp", 0x102, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&header.m_08, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsavegame.cpp", 0x103, "Serialize failed reason is %s", reason);
        return false;
    }
    file.Access(&version, 4);
    if (file.m_bLoading)
    {
        bool result = true;
        if (header.m_00 != 0x52485347)
        {
            SBAssert(0, "P:\\Robin Hood\\RHsavegame.cpp", 0x10d,
                // STRING: GAME 0x006b22bc
                "Warning: trying to load an invalid savegame file.");
            result = false;
        }
        if (header.m_04 != 0x30 || version != 0x30)
            result = true;
        return result;
    }
    else
        return true;
}

// FUNCTION: GAME 0x0056ecc0
void RHSaveGame::SynchronizeWithFile()
{
    std::string name = FUN_0056e5d0();
    if (FUN_005f6400(name))
    {
        RHUnk005f4fc0 file;
        Header header;
        if (file.FUN_005f5090(name, 1) != 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHsavegame.cpp", 0x142,
                // STRING: GAME 0x006b22f0
                "Unable to access a savegame file.");
            return;
        }
        file.FUN_005f6200(RHSaveGame_m_38);
        SerializeHeader(file, header);
        RHSaveGame_m_04 = header.m_08;
        file.FUN_005f5290();
    }
}

struct _FILETIME
{
    unsigned long m_low;
    unsigned long m_high;
};

extern "C" __declspec(dllimport) int __stdcall SystemTimeToFileTime(const _SYSTEMTIME *, _FILETIME *);
extern "C" __declspec(dllimport) long __stdcall CompareFileTime(const _FILETIME *, const _FILETIME *);

// FUNCTION: GAME 0x0056ee20
bool RHSaveGame::operator<(const RHSaveGame &other) const
{
    _FILETIME mine;
    _FILETIME theirs;
    SystemTimeToFileTime(&GetTime(), &mine);
    SystemTimeToFileTime(&other.GetTime(), &theirs);
    return CompareFileTime(&mine, &theirs) > 0;
}

// FUNCTION: GAME 0x00570320
bool FUN_00570320(const RHSaveGame *first, const RHSaveGame *second)
{
    return *first < *second;
}

void RHSaveGame::Emit(SBFile &file, Header &header)
{
    FUN_0056e780();
    SerializeHeader(file, header);
    SynchronizeWithFile();
}
