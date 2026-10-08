#ifndef RHSOUNDCACHE_H
#define RHSOUNDCACHE_H

#include "SB.h"
#include "Decomp.h"
#include "RHSoundCacheEntry.h"
#include "RHCivilianProfile.h"
#include <map>
#include <list>
#include <stdlib.h>
#include <new>
#include <vector>

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

// SIZE 0x0c
struct RHSoundCacheListNode
{
    RHSoundCacheListNode *m_next; // 0x00
    RHSoundCacheListNode *m_previous; // 0x04
    unsigned long m_value; // 0x08
};

// SIZE 0x04
struct RHSoundCacheListIterator : std::iterator<std::bidirectional_iterator_tag, unsigned long>
{
    RHSoundCacheListNode *m_node; // 0x00
    RHSoundCacheListIterator() {}
    RHSoundCacheListIterator(RHSoundCacheListNode *node) : m_node(node) {}
    RHSoundCacheListIterator(const RHSoundCacheListIterator &other) : m_node(other.m_node) {}
    RHSoundCacheListIterator &operator=(const RHSoundCacheListIterator &other) { m_node = other.m_node; return *this; }
    RHSoundCacheListIterator &operator++() { m_node = m_node->m_next; return *this; }
    RHSoundCacheListIterator &operator--() { m_node = m_node->m_previous; return *this; }
    unsigned long &operator*() { return m_node->m_value; }
};

// SIZE 0x18
struct RHSoundCacheList
{
    undefined m_00; // 0x00
    RHSoundCacheListNode *m_04; // 0x04
    int m_08; // 0x08
    RHSoundCacheListIterator m_0c; // 0x0c
    bool m_10; // 0x10
    int m_14; // 0x14

    RHSoundCacheList(const std::allocator<unsigned long> &allocator = std::allocator<unsigned long>())
    {
        m_00 = *(const char *)&allocator;
        RHSoundCacheListNode *head = new RHSoundCacheListNode;
        head->m_next = head;
        head->m_previous = head;
        m_04 = head;
        m_08 = 0;
        m_10 = true;
    }
    ~RHSoundCacheList();
    void FUN_005c8e40(int);
    RHSoundCacheListIterator FUN_0046eb80();
    RHSoundCacheListIterator FUN_00424410(RHSoundCacheListIterator, const unsigned long &);
    __forceinline RHSoundCacheListIterator begin()
    {
        RHSoundCacheListNode *first = *(RHSoundCacheListNode *volatile *)&m_04->m_next;
        return RHSoundCacheListIterator(first);
    }
    __forceinline RHSoundCacheListIterator end()
    {
        return RHSoundCacheListIterator(*(RHSoundCacheListNode *volatile *)&m_04);
    }
    __forceinline void GoTo(int wanted)
    {
        int count = m_08;
        if (m_10)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                m_0c = begin();
                FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                m_0c = end();
                FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - count, category);
            }
            m_10 = false;
            m_14 = wanted;
        }
        else
        {
            int previous = m_14;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        m_0c = begin();
                        FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - previous, category);
                }
                else
                {
                    m_0c = end();
                    int distance = wanted - count;
                    for (; distance > 0; --distance)
                        ++m_0c;
                    for (; distance < 0; ++distance)
                        --m_0c;
                }
                m_14 = wanted;
            }
        }
    }
    unsigned long &operator[](int wanted)
    {
        GoTo(wanted);
        return *m_0c;
    }
};

// SIZE 0x2c
struct RHsoundGroup
{
    RHsoundGroup() {}
    ~RHsoundGroup();

    int m_00; // 0x00
    RHSoundCacheList m_04; // 0x04
    undefined m_1c[0xc]; // 0x1c
    unsigned short m_28; // 0x28
};

// SIZE 0x18
struct RHSoundCacheGroupNode
{
    RHSoundCacheGroupNode *m_00; // 0x00
    RHSoundCacheGroupNode *m_04; // 0x04
    RHSoundCacheGroupNode *m_08; // 0x08
    unsigned long m_0c; // 0x0c
    RHsoundGroup *m_10; // 0x10
    undefined4 m_14; // 0x14
};

