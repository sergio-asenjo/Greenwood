#include "RHProfileManager.h"
#include "RHActorProfiles.h"
#include "RHMissionProfile.h"
#include "RHProfileFile.h"
#include <algorithm>
#include <string.h>

class RHProfileManagerParseCalls
{
public:
    int FUN_0056c100(void *, unsigned, unsigned);
    bool FUN_0056c200(void *, unsigned, unsigned);
    unsigned FUN_0056c250(const char *);
    unsigned FUN_0056c290(void *, unsigned, unsigned);
    unsigned FUN_0056c360(void *, unsigned, unsigned);
    unsigned FUN_0056c410(void *, unsigned, unsigned);
    unsigned FUN_0056c490(void *, unsigned, unsigned);
    unsigned FUN_0056c5b0(void *, unsigned, unsigned);
    const char *FUN_0056c700(void *, unsigned, unsigned);
    unsigned FUN_0056cab0(void *, unsigned, unsigned);
    unsigned FUN_0056cb00(void *, unsigned, unsigned);
    unsigned FUN_0056cc40(void *, unsigned, unsigned);
    unsigned FUN_0056cdb0(void *, unsigned, unsigned);
    int FUN_0056ce70(void *);
};

static inline const char *RHProfileToken(void *token)
{
    const char *value = *(const char **)((char *)token + 4);
    return value ? value : "";
}

static inline bool RHProfileTokenEquals(const char *first, const char *second)
{
    return _stricmp(first, second) == 0;
}

// FUNCTION: GAME 0x0056c100
int RHProfileManagerParseCalls::FUN_0056c100(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006b1bec
    if (RHProfileTokenEquals(RHProfileToken(profile), "head"))
        return 0;
    // STRING: GAME 0x006b1be4
    if (RHProfileTokenEquals(RHProfileToken(profile), "throat"))
        return 1;
    // STRING: GAME 0x006b1bdc
    if (RHProfileTokenEquals(RHProfileToken(profile), "chest"))
        return 2;
    // STRING: GAME 0x006b1bd4
    if (RHProfileTokenEquals(RHProfileToken(profile), "back"))
        return 3;
    // STRING: GAME 0x006b1bcc
    if (RHProfileTokenEquals(RHProfileToken(profile), "legs"))
        return 4;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1b70
        "In weapon profile at (%d,%d) : target of thrust not recognized (%s), defaulting to HEAD\n",
        line, column, RHProfileToken(profile));
    return 0;
}

// FUNCTION: GAME 0x0056c200
bool RHProfileManagerParseCalls::FUN_0056c200(void *token, unsigned, unsigned)
{
    // STRING: GAME 0x006b1bf8
    if (RHProfileTokenEquals(RHProfileToken(token), "yes") ||
        // STRING: GAME 0x006b1bf4
        RHProfileTokenEquals(RHProfileToken(token), "x"))
        return true;
    return false;
}

// FUNCTION: GAME 0x0056c250
unsigned RHProfileManagerParseCalls::FUN_0056c250(const char *token)
{
    struct { unsigned word; char terminator; } value;
    value.word = 0;
    value.terminator = 0;
    // STRING: GAME 0x006b1bfc
    if (!RHProfileTokenEquals(token, "NONE"))
        strncpy((char *)&value, token, 4);
    return value.word;
}

// FUNCTION: GAME 0x0056c290
unsigned RHProfileManagerParseCalls::FUN_0056c290(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006af5f4
    if (RHProfileTokenEquals(RHProfileToken(profile), "wood"))
        return 0;
    // STRING: GAME 0x006b1c7c
    if (RHProfileTokenEquals(RHProfileToken(profile), "steel"))
        return 1;
    // STRING: GAME 0x006b1c70
    if (RHProfileTokenEquals(RHProfileToken(profile), "cast iron"))
        return 2;
    // STRING: GAME 0x006b1c60
    if (RHProfileTokenEquals(RHProfileToken(profile), "steel and wood"))
        return 3;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1c04
        "In profile at (%d,%d) : type of weapon material not recognized (%s), defaulting to WOOD\n",
        line, column, RHProfileToken(profile));
    return 0;
}

// FUNCTION: GAME 0x0056c360
unsigned RHProfileManagerParseCalls::FUN_0056c360(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006b1cf4
    if (RHProfileTokenEquals(RHProfileToken(profile), "leather"))
        return 0;
    // STRING: GAME 0x006b1ce8
    if (RHProfileTokenEquals(RHProfileToken(profile), "chainmail"))
        return 1;
    // STRING: GAME 0x006b1ce0
    if (RHProfileTokenEquals(RHProfileToken(profile), "plate"))
        return 2;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1c84
        "In profile at (%d,%d) : type of armor material not recognized (%s), defaulting to LEATHER\n",
        line, column, RHProfileToken(profile));
    return 0;
}

// FUNCTION: GAME 0x0056c410
unsigned RHProfileManagerParseCalls::FUN_0056c410(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006b1d60
    if (RHProfileTokenEquals(RHProfileToken(profile), "friendly"))
        return 1;
    // STRING: GAME 0x006b1d58
    if (RHProfileTokenEquals(RHProfileToken(profile), "hostile"))
        return 0;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1cfc
        "In civilian profile at (%d,%d) : unknow attitude descriptor (%s), defaulting to friendly\n",
        line, column, RHProfileToken(profile));
    return 1;
}

