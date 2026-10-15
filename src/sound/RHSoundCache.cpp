#include "SBNullstr.h"
#include "RHSoundCache.h"
#include "RHSoundCacheSpeechList.h"

DECOMP_SIZE_ASSERT(RHSoundCache, 0x138)
DECOMP_SIZE_ASSERT(RHcacheData, 0x0c)
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

// Reconstructed cache-array teardown; per-entry sample release remains incomplete.
// STUB: GAME 0x005ab4e0
void RHSoundCache::FUN_005ab4e0(RHcacheData &cache)
{
    for (unsigned int index = 0; index < cache.m_04; ++index)
        (cache.m_00 + index)->~RHSoundCacheEntry();
    operator delete(cache.m_00);
    cache.m_00 = 0;
    cache.m_04 = 0;
    cache.m_08 = 0;
}

// Reconstructed loaded-sample iteration; the target's unload callback and stats updates remain incomplete.
// STUB: GAME 0x005ab530
void RHSoundCache::FUN_005ab530(RHcacheData &cache, unsigned long)
{
    for (unsigned int index = 0; index < cache.m_04; ++index)
    {
        RHSoundCacheEntry *entry = cache.m_00 + index;
        if (entry->m_sample)
        {
            entry->m_sample = 0;
            entry->m_duration = 0;
        }
    }
}

// Reconstructed cache-map and backing-array teardown; sample accounting remains incomplete.
// STUB: GAME 0x005ab660
void RHSoundCache::FUN_005ab660(std::map<unsigned long, RHSoundCacheEntry *> &entries, RHcacheData &cache)
{
    for (std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = entries.begin(); entry != entries.end(); ++entry)
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
    for (std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = entries.begin(); entry != entries.end(); ++entry)
    {
        delete entry->second;
        entry->second = 0;
    }
    entries.clear();
}

// Parked 25.48%: the candidate map lookup is reconstructed, but argument-slot lifetime, sample-state updates, and entry return scheduling differ.
// STUB: GAME 0x005ab730
RHSoundCacheEntry *RHSoundCache::GetSample(bool load, std::map<unsigned long, RHSoundCacheEntry *> &entries, void *stats, unsigned long id, unsigned long stamp, unsigned long lifetime, bool spatial)
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

// Parked: inlined string erase retains different pointer registers.
// STUB: GAME 0x005ad250
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

// FUNCTION: GAME 0x005aed30
RHSoundCacheEntry *RHSoundCache::GetSourceCacheEntryForID(unsigned long id)
{
    std::map<unsigned long, RHSoundCacheEntry *>::iterator entry = m_044.find(id);
    if (entry != m_044.end())
        return entry->second;
    SBAssert(1, "P:\\Robin Hood\\RHsoundcache.cpp", 1782,
        // STRING: GAME 0x006b8564
        "Unable to find cache entry for id %d !", id);
    return 0;
}

// LIBRARY: GAME 0x005aef50
// ??1?$pair@$$CBKV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@QAE@XZ

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

// FUNCTION: GAME 0x005afc50
RHSoundCacheGroupIterator &RHSoundCacheGroups::FUN_005afc50(RHSoundCacheGroupIterator &result, const unsigned long &key)
{
    result.m_node = FUN_005b13e0(key);
    return result;
}

// GLOBAL: GAME 0x006c10a4
RHSoundCacheGroupNode *g_unk0x006c10a4;

// GLOBAL: GAME 0x006c10ac
RHSoundCacheGroupNode *g_unk0x006c10ac;

RHSoundCacheGroupNode *RHSoundCacheGroups::FUN_005b13e0(const unsigned long &key)
{
    RHUnk00641782 lock;
    lock.FUN_00641782();
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
    lock.FUN_0064181e();
    return result;
}

RHSoundCacheGroupNode *RHSoundCacheEntryMap::FUN_005b1430(const unsigned long &key)
{
    RHUnk00641782 lock;
    lock.FUN_00641782();
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
    lock.FUN_0064181e();
    return result;
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
    AddSoundGroup(groups, 1, index, index);
    InitializeMusic(profile);
    GetFXSample(true, index, 0);
    GetExclamationSample(true, index, index);
    AddSoundEntry(index, profile->m_0c4, m_044);
    RHcacheData cache;
    AddSoundEntry(profile->m_0c4, cache);
    GetQuietMusic(index);
    GetAlertMusic(index);
    GetFightMusic(index);
    GetSourceCacheEntryForID(index);
    RHUnk005b1ca0 entry;
    entry.FUN_005b2040();
    ((RHSoundCacheEntryMap *)&m_044)->FUN_005b1430(index);
}
