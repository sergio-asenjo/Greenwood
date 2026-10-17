#include "SBNullstr.h"
#include "VMArray.h"
#include "SCQuad.h"
#include <new>
#include <string.h>

// FUNCTION: GAME 0x0063a140
int VMUnk0063a140::FUN_0063a140(int size, bool preserve)
{
    if (size > 0) {
        unsigned char *buffer = new unsigned char[size];
        memset(buffer, 0, size);
        if (preserve) {
            int count = *(int *)(m_pad0 + 4);
            if (size < count)
                count = size;
            memcpy(buffer, *(unsigned char **)m_pad0, count);
        }
        if (*(unsigned char **)m_pad0 != 0)
            operator delete(*(unsigned char **)m_pad0);
        *(unsigned char **)m_pad0 = buffer;
        *(int *)(m_pad0 + 4) = size;
        return size;
    }
    *(unsigned char **)m_pad0 = 0;
    *(int *)(m_pad0 + 4) = 0;
    return size;
}

// FUNCTION: GAME 0x0063a1d0
unsigned RHUnk0063a1d0::FUN_0063a1d0()
{
    return *(unsigned *)((char *)this + 4);
}

// FUNCTION: GAME 0x0063a1e0
int *VMUnk0063a140::FUN_0063a1e0(int offset)
{
    return (int *)(*(unsigned char **)m_pad0 + offset);
}

// FUNCTION: GAME 0x0063a1f0
void VMUnk0063a140::FUN_0063a1f0(int offset, unsigned char *source, int size)
{
    memcpy(*(unsigned char **)m_pad0 + offset, source, size);
}

void EmitVMArray(VMUnk0063a140 *array)
{
    array->FUN_0063a1f0(0, 0, 0);
    array->FUN_0063a1e0(0);
}
