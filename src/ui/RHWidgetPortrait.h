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
#include "Decomp.h"

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
};

// Sub-object at RHWidgetPortrait+0x7bc. Only the virtual at index 21
// (vtable byte offset 0x54) is exercised by the target; the preceding slots
// exist to place it at that index.
// SIZE 0x04
class RHUnk005d92c0Sub
{
public:
    virtual void v00(); // vtable+0x00
    virtual void v01(); // vtable+0x04
    virtual void v02(); // vtable+0x08
    virtual void v03(); // vtable+0x0c
    virtual void v04(); // vtable+0x10
    virtual void v05(); // vtable+0x14
    virtual void v06(); // vtable+0x18
    virtual void v07(); // vtable+0x1c
    virtual void v08(const SBGeoPoint2D &point); // vtable+0x20
    virtual void v09(); // vtable+0x24
    virtual void v10(); // vtable+0x28
    virtual void v11(); // vtable+0x2c
    virtual void v12(); // vtable+0x30
    virtual void v13(); // vtable+0x34
    virtual void v14(RHUnk005d92c0Sub *widget); // vtable+0x38
    virtual void v15(RHUnk005d92c0Sub *widget); // vtable+0x3c
    virtual void v16(); // vtable+0x40
    virtual void v17(); // vtable+0x44
    virtual void v18(); // vtable+0x48
    virtual void v19(); // vtable+0x4c
    virtual void v20(); // vtable+0x50
    virtual void v21(int value); // vtable+0x54
};

// SIZE 0x04
class RHUnk005d73d0Actor : public RHUnk005d92c0Sub
{
public:
    char FUN_0049f510();
    virtual void v22(); // vtable+0x58
    virtual void v23(); // vtable+0x5c
    virtual void v24(); // vtable+0x60
    virtual void v25(); // vtable+0x64
    virtual void v26(); // vtable+0x68
    virtual void v27(); // vtable+0x6c
    virtual void v28(); // vtable+0x70
    virtual void v29(); // vtable+0x74
    virtual void v30(); // vtable+0x78
    virtual void v31(); // vtable+0x7c
    virtual void v32(); // vtable+0x80
    virtual void v33(); // vtable+0x84
    virtual void v34(); // vtable+0x88
    virtual void v35(); // vtable+0x8c
    virtual void v36(); // vtable+0x90
    virtual void v37(); // vtable+0x94
    virtual void v38(); // vtable+0x98
    virtual void v39(); // vtable+0x9c
    virtual void v40(); // vtable+0xa0
    virtual void v41(); // vtable+0xa4
    virtual void v42(); // vtable+0xa8
    virtual void v43(); // vtable+0xac
    virtual void v44(); // vtable+0xb0
    virtual void v45(); // vtable+0xb4
    virtual void v46(); // vtable+0xb8
    virtual void v47(); // vtable+0xbc
    virtual void v48(); // vtable+0xc0
    virtual void v49(); // vtable+0xc4
    virtual void v50(); // vtable+0xc8
    virtual int v51(); // vtable+0xcc
};

// SIZE 0x104
struct RHUnk005d92c0Elem
{
    int m_00;      // [0x00]
    char m_04;     // [0x04]
    char m_05;     // [0x05]
    undefined m_pad0[0x4e - 0x06]; // 0x06
    char m_4e;     // [0x4e]
    char m_4f;     // [0x4f]
    char m_50;     // [0x50]
    char m_51;     // [0x51]
    undefined m_pad1[0x104 - 0x52]; // 0x52
};

// The file version lives at SBFile+0x10. SB.h is shared and must not change,
// so it is reached through an explicit offset accessor.
inline unsigned int &FileVersion(SBFile &f)
{
    return *(unsigned int *)((char *)&f + 0x10);
}

// SIZE 0xe58
class RHWidgetPortrait
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    bool Method005d6690();
    bool Method005d67e0();
    bool Method005d73d0();
    bool Method005d7530();
    void FUN_005d8ed0(int value, int height);
    void FUN_005d9c30();
    void FUN_005da1f0();

private:
    undefined m_pad0[0x16c]; // 0x00
    float m_16c;           // [0x16c]
    undefined m_pad1[0x7bc - 0x170]; // 0x170
    RHUnk005d92c0Sub m_7bc; // [0x7bc]
    char m_7c0;            // [0x7c0]
    undefined m_pad2[0xa50 - 0x7c1]; // 0x7c1
    RHUnk005d92c0Elem m_arr[3]; // [0xa50]
    undefined m_pad3[0xe50 - (0xa50 + 3 * 0x104)]; // 0xd5c
    char m_e50[6];         // [0xe50]
};

void RHSerializeName(SBFile &file, const char *name);
