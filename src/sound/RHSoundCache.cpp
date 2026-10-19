#include "SBNullstr.h"
#include "RHSoundCache.h"
#include "RHSoundCacheSpeechList.h"

DECOMP_SIZE_ASSERT(RHSoundCache, 0x138)
DECOMP_SIZE_ASSERT(RHcacheData, 0x0c)
DECOMP_SIZE_ASSERT(RHsampleCacheStats, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005b1ca0, 0x24)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_SIZE_ASSERT(RHSoundCacheListNode, 0x0c)
DECOMP_SIZE_ASSERT(RHSoundCacheListIterator, 0x04)
DECOMP_SIZE_ASSERT(RHSoundCacheList, 0x18)
DECOMP_SIZE_ASSERT(RHsoundGroup, 0x2c)
DECOMP_SIZE_ASSERT(RHSoundCacheGroupNode, 0x18)
DECOMP_SIZE_ASSERT(RHSoundCacheGroupIterator, 0x04)
DECOMP_SIZE_ASSERT(RHSoundCacheGroupInsert, 0x08)
DECOMP_SIZE_ASSERT(RHSoundCacheGroups, 0x10)
DECOMP_SIZE_ASSERT(RHSoundCacheEntryMap, 0x10)
DECOMP_SIZE_ASSERT(RHSoundCacheMusicArray, 0x2c)
DECOMP_SIZE_ASSERT(RHSoundCacheString, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00641782, 0x01)

// LIBRARY: GAME 0x004023a0
// ?insert@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@IABV32@@Z

void RHSoundCacheMusicArray::FUN_004023a0(RHSoundCacheMusic *position, unsigned int count, const RHSoundCacheMusic &value)
{
    ((std::vector<RHSoundCacheMusic> *)this)->insert(position, count, value);
}

// LIBRARY: GAME 0x004e4b40
// ??Hstd@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@0@Z

std::string FUN_004e4b40(const std::string &first, const std::string &second)
{
    std::string result(first);
    result.append(second);
    return result;
}

// TEMPLATE: GAME 0x005014a0
// ?_Buynode@?$_Tree@KU?$pair@$$CBKPAVRHSoundCacheEntry@@@std@@U_Kfn@?$map@KPAVRHSoundCacheEntry@@U?$less@K@std@@V?$allocator@PAVRHSoundCacheEntry@@@3@@2@U?$less@K@2@V?$allocator@PAVRHSoundCacheEntry@@@2@@std@@IAEPAU_Node@12@PAU312@W4_Redbl@12@@Z

// FUNCTION: GAME 0x0056dac0
void RHSoundCacheMusicArray::FUN_0056dac0(RHSoundCacheMusic *first, RHSoundCacheMusic *last)
{
    for (; first != last; ++first)
        first->~basic_string();
}

// unannotated: 0x0056dbc0 is called by InitializeMusic; register scheduling remains unmatched.
RHSoundCacheMusic *FUN_0056dbc0(RHSoundCacheMusic *first, RHSoundCacheMusic *last, RHSoundCacheMusic *destination)
{
    for (; first != last; ++first, ++destination)
    {
        RHSoundCacheString &value = *(RHSoundCacheString *)destination;
        const RHSoundCacheString &source = *(const RHSoundCacheString *)first;
        unsigned int size = source.size();
        if (std::string::npos < size)
            size = std::string::npos;
        if (&value == &source)
        {
            value.erase(size);
            value.FUN_00402780();
        }
        else if (size > 0 && size == source.size() && (unsigned char)source.c_str()[-1] < 254)
        {
            value.Release();
            value.m_04 = (char *)source.c_str();
            value.m_08 = source.size();
            value.m_0c = source.capacity();
            ++value.m_04[-1];
        }
        else if (((RHProfileText *)&value)->FUN_00402280(size, true))
        {
            memcpy(value.m_04, source.c_str(), size);
            value.m_08 = size;
            value.m_04[size] = 0;
        }
    }
    return destination;
}

// FUNCTION: GAME 0x005ab410
void RHSoundCache::FUN_005ab410(RHcacheData &cache)
{
    memset(&cache, 0, sizeof(cache));
}

// FUNCTION: GAME 0x005ab430
unsigned long RHSoundCache::FUN_005ab430(RHcacheData &cache)
{
    if (cache.m_04 == cache.m_08)
    {
        cache.m_00 = (RHSoundCacheEntry *)FUN_00643705(cache.m_00, (cache.m_08 + 200) * sizeof(RHUnk005b1ca0));
        RHUnk005b1ca0 *first = (RHUnk005b1ca0 *)(cache.m_00 + cache.m_04);
        for (unsigned int index = 0; index < 200; ++index)
            new (first + index) RHUnk005b1ca0;
        cache.m_08 += 200;
    }
    return cache.m_04++;
}


// FUNCTION: GAME 0x005ab4e0
void RHSoundCache::FUN_005ab4e0(RHcacheData &cache)
{
    for (unsigned int index = 0; index < cache.m_04; ++index)
        ((RHUnk005b1ca0 *)cache.m_00 + index)->~RHUnk005b1ca0();
    operator delete(cache.m_00);
    memset(&cache, 0, sizeof(cache));
}


// FUNCTION: GAME 0x005ab530
void RHSoundCache::FUN_005ab530(RHcacheData &cache, RHsampleCacheStats &stats)
{
    for (unsigned int index = 0; index < cache.m_04; ++index)
    {
        RHSoundCacheEntry *entry = cache.m_00 + index;
        if (entry->m_sample)
            UnloadSample(entry, stats);
    }
}


// FUNCTION: GAME 0x005ab570
void RHSoundCache::UpdateCacheState(RHcacheData &cache, RHsampleCacheStats &stats, unsigned long elapsed)
{
    for (unsigned int index = 0; index < cache.m_04; ++index)
    {
        RHSoundCacheEntry *entry = cache.m_00 + index;
        if (*(unsigned short *)((char *)entry + 0x1e) == 0 && entry->m_stamp > 0)
        {
            if (entry->m_stamp < elapsed)
                entry->m_stamp = 0;
            else
                entry->m_stamp -= elapsed;
            if (entry->m_stamp == 0)
                UnloadSample(entry, stats);
        }
    }
}

// Parked: iterator stack-slot coloring and map/statistics register lifetimes differ.
// STUB: GAME 0x005ab5e0
void RHSoundCache::UpdateCacheState(std::map<unsigned long, RHSoundCacheEntry *> &entries, RHsampleCacheStats &stats, unsigned long elapsed)
{
    typedef std::map<unsigned long, RHSoundCacheEntry *> Map;
    typedef RHSoundCacheEraseIterator<1> Iterator;
    typedef void (Iterator::*Increment)();
    Increment increment = &Iterator::Advance;
    for (Map::iterator position = entries.begin(); position != entries.end(); (((Iterator *)&position)->*increment)())
    {
        RHSoundCacheEntry *entry = position->second;
        if (*(unsigned short *)((char *)entry + 0x1e) == 0 && entry->m_stamp > 0)
        {
            if (entry->m_stamp < elapsed)
                entry->m_stamp = 0;
            else
                entry->m_stamp -= elapsed;
            if (entry->m_stamp == 0)
                UnloadSample(entry, stats);
        }
    }
}

// Reconstructed cache-map and backing-array teardown; sample accounting remains incomplete.
// STUB: GAME 0x005ab660
void RHSoundCache::FUN_005ab660(std::map<unsigned long, RHSoundCacheEntry *> &entries, RHcacheData &cache)
{
    for (std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = entries.begin(); entry != entries.end(); ((RHSoundCacheEraseIterator<1> *)&entry)->Advance())
    {
        delete entry->second;
        entry->second = 0;
    }
    entries.clear();
    FUN_005ab4e0(cache);
}

