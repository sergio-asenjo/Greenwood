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

class RHUnk00584d60
{
public:
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char data[0x64];
};

class RHSequenceElementCalls;
class RHElement;

class RHEngine
{
public:
    void FUN_004ca410(RHSequenceElementCalls *element);
    bool SerializeElementPointer(SBFile &file, RHElement *&element);
};

extern RHEngine *g_pEngine;

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
    virtual void Slot4c() = 0;
    virtual void Slot50() = 0;
    virtual void Slot54(RHSequenceElementCalls *element) = 0;
};

class RHSequenceElementCalls
{
public:
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0c() = 0;
    virtual void Slot10() = 0;
    virtual void FUN_00585d00();
    virtual void FUN_00585c80();
    virtual void FUN_00585d40();
    virtual void FUN_00585e30();
    virtual void FUN_00585cc0(int value);
    bool FUN_00585b70();
    RHSequenceElementCalls *FUN_00585d80();
    void FUN_00585df0(RHSequenceElementCalls *other);
    void Emit(int value, RHSequenceElementCalls *other);

    char m_04[0x0c];
    int m_10;
    char m_14[0x28];
    int m_3c;
    int m_40;
    int m_44;
    void *m_48;
    RHSequenceElementCalls *m_4c;
    RHSequenceElementCalls *m_50;
    void *m_54;
    void *m_58;
    void *m_5c;
    int m_60;
};

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
    ((RHSequenceElement *)this)->RHSequenceElement::RHSequenceElement();
    *(unsigned *)this = 0x679d04;
    m_04 = 3;
}

class RHUnk00585ea0 : public RHUnk00584d60
{
public:
    RHUnk00585ea0(unsigned short level, int command, void *actor, void *target);
    ~RHUnk00585ea0();
    void *m_64;
};

// FUNCTION: GAME 0x00585ea0
RHUnk00585ea0::RHUnk00585ea0(unsigned short level, int command, void *actor, void *target)
    : RHUnk00584d60(level, command, actor)
{
    *(unsigned *)this = 0x679d04;
    m_64 = target;
    data[4] = 3;
}

class RHSequenceInteractionCalls : public RHSequenceElementCalls
{
public:
    RHSequenceInteractionCalls *FUN_00585ed0();
    bool FUN_00585f40(SBFile &file, bool pointers);
    int FUN_00585f70();
    void Emit(SBFile &file, bool pointers);
    void *m_64;
};

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
