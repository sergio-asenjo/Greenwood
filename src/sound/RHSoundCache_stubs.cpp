#include "RHSoundCache.h"

// GLOBAL: GAME 0x006c1090
RHSoundCacheMusic g_unk0x006c1090;

// GLOBAL: GAME 0x006c0686
bool g_unk0x006c0686;

RHsoundGroup::~RHsoundGroup() {}
RHSoundCacheList::~RHSoundCacheList() {}
void RHSoundCacheList::FUN_005c8e40(int) {}
RHSoundCacheListIterator RHSoundCacheList::FUN_0046eb80() { return RHSoundCacheListIterator(m_04->m_next); }
RHSoundCacheListIterator RHSoundCacheList::FUN_00424410(RHSoundCacheListIterator position, const unsigned long &value)
{
    RHSoundCacheListNode *node = new RHSoundCacheListNode;
    node->m_next = position.m_node;
    node->m_previous = position.m_node->m_previous;
    node->m_value = value;
    node->m_previous->m_next = node;
    position.m_node->m_previous = node;
    ++m_08;
    return RHSoundCacheListIterator(node);
}

unsigned int RHMapResources::FUN_00600620(unsigned long) { return 0; }
bool RHMapResources::FUN_00600bb0(unsigned long, unsigned int, std::string &) { return false; }
RHSoundCacheGroupIterator &RHSoundCacheGroups::FUN_005afc50(RHSoundCacheGroupIterator &result, const unsigned long &key)
{
    result.m_node = (RHSoundCacheGroupNode *)lower_bound(key)._Mynode();
    return result;
}
void RHSoundCache::FUN_005ab7e0(RHSoundCacheEntry *, void *, unsigned short, bool) {}

RHSoundCacheGroupInsert &RHSoundCacheGroups::FUN_005af600(RHSoundCacheGroupInsert &result, const value_type &value)
{
    std::pair<iterator, bool> inserted = insert(value);
    result.first = inserted.first;
    result.second = inserted.second;
    return result;
}

RHSoundCacheMusic *FUN_0056dbc0(RHSoundCacheMusic *, RHSoundCacheMusic *, RHSoundCacheMusic *destination)
{
    return destination;
}

void RHSoundCacheMusicArray::FUN_0056dac0(RHSoundCacheMusic *, RHSoundCacheMusic *) {}
void RHSoundCacheMusicArray::FUN_004023a0(RHSoundCacheMusic *, unsigned int, const RHSoundCacheMusic &) {}

RHUnk005b1ca0::RHUnk005b1ca0() {}
RHUnk005b1ca0::~RHUnk005b1ca0() {}
void RHUnk005b1ca0::FUN_005b2040() {}
unsigned long RHSoundCache::FUN_005ab430(RHcacheData &) { return 0; }

void FUN_006416e6() {}
void *FUN_00642580(void *destination, const void *, unsigned int) { return destination; }
void RHSoundCacheString::FUN_00402780() {}
RHSoundCacheString &RHSoundCacheString::FUN_00402a70(unsigned int, unsigned int) { return *this; }
std::pair<RHSoundCacheEntryMap::iterator, bool> RHSoundCacheEntryMap::FUN_005af0c0(const value_type &value)
{
    return insert(value);
}

void EmitRHSoundCacheInitializers(RHSoundCache &cache, const std::string &profile, unsigned long id)
{
    cache.InitializeFXCache();
    cache.InitializeExclamationsForProfile(profile, id);
    cache.InitializeMenuCache();
}