// Reconstructed map-entry destruction and clear; target-specific node helpers remain unresolved.
// STUB: GAME 0x005ab6d0
void RHSoundCache::FUN_005ab6d0(std::map<unsigned long, RHSoundCacheEntry *> &entries)
{
    for (std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = entries.begin(); entry != entries.end(); ((RHSoundCacheEraseIterator<1> *)&entry)->Advance())
    {
        delete entry->second;
        entry->second = 0;
    }
    entries.clear();
}

// Parked 25.48%: the candidate map lookup is reconstructed, but argument-slot lifetime, sample-state updates, and entry return scheduling differ.
// STUB: GAME 0x005ab730
RHSoundCacheEntry *RHSoundCache::GetSample(bool load, std::map<unsigned long, RHSoundCacheEntry *> &entries, void *stats, unsigned long stamp, unsigned long lifetime, unsigned long id, bool spatial)
{
    std::map<unsigned long, RHSoundCacheEntry *>::iterator found = entries.lower_bound(id);
    if (found == entries.end() || found->first != id)
        return 0;
    RHSoundCacheEntry *entry = found->second;
    entry->m_stamp = (unsigned short)stamp;
    if (load)
    {
        if (entry->m_sample)
        {
            ++*(unsigned long *)stats;
            entry->m_stamp = (unsigned short)(entry->m_stamp + lifetime);
            return entry;
        }
        FUN_005ab7e0(entry, stats, (unsigned short)lifetime, spatial);
    }
    else if (entry->m_duration == 0)
        FUN_005ab7e0(entry, stats, (unsigned short)lifetime, spatial);
    return entry;
}

// FUNCTION: GAME 0x005ab7e0
void RHSoundCache::FUN_005ab7e0(RHSoundCacheEntry *entry, void *data, unsigned short stamp, bool spatial)
{
    entry->LoadSample(spatial, stamp);
    if (entry->m_sample)
    {
        RHcacheData &cache = *(RHcacheData *)data;
        ++cache.m_04;
        cache.m_08 += entry->m_size;
    }
}

// FUNCTION: GAME 0x005ab820
void RHSoundCache::UnloadSample(RHSoundCacheEntry *entry, RHsampleCacheStats &stats)
{
    stats.m_values[2] -= entry->m_size;
    ((RHUnk005b1ca0 *)entry)->FUN_005b2040();
}

// FUNCTION: GAME 0x005ab840
RHsoundGroup *RHSoundCache::AddSoundGroup(RHSoundCacheGroups &groups, int type, unsigned long id, unsigned short stamp)
{
    if (groups.find(id) != groups.end())
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 474,
            // STRING: GAME 0x006b8158
            "FATAL: Sound group %d already allocated.", id);
    RHsoundGroup *group = new RHsoundGroup;
    group->m_00 = type;
    if (type == 1)
        group->m_28 = stamp;
    else
        group->m_28 = 0;
    groups[id] = group;
    return group;
}

// String expansion and EH scheduling remain unmatched.
// STUB: GAME 0x005ab960
void RHSoundCache::InitializeFXCache()
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(g_unk0x006c0600 +
        // STRING: GAME 0x006b8210
        "\\robin hood.fxg", 1))
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 520,
            // STRING: GAME 0x006b81f8
            "Unable to open FX bank");
    unsigned long value, count;
    file.Access(&value, 4);
    if (value != 0x4b425846)
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 529,
            "Invalid FX ID bank file");
    file.Access(&value, 4);
    file.Access(&value, 4);
    file.Access(&count, 4);
    for (unsigned short item = 0; item < count; ++item)
    {
        unsigned long type, id;
        unsigned short flags;
        file.Access(&type, 4);
        file.Access(&id, 4);
        file.Access(&flags, 2);
        if (id & 0xffff0000)
            SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 557,
                // STRING: GAME 0x006b81c4
                "Found an invalid FX ID : %x", id);
        if (type <= 1)
        {
            unsigned short stamp;
            unsigned long variants;
            file.Access(&stamp, 2);
            file.Access(&variants, 4);
            RHsoundGroup *group = AddSoundGroup(m_00c, type, id, stamp);
            FUN_005aca40(file, group, variants);
            item = (unsigned short)(item + variants);
        }
        else if (type == 2)
        {
            unsigned short length;
            file.Access(&length, 2);
            char *text = (char *)operator new(length + 5);
            text[length] = 0;
            file.Access(text, length);
            if (length > 4 && text[length - 4] != '.')
                strcat(text, ".wav");
            RHsoundGroup *group = AddSoundGroup(m_00c, type, id, 0);
            unsigned long index = AddSoundEntry(std::string(text), *(RHcacheData *)this);
            group->m_04.FUN_00424410(RHSoundCacheListIterator(group->m_04.m_04), index);
            group->m_04.m_10 = true;
            operator delete(text);
        }
    }
    const char *pairs[10] = { "wowo", "wost", "woci", "wosw", "stst", "stci", "stsw", "cici", "cisw", "swsw" };
    const char *materials[12] = { "wolt", "wocm", "wopl", "stlt", "stcm", "stpl", "cilt", "cicm", "cipl", "swlt", "swcm", "swpl" };
    std::map<unsigned long, RHSoundCacheEntry *> &combat =
        *(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x28);
    unsigned long index = 0;
    for (int pair = 0; pair < 10; ++pair)
    {
        AddSoundEntry(index++, std::string("ssw1") + pairs[pair % 10] + ".wav", combat);
        AddSoundEntry(index++, std::string("ssw2") + pairs[pair % 10] + ".wav", combat);
    }
    for (int light = 0; light < 10; ++light)
    {
        AddSoundEntry(index++, std::string("slp1") + pairs[light % 10] + ".wav", combat);
        AddSoundEntry(index++, std::string("slp2") + pairs[light % 10] + ".wav", combat);
    }
    for (int heavy = 0; heavy < 10; ++heavy)
    {
        AddSoundEntry(index++, std::string("shp1") + pairs[heavy % 10] + ".wav", combat);
        AddSoundEntry(index++, std::string("shp2") + pairs[heavy % 10] + ".wav", combat);
    }
    for (int lightImpact = 0; lightImpact < 12; ++lightImpact)
        AddSoundEntry(index++, std::string("ila_") + materials[lightImpact % 12] + ".wav", combat);
    for (int heavyImpact = 0; heavyImpact < 12; ++heavyImpact)
        AddSoundEntry(index++, std::string("iha_") + materials[heavyImpact % 12] + ".wav", combat);
}

// String/list temporaries and EH slots remain unmatched.
// STUB: GAME 0x005aca40
void RHSoundCache::FUN_005aca40(SBFile &file, RHsoundGroup *group, unsigned long count)
{
    while (count != 0)
    {
        unsigned long bank, resource;
        unsigned short flags, length;
        file.Access(&bank, 4);
        file.Access(&resource, 4);
        file.Access(&flags, 2);
        file.Access(&length, 2);
        char *text = (char *)operator new(length + 5);
        text[length] = 0;
        file.Access(text, length);
        if (length > 4 && text[length - 4] != '.')
            strcat(text, ".wav");
        if (group)
        {
            unsigned long index = AddSoundEntry(std::string(text), *(RHcacheData *)this);
            group->m_04.FUN_00424410(RHSoundCacheListIterator(group->m_04.m_04), index);
            group->m_04.m_10 = true;
        }
        operator delete(text);
        --count;
    }
}

