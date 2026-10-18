#include "SBNullstr.h"
#include "RHSound.h"
#include "RHSoundGeometry.h"
#include "RHSoundActorCalls.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

void FUN_0064158f(void *memory);
void FUN_005aa090(void *value, void *first, void *last);

DECOMP_SIZE_ASSERT(RHSound, 0x294)
DECOMP_SIZE_ASSERT(RHUnk005a7220, 0x50)
DECOMP_SIZE_ASSERT(RHUnk005a9260, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005ad570Profiles, 0x6c)
DECOMP_SIZE_ASSERT(RHSoundQueue, 0x0c)
DECOMP_SIZE_ASSERT(RHSoundSourceArray, 0x20)
DECOMP_SIZE_ASSERT(RHSoundSourceManager, 0x24)
DECOMP_SIZE_ASSERT(RHSoundChannelSettings, 0x20)
DECOMP_SIZE_ASSERT(RHSoundGeometryView, 0xc8)
DECOMP_SIZE_ASSERT(RHSoundChannel, 0x10)
DECOMP_SIZE_ASSERT(RHSoundChannels, 0x2c)
DECOMP_SIZE_ASSERT(RHSoundSettings, 0x18)
DECOMP_SIZE_ASSERT(RHSoundPendingData, 0x24)
DECOMP_SIZE_ASSERT(RHSoundPendingNode, 0x2c)
DECOMP_SIZE_ASSERT(RHSoundQueueNode, 0x40)
DECOMP_SIZE_ASSERT(RHSoundVirtualSlot39, 0x04)
DECOMP_SIZE_ASSERT(RHUnk005aada0, 0x10)

extern float g_unk0x0067749c;
extern double g_unk0x00677d90;
extern float g_unk0x006774a0;

// GLOBAL: GAME 0x00677670
double g_unk0x00677670 = 2.0;
// GLOBAL: GAME 0x00679e08
static double g_unk0x00679e08 = 127.5;
// GLOBAL: GAME 0x00679e10
static double g_unk0x00679e10 = 0.02;

// GLOBAL: GAME 0x00679dd8
static float g_unk0x00679dd8 = 3.6f;

// GLOBAL: GAME 0x00679e18
static double g_unk0x00679e18 = 255.0;

// GLOBAL: GAME 0x00679e20
static double g_unk0x00679e20 = 90.0;

extern double g_unk0x006774b8;
extern float g_dialogueVolumeHigh;

// GLOBAL: GAME 0x00679dd4
float g_unk0x00679dd4 = 0.1111111119389534f;

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &);
    ~SBGeoPoint2D();
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &) const;
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    float m_x;
    float m_y;
};

inline void RHUnk005aada0::Destroy(SBGeoPoint2D *first, SBGeoPoint2D *last)
{
    for (; first != last; ++first)
        first->~SBGeoPoint2D();
}

inline SBGeoPoint2D *RHUnk005aada0::Remove(SBGeoPoint2D *first, SBGeoPoint2D *last)
{
    SBGeoPoint2D *next = std::copy(last, End(), first);
    Destroy(next, End());
    m_last = next;
    return first;
}

inline RHUnk005aada0::~RHUnk005aada0()
{
    Destroy(Begin(), End());
    operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

class RHUnk005aa860 : public RHUnk005aada0
{
public:
    ~RHUnk005aa860();
    unsigned char m_10[0xc];
    SBGeoPoint2D m_1c;
};

DECOMP_SIZE_ASSERT(RHUnk005aa860, 0x24)

class RHScriptFXArray
{
public:
    void Unk005008e0(void **, void **);
};

DECOMP_SIZE_ASSERT(RHUnk005b2410, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)

extern float g_unk0x006774ec;
// GLOBAL: GAME 0x006774f0
float g_unk0x006774f0 = 0.01f;

// GLOBAL: GAME 0x00679df4
static float g_unk0x00679df4 = 128.0f;
// GLOBAL: GAME 0x00679df8
static float g_unk0x00679df8 = 126.0f;
// GLOBAL: GAME 0x00679dfc
static float g_unk0x00679dfc = 63.0f;
// GLOBAL: GAME 0x00679e00
static float g_unk0x00679e00 = -63.0f;
// GLOBAL: GAME 0x00679e04
static float g_unk0x00679e04 = 0.003921568859368563f;

void RHSerializeName(SBFile &, const char *);

// GLOBAL: GAME 0x006b79ac
static const char *g_unk0x006b79ac[8] = {
    "Jingle_01.wav", "Jingle_02.wav", "Jingle_03.wav", "Jingle_04.wav",
    "Jingle_05.wav", "Jingle_06.wav", "Jingle_07.wav", "Jingle_08.wav"
};

static inline const char *SoundStringData(const std::string &name)
{
    const char *chars = reinterpret_cast<const SBString *>(&name)->m_chars;
    return chars ? chars : "";
}

// deferred: 0x00402260 unannotated pending reccmp #534
void RHProfileText::FUN_00402260(unsigned int size)
{
    m_size = size;
    m_chars[size] = 0;
}

// LIBRARY: GAME 0x0040bb20
// ?append@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z

void RHSoundPendingData::FUN_0052c5a0()
{
    ((SBGeoPoint2D *)((char *)this + 4))->~SBGeoPoint2D();
}

#include "RHSoundSettingsLifetime.h"

inline RHSoundPendingData::~RHSoundPendingData()
{
}

void FUN_005aa990(RHSoundPendingData *, const RHSoundPendingData *);

// STUB: GAME 0x005a6520
bool RHSound::FUN_005a6520(unsigned long &driver)
{
    std::string devices;
    std::string name;
    HKEY key;
    if (g_rhsoundRegOpenKeyExA(HKEY_LOCAL_MACHINE,
        // STRING: GAME 0x006a6db4
        "Software\\Spellbound Software\\Robin Hood 1.0", 0, KEY_READ, &key) == ERROR_SUCCESS)
    {
        unsigned long type;
        unsigned long hash;
        unsigned long size = 4;
        if (g_rhsoundRegQueryValueExA(key,
            // STRING: GAME 0x006b7b28
            "SoundConfig", 0, &type, (unsigned char *)&hash, &size) == ERROR_SUCCESS && type == REG_DWORD && size == 4)
        {
            if (g_rhsoundRegQueryValueExA(key,
                // STRING: GAME 0x006b7b1c
                "SoundDevice", 0, &type, (unsigned char *)&driver, &size) == ERROR_SUCCESS && type == REG_DWORD && size == 4)
            {
                g_rhsoundRegCloseKey(key);
                unsigned int count = FSOUND_GetNumDrivers();
                for (unsigned int index = 0; index < count; ++index)
                {
                    name.assign(FSOUND_GetDriverName(index));
                    if (name.size() == 0)
                        SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 251,
                            // STRING: GAME 0x006b7afc
                            "Unable to get sound device name");
                    devices.append(name);
                }
                return crc32(0, (const Bytef *)SoundStringData(devices), devices.size()) == hash;
            }
            g_rhsoundRegCloseKey(key);
        }
        else
            g_rhsoundRegCloseKey(key);
    }
    return false;
}

// STUB: GAME 0x005a67b0
void RHSound::FUN_005a67b0(unsigned long &driver)
{
    std::string devices;
    std::string name;
    unsigned int count = FSOUND_GetNumDrivers();
    driver = 0;
    for (unsigned int index = 0; index < count; ++index)
    {
        name = FSOUND_GetDriverName(index);
        if (name.size() == 0)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 284, "Unable to get sound device name");
        unsigned int caps;
        if (!FSOUND_GetDriverCaps(index, &caps))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 289,
                // STRING: GAME 0x006b7bdc
                "Unable to get caps for sound device \"%s\"", SoundStringData(name));
        if ((caps & 1) && index == 0)
            driver = index;
        devices.append(name);
    }
    unsigned long hash = crc32(0, (const Bytef *)SoundStringData(devices), devices.size());
    HKEY key;
    unsigned long disposition;
    if (g_rhsoundRegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Spellbound Software\\Robin Hood 1.0", 0,
        // STRING: GAME 0x006b7bcc
        "Chuppa Chups", 0, KEY_WRITE, 0, &key, &disposition) != ERROR_SUCCESS)
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 306,
            // STRING: GAME 0x006b7ba4
            "Failed to create key in the registry");
    if (g_rhsoundRegSetValueExA(key, "SoundConfig", 0, REG_DWORD, (const unsigned char *)&hash, 4) != ERROR_SUCCESS)
    {
        g_rhsoundRegCloseKey(key);
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 313,
            // STRING: GAME 0x006b7b6c
            "Failed to set value for sound config in the registry");
    }
    if (g_rhsoundRegSetValueExA(key, "SoundDevice", 0, REG_DWORD, (const unsigned char *)&driver, 4) != ERROR_SUCCESS)
    {
        g_rhsoundRegCloseKey(key);
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 321,
            // STRING: GAME 0x006b7b34
            "Failed to set value for sound device ID in the registry");
    }
    g_rhsoundRegCloseKey(key);
}

