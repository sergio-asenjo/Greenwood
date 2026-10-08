#ifndef RHSOUNDSOURCEMANAGER_H
#define RHSOUNDSOURCEMANAGER_H

#include "RHSaveGameManager.h"
#include "Decomp.h"

// SIZE 0x08
class RHUnk005fc030
{
public:
    RHUnk005fc030();
    float x; // 0x00
    float y; // 0x04
};

// SIZE 0x10
class RHSoundSourcePointStorage
{
public:
    RHSoundSourcePointStorage()
    {
        undefined allocator;
        m_allocator = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }
    ~RHSoundSourcePointStorage();

    undefined m_allocator; // 0x00
    RHUnk005fc030 *m_first; // 0x04
    RHUnk005fc030 *m_last; // 0x08
    RHUnk005fc030 *m_end; // 0x0c
};

// SIZE 0x24
class RHSoundSourcePoints
{
public:
    RHSoundSourcePoints() : m_changed(true) {}
    RHSoundSourcePointStorage m_storage; // 0x00
    undefined4 m_10; // 0x10
    bool m_changed; // 0x14
    undefined4 m_18; // 0x18
    RHUnk005fc030 m_1c; // 0x1c
};

// SIZE 0x3c
class RHSoundSourceFields
{
public:
    RHSoundSourceFields() : m_00(0), m_02(0), m_04(0), m_06(0), m_08(0), m_0a(0),
        m_30(0), m_34(0), m_36(0), m_38(1), m_3a(0) {}
    undefined &operator[](int index) { return ((undefined *)this)[index]; }

    undefined m_00; // 0x00
    undefined2 m_02; // 0x02
    undefined2 m_04; // 0x04
    undefined2 m_06; // 0x06
    undefined2 m_08; // 0x08
    undefined2 m_0a; // 0x0a
    RHSoundSourcePoints m_0c; // 0x0c
    undefined4 m_30; // 0x30
    undefined2 m_34; // 0x34
    undefined2 m_36; // 0x36
    undefined2 m_38; // 0x38
    undefined2 m_3a; // 0x3a
};

// VTABLE: GAME 0x00679e28
// SIZE 0x50
class RHSoundSource
{
public:
    RHSoundSource();
    virtual ~RHSoundSource(); // vtable+0x00
    virtual bool Serialize(SBFile &file); // vtable+0x04

    undefined4 m_04; // 0x04
    undefined4 m_08; // 0x08
    int m_0c; // 0x0c
    RHSoundSourceFields m_10; // 0x10
    bool m_4c; // 0x4c
};

// SIZE 0x04
struct RHSoundSourceIterator
{
    RHSoundSourceIterator(RHSoundSource **node) : m_node(node) {}
    RHSoundSourceIterator(const RHSoundSourceIterator &other) : m_node(other.m_node) {}
    RHSoundSource **m_node; // 0x00
};

// SIZE 0x20
class RHSoundSourceArray
{
public:
    int m_grow;                     // +0x00
    RHSoundSource **m_first;         // +0x04
    RHSoundSource **m_last;          // +0x08
    RHSoundSource **m_end;           // +0x0c
    RHSoundSource **m_search;        // +0x10
    bool m_changed;                 // +0x14
    bool m_searching;               // +0x15
    int m_index;                    // +0x18
    RHSoundSource *m_value;          // +0x1c

    int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    RHSoundSource *operator[](unsigned short index) { return m_first[index]; }
    RHSoundSource **begin() { return m_first; }
    RHSoundSource **end() { return m_last; }
    RHSoundSourceIterator RemoveAll()
    {
        RHSoundSource **first = copy(end(), end(), begin());
        RHSoundSourceIterator result(end());
        m_last = first;
        m_changed = true;
        return result;
    }
    void InsertLast(RHSoundSource *const &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert(
            (RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
        m_changed = true;
    }
    long Find(RHSoundSource *const &value, bool searching = true)
    {
        m_changed = false;
        m_value = value;
        int count = GetSize();
        m_search = m_first;
        int index = 0;
        m_searching = searching;
        for (; index < count; ++index, ++m_search)
            if (*m_search == value)
                break;
        m_index = index < count ? index : -1;
        return m_index;
    }
};

// SIZE 0x24
class RHSoundSourceManager
{
public:
    RHSoundSource *GetSoundSource(unsigned short id);
    bool AddSoundSource(RHSoundSource *source);
    bool Serialize(SBFile &file);
    void RHUnk005b4ae0();
    bool FUN_005b4f00(RHSoundSource *source);
    void Emit(SBFile &file, RHSoundSource *source, unsigned short id);

    undefined m_00[4];              // +0x00
    RHSoundSourceArray m_sources;    // +0x04
};

#endif
