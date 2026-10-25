#include "SBNullstr.h"
#include "RHSound.h"

namespace std
{
template <> void _Construct(pair<const unsigned long, string> *output, const pair<const unsigned long, string> &value)
{
    new ((void *)output) pair<const unsigned long, string>(value);
}
}
#include <windows.h>

// GLOBAL: GAME 0x00677000
LONG (__stdcall *g_rhsoundRegSetValueExA)(HKEY, LPCSTR, DWORD, DWORD, const BYTE *, DWORD) = 0;
// GLOBAL: GAME 0x00677004
LONG (__stdcall *g_rhsoundRegOpenKeyExA)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY) = 0;
// GLOBAL: GAME 0x00677008
LONG (__stdcall *g_rhsoundRegCloseKey)(HKEY) = 0;
// GLOBAL: GAME 0x0067700c
LONG (__stdcall *g_rhsoundRegCreateKeyExA)(HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD) = 0;
// GLOBAL: GAME 0x00677010
LONG (__stdcall *g_rhsoundRegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD) = 0;

// GLOBAL: GAME 0x006c0685
char g_unk0x006c0685 = 0;
// GLOBAL: GAME 0x006c1080
unsigned long g_unk0x006c1080 = 0;
// GLOBAL: GAME 0x006c1078
RHSoundQueue g_unk0x006c1078;
// GLOBAL: GAME 0x006c0610
std::string g_unk0x006c0610;



RHSoundSource *RHSoundSourceManager::FUN_005b4e00(unsigned short) { return 0; }

// LIBRARY: GAME 0x005e39d0
extern "C" void __stdcall FSOUND_Close() {}

// FUNCTION: GAME 0x005a5f60
RHSoundPendingData::RHSoundPendingData(const RHSoundSettings &settings) : m_00(settings)
{
    m_18 = -2;
    m_1c = 0;
    m_20 = 0;
}

int RHSoundChannels::FUN_0045a490() { return Size(); }

// FUNCTION: GAME 0x005b2410
RHUnk005b2410::RHUnk005b2410(float first, float second, float third, float fourth) : m_00(first), m_04(second), m_08(third), m_0c(fourth) {}

// LIBRARY: GAME 0x00643030
extern "C" double _CIpow() { return 0; }

