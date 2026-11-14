#ifndef VMNATIVESTACK_H
#define VMNATIVESTACK_H

#include <new>
#include <string.h>

struct VMNativeStack
{
    VMNativeStack() : m_data(new char[48]), m_size(0), m_result(0) {}
    ~VMNativeStack()
    {
        if (m_data)
            operator delete(m_data);
    }
    void Push(const void *value, int size)
    {
        memcpy(m_data + m_size, value, size);
        m_size += size;
    }
    char *m_data;
    int m_size;
    int m_result;
};

typedef int (__cdecl *VMUnk00635210Handler)(VMNativeStack *);

extern VMUnk00635210Handler *g_unk0x006c1944;
extern int g_unk0x006c1948;

#endif
