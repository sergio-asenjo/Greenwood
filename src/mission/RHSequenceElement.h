// RHSequenceElement — declarations for RHSequenceElement.cpp (decompiled TU).
//
// BINDING (0x005852c0): RHSequenceElement::SerializeStaticStuff(SBFile&). See
// src/RHSequenceElement.cpp for the evidence chain.
//
// The Windows codegen calls this WITHOUT a `this` (the body never uses ecx as
// this), so on this build it is a static member.

#include "SB.h"

class RHSequenceElement
{
public:
    RHSequenceElement();
    static bool SerializeStaticStuff(SBFile &file);
    bool FUN_00584ef0(SBFile &file, bool pointers);

    static void Emit(SBFile &file);
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

// The 4-byte global accessed by SerializeStaticStuff (original 0x006b74d8).
// The // GLOBAL: marker sits on its definition in RHSequenceElement.cpp.
extern int g_unk0x6b74d8;
