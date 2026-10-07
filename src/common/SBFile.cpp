#include "SBFile.h"
#include "RHSaveGame.h"
#include "SCSerialize.h"

#define SBFile_stream (*(FILE **)((char *)this))
#define SBFile_position (*(int *)((char *)this + 0xc))
#define SBFile_error (*(int *)((char *)this + 0x14))
#define SBFile_embedded (*(char *)((char *)this + 0x28))
#define SBFile_start (*(int *)((char *)this + 0x2c))

// FUNCTION: GAME 0x005f5280
int SBFileUnk005f5280::FUN_005f5280(int)
{
    return -1;
}

// deferred: unannotated pending reccmp #534.
void RHUnk005f4fc0::FUN_005f5290()
{
    if (SBFile_embedded != 1) {
        SCSerializeUnk00643c56(SBFile_stream);
        SBFile_stream = 0;
    }
}

// Unannotated: coupled callers; embedded-position scheduling differs.
int SBFile::Access(void *buffer, int size)
{
    if (SBFile_stream == 0 && SBFile_embedded == 0)
        return SBFile_error = -4;
    if (SBFile_embedded == 1) {
        int position = SBFile_start + SBFile_position;
        if (SBFileUnk00643a8f(SBFile_stream) != position)
            SBFileUnk006439d6(SBFile_stream, position, 0);
    }
    if (m_bLoading != 0) {
        if (SBFileUnk00643e0c(buffer, 1, size, SBFile_stream) != size)
            return SBFile_error = -5;
    } else {
        if (SBFileUnk00643cd3(buffer, 1, size, SBFile_stream) != size)
            return SBFile_error = -6;
    }
    SBFile_error = 0;
    SBFile_position += size;
    return 0;
}

void SBFileEmit(SBFileUnk005f5280 *file)
{
    file->FUN_005f5280(0);
}

// GLOBAL: GAME 0x006c135c
void **g_unk0x006c135c = 0;

// GLOBAL: GAME 0x006c1364
unsigned int g_unk0x006c1364 = 0;

// FUNCTION: GAME 0x005f54d0
int FUN_005f54d0()
{
    int result = 0;
    while (g_unk0x006c1364 != 0 && result == 0) {
        result = (int)*g_unk0x006c135c + 12;
        result = FUN_005f5500((void *)result);
    }
    return result;
}