// LIBRARY: GAME 0x005e39e8
extern "C" signed char __stdcall FSOUND_GetDriverCaps(int, unsigned int *) { return 0; }
// LIBRARY: GAME 0x005e39dc
extern "C" const char *__stdcall FSOUND_GetDriverName(int) { return 0; }
// LIBRARY: GAME 0x005e39e2
extern "C" unsigned int __stdcall FSOUND_GetNumDrivers() { return 0; }
// LIBRARY: GAME 0x005e39ee
extern "C" unsigned int __stdcall FSOUND_GetNumHardwareChannels() { return 0; }
// LIBRARY: GAME 0x005e39f4
extern "C" int __stdcall FSOUND_GetMaxChannels() { return 0; }
// LIBRARY: GAME 0x005e39fa
extern "C" void __stdcall FSOUND_3D_Listener_SetRolloffFactor(float) {}
// LIBRARY: GAME 0x005e3a00
extern "C" void __stdcall FSOUND_3D_Listener_SetDistanceFactor(float) {}
// LIBRARY: GAME 0x005e3a06
extern "C" signed char __stdcall FSOUND_Init(int, int, unsigned int) { return 0; }
// LIBRARY: GAME 0x005e3a0c
extern "C" signed char __stdcall FSOUND_SetBufferSize(int) { return 0; }
// LIBRARY: GAME 0x005e3a12
extern "C" signed char __stdcall FSOUND_SetOutput(int) { return 0; }
// LIBRARY: GAME 0x005e3a18
extern "C" signed char __stdcall FSOUND_SetMaxHardwareChannels(int) { return 0; }
// LIBRARY: GAME 0x005e3a1e
extern "C" signed char __stdcall FSOUND_SetMinHardwareChannels(int) { return 0; }
// LIBRARY: GAME 0x005e3a24
extern "C" signed char __stdcall FSOUND_SetMixer(int) { return 0; }
// LIBRARY: GAME 0x005e3a2a
extern "C" signed char __stdcall FSOUND_SetDriver(int) { return 0; }
// LIBRARY: GAME 0x005e3a30
extern "C" signed char __stdcall FSOUND_SetHWND(void *) { return 0; }
// LIBRARY: GAME 0x005e3a3c
extern "C" signed char __stdcall FSOUND_SetPaused(int, signed char) { return 0; }
// LIBRARY: GAME 0x005e3a36
extern "C" void *__stdcall FSOUND_GetOutputHandle() { return 0; }
// LIBRARY: GAME 0x005e3aba
extern "C" signed char __stdcall FSOUND_GetCurrentLevels(int, float *, float *) { return 0; }
// LIBRARY: GAME 0x005e3a42
extern "C" signed char __stdcall FSOUND_SetCurrentPosition(int, unsigned int) { return 0; }
// LIBRARY: GAME 0x005e3a48
extern "C" int __stdcall FSOUND_PlaySoundEx(int, void *, void *, signed char) { return 0; }
// LIBRARY: GAME 0x005e3a66
extern "C" float __stdcall FSOUND_GetVersion() { return 0; }
// LIBRARY: GAME 0x005e3a6c
extern "C" unsigned int __stdcall FSOUND_Stream_GetTime(void *) { return 0; }
// LIBRARY: GAME 0x005e3a90
extern "C" signed char __stdcall FSOUND_Stream_SetTime(void *, unsigned int) { return 0; }
// LIBRARY: GAME 0x005e3a96
extern "C" unsigned int __stdcall FSOUND_Stream_GetLengthMs(void *) { return 0; }

// LIBRARY: GAME 0x005e39d6
extern "C" signed char __stdcall FSOUND_IsPlaying(int) { return 0; }
// LIBRARY: GAME 0x005e3a4e
extern "C" signed char __stdcall FSOUND_SetPriority(int, int) { return 0; }
// LIBRARY: GAME 0x005e3a54
extern "C" signed char __stdcall FSOUND_SetVolume(int, int) { return 0; }
// LIBRARY: GAME 0x005e3a5a
extern "C" signed char __stdcall FSOUND_SetPan(int, int) { return 0; }
// LIBRARY: GAME 0x005e3a60
extern "C" signed char __stdcall FSOUND_3D_SetAttributes(int, const float *, const float *) { return 0; }
// LIBRARY: GAME 0x005e3a78
extern "C" void __stdcall FSOUND_3D_Listener_SetAttributes(const float *, const float *, float, float, float, float, float, float) {}
// LIBRARY: GAME 0x005e3a72
extern "C" signed char __stdcall FSOUND_StopSound(int) { return 0; }
// LIBRARY: GAME 0x005e3a7e
extern "C" int __stdcall FSOUND_Stream_Play(int, void *) { return 0; }
// LIBRARY: GAME 0x005e3a84
extern "C" signed char __stdcall FSOUND_Stream_SetEndCallback(void *, void *, int) { return 0; }
// LIBRARY: GAME 0x005e3a8a
extern "C" void *__stdcall FSOUND_Stream_OpenFile(const char *, unsigned int, int) { return 0; }
// LIBRARY: GAME 0x005e3a9c
extern "C" signed char __stdcall FSOUND_Stream_Close(void *) { return 0; }
// LIBRARY: GAME 0x005e3aa2
extern "C" signed char __stdcall FSOUND_Stream_Stop(void *) { return 0; }
// LIBRARY: GAME 0x005e3aa8
extern "C" int __stdcall FSOUND_PlaySound(int, void *) { return 0; }
// LIBRARY: GAME 0x005e3ab4
extern "C" void __stdcall FSOUND_3D_Update() {}
// GLOBAL: GAME 0x006c10b4
RHSoundFileTree::Node *g_unk0x006c10b4 = 0;
