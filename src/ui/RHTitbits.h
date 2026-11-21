// RHTitbits — declarations shared by RHTitbits.cpp (decompiled TU) and
// RHTitbits_stubs.cpp (external-symbol stubs).
//
// BINDING (0x005c3a60): RHTitbits::Serialize(SBFile&). See
// src/RHTitbits.cpp for the evidence chain.
//
// Member layout derived from the target instructions of
// RHTitbits::Serialize (0x005c3a60):
//   - +0x20: an intrusive doubly-linked list of 0x38-byte nodes (next/prev at
//     +0/+4, 48-byte payload at +8); the list object keeps head/count/cursor/
//     cache-flag/cached-index at +0x04/+0x08/+0x0c/+0x10/+0x14;
//   - +0xa4 / +0xa8: int/float reset only on load;
//   - +0xac: the first serialised int.
//
// The 48-byte payload element (RHTitbit) field offsets are taken verbatim from
// the Access() calls in the target.

#ifndef RHTITBITS_H
#define RHTITBITS_H
#include "RHTitbitsCore.h"

#include "SB.h"
#include <string>

// Target 0x004593f0-style engine helper: serialises other engine objects.
// Class identity of the engine is RHEngine (thiscall receiver read from the
// global 0x006c0a88, the same singleton RHMenuDialogue::GetDialogue uses).
class RHEngine;
class RHElement;
class RHElementActorPC;

extern RHEngine *g_pEngine;

class SBGeoBoundingBox2D;
class SBGeoPoint2D;

// Target 0x005df510: __thiscall(SBFile&) serialising a 12-byte triple of ints.
#include "RHUnk005df510.h"

// Target 0x00613e90: trivial ctor (`mov eax,ecx; ret`); stored as a 12-byte
// sub-object at RHTitbit+0x18.
#include "RHUnk00613e90.h"

struct RHTitbitNode
{
    RHTitbitNode *m_next; // [0x00]
    RHTitbitNode *m_prev; // [0x04]
    RHTitbit m_data;      // [0x08]
};

struct RHTitbitIterator
{
    RHTitbitList::Node *node;
    RHTitbitIterator(RHTitbitList::Node *value) : node(value) {}
};

inline RHTitbit &RHTitbitList::Item(int index)
{
    At(index);
    return *m_current;
}

inline void RHTitbitList::Advance(int distance)
{
    for (; distance > 0; --distance)
        ++m_current;
    for (; distance < 0; ++distance)
        --m_current;
}

inline void RHTitbitList::Seek(int i)
{
    const int count = size();
    if (m_dirty)
    {
        if (i <= (count + 1) / 2)
        {
            m_current = begin();
            Advance(i);
        }
        else
        {
            m_current = end();
            Advance(i - count);
        }
        m_dirty = false;
        m_index = i;
    }
    else
    {
        if (i == m_index)
            return;
        if (i < m_index)
        {
            if (i >= (m_index + 1) / 2)
            {
                Advance(i - m_index);
            }
            else
            {
                m_current = begin();
                Advance(i);
            }
        }
        else
        {
            if (i >= (m_index + count) / 2)
            {
                m_current = end();
                Advance(i - count);
            }
            else
            {
                Advance(i - m_index);
            }
        }
        m_index = i;
    }
}

void RHSerializeName(SBFile &file, const char *name);

#endif
