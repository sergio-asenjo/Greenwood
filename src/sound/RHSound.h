#ifndef RHSOUND_H
#define RHSOUND_H

#include "RHSoundCacheEntry.h"
#include "RHSoundCache.h"
#include <windows.h>

extern LONG (__stdcall *g_rhsoundRegSetValueExA)(HKEY, LPCSTR, DWORD, DWORD, const BYTE *, DWORD);
extern LONG (__stdcall *g_rhsoundRegOpenKeyExA)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
extern LONG (__stdcall *g_rhsoundRegCloseKey)(HKEY);
extern LONG (__stdcall *g_rhsoundRegCreateKeyExA)(HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD);
extern LONG (__stdcall *g_rhsoundRegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);

class SBFile;

// SIZE 0x10
class RHUnk0040bb20 : public std::string
{
public:
    std::string &FUN_0040bb20(const std::string &, unsigned int, unsigned int);
};
class RHSoundSource;
struct RHSoundPendingNode;
struct RHSoundPendingData;
struct RHSoundQueueNode;

// SIZE 0x04
class RHSoundVirtualSlot39
{
public:
    virtual void Slot00() = 0; // vtable+0x00
    virtual void Slot01() = 0; // vtable+0x04
    virtual void Slot02() = 0; // vtable+0x08
    virtual void Slot03() = 0; // vtable+0x0c
    virtual void Slot04() = 0; // vtable+0x10
    virtual void Slot05() = 0; // vtable+0x14
    virtual void Slot06() = 0; // vtable+0x18
    virtual void Slot07() = 0; // vtable+0x1c
    virtual void Slot08() = 0; // vtable+0x20
    virtual void Slot09() = 0; // vtable+0x24
    virtual void Slot10() = 0; // vtable+0x28
    virtual void Slot11() = 0; // vtable+0x2c
    virtual void Slot12() = 0; // vtable+0x30
    virtual void Slot13() = 0; // vtable+0x34
    virtual void Slot14() = 0; // vtable+0x38
    virtual void Slot15() = 0; // vtable+0x3c
    virtual void Slot16() = 0; // vtable+0x40
    virtual void Slot17() = 0; // vtable+0x44
    virtual void Slot18() = 0; // vtable+0x48
    virtual void Slot19() = 0; // vtable+0x4c
    virtual void Slot20() = 0; // vtable+0x50
    virtual void Slot21() = 0; // vtable+0x54
    virtual void Slot22() = 0; // vtable+0x58
    virtual void Slot23() = 0; // vtable+0x5c
    virtual void Slot24() = 0; // vtable+0x60
    virtual void Slot25() = 0; // vtable+0x64
    virtual void Slot26() = 0; // vtable+0x68
    virtual void Slot27() = 0; // vtable+0x6c
    virtual void Slot28() = 0; // vtable+0x70
    virtual void Slot29() = 0; // vtable+0x74
    virtual void Slot30() = 0; // vtable+0x78
    virtual void Slot31() = 0; // vtable+0x7c
    virtual void Slot32() = 0; // vtable+0x80
    virtual void Slot33() = 0; // vtable+0x84
    virtual void Slot34() = 0; // vtable+0x88
    virtual void Slot35() = 0; // vtable+0x8c
    virtual void Slot36() = 0; // vtable+0x90
    virtual void Slot37() = 0; // vtable+0x94
    virtual void Slot38() = 0; // vtable+0x98
    virtual void Slot39(unsigned short) = 0; // vtable+0x9c
};

// SIZE 0x0c
struct RHSoundQueue
{
    undefined m_00[4]; // 0x00
    RHSoundQueueNode *m_04; // 0x04
    unsigned int m_08; // 0x08
    RHSoundQueueNode **FUN_005aa1c0(RHSoundQueueNode **, RHSoundQueueNode *);
};

// SIZE 0x20
struct RHSoundSourcesView
{
    undefined4 m_00; // 0x00
    RHSoundSource **m_04; // 0x04
    RHSoundSource **m_08; // 0x08
    undefined m_0c[0x14]; // 0x0c
    int GetSize() const { return m_04 == 0 ? 0 : m_08 - m_04; }
};