// String temporaries and EH layout remain unmatched.
// STUB: GAME 0x005acc50
void RHSoundCache::InitializeExclamationsForProfile(const std::string &profile, unsigned long id)
{
    RHUnk005f4fc0 file;
    std::string path = g_unk0x006c0600 + std::string(
        // STRING: GAME 0x006b82c8
        "\\Exclamations\\") + profile;
    if (file.FUN_005f5090(path, 1))
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 777,
            // STRING: GAME 0x006b82ac
            "Missing exclamation file %s", path.c_str());
    unsigned long magic, version, bank, groups;
    file.Access(&magic, 4);
    if (magic != 0x4655454e)
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 785,
            // STRING: GAME 0x006b829c
            "Invalid file %s", path.c_str());
    file.Access(&version, 4);
    if (version != 1)
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 792,
            // STRING: GAME 0x006b8280
            "Invalid file version for %s", path.c_str());
    file.Access(&bank, 4);
    RHMapResources *resources = g_unk0x006c1840;
    unsigned int resourcesCount = resources->FUN_00600620(bank);
    file.Access(&groups, 4);
    for (unsigned int groupIndex = 0; groupIndex < groups; ++groupIndex)
    {
        unsigned long variants;
        file.Access(&variants, 4);
        RHsoundGroup *group = AddSoundGroup(m_06c, 1, id | (short)groupIndex, 0);
        for (unsigned int variant = 0; variant < variants; ++variant)
        {
            std::string name;
            unsigned long resource;
            file.Access(&resource, 4);
            if (resource >= resourcesCount)
                SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 826,
                    // STRING: GAME 0x006b8230
                    "Invalid exclamation resource index ! (ID = %u, Exclamation = %u, Variant = %u)",
                    (unsigned char)(id >> 16), groupIndex, variant);
            resources->FUN_00600bb0(bank, resource, name);
            name = std::string(
                // STRING: GAME 0x006b8220
                "Exclamations\\") + name;
            unsigned long index = AddSoundEntry(name, *(RHcacheData *)&m_060);
            group->m_04.FUN_00424410(RHSoundCacheListIterator(group->m_04.m_04), index);
            group->m_04.m_10 = true;
        }
    }
    file.FUN_005f5290();
}

// FUNCTION: GAME 0x005ad160
RHSoundCacheEntry *RHSoundCache::AddSoundEntry(unsigned long id, const std::string &name, std::map<unsigned long, RHSoundCacheEntry *> &entries)
{
    RHSoundCacheEntry *entry = (RHSoundCacheEntry *)new RHUnk005b1ca0;
    typedef std::string &(std::string::*Assign)(const std::string &, unsigned int, unsigned int);
    Assign assign = &std::string::assign;
    (((std::string *)entry)->*assign)(name, 0, std::string::npos);
    if (g_unk0x006c0686)
    {
        if (!entry->LoadSample(m_134, 0))
        {
            SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 867,
                // STRING: GAME 0x006b82d8
                "RHSoundCache: Unable to load sample \"%s\" !\n", ((const RHProfileText *)&name)->c_str());
            m_135 = false;
        }
        else
            ((RHUnk005b1ca0 *)entry)->FUN_005b2040();
    }
    ((RHSoundCacheEntryMap *)&entries)->FUN_005af0c0(std::map<unsigned long, RHSoundCacheEntry *>::value_type(id, entry));
    return entry;
}

// FUNCTION: GAME 0x005ad250
unsigned long RHSoundCache::AddSoundEntry(const std::string &name, RHcacheData &cache)
{
    unsigned long index = FUN_005ab430(cache);
    *(RHSoundCacheString *)&cache.m_00[index].m_name = (const RHSoundCacheString &)name;
    if (g_unk0x006c0686)
    {
        if (!cache.m_00[index].LoadSample(m_134, 0))
        {
            SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 909,
                "RHSoundCache: Unable to load sample \"%s\" !\n", ((const RHProfileText *)&name)->c_str());
            m_135 = false;
            return index;
        }
        else
            ((RHUnk005b1ca0 *)&cache.m_00[index])->FUN_005b2040();
    }
    return index;
}

// FUNCTION: GAME 0x005ad930
void RHSoundCache::InitializeMusic(const RHSoundCacheMissionProfile *profile)
{
    RHSoundCacheMusicArray &quiet = m_0b0;
    quiet.erase(quiet.begin(), quiet.end());
    RHSoundCacheMusicArray &alert = m_0dc;
    alert.erase(alert.begin(), alert.end());
    RHSoundCacheMusicArray &fight = m_108;
    fight.erase(fight.begin(), fight.end());
    const std::string &green = profile->m_0c4;
    quiet.push_back(green);
    const std::string &yellow = profile->m_0d4;
    alert.push_back(yellow);
    const std::string &red = profile->m_0e4;
    fight.push_back(red);
    if (g_unk0x006c0686)
    {
        if (((const RHSoundCacheTextView *)&green)->compare(g_unk0x6c0560) == 0)
            SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 1039,
                // STRING: GAME 0x006b8370
                "RHSoundCache: missing green music loop");
        if (yellow.compare(g_unk0x6c0560) == 0)
            SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 1044,
                // STRING: GAME 0x006b8348
                "RHSoundCache: missing yellow music loop");
        if (red.compare(g_unk0x6c0560) == 0)
            SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 1049,
                // STRING: GAME 0x006b8320
                "RHSoundCache: missing red music loop");
    }
}

// String temporaries and EH layout remain unmatched.
// STUB: GAME 0x005adb20
void RHSoundCache::InitializeMenuCache()
{
    std::string unused;
    RHUnk005f4fc0 file;
    std::string name;
    std::string path = g_unk0x006c0600 + std::string(
        // STRING: GAME 0x006b83e4
        "\\menu\\menu.fxg");
    if (file.FUN_005f5090(path, 1))
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1081,
            // STRING: GAME 0x006b83c0
            "Unable to open menu sound bank !");
    unsigned long value, count;
    file.Access(&value, 4);
    if (value != 0x4b425846)
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1088,
            // STRING: GAME 0x006b81e0
            "Invalid FX ID bank file");
    file.Access(&value, 4);
    file.Access(&value, 4);
    file.Access(&count, 4);
    for (unsigned int item = 0; item < count; ++item)
    {
        unsigned long type, bank, variants, resource;
        unsigned short flags, stamp, length, extra;
        file.Access(&type, 4);
        file.Access(&bank, 4);
        file.Access(&flags, 2);
        if (type != 0)
        {
            SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1184,
                // STRING: GAME 0x006b83a0
                "Invalid menu sound bank file !");
            continue;
        }
        file.Access(&stamp, 2);
        file.Access(&variants, 4);
        for (unsigned int variant = 0; variant < 2; ++variant)
        {
            file.Access(&bank, 4);
            file.Access(&resource, 4);
            file.Access(&extra, 2);
            file.Access(&length, 2);
            char *text = (char *)operator new(length + 5);
            text[(unsigned short)item] = 0;
            file.Access(text, length);
            if (length > 4 && text[length - 4] != '.')
                strcat(text, ".wav");
            name = std::string(
                // STRING: GAME 0x006b8398
                "\\Menu\\") + std::string(text);
            AddSoundEntry((bank << 16) | variant, std::string(name.c_str()),
                *(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x94));
            operator delete(text);
        }
        for (unsigned int skipped = 2; skipped < variants; ++skipped)
        {
            file.Access(&bank, 4);
            file.Access(&resource, 4);
            file.Access(&extra, 2);
            file.Access(&length, 2);
            ((RHProfileFile *)&file)->FUN_005f5370(length, 1);
        }
        item += variants;
    }
    file.FUN_005f5290();
}

