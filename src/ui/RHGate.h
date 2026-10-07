#ifndef RHGATE_H
#define RHGATE_H

#include "SB.h"

class RHGate
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[0x8c];
    char m_8c;
    char m_8d;
    char m_8e;
    char m_8f;
    char m_pad90[0x24];
    char m_b4;
    char m_padb5;
    short m_b6;
    short m_b8;
};

void RHSerializeName(SBFile &file, const char *name);

#endif
