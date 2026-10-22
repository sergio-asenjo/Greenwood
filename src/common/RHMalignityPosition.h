#ifndef RHMALIGNITYPOSITION_H
#define RHMALIGNITYPOSITION_H

// SIZE 0x10
struct RHMalignityPosition
{
    float x; // 0x00
    float y; // 0x04
    void *area; // 0x08
    unsigned short layer; // 0x0c
};

#endif
