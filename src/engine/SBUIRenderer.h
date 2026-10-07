#ifndef SBUIRENDERER_H
#define SBUIRENDERER_H

class SBUIListboxUnk0061e890;

class SBUIUnk005fd4a0
{
public:
    void FUN_005fd4a0(long);
};

class SBUIUnk0060d530
{
public:
    char m_bytes[0x3c];
    unsigned int FUN_0060d500(unsigned int);
    void FUN_0060d520();
    void FUN_0060d530(unsigned int);
    void *FUN_0060d690();
};

class SBUIUnk0060da20
{
public:
    char m_bytes[0x4c];
    bool FUN_0060da20(unsigned int id);
};

class SBUIUnk0060dae0
{
public:
    char m_bytes[0x50];
    bool FUN_0060dae0(unsigned int id);
    unsigned int FUN_0060db80(unsigned int);
};

class SBUIUnk0060dd00
{
public:
    char m_bytes[0x7c];
    int FUN_0060dc20(unsigned int);
    int FUN_0060dcd0();
    void *FUN_0060dd00();
    int FUN_0060dda0(SBUIListboxUnk0061e890 *, bool);
    bool FUN_0060e0d0(void *, void *, void *, void *);
};

#endif
