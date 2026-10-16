#include "RHSoundCache.h"

// GLOBAL: GAME 0x006c1090
RHSoundCacheMusic g_unk0x006c1090;

// GLOBAL: GAME 0x006c0686
bool g_unk0x006c0686;

void RHUnk00641782::FUN_00641782() {}
void RHUnk00641782::FUN_0064181e() {}
void *FUN_00643705(void *memory, unsigned int size) { return realloc(memory, size); }

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




void FUN_006416e6() {}
void *FUN_00642580(void *destination, const void *, unsigned int) { return destination; }
void RHSoundCacheString::FUN_00402780() {}
RHSoundCacheGroupIterator RHSoundCacheEntryMap::FUN_005b04c0(RHSoundCacheGroupNode *, RHSoundCacheGroupNode *, const value_type &value)
{
    return RHSoundCacheGroupIterator((RHSoundCacheGroupNode *)insert(value).first._Mynode());
}

RHSoundCacheGroupIterator RHSoundCacheGroups::FUN_005b10e0(RHSoundCacheGroupNode *, RHSoundCacheGroupNode *, const value_type &value)
{
    return RHSoundCacheGroupIterator((RHSoundCacheGroupNode *)insert(value).first._Mynode());
}

void RHSoundCacheGroupIterator::FUN_005b1480()
{
    --*(RHSoundCacheEntryMap::iterator *)this;
}

void RHSoundCacheGroupIterator::FUN_005b1880()
{
    --*(RHSoundCacheGroups::iterator *)this;
}

void EmitRHSoundCacheInitializers(RHSoundCache &cache, const std::string &profile, unsigned long id)
{
    cache.InitializeFXCache();
    cache.InitializeExclamationsForProfile(profile, id);
    cache.InitializeMenuCache();
}