// SIZE 0x04
struct RHSoundCacheGroupIterator
{
    RHSoundCacheGroupNode *m_node; // 0x00
    RHSoundCacheGroupIterator() {}
    RHSoundCacheGroupIterator(RHSoundCacheGroupNode *node) : m_node(node) {}
    RHSoundCacheGroupIterator(const RHSoundCacheGroupIterator &other) : m_node(other.m_node) {}
    bool operator==(const RHSoundCacheGroupIterator &other) const { return m_node == other.m_node; }
    void FUN_005b1480();
    void FUN_005b1880();
};

// SIZE 0x08
struct RHSoundCacheGroupInsert
{
    std::map<unsigned long, RHsoundGroup *>::iterator first; // 0x00
    bool second; // 0x04
    RHSoundCacheGroupInsert() {}
    RHSoundCacheGroupInsert(const RHSoundCacheGroupIterator &entry, bool inserted)
    {
        *(RHSoundCacheGroupIterator *)&first = entry;
        second = inserted;
    }
};

// SIZE 0x01
struct RHUnk00641782
{
    void FUN_00641782();
    void FUN_0064181e();
    undefined m_00; // 0x00
};

// SIZE 0x10
class RHSoundCacheGroups : public std::map<unsigned long, RHsoundGroup *>
{
public:
    RHSoundCacheGroupNode *FUN_005b13e0(const unsigned long &);
    RHSoundCacheGroupIterator FUN_005b10e0(RHSoundCacheGroupNode *, RHSoundCacheGroupNode *, const value_type &);
    RHSoundCacheGroupIterator &FUN_005afc50(RHSoundCacheGroupIterator &, const unsigned long &);
    RHSoundCacheGroupIterator End() { return RHSoundCacheGroupIterator(*(RHSoundCacheGroupNode **)((char *)this + 4)); }
    RHSoundCacheGroupIterator Find(const unsigned long &key)
    {
        RHSoundCacheGroupIterator temporary;
        RHSoundCacheGroupIterator entry = FUN_005afc50(temporary, key);
        return entry == End() || key < entry.m_node->m_0c ? End() : entry;
    }
    RHSoundCacheGroupInsert &FUN_005af600(RHSoundCacheGroupInsert &, const value_type &);
    RHsoundGroup *&operator[](const unsigned long &key)
    {
        RHSoundCacheGroupInsert temporary;
        RHSoundCacheGroupInsert result = FUN_005af600(temporary, value_type(key, 0));
        iterator entry = result.first;
        return entry->second;
    }
};

typedef std::string RHSoundCacheMusic;

// SIZE 0x58
class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &, int);
    void FUN_005f5290();
    undefined m_14[4]; // 0x14
    std::string m_18; // 0x18
    bool m_28; // 0x28
    undefined m_29[7]; // 0x29
    undefined4 m_30; // 0x30
    undefined4 m_34; // 0x34
    undefined4 m_38; // 0x38
    bool m_3c; // 0x3c
    undefined m_3d[0x1b]; // 0x3d
};

class RHProfileFile
{
public:
    int FUN_005f5370(int, int);
};

class RHMapResources
{
public:
    unsigned int FUN_00600620(unsigned long);
    bool FUN_00600bb0(unsigned long, unsigned int, std::string &);
};

extern RHMapResources *g_unk0x006c1840;

RHSoundCacheMusic *FUN_0056dbc0(RHSoundCacheMusic *, RHSoundCacheMusic *, RHSoundCacheMusic *);

// SIZE 0x2c
struct RHSoundCacheMusicArray
{
    undefined4 m_00; // 0x00
    RHSoundCacheMusic *m_04; // 0x04
    RHSoundCacheMusic *m_08; // 0x08
    RHSoundCacheMusic *m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    bool m_14; // 0x14
    undefined m_15[0x17]; // 0x15

