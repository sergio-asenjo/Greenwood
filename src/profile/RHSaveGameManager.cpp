// RHSaveGameManager.cpp — translation unit with __FILE__ evidence at 0x0056ff10
// ("P:\Robin Hood\RHsavegamemanager.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0056ff10 -> RHSaveGameManager::Serialize(SBFile&)):
//   - TU:     rhsavegamemanager.cpp (embedded __FILE__ string 0x006b2314).
//   - Class:  RHSaveGameManager (symbols/oracle-correlation.tsv:
//             rhsavegamemanager -> class RHSaveGameManager, 27 methods).
//   - Method: RHSaveGameManager::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * the first act writes the tag "RHSaveGameManager" (string 0x006b2374)
//         via RHSerializeName;
//       * a __thiscall(SBFile&) with an EH frame (new/delete below);
//       * the body drives an SBArray<RHSaveGame*> at this+0x8: it deletes every
//         element, clears the array (inlined erase/copy), reads a count and
//         re-creates that many RHSaveGame objects on load, then serialises every
//         element through RHSaveGame::Serialize.

#include "SBNullstr.h"
#include "RHSaveGameManager.h"
#include <vector>

template <class T>
inline SBArray<T>::~SBArray()
{
    typedef std::vector<T> Vector;
    ((Vector *)this)->~Vector();
}

template <class T>
inline void SBArray<T>::Remove(unsigned long index)
{
    ((std::vector<T> *)this)->erase(begin() + index);
}

extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *);

#include "RHGameSaveCalls.h"

class RHGameContinueCalls
{
public:
    void FUN_0056f700(RHSaveGame *source, RHSaveGame *target, const std::wstring &text);
    RHSaveGame *FUN_0056f730(const std::wstring &text, const std::string &fileName);
};

#include "RHUnk0056fb70.h"

// SIZE 0x48
struct RHSaveGameStrings
{
    char m_00[0x08];       // 0x00
    std::string m_08;      // 0x08
    std::string m_18;      // 0x18
    std::wstring m_28;     // 0x28
    char m_38[0x10];       // 0x38
};

void RHSaveGameManager::Emit(SBFile &file)
{
    GetNextSaveGameFileName();
    CreateSaveGame(std::wstring());
    GetSaveGame(0);
    GetSaveGameCount();
    RemoveSaveGame(0);
    Serialize(file);
}

// FUNCTION: GAME 0x0056f600
RHSaveGameManager::RHSaveGameManager() : m_04(0)
{
}

// FUNCTION: GAME 0x0056f620
RHSaveGameManager::~RHSaveGameManager()
{
    RHSaveGame **it;
    for (it = m_saveGames.begin(); it != m_saveGames.end(); ++it)
        delete (RHSaveGameStrings *)*it;
    ((std::vector<RHSaveGame *> *)&m_saveGames)->erase(m_saveGames.begin(), m_saveGames.end());
}

// FUNCTION: GAME 0x0056f700
void RHGameContinueCalls::FUN_0056f700(RHSaveGame *source, RHSaveGame *target, const std::wstring &text)
{
    target->CopyFiles(source);
    target->SetText(text);
}

// FUNCTION: GAME 0x0056f730
RHSaveGame *RHGameContinueCalls::FUN_0056f730(const std::wstring &text, const std::string &fileName)
{
    RHSaveGameManager *manager = (RHSaveGameManager *)this;
    RHSaveGame *saveGame = (RHSaveGame *)((RHUnk0056fb70 *)this)->FUN_0056fb70(&fileName);
    if (!saveGame)
    {
        saveGame = new RHSaveGame(manager, fileName, text);
        ((std::vector<RHSaveGame *> *)&manager->m_saveGames)->push_back(saveGame);
    }
    saveGame->SetText(text);
    return saveGame;
}

// FUNCTION: GAME 0x0056f940
unsigned long RHSaveGameManager::CreateSaveGame(const std::wstring &name)
{
    RHSaveGame *saveGame = new RHSaveGame(this, GetNextSaveGameFileName(), name);
    m_saveGames.InsertLast(saveGame);
    return m_saveGames.GetSize() - 1;
}

// FUNCTION: GAME 0x0056fa30
std::string RHSaveGameManager::GetNextSaveGameFileName()
{
    char name[256];
    sprintf(name,
        // STRING: GAME 0x006b2364
        "Savegame_%03i", m_04++);
    return std::string(name);
}

// FUNCTION: GAME 0x0056fb30
RHSaveGame *RHSaveGameManager::GetSaveGame(unsigned long index) const
{
    return ((const std::vector<RHSaveGame *> &)m_saveGames).at(index);
}

// FUNCTION: GAME 0x0056fb70
void *RHUnk0056fb70::FUN_0056fb70(const void *value)
{
    const std::string &fileName = *(const std::string *)value;
    RHSaveGameManager *manager = (RHSaveGameManager *)this;
    RHSaveGame *saveGame = 0;
    std::string path = manager->GetSaveGameDirectory() + "\\" + fileName;
    RHSaveGame **it;
    for (it = manager->m_saveGames.begin(); it != manager->m_saveGames.end(); ++it)
    {
        if ((*it)->FUN_0056e5d0() == path)
        {
            saveGame = *it;
            break;
        }
    }
    return saveGame;
}

// FUNCTION: GAME 0x0056fd00
unsigned long RHSaveGameManager::GetSaveGameCount() const
{
    return m_saveGames.GetSize();
}

// Parked: carried index and receiver use different registers from the target.
// STUB: GAME 0x0056fd20
void RHSaveGameManager::RemoveSaveGame(unsigned long index)
{
    SBArray<RHSaveGame *> &games = m_saveGames;
    RemoveSaveGameFile(*(index + games.begin()));
    delete *(index + games.begin());
    games.Remove(index);
}

// FUNCTION: GAME 0x0056fe30
void RHSaveGameManager::RemoveSaveGameFile(const RHSaveGame *saveGame)
{
    std::string name = saveGame->FUN_0056e5d0();
    std::string settingsName = ((RHGameSaveCalls *)saveGame)->FUN_0056e6b0();
    DeleteFileA(name.c_str());
    DeleteFileA(settingsName.c_str());
}

// FUNCTION: GAME 0x0056ff10
bool RHSaveGameManager::Serialize(SBFile &file)
{
    SBArray<RHSaveGame *> &list = m_saveGames;
    unsigned int count = list.GetSize();

    // STRING: GAME 0x6b2374
    RHSerializeName(file, "RHSaveGameManager");

    if (file.Access(&m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b2314
                 "P:\\Robin Hood\\RHsavegamemanager.cpp",
                 0x149,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    if (file.Access(&count, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 "P:\\Robin Hood\\RHsavegamemanager.cpp",
                 0x14a,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.m_bLoading)
    {
        RHSaveGame **it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            RHSaveGame *p = *it;
            if (p)
                delete p;
        }
        ((std::vector<RHSaveGame *> *)&list)->erase(list.begin(), list.end());
        while (count != 0)
        {
            list.InsertLast(new RHSaveGame(this));
            --count;
        }
    }

    RHSaveGame **it;
    for (it = m_saveGames.begin(); it != m_saveGames.end(); ++it)
        (*it)->Serialize(file);

    return true;
}

// TEMPLATE: GAME 0x00570360
// ?_Xran@?$vector@PAVRHSaveGame@@V?$allocator@PAVRHSaveGame@@@std@@@std@@IBEXXZ
