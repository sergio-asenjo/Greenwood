#ifndef RHSOUNDSOURCEMANAGER_H
#define RHSOUNDSOURCEMANAGER_H

#include "RHSoundSourceManagerCore.h"
#include "RHSaveGameManager.h"
#include <vector>

inline RHSoundSourceArray::~RHSoundSourceArray()
{
    ((std::vector<RHSoundSource *> *)this)->erase(begin(), end());
    ((std::vector<RHSoundSource *> *)this)->~vector();
}

inline void RHSoundSourceArray::RemoveAll()
{
    ((std::vector<RHSoundSource *> *)this)->erase(begin(), end());
    m_changed = true;
}

inline void RHSoundSourceArray::InsertLast(RHSoundSource *const &value)
{
    ((SBArray<RHSaveGame *> *)this)->Insert(
        (RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
    m_changed = true;
}

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    bool Serialize(SBFile &file);
    float m_x; // 0x00
    float m_y; // 0x04
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
    SBGeoPoint2D *m_first; // 0x04
    SBGeoPoint2D *m_last; // 0x08
    SBGeoPoint2D *m_end; // 0x0c
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
    SBGeoPoint2D m_1c; // 0x1c
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
    float FUN_005b39e0(const SBGeoPoint2D &second, const SBGeoPoint2D &first);
    unsigned short FUN_005b3c20(unsigned short index);
    float FUN_005b3a10(const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned char &visible);
    unsigned short FUN_005b3c40(const void *point);
    void FUN_005b3f30(SBFile &file);
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

#endif