static void ClearSoundMusic(RHSoundCacheMusicArray &music)
{
    typedef std::string &(std::string::*Assign)(const std::string &, unsigned int, unsigned int);
    Assign assign = &std::string::assign;
    std::string *destination = music.begin();
    for (std::string *source = music.end(); source != music.end(); ++source, ++destination)
        (destination->*assign)(*source, 0, *(const volatile unsigned int *)&std::string::npos);
    for (std::string *entry = destination; entry != music.end(); ++entry)
        entry->~basic_string();
    music.m_08 = destination;
    music.m_14 = true;
}

// Parked: music erase helper stays out of line; inline variants expand string cleanup.
// STUB: GAME 0x005ae1c0
void RHSoundCache::FUN_005ae1c0(bool clear)
{
    if (clear)
    {
        FUN_005ab660(*(std::map<unsigned long, RHSoundCacheEntry *> *)&m_00c, *(RHcacheData *)this);
        FUN_005ab6d0(*(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x28));
        FUN_005ab660(*(std::map<unsigned long, RHSoundCacheEntry *> *)&m_06c, *(RHcacheData *)((char *)this + 0x60));
        FUN_005ab6d0(*(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x94));
    }
    FUN_005ab6d0(m_044);
    ClearSoundMusic(m_0b0);
    ClearSoundMusic(m_0dc);
    ClearSoundMusic(m_108);
    FUN_005aec70();
}

// FUNCTION: GAME 0x005ae320
bool RHSoundCache::FUN_005ae320(unsigned long id)
{
    RHSoundCacheGroups &groups = m_00c;
    RHSoundCacheGroupNode *found = groups.FUN_005b13e0(id);
    RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode *volatile *)((char *)&groups + 4);
    RHSoundCacheGroupIterator entry;
    *(RHSoundCacheGroupNode *volatile *)&entry.m_node = found;
    RHSoundCacheGroupIterator chosen = found == head || id < found->m_0c ? RHSoundCacheGroupIterator(head) : entry;
    if (chosen.m_node == *(RHSoundCacheGroupNode **)((char *)this + 0x10))
        return false;
    return chosen.m_node->m_10->m_00 == 0;
}

// FUNCTION: GAME 0x005ae380
RHSoundCacheEntry *RHSoundCache::GetFXSample(bool load, unsigned long id, int material)
{
    RHSoundCacheEntry *entry = 0;
    RHSoundCacheGroupIterator found = m_00c.Find(id);
    if (found == m_00c.End())
        return 0;
    RHsoundGroup *group = found.m_node->m_10;
    unsigned long index;
    switch (group->m_00)
    {
    case 0:
        {
            if (material >= 9)
            {
                SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 1345,
                    // STRING: GAME 0x006b83f4
                    "Warning: Incorrect material type supplied (SFX id %d). Probably due an inccorect edition of the animation !", id);
                return 0;
            }
            RHSoundCacheList &samples = group->m_04;
            samples.FUN_005c8e40(material);
            index = *samples.m_0c;
            goto sample;
        }
    case 1:
        {
            int count = group->m_04.m_08;
            unsigned short wanted = (unsigned short)((rand() * ((unsigned short)count + group->m_28)) * g_unk0x00677f7c);
            if (wanted >= (unsigned short)count)
                goto done;
            index = group->m_04[wanted];
        }
        goto sample;
    case 2:
        {
            RHSoundCacheList &samples = group->m_04;
            samples.FUN_005c8e40(0);
            index = *samples.m_0c;
            goto sample;
        }
    default:
        goto done;
    }
sample:
    if (index != (unsigned long)-1)
    {
        entry = m_000 + index;
        if (load)
        {
            if (entry->m_sample != 0)
            {
                ++m_01c;
                entry->m_stamp += 200;
                goto done;
            }
            FUN_005ab7e0(entry, &m_01c, 400, m_134);
            goto done;
        }
        if (entry->m_duration == 0)
            FUN_005ab7e0(entry, &m_01c, 400, m_134);
    }
done:
    return entry;
}

// FUNCTION: GAME 0x005ae640
RHSoundCacheEntry *RHSoundCache::FUN_005ae640(bool load, unsigned long id)
{
    return GetSample(load, *(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x28),
        (char *)this + 0x38, 400, 200, id, false);
}

// FUNCTION: GAME 0x005ae670
RHSoundCacheEntry *RHSoundCache::FUN_005ae670(bool load, unsigned long id, bool spatial)
{
    return GetSample(load, m_044, m_054, 400, 200, id, spatial);
}

// Cached-list control flow remains unmatched.
// STUB: GAME 0x005ae6a0
RHSoundCacheEntry *RHSoundCache::GetExclamationSample(bool load, unsigned long id, unsigned long variant)
{
    RHSoundCacheGroupIterator found = m_06c.Find(id);
    RHsoundGroup *group;
    int count;
    if (found == m_06c.End())
        goto missing;
    group = found.m_node->m_10;
    if (group->m_00 != 1)
        SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1460,
            // STRING: GAME 0x006b8498
            "Speech groups MUST be random ones !");
    RHSoundCacheEntry *entry;
    count = group->m_04.m_08;
    if (variant == (unsigned long)-1)
        goto random;
    if (variant < (unsigned short)count)
    {
        entry = m_060 + ((RHSoundCacheSpeechList *)&group->m_04)->SpeechAt(variant);
        goto sample;
    }
    SBAssert(0, "P:\\Robin Hood\\RHsoundcache.cpp", 1474,
        // STRING: GAME 0x006b8460
        "Trying to get a speech variant that doesn't exists !");
missing:
    return 0;
random:
    {
        unsigned short wanted = (unsigned short)((rand() * ((unsigned short)count + group->m_28)) * g_unk0x00677f7c);
        if (wanted >= (unsigned short)count)
            goto missing;
        entry = m_060 + ((RHSoundCacheSpeechList *)&group->m_04)->SpeechAt(wanted);
    }
sample:
    if (load)
    {
        if (entry->m_sample != 0)
        {
            ++m_07c;
            entry->m_stamp += 200;
            return entry;
        }
        FUN_005ab7e0(entry, &m_07c, 400, m_134);
        return entry;
    }
    if (entry->m_duration == 0)
        FUN_005ab7e0(entry, &m_07c, 400, m_134);
    return entry;
}

// FUNCTION: GAME 0x005aea90
RHSoundCacheMusic *RHSoundCache::GetQuietMusic(unsigned short index)
{
    if ((int)m_0b0.Size() > 0)
    {
        if (index > (int)m_0b0.Size())
            SBAssert(1,
                // STRING: GAME 0x006b80e0
                "P:\\Robin Hood\\RHsoundcache.cpp", 1572,
                // STRING: GAME 0x006b84bc
                "Trying to get an non existing music loop for quiet mode");
        return m_0b0.m_04 + index;
    }
    return &g_unk0x006c1090;
}

// FUNCTION: GAME 0x005aeb10
RHSoundCacheMusic *RHSoundCache::GetAlertMusic(unsigned short index)
{
    if ((int)m_0dc.Size() > 0)
    {
        if (index > (int)m_0dc.Size())
            SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1600,
                // STRING: GAME 0x006b84f4
                "Trying to get an non existing music loop for alert mode");
        return m_0dc.m_04 + index;
    }
    return &g_unk0x006c1090;
}

// FUNCTION: GAME 0x005aeb90
RHSoundCacheMusic *RHSoundCache::GetFightMusic(unsigned short index)
{
    if ((int)m_108.Size() > 0)
    {
        if (index > (int)m_108.Size())
            SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1628,
                // STRING: GAME 0x006b852c
                "Trying to get an non existing music loop for fight mode");
        return m_108.m_04 + index;
    }
    return &g_unk0x006c1090;
}

