// RHSequenceElement.cpp — translation unit with __FILE__ evidence at 0x005852c0
// ("P:\Robin Hood\RHsequenceelement.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005852c0 -> RHSequenceElement::SerializeStaticStuff(SBFile&)):
//   - TU:        rhsequenceelement.cpp (embedded __FILE__ string 0x006b74b4).
//   - Class:     RHSequenceElement (symbols/oracle-correlation.tsv:
//                rhsequenceelement -> class RHSequenceElement, 36 methods).
//   - Signature: RHSequenceElement::SerializeStaticStuff(SBFile&)
//                (symbols/mac-RH.txt; zeta-robin.txt
//                SerializeStaticStuff__17RHSequenceElementR6SBFile).
//   - Signals:
//       * the function writes the type-name tag
//         "RHSequenceElement::SerializeStaticStuff" (string 0x006b74fc) as its
//         first act via the 0x005e1b70 helper;
//       * a single SBFile::Access check on the 4-byte global 0x006b74d8, then
//         the "Serialize failed reason is %s" assert idiom — a serializer with
//         no loop, no `new`, no base call;
//       * the body never uses ecx as `this` (arg is `[esp+8]`), so Windows
//         emits it as a static member — declared `static` here.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHSequenceElement.h"

// The 4-byte global read/written by SerializeStaticStuff (original 0x006b74d8).
// GLOBAL: GAME 0x006b74d8
int g_unk0x6b74d8;