// FUNCTION: GAME 0x0056c490
unsigned RHProfileManagerParseCalls::FUN_0056c490(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006b1df4
    if (RHProfileTokenEquals(RHProfileToken(profile), "man"))
        return 0;
    // STRING: GAME 0x006b1dec
    if (RHProfileTokenEquals(RHProfileToken(profile), "woman"))
        return 1;
    // STRING: GAME 0x006b1de4
    if (RHProfileTokenEquals(RHProfileToken(profile), "old man"))
        return 2;
    // STRING: GAME 0x006b1ddc
    if (RHProfileTokenEquals(RHProfileToken(profile), "child"))
        return 3;
    // STRING: GAME 0x006b1dd4
    if (RHProfileTokenEquals(RHProfileToken(profile), "beggar"))
        return 4;
    // STRING: GAME 0x006b1dd0
    if (RHProfileTokenEquals(RHProfileToken(profile), "vip"))
        return 5;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1d6c
        "In civilian profile at (%d,%d) : type of civilian not recognized (%s), defaulting to CIVILIAN_MAN\n",
        line, column, RHProfileToken(profile));
    return 0;
}

// FUNCTION: GAME 0x0056c5b0
unsigned RHProfileManagerParseCalls::FUN_0056c5b0(void *profile, unsigned line, unsigned column)
{
    // STRING: GAME 0x006b1eac
    if (RHProfileTokenEquals(RHProfileToken(profile), "straight"))
        return 0;
    // STRING: GAME 0x006b1ea4
    if (RHProfileTokenEquals(RHProfileToken(profile), "lateral"))
        return 1;
    // STRING: GAME 0x006b1e98
    if (RHProfileTokenEquals(RHProfileToken(profile), "push aside"))
        return 2;
    // STRING: GAME 0x006b1e84
    if (RHProfileTokenEquals(RHProfileToken(profile), "true half circle"))
        return 3;
    // STRING: GAME 0x006b1e78
    if (RHProfileTokenEquals(RHProfileToken(profile), "true circle"))
        return 4;
    // STRING: GAME 0x006b1e64
    if (RHProfileTokenEquals(RHProfileToken(profile), "false half circle"))
        return 5;
    // STRING: GAME 0x006b1e54
    if (RHProfileTokenEquals(RHProfileToken(profile), "false circle"))
        return 6;
    FUN_0056cf40((const RHProfileManager *)this,
        // STRING: GAME 0x006b1df8
        "In weapon profile at (%d,%d) : kind of thrust not recognized (%s) defaulting to straight\n",
        line, column, RHProfileToken(profile));
    return 0;
}

// Parked: The full indexed action table and the target's sentinel handling remain unresolved.
// STUB: GAME 0x0056c700
const char *RHProfileManagerParseCalls::FUN_0056c700(void *profile, unsigned line, unsigned column)
{
    struct Entry { const char *name; unsigned value; };
    static const Entry entries[] = {
        {"hit", 0}, {"bow", 1}, {"net", 2}, {"hit hard", 3},
        {"hit harder", 3}, {"purse", 4}, {"stone", 5},
        {"slingshot", 5}, {"shield", 6}, {"big shield", 7},
        {"bigger shield", 7}, {"strangle", 8}, {"lever", 9},
        {"help to climb", 10}, {"apple", 11}, {"guzzle", 13},
        {"listen", 14}, {"beggar", 17}, {"climb", 18},
        {"megajump", 21}, {"search", 22}, {"resuscitate", 23},
        {"little john carry", 24}, {"farmer carry", 25}, {"tie", 26},
        {"lockpick", 27}, {"kill on ground", 28}, {"execute", 12},
        {"whistle", 29}, {"test", 22}, {"end", 0}
    };
    const char *value = RHProfileToken(profile);
    for (unsigned i = 0; i < sizeof(entries) / sizeof(entries[0]); ++i)
    {
        if (RHProfileTokenEquals(value, entries[i].name))
        {
            if (RHProfileTokenEquals(entries[i].name, "end"))
                FUN_0056cf40((const RHProfileManager *)this,
                    "In character profile at (%d,%d) : action %s", line, column, value);
            return (const char *)entries[i].value;
        }
    }
    FUN_0056cf40((const RHProfileManager *)this,
        "In character profile at (%d,%d) : action %s", line, column, value);
    return 0;
}

// FUNCTION: GAME 0x0056cab0
unsigned RHProfileManagerParseCalls::FUN_0056cab0(void *value, unsigned, unsigned)
{
    // STRING: GAME 0x006b205c
    if (RHProfileTokenEquals(RHProfileToken(value), "left"))
        return 0;
    // STRING: GAME 0x006b2054
    if (RHProfileTokenEquals(RHProfileToken(value), "right"))
        return 1;
    return 2;
}

// FUNCTION: GAME 0x0056cb00
unsigned RHProfileManagerParseCalls::FUN_0056cb00(void *profile, unsigned line, unsigned column)
{
    unsigned short index = 0;
    struct Entry { const char *name; unsigned value; };
    Entry entries[] = {
        // STRING: GAME 0x006b20ec
        {"historical", 0},
        // STRING: GAME 0x006b20e4
        {"attack", 1},
        // STRING: GAME 0x006b20dc
        {"rescue", 2},
        // STRING: GAME 0x006b20d4
        {"ambush", 3},
        // STRING: GAME 0x006b20d0
        {"hq", 4},
        // STRING: GAME 0x006b20c8
        {"pseudo", 5},
        // STRING: GAME 0x006b20bc
        {"tactical", 6},
        // STRING: GAME 0x006b1f0c
        {"end", 7}
    };
    while (!RHProfileTokenEquals(entries[index].name, RHProfileToken(profile)) &&
        !RHProfileTokenEquals(entries[index].name, "end"))
        ++index;
    unsigned value = entries[index].value;
    if (strcmp(entries[index].name, "end") == 0)
        FUN_0056cf40((const RHProfileManager *)this,
            // STRING: GAME 0x006b2064
            "In mission profile at (%d,%d) : mission type not recognized (%s) defaulting to none\n",
            line, column, RHProfileToken(profile));
    return value;
}

