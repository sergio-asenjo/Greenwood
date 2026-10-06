// RHElementObject — declarations shared by RHElementObject.cpp (decompiled TU)
// and RHElementObject_stubs.cpp (external-symbol stubs).
//
// BINDING (0x004b2190): RHElementObject::Serialize(SBFile&). See
// src/RHElementObject.cpp for the evidence chain.
//
// Member offsets are derived from the target instructions of
// RHElementObject::Serialize (0x004b2190) and its neighbour
// RHElementObject::Create (0x004b2010, Mac name from
// symbols/mac-RH.txt). Only the offsets the matched function touches are laid
// out; every other byte is opaque padding. The base RHElement is 0xa8 bytes
// (its own vptr + untouched fields), so RHElementObject's members start there.

#include "SB.h"

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);

private:
    char m_unkBase[0xa4]; // [0x04, 0xa8): RHElement-owned, not touched here
};

// Nested serialisable sub-object stored at RHElementObject+0xbc. Its
// Serialize is the target 0x00521210; identity unproven, so the type keeps a
// neutral name (see 05-naming.md).
class RHUnk004b2190Member
{
public:
    bool Serialize(SBFile &file);

private:
    char m_unk[0x40]; // [0x00, 0x40): opaque; keeps the following member at +0xfc
};

class RHElementObject : public RHElement
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    int m_a8;                     // [0xa8]
    char m_ac;                    // [0xac]
    char m_ad;                    // [0xad]
    short m_ae;                   // [0xae]
    int m_b0;                     // [0xb0]
    int m_b4;                     // [0xb4]
    int m_b8;                     // [0xb8]
    RHUnk004b2190Member m_member; // [0xbc]
    char m_fc;                    // [0xfc]
    char m_fd;                    // [0xfd]
    short m_fe;                   // [0xfe]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Free-function
// form is a placeholder calling convention — the target ignores its incoming
// ecx and takes (SBFile&, const char*); see the binding notes.
void RHSerializeName(SBFile &file, const char *name);
