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
#include "RHOrder.h"
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

class RHUnk005866a0 : public RHSequenceElement
{
public:
    RHUnk005866a0();

    char m_pad1[0x74 - 0x64];
};

class RHUnk585e70 : public RHSequenceElement
{
public:
    RHUnk585e70();

    char m_pad1[0x68 - 0x64];
};

class RHUnk00588530 : public RHSequenceElement
{
public:
    RHUnk00588530();

    char m_pad1[0x9c - 0x64];
};

// SBList node: {next, prev, data}. The read-path insert allocates 0xc bytes.
class RHSeqNode
{
public:
    RHSeqNode *m_next;
    RHSeqNode *m_prev;
    RHSequenceElement *m_data;
};

// SBList<RHSequenceElement*> at RHSequence+0x08. Layout from RHSaveGameManager /
// RHGroundMark (m_head at list+0x04, m_count at list+0x08, m_cur at list+0x0c,
// m_valid at list+0x10, m_index at list+0x14).
class RHSeqList
{
public:
    char m_pad0[4];
    RHSeqNode *m_head; // [0x04]
    int m_count;       // [0x08]
    RHSeqNode *m_cur;  // [0x0c]
    char m_valid;      // [0x10]
    char m_pad1[3];
    int m_index; // [0x14]

    void GoTo(int i); // target 0x005c8e40

    RHSeqIter end() { return RHSeqIter(m_head); }

    // Target 0x0059fb00 (out-of-line 4-byte payload copy).
    static void CopyData(RHSequenceElement **dst, RHSequenceElement *const *src);

    RHSeqIter insert(RHSeqIter pos, RHSequenceElement *const &value);
};

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
class RHSequence
{
public:
    bool Serialize(SBFile &file, bool bArg); // 0x005843c0

    static bool SerializeStaticStuff(SBFile &file);

    void Emit(SBFile &file);

    char m_pad0[4];        // [0x00] (opaque)
    int m_04;              // [0x04]
    RHSeqList m_list;      // [0x08] SBList<RHSequenceElement*>
    char m_pad20[0xc];     // [0x20, 0x2c)
    short m_2c;            // [0x2c]
    short m_2e;            // [0x2e]
    short m_30;            // [0x30]
    short m_32;            // [0x32]
    char m_34;             // [0x34]
};

// SIZE 0x14
class RHSequenceElementListStorage : public std::list<RHSequenceElement *>
{
public:
    RHSequenceElementListStorage() : m_dirty(true) {}
    ~RHSequenceElementListStorage();
    iterator m_cursor; // 0x0c
    bool m_dirty;      // 0x10
};

class RHSequenceElementList : public RHSequenceElementListStorage
{
public:
    ~RHSequenceElementList();
    void DeleteAll();
    void clear();
};

// VTABLE: GAME 0x00679cd4
// SIZE 0x3c
class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    void *FUN_00582280(unsigned int flags);
    virtual void Slot00();
    int m_04;                        // 0x04
    RHSequenceElementList m_elements; // 0x08
    char m_1c[0x10];                 // 0x1c
    short m_2c;                      // 0x2c
    short m_2e;                      // 0x2e
    short m_30;                      // 0x30
    short m_32;                      // 0x32
    char m_34;                       // 0x34
    char m_35[7];                    // 0x35
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);

// The 4-byte global accessed by SerializeStaticStuff (original 0x006b7480).
// The // GLOBAL: marker sits on its definition in RHSequence.cpp.
extern int g_unk0x6b7480;
