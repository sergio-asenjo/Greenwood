#include "RHSound.h"
#include <windows.h>
#include <math.h>

// GLOBAL: GAME 0x00679dd8
static float g_unk0x00679dd8 = 3.6f;

class RHProfileManager;
RHProfileManager *RHUnk00436500GetProfileManager();

class RHSoundGeometry
{
public:
    bool Serialize(SBFile &);
};

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

void RHSound::Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings)
{
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
}
