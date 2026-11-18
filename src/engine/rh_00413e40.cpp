#include "SBNullstr.h"
#include "RHEngine.h"

// STUB: GAME 0x00413e40
void FUN_00413e40()
{
    char *engine = (char *)g_pEngine;
    unsigned count = 0;
    if (*(int *)(engine + 0x495c) != 0)
        count = (*(int *)(engine + 0x4960) - *(int *)(engine + 0x495c)) >> 2;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        char *actor = (*(char ***)(engine + 0x495c))[index];
        char *vbase = actor + 0x49c + (*(int **)(actor + 0x49c))[1];
        (*(void (__fastcall **)(void *))(*(char **)vbase + 0x14))(vbase);
    }
}
