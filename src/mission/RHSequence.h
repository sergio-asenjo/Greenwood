// RHSequence — declarations for RHSequence.cpp (decompiled TU).
//
// BINDING (0x005843c0): RHSequence::Serialize(SBFile&, bool) — the Mac oracle
// names the only other serializer in this TU (symbols/mac-functions-by-file.tsv:
// 0x001a88b0 Serialize); the Windows-side signals are the "RHSequence" tag
// (0x006b7484), the `__FILE__` 0x006b7460, the 1210/… assert line numbers and the
// element-list walk at this+0x08.
// BINDING (0x00584980): RHSequence::SerializeStaticStuff(SBFile&). See
// src/RHSequence.cpp for both evidence chains.
//
// Member layout derived from the target instructions of RHSequence::Serialize
// (0x005843c0):
//   - +0x04: 4-byte serialised field (Access size 4);
//   - +0x08: an SBList<RHSequenceElement*> — sentinel node pointer at +0x0c,
//     count at +0x10, cursor at +0x14, validity byte at +0x18, index at +0x1c
//     (the same SBList shape RHGroundMark uses: head at list+0x04);
//   - +0x2c/+0x2e/+0x30/+0x32: 2-byte serialised fields;
//   - +0x34: 4-byte serialised field.
//
// The Windows codegen calls SerializeStaticStuff WITHOUT a `this` (the body
// never uses ecx as this), so on this build it is a static member.

// Reused verbatim from RHOrder.h (which pulls in SB.h) so the singleton type of
// g_unk0x6c1040 is identical across TUs (the global's C++ symbol is
// type-mangled). This TU only declares `extern RHUnk6c1040 *g_unk0x6c1040` and
// reinterprets +0x190.
#include "SBGeoPoint2D.h"
#include "RHOrder.h"
#include "RHSectorActorList.h"
#include <list>

class RHSequenceElement;
class RHSequence;

// Minimal MSVC6 _List_iterator-shaped value: constructs from a node pointer,
// returned by value through a hidden pointer (Hard rule 22).
class RHSeqIter
{
public:
    void *m_p;

    RHSeqIter(void *p) : m_p(p) {}
};

// The sequence-element base (target size 0x64, ctor 0x00584cf0). Only the vtable
// slot used by the Serialize vcall ([vtable+0x8]) is modelled; the rest stays an
// opaque run (fields at +0x4c / +0x54 are reached by explicit offsets in
// RHSequence.cpp). The virtual destructor puts Serialize at slot +0x8.
class RHSequenceElement
{
public:
    RHSequenceElement();
    ~RHSequenceElement();
    virtual void Dummy1();
    virtual void Dummy2();
    virtual bool Serialize(SBFile &file, bool bArg);

    char m_pad[0x60];
};

// SBList node: {next, prev, data}. The read-path insert allocates 0xc bytes.
class RHUnk586050 : public RHSequenceElement
{
public:
    RHUnk586050();

    char m_pad1[0x7c - 0x64];
};

#include "RHSequenceGenericConstruction.h"

class RHUnk585e70 : public RHSequenceElement
{
public:
    RHUnk585e70();

    char m_pad1[0x68 - 0x64];
};

#include "RHSequenceMovementConstruction.h"

// std::list<RHSequence*>-shaped object held by g_unk0x6c1040 at +0x190. The
// inlined std::list insert is the out-of-line target 0x00424410 (same callee as
// RHOrder::Serialize; MSVC6 std::list layout: _Head at +0x04, _Size at +0x08,
// an extra flag at +0x10).
class RHUnkListSeq
{
public:
    RHSeqIter insert(RHSeqIter pos, RHSequence *const &value); // target 0x00424410

    RHSeqIter end() { return RHSeqIter(m_4); }

    char m_pad0[4];
    void *m_4;     // [0x4] end/sentinel node
    int m_8;       // [0x8] count
    char m_pad1[4];
    char m_flag10; // [0x10]
};

// The +0x190 view of the g_unk0x6c1040 singleton (the RHOrder.h view stops at
// +0x148; this is the same object, reinterpreted).
struct RHUnk6c1040Seq
{
    char m_pad0[0x190];
    RHUnkListSeq m_190; // [0x190]
};

inline RHUnkListSeq &RHSequenceGlobalList()
{
    return ((RHUnk6c1040Seq *)(void *)g_unk0x6c1040)->m_190;
}

// The five element types the load path allocates (sizes from the operator new
// operands: 0x64 / 0x7c / 0x74 / 0x68 / 0x9c). Method identity is NOT proven, so
// each stays provisional RHUnk*; only the size and the virtual Serialize matter.
#include "RHSequenceConstructionCalls.h"

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

// The 4-byte global accessed by SerializeStaticStuff (original 0x006b7480).
// The // GLOBAL: marker sits on its definition in RHSequence.cpp.
extern int g_unk0x6b7480;