// STUB: GAME 0x005a6a50
bool RHSound::InitializeSound(unsigned short driver, bool spatial, std::string &error)
{
    if (!g_unk0x006c0685)
    {
        m_20a = 0;
        m_208 = driver;
        return true;
    }
    if (!FSOUND_SetHWND(m_204))
    {
        error =
            // STRING: GAME 0x006b7d4c
            "Unable to set window handle !";
        return false;
    }
    if (!FSOUND_SetDriver(driver))
    {
        error =
            // STRING: GAME 0x006b7d30
            "Unable to select driver !";
        return false;
    }
    if (!FSOUND_SetMixer(m_214 ? 4 : 0))
    {
        error =
            // STRING: GAME 0x006b7d18
            "Unable to set mixer !";
        return false;
    }
    m_210 = m_211 && spatial;
    if (m_210)
    {
        if (!FSOUND_SetMinHardwareChannels(8))
        {
            error =
                // STRING: GAME 0x006b7ce0
                "Unable to set minimal number of 3D hardware channels !";
            return false;
        }
        if (!FSOUND_SetMaxHardwareChannels(32))
        {
            error =
                // STRING: GAME 0x006b7ca8
                "Unable to set maximal number of 3D hardware channels !";
            return false;
        }
    }
    if (!FSOUND_SetOutput(2))
    {
        error =
            // STRING: GAME 0x006b7c84
            "Unable to set DirectSound output !";
        return false;
    }
    m_000.m_134 = m_210 != 0;
    m_208 = driver;
    if (!FSOUND_SetBufferSize(100))
    {
        error =
            // STRING: GAME 0x006b7c60
            "Unable to set mixing buffer size !";
        return false;
    }
    m_20a = FSOUND_Init(44100, m_214 ? 32 : 16, 8) != 0;
    if (!m_20a)
    {
        error =
            // STRING: GAME 0x006b7c44
            "Unable to initialize FMod !";
        return false;
    }
    if (m_210)
    {
        FSOUND_3D_Listener_SetDistanceFactor(1.0f);
        FSOUND_3D_Listener_SetRolloffFactor(1.0f);
    }
    m_218 = FSOUND_GetMaxChannels();
    unsigned int hardware = FSOUND_GetNumHardwareChannels();
    if (!m_210 || hardware < 8)
        m_218 -= hardware;
    if (m_21c.Size() < m_218)
    {
        RHSoundChannel value;
        m_21c.FUN_005aaa50(m_218, value);
        m_21c.m_14 = true;
    }
    for (unsigned int index = 0; index < m_218; ++index)
    {
        m_21c.m_04[index].m_00 = 0;
        m_21c.m_04[index].m_08 = 0;
        m_21c.m_04[index].m_0c = 0;
        m_21c.m_04[index].m_0c = 0;
        m_21c.m_04[index].m_04 = 0;
    }
    if (spatial && !m_211)
    {
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 457,
            // STRING: GAME 0x006b7c08
            "Want to use 3D sound on a device that doesn't support it !");
        error.assign("Want to use 3D sound on a device that doesn't support it !", 0, std::string::npos);
    }
    return true;
}

// deferred: 0x005a6fb0 coupled callers; SIB operand order remains unmatched.
void RHSound::FUN_005a6fb0(int channel, int type, RHSoundCacheEntry *entry, void *value, void *value2, void *value3)
{
    if (channel != -1)
    {
        RHSoundCacheEntry *previous = m_21c.m_04[channel].m_08;
        if (previous)
            --*(unsigned short *)((char *)previous + 0x1e);
        m_21c.m_04[channel].m_00 = 0;
        m_21c.m_04[channel].m_08 = 0;
        m_21c.m_04[channel].m_0c = 0;
        m_21c.m_04[channel].m_0c = 0;
        m_21c.m_04[channel].m_04 = 0;
        switch (type)
        {
        case 1:
            if (value)
                m_21c.m_04[channel].m_0c = value;
            break;
        case 5:
            m_21c.m_04[channel].m_04 = value3;
            m_21c.m_04[channel].m_0c = value2;
            break;
        }
        m_21c.m_04[channel].m_00 = type;
        if (entry)
        {
            m_21c.m_04[channel].m_08 = entry;
            ++*(unsigned short *)((char *)m_21c.m_04[channel].m_08 + 0x1e);
        }
    }
}

// FUNCTION: GAME 0x005a6f90
void *RHSound::FUN_005a6f90()
{
    if (m_20a)
        return FSOUND_GetOutputHandle();
    return 0;
}

// FUNCTION: GAME 0x005a7080
RHSoundCacheEntry *RHSound::FUN_005a7080(const RHSoundSettings &sound, bool load)
{
    RHSoundCacheEntry *entry;
    switch (sound.m_00)
    {
    case 1:
        {
            RHUnk005a7220 *source = (RHUnk005a7220 *)sound.m_14;
            int type = source->m_08;
            unsigned long id = source->m_0c;
            entry = m_000.FUN_005ae670(load, id, type == 1);
        }
        break;
    case 2:
    case 4:
        entry = m_000.GetFXSample(load, (unsigned long)sound.m_0c, (unsigned char)sound.m_10[0]);
        break;
    case 3:
        entry = m_000.FUN_005ae640(load, (unsigned long)sound.m_0c);
        break;
    case 5:
        entry = m_000.GetExclamationSample(load, (unsigned long)sound.m_0c, *(unsigned long *)sound.m_10);
        break;
    }
    if (!entry || (load && !entry->m_sample))
        return 0;
    return entry;
}

// FUNCTION: GAME 0x005a7110
void RHSound::FUN_005a7110(RHSoundSource *source)
{
    RHSoundSettings settings;
    settings.m_00 = 1;
    settings.m_14 = source;
    RHSoundPendingData sound(settings);
    RHSoundPendingNode *head = m_24c;
    RHSoundPendingNode *previous = head->m_04;
    RHSoundPendingNode *node = (RHSoundPendingNode *)operator new(sizeof(RHSoundPendingNode));
    RHSoundPendingNode *nextLink = head;
    if (!head)
        nextLink = node;
    node->m_00 = nextLink;
    RHSoundPendingNode *previousLink = previous;
    if (!previous)
        previousLink = node;
    node->m_04 = previousLink;
    head->m_04 = node;
    RHSoundPendingNode *linkedPrevious = node->m_04;
    linkedPrevious->m_00 = node;
    FUN_005aa990(&node->m_08, &sound);
    ++m_250;
}

// FUNCTION: GAME 0x005a71f0
bool RHSound::FUN_005a71f0(RHSoundSource *source)
{
    RHSoundPendingNode *node = m_24c->m_00;
    for (; node != m_24c; node = node->m_00)
        if (node->m_08.m_00.m_00 == 1 && node->m_08.m_00.m_14 == source)
            break;
    return node != m_24c;
}

// FUNCTION: GAME 0x005a7220
void RHSound::FUN_005a7220(void *value)
{
    RHUnk005a7220 *source = (RHUnk005a7220 *)value;
    switch (source->m_08)
    {
    case 0:
        source->m_4c = false;
        break;
    case 2:
        {
            float scale = source->m_48;
            int minimum = source->m_44;
            source->m_4a = (unsigned short)(((rand() * scale) * g_unk0x00677f7c) * (source->m_46 - minimum)
                / scale + minimum);
        }
        break;
    case 3:
        source->m_4c = false;
        m_200->FUN_005b4f00((RHSoundSource *)source);
        break;
    }
}

// STUB: GAME 0x005a72c0
int RHSound::FUN_005a72c0(const RHSoundSettings &sound, RHSoundChannelSettings &settings, unsigned int position)
{
    RHSoundCacheEntry *entry = FUN_005a7080(sound, true);
    if (entry)
    {
        if (m_210)
            m_138.FUN_005b3420(settings);
        else
            m_138.FUN_005b33b0(settings);
        int result = FSOUND_PlaySoundEx(-1, entry->m_sample, 0, true);
        if (result != -1)
        {
            int channel = result & 0xfff;
            FUN_005a7410(channel, settings);
            if (!FSOUND_SetCurrentPosition(channel, position))
                SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 756,
                    // STRING: GAME 0x006b7d6c
                    "Failed to set sample length !");
            FSOUND_SetPaused(result, false);
            switch (sound.m_00)
            {
            case 1:
                FUN_005a6fb0(channel, 1, entry, sound.m_14, 0, 0);
                break;
            case 2:
            case 4:
                FUN_005a6fb0(channel, sound.m_00, entry, 0, 0, sound.m_0c);
                break;
            case 3:
                FUN_005a6fb0(channel, 3, entry, 0, 0, sound.m_0c);
                break;
            case 5:
                FUN_005a6fb0(channel, 5, entry, 0, sound.m_14, sound.m_0c);
                break;
            }
            return channel;
        }
    }
    return -1;
}

// FUNCTION: GAME 0x005a7410
void RHSound::FUN_005a7410(int channel, RHSoundChannelSettings &settings)
{
    if (m_210)
    {
        m_138.FUN_005b3420(settings);
        if (!FSOUND_3D_SetAttributes(channel, settings.m_14, 0))
            SBAssert(1,
                // STRING: GAME 0x006b78c8
                "P:\\Robin Hood\\RHsound.cpp", 808,
                // STRING: GAME 0x006b7dd8
                "Unable to set 3D position.\n");
    }
    else
    {
        m_138.FUN_005b33b0(settings);
        if (!FSOUND_SetPan(channel, settings.m_10))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 817,
                // STRING: GAME 0x006b7dc0
                "Unable to set panning.\n");
    }
    if (!FSOUND_SetVolume(channel, settings.m_0e))
        SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 824,
            // STRING: GAME 0x006b7da8
            "Unable to set volume.\n");
    if (!FSOUND_SetPriority(channel, settings.m_0c))
        SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 829,
            // STRING: GAME 0x006b7d8c
            "Unable to set priority.\n");
}