// SIZE 0x24
class RHSoundSourceManager
{
public:
    RHSoundSource *GetSoundSource(unsigned short);
    bool Serialize(SBFile &);
    undefined m_00[4]; // 0x00
    RHSoundSourcesView m_04; // 0x04
};

// SIZE 0x20
struct RHSoundChannelSettings
{
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    unsigned short m_0c; // 0x0c
    unsigned short m_0e; // 0x0e
    unsigned short m_10; // 0x10
    unsigned short m_12; // 0x12
    float m_14[3]; // 0x14
};

// SIZE 0xc8
struct RHSoundGeometryView
{
    void FUN_005b33b0(RHSoundChannelSettings &settings);
    void FUN_005b3420(RHSoundChannelSettings &settings);
    unsigned short FUN_005b3500();
    unsigned short FUN_005b3490(bool);
    unsigned short FUN_005b34e0();
    bool FUN_005b2ff0(const struct RHSoundSettings &, bool, RHSoundChannelSettings &);
    undefined m_00[0x10]; // 0x00
    float m_10; // 0x10
    undefined m_14[0xb4]; // 0x14
};

// SIZE 0x10
struct RHSoundChannel
{
    int m_00; // 0x00
    void *m_04; // 0x04
    RHSoundCacheEntry *m_08; // 0x08
    void *m_0c; // 0x0c
};

// SIZE 0x2c
struct RHSoundChannels
{
    undefined4 m_00; // 0x00
    RHSoundChannel *m_04; // 0x04
    RHSoundChannel *m_08; // 0x08
    RHSoundChannel *m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    bool m_14; // 0x14
    undefined m_15[0x17]; // 0x15
    unsigned int Size() const { return m_04 ? m_08 - m_04 : 0; }
    void FUN_005aaa50(unsigned int, const RHSoundChannel &);
    int FUN_0045a490();
    RHSoundChannel *FUN_005aaca0(RHSoundChannel *, RHSoundChannel *, RHSoundChannel *);
    void FUN_005aacf0(RHSoundChannel *, unsigned int, const RHSoundChannel &);
};

// SIZE 0x294
class RHSound
{
public:
    bool FUN_005a6520(unsigned long &driver);
    void FUN_005a67b0(unsigned long &driver);
    bool InitializeSound(unsigned short driver, bool spatial, std::string &error);
    int FUN_005a72c0(const struct RHSoundSettings &sound, RHSoundChannelSettings &settings, unsigned int position);
    void FUN_005a7410(int channel, RHSoundChannelSettings &settings);
    bool InitializeSoundEngine(std::string &error);
    void Activate(const RHSoundCacheMissionProfile *profile, bool flag);
    void ApplySoundSettings();
    void FUN_005a8420(int channel);
    void PlayJingle(int jingle);
    unsigned long OpenStream(const std::string &name, void *&stream, bool loop, unsigned long position);
    int FUN_005a9040(void *stream, void *callback, int channel);
    void FUN_005a90d0(void *&stream, int &channel);
    bool FUN_005a9170(unsigned long id);
    void FUN_005a9420();
    bool PlayDialog(std::string &name);
    bool Serialize(SBFile &file);
    void FUN_005a6fb0(int channel, int type, RHSoundCacheEntry *entry, void *value, void *value2, void *value3);
    RHSoundCacheEntry *FUN_005ae9f0(unsigned long id);
    RHSoundCacheEntry *FUN_005a7080(const RHSoundSettings &, bool);
    void FUN_005a7110(RHSoundSource *);
    bool FUN_005a9260(unsigned short, bool, unsigned long &, std::string &);
    void FUN_005ad570(void *);
    void FUN_005a79f0(bool);
    void FUN_005a74e0(unsigned long);
    bool FUN_005a71f0(RHSoundSource *);
    void FUN_005a7220(void *);
    void FUN_005a9380();
    void FUN_005aec10();
    void FUN_005ab570(void *, unsigned int &, unsigned short);
    void FUN_005ab5e0(void *, void *, unsigned short);
    void FUN_005a7660(bool);
    void FUN_005a8780();
    void FUN_005ae1c0(bool);
    void FUN_005aeda0();
    RHSoundCacheEntry *FUN_005ae640(bool, unsigned long);
    RHSoundCacheEntry *FUN_005ae670(bool, unsigned long, bool);
    unsigned long FUN_005a93e0(RHSoundPendingData &);
    bool FUN_005a9400(const RHSoundSettings &);
    bool FUN_005ae320(void *);
    void Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings);

    RHSoundCache m_000; // 0x000
    RHSoundGeometryView m_138; // 0x138
    RHSoundSourceManager *m_200; // 0x200
    void *m_204; // 0x204
    unsigned short m_208; // 0x208
    char m_20a; // 0x20a
    char m_20b; // 0x20b
    undefined m_20c[4]; // 0x20c
    bool m_210; // 0x210
    char m_211; // 0x211
    char m_212; // 0x212
    bool m_213; // 0x213
    char m_214; // 0x214
    undefined m_215[3]; // 0x215
    unsigned int m_218; // 0x218
    RHSoundChannels m_21c; // 0x21c
    undefined m_248[4]; // 0x248
    RHSoundPendingNode *m_24c; // 0x24c
    unsigned int m_250; // 0x250
    void *m_254; // 0x254
    unsigned long m_258; // 0x258
    int m_25c; // 0x25c
    void *m_260; // 0x260
    int m_264; // 0x264
    void *m_268; // 0x268
    int m_26c; // 0x26c
    void *m_270; // 0x270
    int m_274; // 0x274
    char m_278; // 0x278
    bool m_279; // 0x279
    char m_27a; // 0x27a
    char m_27b; // 0x27b
    char m_27c; // 0x27c
    char m_27d; // 0x27d
    char m_27e; // 0x27e
    char m_27f; // 0x27f
    int m_280; // 0x280
    unsigned short m_284; // 0x284
    undefined m_286[2]; // 0x286
    unsigned long m_288; // 0x288
    unsigned long m_28c; // 0x28c
    unsigned long m_290; // 0x290
};

