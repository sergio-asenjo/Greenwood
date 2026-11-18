// RHSequenceElement — declarations for RHSequenceElement.cpp (decompiled TU).
//
// BINDING (0x005852c0): RHSequenceElement::SerializeStaticStuff(SBFile&). See
// src/RHSequenceElement.cpp for the evidence chain.
//
// SerializeStaticStuff does not receive a this pointer.

#include "SB.h"

class RHElement;
class RHOrder;
class RHSequence;

class RHSequenceElement
{
public:
    RHSequenceElement();
    ~RHSequenceElement();
    virtual void Dummy1();
    virtual void Dummy2();
    virtual bool Serialize(SBFile &file, bool pointers);
    bool FUN_00584ef0(SBFile &file, bool pointers);
    int Unk00587160(int argument);
    static bool SerializeStaticStuff(SBFile &file);
    static void Emit(SBFile &file);

    char m_04[4];
    int m_08;
    char m_0c;
    char m_0d[3];
    int m_10;
    unsigned short m_14;
    char m_16[2];
    char m_18[0x24];
    int m_3c;
    int m_40;
    int m_44;
    RHElement *m_48;
    RHSequenceElement *m_4c;
    RHSequenceElement *m_50;
    RHSequence *m_54;
    int m_58;
    int m_5c;
    char m_60;
    char m_61[3];
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

// The 4-byte global accessed by SerializeStaticStuff (original 0x006b74d8).
// The // GLOBAL: marker sits on its definition in RHSequenceElement.cpp.
extern int g_unk0x6b74d8;
