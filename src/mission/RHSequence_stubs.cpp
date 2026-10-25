// Stub definitions for the external symbols RHSequence.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHSequence::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched function
// (Hard rule 5: the element ctor/dtor must not be visible at the `new` site).
//
// SBFile::Access / SBFile::GetError / SBAssert are defined once in
// RHSword_stubs.cpp; RHSerializeName once in RHElementObject_stubs.cpp;
// operator new once (LIBRARY seed) in crt_stubs.cpp. This TU only defines the
// new targets.

#include "SBNullstr.h"
#include "RHSequence.h"

// Target 0x00584cf0 (RHSequenceElement base ctor). Parked: the body is a
// list-node ctor with the vptr written LAST, but the class must keep its
// virtuals for the Serialize vcall ([vtable+0x8]). Adding __declspec(novtable)
// to suppress the automatic top vptr store DEMOTED the counted derived ctors
// 0x005865a0 (1 -> 0.9836) and 0x00588270 (1 -> 0.9677): the attribute
// propagates to the derived classes and drops their own vptr store. Reverted.
RHSequenceElement::RHSequenceElement() {}

// Target 0x00584de0 (RHSequenceElement base dtor, out-of-line).
RHSequenceElement::~RHSequenceElement() {}

// Unused vtable fillers that keep Serialize at slot +0x8 (the target's vcall).
void RHSequenceElement::Dummy1() {}
void RHSequenceElement::Dummy2() {}

// Target 0x00584e80 / the shared vcall slot (+0x8). Never matched here.
bool RHSequenceElement::Serialize(SBFile &, bool) { return true; }

// Targets 0x00586050 / 0x005865a0 / 0x00585e70 / 0x00588270.

// Inlined SBList<RHSequenceElement*>::insert(iterator, T* const&). The node is
// 0xc bytes ({next, prev, data}); only the tail links through CopyData.
RHSeqIter RHSeqList::insert(RHSeqIter pos, RHSequenceElement *const &value)
{
    RHSeqNode *s = (RHSeqNode *)pos.m_p;
    RHSeqNode *node = (RHSeqNode *)::operator new(0xc);
    node->m_next = s;
    node->m_prev = s->m_prev;
    s->m_prev = node;
    node->m_prev->m_next = node;
    CopyData(&node->m_data, &value);
    return RHSeqIter(node);
}

// Target 0x00424410: std::list<RHSequence*>::insert (`ret 0xc`, ecx = the list).
RHSeqIter RHUnkListSeq::insert(RHSeqIter pos, RHSequence *const &value)
{
    return pos;
}
void RHUnk00582220::Slot00() {}
