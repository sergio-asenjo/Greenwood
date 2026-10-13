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
#include "../engine/RHGame_calls.h"

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
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

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~SBGeoBoundingBox2D() {}
    bool FUN_006083b0(const SBGeoPoint2D &point) const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    bool Unk00608f30() const;
    void FUN_00607d90();
    SBGeoBoundingBox2D &FUN_00607da0(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &offset) const;
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
    int m_10;
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
    virtual void *v20(); // vtable+0x50
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
    virtual void v52(); // vtable+0xd0
    virtual void v53(); // vtable+0xd4
    virtual void v54(); // vtable+0xd8
    virtual void v55(); // vtable+0xdc
    virtual void v56(); // vtable+0xe0
    virtual unsigned short v57(int action); // vtable+0xe4
    virtual void v58(); // vtable+0xe8
    virtual void v59(); // vtable+0xec
    virtual void v60(); // vtable+0xf0
    virtual void v61(); // vtable+0xf4
    virtual bool v62(); // vtable+0xf8
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

    bool FUN_005d75c0(int first, int second, int third);
    bool FUN_005d7730(int value);
    bool FUN_005d7810(unsigned int index, void *value);
    bool FUN_005d7930(int value);
    bool FUN_005d7a30(int value);
    bool FUN_005d7b30(int value);
    bool FUN_005d7c40(int index, void *value, int mode);
    bool FUN_005d7ea0();
    bool FUN_005d8430();
    void FUN_005d8ed0(int value, int height);
    void FUN_005d9070();
    bool FUN_005d9090(unsigned int index);
    bool FUN_005d90c0(unsigned int index);
    void FUN_005d9160();
    void FUN_005d9180();
    void *FUN_005d9210(unsigned int value);

    bool Method005d6690();
    bool Method005d67e0();
    bool Method005d73d0();
    bool Method005d7530();
    void FUN_005d9c30();
    void FUN_005da1f0();
    void FUN_005d9920();
    bool FUN_005d9a20(int action);
    void FUN_005d9bc0();
    bool FUN_005d9eb0(int action);
    std::wstring GetPCName() const;

private:
    undefined m_pad0[0x16c]; // 0x00
    float m_16c;           // [0x16c]
    float m_170;           // [0x170]
    undefined m_pad1[0x7bc - 0x174]; // 0x174
    RHUnk005d92c0Sub m_7bc; // [0x7bc]
    char m_7c0;            // [0x7c0]
    undefined m_pad2[0xa50 - 0x7c1]; // 0x7c1
    RHUnk005d92c0Elem m_arr[3]; // [0xa50]
    undefined m_pad3[0xe50 - (0xa50 + 3 * 0x104)]; // 0xd5c
    char m_e50[6];         // [0xe50]
};

void RHSerializeName(SBFile &file, const char *name);

class RHPortraitRendererCalls
{
public:
    void FUN_005cb2a0();
    void FUN_005cb2b0(int value);
    void FUN_005cae10(int mode);
    void FUN_005cafa0(unsigned id);
};

class RHPortraitRenderer005cadc0
{
public:
    RHPortraitRenderer005cadc0();
    ~RHPortraitRenderer005cadc0();
    undefined m_data[0x58];
};

class RHPortraitRenderer005ca330
{
public:
    RHPortraitRenderer005ca330();
    ~RHPortraitRenderer005ca330();
    undefined m_data[0x5c];
};

class RHPortraitRenderer005cc110
{
public:
    ~RHPortraitRenderer005cc110();
    undefined m_data[0x70];
};

class RHPortraitStrategyCalls
{
public:
    RHPortraitStrategyCalls();
};

class SBGeoBoundingBox2D;
class RHPortraitWidgetSetupCalls
{
public:
    bool FUN_0060d130(const std::wstring &text, const SBGeoBoundingBox2D &box, bool value);
};

class RHPortraitRootLifetime
{
public:
    RHPortraitRootLifetime();
    ~RHPortraitRootLifetime();
    void FUN_0061a800(void *widget);
    void FUN_0061aa30(void *widget);
    bool FUN_0061a920(void *widget);
    void *FUN_0061a6e0(const void *input);
    unsigned m_vptr;
    undefined m_data[0x9c];
};

class RHPortraitResourceCollection
{
public:
    RHPortraitResourceCollection(bool value);
    ~RHPortraitResourceCollection();
    undefined m_data[0x20];
};

class RHPortraitCtorCalls
{
public:
    void FUN_005d6940(unsigned short index);
};

class RHPortraitResourceCalls
{
public:
    RHPortraitResourceCalls *FUN_00502270();
};

RHPortraitResourceCalls *FUN_005024f0(const std::string &name);

class RHPortraitLifetime005d6200 : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitLifetime005d6200();
    ~RHPortraitLifetime005d6200();
    RHPortraitRenderer005ca330 m_renderer;
};

class RHPortraitLifetime005d63b0 : public RHGameWidgetLifetimeBase
{
public:
    ~RHPortraitLifetime005d63b0();
    RHPortraitRenderer005cc110 m_renderer;
};

class RHPortraitLifetime005d6320 : public RHPortraitLifetime005d63b0
{
public:
    RHPortraitLifetime005d6320();
    ~RHPortraitLifetime005d6320();
    SBGeoBoundingBox2D m_box;
};

class RHPortraitMessageWidgetBase : public RHGameLifetime00516430
{
public:
    RHPortraitMessageWidgetBase();
    ~RHPortraitMessageWidgetBase() { m_vptr = 0x00678e50; }
    unsigned m_strategy;
    int m_value;
};

class RHPortraitActorCalls
{
public:
    const std::wstring &FUN_00492730();
};

class RHPortraitUnk005cf320
{
public:
    ~RHPortraitUnk005cf320();
    void *FUN_005d09b0(unsigned flags);
};

class RHPortraitUnk005cf570
{
public:
    ~RHPortraitUnk005cf570();
    void *FUN_005d09d0(unsigned flags);
};

class RHPortraitUnk005d0180
{
public:
    ~RHPortraitUnk005d0180();
    void *FUN_005d09f0(unsigned flags);
};

class RHPortraitInputRenderer
{
public:
    RHPortraitInputRenderer();
    ~RHPortraitInputRenderer();
    void *FUN_005d1b40(unsigned flags);
    void FUN_0061d570(unsigned short position, int limit);
    unsigned FUN_0061d5e0();
    SBGeoBoundingBox2D FUN_0061d3f0(unsigned short line, int value);
    SBGeoBoundingBox2D FUN_0061d7c0();
    unsigned m_vptr;
};

class RHPortraitInputCalls
{
public:
    bool FUN_005cfc30(const void *input);
};

class RHPortraitRenderer006212d0
{
public:
    RHPortraitRenderer006212d0();
    ~RHPortraitRenderer006212d0();
    undefined m_data[0x90];
};

class RHPortraitText0061db10
{
public:
    RHPortraitText0061db10();
    ~RHPortraitText0061db10();
    undefined m_data[0x48];
};

class RHPortraitUIOwner
{
public:
    void *FUN_004fffd0();
};

class RHMapWideText;

class SBUIInputFieldUnk00621440
{
public:
    bool FUN_00621470(unsigned int id);
    void FUN_0061e340();
    void FUN_0061e060(RHMapWideText *text);
};

class SBUIInputFieldTextUnk
{
public:
    void FUN_0061e320(unsigned char value);
    char FUN_0061e230();
    unsigned FUN_0061dd00();
    unsigned FUN_0061df50();
};
