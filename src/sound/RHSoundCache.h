#ifndef RHSOUNDCACHE_H
#define RHSOUNDCACHE_H

#include "SB.h"
#include "RHSoundCacheEntry.h"
#include "RHCivilianProfile.h"
#include <map>
#include <list>
#include <stdlib.h>

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

struct RHSoundCacheListNode
{
    RHSoundCacheListNode *m_next;
    RHSoundCacheListNode *m_previous;
    unsigned long m_value;
};

struct RHSoundCacheListIterator : std::iterator<std::bidirectional_iterator_tag, unsigned long>
{
    RHSoundCacheListNode *m_node;
    RHSoundCacheListIterator() {}
    RHSoundCacheListIterator(RHSoundCacheListNode *node) : m_node(node) {}
    RHSoundCacheListIterator(const RHSoundCacheListIterator &other) : m_node(other.m_node) {}
    RHSoundCacheListIterator &operator=(const RHSoundCacheListIterator &other) { m_node = other.m_node; return *this; }
    RHSoundCacheListIterator &operator++() { m_node = m_node->m_next; return *this; }
    RHSoundCacheListIterator &operator--() { m_node = m_node->m_previous; return *this; }
    unsigned long &operator*() { return m_node->m_value; }
};

struct RHSoundCacheList
{
    char m_00;
    RHSoundCacheListNode *m_04;
    int m_08;
    RHSoundCacheListIterator m_0c;
    bool m_10;
    int m_14;

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

struct RHsoundGroup
{
    RHsoundGroup() {}
    ~RHsoundGroup();

    int m_00;
    RHSoundCacheList m_04;
    unsigned char m_1c[0xc];
    unsigned short m_28;
};

struct RHSoundCacheGroupNode
{
    RHSoundCacheGroupNode *m_00;
    RHSoundCacheGroupNode *m_04;
    RHSoundCacheGroupNode *m_08;
    unsigned long m_0c;
    RHsoundGroup *m_10;
};

struct RHSoundCacheGroupIterator
{
    RHSoundCacheGroupNode *m_node;
    RHSoundCacheGroupIterator() {}
    RHSoundCacheGroupIterator(RHSoundCacheGroupNode *node) : m_node(node) {}
    RHSoundCacheGroupIterator(const RHSoundCacheGroupIterator &other) : m_node(other.m_node) {}
    bool operator==(const RHSoundCacheGroupIterator &other) const { return m_node == other.m_node; }
};

struct RHSoundCacheGroupInsert
{
    std::map<unsigned long, RHsoundGroup *>::iterator first;
    int second;
    RHSoundCacheGroupInsert() {}
};

class RHSoundCacheGroups : public std::map<unsigned long, RHsoundGroup *>
{
public:
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

class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &, int);
    void FUN_005f5290();
    unsigned char m_14[0x44];
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

struct RHSoundCacheMusicArray
{
    unsigned int m_00;
    RHSoundCacheMusic *m_04;
    RHSoundCacheMusic *m_08;
    RHSoundCacheMusic *m_0c;
    unsigned char m_10[4];
    bool m_14;
    unsigned char m_15[0x17];

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
    unsigned char m_000[0xc4];
    std::string m_0c4;
    std::string m_0d4;
    std::string m_0e4;
};

struct RHSoundCacheTextView
{
    unsigned char m_00[8];
    unsigned int m_08;
    unsigned char m_0c[4];
    int compare(const char *value) const
    {
        return ((const RHProfileText *)this)->FUN_00460900(0, m_08, value, strlen(value));
    }
};

void FUN_006416e6();
void *FUN_00642580(void *, const void *, unsigned int);

struct RHSoundCacheString
{
    char m_00;
    char *m_04;
    unsigned int m_08;
    unsigned int m_0c;

    const char *c_str() const { return m_04 ? m_04 : ""; }
    unsigned int size() const { return m_08; }
    unsigned int capacity() const { return m_0c; }
    void FUN_00402780();
    RHSoundCacheString &FUN_00402a70(unsigned int, unsigned int);
    RHSoundCacheString &erase(unsigned int position, unsigned int count = std::string::npos)
    {
        if (m_08 < position)
            FUN_006416e6();
        FUN_00402780();
        unsigned int available = m_08 - position;
        if (available < count)
            count = available;
        if (0 < count)
        {
            FUN_00642580(m_04 + position, m_04 + position + count, available - count);
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

class RHSoundCacheEntryMap : public std::map<unsigned long, RHSoundCacheEntry *>
{
public:
    std::pair<iterator, bool> FUN_005af0c0(const value_type &);
};

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

    RHSoundCacheEntry *m_000;
    unsigned int m_004;
    unsigned int m_008;
    RHSoundCacheGroups m_00c;
    unsigned int m_01c;
    unsigned char m_020[0x24];
    std::map<unsigned long, RHSoundCacheEntry *> m_044;
    unsigned char m_054[0xc];
    RHSoundCacheEntry *m_060;
    unsigned int m_064;
    unsigned int m_068;
    RHSoundCacheGroups m_06c;
    unsigned int m_07c;
    unsigned char m_080[0x30];
    RHSoundCacheMusicArray m_0b0;
    RHSoundCacheMusicArray m_0dc;
    RHSoundCacheMusicArray m_108;
    bool m_134;
    bool m_135;
};

extern RHSoundCacheMusic g_unk0x006c1090;
extern bool g_unk0x006c0686;
extern char g_unk0x6c0560[4];
extern float g_unk0x00677f7c;

struct RHUnk005b1ca0
{
    RHUnk005b1ca0();
    ~RHUnk005b1ca0();
    void FUN_005b2040();
    unsigned char m_00[0x24];
};

struct RHcacheData
{
    RHSoundCacheEntry *m_00;
    unsigned int m_04;
    unsigned int m_08;
};

#endif
