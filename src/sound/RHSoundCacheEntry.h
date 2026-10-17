#ifndef RHSOUNDCACHEENTRY_H
#define RHSOUNDCACHEENTRY_H

#include <string>

class RHSoundCacheEntry
{
public:
    bool UpdateSampleSize();
    bool LoadSample(bool spatial, unsigned short stamp);
    void Emit(bool spatial, unsigned short stamp);

    std::string m_name; // [0x00]
    void *m_sample; // [0x10]
    unsigned int m_size; // [0x14]
    unsigned int m_duration; // [0x18]
    bool m_loop; // [0x1c]
    char m_1d[3];
    unsigned short m_stamp; // [0x20]
};

extern "C" unsigned int __stdcall FSOUND_Sample_GetMode(void *);
extern "C" unsigned int __stdcall FSOUND_Sample_GetLength(void *);
extern "C" signed char __stdcall FSOUND_Sample_GetDefaults(void *, int *, int *, int *, int *);
extern "C" void __stdcall FSOUND_Sample_Free(void *);
extern "C" signed char __stdcall FSOUND_Sample_SetMinMaxDistance(void *, float, float);
extern "C" void *__stdcall FSOUND_Sample_Load(int, const char *, unsigned int, int);
int FUN_005f5a80(std::string &, bool);
extern std::string g_unk0x006c0600;

#endif
