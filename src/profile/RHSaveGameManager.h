// RHSaveGameManager — declarations shared by RHSaveGameManager.cpp (decompiled
// TU) and RHSaveGameManager_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0056ff10 -> RHSaveGameManager::Serialize(SBFile&)): see
// src/RHSaveGameManager.cpp.
//
// Member layout derived from the target instructions of
// RHSaveGameManager::Serialize:
//   - +0x04: a 4-byte field serialised at line 0x149;
//   - +0x08: an SBArray<RHSaveGame*> (m_grow at +0x08, m_first at +0x0c,
//     m_last at +0x10, m_end at +0x14).

#include "SB.h"

class RHSaveGameManager;
class RHSaveGame;

class RHSaveGame
{
public:
    RHSaveGame(RHSaveGameManager *mgr);
    ~RHSaveGame();

    bool Serialize(SBFile &file);

    char m_data[0x48];
};

template <class T>
T *copy(T *first, T *last, T *dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}

template <class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;

    unsigned int GetSize() const
    {
        return (m_first == 0 ? 0 : (m_last - m_first));
    }

    T *begin() { return m_first; }
    T *end() { return m_last; }

    void Insert(T *pos, unsigned int count, const T &value);
    void InsertLast(const T &value) { Insert(m_last, 1, value); }
    void RemoveAll() { m_last = copy(end(), end(), begin()); }
};

class RHSaveGameManager
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[4];
    int m_04;
    SBArray<RHSaveGame *> m_saveGames;
};

void RHSerializeName(SBFile &file, const char *name);
