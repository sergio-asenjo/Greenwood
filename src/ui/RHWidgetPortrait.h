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

#include "RHRendererGeometry.h"

#include "RHWidgetPortraitClass.h"

// SIZE 0x04
#include "RHPortraitActorCalls.h"

// The file version lives at SBFile+0x10. SB.h is shared and must not change,
// so it is reached through an explicit offset accessor.
inline unsigned int &FileVersion(SBFile &f)
{
    return *(unsigned int *)((char *)&f + 0x10);
}

void RHSerializeName(SBFile &file, const char *name);

#include "RHPortraitRenderer005cadc0.h"

class RHPortraitRenderer005ca330
{
public:
    RHPortraitRenderer005ca330();
    ~RHPortraitRenderer005ca330();
    undefined m_data[0x5c];
};

#include "RHUIRendererShiftingTitbitClass.h"

class RHPortraitRenderer005cc110
{
public:
    ~RHPortraitRenderer005cc110()
    {
        ((RHUIRendererShiftingTitbit *)this)->~RHUIRendererShiftingTitbit();
    }
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

#include "RHPortraitRootLifetime.h"

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
    void FUN_0061c610(unsigned long surface);
    void FUN_0061d570(unsigned short position, int limit);
    unsigned FUN_0061d5e0();
    SBGeoBoundingBox2D FUN_0061d3f0(unsigned short line, int value);
    SBGeoBoundingBox2D FUN_0061d7c0();
    SBGeoBoundingBox2D FUN_0061d620();
    unsigned FUN_0061d950();
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

#include "RHFocusManager.h"

typedef RHFocusManager RHPortraitUIOwner;

class RHPortraitTextLinkedCalls
{
public:
    void FUN_0053f9f0(void *stop);
};

class RHPortraitTextResourceCalls
{
public:
    void *FUN_0053be80(const std::string &name);
};

struct SBUIInputFieldUnkResource;

class RHMapWideText;

class SBUIInputFieldUnk00621440
{
public:
    bool FUN_00621470(unsigned int id);
    void FUN_0061e340();
    void FUN_0061e060(RHMapWideText *text);
    void FUN_0061e4b0();
    RHMapWideText FUN_0061df60();
    void FUN_00621440(SBUIInputFieldUnkResource *resource);
    bool FUN_00621c30(const SBGeoBoundingBox2D &box);
};

class SBUIInputFieldTextUnk
{
public:
    void FUN_0061e320(unsigned char value);
    char FUN_0061e230();
    unsigned FUN_0061dd00();
    unsigned FUN_0061df50();
    unsigned FUN_0061dd30();
    void FUN_0061e240(unsigned direction);
    void FUN_0061e2b0(unsigned index);
};

class SBUIInputFieldUnk0061e180
{
public:
    bool Insert(unsigned short character);
};

#include "SBUIKeyboardCalls.h"

unsigned FUN_005fb1d0(unsigned key);
int FUN_005fb0f0(unsigned key, unsigned short *characters, const void *state, unsigned flags);