// FUNCTION: GAME 0x0056cc40
unsigned RHProfileManagerParseCalls::FUN_0056cc40(void *profile, unsigned line, unsigned column)
{
    unsigned short index = 0;
    struct Entry { const char *name; unsigned value; };
    Entry entries[] = {
        // STRING: GAME 0x006b2194
        {"Cross 1", 1},
        // STRING: GAME 0x006b218c
        {"Cross 2", 2},
        // STRING: GAME 0x006b2184
        {"Cross 3", 3},
        // STRING: GAME 0x006b217c
        {"Derby", 4},
        // STRING: GAME 0x006b2170
        {"Leicester", 5},
        // STRING: GAME 0x006b2168
        {"Lincoln", 6},
        // STRING: GAME 0x006b215c
        {"Nottingham", 7},
        // STRING: GAME 0x006a70a8
        {"Sherwood", 8},
        // STRING: GAME 0x006b2154
        {"York", 9},
        {"end", 10}
    };
    while (!RHProfileTokenEquals(entries[index].name, RHProfileToken(profile)) &&
        !RHProfileTokenEquals(entries[index].name, "end"))
        ++index;
    unsigned value = entries[index].value;
    if (strcmp(entries[index].name, "end") == 0)
        FUN_0056cf40((const RHProfileManager *)this,
            // STRING: GAME 0x006b20f8
            "In mission profile at (%d,%d) : mission location not recognized (%s) defaulting to none\n",
            line, column, RHProfileToken(profile));
    return value;
}

// Parked: byte-accessor fallback pointer polarity still differs after two source shapes.
// STUB: GAME 0x0056cdb0
unsigned RHProfileManagerParseCalls::FUN_0056cdb0(void *profile, unsigned line, unsigned column)
{
    const char *value = RHProfileToken(profile);
    if (*(unsigned *)((char *)profile + 8) != 2 ||
        !((value[0] >= 'A' && value[0] <= 'Z') || (value[0] >= 'a' && value[0] <= 'z')) ||
        !((value[1] >= '0' && value[1] <= '9') || (value[1] >= 'A' && value[1] <= 'Z') ||
            (value[1] >= 'a' && value[1] <= 'z')))
        FUN_0056cf40((const RHProfileManager *)this,
            "In mission profile at (%d,%d) : identifier %s", line, column, value);
    return (unsigned char)value[0] | ((unsigned char)value[1] << 8);
}

// Parked: canonical text access fixes the subobject load but not the fallback pointer arm schedule.
// STUB: GAME 0x0056ce70
int RHProfileManagerParseCalls::FUN_0056ce70(void *profile)
{
    const char *value = RHProfileToken(profile);
    for (RHCharacterProfile **it = ((RHProfileManager *)this)->m_characters.begin();
         it != ((RHProfileManager *)this)->m_characters.end(); ++it)
    {
        const char *name = *(const char **)((char *)*it + 0x18);
        if (RHProfileTokenEquals(name ? name : "", value))
            return (int)*it;
    }
    FUN_0056cf40((const RHProfileManager *)this,
        "In mission profile : character name %s", value);
    return 0;
}

