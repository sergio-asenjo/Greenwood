#ifndef RHMALIGNITYARRAY_H
#define RHMALIGNITYARRAY_H

// SIZE 0x0c
struct RHMalignityArray
{
    int m_grow; // +0x00
    void **m_first; // +0x04
    void **m_last; // +0x08
    unsigned short size() { return m_first ? m_last - m_first : 0; }
};

#endif