// FUNCTION: GAME 0x005a74e0
void RHSound::FUN_005a74e0(unsigned long position)
{
    std::string name;
    switch (m_280)
    {
    case 0:
        {
            std::string *music = m_000.GetQuietMusic(m_284);
            name = *music;
        }
        break;
    case 1:
        {
            std::string *music = m_000.GetAlertMusic(m_284);
            name = *music;
        }
        break;
    case 2:
        {
            std::string *music = m_000.GetFightMusic(m_284);
            name = *music;
        }
        break;
    }
    if (m_254)
    {
        int channel = m_25c;
        FUN_005a90d0(m_254, channel);
    }
    if (name.compare(g_unk0x6c0560) != 0)
        m_258 = OpenStream(name, m_254, false, position);
    else
    {
        m_254 = 0;
        m_258 = 1;
    }
}

// Parked: integer volume loads and final stores reorder; effective-only match.
// STUB: GAME 0x005a7660
void RHSound::FUN_005a7660(bool dialogue)
{
    RHUnk005a9260 settings;
    settings = *(RHUnk005a9260 *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x44);
    float first = *(unsigned short *)((char *)&settings + 6) * g_unk0x00679dd4;
    float second = *(unsigned short *)((char *)&settings + 4) * g_unk0x00679dd4;
    float third = *(unsigned short *)((char *)&settings + 2) * g_unk0x00679dd4;
    float fourth = *(unsigned short *)&settings * g_unk0x00679dd4;
    if (dialogue)
    {
        float firstVolume = first;
        first = firstVolume * g_dialogueVolumeHigh;
        float secondVolume = second;
        second = secondVolume * g_dialogueVolumeHigh;
        float fourthVolume = fourth;
        fourth = fourthVolume * g_dialogueVolumeHigh;
    }
    float *geometry = (float *)&m_138;
    geometry[4] = second;
    geometry[5] = fourth;
    geometry[3] = first;
    geometry[7] = third;
    m_27c = 1;
    m_27d = 1;
}

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
extern unsigned short g_unk0x006c07e4;
extern unsigned short g_unk0x006c07e6;

// FUNCTION: GAME 0x005a7750
bool FUN_005a7750()
{
    int state = g_unk0x006c07e6 ? 2 : (g_unk0x006c07e4 ? 1 : 0);
    switch (state)
    {
    case 0:
        ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(0);
        break;
    case 1:
        ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(1);
        break;
    case 2:
        ((RHScriptSoundStateCalls *)g_unk0x006c1070)->FUN_005a7ef0(2);
        break;
    }
    ((RHSound *)g_unk0x006c1070)->m_27a = 1;
    return false;
}

// FUNCTION: GAME 0x005a77d0
bool FUN_005a77d0()
{
    ((RHSound *)g_unk0x006c1070)->m_27e = 1;
    return false;
}

// FUNCTION: GAME 0x005a77e0
bool FUN_005a77e0()
{
    ((RHSound *)*(RHArtificialIntelligenceSoundCalls *volatile *)&g_unk0x006c1070)->m_278 = 1;
    ((RHSound *)g_unk0x006c1070)->m_27f = 1;
    return false;
}

// FUNCTION: GAME 0x005a7800
bool RHSound::InitializeSoundEngine(std::string &error)
{
    if (g_unk0x006c0685)
    {
        if (FSOUND_GetVersion() != g_unk0x00679dd8)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1027,
                // STRING: GAME 0x006b7e14
                "Invalid DLL version ! Need FMOD %.02f\n", 3.6f);
        FSOUND_SetOutput(2);
        unsigned long driver;
        if (!FUN_005a6520(driver))
            FUN_005a67b0(driver);
        unsigned int caps;
        if (!FSOUND_GetDriverCaps(driver, &caps))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1040,
                // STRING: GAME 0x006b7df4
                "Failed get sound device caps");
        m_211 = caps & 1;
        m_212 = (caps & 2) || (caps & 16);
        unsigned long value;
        if (!FUN_005a9260((unsigned short)driver, true, value, error))
            return false;
        m_000.InitializeMenuCache();
        m_000.InitializeFXCache();
        FUN_005ad570(RHUnk00436500GetProfileManager());
    }
    return true;
}

// FUNCTION: GAME 0x005a7900
void RHSound::Activate(const RHSoundCacheMissionProfile *profile, bool flag)
{
    if (m_20a)
    {
        if (profile)
            m_000.InitializeMusic(profile);
        m_213 = flag;
        if (!m_000.m_135)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1131,
                // STRING: GAME 0x006b7e6c
                "FATAL: RHSound: Some samples are missing !");
        unsigned short count = m_200->m_sources.GetSize();
        for (unsigned short index = 0; index < count; ++index)
        {
            RHSoundSource *source = m_200->GetSoundSource(index);
            if (source && *((char *)source + 0x4c))
                FUN_005a7110(source);
        }
        m_288 = 0;
        m_28c = 0;
        m_290 = 0;
        m_27a = 1;
        m_27e = 0;
        m_27f = 0;
        m_20b = 1;
        if (g_unk0x006c1080)
            SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 1164,
                // STRING: GAME 0x006b7e3c
                "Fx to play list not empty at sound activation !");
    }
}

// FUNCTION: GAME 0x005a79f0
void RHSound::FUN_005a79f0(bool clear)
{
    if (m_254)
    {
        int channel = m_25c;
        FUN_005a90d0(m_254, channel);
    }
    if (m_270)
        FUN_005a90d0(m_270, m_274);
    if (m_268)
        FUN_005a90d0(m_268, m_26c);
    for (unsigned int channel = 0; channel < m_218; ++channel)
        if (channel != m_264 && m_21c.m_04[channel].m_00 != 4)
            FUN_005a8420(channel);
    if (clear)
    {
        m_200->RHUnk005b4ae0();
        m_000.FUN_005ae1c0(false);
    }
    else
    {
        FUN_005a8780();
        m_000.FUN_005aeda0();
    }
    RHSoundPendingNode *head = m_24c;
    RHSoundPendingNode *node = head->m_00;
    while (node != head)
    {
        RHSoundPendingNode *removed = node;
        node = node->m_00;
        removed->m_04->m_00 = removed->m_00;
        removed->m_00->m_04 = removed->m_04;
        removed->m_08.FUN_0052c5a0();
        operator delete(removed);
        --m_250;
    }
    for (unsigned int index = 0; index < m_218; ++index)
        m_21c.m_04[index].m_00 = 0;
    m_20b = 0;
}

// FUNCTION: GAME 0x005a7d40
void RHSound::ApplySoundSettings()
{
    if (m_20a)
    {
        std::string error;
        unsigned long value;
        if (!FUN_005a9260(m_208, false, value, error))
            SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 1330, SoundStringData(error));
        if (value != -1)
        {
            OpenStream(std::string(
                // STRING: GAME 0x006b7e98
                "menu"), m_260, true, value);
            m_264 = FUN_005a9040(m_260, 0, -1);
        }
        FSOUND_SetVolume(m_264, m_138.FUN_005b3490(false));
    }
}

// FUNCTION: GAME 0x005a7ef0
void RHScriptSoundStateCalls::FUN_005a7ef0(int state)
{
    RHSound *sound = (RHSound *)this;
    switch (state)
    {
    case 0:
        if (!sound->m_213)
        {
            sound->m_288 += 128;
            if (sound->m_288 > 256)
                sound->m_288 = 256;
            break;
        }
    case 1:
        sound->m_28c += 128;
        if (sound->m_28c > 256)
            sound->m_28c = 256;
        if (sound->m_280 < 1)
            sound->m_27a = 1;
        break;
    case 2:
        sound->m_290 += 128;
        if (sound->m_290 > 256)
            sound->m_290 = 256;
        if (sound->m_280 < 2)
            sound->m_27a = 1;
        break;
    }
}

// FUNCTION: GAME 0x005a7fb0
void RHScriptSoundStateCalls::FUN_005a7fb0(int state)
{
    RHSound *sound = (RHSound *)this;
    switch (state)
    {
    case 0:
    {
        unsigned long first = sound->m_213 ? 0 : 128;
        unsigned long second = sound->m_213 ? 128 : 0;
        sound->m_288 = first;
        sound->m_28c = second;
        sound->m_290 = 0;
        break;
    }
    case 1:
        sound->m_288 = 0;
        sound->m_290 = 0;
        sound->m_28c = 128;
        break;
    case 2:
        sound->m_288 = 0;
        sound->m_28c = 0;
        sound->m_290 = 128;
        break;
    }
    sound->m_27a = 1;
}

// FUNCTION: GAME 0x005a8040
unsigned short RHSound::FUN_005a8040()
{
    if (m_254)
        return (unsigned short)(FSOUND_Stream_GetTime(m_254) * 100 / m_258);
    return 0;
}

// FUNCTION: GAME 0x005a8420
void RHSound::FUN_005a8420(int channel)
{
    if (channel != -1 && channel != -2)
    {
        if (!FSOUND_StopSound(channel))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1639,
                // STRING: GAME 0x006b7ea0
                "Unable to stop channel %d.\n", channel);
        FUN_005a6fb0(channel, 0, 0, 0, 0, 0);
    }
}