    unsigned int Size() const { return m_04 == 0 ? 0 : m_08 - m_04; }
    RHSoundCacheMusic *begin() { return m_04; }
    RHSoundCacheMusic *end() { return m_08; }
    void FUN_0056dac0(RHSoundCacheMusic *, RHSoundCacheMusic *);
    void FUN_004023a0(RHSoundCacheMusic *, unsigned int, const RHSoundCacheMusic &);
    void erase(RHSoundCacheMusic *first, RHSoundCacheMusic *last)
    {
        RHSoundCacheMusic *next = FUN_0056dbc0(last, end(), first);
        FUN_0056dac0(next, end());
        m_08 = next;
        m_14 = true;
    }
    void push_back(const RHSoundCacheMusic &value)
    {
        FUN_004023a0(end(), 1, value);
        m_14 = true;
    }
};

struct RHSoundCacheMissionProfile
{
    undefined m_000[0xc4]; // 0x000
    std::string m_0c4; // 0x0c4
    std::string m_0d4; // 0x0d4
    std::string m_0e4; // 0x0e4
};

struct RHSoundCacheTextView
{
    undefined m_00[8]; // 0x00
    unsigned int m_08; // 0x08
    undefined m_0c[4]; // 0x0c
    int compare(const char *value) const
    {
        return ((const RHProfileText *)this)->FUN_00460900(0, m_08, value, strlen(value));
    }
};

void FUN_006416e6();
void *FUN_00642580(void *, const void *, unsigned int);
void *FUN_00643705(void *, unsigned int);

// SIZE 0x10
struct RHSoundCacheString
{
    undefined m_00; // 0x00
    char *m_04; // 0x04
    unsigned int m_08; // 0x08
    unsigned int m_0c; // 0x0c

    const char *c_str() const { return m_04 ? m_04 : ""; }
    unsigned int size() const { return m_08; }
    unsigned int capacity() const { return m_0c; }
    __forceinline void Release()
    {
        if (m_04)
        {
            char *storage = m_04 - 1;
            unsigned char references = (unsigned char)*storage;
            if (references != 0 && references != 255)
                *storage = references - 1;
            else
                operator delete(storage);
        }
        m_04 = 0;
        m_08 = 0;
        m_0c = 0;
    }
    void FUN_00402780();
    RHSoundCacheString &FUN_00402a70(unsigned int, unsigned int);
    RHSoundCacheString &erase(unsigned int position, unsigned int count = std::string::npos)
    {
        if (m_08 < position)
            std::_Xran();
        FUN_00402780();
        unsigned int available = m_08 - position;
        if (available < count)
            count = available;
        if (0 < count)
        {
            position += (unsigned int)m_04;
            char *first = (char *)position;
            FUN_00642580(first, first + count, available - count);
            unsigned int size = m_08 - count;
            if (((RHProfileText *)this)->FUN_00402280(size, false))
                ((RHProfileText *)this)->FUN_00402260(size);
        }
        return *this;
    }
    RHSoundCacheString &assign(const RHSoundCacheString &value, unsigned int position, unsigned int count)
    {
        if (value.size() < position)
            FUN_006416e6();
        unsigned int size = value.size() - position;
        if (count < size)
            size = count;
        if (this == &value)
        {
            erase(position + size);
            FUN_00402a70(0, position);
        }
        else if (0 < size && size == value.size() && (unsigned char)value.c_str()[-1] < 254)
        {
            ((RHProfileText *)this)->FUN_00401ee0(true);
            m_04 = (char *)value.c_str();
            m_08 = value.size();
            m_0c = value.capacity();
            ++m_04[-1];
        }
        else if (((RHProfileText *)this)->FUN_00402280(size, true))
        {
            memcpy(m_04, value.c_str() + position, size);
            ((RHProfileText *)this)->FUN_00402260(size);
        }
        return *this;
    }
    RHSoundCacheString &operator=(const RHSoundCacheString &value)
    {
        return assign(value, 0, std::string::npos);
    }
};

