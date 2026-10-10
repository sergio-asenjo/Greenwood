#ifndef SCQUAD_H
#define SCQUAD_H

#include <stdio.h>

class RHUnk0063a1d0
{
public:
    unsigned FUN_0063a1d0();
};

struct SCQuadUnkSymbol
{
    char m_pad00[0x38];
    unsigned char m_38;
    char m_pad39[3];
    int m_3c;
    unsigned char m_40;
};

class SCQuadArg
{
public:
    unsigned char m_00;
    char m_pad01[3];
    float m_04;
    signed char m_08;

    unsigned char GetType();
    float GetFloat();
    signed char GetReference();
    int Serialize(FILE *, bool, bool);
};

struct VMQuad
{
    unsigned char m_00;
    char m_pad01[3];
    unsigned m_04;
    union { unsigned m_08; float m_float08; };
};

class SCQuad
{
public:
    int m_00;
    SCQuadArg m_04;
    SCQuadArg m_10;
    SCQuadArg m_1c;

    int Serialize(FILE *, bool, bool);
    void InitializeVMQuadWithSCQuad(SCQuad &, VMQuad &);
    void InitializeVMQuadSymbolWithSCQuadArg(unsigned short &, SCQuadArg &);
};

int SCSerializeUnk00642a2f(const char *, ...);
int SCQuadUnk00644112(FILE *, const char *, ...);
const char *SCQuadUnk0063c760(int);

#endif