// SIZE 0x18
struct RHSoundSettings
{
    RHSoundSettings();
    ~RHSoundSettings();
    int m_00; // 0x00
    undefined m_04[8]; // 0x04
    void *m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    void *m_14; // 0x14
};

// SIZE 0x50
struct RHUnk005a7220
{
    undefined m_00[8]; // 0x00
    int m_08; // 0x08
    unsigned long m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11; // 0x11
    unsigned short m_12; // 0x12
    unsigned short m_14; // 0x14
    undefined m_16[2]; // 0x16
    unsigned short m_18; // 0x18
    unsigned short m_1a; // 0x1a
    undefined m_1c[0x24]; // 0x1c
    int m_40; // 0x40
    unsigned short m_44; // 0x44
    unsigned short m_46; // 0x46
    unsigned short m_48; // 0x48
    unsigned short m_4a; // 0x4a
    bool m_4c; // 0x4c
    undefined m_4d[3]; // 0x4d
};

// SIZE 0x0c
struct RHUnk005a9260
{
    RHUnk005a9260();
    undefined m_00[0xa]; // 0x00
    bool m_0a; // 0x0a
    char m_0b; // 0x0b
};

// SIZE 0x6c
struct RHUnk005ad570Profiles
{
    undefined m_00[0x14]; // 0x00
    void **m_14; // 0x14
    void **m_18; // 0x18
    undefined m_1c[8]; // 0x1c
    void **m_24; // 0x24
    void **m_28; // 0x28
    undefined m_2c[0x38]; // 0x2c
    void **m_64; // 0x64
    void **m_68; // 0x68
};

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

extern undefined g_unk0x006c0e48[];

class RHUnk005a7220Manager
{
public:
    void FUN_005b4f00(RHUnk005a7220 *);
    void FUN_005b4ae0();
};

// SIZE 0x10
struct RHUnk005b2410
{
    RHUnk005b2410(float, float, float, float);
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
};

class SBGeoPoint2D;
class RHUnk005b2ff0Geometry
{
public:
    float FUN_005b2510(float, const RHUnk005b2410 &);
    float FUN_005b2560(const SBGeoPoint2D &, const RHUnk005b2410 &);
    float FUN_005b25e0(const RHUnk005b2410 &);
    float FUN_005b27e0(const RHUnk005b2410 &);
    void FUN_005b2a30(RHUnk005a7220 *, RHUnk005b2410 &);
};