// FUNCTION: GAME 0x004582d0
void SBArray<RHSaveGame *>::Insert(RHSaveGame **position, unsigned int count, RHSaveGame *const &value)
{
    if ((unsigned int)(m_end - m_last) < count)
    {
        unsigned int capacity = GetSize() + (count < GetSize() ? GetSize() : count);
        RHSaveGame **storage = std::_Allocate((int)capacity, (RHSaveGame **)0);
        RHSaveGame **destination = RHProfileConstructCopy(m_first, position, storage);
        RHProfileConstructFill(destination, count, value);
        RHProfileConstructCopy(position, m_last, destination + count);
        RHProfileDestroy(m_first, m_last);
        std::allocator<RHSaveGame *>().deallocate(m_first, m_end - m_first);
        m_end = storage + capacity;
        m_last = storage + GetSize() + count;
        m_first = storage;
    }
    else if ((unsigned int)(m_last - position) < count)
    {
        RHProfileConstructCopy(position, m_last, position + count);
        RHProfileConstructFill(m_last, count - (m_last - position), value);
        std::fill(position, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        RHProfileConstructCopy(m_last - count, m_last, m_last);
        std::copy_backward(position, m_last - count, m_last);
        std::fill(position, position + count, value);
        m_last += count;
    }
}

// FUNCTION: GAME 0x004598e0
void **FUN_004598e0(void **first, void **last, void **destination)
{
    for (; first != last; ++destination, ++first)
        *destination = *first;
    return destination;
}

// FUNCTION: GAME 0x00460900
int RHProfileText::FUN_00460900(unsigned int first, unsigned int count, const char *value, unsigned int size) const
{
    if (m_size < first)
        std::_Xran();
    if (m_size - first < count)
        count = m_size - first;
    int result = memcmp(m_chars == 0 ? 0 : m_chars + first, value, count < size ? count : size);
    if (result != 0)
        return result;
    if (count < size)
        return -1;
    return count != size;
}

// deferred: unannotated pending reccmp #534 (0x005008e0)
void RHScriptFXArray::Unk005008e0(void **, void **) {}

void RHProfileManager::Emit(SBFile &file)
{
    SerializeCivilians(file);
    SerializeCharacters(file);
    SerializeMissions(file);
    SerializeSoldiers(file);
    SerializeHandToHandWeapon(file);
    SerializeShootWeapon(file);
    const RHHtHWeaponProfile *handToHand = 0;
    RHMissionProfile *mission = 0;
    const RHBow::Profile *shoot = 0;
    const RHCharacterProfile *character = 0;
    SerializeProfilePointer(file, handToHand);
    SerializeProfilePointer(file, mission);
    SerializeProfilePointer(file, shoot);
    SerializeProfilePointer(file, character);
}

#define RH_PROFILE_ACCESS(value, bytes, line) \
    if (file.Access(value, bytes) < 0) \
    { \
        SBString *err = file.GetError(); \
        const char *reason = err->m_chars ? err->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

#define RH_PROFILE_CIVILIAN_ACCESS(value, bytes, line) \
    if (file.Access(value, bytes) < 0) \
    { \
        SBString *err = file.GetError(); \
        const char *reason = err->m_chars ? err->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", line, "Serialize failed reason is %s", reason); \
        goto failed; \
    }

// FUNCTION: GAME 0x00564e60
void RHProfileManager::FUN_00564e60(SBFile &file)
{
    SerializeHandToHandWeapon(file);
    SerializeShootWeapon(file);
    SerializeCharacters(file);
    SerializeSoldiers(file);
    SerializeMissions(file);
    SerializeCivilians(file);
}

// FUNCTION: GAME 0x00564ea0
bool RHProfileManager::SerializeCivilians(SBFile &file)
{
    unsigned int count;
    bool result;
    RHCivilianProfile **it;
    if (!file.m_bLoading)
    {
        count = m_civilians.GetSize();
        RH_PROFILE_CIVILIAN_ACCESS(&count, 4, 0xce);
    }
    else
    {
        RHProfileArray<RHCivilianProfile *> &profiles = m_civilians;
        RHCivilianProfile **last = (RHCivilianProfile **)FUN_004598e0(
            (void **)profiles.end(), (void **)profiles.end(), (void **)profiles.begin());
        ((RHScriptFXArray *)&profiles)->Unk005008e0((void **)last, (void **)profiles.end());
        profiles.m_last = last;
        RH_PROFILE_CIVILIAN_ACCESS(&count, 4, 0xd4);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHCivilianProfile);
    }

    for (it = m_civilians.begin(); it != m_civilians.end(); ++it)
    {
        RHCivilianProfile *profile = *it;
        FUN_005e0c90(file, *(std::string *)&profile->m_00);
        FUN_005e0c90(file, *(std::string *)&profile->m_10);
        FUN_005e0c90(file, profile->m_20);
        RH_PROFILE_CIVILIAN_ACCESS(&profile->m_30, 4, 0xe4);
        RH_PROFILE_CIVILIAN_ACCESS(&profile->m_34, 4, 0xe5);
        RH_PROFILE_CIVILIAN_ACCESS(&profile->m_38, 4, 0xe6);
    }
    result = true;
    goto finished;
failed:
    result = false;
finished:
    return result;
}

// FUNCTION: GAME 0x00565490
bool RHProfileManager::SerializeCharacters(SBFile &file)
{
    unsigned int count;
    unsigned int index = 0;
    if (!file.m_bLoading)
    {
        count = m_characters.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x11a);
    }
    else
    {
        RHProfileArray<RHCharacterProfile *> &profiles = m_characters;
        RHCharacterProfile **last = copy(profiles.end(), profiles.end(), profiles.begin());
        ((RHScriptFXArray *)&profiles)->Unk005008e0((void **)last, (void **)profiles.end());
        profiles.m_last = last;
        RH_PROFILE_ACCESS(&count, 4, 0x120);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHCharacterProfile);
    }
    for (RHCharacterProfile **it = m_characters.begin(); it != m_characters.end(); ++index, ++it)
    {
        RHCharacterProfile *profile = *it;
        profile->m_00 = *(volatile unsigned int *)&index - 1;
        profile->m_8c = 10 - (short)profile->m_00;
        FUN_005e0c90(file, *(std::string *)&profile->m_04);
        FUN_005e0c90(file, *(std::string *)&profile->m_14);
        FUN_005e0c90(file, profile->m_24);
        RH_PROFILE_ACCESS(&profile->m_34, 1, 0x133);
        RH_PROFILE_ACCESS(&profile->m_35, 1, 0x134);
        RH_PROFILE_ACCESS(&profile->m_36, 2, 0x136);
        RH_PROFILE_ACCESS(&profile->m_38, 2, 0x137);
        RH_PROFILE_ACCESS(&profile->m_3a, 2, 0x138);
        RH_PROFILE_ACCESS(&profile->m_3c, 4, 0x13a);
        RH_PROFILE_ACCESS(&profile->m_40, 4, 0x13b);
        RH_PROFILE_ACCESS(&profile->m_44, 4, 0x13c);
        RH_PROFILE_ACCESS(&profile->m_48, 4, 0x13e);
        RH_PROFILE_ACCESS(&profile->m_54, 2, 0x13f);
        RH_PROFILE_ACCESS(&profile->m_4c, 4, 0x141);
        RH_PROFILE_ACCESS(&profile->m_56, 2, 0x142);
        RH_PROFILE_ACCESS(&profile->m_50, 4, 0x144);
        RH_PROFILE_ACCESS(&profile->m_58, 2, 0x145);
        RH_PROFILE_ACCESS(&profile->m_5c, 4, 0x147);
        RH_PROFILE_ACCESS(&profile->m_60, 4, 0x148);
        RH_PROFILE_ACCESS(&profile->m_64, 4, 0x149);
        RH_PROFILE_ACCESS(&profile->m_68, 4, 0x14a);
        RH_PROFILE_ACCESS(profile->m_6c, 1, 0x14c);
        profile->m_70.Serialize(file);
        profile->m_84.Serialize(file);
        RH_PROFILE_ACCESS(&profile->m_8e, 2, 0x151);
        RH_PROFILE_ACCESS(&profile->m_94, 4, 0x152);
        RH_PROFILE_ACCESS(&profile->m_98, 4, 0x153);
        RH_PROFILE_ACCESS(&profile->m_92, 2, 0x154);
        RH_PROFILE_ACCESS(&profile->m_90, 2, 0x155);
    }
    return true;
}

