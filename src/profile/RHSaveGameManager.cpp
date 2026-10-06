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
//
// STATUS: BLOCKED — not a byte match (binding is solid; logic and frame
// reproduced). reccmp: 93.73%. The residual is compiler scheduling/entropy in
// the SBArray erase + insert region, not the code (isolate-probed at /O2 /GX):
//   * after `list.RemoveAll()` the original keeps an extra pair of instructions
//     (`mov ecx,[esi+8]` / `mov [esp+0x28],ecx`) — the old m_last spilled to the
//     outgoing-argument slot — and schedules `m_last = <copy result>` *after*
//     `test eax,eax`; VC6 at every probed source shape emits the assignment
//     first and drops the dead spill.
//   * the inlined Insert materialises its value temporary into the arg slot
//     BEFORE loading `m_last` (`lea edx,[esp+0x28]; mov [esp+0x28],eax;
//     mov eax,[esi+8]`); every probed shape defers the store until after the
//     three `push`es.
// `RemoveAll()` reproduces the erase exactly only as `copy(end(), end(), begin())`
// (a `copy(m_last, m_last, m_first)` source emits `mov eax,edx; cmp eax,edx`
// instead of the target's `cmp ecx,ecx; mov eax,ecx`). Kept as STUB so reccmp
// does not count it; the reconstruction is for reference.

#include "RHSaveGameManager.h"

// STUB: GAME 0x0056ff10
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
        list.RemoveAll();
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