// SIZE 0x24
struct RHSoundPendingData
{
    RHSoundPendingData() {}
    RHSoundPendingData(const RHSoundSettings &);
    ~RHSoundPendingData();
    RHSoundSettings m_00; // 0x00
    int m_18; // 0x18
    unsigned long m_1c; // 0x1c
    unsigned long m_20; // 0x20
    void FUN_0052c5a0();
};

// SIZE 0x2c
struct RHSoundPendingNode
{
    RHSoundPendingNode *m_00; // 0x00
    RHSoundPendingNode *m_04; // 0x04
    RHSoundPendingData m_08; // 0x08
};

// SIZE 0x40
struct RHSoundQueueNode
{
    RHSoundQueueNode *m_00; // 0x00
    RHSoundQueueNode *m_04; // 0x04
    RHSoundSettings m_08; // 0x08
    RHSoundChannelSettings m_20; // 0x20
};

extern RHSoundQueue g_unk0x006c1078;
unsigned long FUN_005a93c0(unsigned long, unsigned long);

extern float g_unk0x00679148;
extern char g_unk0x006c0685;
extern unsigned long g_unk0x006c1080;
extern std::string g_unk0x006c0610;
extern "C" signed char __stdcall FSOUND_SetPaused(int, signed char);
extern "C" signed char __stdcall FSOUND_SetCurrentPosition(int, unsigned int);
extern "C" int __stdcall FSOUND_PlaySoundEx(int, void *, void *, signed char);
extern "C" signed char __stdcall FSOUND_SetOutput(int);
extern "C" unsigned int __stdcall FSOUND_GetNumDrivers();
extern "C" const char *__stdcall FSOUND_GetDriverName(int);
extern "C" signed char __stdcall FSOUND_SetHWND(void *);
extern "C" signed char __stdcall FSOUND_SetDriver(int);
extern "C" signed char __stdcall FSOUND_SetMixer(int);
extern "C" signed char __stdcall FSOUND_SetMinHardwareChannels(int);
extern "C" signed char __stdcall FSOUND_SetMaxHardwareChannels(int);
extern "C" signed char __stdcall FSOUND_SetBufferSize(int);
extern "C" signed char __stdcall FSOUND_Init(int, int, unsigned int);
extern "C" void __stdcall FSOUND_3D_Listener_SetDistanceFactor(float);
extern "C" void __stdcall FSOUND_3D_Listener_SetRolloffFactor(float);
extern "C" int __stdcall FSOUND_GetMaxChannels();
extern "C" unsigned int __stdcall FSOUND_GetNumHardwareChannels();
extern "C" void __stdcall FSOUND_3D_Update();
unsigned long FUN_006183c0(unsigned long, const char *, unsigned long);
extern "C" float __stdcall FSOUND_GetVersion();
extern "C" signed char __stdcall FSOUND_GetDriverCaps(int, unsigned int *);
extern "C" signed char __stdcall FSOUND_Stream_SetTime(void *, unsigned int);
extern "C" unsigned int __stdcall FSOUND_Stream_GetLengthMs(void *);
extern "C" unsigned int __stdcall FSOUND_Stream_GetTime(void *);
std::string FUN_004e4c70(const std::string &, const char *);
std::string FUN_004e4b40(const std::string &, const std::string &);
extern "C" signed char __stdcall FSOUND_SetPriority(int, int);
extern "C" signed char __stdcall FSOUND_SetVolume(int, int);
extern "C" signed char __stdcall FSOUND_SetPan(int, int);
extern "C" signed char __stdcall FSOUND_3D_SetAttributes(int, const float *, const float *);
extern "C" signed char __stdcall FSOUND_StopSound(int);
extern "C" signed char __stdcall FSOUND_IsPlaying(int);
extern "C" int __stdcall FSOUND_Stream_Play(int, void *);
extern "C" signed char __stdcall FSOUND_Stream_SetEndCallback(void *, void *, int);
extern "C" void *__stdcall FSOUND_Stream_OpenFile(const char *, unsigned int, int);
extern "C" signed char __stdcall FSOUND_Stream_Close(void *);
extern "C" signed char __stdcall FSOUND_Stream_Stop(void *);
extern "C" int __stdcall FSOUND_PlaySound(int, void *);
extern "C" void __stdcall FSOUND_Close();

#endif
