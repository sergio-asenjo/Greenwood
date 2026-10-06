#include "RHSoundCacheEntry.h"

// GLOBAL: GAME 0x006773d8
// std::basic_string<char,std::char_traits<char>,std::allocator<char> >::npos
template class std::basic_string<char>;

// GLOBAL: GAME 0x006c0600
std::string g_unk0x006c0600;

// LIBRARY: GAME 0x005e3aae
extern "C" unsigned int __stdcall FSOUND_Sample_GetLength(void *) { return 0; }
// LIBRARY: GAME 0x005e3ac0
extern "C" signed char __stdcall FSOUND_Sample_GetDefaults(void *, int *, int *, int *, int *) { return 0; }
// LIBRARY: GAME 0x005e3ac6
extern "C" unsigned int __stdcall FSOUND_Sample_GetMode(void *) { return 0; }
// LIBRARY: GAME 0x005e3acc
extern "C" void __stdcall FSOUND_Sample_Free(void *) {}
// LIBRARY: GAME 0x005e3ad2
extern "C" signed char __stdcall FSOUND_Sample_SetMinMaxDistance(void *, float, float) { return 0; }
// LIBRARY: GAME 0x005e3ad8
extern "C" void *__stdcall FSOUND_Sample_Load(int, const char *, unsigned int, int) { return 0; }

void FUN_005f5a80(std::string &, bool) {}
