#ifndef RHACTORTRANSLATION_H
#define RHACTORTRANSLATION_H

#include <new>

template <class T>
inline T &RHActorField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

class RHOrder
{
public:
    RHOrder();
    virtual ~RHOrder();
    char m_04[0x20];
    int m_24;
    unsigned char m_28;
    unsigned char m_29;
    unsigned char m_2a;
    unsigned char m_2b;
    unsigned char m_2c;
    unsigned char m_2d;
    unsigned char m_2e;
    unsigned char m_2f;
    void *m_30;
    unsigned m_34;
    void *m_38;
};

class RHActorTranslationSequenceCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c(int value, bool mode) = 0;
    void FUN_00585970(RHOrder *order);
};

#endif