// Parked: the shared pending-list owner and its EH cleanup type remain provisional.
// STUB: GAME 0x005a8470
void RHSound::FUN_005a8470(void *first, void *second)
{
    RHUnk00641782 lock;
    lock.FUN_00641782();
    void **sentinel = (void **)0x006c1088;
    unsigned long *references = (unsigned long *)0x006c1084;
    if (*sentinel == 0)
    {
        *sentinel = operator new(0x14);
        ((void **)*sentinel)[0] = 0;
        ((void **)*sentinel)[1] = 0;
        ((void **)*sentinel)[2] = 0;
        ((void **)*sentinel)[4] = (void *)1;
    }
    void **node = (void **)operator new(0x14);
    node[0] = node;
    node[1] = *sentinel;
    node[2] = node;
    node[4] = 0;
    ++*references;
    lock.FUN_0064181e();

    RHSoundPendingData data;
    m_200->FUN_005b4b50(first, second, &data);
    if (m_20a)
    {
        FUN_005ad400(&data);
        m_200->FUN_005b4db0();
        m_000.FUN_005aec70();
    }
    data.~RHSoundPendingData();
    FUN_005aa090(&first, node[0], node);
    FUN_0064158f(node);

    lock.FUN_00641782();
    if (--*references == 0)
    {
        operator delete(*sentinel);
        *sentinel = 0;
    }
    lock.FUN_0064181e();
}

// Parked: the original helper's list-value type is not attributed to RHSound.
// STUB: GAME 0x005a85e0
void RHSound::FUN_005a85e0()
{
    RHUnk00641782 lock;
    void **value = (void **)((char *)this + 4);
    void *memory = *value;
    FUN_005aa090(this, *(void **)memory, memory);
    FUN_0064158f(memory);
    *value = 0;
    *(void **)((char *)this + 0x0c) = 0;
    lock.FUN_00641782();
    unsigned long *references = (unsigned long *)0x006c1084;
    void **sentinel = (void **)0x006c1088;
    if (--*references == 0)
    {
        FUN_0064158f(*sentinel);
        *sentinel = 0;
    }
    lock.FUN_0064181e();
}

// FUNCTION: GAME 0x005a8650
void RHSound::FUN_005a8650(const SBGeoPoint2D &position, float zoom)
{
    SBGeoPoint2D &listener = *(SBGeoPoint2D *)((char *)this + 0x138);
    if (listener.FUN_005fc0e0(position))
    {
        listener = position;
        m_27d = 1;
    }
    if (((float *)((char *)this + 0x140))[0] != zoom)
    {
        ((RHSoundGeometry *)&m_138)->RHUnk005b2f30(zoom);
        m_27c = 1;
        m_27d = 1;
    }
    if (m_20b && m_210)
    {
        float attributes[3] = {0.0f, 0.0f, 0.0f};
        FSOUND_3D_Listener_SetAttributes(attributes, 0, 0.0f, 0.0f, -1.0f,
                                         0.0f, 1.0f, 0.0f);
    }
}

// FUNCTION: GAME 0x005a8700
void RHSound::FUN_005a8700(void *position, void *zoom)
{
    FUN_005a8650(*(const SBGeoPoint2D *)position, *(float *)&zoom);
    unsigned short count = (unsigned short)m_200->m_sources.GetSize();
    for (int index = 0; (unsigned short)index < count; ++index)
    {
        RHSoundSource *source = m_200->GetSoundSource(index);
        if (source && *((char *)source + 0x4c) && !FUN_005a71f0(source))
            FUN_005a7110(source);
    }
}

// Parked: compiler cleanup and list-node lifetime layout still differ.
// STUB: GAME 0x005a8780
void RHSound::FUN_005a8780()
{
    RHSoundPendingNode *head = m_24c;
    RHSoundPendingNode *node = head->m_00;
    while (node != head)
    {
        if (node->m_08.m_00.m_00 == 1)
        {
            RHSoundPendingNode *next = node->m_00;
            FUN_005a8420(node->m_08.m_18);
            node->m_04->m_00 = node->m_00;
            node->m_00->m_04 = node->m_04;
            node->m_08.FUN_0052c5a0();
            FUN_0064158f(node);
            --m_250;
            node = next;
        }
        else
            node = node->m_00;
    }
}

// FUNCTION: GAME 0x005a8880
bool RHSound::FUN_005a8880(RHSoundSource *source)
{
    if (m_20b)
        m_200->AddSoundSource(source);
    return true;
}

// FUNCTION: GAME 0x005a88a0
bool RHSound::FUN_005a88a0(void *source)
{
    if (m_20b && source)
    {
        FUN_005a8810(source);
        return m_200->FUN_005b4f00((RHSoundSource *)source);
    }
    return true;
}

// STUB: GAME 0x005a88e0
void RHSound::PlayJingle(int jingle)
{
    if (m_20a)
    {
        std::string path;
        std::string directory;
        directory =
            // STRING: GAME 0x006b7f5c
            "Data\\Sounds\\";
        path = FUN_004e4c70(directory, g_unk0x006b79ac[jingle]);
        FUN_005a90d0(m_268, m_26c);
        m_26c = -1;
        m_268 = FSOUND_Stream_OpenFile(SoundStringData(path), 0x2000, 0);
        if (!m_268)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1890,
                // STRING: GAME 0x006b7f20
                "FATAL: MISSING FILE \"%s\". Unable to open jingle stream !", SoundStringData(path));
        if (!FSOUND_Stream_SetEndCallback(m_268, (void *)0x005a77d0, 0))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1895,
                // STRING: GAME 0x006b7f00
                "Unable to set jingle callback !");
        if (jingle == 1 || jingle == 2)
        {
            int channel = m_25c;
            FUN_005a90d0(m_254, channel);
        }
        int channel = FSOUND_Stream_Play(-1, m_268);
        if (channel == -1)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1913,
                "Unable to play stream %s !", SoundStringData(path));
        m_26c = channel & 0xfff;
        if (!FSOUND_SetVolume(m_26c, m_138.FUN_005b34e0()))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 1921,
                "Unable to set volume for channel %d.\n", m_26c);
        FUN_005a6fb0(m_26c, 8, 0, 0, 0, 0);
    }
}

// FUNCTION: GAME 0x005a8b70
void RHArtificialIntelligenceSoundCalls::Unk005a8b70(int category, void *profile, unsigned short remark, long variant, SBGeoPoint2D *position, RHArtificialIntelligenceActor *actor)
{
    RHSound *sound = (RHSound *)this;
    if (sound->m_20b)
    {
        SBGeoPoint2D location;
        if (category == 0)
        {
            location = *(SBGeoPoint2D *)&sound->m_138;
            if (sound->m_210)
            {
                location.m_x -= g_unk0x006774a0;
                location.m_y -= g_unk0x006774a0;
            }
        }
        else
            location = *position;
        RHSoundSettings settings;
        settings.m_00 = 5;
        *(SBGeoPoint2D *)settings.m_04 = location;
        settings.m_0c = (void *)(((unsigned long)profile & 0xffff0000) | remark);
        *(long *)settings.m_10 = variant;
        settings.m_14 = actor;
        RHSoundPendingData data(settings);
        RHSoundPendingNode *head = sound->m_24c;
        RHSoundPendingNode *previous = head->m_04;
        RHSoundPendingNode *node = (RHSoundPendingNode *)operator new(sizeof(RHSoundPendingNode));
        RHSoundPendingNode *nextLink = head;
        if (!head)
            nextLink = node;
        node->m_00 = nextLink;
        RHSoundPendingNode *previousLink = previous;
        if (!previous)
            previousLink = node;
        node->m_04 = previousLink;
        head->m_04 = node;
        RHSoundPendingNode *linkedPrevious = node->m_04;
        linkedPrevious->m_00 = node;
        FUN_005aa990(&node->m_08, &data);
        ++sound->m_250;
    }
    else if (actor)
    {
        RHSoundVirtualSlot39 *receiver = (RHSoundVirtualSlot39 *)actor;
        unsigned short value = remark;
        receiver->Slot39(value);
    }
}

// FUNCTION: GAME 0x005a8d10
bool RHArtificialIntelligenceSoundCalls::Unk005a8d10(RHArtificialIntelligenceActor *actor)
{
    RHSound *sound = (RHSound *)this;
    if (sound->m_20b)
    {
        unsigned int channel = 0;
        for (; channel < sound->m_218; ++channel)
        {
            RHSoundChannel &entry = sound->m_21c.m_04[channel];
            if (entry.m_00 == 5 && entry.m_0c == actor)
            {
                sound->FUN_005a8420(channel);
                break;
            }
        }
        RHSoundPendingNode *head = sound->m_24c;
        RHSoundPendingNode *node = head->m_00;
        while (node != head)
        {
            if (node->m_08.m_00.m_00 == 5 && node->m_08.m_00.m_14 == actor)
            {
                node->m_04->m_00 = node->m_00;
                node->m_00->m_04 = node->m_04;
                node->m_08.FUN_0052c5a0();
                operator delete(node);
                --sound->m_250;
                break;
            }
            node = node->m_00;
        }
        return channel < sound->m_218;
    }
    return true;
}

// STUB: GAME 0x005a8dd0
unsigned long RHSound::OpenStream(const std::string &name, void *&stream, bool loop, unsigned long position)
{
    std::string path;
    path = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c0610, std::string("\\")), name), std::string(
        // STRING: GAME 0x006b7fa4
        ".wav"));
    stream = FSOUND_Stream_OpenFile(SoundStringData(path), (loop ? 2 : 1) | 0x1002050, 0);
    if (!stream)
        SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2069,
            // STRING: GAME 0x006b7f6c
            "FATAL: MISSING FILE \"%s\". Unable to open music stream !", SoundStringData(path));
    unsigned long length = FSOUND_Stream_GetLengthMs(stream);
    while (length == 0)
    {
        Sleep(1);
        length = FSOUND_Stream_GetLengthMs(stream);
    }
    if (position != 0 && position < length)
        while (!FSOUND_Stream_SetTime(stream, position))
            Sleep(1);
    return length;
}

