#ifndef RHSAVEGAMEMANAGER_H
#define RHSAVEGAMEMANAGER_H

#include "RHSaveGame.h"

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
    SBArray(const std::allocator<T> &allocator = std::allocator<T>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0)
    {
    }
    ~SBArray();

    std::allocator<T> m_allocator;
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
    void Remove(unsigned long index);
};

// VTABLE: GAME 0x00679be8
class RHSaveGameManager
{
public:
    RHSaveGameManager();
    ~RHSaveGameManager();
    virtual std::string GetSaveGameDirectory() const = 0;
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    int m_04;
    SBArray<RHSaveGame *> m_saveGames;

    std::string GetNextSaveGameFileName();
    unsigned long CreateSaveGame(const std::wstring &name);
    RHSaveGame *GetSaveGame(unsigned long index) const;
    unsigned long GetSaveGameCount() const;
    void RemoveSaveGame(unsigned long index);
    void RemoveSaveGameFile(const RHSaveGame *saveGame);
    void SortSaveGames();
};

void RHSerializeName(SBFile &file, const char *name);

#endif
