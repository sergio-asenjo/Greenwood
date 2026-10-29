// Stub definitions for the external symbols RHTitbits.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHTitbits::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName and the
// g_pEngine global are already defined once, in RHSword_stubs.cpp /
// RHElementObject_stubs.cpp / RHMenuDialogue_stubs.cpp; this TU only declares
// them (include/SB.h, include/RHTitbits.h).

#include "SBNullstr.h"
#include "RHTitbits.h"

// TEMPLATE: GAME 0x00613e90 FOLDED
// ??0RHUnk00613e90@@QAE@XZ
RHUnk00613e90::RHUnk00613e90() {}


// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?Clear@RHTitbitList@@QAEPAXPAXPAURHTitbitNode@@1@Z
void *RHTitbitList::Clear(void *out, RHTitbitNode *first, RHTitbitNode *last)
{
    RHTitbitNode *node = first;
    while (node != last)
    {
        RHTitbitNode *erased = node;
        node = node->m_next;
        erased->m_prev->m_next = erased->m_next;
        erased->m_next->m_prev = erased->m_prev;
        operator delete(erased);
        --m_count;
    }
    *(RHTitbitNode **)out = node;
    return out;
}