static bool SerializeMissionArray(SBFile &file, RHMissionArray<unsigned long> &values)
{
    unsigned int count;
    if (!file.m_bLoading)
    {
        count = values.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x7b);
        for (unsigned long *it = values.begin(); it != values.end(); ++it)
        {
            unsigned long value = *it;
            RH_PROFILE_ACCESS(&value, 4, 0x80);
        }
    }
    else
    {
        values.FUN_004609a0(values.begin(), values.end());
        RH_PROFILE_ACCESS(&count, 4, 0x87);
        for (unsigned int i = 0; i < count; ++i)
        {
            unsigned long value;
            RH_PROFILE_ACCESS(&value, 4, 0x8c);
            values.FUN_004e5820(values.end(), value);
        }
    }
    return true;
}

// Parked: 62.60%; frame 0x34 reproduced, allocator temporaries and EH epilogues differ.
// STUB: GAME 0x00566570
bool RHProfileManager::SerializeMissions(SBFile &file)
{
    unsigned int count;
    if (!file.m_bLoading)
    {
        count = m_missions.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x1ad);
    }
    else
    {
        RHProfileArray<RHMissionProfile *> &profiles = m_missions;
        RHMissionProfile **last = (RHMissionProfile **)FUN_004598e0(
            (void **)profiles.end(), (void **)profiles.end(), (void **)profiles.begin());
        ((RHScriptFXArray *)&profiles)->Unk005008e0((void **)last, (void **)profiles.end());
        profiles.m_last = last;
        RH_PROFILE_ACCESS(&count, 4, 0x1b3);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHMissionProfile);
    }
    for (RHMissionProfile **it = m_missions.begin(); it != m_missions.end(); ++it)
    {
        RHMissionProfile *profile = *it;
        RH_PROFILE_ACCESS(&profile->m_00, 4, 0x1bf);
        FUN_005e0c90(file, *(std::string *)&profile->m_04);
        FUN_005e0c90(file, profile->m_14);
        FUN_005e0c90(file, profile->m_24);
        RH_PROFILE_ACCESS(&profile->m_34, 4, 0x1c5);
        RH_PROFILE_ACCESS(profile->m_38 + 4, 4, 0x1c6);
        RH_PROFILE_ACCESS(profile->m_38, 1, 0x1c7);
        RH_PROFILE_ACCESS(profile->m_38 + 20, 2, 0x1c8);
        RH_PROFILE_ACCESS(profile->m_38 + 39, 1, 0x1c9);
        RH_PROFILE_ACCESS(profile->m_38 + 26, 2, 0x1ca);
        RH_PROFILE_ACCESS(profile->m_38 + 8, 4, 0x1cb);
        RH_PROFILE_ACCESS(profile->m_38 + 12, 4, 0x1cc);
        SerializeMissionArray(file, profile->m_94);
        SerializeMissionArray(file, profile->m_a4);
        RH_PROFILE_ACCESS(profile->m_38 + 16, 2, 0x1d1);
        RH_PROFILE_ACCESS(profile->m_38 + 18, 2, 0x1d2);
        RH_PROFILE_ACCESS(profile->m_38 + 22, 2, 0x1d3);
        RH_PROFILE_ACCESS(profile->m_38 + 24, 2, 0x1d4);
        if (!file.m_bLoading)
        {
            unsigned int characters = profile->m_74.GetSize();
            RH_PROFILE_ACCESS(&characters, 4, 0x1db);
            for (RHCharacterProfile **character = profile->m_74.begin(); character != profile->m_74.end(); ++character)
            {
                int index = FUN_0056cef0(*character);
                RH_PROFILE_ACCESS(&index, 4, 0x1e0);
            }
        }
        else
        {
            unsigned int characters;
            RH_PROFILE_ACCESS(&characters, 4, 0x1e5);
            for (unsigned int i = 0; i < characters; ++i)
            {
                int index;
                RH_PROFILE_ACCESS(&index, 4, 0x1e8);
                profile->m_74.InsertLast(m_characters.m_first[index]);
            }
        }
        RH_PROFILE_ACCESS(profile->m_38 + 28, 1, 0x1f2);
        for (int i = 0; i < 9; ++i)
        {
            RH_PROFILE_ACCESS(profile->m_38 + 29 + i, 1, 0x1f6);
        }
        RH_PROFILE_ACCESS(profile->m_38 + 40, 1, 0x1f9);
        RH_PROFILE_ACCESS(profile->m_38 + 41, 1, 0x1fa);
        RH_PROFILE_ACCESS(profile->m_38 + 42, 1, 0x1fb);
        RH_PROFILE_ACCESS(profile->m_38 + 44, 2, 0x1fd);
        RH_PROFILE_ACCESS(profile->m_38 + 46, 2, 0x1fe);
        RH_PROFILE_ACCESS(profile->m_38 + 48, 2, 0x200);
        RH_PROFILE_ACCESS(profile->m_38 + 50, 2, 0x201);
        RH_PROFILE_ACCESS(profile->m_38 + 52, 2, 0x202);
        RH_PROFILE_ACCESS(profile->m_38 + 54, 2, 0x203);
        RH_PROFILE_ACCESS(profile->m_38 + 56, 2, 0x204);
        FUN_005e0c90(file, profile->m_c4);
        FUN_005e0c90(file, profile->m_d4);
        FUN_005e0c90(file, profile->m_e4);
    }
    if (file.m_bLoading)
    {
        for (RHMissionProfile **it = m_missions.begin(); it != m_missions.end(); ++it)
        {
            // STRING: GAME 0x006b1a20
            if ((*it)->m_34 != 5 && (*it)->m_14 != "Impossible_mission")
                ImportBeamMes(*it);
        }
    }
    return true;
}