// SIZE 0x10
class RHSoundCacheEntryMap : public std::map<unsigned long, RHSoundCacheEntry *>
{
public:
    RHSoundCacheGroupNode *FUN_005b1430(const unsigned long &);
    RHSoundCacheGroupIterator FUN_005b04c0(RHSoundCacheGroupNode *, RHSoundCacheGroupNode *, const value_type &);
    std::pair<iterator, bool> FUN_005af0c0(const value_type &);
};

extern RHSoundCacheGroupNode *g_unk0x006c10a4;
extern RHSoundCacheGroupNode *g_unk0x006c10ac;

// SIZE 0x138
class RHSoundCache
{
public:
    RHsoundGroup *AddSoundGroup(RHSoundCacheGroups &, int, unsigned long, unsigned short);
    void InitializeFXCache();
    void FUN_005aca40(SBFile &, RHsoundGroup *, unsigned long);
    void InitializeExclamationsForProfile(const std::string &, unsigned long);
    RHSoundCacheEntry *AddSoundEntry(unsigned long, const std::string &, std::map<unsigned long, RHSoundCacheEntry *> &);
    unsigned long AddSoundEntry(const std::string &, struct RHcacheData &);
    unsigned long FUN_005ab430(struct RHcacheData &);
    RHSoundCacheEntry *GetFXSample(bool, unsigned long, int);
    RHSoundCacheEntry *GetExclamationSample(bool, unsigned long, unsigned long);
    void FUN_005ab7e0(RHSoundCacheEntry *, void *, unsigned short, bool);
    void InitializeMusic(const RHSoundCacheMissionProfile *);
    void InitializeMenuCache();
    RHSoundCacheMusic *GetQuietMusic(unsigned short);
    RHSoundCacheMusic *GetAlertMusic(unsigned short);
    RHSoundCacheMusic *GetFightMusic(unsigned short);
    RHSoundCacheEntry *GetSourceCacheEntryForID(unsigned long);
    void Emit(unsigned short, RHSoundCacheGroups &, const RHSoundCacheMissionProfile *);

    RHSoundCacheEntry *m_000; // 0x000
    unsigned int m_004; // 0x004
    unsigned int m_008; // 0x008
    RHSoundCacheGroups m_00c; // 0x00c
    unsigned int m_01c; // 0x01c
    undefined m_020[0x24]; // 0x020
    std::map<unsigned long, RHSoundCacheEntry *> m_044; // 0x044
    undefined m_054[0xc]; // 0x054
    RHSoundCacheEntry *m_060; // 0x060
    unsigned int m_064; // 0x064
    unsigned int m_068; // 0x068
    RHSoundCacheGroups m_06c; // 0x06c
    unsigned int m_07c; // 0x07c
    undefined m_080[0x30]; // 0x080
    RHSoundCacheMusicArray m_0b0; // 0x0b0
    RHSoundCacheMusicArray m_0dc; // 0x0dc
    RHSoundCacheMusicArray m_108; // 0x108
    bool m_134; // 0x134
    bool m_135; // 0x135
};

extern RHSoundCacheMusic g_unk0x006c1090;
extern bool g_unk0x006c0686;
extern char g_unk0x6c0560[4];
extern float g_unk0x00677f7c;

// SIZE 0x24
struct RHUnk005b1ca0
{
    RHUnk005b1ca0();
    ~RHUnk005b1ca0();
    void FUN_005b2040();
    std::string m_00; // 0x00
    void *m_10; // 0x10
    undefined4 m_14; // 0x14
    undefined4 m_18; // 0x18
    bool m_1c; // 0x1c
    undefined m_1d; // 0x1d
    undefined2 m_1e; // 0x1e
    undefined2 m_20; // 0x20
};

// SIZE 0x0c
struct RHcacheData
{
    RHSoundCacheEntry *m_00; // 0x00
    unsigned int m_04; // 0x04
    unsigned int m_08; // 0x08
};

#endif
