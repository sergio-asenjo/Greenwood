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
RHSoundCacheListIterator RHSoundCacheList::FUN_0046eb80() { return RHSoundCacheListIterator(m_04->m_next); }
// TEMPLATE: GAME 0x00424410 FOLDED
// ?FUN_00424410@RHSoundCacheList@@QAE?AURHSoundCacheListIterator@@U2@ABK@Z
RHSoundCacheListIterator RHSoundCacheList::FUN_00424410(RHSoundCacheListIterator position, const unsigned long &value)
{
    RHSoundCacheListNode *next = position.m_node;
    RHSoundCacheListNode *previous = next->m_previous;
    RHSoundCacheListNode *node = (RHSoundCacheListNode *)operator new(sizeof(RHSoundCacheListNode));
    node->m_next = next ? next : node;
    node->m_previous = previous ? previous : node;
    next->m_previous = node;
    node->m_previous->m_next = node;
    new (&node->m_value) unsigned long(value);
    ++m_08;
    return RHSoundCacheListIterator(node);
}

unsigned int RHMapResources::FUN_00600620(unsigned long) { return 0; }




void FUN_006416e6() {}
void RHSoundCacheString::FUN_00402780() {}

RHUnk00641782Lock::RHUnk00641782Lock() {}
RHUnk00641782Lock::~RHUnk00641782Lock() {}

RHSoundCacheGroupIterator EmitRHSoundCacheEntryInsert(RHSoundCacheEntryMap &tree, const RHSoundCacheEntryMap::value_type &value)
{
    return RHSoundCacheGroupIterator((RHSoundCacheGroupNode *)tree.insert(value).first._Mynode());
}

void EmitRHSoundCacheInitializers(RHSoundCache &cache, const std::string &profile, unsigned long id)
{
    cache.InitializeFXCache();
    cache.InitializeExclamationsForProfile(profile, id);
    cache.InitializeMenuCache();
}