// FUNCTION: GAME 0x005aec70
void RHSoundCache::FUN_005aec70()
{
    unsigned long *fields = (unsigned long *)this;
    fields[7] = 0;
    fields[8] = 0;
    fields[9] = 0;
    fields[14] = 0;
    fields[15] = 0;
    fields[16] = 0;
    fields[21] = 0;
    fields[22] = 0;
    fields[23] = 0;
    fields[31] = 0;
    fields[32] = 0;
    fields[33] = 0;
    fields[34] = 0;
    fields[35] = 0;
    fields[36] = 0;
}

// FUNCTION: GAME 0x005aecb0
void RHSoundCache::GetCacheStats(RHsampleCacheStats *stats)
{
    stats->m_values[0] = m_01c;
    stats->m_values[1] = *(unsigned long *)((char *)this + 0x20);
    stats->m_values[2] = *(unsigned long *)((char *)this + 0x24);
    stats[1].m_values[0] = *(unsigned long *)((char *)this + 0x54);
    stats[1].m_values[1] = *(unsigned long *)((char *)this + 0x58);
    stats[1].m_values[2] = *(unsigned long *)((char *)this + 0x5c);
    stats[2].m_values[0] = m_07c;
    stats[2].m_values[1] = *(unsigned long *)((char *)this + 0x80);
    stats[2].m_values[2] = *(unsigned long *)((char *)this + 0x84);
    stats[3].m_values[0] = *(unsigned long *)((char *)this + 0x54) + m_07c + m_01c;
    stats[3].m_values[1] = *(unsigned long *)((char *)this + 0x58) + *(unsigned long *)((char *)this + 0x80) + *(unsigned long *)((char *)this + 0x20);
    stats[3].m_values[2] = *(unsigned long *)((char *)this + 0x84) + *(unsigned long *)((char *)this + 0x24) + *(unsigned long *)((char *)this + 0x5c);
}

// FUNCTION: GAME 0x005aed30
RHSoundCacheEntry *RHSoundCache::GetSourceCacheEntryForID(unsigned long id)
{
    std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = ((RHSoundCacheEntryMap &)m_044).find(id);
    if (entry != m_044.end())
        return entry->second;
    SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1782,
        // STRING: GAME 0x006b8564
        "Unable to find cache entry for id %d !", id);
    return 0;
}

// Parked: loop-back node reloads precede sentinel reloads; effective-only match.
// STUB: GAME 0x005aeda0
void RHSoundCache::FUN_005aeda0()
{
    typedef std::map<unsigned long, RHSoundCacheEntry *> Map;
    typedef RHSoundCacheEraseIterator<1> Iterator;
    typedef void (Iterator::*Increment)();
    Increment increment = &Iterator::Advance;
    FUN_005ab530(*(RHcacheData *)this, *(RHsampleCacheStats *)((char *)this + 0x1c));
    Map &first = *(Map *)((char *)this + 0x28);
    Map::iterator position = first.begin();
    for (; position != first.end(); (((Iterator *)&position)->*increment)())
    {
        RHSoundCacheEntry *entry = position->second;
        if (entry->m_sample)
            UnloadSample(entry, *(RHsampleCacheStats *)((char *)this + 0x38));
    }
    position = m_044.begin();
    for (; position != m_044.end(); (((Iterator *)&position)->*increment)())
    {
        RHSoundCacheEntry *entry = position->second;
        if (entry->m_sample)
            UnloadSample(entry, *(RHsampleCacheStats *)((char *)this + 0x54));
    }
    FUN_005ab530(*(RHcacheData *)((char *)this + 0x60), *(RHsampleCacheStats *)((char *)this + 0x7c));
    Map &last = *(Map *)((char *)this + 0x94);
    position = last.begin();
    for (; position != last.end(); (((Iterator *)&position)->*increment)())
    {
        RHSoundCacheEntry *entry = position->second;
        if (entry->m_sample)
            UnloadSample(entry, *(RHsampleCacheStats *)((char *)this + 0x54));
    }
}

// GLOBAL: GAME 0x006c10a8
unsigned g_unk0x006c10a8;

// GLOBAL: GAME 0x006c10b0
unsigned g_unk0x006c10b0;

// FUNCTION: GAME 0x005aee70
void RHSoundCacheGroups::FUN_005aee70()
{
    EraseIterator first(Leftmost());
    EraseIterator last(Head());
    FUN_005aef90(first, last);
    operator delete(Head());
    Head() = 0;
    Count() = 0;
    {
        RHUnk00641782Lock lock;
        if (--g_unk0x006c10a8 == 0) {
            operator delete(g_unk0x006c10a4);
            g_unk0x006c10a4 = 0;
        }
    }
}

// FUNCTION: GAME 0x005aeee0
void RHSoundCacheEntryMap::FUN_005aeee0()
{
    EraseIterator first(Leftmost());
    EraseIterator last(Head());
    FUN_005af1f0(first, last);
    operator delete(Head());
    Head() = 0;
    Count() = 0;
    {
        RHUnk00641782Lock lock;
        if (--g_unk0x006c10b0 == 0) {
            operator delete(g_unk0x006c10ac);
            g_unk0x006c10ac = 0;
        }
    }
}

// LIBRARY: GAME 0x005aef50
// ??1?$pair@$$CBKV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@QAE@XZ