// FUNCTION: GAME 0x005a9040
int RHSound::FUN_005a9040(void *stream, void *callback, int channel)
{
    if (stream)
    {
        if (!FSOUND_Stream_SetEndCallback(stream, callback, 0))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2107,
                // STRING: GAME 0x006b7fac
                "Unable to set stream callback !");
        int result;
        while ((result = FSOUND_Stream_Play(channel, stream)) == -1)
            Sleep(1);
        int index = result & 0xfff;
        FUN_005a6fb0(index, 6, 0, 0, 0, 0);
        return index;
    }
    return -1;
}

// FUNCTION: GAME 0x005a90d0
void RHSound::FUN_005a90d0(void *&stream, int &channel)
{
    if (stream)
    {
        FSOUND_Stream_SetEndCallback(stream, 0, 0);
        if (FSOUND_IsPlaying(channel) && !FSOUND_Stream_Stop(stream))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2146,
                // STRING: GAME 0x006b7fec
                "Unable to stop music !");
        if (!FSOUND_Stream_Close(stream))
            SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", 2152,
                // STRING: GAME 0x006b7fcc
                "Unable to close music stream !");
        stream = 0;
        FUN_005a6fb0(channel, 0, 0, 0, 0, 0);
        channel = -1;
    }
}

// FUNCTION: GAME 0x005a9170
bool RHSound::FUN_005a9170(unsigned long id)
{
    if (m_20a)
    {
        RHSoundCacheEntry *entry = FUN_005ae9f0(id);
        if (!entry)
            return false;
        int result = FSOUND_PlaySound(-1, entry->m_sample);
        if (result == -1)
            return false;
        int channel = result & 0xfff;
        float volume = m_138.m_10;
        volume *= g_unk0x00679148;
        if (!FSOUND_SetVolume(channel, (unsigned short)volume))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2200,
                // STRING: GAME 0x006b8050
                "Unable to set volume for channel %d !", channel);
        if (!FSOUND_SetPan(channel, 128))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2205,
                // STRING: GAME 0x006b802c
                "Unable to set pan for channel %d !", channel);
        if (!FSOUND_SetPriority(channel, 255))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2210,
                // STRING: GAME 0x006b8004
                "Unable to set priority for channel %d !", channel);
        FUN_005a6fb0(channel, 4, entry, 0, 0, 0);
    }
    return true;
}

// FUNCTION: GAME 0x005a9260
bool RHSound::FUN_005a9260(unsigned short driver, bool force, unsigned long &position, std::string &error)
{
    RHUnk005a9260 settings;
    settings = *(RHUnk005a9260 *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x44);
    position = -1;
    char mixer = settings.m_b == 0;
    bool reactivate = false;
    if (force || settings.m_a != m_210 || mixer != m_214)
    {
        m_210 = settings.m_a;
        m_214 = mixer;
        if (m_20a)
        {
            if (m_20b)
            {
                FUN_005a79f0(false);
                reactivate = true;
            }
            if (m_260)
            {
                position = FSOUND_Stream_GetTime(m_260);
                FUN_005a90d0(m_260, m_264);
            }
            m_000.FUN_005aeda0();
            FSOUND_Close();
            m_20a = 0;
        }
        if (!InitializeSound(driver, m_210, error))
            return false;
    }
    FUN_005a7660(m_279);
    if (reactivate)
        Activate(0, m_213);
    return true;
}

// FUNCTION: GAME 0x005a9380
void RHSound::FUN_005a9380()
{
    for (unsigned int channel = 0; channel < m_218; ++channel)
        if (!FSOUND_IsPlaying(channel))
            FUN_005a6fb0(channel, 0, 0, 0, 0, 0);
}

// FUNCTION: GAME 0x005a93c0
unsigned long FUN_005a93c0(unsigned long start, unsigned long end)
{
    unsigned long elapsed;
    if (start > end)
        elapsed = ~start + end + 1;
    else
        elapsed = end - start;
    return elapsed;
}

// FUNCTION: GAME 0x005a93e0
unsigned long RHSound::FUN_005a93e0(RHSoundPendingData &sound)
{
    unsigned long duration = 0;
    RHSoundCacheEntry *entry = FUN_005a7080(sound.m_00, false);
    if (entry)
        duration = entry->m_duration;
    return duration;
}

// FUNCTION: GAME 0x005a9400
bool RHSound::FUN_005a9400(const RHSoundSettings &sound)
{
    if (sound.m_00 == 2)
        return m_000.FUN_005ae320((unsigned long)sound.m_0c);
    return false;
}

// STUB: GAME 0x005a9420
void RHSound::FUN_005a9420()
{
    if (m_20b)
    {
        int count = (unsigned short)m_200->m_sources.GetSize();
        for (short index = 0; index < count; ++index)
        {
            RHSoundSource *source = m_200->GetSoundSource(index);
            if (source && *(int *)((char *)source + 8) == 2 && *((char *)source + 0x4c) && !FUN_005a71f0(source))
            {
                unsigned short &delay = *(unsigned short *)((char *)source + 0x4a);
                if (delay == 0)
                    FUN_005a7110(source);
                else
                    --delay;
            }
        }
        if (m_210)
            FSOUND_3D_Update();
        FUN_005a9380();
        if (m_27e)
        {
            FUN_005a90d0(m_268, m_26c);
            m_27e = 0;
        }
        if (m_27f)
        {
            FUN_005a90d0(m_270, m_274);
            m_27f = 0;
        }
        if (m_288)
            --m_288;
        if (m_28c)
            --m_28c;
        if (m_290)
            --m_290;
        if (m_27a)
        {
            unsigned long maximum;
            if (m_288 >= m_28c)
            {
                m_280 = 0;
                maximum = m_288;
            }
            else
            {
                m_280 = 1;
                maximum = m_28c;
            }
            if (m_290 > maximum)
                m_280 = 2;
            switch (m_280)
            {
            case 0:
                m_284 = (unsigned short)(rand() * (unsigned short)m_000.m_0b0.Size() * g_unk0x00677f7c);
                break;
            case 1:
                m_284 = (unsigned short)(rand() * (unsigned short)m_000.m_0dc.Size() * g_unk0x00677f7c);
                break;
            case 2:
                m_284 = (unsigned short)(rand() * (unsigned short)m_000.m_108.Size() * g_unk0x00677f7c);
                break;
            }
            FUN_005a74e0(0);
            m_27a = 0;
            m_27b = 1;
        }
        if (m_27b)
        {
            FUN_005a9040(m_254, (void *)0x005a7750, m_25c);
            m_27b = 0;
            m_27c = 1;
        }
        if (m_27c && m_25c != -1)
        {
            if (!FSOUND_SetVolume(m_25c, m_138.FUN_005b3490(true)))
                SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2539,
                    "Unable to set volume for channel %d.\n", m_25c);
            m_27c = 0;
        }
        RHSoundQueueNode *queued;
        for (queued = g_unk0x006c1078.m_04->m_00; queued != g_unk0x006c1078.m_04; queued = queued->m_00)
            FUN_005a72c0(queued->m_08, queued->m_20, 0);
        RHSoundQueueNode *head = g_unk0x006c1078.m_04;
        queued = head->m_00;
        while (queued != head)
        {
            RHSoundQueueNode *removed = queued;
            queued = queued->m_00;
            RHSoundQueueNode *result;
            g_unk0x006c1078.FUN_005aa1c0(&result, removed);
        }
        unsigned long time = GetTickCount();
        RHSoundPendingNode *node = m_24c->m_00;
        while (node != m_24c)
        {
            RHSoundPendingData &sound = node->m_08;
            unsigned long elapsed;
            if (sound.m_20 == 0)
            {
                sound.m_1c = time;
                sound.m_20 = FUN_005a93e0(sound);
                if (sound.m_20 == 0)
                    elapsed = 0;
                else
                    elapsed = FUN_005a93c0(sound.m_1c, time);
            }
            else if (sound.m_00.m_00 == 1 && *(int *)((char *)sound.m_00.m_14 + 8) == 1)
                elapsed = 0;
            else
                elapsed = FUN_005a93c0(sound.m_1c, time);
            if (elapsed >= sound.m_20)
            {
                if (sound.m_00.m_00 == 1)
                    FUN_005a7220(sound.m_00.m_14);
                else if (sound.m_00.m_00 == 5 && sound.m_00.m_14)
                    ((RHSoundVirtualSlot39 *)sound.m_00.m_14)->Slot39(*(unsigned short *)&sound.m_00.m_0c);
                node->m_04->m_00 = node->m_00;
                node->m_00->m_04 = node->m_04;
                sound.FUN_0052c5a0();
                RHSoundPendingNode *next = node->m_00;
                operator delete(node);
                --m_250;
                node = next;
            }
            else
                node = node->m_00;
        }
        RHSoundChannelSettings settings;
        if (m_27d)
        {
            for (node = m_24c->m_00; node != m_24c; node = node->m_00)
            {
                RHSoundPendingData &sound = node->m_08;
                bool flag = FUN_005a9400(sound.m_00);
                if (m_138.FUN_005b2ff0(sound.m_00, flag, settings))
                {
                    if (sound.m_18 != -2)
                    {
                        if (sound.m_18 != -1)
                            FUN_005a7410(sound.m_18, settings);
                        else
                            sound.m_18 = -2;
                    }
                }
                else
                {
                    FUN_005a8420(sound.m_18);
                    sound.m_18 = -1;
                }
            }
            m_27d = 0;
        }
        for (node = m_24c->m_00; node != m_24c; node = node->m_00)
        {
            RHSoundPendingData &sound = node->m_08;
            if (sound.m_18 == -2)
            {
                bool flag = FUN_005a9400(sound.m_00);
                if (m_138.FUN_005b2ff0(sound.m_00, flag, settings))
                {
                    RHSoundCacheEntry *entry = FUN_005a7080(sound.m_00, true);
                    if (entry)
                    {
                        float fraction = (float)FUN_005a93c0(sound.m_1c, time) / sound.m_20;
                        if (sound.m_00.m_00 == 1 && *(int *)((char *)sound.m_00.m_14 + 8) == 1)
                            fraction = (float)(fraction - floor(fraction));
                        int channel = FUN_005a72c0(sound.m_00, settings,
                            (unsigned int)(FSOUND_Sample_GetLength(entry->m_sample) * fraction));
                        if (channel != -1)
                            sound.m_18 = channel;
                    }
                }
                else
                    sound.m_18 = -1;
            }
        }
        FUN_005aec10();
    }
}

