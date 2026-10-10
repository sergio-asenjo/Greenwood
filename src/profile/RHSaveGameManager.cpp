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

void RHSaveGameManager::Emit(SBFile &file)
{
    Serialize(file);
}
