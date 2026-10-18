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

#include "SB.h"

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
class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;

    bool Serialize(SBFile &file);
};

// Target 0x00613e90: trivial ctor (`mov eax,ecx; ret`); stored as a 12-byte
// sub-object at RHTitbit+0x18.
#include "RHUnk00613e90.h"

// The 48-byte serialised element. Fields are named by offset only; identity is
// unproven (no oracle signal).
struct RHTitbit
{
    int m_00;      // [0x00]
    short m_04;    // [0x04]
    short m_06;    // [0x06]
    short m_08;    // [0x08]
    short m_0a;    // [0x0a]
    int m_0c;      // [0x0c]
    int m_10;      // [0x10]
    union
    {
        int m_14i;
        short m_14s;
    } m_u14;       // [0x14]
    RHUnk00613e90 m_sub; // [0x18]
    int m_24;      // [0x24]
    char m_28;     // [0x28]
    char m_29;
    char m_2a;
    char m_2b;
    int m_2c;      // [0x2c]
};

struct RHTitbitNode
{
    RHTitbitNode *m_next; // [0x00]
    RHTitbitNode *m_prev; // [0x04]
    RHTitbit m_data;      // [0x08]
};

struct RHTitbitIterator
{
    RHTitbitNode *node;
    RHTitbitIterator(RHTitbitNode *value) : node(value) {}
};

class RHTitbitList
{
public:
    int m_00;                // [0x00]
    RHTitbitNode *m_head;    // [0x04]
    int m_count;             // [0x08]
    RHTitbitNode *m_cur;     // [0x0c]
    char m_valid;            // [0x10]
    int m_index;             // [0x14]

    void At(int i); // target 0x005c8e40 (out-of-line at the write call site)

    void Advance(int distance)
    {
        for (; distance > 0; --distance)
            m_cur = m_cur->m_next;
        for (; distance < 0; ++distance)
            m_cur = m_cur->m_prev;
    }

    void Seek(int i)
    {
        if (m_valid)
        {
            if (i <= (m_count + 1) / 2)
            {
                m_cur = m_head->m_next;
                Advance(i);
            }
            else
            {
                m_cur = m_head;
                Advance(i - m_count);
            }
            m_valid = 0;
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
                    m_cur = m_head->m_next;
                    Advance(i);
                }
            }
            else
            {
                if (i >= (m_index + m_count) / 2)
                {
                    m_cur = m_head;
                    Advance(i - m_count);
                }
                else
                {
                    Advance(i - m_index);
                }
            }
            m_index = i;
        }
    }

    void Resize(long n);                                   // 0x005c8d30
    void FUN_005c8bf0(RHTitbitList &other);
    void FUN_005c8980();
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last); // 0x0044e8b0
};

class RHTitbits
{
public:
    virtual bool Serialize(SBFile &file);
    bool RemoveQuickActionTitbitsFor(RHElementActorPC *actor, unsigned short action);
    short FUN_005c7fb0(unsigned long id);
    void FUN_005c8120(int kind, RHElement *element);
    bool FUN_005c8340(int kind, RHElement *element);
    bool IsRunningForQA(unsigned long id);
    bool RenderText(const std::wstring &text, const SBGeoPoint2D &point) const;
    bool RenderText(const std::wstring &text, const SBGeoBoundingBox2D &box, unsigned long flags) const;

    void Emit(SBFile &file);

    char m_pad0[0x1c];   // [0x04, 0x20): opaque; keeps the list at +0x20
    RHTitbitList m_list; // [0x20]
    char m_pad1[0x6c];   // [0x38, 0xa4): opaque
    int m_a4;            // [0xa4]
    float m_a8;          // [0xa8]
    int m_ac;            // [0xac]
};

void RHSerializeName(SBFile &file, const char *name);

#endif