// FUNCTION: GAME 0x005a99b0
void RHSound::FUN_005a99b0()
{
    m_279 = true;
    FUN_005a7660(true);
}

// FUNCTION: GAME 0x005a99c0
void RHSound::FUN_005a99c0()
{
    m_279 = false;
    FUN_005a7660(false);
}

// FUNCTION: GAME 0x005a99d0
bool RHSound::PlayDialog(std::string &name)
{
    if (m_20a)
    {
        FUN_005a90d0(m_270, m_274);
        m_278 = 1;
        FUN_005f5a80(name, true);
        m_274 = -1;
        m_270 = FSOUND_Stream_OpenFile(SoundStringData(name), 0x2000, 0);
        if (!m_270)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2854,
                // STRING: GAME 0x006b809c
                "FATAL: MISSING FILE \"%s\". Unable to open dialog stream !", SoundStringData(name));
        if (!FSOUND_Stream_SetEndCallback(m_270, (void *)0x005a77e0, 0))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2859,
                // STRING: GAME 0x006b8078
                "Unable to set dialogue callback !");
        int channel = FSOUND_Stream_Play(-1, m_270);
        if (channel == -1)
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2868,
                // STRING: GAME 0x006b7ee4
                "Unable to play stream %s !", SoundStringData(name));
        m_274 = channel & 0xfff;
        if (!FSOUND_SetVolume(m_274, m_138.FUN_005b3500()))
            SBAssert(1, "P:\\Robin Hood\\RHsound.cpp", 2876,
                // STRING: GAME 0x006b7ebc
                "Unable to set volume for channel %d.\n", m_274);
        m_278 = 0;
        FUN_005a6fb0(m_274, 7, 0, 0, 0, 0);
    }
    return true;
}

extern float g_unk0x00677488;

// FUNCTION: GAME 0x005a9b30
float RHSound::GetDialogVolume()
{
    if (m_20a)
    {
        float left;
        float right;
        FSOUND_GetCurrentLevels(m_274, &left, &right);
        float sum = left + right;
        float level = sum < g_unk0x0067749c ? sum : 1.0f;
        if (m_138.FUN_005b3500() > g_unk0x0067749c)
            return g_unk0x00679148 / m_138.FUN_005b3500() * level;
        float divisor = g_unk0x0067749c;
        return g_unk0x00679148 / divisor * level;
    }
    return g_unk0x00677488;
}

// FUNCTION: GAME 0x005a9bf0
bool RHSound::IsDialogFinished()
{
    if (m_20a == 1)
        return *(bool *)&m_278;
    return true;
}

// FUNCTION: GAME 0x005a9c10
bool RHSound::CloseDialog()
{
    if (m_20a)
        FUN_005a90d0(m_270, m_274);
    return true;
}

#define RHSOUND_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) { \
        const char *reason = file.GetError()->m_chars; \
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", line, "Serialize failed reason is %s", reason ? reason : ""); \
        return false; \
    }

// FUNCTION: GAME 0x005a9c30
void RHSound::GetCacheStats(RHsampleCacheStats *stats, int &count)
{
    m_000.GetCacheStats(stats);
    count = m_250;
}

// Parked: preserving loading in an aggregate adds observable stores; scalar colouring remains unresolved.
// STUB: GAME 0x005a9c50
bool RHSound::Serialize(SBFile &file)
{
    char loading = file.m_bLoading;
    char available = g_unk0x006c0685;
    RHSOUND_ACCESS(available, 1, 2991);
    if (available)
    {
        RHSerializeName(file,
            // STRING: GAME 0x006b80d8
            "RHSound");
        char enabled;
        char spatial;
        char active;
        if (!loading)
        {
            enabled = m_20a;
            spatial = m_210;
            active = m_20b;
        }
        RHSOUND_ACCESS(enabled, 1, 3010);
        RHSOUND_ACCESS(spatial, 1, 3011);
        RHSOUND_ACCESS(active, 1, 3012);
        if (loading)
            FUN_005a79f0(false);
        ((RHSoundGeometry *)&m_138)->Serialize(file);
        unsigned char mode;
        if (loading)
        {
            RHSOUND_ACCESS(mode, 1, 3032);
            m_280 = mode;
        }
        else
        {
            mode = (unsigned char)m_280;
            RHSOUND_ACCESS(mode, 1, 3039);
        }
        unsigned short index;
        RHSOUND_ACCESS(index, 2, 3044);
        RHSOUND_ACCESS(m_288, 4, 3046);
        RHSOUND_ACCESS(m_28c, 4, 3047);
        RHSOUND_ACCESS(m_290, 4, 3048);
        RHSOUND_ACCESS(m_284, 2, 3050);
        unsigned long position;
        if (loading)
        {
            RHSOUND_ACCESS(position, 4, 3054);
            FUN_005a74e0(position);
        }
        else
        {
            position = m_254 ? FSOUND_Stream_GetTime(m_254) : 0;
            RHSOUND_ACCESS(position, 4, 3069);
        }
        m_200->Serialize(file);
        if (loading)
        {
            Activate(0, m_213 != 0);
            if (g_unk0x006c0685)
            {
                m_27a = 0;
                m_27b = 1;
                m_27d = 1;
            }
        }
    }
    return true;
}

#undef RHSOUND_ACCESS

// FUNCTION: GAME 0x005aa030
RHSoundQueue::~RHSoundQueue()
{
    RHSoundQueueNode *head = m_04;
    RHSoundQueueNode *next = head->m_00;
    while (next != head)
    {
        RHSoundQueueNode *node = next;
        next = next->m_00;
        node->m_04->m_00 = node->m_00;
        node->m_00->m_04 = node->m_04;
        ((RHSoundPendingData *)&node->m_08)->FUN_0052c5a0();
        operator delete(node);
        --m_08;
    }
    operator delete(m_04);
    m_04 = 0;
    m_08 = 0;
}

// Parked: distinct unlink locals and a named payload receiver retain the EAX/ECX scheduling seam.
// STUB: GAME 0x005aa1c0
RHSoundQueueNode **RHSoundQueue::FUN_005aa1c0(RHSoundQueueNode **result, RHSoundQueueNode *node)
{
    RHSoundQueueNode *previous = *(RHSoundQueueNode *volatile *)&node->m_04;
    RHSoundQueueNode *value = *(RHSoundQueueNode *volatile *)&node->m_00;
    RHSoundQueueNode *next = node->m_00;
    previous->m_00 = value;
    value = node->m_00;
    previous = node->m_04;
    value->m_04 = previous;
    ((RHSoundPendingData *)&node->m_08)->FUN_0052c5a0();
    operator delete(node);
    --m_08;
    *result = next;
    return result;
}

// FUNCTION: GAME 0x005aa860
RHUnk005aa860::~RHUnk005aa860()
{
    Remove(Begin(), End());
}

// FUNCTION: GAME 0x005aa920
void RHSoundChannels::FUN_005aa920()
{
    Remove(Begin(), End());
    Destroy(Begin(), End());
    operator delete(m_04);
    m_04 = 0;
    m_08 = 0;
    m_0c = 0;
}

// FUNCTION: GAME 0x005aa990
void FUN_005aa990(RHSoundPendingData *destination, const RHSoundPendingData *source)
{
    new (destination) RHSoundPendingData(*source);
}

// SIZE 0x38
struct RHUnk005aa9f0
{
    RHSoundSettings m_00;
    RHSoundChannelSettings m_18;
};

DECOMP_SIZE_ASSERT(RHUnk005aa9f0, 0x38)

// FUNCTION: GAME 0x005aa9f0
void FUN_005aa9f0(RHUnk005aa9f0 *destination, const RHUnk005aa9f0 *source)
{
    new (destination) RHUnk005aa9f0(*source);
}

void EmitSoundChannelCleanup(RHSoundChannels *channels)
{
    channels->FUN_005aa920();
}

// STUB: GAME 0x005aaa50
void RHSoundChannels::FUN_005aaa50(unsigned int count, const RHSoundChannel &value)
{
    if (Size() < count)
    {
        unsigned int added = count - Size();
        RHSoundChannel *position = m_08;
        if ((unsigned int)(m_0c - m_08) < added)
        {
            unsigned int growth = Size() < added ? added : Size();
            int capacity = FUN_0045a490() + growth;
            RHSoundChannel *storage = (RHSoundChannel *)operator new((capacity < 0 ? 0 : capacity) * sizeof(RHSoundChannel));
            RHSoundChannel *next = FUN_005aaca0(m_04, position, storage);
            FUN_005aacf0(next, added, value);
            FUN_005aaca0(position, m_08, next + added);
            ((RHScriptFXArray *)this)->Unk005008e0((void **)m_04, (void **)m_08);
            operator delete(m_04);
            m_0c = storage + capacity;
            m_08 = storage + (FUN_0045a490() + added);
            m_04 = storage;
        }
        else if ((unsigned int)(m_08 - position) < added)
        {
            FUN_005aaca0(position, m_08, position + added);
            FUN_005aacf0(m_08, added - (m_08 - position), value);
            std::fill(position, m_08, value);
            m_08 += added;
        }
        else if (added > 0)
        {
            FUN_005aaca0(m_08 - added, m_08, m_08);
            std::copy_backward(position, m_08 - added, m_08);
            std::fill(position, position + added, value);
            m_08 += added;
        }
    }
    else if (m_04 && count < Size())
    {
        RHSoundChannel *next = std::copy(m_08, m_08, m_04 + count);
        m_08 = next;
    }
}

