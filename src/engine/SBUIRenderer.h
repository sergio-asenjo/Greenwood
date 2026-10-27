#ifndef SBUIRENDERER_H
#define SBUIRENDERER_H

#include "Decomp.h"

class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class RHUnk005fc3b0;

class SBUIUnk006006f0
{
public:
    bool FUN_006006f0(long, RHUnk005fc3b0 &);
};

class SBUIListboxUnk0061e890;

#include "SBUIUnk005fd4a0.h"

// SIZE 0x3c
class SBUIUnk0060d530
{
public:
    undefined m_bytes[0x3c]; // 0x00
    unsigned int FUN_0060d500(unsigned int);
    void FUN_0060d520();
    bool FUN_0060d550(long);
    void *FUN_0060d690();
};

// SIZE 0x4c
class SBUIUnk0060da20
{
public:
    undefined m_bytes[0x4c]; // 0x00
    bool FUN_0060da20(unsigned int id);
};

// SIZE 0x50
class SBUIUnk0060dae0
{
public:
    undefined m_bytes[0x50]; // 0x00
    bool FUN_0060dae0(unsigned int id);
    unsigned int FUN_0060db80(unsigned int);
};

// SIZE 0x7c
class SBUIUnk0060dd00
{
public:
    undefined m_bytes[0x7c]; // 0x00
    int FUN_0060dc20(unsigned int);
    int FUN_0060dcd0();
    void *FUN_0060dd00();
    int FUN_0060dda0(SBUIListboxUnk0061e890 *, bool);
    bool FUN_0060e0d0(void *, void *, void *, void *);
};

#endif
