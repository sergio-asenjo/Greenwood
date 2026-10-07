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
class RHSoundSource;
struct RHSoundPendingNode;
struct RHSoundPendingData;
struct RHSoundQueueNode;

class RHSoundVirtualSlot39
{
public:
    virtual void Slot00() = 0;
    virtual void Slot01() = 0;
    virtual void Slot02() = 0;
    virtual void Slot03() = 0;
    virtual void Slot04() = 0;
    virtual void Slot05() = 0;
    virtual void Slot06() = 0;
    virtual void Slot07() = 0;
    virtual void Slot08() = 0;
    virtual void Slot09() = 0;
    virtual void Slot10() = 0;
    virtual void Slot11() = 0;
    virtual void Slot12() = 0;
    virtual void Slot13() = 0;
    virtual void Slot14() = 0;
    virtual void Slot15() = 0;
    virtual void Slot16() = 0;
    virtual void Slot17() = 0;
    virtual void Slot18() = 0;
    virtual void Slot19() = 0;
    virtual void Slot20() = 0;
    virtual void Slot21() = 0;
    virtual void Slot22() = 0;
    virtual void Slot23() = 0;
    virtual void Slot24() = 0;
    virtual void Slot25() = 0;
    virtual void Slot26() = 0;
    virtual void Slot27() = 0;
    virtual void Slot28() = 0;
    virtual void Slot29() = 0;
    virtual void Slot30() = 0;
    virtual void Slot31() = 0;
    virtual void Slot32() = 0;
    virtual void Slot33() = 0;
    virtual void Slot34() = 0;
    virtual void Slot35() = 0;
    virtual void Slot36() = 0;
    virtual void Slot37() = 0;
    virtual void Slot38() = 0;
    virtual void Slot39(unsigned short) = 0;
};

struct RHSoundQueue
{
    char m_00[4];
    RHSoundQueueNode *m_04;
    unsigned int m_08;
    RHSoundQueueNode **FUN_005aa1c0(RHSoundQueueNode **, RHSoundQueueNode *);
};

struct RHSoundSourcesView
{
    int m_00;
    RHSoundSource **m_04;
    RHSoundSource **m_08;
    char m_0c[0x14];
    int GetSize() const { return m_04 == 0 ? 0 : m_08 - m_04; }
};

class RHSoundSourceManager
{
public:
    RHSoundSource *GetSoundSource(unsigned short);
    bool Serialize(SBFile &);
    char m_00[4];
    RHSoundSourcesView m_04;
};

struct RHSoundChannelSettings
{
    float m_00;
    float m_04;
    float m_08;
    unsigned short m_0c;
    unsigned short m_0e;
    unsigned short m_10;
    unsigned short m_12;
    float m_14[3];
};

struct RHSoundGeometryView
{
    void FUN_005b33b0(RHSoundChannelSettings &settings);
    void FUN_005b3420(RHSoundChannelSettings &settings);
    unsigned short FUN_005b3500();
    unsigned short FUN_005b3490(bool);
    unsigned short FUN_005b34e0();
    bool FUN_005b2ff0(const struct RHSoundSettings &, bool, RHSoundChannelSettings &);
    char m_00[0x10];
    float m_10;
    char m_14[0xb4];
};

struct RHSoundChannel
{
    int m_00;
    void *m_04;
    RHSoundCacheEntry *m_08;
    void *m_0c;
};

struct RHSoundChannels
{
    unsigned int m_00;
    RHSoundChannel *m_04;
    RHSoundChannel *m_08;
    RHSoundChannel *m_0c;
    char m_10[4];
    bool m_14;
    char m_15[0x17];
    unsigned int Size() const { return m_04 ? m_08 - m_04 : 0; }
    void FUN_005aaa50(unsigned int, const RHSoundChannel &);
};

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
    unsigned long FUN_005a93e0(RHSoundPendingData &);
    bool FUN_005a9400(const RHSoundSettings &);
    void Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings);

    RHSoundCache m_000;
    RHSoundGeometryView m_138;
    RHSoundSourceManager *m_200;
    void *m_204;
    unsigned short m_208;
    char m_20a;
    char m_20b;
    char m_20c[4];
    char m_210;
    char m_211;
    char m_212;
    char m_213;
    char m_214;
    char m_215[3];
    unsigned int m_218;
    RHSoundChannels m_21c;
    char m_248[4];
    RHSoundPendingNode *m_24c;
    unsigned int m_250;
    void *m_254;
    char m_258[4];
    int m_25c;
    void *m_260;
    int m_264;
    void *m_268;
    int m_26c;
    void *m_270;
    int m_274;
    char m_278;
    char m_279;
    char m_27a;
    char m_27b;
    char m_27c;
    char m_27d;
    char m_27e;
    char m_27f;
    int m_280;
    unsigned short m_284;
    char m_286[2];
    unsigned long m_288;
    unsigned long m_28c;
    unsigned long m_290;
};

struct RHSoundSettings
{
    int m_00;
    char m_04[8];
    void *m_0c;
    char m_10[4];
    void *m_14;
};

struct RHSoundPendingData
{
    RHSoundSettings m_00;
    int m_18;
    unsigned long m_1c;
    unsigned long m_20;
    void FUN_0052c5a0();
};

struct RHSoundPendingNode
{
    RHSoundPendingNode *m_00;
    RHSoundPendingNode *m_04;
    RHSoundPendingData m_08;
};

struct RHSoundQueueNode
{
    RHSoundQueueNode *m_00;
    RHSoundQueueNode *m_04;
    RHSoundSettings m_08;
    RHSoundChannelSettings m_20;
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

#endif
