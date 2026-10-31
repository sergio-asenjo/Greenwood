#include "SBNullstr.h"
#include "RHSaveGame.h"
#include <string.h>
#include "RHGameSaveCalls.h"

void RHSerializeName(SBFile &, const char *);
bool FUN_005e0c90(SBFile &, std::string &);
bool FUN_005e0ea0(SBFile &, std::wstring &);

// FUNCTION: GAME 0x0056e250
RHSaveGame::RHSaveGame(RHSaveGameManager *manager)
    : m_manager(manager), m_04(0xffffffff)
{
}

// STRING: GAME 0x006b22ac
#define RHSAVEGAME_SETTINGS_SUFFIX "_t"

// FUNCTION: GAME 0x0056e2a0
RHSaveGame::RHSaveGame(RHSaveGameManager *manager, const std::string &fileName, const std::wstring &name)
    : m_manager(manager), m_04(0xffffffff), m_08(fileName), m_18(fileName + RHSAVEGAME_SETTINGS_SUFFIX),
      m_28(name)
{
    memset(m_38, 0, sizeof(m_38));
}

extern "C" __declspec(dllimport) int __stdcall CopyFileA(const char *, const char *, int);

// FUNCTION: GAME 0x0056e440
void RHSaveGame::CopyFiles(const RHSaveGame *source)
{
    CopyFileA(source->FUN_0056e5d0().c_str(), FUN_0056e5d0().c_str(), 0);
    CopyFileA(((RHGameSaveCalls *)source)->FUN_0056e6b0().c_str(),
        ((RHGameSaveCalls *)this)->FUN_0056e6b0().c_str(), 0);
    SynchronizeWithFile();
}

// FUNCTION: GAME 0x0056e6a0
const _SYSTEMTIME &RHSaveGame::GetTime() const
{
    return *(const _SYSTEMTIME *)m_38;
}

// FUNCTION: GAME 0x0056e780
const std::wstring &RHSaveGame::FUN_0056e780() const
{
    return m_28;
}

extern std::string g_unk0x006c0ea0;
extern std::string g_unk0x006c0ed8;
extern std::string g_unk0x006c0ee8;

// GLOBAL: GAME 0x006c0eb8
std::string g_unk0x006c0eb8 = "QuickSave";
// GLOBAL: GAME 0x006c0ec8
std::string g_unk0x006c0ec8 = "ExQuickSave";

// Parked: compare expansion retains a length-alias guard and different receiver registers after two shapes.
// STUB: GAME 0x0056e8b0
int RHSaveGame::FUN_0056e8b0() const
{
    const std::string &name = m_08;
    if (name.compare(g_unk0x006c0ea0) == 0 || name.compare(g_unk0x006c0ec8) == 0 ||
        name.compare(g_unk0x006c0eb8) == 0 || name.compare(g_unk0x006c0ed8) == 0 ||
        name.compare(g_unk0x006c0ee8) == 0)
        return 1;
    return 0;
}

// FUNCTION: GAME 0x0056ea20
bool RHSaveGame::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006b22b0
        "RHSaveGame");
    FUN_005e0c90(file, m_08);
    FUN_005e0c90(file, m_18);
    FUN_005e0ea0(file, m_28);
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

// FUNCTION: GAME 0x0056eb80
void RHSaveGame::SetText(const std::wstring &text)
{
    m_28 = text;
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
        file.FUN_005f6200(m_38);
        SerializeHeader(file, header);
        m_04 = header.m_08;
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