// Parked: 84.30%; array constructor call boundaries and zero-run register scheduling.
// STUB: GAME 0x00568ba0
RHMissionProfile *RHProfileManager::AddForcedMission(const std::string &first, const std::string &second, const std::string &third)
{
    SBAssert(0,
        // STRING: GAME 0x006b1a6c
        "P:\\Robin Hood\\RHProfileManager.cpp", 0x331,
        // STRING: GAME 0x006b1a90
        "ACHTUNG : Adding a forced mission profile !");
    RHMissionProfile *profile = new RHMissionProfile;
    ((RHProfileText *)&profile->m_14)->FUN_00401ce0(second, 0, std::string::npos);
    profile->m_04.FUN_00401ce0(first, 0, std::string::npos);
    ((RHProfileText *)&profile->m_24)->FUN_00401ce0(third, 0, std::string::npos);
    // STRING: GAME 0x006a7098
    const char *outro = "SherwoodOutro";
    if (((const RHProfileText *)&second)->FUN_00460900(0, second.size(), outro, strlen(outro)) == 0)
    {
        profile->m_38[40] = 11;
        profile->m_38[41] = 11;
    }
    m_missions.InsertLast(profile);
    return m_missions.m_last[-1];
}

// FUNCTION: GAME 0x00568e00
bool RHProfileManager::SerializeHandToHandWeapon(SBFile &file)
{
    unsigned int count;
    if (!file.m_bLoading)
    {
        count = m_handToHand.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x34f);
    }
    else
    {
        RHProfileArray<RHHtHWeaponProfile *> &profiles = m_handToHand;
        profiles.RemoveAll();
        RH_PROFILE_ACCESS(&count, 4, 0x355);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHHtHWeaponProfile);
    }

    for (RHHtHWeaponProfile **it = m_handToHand.begin(); it != m_handToHand.end(); ++it)
    {
        RHHtHWeaponProfile *profile = *it;
        RH_PROFILE_ACCESS(&profile->m_00, 2, 0x361);
        RH_PROFILE_ACCESS(&profile->m_02, 2, 0x362);
        RH_PROFILE_ACCESS(&profile->m_04, 2, 0x363);
        RH_PROFILE_ACCESS(&profile->m_06, 2, 0x364);
        RH_PROFILE_ACCESS(&profile->m_08, 2, 0x366);
        RH_PROFILE_ACCESS(&profile->m_0a, 2, 0x367);
        RH_PROFILE_ACCESS(&profile->m_0c, 2, 0x368);
        RH_PROFILE_ACCESS(&profile->m_0e, 2, 0x369);
        RH_PROFILE_ACCESS(&profile->m_10, 2, 0x36a);
        RH_PROFILE_ACCESS(&profile->m_12, 2, 0x36c);
        RH_PROFILE_ACCESS(&profile->m_14, 2, 0x36d);
        RH_PROFILE_ACCESS(&profile->m_16, 1, 0x36f);
        RH_PROFILE_ACCESS(&profile->m_17, 1, 0x370);
        RH_PROFILE_ACCESS(&profile->m_18, 2, 0x371);
        RH_PROFILE_ACCESS(&profile->m_1a, 2, 0x372);
        for (int i = 0; i <= 9; ++i)
        {
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_00, 4, 0x376);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_0c, 2, 0x377);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_0e, 2, 0x378);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_10, 2, 0x379);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_12, 2, 0x37a);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_04, 4, 0x37b);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_08, 4, 0x37c);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_14, 2, 0x37d);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_16, 2, 0x37e);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_18, 2, 0x37f);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_1a, 2, 0x380);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_1c, 2, 0x381);
            RH_PROFILE_ACCESS(&profile->m_1c[i].m_1e, 2, 0x382);
        }
    }
    return true;
}

// FUNCTION: GAME 0x00569f40
bool RHProfileManager::SerializeShootWeapon(SBFile &file)
{
    unsigned int count;
    if (!file.m_bLoading)
    {
        count = m_shoot.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x3db);
    }
    else
    {
        RHProfileArray<RHBow::Profile *> &profiles = m_shoot;
        profiles.RemoveAll();
        RH_PROFILE_ACCESS(&count, 4, 0x3e1);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHBow::Profile);
    }

    for (RHBow::Profile **it = m_shoot.begin(); it != m_shoot.end(); ++it)
    {
        RHBow::Profile *profile = *it;
        RH_PROFILE_ACCESS(&profile->m_00, 2, 0x3ed);
        for (int i = 0; i < 6; ++i)
        {
            RH_PROFILE_ACCESS(&profile->m_04[i], 2, 0x3f0);
            RH_PROFILE_ACCESS(&profile->m_10[i], 2, 0x3f1);
            RH_PROFILE_ACCESS(&profile->m_1c[i], 2, 0x3f2);
        }
        RH_PROFILE_ACCESS(&profile->m_02, 2, 0x3f5);
        RH_PROFILE_ACCESS(&profile->m_78, 1, 0x3f7);
        RH_PROFILE_ACCESS(&profile->m_28, 2, 0x3f8);
        for (int j = 0; j < 6; ++j)
        {
            RH_PROFILE_ACCESS(&profile->m_2c[j], 2, 0x3fc);
            RH_PROFILE_ACCESS(&profile->m_38[j], 2, 0x3fd);
            RH_PROFILE_ACCESS(&profile->m_44[j], 2, 0x3fe);
        }
        RH_PROFILE_ACCESS(&profile->m_2a, 2, 0x401);
    }
    return true;
}

