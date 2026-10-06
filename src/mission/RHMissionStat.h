// RHMissionStat — declarations shared by RHMissionStat.cpp (decompiled TU)
// and RHMissionStat_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0054e250): RHMissionStat::Serialize(SBFile&). See
// src/RHMissionStat.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHMissionStat::Serialize (0x0054e250): nine 32-bit fields at +0x04..+0x24,
// then an opaque list object at +0x28 whose element serializer is the free
// helper at 0x004593f0.

#include "SB.h"

// The list object at RHMissionStat+0x28. Only the layout the list serializer
// (0x004593f0) touches is modelled: begin/end pointers at +0x04/+0x08. Its
// identity is unproven, so it keeps a neutral name.
class RHUnk0054e250List
{
public:
    char m_pad0[4];
    void *m_begin; // [this+0x04]
    void *m_end;   // [this+0x08]
};

class RHMissionStat
{
public:
    // Virtual so the object layout carries the vptr at +0x00 the target
    // instructions imply (the first serialised int is at +0x04).
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    int m_f04; // [0x04]
    int m_f08; // [0x08]
    int m_f0c; // [0x0c]
    int m_f10; // [0x10]
    int m_f14; // [0x14]
    int m_f18; // [0x18]
    int m_f1c; // [0x1c]
    int m_f20; // [0x20]
    int m_f24; // [0x24]

    RHUnk0054e250List m_list; // [0x28]
};

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h; no TU includes
// both headers, so the declaration does not collide.
void RHSerializeName(SBFile &file, const char *name);

// Target 0x004593f0: serialises a container of elements, invoking the
// per-element serializer passed as the third argument.
bool RHUnk004593f0SerializeList(SBFile &file, RHUnk0054e250List &list, void *elementFn);
