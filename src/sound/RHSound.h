#ifndef RHSOUND_H
#define RHSOUND_H

#include "RHSoundCacheEntry.h"
#include "RHSoundCache.h"
#include "RHSoundGeometryCalls.h"
#include <windows.h>

extern LONG (__stdcall *g_rhsoundRegSetValueExA)(HKEY, LPCSTR, DWORD, DWORD, const BYTE *, DWORD);
extern LONG (__stdcall *g_rhsoundRegOpenKeyExA)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
extern LONG (__stdcall *g_rhsoundRegCloseKey)(HKEY);
extern LONG (__stdcall *g_rhsoundRegCreateKeyExA)(HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD);
extern LONG (__stdcall *g_rhsoundRegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);

class SBFile;
class SBGeoPoint2D;

class RHUnk005aada0
{
public:
    ~RHUnk005aada0();
    void FUN_005aada0();
    SBGeoPoint2D *Begin() { return m_first; }
    SBGeoPoint2D *End() { return m_last; }
    void Destroy(SBGeoPoint2D *, SBGeoPoint2D *);
    SBGeoPoint2D *Remove(SBGeoPoint2D *, SBGeoPoint2D *);
    undefined4 m_00;
    SBGeoPoint2D *m_first;
    SBGeoPoint2D *m_last;
    SBGeoPoint2D *m_end;
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
    ~RHSoundQueue();
    undefined m_00[4]; // 0x00
    RHSoundQueueNode *m_04; // 0x04
    unsigned int m_08; // 0x08
    RHSoundQueueNode **FUN_005aa1c0(RHSoundQueueNode **, RHSoundQueueNode *);
};

#include "RHSoundSourceManagerCore.h"

#include "RHSoundCore.h"

#include "RHSoundSettings.h"

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
#include "RHSoundConfig.h"
typedef RHSoundConfig RHUnk005a9260;

// SIZE 0x10
class RHSoundFileTree
{
public:
    struct Node
    {
        Node *m_left; // 0x00
        Node *m_parent; // 0x04
        Node *m_right; // 0x08
        unsigned long m_key; // 0x0c
        std::string m_value; // 0x10
        undefined4 m_color; // 0x20
    };
    struct Iterator
    {
        Node *m_node; // 0x00
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        static Node *&Left(Node *value) { return value->m_left; }
        void FUN_005b1940();
        void FUN_005b1030();
    };
    typedef std::pair<Iterator, bool> Pair;
    struct Value
    {
        unsigned long m_key; // 0x00
        std::string m_value; // 0x04
    };
    Pair FUN_005af320(const Value &);
    Pair FUN_005b0870(const Value &);
    Iterator FUN_005b1580(Node *, Node *, const Value &);
    void Lrotate(Node *);
    void Rrotate(Node *);
    Node *&Root() { return m_head->m_parent; }
    undefined m_00[4]; // 0x00
    Node *m_head; // 0x04
    undefined m_multi; // 0x08
    undefined m_09[3]; // 0x09
    unsigned int m_size; // 0x0c
};

extern RHSoundFileTree::Node *g_unk0x006c10b4;

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
extern "C" void *__stdcall FSOUND_GetOutputHandle();
extern "C" signed char __stdcall FSOUND_GetCurrentLevels(int, float *, float *);
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
#include "zlib.h"
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
extern "C" void __stdcall FSOUND_3D_Listener_SetAttributes(const float *, const float *, float, float, float, float, float, float);
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