// FUNCTION: GAME 0x0056a7d0
bool RHProfileManager::SerializeSoldiers(SBFile &file)
{
    unsigned int count;
    if (!file.m_bLoading)
    {
        count = m_soldiers.GetSize();
        RH_PROFILE_ACCESS(&count, 4, 0x489);
    }
    else
    {
        RHProfileArray<RHSoldierProfile *> &profiles = m_soldiers;
        RHSoldierProfile **last = (RHSoldierProfile **)FUN_004598e0(
            (void **)profiles.end(), (void **)profiles.end(), (void **)profiles.begin());
        ((RHScriptFXArray *)&profiles)->Unk005008e0((void **)last, (void **)profiles.end());
        profiles.m_last = last;
        RH_PROFILE_ACCESS(&count, 4, 0x48f);
        for (unsigned int i = 0; i < count; ++i)
            profiles.InsertLast(new RHSoldierProfile);
    }
    for (RHSoldierProfile **it = m_soldiers.begin(); it != m_soldiers.end(); ++it)
    {
        RHSoldierProfile *profile = *it;
        FUN_005e0c90(file, *(std::string *)&profile->m_00);
        FUN_005e0c90(file, *(std::string *)&profile->m_10);
        FUN_005e0c90(file, profile->m_20);
        RH_PROFILE_ACCESS(&profile->m_30, 2, 0x49f);
        RH_PROFILE_ACCESS(&profile->m_32, 2, 0x4a0);
        RH_PROFILE_ACCESS(&profile->m_34, 2, 0x4a1);
        RH_PROFILE_ACCESS(&profile->m_36, 2, 0x4a2);
        RH_PROFILE_ACCESS(&profile->m_38, 2, 0x4a3);
        RH_PROFILE_ACCESS(profile->m_3a, 1, 0x4a4);
        RH_PROFILE_ACCESS(&profile->m_3c, 2, 0x4a5);
        RH_PROFILE_ACCESS(&profile->m_3e, 2, 0x4a6);
        RH_PROFILE_ACCESS(&profile->m_40, 2, 0x4a7);
        RH_PROFILE_ACCESS(&profile->m_58, 4, 0x4a8);
        RH_PROFILE_ACCESS(&profile->m_44, 4, 0x4aa);
        RH_PROFILE_ACCESS(&profile->m_42, 2, 0x4ab);
        RH_PROFILE_ACCESS(profile->m_5c, 1, 0x4ac);
        RH_PROFILE_ACCESS(&profile->m_54, 2, 0x4ad);
        RH_PROFILE_ACCESS(&profile->m_52, 2, 0x4ae);
        RH_PROFILE_ACCESS(&profile->m_50, 2, 0x4af);
        RH_PROFILE_ACCESS(&profile->m_56, 2, 0x4b0);
        RH_PROFILE_ACCESS(&profile->m_48, 4, 0x4b2);
        RH_PROFILE_ACCESS(&profile->m_4c, 4, 0x4b3);
        RH_PROFILE_ACCESS(profile->m_5c + 1, 1, 0x4b5);
        profile->m_60.Serialize(file);
        profile->m_74.Serialize(file);
        RH_PROFILE_ACCESS(&profile->m_7c, 2, 0x4b9);
        RH_PROFILE_ACCESS(&profile->m_80, 4, 0x4ba);
        RH_PROFILE_ACCESS(&profile->m_84, 4, 0x4bb);
    }
    return true;
}

extern std::string g_unk0x006c05f0;

// Parked: 64.03%; frame 0xe0 versus 0xfc, string temporaries and register allocation differ.
// STUB: GAME 0x0056b8d0
void RHProfileManager::ImportBeamMes(RHMissionProfile *profile)
{
    RHProfileFile file;
    // STRING: GAME 0x006af37c
    const char *extension = ".rhm";
    RHProfileText path((*(RHProfileText *)&g_unk0x006c05f0 + RHProfileText("\\") + *(RHProfileText *)&profile->m_14 + RHProfileText(extension)).c_str());
    if (file.FUN_005f5090(RHProfileText(path.c_str()), 1) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x522,
            // STRING: GAME 0x006af308
            "STRENGSTENS UNTERSAGT : Unable to open mission file !");
        return;
    }
    FUN_005e1d50(file, 0x44555459, 2);
    while (file.Position() < file.Size())
    {
        if (FUN_005e1d00(file) != 0x424f595a)
        {
            FUN_005e2300(file);
        }
        else if (FUN_005e2020(file, 0x424f595a, 3))
        {
            FUN_005e1d50(file, 0x424f595a, 3);
            unsigned short count;
            file.Access(&count, 2);
            for (unsigned int i = 0; (unsigned short)i < count; ++i)
            {
                if (FUN_005e1d00(file) != 0x53434f54)
                {
                    FUN_005e2300(file);
                }
                else
                {
                    std::string name;
                    if (FUN_005e2020(file, 0x53434f54, 4))
                    {
                        FUN_005e1d50(file, 0x53434f54, 4);
                        unsigned short actors;
                        file.Access(&actors, 2);
                        *(unsigned short *)(profile->m_38 + 58) = actors;
                        for (unsigned int actor = 0; (unsigned short)actor < actors; ++actor)
                        {
                            file.FUN_005f5370(0x16, 1);
                            char enabled;
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(21);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(22);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(28);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(1);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(25);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(27);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(2);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(9);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(13);
                            file.Access(&enabled, 1);
                            if (enabled) profile->m_84.InsertLast(23);
                            char hasName;
                            file.Access(&hasName, 1);
                            if (hasName) FUN_005e0c90(file, name);
                            char trailing;
                            file.Access(&trailing, 1);
                        }
                        FUN_005e20c0(file);
                    }
                    else
                    {
                        SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x576,
                            // STRING: GAME 0x006b1b34
                            "Warning: A mission in the missions list is not up to date.");
                        *(unsigned short *)(profile->m_38 + 58) = 5;
                        FUN_005e2300(file);
                    }
                }
            }
            FUN_005e20c0(file);
        }
        else
        {
            SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x588, "Warning: A mission in the missions list is not up to date.");
            *(unsigned short *)(profile->m_38 + 58) = 5;
            FUN_005e2300(file);
        }
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x0056cef0
int RHProfileManager::FUN_0056cef0(const RHCharacterProfile *profile) const
{
    int index = 0;
    for (RHCharacterProfile **it = m_characters.m_first; it != m_characters.m_last; ++it, ++index)
    {
        if (*it == profile)
            return index;
    }
    FUN_0056cf40(this,
        // STRING: GAME 0x006b21d0
        "In mission profile : character not recognized (%s) defaulting to none\n",
        profile->m_14.c_str());
    return -1;
}

