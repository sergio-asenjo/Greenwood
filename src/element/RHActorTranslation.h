#ifndef RHACTORTRANSLATION_H
#define RHACTORTRANSLATION_H

#include <new>

template <class T>
inline T &RHActorField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

// SIZE 0x3c
class RHOrder
{
public:
    RHOrder();
    virtual ~RHOrder(); // vtable+0x00
    void FUN_0054e730();
    char m_04[0x20]; // 0x04
    int m_24; // 0x24
    unsigned char m_28; // 0x28
    unsigned char m_29; // 0x29
    unsigned char m_2a; // 0x2a
    unsigned char m_2b; // 0x2b
    unsigned char m_2c; // 0x2c
    unsigned char m_2d; // 0x2d
    unsigned char m_2e; // 0x2e
    unsigned char m_2f; // 0x2f
    void *m_30; // 0x30
    unsigned m_34; // 0x34
    void *m_38; // 0x38
};

#include "RHActorTranslationSequenceCalls.h"

#endif