// FUNCTION: GAME 0x005852c0
bool RHSequenceElement::SerializeStaticStuff(SBFile &file)
{
    // STRING: GAME 0x6b74fc
    RHSerializeName(file, "RHSequenceElement::SerializeStaticStuff");

    if (file.Access(&g_unk0x6b74d8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b74b4
                 "P:\\Robin Hood\\RHsequenceelement.cpp",
                 172,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps SerializeStaticStuff in the build.
void RHSequenceElement::Emit(SBFile &file)
{
    SerializeStaticStuff(file);
}

#include "RHSequenceGenericCalls.h"

class RHSequenceElementCalls;
class RHElement;

class RHImmediateElementCalls
{
public:
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0c() = 0;
    virtual void Slot10() = 0;
    virtual void Slot14() = 0;
    virtual void Slot18() = 0;
    virtual void Slot1c() = 0;
    virtual void Slot20() = 0;
    virtual void Slot24() = 0;
    virtual void Slot28() = 0;
    virtual void Slot2c() = 0;
    virtual void Slot30() = 0;
    virtual void Slot34() = 0;
    virtual void Slot38() = 0;
    virtual void Slot3c() = 0;
    virtual void Slot40() = 0;
    virtual void Slot44() = 0;
    virtual void Slot48() = 0;
    virtual void Slot4c(RHSequenceElementCalls *element) = 0;
    virtual void Slot50(RHSequenceElementCalls *element) = 0;
    virtual void Slot54(RHSequenceElementCalls *element) = 0;
};

#include "RHSequenceElementCalls.h"
#include "RHSequenceAppendCalls.h"
#include <list>

class RHSequenceAppendList : public std::list<RHSequenceElementCalls *>
{
public:
    void Append(RHSequenceElementCalls *const &element, volatile bool &dirty)
    {
        _Nodeptr node = _Head;
        _Acc::_Prev(node) = _Buynode(node, _Acc::_Prev(node));
        node = _Acc::_Prev(node);
        _Acc::_Next(_Acc::_Prev(node)) = node;
        allocator.construct(&_Acc::_Value(node), element);
        unsigned count = *(volatile unsigned *)&_Size;
        dirty = true;
        _Size = count + 1;
    }
};

struct RHSequenceAppendView
{
    char m_00[8];
    RHSequenceAppendList elements;
    char m_14[4];
    bool m_18;
};

// FUNCTION: GAME 0x00584cf0
RHUnk00584d60::RHUnk00584d60()
{
    m_04 = 0;
    m_4c = 0;
    m_50 = 0;
    m_54 = 0;
    m_60 = false;
}

// FUNCTION: GAME 0x00584d40
void *RHUnk00584d60::FUN_00584d40(unsigned int flags)
{
    this->~RHUnk00584d60();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00584d60
RHUnk00584d60::RHUnk00584d60(unsigned short level, int command, void *actor)
    : m_10(command), m_14(level), m_48(actor)
{
    m_08 = g_unk0x6b74d8++;
    m_4c = 0;
    m_50 = 0;
    m_54 = 0;
    m_0c = 0;
    m_04 = 0;
    m_60 = false;
    m_58 = 3;
    m_5c = 11;
}

// Parked: list teardown inlining and the base iterator increment differ.
// STUB: GAME 0x00584de0
RHUnk00584d60::~RHUnk00584d60()
{
    m_orders.DeleteAll();
}

class RHSequenceStopOwner
{
public:
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0c() = 0;
    virtual void Slot10() = 0;
    virtual void Slot14() = 0;
    virtual void Slot18() = 0;
    virtual void Slot1c() = 0;
    virtual void Slot20() = 0;
    virtual void Slot24() = 0;
    virtual void Slot28() = 0;
    virtual void Slot2c() = 0;
    virtual void Slot30() = 0;
    virtual void Slot34() = 0;
    virtual void Slot38() = 0;
    virtual void Slot3c() = 0;
    virtual void Slot40() = 0;
    virtual void Slot44() = 0;
    virtual void Slot48() = 0;
    virtual void Slot4c() = 0;
    virtual void Slot50() = 0;
    virtual void Slot54() = 0;
    virtual void Slot58() = 0;
    virtual void Slot5c() = 0;
    virtual void Slot60() = 0;
    virtual void Slot64() = 0;
    virtual void Slot68() = 0;
    virtual void Slot6c() = 0;
    virtual void Slot70() = 0;
    virtual void Slot74() = 0;
    virtual void Slot78() = 0;
    virtual void Slot7c() = 0;
    virtual void Slot80() = 0;
    virtual void Slot84() = 0;
    virtual void Slot88() = 0;
    virtual void Slot8c() = 0;
    virtual void Slot90() = 0;
    virtual int Slot94(RHSequenceElementCalls *element) = 0;
    unsigned char m_04;
};

#include "RHSequenceDispatch.h"

class RHSequenceStateOrders : public RHSequenceOrderList
{
public:
    void Clear()
    {
        iterator position = begin();
        iterator last = end();
        typedef iterator (RHUnk0046eb30::*Erase)(iterator);
        while (position != last)
            (((RHUnk0046eb30 *)this)->*(Erase)&RHUnk0046eb30::erase)(position++);
        m_dirty = true;
    }
    void DeleteOrders()
    {
        m_cursor = begin();
        if (m_cursor != end())
        {
            do
            {
                delete *m_cursor;
            }
            while (++m_cursor != end());
        }
        Clear();
    }
};

// STUB: GAME 0x00585320
void RHSequenceElementCalls::FUN_00585320(int state, int value)
{
    int previous = m_58;
    if (previous == state)
        return;
    m_58 = state;
    if (state == 2)
        ++*(unsigned short *)((char *)m_54 + 0x32);
    else if (previous == 2)
        --*(unsigned short *)((char *)m_54 + 0x32);
    switch (state)
    {
    case 5:
        FUN_00585710();
    case 6:
        ((RHSequenceStateOrders *)((char *)this + 0x18))->DeleteOrders();
        if (m_48)
            ((RHImmediateElementCalls *)m_48)->Slot4c(this);
        if (value & 2)
        {
            if (m_4c)
                m_4c->Slot0c(state, 2);
        }
        else if (value & 1)
        {
            RHSequenceElementCalls *next = this;
            do
            {
                next = next->m_4c;
            }
            while (next && *(volatile unsigned short *)next->m_14 == *(volatile unsigned short *)m_14);
            if (next)
                next->Slot0c(state, 2);
        }
        break;
    case 0:
        if (previous >= 2 && previous <= 4)
        {
            if (m_48)
                ((RHImmediateElementCalls *)m_48)->Slot4c(this);
            ((RHUnk00582620 *)m_54)->FUN_00582620((int)this);
            FUN_00585710();
        }
        break;
    }
}

// FUNCTION: GAME 0x00585450
void RHSequenceElementCalls::FUN_00585450(int priority)
{
    if (m_5c == 11) {
        RHSequenceStopOwner *owner = (RHSequenceStopOwner *)m_48;
        if (!owner || (owner->m_04 & 3) || (m_5c = owner->Slot94(this)) == 10)
            m_5c = 8;
    }
    if (m_5c >= priority) {
        if (m_58 == 2 && (unsigned char)m_04[0] == 4) {
            if (m_4c)
                m_4c->Slot0c(6, 1);
        } else
            Slot0c(6, 1);
    } else if (m_4c) {
        m_4c->Slot10(priority);
        if (m_4c && m_4c->m_58 == 6)
            m_4c = 0;
    }
    if (m_50) {
        m_50->Slot10(priority);
        if (m_50 && m_50->m_58 == 6)
            m_50 = 0;
    }
}

// FUNCTION: GAME 0x00585500
void RHUnk00585500::Unk(void *sequence)
{
    RHSequenceAppendView *owner = (RHSequenceAppendView *)sequence;
    RHSequenceElementCalls *element = (RHSequenceElementCalls *)this;
    if (*(unsigned short *)((char *)sequence + 0x10) != 0)
        owner->elements.back()->m_4c = element;
    element->m_54 = sequence;
    owner->elements.Append(element, owner->m_18);
}

// FUNCTION: GAME 0x00585570
void RHSequenceElementCalls::FUN_00585570()
{
    if ((int)m_58 >= 3 && (int)m_58 <= 4)
    {
        if (m_48)
            ((RHImmediateElementCalls *)m_48)->Slot50(this);
        else
            g_pEngine->FUN_004ca410(this);
    }
}

struct RHSequenceStateActorInfo
{
    char m_00[0x8c];
    int m_8c;
};

struct RHSequenceStateActor
{
    char m_00[0x50];
    RHSequenceStateActorInfo *m_50;
};

// STUB: GAME 0x00585710
void RHSequenceElementCalls::FUN_00585710()
{
    if (m_50)
    {
        if (m_50->m_10 == 22 && m_50->m_48 &&
            ((RHSequenceStateActor *)m_48)->m_50->m_8c != ((RHSequenceStateActor *)m_50->m_48)->m_50->m_8c)
        {
            ((RHSequenceStateOrders *)((char *)m_50 + 0x18))->DeleteOrders();
            m_50->m_10 = 20;
        }
        ((RHSequenceManager *)g_unk0x6c1040)->FUN_0058bb80((RHSequenceElement *)m_50);
        m_50 = 0;
    }
}

// FUNCTION: GAME 0x00585940
void RHSequenceElementCalls::FUN_00585940(RHSequenceElementCalls *other)
{
    if (other->m_50)
    {
        if (m_50)
            m_50->FUN_00585940(other);
        else
        {
            m_50 = other->m_50;
            other->m_50 = 0;
        }
    }
}

// FUNCTION: GAME 0x00585b70
bool RHSequenceElementCalls::FUN_00585b70()
{
    switch (m_10)
    {
    case 24:
    case 127:
    case 128:
    case 129:
    case 146:
    case 156:
    case 157:
    case 158:
    case 159:
    case 170:
    case 171:
        ((RHImmediateElementCalls *)m_48)->Slot54(this);
        return true;
    case 4:
    case 5:
    case 7:
    case 11:
    case 79:
    case 80:
    case 175:
        g_pEngine->FUN_004ca410(this);
        return true;
    case 15:
        if (m_48)
            ((RHImmediateElementCalls *)m_48)->Slot54(this);
        else
            g_pEngine->FUN_004ca410(this);
        return true;
    default:
        return false;
    }
}

// FUNCTION: GAME 0x00585c80
void RHSequenceElementCalls::FUN_00585c80()
{
    if (m_4c && m_4c->m_48 == m_48)
        m_4c->FUN_00585c80();
    if (m_50 && m_50->m_48 == m_48)
        m_50->FUN_00585c80();
}

// FUNCTION: GAME 0x00585cc0
void RHSequenceElementCalls::FUN_00585cc0(int value)
{
    if (m_4c && m_4c->m_48 == m_48)
        m_4c->FUN_00585cc0(value);
    if (m_50 && m_50->m_48 == m_48)
        m_50->FUN_00585cc0(value);
}

// FUNCTION: GAME 0x00585d00
void RHSequenceElementCalls::FUN_00585d00()
{
    if (m_4c && m_4c->m_48 == m_48)
        m_4c->FUN_00585d00();
    if (m_50 && m_50->m_48 == m_48)
        m_50->FUN_00585d00();
}

// FUNCTION: GAME 0x00585d40
void RHSequenceElementCalls::FUN_00585d40()
{
    if (m_10 == 0x4d)
        m_10 = 0;
    if (m_4c && m_4c->m_48 == m_48)
        m_4c->FUN_00585d40();
    if (m_50 && m_50->m_48 == m_48)
        m_50->FUN_00585d40();
}

// FUNCTION: GAME 0x00585d80
RHSequenceElementCalls *RHSequenceElementCalls::FUN_00585d80()
{
    RHSequenceElementCalls *copy = (RHSequenceElementCalls *)new RHUnk00584d60(*(unsigned short *)m_14, m_10, m_48);
    copy->FUN_00585df0(this);
    return copy;
}

// FUNCTION: GAME 0x00585df0
void RHSequenceElementCalls::FUN_00585df0(RHSequenceElementCalls *other)
{
    m_4c = other->m_4c;
    m_50 = other->m_50;
    m_54 = other->m_54;
    m_58 = other->m_58;
    m_5c = other->m_5c;
    m_3c = other->m_3c;
    m_40 = other->m_40;
}

// FUNCTION: GAME 0x00585e30
void RHSequenceElementCalls::FUN_00585e30()
{
    if (m_4c && m_4c->m_48 == m_48)
        m_4c->FUN_00585e30();
    if (m_50 && m_50->m_48 == m_48)
        m_50->FUN_00585e30();
}

void RHSequenceElementCalls::Emit(int value, RHSequenceElementCalls *other)
{
    ((RHUnk00585500 *)this)->Unk(other);
    FUN_00585570();
    FUN_00585940(other);
    FUN_00585b70();
    RHSequenceElementCalls::FUN_00585c80();
    RHSequenceElementCalls::FUN_00585cc0(value);
    RHSequenceElementCalls::FUN_00585d00();
    RHSequenceElementCalls::FUN_00585d40();
    FUN_00585d80();
    FUN_00585df0(other);
    RHSequenceElementCalls::FUN_00585e30();
}

class RHUnk585e70
{
public:
    RHUnk585e70();
    char m_00[4];
    unsigned char m_04;
    char m_05[0x63];
};

// FUNCTION: GAME 0x00585e70
RHUnk585e70::RHUnk585e70()
{
    ((RHUnk00584d60 *)this)->RHUnk00584d60::RHUnk00584d60();
    *(unsigned *)this = 0x679d04;
    m_04 = 3;
}

#include "RHSequenceInteractionAction.h"

// FUNCTION: GAME 0x00585ea0
RHUnk00585ea0::RHUnk00585ea0(unsigned short level, int command, void *actor, void *target)
    : RHUnk00584d60(level, command, actor)
{
    *(unsigned *)this = 0x679d04;
    m_64 = target;
    m_04 = 3;
}

#include "RHSequenceInteractionCalls.h"

// FUNCTION: GAME 0x00585ed0
RHSequenceInteractionCalls *RHSequenceInteractionCalls::FUN_00585ed0()
{
    RHSequenceInteractionCalls *copy = (RHSequenceInteractionCalls *)new RHUnk00585ea0(*(unsigned short *)m_14, m_10, m_48, m_64);
    copy->FUN_00585df0(this);
    return copy;
}

// FUNCTION: GAME 0x00585f40
bool RHSequenceInteractionCalls::FUN_00585f40(SBFile &file, bool pointers)
{
    ((RHSequenceElement *)this)->FUN_00584ef0(file, pointers);
    g_pEngine->SerializeElementPointer(file, *(RHElement **)&m_64);
    return true;
}

// FUNCTION: GAME 0x00585f70
int RHSequenceInteractionCalls::FUN_00585f70()
{
    if (m_10 == 20 || m_10 == 22 || m_10 == 21 || m_10 == 19 || m_10 == 83 || m_10 == 2)
        return 1;
    return 0;
}

void RHSequenceInteractionCalls::Emit(SBFile &file, bool pointers)
{
    FUN_00585ed0();
    FUN_00585f40(file, pointers);
    FUN_00585f70();
}