// FUNCTION: GAME 0x005aef90
RHSoundCacheGroups::EraseIterator RHSoundCacheGroups::FUN_005aef90(EraseIterator first, EraseIterator last)
{
    if (Count() != 0 && first.m_node == Head()->m_00 && last.m_node == Head()) {
        RHUnk00641782Lock lock;
        RHSoundCacheGroupNode *node = Root();
        {
            RHUnk00641782Lock inner;
            for (RHSoundCacheGroupNode *next = node; next != g_unk0x006c10a4; node = next) {
                FUN_005afc70(next->m_08);
                next = next->m_00;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c10a4;
        Count() = 0;
        Leftmost() = Head();
        Rightmost() = Head();
        return Begin();
    }
    while (first != last)
        FUN_005af730(first++);
    return first;
}

// FUNCTION: GAME 0x005af0c0
std::pair<RHSoundCacheEntryMap::iterator, bool> RHSoundCacheEntryMap::FUN_005af0c0(const value_type &value)
{
    RHSoundCacheGroupNode *parent = *(RHSoundCacheGroupNode **)((char *)this + 4);
    RHSoundCacheGroupNode *node = parent->m_04;
    bool left = true;
    RHUnk00641782 lock;
    lock.FUN_00641782();
    while (node != g_unk0x006c10ac)
    {
        parent = node;
        left = value.first < node->m_0c;
        node = left ? node->m_00 : node->m_08;
    }
    lock.FUN_0064181e();
    if (*(bool *)((char *)this + 8))
    {
        std::pair<iterator, bool> result((const iterator &)FUN_005b04c0(node, parent, value), true);
        return result;
    }
    RHSoundCacheGroupIterator previous(parent);
    if (left)
    {
        RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode **)((char *)this + 4);
        if (parent == head->m_00)
        {
            std::pair<iterator, bool> result((const iterator &)FUN_005b04c0(node, parent, value), true);
            return result;
        }
        previous.FUN_005b1480();
    }
    if (previous.m_node->m_0c < value.first)
    {
        std::pair<iterator, bool> result((const iterator &)FUN_005b04c0(node, parent, value), true);
        return result;
    }
    std::pair<iterator, bool> result((const iterator &)previous, false);
    return result;
}

// FUNCTION: GAME 0x005af1f0
RHSoundCacheEntryMap::EraseIterator RHSoundCacheEntryMap::FUN_005af1f0(EraseIterator first, EraseIterator last)
{
    if (Count() != 0 && first.m_node == Head()->m_00 && last.m_node == Head()) {
        RHUnk00641782Lock lock;
        RHSoundCacheGroupNode *node = Root();
        {
            RHUnk00641782Lock inner;
            for (RHSoundCacheGroupNode *next = node; next != g_unk0x006c10ac; node = next) {
                FUN_005b0380(next->m_08);
                next = next->m_00;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c10ac;
        Count() = 0;
        Leftmost() = Head();
        Rightmost() = Head();
        return Begin();
    }
    while (first != last)
        FUN_005afe60(first++);
    return first;
}

void EmitRHSoundCacheErase(RHSoundCacheGroups *groups, RHSoundCacheEntryMap *entries)
{
    groups->FUN_005aee70();
    entries->FUN_005aeee0();
    groups->FUN_005aef90(groups->Begin(), RHSoundCacheGroups::EraseIterator(groups->Head()));
    entries->FUN_005af1f0(entries->Begin(), RHSoundCacheEntryMap::EraseIterator(entries->Head()));
}

// FUNCTION: GAME 0x005af600
RHSoundCacheGroupInsert &RHSoundCacheGroups::FUN_005af600(RHSoundCacheGroupInsert &output, const value_type &value)
{
    RHSoundCacheGroupNode *parent = *(RHSoundCacheGroupNode **)((char *)this + 4);
    RHSoundCacheGroupNode *node = parent->m_04;
    bool left = true;
    RHUnk00641782 lock;
    lock.FUN_00641782();
    while (node != g_unk0x006c10a4)
    {
        parent = node;
        left = value.first < node->m_0c;
        node = left ? node->m_00 : node->m_08;
    }
    lock.FUN_0064181e();
    if (*(bool *)((char *)this + 8))
    {
        output = RHSoundCacheGroupInsert(FUN_005b10e0(node, parent, value), true);
        return output;
    }
    RHSoundCacheGroupIterator previous(parent);
    if (left)
    {
        RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode **)((char *)this + 4);
        if (parent == head->m_00)
        {
            output = RHSoundCacheGroupInsert(FUN_005b10e0(node, parent, value), true);
            return output;
        }
        previous.FUN_005b1880();
    }
    if (previous.m_node->m_0c < value.first)
    {
        output = RHSoundCacheGroupInsert(FUN_005b10e0(node, parent, value), true);
        return output;
    }
    output = RHSoundCacheGroupInsert(previous, false);
    return output;
}

static inline RHSoundCacheGroupNode *RHSoundCacheGroupMinimum(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c10a4)
        node = node->m_00;
    return node;
}

static inline RHSoundCacheGroupNode *RHSoundCacheGroupMaximum(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c10a4)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x005af730
RHSoundCacheGroups::EraseIterator RHSoundCacheGroups::FUN_005af730(EraseIterator position)
{
    Node *x;
    Node *y = (position++).m_node;
    Node *z = y;
    RHUnk00641782Lock lock;
    if (Left(y) == g_unk0x006c10a4)
        x = Right(y);
    else if (Right(y) == g_unk0x006c10a4)
        x = Left(y);
    else
    {
        y = RHSoundCacheGroupMinimum(Right(y));
        x = Right(y);
    }
    {
        if (y != z)
        {
            Parent(Left(z)) = y;
            Left(y) = Left(z);
            if (y == Right(z))
                Parent(x) = y;
            else
            {
                Parent(x) = Parent(y);
                Left(Parent(y)) = x;
                Right(y) = Right(z);
                Parent(Right(z)) = y;
            }
            if (Root() == z)
                Root() = y;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = y;
            else
                Right(Parent(z)) = y;
            Parent(y) = Parent(z);
            std::swap(Color(y), Color(z));
            y = z;
        }
        else
        {
            Parent(x) = Parent(y);
            if (Root() == z)
                Root() = x;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = x;
            else
                Right(Parent(z)) = x;
            if (Leftmost() == z)
            {
                if (Right(z) == g_unk0x006c10a4)
                    Leftmost() = Parent(z);
                else
                    Leftmost() = RHSoundCacheGroupMinimum(x);
            }
            if (Rightmost() == z)
            {
                if (Left(z) == g_unk0x006c10a4)
                    Rightmost() = Parent(z);
                else
                    Rightmost() = RHSoundCacheGroupMaximum(x);
            }
        }
        if (Color(y) == 1)
        {
            while (x != Root() && Color(x) == 1)
            {
                if (x == Left(Parent(x)))
                {
                    Node *w = Right(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Lrotate(Parent(x));
                        w = Right(Parent(x));
                    }
                    if (Color(Left(w)) == 1 && Color(Right(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Right(w)) == 1)
                        {
                            Color(Left(w)) = 1;
                            Color(w) = 0;
                            Rrotate(w);
                            w = Right(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Right(w)) = 1;
                        Lrotate(Parent(x));
                        break;
                    }
                }
                else
                {
                    Node *w = Left(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Rrotate(Parent(x));
                        w = Left(Parent(x));
                    }
                    if (Color(Right(w)) == 1 && Color(Left(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Left(w)) == 1)
                        {
                            Color(Right(w)) = 1;
                            Color(w) = 0;
                            Lrotate(w);
                            w = Left(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Left(w)) = 1;
                        Rrotate(Parent(x));
                        break;
                    }
                }
            }
            Color(x) = 1;
        }
    }
    operator delete(y);
    --Count();
    return position;
}

// FUNCTION: GAME 0x005afc50
RHSoundCacheGroupIterator &RHSoundCacheGroups::FUN_005afc50(RHSoundCacheGroupIterator &result, const unsigned long &key)
{
    result.m_node = FUN_005b13e0(key);
    return result;
}

// FUNCTION: GAME 0x005afc70
void RHSoundCacheGroups::FUN_005afc70(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    for (RHSoundCacheGroupNode *next = node; next != g_unk0x006c10a4; node = next) {
        FUN_005afc70(next->m_08);
        next = next->m_00;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x005afd00
void RHSoundCacheGroups::FUN_005afd00()
{
    RHUnk00641782Lock lock;
    if (g_unk0x006c10a4 == 0) {
        Node *node = (Node *)operator new(sizeof(Node));
        node->m_04 = 0;
        node->m_14 = 1;
        g_unk0x006c10a4 = node;
        g_unk0x006c10a4->m_00 = 0;
        g_unk0x006c10a4->m_08 = 0;
    }
    ++g_unk0x006c10a8;
    Node *sentinel = g_unk0x006c10a4;
    Node *head = (Node *)operator new(sizeof(Node));
    head->m_04 = sentinel;
    head->m_14 = 0;
    Head() = head;
    Count() = 0;
    Head()->m_00 = Head();
    Head()->m_08 = Head();
}

// GLOBAL: GAME 0x006c10a4
RHSoundCacheGroupNode *g_unk0x006c10a4;

// GLOBAL: GAME 0x006c10ac
RHSoundCacheGroupNode *g_unk0x006c10ac;

namespace std
{
template <> void _Construct(pair<const unsigned long, RHsoundGroup *> *, const pair<const unsigned long, RHsoundGroup *> &);
}

static inline RHSoundCacheGroupNode *RHSoundCacheMinimumA4(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c10a4)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x005afdb0
template <> void RHSoundCacheEraseIterator<0>::Advance()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c10a4)
        m_node = RHSoundCacheMinimumA4(m_node->m_08);
    else
    {
        RHSoundCacheGroupNode *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

static inline RHSoundCacheGroupNode *RHSoundCacheEntryMinimum(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c10ac)
        node = node->m_00;
    return node;
}

static inline RHSoundCacheGroupNode *RHSoundCacheEntryMaximum(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c10ac)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x005afe60
RHSoundCacheEntryMap::EraseIterator RHSoundCacheEntryMap::FUN_005afe60(EraseIterator position)
{
    Node *x;
    Node *y = (position++).m_node;
    Node *z = y;
    RHUnk00641782Lock lock;
    if (Left(y) == g_unk0x006c10ac)
        x = Right(y);
    else if (Right(y) == g_unk0x006c10ac)
        x = Left(y);
    else
    {
        y = RHSoundCacheEntryMinimum(Right(y));
        x = Right(y);
    }
    {
        if (y != z)
        {
            Parent(Left(z)) = y;
            Left(y) = Left(z);
            if (y == Right(z))
                Parent(x) = y;
            else
            {
                Parent(x) = Parent(y);
                Left(Parent(y)) = x;
                Right(y) = Right(z);
                Parent(Right(z)) = y;
            }
            if (Root() == z)
                Root() = y;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = y;
            else
                Right(Parent(z)) = y;
            Parent(y) = Parent(z);
            std::swap(Color(y), Color(z));
            y = z;
        }
        else
        {
            Parent(x) = Parent(y);
            if (Root() == z)
                Root() = x;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = x;
            else
                Right(Parent(z)) = x;
            if (Leftmost() == z)
            {
                if (Right(z) == g_unk0x006c10ac)
                    Leftmost() = Parent(z);
                else
                    Leftmost() = RHSoundCacheEntryMinimum(x);
            }
            if (Rightmost() == z)
            {
                if (Left(z) == g_unk0x006c10ac)
                    Rightmost() = Parent(z);
                else
                    Rightmost() = RHSoundCacheEntryMaximum(x);
            }
        }
        if (Color(y) == 1)
        {
            while (x != Root() && Color(x) == 1)
            {
                if (x == Left(Parent(x)))
                {
                    Node *w = Right(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Lrotate(Parent(x));
                        w = Right(Parent(x));
                    }
                    if (Color(Left(w)) == 1 && Color(Right(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Right(w)) == 1)
                        {
                            Color(Left(w)) = 1;
                            Color(w) = 0;
                            Rrotate(w);
                            w = Right(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Right(w)) = 1;
                        Lrotate(Parent(x));
                        break;
                    }
                }
                else
                {
                    Node *w = Left(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        Rrotate(Parent(x));
                        w = Left(Parent(x));
                    }
                    if (Color(Right(w)) == 1 && Color(Left(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Left(w)) == 1)
                        {
                            Color(Right(w)) = 1;
                            Color(w) = 0;
                            Lrotate(w);
                            w = Left(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Left(w)) = 1;
                        Rrotate(Parent(x));
                        break;
                    }
                }
            }
            Color(x) = 1;
        }
    }
    operator delete(y);
    --Count();
    return position;
}

struct RHSoundCacheInsertStorage
{
    char m_00[4];
    RHSoundCacheGroupNode *m_head;
    unsigned m_08;
    unsigned m_size;
};

inline void RHSoundCacheEntryMap::Lrotate(RHSoundCacheGroupNode *x)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *y = x->m_08;
    x->m_08 = y->m_00;
    if (y->m_00 != g_unk0x006c10ac)
        y->m_00->m_04 = x;
    y->m_04 = x->m_04;
    if (x == Root())
        Root() = y;
    else if (x == x->m_04->m_00)
        x->m_04->m_00 = y;
    else
        x->m_04->m_08 = y;
    y->m_00 = x;
    x->m_04 = y;
}

inline void RHSoundCacheEntryMap::Rrotate(RHSoundCacheGroupNode *x)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *y = x->m_00;
    x->m_00 = y->m_08;
    if (y->m_08 != g_unk0x006c10ac)
        y->m_08->m_04 = x;
    y->m_04 = x->m_04;
    if (x == Root())
        Root() = y;
    else if (x == x->m_04->m_08)
        x->m_04->m_08 = y;
    else
        x->m_04->m_00 = y;
    y->m_08 = x;
    x->m_04 = y;
}

// FUNCTION: GAME 0x005b0380
void RHSoundCacheEntryMap::FUN_005b0380(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    for (RHSoundCacheGroupNode *next = node; next != g_unk0x006c10ac; node = next) {
        FUN_005b0380(next->m_08);
        next = next->m_00;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x005b0410
void RHSoundCacheEntryMap::FUN_005b0410()
{
    RHUnk00641782Lock lock;
    if (g_unk0x006c10ac == 0) {
        Node *node = (Node *)operator new(sizeof(Node));
        node->m_04 = 0;
        node->m_14 = 1;
        g_unk0x006c10ac = node;
        g_unk0x006c10ac->m_00 = 0;
        g_unk0x006c10ac->m_08 = 0;
    }
    ++g_unk0x006c10b0;
    Node *sentinel = g_unk0x006c10ac;
    Node *head = (Node *)operator new(sizeof(Node));
    head->m_04 = sentinel;
    head->m_14 = 0;
    Head() = head;
    Count() = 0;
    Head()->m_00 = Head();
    Head()->m_08 = Head();
}

// FUNCTION: GAME 0x005b04c0
RHSoundCacheGroupIterator RHSoundCacheEntryMap::FUN_005b04c0(RHSoundCacheGroupNode *x, RHSoundCacheGroupNode *y, const value_type &value)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *z = (RHSoundCacheGroupNode *)operator new(sizeof(RHSoundCacheGroupNode));
    z->m_04 = y;
    z->m_14 = 0;
    z->m_00 = g_unk0x006c10ac;
    z->m_08 = g_unk0x006c10ac;
    typedef std::pair<const unsigned long, RHsoundGroup *> StoredValue;
    std::_Construct((StoredValue *)&z->m_0c, *(const StoredValue *)&value);
    RHSoundCacheInsertStorage *tree = (RHSoundCacheInsertStorage *)this;
    ++tree->m_size;
    if (y == tree->m_head || x != g_unk0x006c10ac || value.first < y->m_0c)
    {
        y->m_00 = z;
        if (y == Head())
        {
            Root() = z;
            Rightmost() = z;
        }
        else if (y == Leftmost())
            Leftmost() = z;
    }
    else
    {
        y->m_08 = z;
        if (y == Rightmost())
            Rightmost() = z;
    }
    for (x = z; x != Root() && x->m_04->m_14 == 0; )
        if (x->m_04 == RHSoundCacheGroupIterator::Left(x->m_04->m_04))
        {
            y = x->m_04->m_04->m_08;
            if (y->m_14 == 0)
            {
                x->m_04->m_14 = 1;
                y->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_08)
                {
                    x = x->m_04;
                    Lrotate(x);
                }
                x->m_04->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                Rrotate(x->m_04->m_04);
            }
        }
        else
        {
            y = RHSoundCacheGroupIterator::Left(x->m_04->m_04);
            if (y->m_14 == 0)
            {
                x->m_04->m_14 = 1;
                y->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_00)
                {
                    x = x->m_04;
                    Rrotate(x);
                }
                x->m_04->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                Lrotate(x->m_04->m_04);
            }
        }
    Root()->m_14 = 1;
    return RHSoundCacheGroupIterator(z);
}

static inline RHSoundCacheGroupNode *RHSoundCacheMinimumAC(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c10ac)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x005b07c0
template <> void RHSoundCacheEraseIterator<1>::Advance()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c10ac)
        m_node = RHSoundCacheMinimumAC(m_node->m_08);
    else
    {
        RHSoundCacheGroupNode *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

inline void RHSoundCacheGroups::Lrotate(RHSoundCacheGroupNode *x)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *y = x->m_08;
    x->m_08 = y->m_00;
    if (y->m_00 != g_unk0x006c10a4)
        y->m_00->m_04 = x;
    y->m_04 = x->m_04;
    if (x == Root())
        Root() = y;
    else if (x == x->m_04->m_00)
        x->m_04->m_00 = y;
    else
        x->m_04->m_08 = y;
    y->m_00 = x;
    x->m_04 = y;
}

inline void RHSoundCacheGroups::Rrotate(RHSoundCacheGroupNode *x)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *y = x->m_00;
    x->m_00 = y->m_08;
    if (y->m_08 != g_unk0x006c10a4)
        y->m_08->m_04 = x;
    y->m_04 = x->m_04;
    if (x == Root())
        Root() = y;
    else if (x == x->m_04->m_08)
        x->m_04->m_08 = y;
    else
        x->m_04->m_00 = y;
    y->m_08 = x;
    x->m_04 = y;
}

// FUNCTION: GAME 0x005b10e0
RHSoundCacheGroupIterator RHSoundCacheGroups::FUN_005b10e0(RHSoundCacheGroupNode *x, RHSoundCacheGroupNode *y, const value_type &value)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *z = (RHSoundCacheGroupNode *)operator new(sizeof(RHSoundCacheGroupNode));
    z->m_04 = y;
    z->m_14 = 0;
    z->m_00 = g_unk0x006c10a4;
    z->m_08 = g_unk0x006c10a4;
    std::_Construct((value_type *)&z->m_0c, value);
    RHSoundCacheInsertStorage *tree = (RHSoundCacheInsertStorage *)this;
    ++tree->m_size;
    if (y == tree->m_head || x != g_unk0x006c10a4 || value.first < y->m_0c)
    {
        y->m_00 = z;
        if (y == Head())
        {
            Root() = z;
            Rightmost() = z;
        }
        else if (y == Leftmost())
            Leftmost() = z;
    }
    else
    {
        y->m_08 = z;
        if (y == Rightmost())
            Rightmost() = z;
    }
    for (x = z; x != Root() && x->m_04->m_14 == 0; )
        if (x->m_04 == RHSoundCacheGroupIterator::Left(x->m_04->m_04))
        {
            y = x->m_04->m_04->m_08;
            if (y->m_14 == 0)
            {
                x->m_04->m_14 = 1;
                y->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_08)
                {
                    x = x->m_04;
                    Lrotate(x);
                }
                x->m_04->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                Rrotate(x->m_04->m_04);
            }
        }
        else
        {
            y = RHSoundCacheGroupIterator::Left(x->m_04->m_04);
            if (y->m_14 == 0)
            {
                x->m_04->m_14 = 1;
                y->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                x = x->m_04->m_04;
            }
            else
            {
                if (x == x->m_04->m_00)
                {
                    x = x->m_04;
                    Rrotate(x);
                }
                x->m_04->m_14 = 1;
                x->m_04->m_04->m_14 = 0;
                Lrotate(x->m_04->m_04);
            }
        }
    Root()->m_14 = 1;
    return RHSoundCacheGroupIterator(z);
}