// FUNCTION: GAME 0x005aaca0
RHSoundChannel *RHSoundChannels::FUN_005aaca0(RHSoundChannel *first, RHSoundChannel *last,
    RHSoundChannel *result)
{
    for (; first != last; ++first, ++result)
        new (result) RHSoundChannel(*first);
    return result;
}

// FUNCTION: GAME 0x005aacf0
void RHSoundChannels::FUN_005aacf0(RHSoundChannel *first, unsigned int count,
    const RHSoundChannel &value)
{
    for (; count > 0; --count, ++first)
        new (first) RHSoundChannel(value);
}

// FUNCTION: GAME 0x005aad30
RHSoundChannel *FUN_005aad30(const RHSoundChannel *first, const RHSoundChannel *last,
    RHSoundChannel *result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// FUNCTION: GAME 0x005aada0
void RHUnk005aada0::FUN_005aada0()
{
    Remove(Begin(), End());
}

// FUNCTION: GAME 0x005aadf0
SBGeoPoint2D *FUN_005aadf0(const SBGeoPoint2D *first, const SBGeoPoint2D *last,
    SBGeoPoint2D *result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

void EmitSoundPointCleanup(RHUnk005aada0 *points)
{
    points->FUN_005aada0();
}

void EmitSoundPointSearchCleanup(RHUnk005aa860 *points)
{
    points->~RHUnk005aa860();
}

// STUB: GAME 0x005ad570
void RHSound::FUN_005ad570(void *value)
{
    RHUnk005ad570Profiles *profiles = (RHUnk005ad570Profiles *)value;
    std::map<unsigned long, std::string> files;
    struct
    {
        unsigned long id;
        char terminator;
    } key;
    key.terminator = 0;
    char name[16];
    void **profile;
    for (profile = profiles->m_14; profile != profiles->m_18; ++profile)
    {
        key.id = *(unsigned long *)((char *)*profile + 0x3c);
        sprintf(name,
            // STRING: GAME 0x006b8314
            "actor%s.dat", &key.id);
        std::map<unsigned long, std::string>::iterator entry = files.insert(
            std::map<unsigned long, std::string>::value_type(key.id, RHProfileString())).first;
        entry->second.assign(name, strlen(name));
    }
    for (profile = profiles->m_24; profile != profiles->m_28; ++profile)
    {
        key.id = *(unsigned long *)((char *)*profile + 0x44);
        sprintf(name, "actor%s.dat", &key.id);
        std::map<unsigned long, std::string>::iterator entry = files.insert(
            std::map<unsigned long, std::string>::value_type(key.id, std::string())).first;
        entry->second.assign(name, strlen(name));
    }
    for (profile = profiles->m_64; profile != profiles->m_68; ++profile)
    {
        key.id = *(unsigned long *)((char *)*profile + 0x38);
        sprintf(name, "actor%s.dat", &key.id);
        std::map<unsigned long, std::string>::iterator entry = files.insert(
            std::map<unsigned long, std::string>::value_type(key.id, std::string())).first;
        entry->second.assign(name, strlen(name));
    }
    for (std::map<unsigned long, std::string>::iterator entry = files.begin(); entry != files.end(); ((RHSoundFileTree::Iterator *)&entry)->FUN_005b1030())
        if (entry->first != 0)
            m_000.InitializeExclamationsForProfile(entry->second, entry->first & 0xffff0000);
}

// FUNCTION: GAME 0x005ae9f0
RHSoundCacheEntry *RHSound::FUN_005ae9f0(unsigned long id)
{
    RHSoundCacheEntryMap &entries = *(RHSoundCacheEntryMap *)((char *)this + 0x94);
    RHSoundCacheGroupNode *found = entries.FUN_005b1430(id);
    RHSoundCacheGroupNode *head = *(RHSoundCacheGroupNode **)((char *)&entries + 4);
    RHSoundCacheGroupIterator entry(found);
    RHSoundCacheGroupIterator chosen = found == head || id < found->m_0c ? RHSoundCacheGroupIterator(head) : entry;
    if (chosen.m_node == *(RHSoundCacheGroupNode **)((char *)this + 0x98))
        return 0;
    RHSoundCacheEntry *sample = (RHSoundCacheEntry *)chosen.m_node->m_10;
    if (sample->m_sample)
    {
        ++*(unsigned int *)((char *)this + 0xa4);
        sample->m_stamp += 200;
    }
    else
        m_000.FUN_005ab7e0(sample, (char *)this + 0x54, 400, false);
    return sample;
}

// FUNCTION: GAME 0x005aec10
void RHSound::FUN_005aec10()
{
    m_000.UpdateCacheState(*(RHcacheData *)this, *(RHsampleCacheStats *)&m_000.m_01c, 5);
    m_000.UpdateCacheState(*(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x28), *(RHsampleCacheStats *)((char *)this + 0x38), 5);
    m_000.UpdateCacheState(*(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x44), *(RHsampleCacheStats *)((char *)this + 0x54), 2);
    m_000.UpdateCacheState(*(RHcacheData *)((char *)this + 0x60), *(RHsampleCacheStats *)&m_000.m_07c, 5);
    m_000.UpdateCacheState(*(std::map<unsigned long, RHSoundCacheEntry *> *)((char *)this + 0x94), *(RHsampleCacheStats *)((char *)this + 0xa4), 10);
}

// FUNCTION: GAME 0x005af320
RHSoundFileTree::Pair RHSoundFileTree::FUN_005af320(const Value &value)
{
    Pair answer;
    answer = FUN_005b0870(value);
    Pair result(answer.first, answer.second);
    return result;
}

// FUNCTION: GAME 0x005b0870
RHSoundFileTree::Pair RHSoundFileTree::FUN_005b0870(const Value &value)
{
    Node *parent = m_head;
    Node *node = parent->m_parent;
    bool left = true;
    {
        RHUnk00641782 lock;
        lock.FUN_00641782();
        while (node != g_unk0x006c10b4)
        {
            parent = node;
            left = value.m_key < node->m_key;
            node = left ? node->m_left : node->m_right;
        }
        lock.FUN_0064181e();
    }
    if (m_multi)
    {
        Pair result(FUN_005b1580(node, parent, value), true);
        return result;
    }
    Iterator previous;
    previous.m_node = parent;
    if (left)
    {
        if (previous.m_node == m_head->m_left)
        {
            Pair result(FUN_005b1580(node, parent, value), true);
            return result;
        }
        previous.FUN_005b1940();
    }
    if (previous.m_node->m_key < value.m_key)
    {
        Pair result(FUN_005b1580(node, parent, value), true);
        return result;
    }
    Pair result(previous, false);
    return result;
}

namespace std
{
template <> void _Construct(pair<const unsigned long, string> *, const pair<const unsigned long, string> &);
}

inline void RHSoundFileTree::Lrotate(Node *x)
{
    RHUnk00641782Lock lock;
    Node *y = x->m_right;
    x->m_right = y->m_left;
    if (y->m_left != g_unk0x006c10b4)
        y->m_left->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_left)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;
    y->m_left = x;
    x->m_parent = y;
}

inline void RHSoundFileTree::Rrotate(Node *x)
{
    RHUnk00641782Lock lock;
    Node *y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right != g_unk0x006c10b4)
        y->m_right->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_right)
        x->m_parent->m_right = y;
    else
        x->m_parent->m_left = y;
    y->m_right = x;
    x->m_parent = y;
}

static inline RHSoundFileTree::Node *RHSoundFileMin(RHSoundFileTree::Node *node)
{
    RHUnk00641782Lock lock;
    while (node->m_left != g_unk0x006c10b4)
        node = node->m_left;
    return node;
}

