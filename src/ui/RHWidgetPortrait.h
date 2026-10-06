// RHWidgetPortrait — declarations shared by RHWidgetPortrait.cpp (decompiled
// TU) and RHWidgetPortrait_stubs.cpp (external-symbol stubs).
//
// BINDING (0x005d92c0): RHWidgetPortrait::Serialize(SBFile&). See
// src/RHWidgetPortrait.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHWidgetPortrait::Serialize (0x005d92c0):
//   - +0x16c: float;
//   - +0x7bc: sub-object with a vtable (virtual dispatched at +0x54);
//   - +0x7c0: char;
//   - +0xa50: array of three 0x104-byte elements (int at +0, char at +5, and
//     bytes at +0x4e..+0x51 which the 0xca6..0xca9 accesses resolve to on
//     element 2);
//   - +0xe50: 6-byte blob.

#include "SB.h"

// Sub-object at RHWidgetPortrait+0x7bc. Only the virtual at index 21
// (vtable byte offset 0x54) is exercised by the target; the preceding slots
// exist to place it at that index.
class RHUnk005d92c0Sub
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21(int value);
};

struct RHUnk005d92c0Elem
{
    int m_00;      // [0x00]
    char m_04;     // [0x04]
    char m_05;     // [0x05]
    char m_pad0[0x4e - 0x06];
    char m_4e;     // [0x4e]
    char m_4f;     // [0x4f]
    char m_50;     // [0x50]
    char m_51;     // [0x51]
    char m_pad1[0x104 - 0x52];
};

// The file version lives at SBFile+0x10. SB.h is shared and must not change,
// so it is reached through an explicit offset accessor.
inline unsigned int &FileVersion(SBFile &f)
{
    return *(unsigned int *)((char *)&f + 0x10);
}

class RHWidgetPortrait
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    void Method005d6690(); // target 0x005d6690
    void Method005d67e0(); // target 0x005d67e0
    void Method005d73d0(); // target 0x005d73d0
    void Method005d7530(); // target 0x005d7530

private:
    char m_pad0[0x16c];
    float m_16c;           // [0x16c]
    char m_pad1[0x7bc - 0x170];
    RHUnk005d92c0Sub m_7bc; // [0x7bc]
    char m_7c0;            // [0x7c0]
    char m_pad2[0xa50 - 0x7c1];
    RHUnk005d92c0Elem m_arr[3]; // [0xa50]
    char m_pad3[0xe50 - (0xa50 + 3 * 0x104)];
    char m_e50[6];         // [0xe50]
};

void RHSerializeName(SBFile &file, const char *name);
