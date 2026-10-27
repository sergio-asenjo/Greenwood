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
            int count = m_size;
            if (size < count)
                count = size;
            memcpy(buffer, m_memory, count);
        }
        if (m_memory != 0)
            operator delete(m_memory);
        m_memory = buffer;
        m_size = size;
        return size;
    }
    m_memory = 0;
    m_size = 0;
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
    return (int *)(m_memory + offset);
}

// FUNCTION: GAME 0x0063a1f0
void VMUnk0063a140::FUN_0063a1f0(int offset, unsigned char *source, int size)
{
    memcpy(m_memory + offset, source, size);
}

void EmitVMArray(VMUnk0063a140 *array)
{
    array->FUN_0063a1f0(0, 0, 0);
    array->FUN_0063a1e0(0);
}