// FUNCTION: GAME 0x005b13e0
RHSoundCacheGroupNode *RHSoundCacheGroups::FUN_005b13e0(const unsigned long &key)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode **)((char *)this + 4);
    RHSoundCacheGroupNode *node = head->m_04;
    RHSoundCacheGroupNode *result = head;
    while (node != g_unk0x006c10a4)
    {
        if (node->m_0c < key)
            node = node->m_08;
        else
        {
            result = node;
            node = node->m_00;
        }
    }
    return result;
}

// FUNCTION: GAME 0x005b1430
RHSoundCacheGroupNode *RHSoundCacheEntryMap::FUN_005b1430(const unsigned long &key)
{
    RHUnk00641782Lock lock;
    RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode **)((char *)this + 4);
    RHSoundCacheGroupNode *node = head->m_04;
    RHSoundCacheGroupNode *result = head;
    while (node != g_unk0x006c10ac)
    {
        if (node->m_0c < key)
            node = node->m_08;
        else
        {
            result = node;
            node = node->m_00;
        }
    }
    return result;
}

static inline RHSoundCacheGroupNode *RHSoundCacheGroupMaxAC(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c10ac)
        node = node->m_08;
    return node;
}

static inline RHSoundCacheGroupNode *RHSoundCacheGroupMaxA4(RHSoundCacheGroupNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c10a4)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x005b1480
void RHSoundCacheGroupIterator::FUN_005b1480()
{
    RHUnk00641782Lock lock;
    if (m_node->m_14 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (Left(m_node) != g_unk0x006c10ac)
        m_node = RHSoundCacheGroupMaxAC(Left(m_node));
    else
    {
        RHSoundCacheGroupNode *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x005b1880
void RHSoundCacheGroupIterator::FUN_005b1880()
{
    RHUnk00641782Lock lock;
    if (m_node->m_14 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (Left(m_node) != g_unk0x006c10a4)
        m_node = RHSoundCacheGroupMaxA4(Left(m_node));
    else
    {
        RHSoundCacheGroupNode *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

// LIBRARY: GAME 0x005b1a00
// ?_Construct@std@@YAXPAU?$pair@$$CBKV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@1@ABU21@@Z

// FUNCTION: GAME 0x005b1ca0
RHUnk005b1ca0::RHUnk005b1ca0()
{
    m_10 = 0;
    m_14 = 0;
    m_18 = 0;
    m_1c = false;
    m_1e = 0;
    m_20 = 0;
}


// FUNCTION: GAME 0x005b1cd0
RHUnk005b1ca0::~RHUnk005b1ca0()
{
    FUN_005b2040();
}

// FUNCTION: GAME 0x005b2040
void RHUnk005b1ca0::FUN_005b2040()
{
    if (m_10)
        FSOUND_Sample_Free(m_10);
    m_10 = 0;
    m_20 = 0;
    m_1e = 0;
}

// FUNCTION: GAME 0x005f4fc0
RHUnk005f4fc0::RHUnk005f4fc0()
{
    *(undefined4 *)m_pad0 = 0;
    m_3c = false;
    m_28 = false;
    m_30 = 0;
    m_34 = 0;
    m_38 = 0;
}

// LIBRARY: GAME 0x005f77d0
// ?_Ucopy@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@IAEPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@PBV32@0PAV32@@Z

// LIBRARY: GAME 0x005f7a40
// ?copy_backward@std@@YAPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@PAV21@00@Z

void RHSoundCache::Emit(unsigned short index, RHSoundCacheGroups &groups, const RHSoundCacheMissionProfile *profile)
{
    RHcacheData cache;
    groups.FUN_005afd00();
    ((RHSoundCacheEntryMap *)&m_044)->FUN_005b0410();
    FUN_005ab410(cache);
    RHsampleCacheStats stats;
    FUN_005aec70();
    AddSoundGroup(groups, 1, index, index);
    InitializeMusic(profile);
    GetFXSample(true, index, 0);
    FUN_005ae640(true, index);
    FUN_005ae670(true, index, false);
    GetExclamationSample(true, index, index);
    AddSoundEntry(index, profile->m_0c4, m_044);
    AddSoundEntry(profile->m_0c4, cache);
    GetQuietMusic(index);
    GetAlertMusic(index);
    GetFightMusic(index);
    GetSourceCacheEntryForID(index);
    RHUnk005b1ca0 entry;
    entry.FUN_005b2040();
    UnloadSample((RHSoundCacheEntry *)&entry, stats);
    ((RHSoundCacheEntryMap *)&m_044)->FUN_005b1430(index);
}