// FUNCTION: GAME 0x0056d0d0
int RHProfileManager::GetProfileIndex(const RHHtHWeaponProfile *profile) const
{
    int index = -1;
    RHHtHWeaponProfile **last = m_handToHand.m_last;
    RHHtHWeaponProfile **it = std::find(m_handToHand.m_first, last, profile);
    if (it != m_handToHand.m_last)
        index = it - m_handToHand.m_first;
    return index;
}

// FUNCTION: GAME 0x0056d100
int RHProfileManager::GetProfileIndex(const RHBow::Profile *profile) const
{
    int index = -1;
    RHBow::Profile **last = m_shoot.m_last;
    RHBow::Profile **it = std::find(m_shoot.m_first, last, profile);
    if (it != m_shoot.m_last)
        index = it - m_shoot.m_first;
    return index;
}

// FUNCTION: GAME 0x0056d130
int RHProfileManager::GetProfileIndex(const RHCharacterProfile *profile) const
{
    int index = -1;
    RHCharacterProfile **last = m_characters.m_last;
    RHCharacterProfile **it = std::find(m_characters.m_first, last, profile);
    if (it != m_characters.m_last)
        index = it - m_characters.m_first;
    return index;
}

// FUNCTION: GAME 0x0056d160
int RHProfileManager::GetProfileIndex(const RHMissionProfile *profile) const
{
    int index = -1;
    RHMissionProfile **last = m_missions.m_last;
    RHMissionProfile **it = std::find(m_missions.m_first, last, profile);
    if (it != m_missions.m_last)
        index = it - m_missions.m_first;
    return index;
}

// FUNCTION: GAME 0x0056d190
bool RHProfileManager::SerializeProfilePointer(SBFile &file, const RHHtHWeaponProfile *&profile) const
{
    int index;
    if (!file.m_bLoading)
    {
        if (profile == 0)
        {
            index = -1;
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                // STRING: GAME 0x006b1944
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x7e3, "Serialize failed reason is %s", reason);
                return false;
            }
        }
        else
        {
            index = GetProfileIndex(profile);
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x7eb, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x7f2, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            profile = 0;
            return true;
        }
        profile = m_handToHand.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x0056d2a0
bool RHProfileManager::SerializeProfilePointer(SBFile &file, RHMissionProfile *&profile) const
{
    int index;
    if (!file.m_bLoading)
    {
        if (profile == 0)
        {
            index = -1;
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x81b, "Serialize failed reason is %s", reason);
                return false;
            }
        }
        else
        {
            index = GetProfileIndex(profile);
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x823, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x82a, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            profile = 0;
            return true;
        }
        profile = m_missions.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x0056d3b0
bool RHProfileManager::SerializeProfilePointer(SBFile &file, const RHBow::Profile *&profile) const
{
    int index;
    if (!file.m_bLoading)
    {
        if (profile == 0)
        {
            index = -1;
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x852, "Serialize failed reason is %s", reason);
                return false;
            }
        }
        else
        {
            index = GetProfileIndex(profile);
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x85a, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x861, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            profile = 0;
            return true;
        }
        profile = m_shoot.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x0056d4c0
bool RHProfileManager::SerializeProfilePointer(SBFile &file, const RHCharacterProfile *&profile) const
{
    int index;
    if (!file.m_bLoading)
    {
        if (profile == 0)
        {
            index = -1;
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x88a, "Serialize failed reason is %s", reason);
                return false;
            }
        }
        else
        {
            index = GetProfileIndex(profile);
            if (file.Access(&index, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x892, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHProfileManager.cpp", 0x899, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            profile = 0;
            return true;
        }
        profile = m_characters.m_first[index];
    }
    return true;
}

// FUNCTION: GAME 0x005e2020
bool FUN_005e2020(SBFile &file, unsigned long tag, int level)
{
    unsigned long actualTag;
    struct
    {
        int level;
        unsigned long unused;
        unsigned long size;
    } header;
    file.Access(&actualTag, 4);
    file.Access(&header.size, 4);
    file.Access(&header.level, 4);
    ((RHProfileFile *)&file)->FUN_005f5370(-4, 1);
    ((RHProfileFile *)&file)->FUN_005f5370(-4, 1);
    ((RHProfileFile *)&file)->FUN_005f5370(-4, 1);
    actualTag = (((actualTag & 0xff0000) | (actualTag >> 16)) >> 8)
        | (((actualTag & 0xff00) | (actualTag << 16)) << 8);
    if (tag != actualTag || level != header.level)
        return false;
    return true;
}