// FUNCTION: GAME 0x005b1030
void RHSoundFileTree::Iterator::FUN_005b1030()
{
    RHUnk00641782Lock lock;
    if (m_node->m_right != g_unk0x006c10b4)
        m_node = RHSoundFileMin(m_node->m_right);
    else {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

void EmitRHSoundFileIncrement(RHSoundFileTree::Iterator &iterator)
{
    iterator.FUN_005b1030();
}

// FUNCTION: GAME 0x005b1580
RHSoundFileTree::Iterator RHSoundFileTree::FUN_005b1580(Node *x, Node *y, const Value &value)
{
    RHUnk00641782Lock lock;
    Node *z = (Node *)operator new(sizeof(Node));
    z->m_parent = y;
    z->m_color = 0;
    z->m_left = g_unk0x006c10b4;
    z->m_right = g_unk0x006c10b4;
    typedef std::pair<const unsigned long, std::string> StoredValue;
    std::_Construct((StoredValue *)&z->m_key, *(const StoredValue *)&value);
    ++m_size;
    if (y == m_head || x != g_unk0x006c10b4 || value.m_key < y->m_key)
    {
        y->m_left = z;
        if (y == m_head)
        {
            Root() = z;
            m_head->m_right = z;
        }
        else if (y == m_head->m_left)
            m_head->m_left = z;
    }
    else
    {
        y->m_right = z;
        if (y == m_head->m_right)
            m_head->m_right = z;
    }
    for (x = z; x != Root() && x->m_parent->m_color == 0; )
        if (x->m_parent == Iterator::Left(x->m_parent->m_parent))
        {
            y = x->m_parent->m_parent->m_right;
            if (y->m_color == 0)
            {
                x->m_parent->m_color = 1;
                y->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                x = x->m_parent->m_parent;
            }
            else
            {
                if (x == x->m_parent->m_right)
                {
                    x = x->m_parent;
                    Lrotate(x);
                }
                x->m_parent->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                Rrotate(x->m_parent->m_parent);
            }
        }
        else
        {
            y = Iterator::Left(x->m_parent->m_parent);
            if (y->m_color == 0)
            {
                x->m_parent->m_color = 1;
                y->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                x = x->m_parent->m_parent;
            }
            else
            {
                if (x == x->m_parent->m_left)
                {
                    x = x->m_parent;
                    Rrotate(x);
                }
                x->m_parent->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                Lrotate(x->m_parent->m_parent);
            }
        }
    Root()->m_color = 1;
    return Iterator(z);
}

static inline RHSoundFileTree::Node *RHSoundFileTreeMax(RHSoundFileTree::Node *node)
{
    RHUnk00641782Lock lock;
    while (node->m_right != g_unk0x006c10b4)
        node = node->m_right;
    return node;
}

// FUNCTION: GAME 0x005b1940
void RHSoundFileTree::Iterator::FUN_005b1940()
{
    RHUnk00641782Lock lock;
    if (m_node->m_color == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (Left(m_node) != g_unk0x006c10b4)
        m_node = RHSoundFileTreeMax(Left(m_node));
    else
    {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

void EmitRHSoundFileTree(RHSoundFileTree *tree, const RHSoundFileTree::Value &value)
{
    tree->FUN_005af320(value);
}

// FUNCTION: GAME 0x005b23c0
RHSoundSettings::RHSoundSettings()
{
    ((SBGeoPoint2D *)m_04)->SBGeoPoint2D::SBGeoPoint2D();
}

// FUNCTION: GAME 0x005b23d0
RHSoundSettings::RHSoundSettings(const RHSoundSettings &other)
{
    m_00 = other.m_00;
    ((SBGeoPoint2D *)m_04)->SBGeoPoint2D::SBGeoPoint2D(*(const SBGeoPoint2D *)other.m_04);
    m_0c = other.m_0c;
    *(unsigned int *)m_10 = *(const unsigned int *)other.m_10;
    m_14 = other.m_14;
}

// FUNCTION: GAME 0x005b2ff0
bool RHSoundGeometryView::FUN_005b2ff0(const RHSoundSettings &sound, bool flag, RHSoundChannelSettings &settings)
{
    RHUnk005b2ff0Geometry *geometry = (RHUnk005b2ff0Geometry *)this;
    RHSoundGeometry *altitude = (RHSoundGeometry *)this;
    if (sound.m_00 == 1)
    {
        RHUnk005a7220 *source = (RHUnk005a7220 *)sound.m_14;
        if (source->m_10)
        {
            settings.m_00 = altitude->GetVolumeForAltitude(1.0f, (RHsoundSourceAltitude)*(int *)&source->m_40) * m_10;
            settings.m_04 = 0;
            settings.m_08 = 0;
        }
        else
        {
            RHUnk005b2410 bounds((float)source->m_14, source->m_1a * g_unk0x00679e04,
                (float)source->m_12, source->m_18 * g_unk0x00679e04);
            geometry->FUN_005b2a30(source, bounds);
            settings.m_00 = altitude->GetVolumeForAltitude(
                geometry->FUN_005b2510(*(float *)((char *)this + 0xb4), bounds),
                (RHsoundSourceAltitude)*(int *)&source->m_40) * m_10;
            if (settings.m_00 < g_unk0x006774f0)
                return false;
            settings.m_04 = geometry->FUN_005b25e0(bounds);
            settings.m_08 = geometry->FUN_005b27e0(bounds);
            float volume = settings.m_00;
            settings.m_0c = 64 - (unsigned short)(volume * g_unk0x00679e00);
        }
    }
    else
    {
        SBGeoPoint2D point;
        float nearDistance;
        float farDistance;
        if (sound.m_00 == 5)
        {
            nearDistance = *(float *)((char *)this + 0xc0);
            farDistance = *(float *)((char *)this + 0xc4);
        }
        else
        {
            nearDistance = *(float *)((char *)this + 0xb8);
            farDistance = *(float *)((char *)this + 0xbc);
        }
        RHUnk005b2410 bounds(nearDistance, 0.0f, farDistance, 1.0f);
        point = ((const SBGeoPoint2D *)sound.m_04)->Unk005fc110(*(SBGeoPoint2D *)this);
        float y = point.m_y;
        point.m_y = y * g_unk0x006774ec;
        float distance = (float)sqrt(point.m_x * point.m_x + point.m_y * point.m_y);
        float volume = altitude->GetVolumeForAltitude(geometry->FUN_005b2510(distance, bounds), RH_ALTITUDE_0);
        if (sound.m_00 >= 2)
        {
            if (sound.m_00 > 4)
            {
                if (sound.m_00 == 5)
                    volume *= *(float *)((char *)this + 0xc);
            }
            else
                volume *= m_10;
        }
        if (volume < g_unk0x006774f0)
            return false;
        settings.m_00 = volume;
        settings.m_04 = geometry->FUN_005b2560(point, bounds);
        settings.m_08 = geometry->FUN_005b2560(point, bounds);
        float channelVolume = settings.m_00;
        if (flag)
            channelVolume *= g_unk0x00679dfc;
        else
            channelVolume = channelVolume * g_unk0x00679df8 + g_unk0x00679df4;
        settings.m_0c = (unsigned short)channelVolume;
    }
    return true;
}

// Parked: floating-point store scheduling remains unmatched.
// STUB: GAME 0x005b33b0
void RHSoundGeometryView::FUN_005b33b0(RHSoundChannelSettings &settings)
{
    if (settings.m_00 < g_unk0x00679e10)
    {
        settings.m_0e = 0;
        settings.m_10 = 128;
        settings.m_12 = 128;
        return;
    }
    float volume = settings.m_00;
    settings.m_0e = (unsigned short)(volume * g_unk0x00679148);
    float pan = settings.m_04;
    settings.m_10 = (unsigned short)((pan + g_unk0x0067749c) * g_unk0x00679e08);
    float depth = settings.m_08;
    settings.m_12 = (unsigned short)((depth + g_unk0x0067749c) * g_unk0x00679e08);
}

// FUNCTION: GAME 0x005b3420
void RHSoundGeometryView::FUN_005b3420(RHSoundChannelSettings &settings)
{
    FUN_005b33b0(settings);
    if (settings.m_00 < g_unk0x00679e10)
    {
        settings.m_14[1] = 10000.0f;
        settings.m_14[0] = 0;
        settings.m_14[2] = 0;
        return;
    }
    settings.m_14[0] = -settings.m_04;
    double squared = pow(settings.m_08, g_unk0x00677670) + pow(settings.m_04, g_unk0x00677670);
    settings.m_14[2] = settings.m_08;
    settings.m_14[1] = (float)(g_unk0x00677d90 - sqrt(squared));
}

// FUNCTION: GAME 0x005b3490
unsigned short RHSoundGeometryView::FUN_005b3490(bool spatial)
{
    if (spatial)
    {
        float value = *(float *)((char *)this + 8);
        return (unsigned short)((g_unk0x00679e18 - (value - g_unk0x006774b8) * g_unk0x00679e20)
            * *(float *)((char *)this + 0x14)) >> 1;
    }
    float value = *(float *)((char *)this + 0x14);
    return (unsigned short)(value * g_unk0x00679148) >> 1;
}

// FUNCTION: GAME 0x005b34e0
unsigned short RHSoundGeometryView::FUN_005b34e0()
{
    float value = m_10;
    *(float *)((char *)this + 0x18) = value;
    return (unsigned short)(*(float *)((char *)this + 0x18) * g_unk0x00679148);
}

// FUNCTION: GAME 0x005b3500
unsigned short RHSoundGeometryView::FUN_005b3500()
{
    float value = *(float *)((char *)this + 0x1c);
    return (unsigned short)(value * g_unk0x00679148);
}

void RHSound::Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings)
{
    unsigned long driver;
    FUN_005a6520(driver);
    FUN_005a67b0(driver);
    InitializeSound(0, false, name);
    FUN_005a6f90();
    RHSoundSettings sound;
    FUN_005a72c0(sound, settings, 0);
    FUN_005a7410(0, settings);
    InitializeSoundEngine(name);
    Activate(0, false);
    ApplySoundSettings();
    FUN_005a8040();
    FUN_005a8420(0);
    FUN_005a8880(0);
    FUN_005a88a0(0);
    PlayJingle(0);
    OpenStream(name, m_270, false, 0);
    FUN_005a9040(0, 0, 0);
    FUN_005a90d0(m_270, m_274);
    FUN_005a9170(0);
    FUN_005a9420();
    PlayDialog(name);
    FUN_005a99b0();
    FUN_005a99c0();
    IsDialogFinished();
    GetDialogVolume();
    CloseDialog();
    RHsampleCacheStats stats[4];
    int count;
    GetCacheStats(stats, count);
    Serialize(file);
    FUN_005a71f0(0);
    RHSoundPendingData pending;
    FUN_005a93e0(pending);
    FUN_005a9400(sound);
    FUN_005a9380();
    m_138.FUN_005b34e0();
    m_138.FUN_005b3500();
}
