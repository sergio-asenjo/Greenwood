#include "RHSound.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

DECOMP_SIZE_ASSERT(RHSound, 0x294)
DECOMP_SIZE_ASSERT(RHUnk0040bb20, 0x10)
DECOMP_SIZE_ASSERT(RHUnk005a7220, 0x50)
DECOMP_SIZE_ASSERT(RHUnk005a9260, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005ad570Profiles, 0x6c)
DECOMP_SIZE_ASSERT(RHSoundQueue, 0x0c)
DECOMP_SIZE_ASSERT(RHSoundSourcesView, 0x20)
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

extern float g_unk0x0067749c;
extern double g_unk0x00677d90;

// GLOBAL: GAME 0x00677670
static double g_unk0x00677670 = 2.0;
// GLOBAL: GAME 0x00679e08
static double g_unk0x00679e08 = 127.5;
// GLOBAL: GAME 0x00679e10
static double g_unk0x00679e10 = 0.02;

// GLOBAL: GAME 0x0067a998
static const unsigned long g_unk0x0067a998[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

// GLOBAL: GAME 0x00679dd8
static float g_unk0x00679dd8 = 3.6f;

// GLOBAL: GAME 0x00679e18
static double g_unk0x00679e18 = 255.0;

// GLOBAL: GAME 0x00679e20
static double g_unk0x00679e20 = 90.0;

extern double g_unk0x006774b8;

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &) const;
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    float m_x;
    float m_y;
};

class RHScriptFXArray
{
public:
    void Unk005008e0(void **, void **);
};

enum RHsoundSourceAltitude
{
    RH_ALTITUDE_0,
    RH_ALTITUDE_1,
    RH_ALTITUDE_2,
    RH_ALTITUDE_3
};

class RHSoundGeometry
{
public:
    bool Serialize(SBFile &);
    float GetVolumeForAltitude(float, RHsoundSourceAltitude);
};

DECOMP_SIZE_ASSERT(RHUnk005b2410, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)

extern float g_unk0x006774ec;
// GLOBAL: GAME 0x006774f0
static float g_unk0x006774f0 = 0.01f;

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

// STUB: GAME 0x0040bb20
std::string &RHUnk0040bb20::FUN_0040bb20(const std::string &value, unsigned int first, unsigned int count)
{
    return append(value, first, count);
}

// deferred: 0x0052c5a0 coupled caller; member tail jump remains unmatched.
void RHSoundPendingData::FUN_0052c5a0()
{
    ((SBGeoPoint2D *)((char *)this + 4))->~SBGeoPoint2D();
}

inline RHSoundSettings::~RHSoundSettings()
{
    ((SBGeoPoint2D *)((char *)this + 4))->~SBGeoPoint2D();
}

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
                return FUN_006183c0(0, SoundStringData(devices), devices.size()) == hash;
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
    unsigned long hash = FUN_006183c0(0, SoundStringData(devices), devices.size());
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

// deferred: 0x005a7080 unannotated pending reccmp #534
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
            entry = FUN_005ae670(load, id, type == 1);
        }
        break;
    case 2:
    case 4:
        entry = m_000.GetFXSample(load, (unsigned long)sound.m_0c, (unsigned char)sound.m_10[0]);
        break;
    case 3:
        entry = FUN_005ae640(load, (unsigned long)sound.m_0c);
        break;
    case 5:
        entry = m_000.GetExclamationSample(load, (unsigned long)sound.m_0c, *(unsigned long *)sound.m_10);
        break;
    }
    if (!entry || (load && !entry->m_sample))
        return 0;
    return entry;
}

// coupled: effective-only pending-node argument register selection.
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
    node->m_04->m_00 = node;
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

// STUB: GAME 0x005a7220
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
            source->m_4a = (unsigned short)(rand() * scale * g_unk0x00677f7c * (source->m_46 - minimum) / scale + minimum);
        }
        break;
    case 3:
        source->m_4c = false;
        ((RHUnk005a7220Manager *)m_200)->FUN_005b4f00(source);
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

