#ifndef RHSOUNDCACHECORE_H
#define RHSOUNDCACHECORE_H

#include "SB.h"
#include "Decomp.h"
#include <map>
#include <vector>

struct RHsoundGroup;
class RHSoundCacheEntry;
struct RHSoundCacheMissionProfile;

struct RHSoundCacheGroupNode
{
    RHSoundCacheGroupNode *m_00;
    RHSoundCacheGroupNode *m_04;
    RHSoundCacheGroupNode *m_08;
    unsigned long m_0c;
    RHsoundGroup *m_10;
    undefined4 m_14;
};

struct RHSoundCacheGroupIterator
{
    RHSoundCacheGroupNode *m_node;
    RHSoundCacheGroupIterator() {}
    RHSoundCacheGroupIterator(RHSoundCacheGroupNode *node) : m_node(node) {}
    RHSoundCacheGroupIterator(const RHSoundCacheGroupIterator &other) : m_node(other.m_node) {}
    bool operator==(const RHSoundCacheGroupIterator &other) const { return m_node == other.m_node; }
    void FUN_005b1480();
    void FUN_005b1880();
};

struct RHSoundCacheGroupInsert
{
    std::map<unsigned long, RHsoundGroup *>::iterator first;
    bool second;
    RHSoundCacheGroupInsert() {}
    RHSoundCacheGroupInsert(const RHSoundCacheGroupIterator &entry, bool inserted)
    {
        *(RHSoundCacheGroupIterator *)&first = entry;
        second = inserted;
    }
};

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
RHSoundCacheMusic *FUN_0056dbc0(RHSoundCacheMusic *, RHSoundCacheMusic *, RHSoundCacheMusic *);

struct RHSoundCacheMusicArray
{
    undefined4 m_00;
    RHSoundCacheMusic *m_04;
    RHSoundCacheMusic *m_08;
    RHSoundCacheMusic *m_0c;
    undefined m_10[4];
    bool m_14;
    undefined m_15[0x17];

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
        typedef void (std::vector<RHSoundCacheMusic>::*Insert)(RHSoundCacheMusic *, unsigned int, const RHSoundCacheMusic &);
        Insert insert = &std::vector<RHSoundCacheMusic>::insert;
        (((std::vector<RHSoundCacheMusic> *)this)->*insert)(end(), 1, value);
        m_14 = true;
    }
};

struct RHsampleCacheStats
{
    unsigned long m_values[3];
};

class RHSoundCache
{
public:
    RHsoundGroup *AddSoundGroup(RHSoundCacheGroups &, int, unsigned long, unsigned short);
    void FUN_005ab410(struct RHcacheData &);
    void UnloadSample(RHSoundCacheEntry *, RHsampleCacheStats &);
    void InitializeFXCache();
    void FUN_005aca40(SBFile &, RHsoundGroup *, unsigned long);
    void InitializeExclamationsForProfile(const std::string &, unsigned long);
    RHSoundCacheEntry *AddSoundEntry(unsigned long, const std::string &, std::map<unsigned long, RHSoundCacheEntry *> &);
    unsigned long AddSoundEntry(const std::string &, struct RHcacheData &);
    unsigned long FUN_005ab430(struct RHcacheData &);
    void FUN_005ab4e0(struct RHcacheData &);
    void FUN_005ab530(struct RHcacheData &, RHsampleCacheStats &);
    void UpdateCacheState(struct RHcacheData &, RHsampleCacheStats &, unsigned long);
    void UpdateCacheState(std::map<unsigned long, RHSoundCacheEntry *> &, RHsampleCacheStats &, unsigned long);
    void FUN_005ab660(std::map<unsigned long, RHSoundCacheEntry *> &, struct RHcacheData &);
    void FUN_005ab6d0(std::map<unsigned long, RHSoundCacheEntry *> &);
    RHSoundCacheEntry *GetSample(bool, std::map<unsigned long, RHSoundCacheEntry *> &, void *, unsigned long, unsigned long, unsigned long, bool);
    RHSoundCacheEntry *GetFXSample(bool, unsigned long, int);
    bool FUN_005ae320(unsigned long);
    RHSoundCacheEntry *FUN_005ae640(bool, unsigned long);
    RHSoundCacheEntry *FUN_005ae670(bool, unsigned long, bool);
    RHSoundCacheEntry *GetExclamationSample(bool, unsigned long, unsigned long);
    void FUN_005ab7e0(RHSoundCacheEntry *, void *, unsigned short, bool);
    void InitializeMusic(const RHSoundCacheMissionProfile *);
    void InitializeMenuCache();
    RHSoundCacheMusic *GetQuietMusic(unsigned short);
    RHSoundCacheMusic *GetAlertMusic(unsigned short);
    RHSoundCacheMusic *GetFightMusic(unsigned short);
    RHSoundCacheEntry *GetSourceCacheEntryForID(unsigned long);
    void GetCacheStats(RHsampleCacheStats *);
    void FUN_005aec70();
    void FUN_005ae1c0(bool);
    void FUN_005aeda0();
    void Emit(unsigned short, RHSoundCacheGroups &, const RHSoundCacheMissionProfile *);

    RHSoundCacheEntry *m_000;
    unsigned int m_004;
    unsigned int m_008;
    RHSoundCacheGroups m_00c;
    unsigned int m_01c;
    undefined m_020[0x24];
    std::map<unsigned long, RHSoundCacheEntry *> m_044;
    undefined m_054[0xc];
    RHSoundCacheEntry *m_060;
    unsigned int m_064;
    unsigned int m_068;
    RHSoundCacheGroups m_06c;
    unsigned int m_07c;
    undefined m_080[0x30];
    RHSoundCacheMusicArray m_0b0;
    RHSoundCacheMusicArray m_0dc;
    RHSoundCacheMusicArray m_108;
    bool m_134;
    bool m_135;
};

#endif
