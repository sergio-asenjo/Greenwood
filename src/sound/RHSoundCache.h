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

#include "RHSoundCacheCore.h"

// SIZE 0x01
struct RHUnk00641782
{
    void FUN_00641782();
    void FUN_0064181e();
    undefined m_00; // 0x00
};


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

#include "RHMapResources.h"

extern RHMapResources *g_unk0x006c1840;


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
#include "RHSoundCacheString.h"

// SIZE 0x10
class RHSoundCacheEntryMap : public std::map<unsigned long, RHSoundCacheEntry *>
{
public:
    typedef RHSoundCacheEraseIterator<1> EraseIterator;
    void FUN_005aeee0();
    EraseIterator FUN_005af1f0(EraseIterator, EraseIterator);
    EraseIterator FUN_005afe60(EraseIterator);
    typedef RHSoundCacheGroupNode Node;
    static Node *&Left(Node *node) { return node->m_00; }
    static Node *&Parent(Node *node) { return node->m_04; }
    static Node *&Right(Node *node) { return node->m_08; }
    static undefined4 &Color(Node *node) { return node->m_14; }
    void FUN_005b0380(RHSoundCacheGroupNode *);
    void FUN_005b0410();
    RHSoundCacheGroupNode *&Head() { return *(RHSoundCacheGroupNode **)((char *)this + 4); }
    RHSoundCacheGroupNode *&Root() { return Head()->m_04; }
    RHSoundCacheGroupNode *&Leftmost() { return Head()->m_00; }
    RHSoundCacheGroupNode *&Rightmost() { return Head()->m_08; }
    EraseIterator Begin() { return EraseIterator(Leftmost()); }
    unsigned &Count() { return *(unsigned *)((char *)this + 0x0c); }
    RHSoundCacheGroupNode *FUN_005b1430(const unsigned long &);
    iterator find(const unsigned long &key)
    {
        RHSoundCacheGroupNode *node = FUN_005b1430(key);
        iterator entry = *(iterator *)&node;
        return entry == end() || key < (*entry).first ? end() : entry;
    }
    RHSoundCacheGroupIterator FUN_005b04c0(RHSoundCacheGroupNode *, RHSoundCacheGroupNode *, const value_type &);
    void Lrotate(RHSoundCacheGroupNode *);
    void Rrotate(RHSoundCacheGroupNode *);
    std::pair<iterator, bool> FUN_005af0c0(const value_type &);
};

extern RHSoundCacheGroupNode *g_unk0x006c10a4;
extern RHSoundCacheGroupNode *g_unk0x006c10ac;


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