// deferred: 0x005a74e0 unannotated pending reccmp #534
void RHSound::FUN_005a74e0(unsigned long position)
{
    std::string name;
    switch (m_280)
    {
    case 0:
        {
            std::string *music = m_000.GetQuietMusic(m_284);
            ((RHProfileText *)&name)->FUN_00401ce0(*music, 0, std::string::npos);
        }
        break;
    case 1:
        {
            std::string *music = m_000.GetAlertMusic(m_284);
            ((RHProfileText *)&name)->FUN_00401ce0(*music, 0, std::string::npos);
        }
        break;
    case 2:
        {
            std::string *music = m_000.GetFightMusic(m_284);
            ((RHProfileText *)&name)->FUN_00401ce0(*music, 0, std::string::npos);
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

// deferred: 0x005a7800 unannotated pending reccmp #534
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

// deferred: 0x005a7900 unannotated pending reccmp #534
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
        unsigned short count = m_200->m_04.GetSize();
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

// deferred: 0x005a79f0 unannotated pending reccmp #534
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
        ((RHUnk005a7220Manager *)m_200)->FUN_005b4ae0();
        FUN_005ae1c0(false);
    }
    else
    {
        FUN_005a8780();
        FUN_005aeda0();
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

// deferred: 0x005a7d40 unannotated pending reccmp #534
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

// deferred: 0x005a90d0 unannotated pending reccmp #534
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

// deferred: 0x005a9260 unannotated pending reccmp #534
bool RHSound::FUN_005a9260(unsigned short driver, bool force, unsigned long &position, std::string &error)
{
    RHUnk005a9260 settings;
    settings = *(RHUnk005a9260 *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x44);
    position = -1;
    char mixer = settings.m_0b == 0;
    bool reactivate = false;
    if (force || settings.m_0a != m_210 || mixer != m_214)
    {
        m_210 = settings.m_0a;
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
            FUN_005aeda0();
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
        return FUN_005ae320(sound.m_0c);
    return false;
}

// STUB: GAME 0x005a9420
void RHSound::FUN_005a9420()
{
    if (m_20b)
    {
        int count = (unsigned short)m_200->m_04.GetSize();
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

#define RHSOUND_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) { \
        const char *reason = file.GetError()->m_chars; \
        SBAssert(0, "P:\\Robin Hood\\RHsound.cpp", line, "Serialize failed reason is %s", reason ? reason : ""); \
        return false; \
    }

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
    for (std::map<unsigned long, std::string>::iterator entry = files.begin(); entry != files.end(); ++entry)
        if (entry->first != 0)
            m_000.InitializeExclamationsForProfile(entry->second, entry->first & 0xffff0000);
}

// deferred: 0x005ae9f0 unannotated pending reccmp #534
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
    FUN_005ab570(this, m_000.m_01c, 5);
    FUN_005ab5e0((char *)this + 0x28, (char *)this + 0x38, 5);
    FUN_005ab5e0((char *)this + 0x44, (char *)this + 0x54, 2);
    FUN_005ab570((char *)this + 0x60, m_000.m_07c, 5);
    FUN_005ab5e0((char *)this + 0x94, (char *)this + 0xa4, 10);
}

// STUB: GAME 0x005b2ff0
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
            settings.m_0c = 64 - (unsigned short)(settings.m_00 * g_unk0x00679e00);
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
        point.m_y *= g_unk0x006774ec;
        float distance = (float)sqrt(point.m_x * point.m_x + point.m_y * point.m_y);
        float volume = altitude->GetVolumeForAltitude(geometry->FUN_005b2510(distance, bounds), RH_ALTITUDE_0);
        if (sound.m_00 >= 2 && sound.m_00 <= 4)
            volume *= m_10;
        else if (sound.m_00 == 5)
            volume *= *(float *)((char *)this + 0xc);
        if (volume < g_unk0x006774f0)
            return false;
        settings.m_00 = volume;
        settings.m_04 = geometry->FUN_005b2560(point, bounds);
        settings.m_08 = geometry->FUN_005b2560(point, bounds);
        if (flag)
            settings.m_0c = (unsigned short)(settings.m_00 * g_unk0x00679dfc);
        else
            settings.m_0c = (unsigned short)(settings.m_00 * g_unk0x00679df8 + g_unk0x00679df4);
    }
    return true;
}

// coupled: effective-only floating-point store scheduling.
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

// deferred: 0x005b3420 unannotated pending reccmp #534
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

// STUB: GAME 0x005b34e0
unsigned short RHSoundGeometryView::FUN_005b34e0()
{
    float value = m_10;
    *(float *)((char *)this + 0x18) = value;
    value *= g_unk0x00679148;
    return (unsigned short)value;
}

// deferred: 0x005b3500 called by PlayDialog; CRT tail jump remains unmatched.
unsigned short RHSoundGeometryView::FUN_005b3500()
{
    float value = *(float *)((char *)this + 0x1c);
    return (unsigned short)(value * g_unk0x00679148);
}

#define RHSOUND_CRC_STEP crc = g_unk0x0067a998[(crc & 0xff) ^ (unsigned char)*data++] ^ (crc >> 8)

// FUNCTION: GAME 0x006183c0
unsigned long FUN_006183c0(unsigned long crc, const char *data, unsigned long length)
{
    if (!data)
        return 0;
    crc = ~crc;
    while (length >= 8)
    {
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        RHSOUND_CRC_STEP;
        length -= 8;
    }
    if (length)
        do
        {
            RHSOUND_CRC_STEP;
        } while (--length);
    return ~crc;
}

#undef RHSOUND_CRC_STEP

void RHSound::Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings)
{
    ((RHUnk0040bb20 *)&name)->FUN_0040bb20(name, 0, 0);
    unsigned long driver;
    FUN_005a6520(driver);
    FUN_005a67b0(driver);
    InitializeSound(0, false, name);
    RHSoundSettings sound;
    FUN_005a72c0(sound, settings, 0);
    FUN_005a7410(0, settings);
    InitializeSoundEngine(name);
    Activate(0, false);
    ApplySoundSettings();
    FUN_005a8420(0);
    PlayJingle(0);
    OpenStream(name, m_270, false, 0);
    FUN_005a9040(0, 0, 0);
    FUN_005a90d0(m_270, m_274);
    FUN_005a9170(0);
    FUN_005a9420();
    PlayDialog(name);
    Serialize(file);
    FUN_005a71f0(0);
    RHSoundPendingData pending;
    FUN_005a93e0(pending);
    FUN_005a9400(sound);
    FUN_005a9380();
    m_138.FUN_005b34e0();
    m_138.FUN_005b3500();
}
