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
#include <list>
#include "RHRendererGeometry.h"
#include "../engine/RHGame_calls.h"

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
    void *FUN_005ca310(unsigned flags);
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

#include "RHPortraitStrategyCalls.h"

// VTABLE: GAME 0x00679f30
class RHUnk005cca80
{
public:
    RHUnk005cca80();
    virtual void *V00() = 0;
    virtual void *V04(bool enabled) = 0;
    unsigned m_4;
};

class SBGeoBoundingBox2D;

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

// VTABLE: GAME 0x0067a4e4
class RHPortraitLifetime005db4a0 : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitLifetime005db4a0() {}
    ~RHPortraitLifetime005db4a0() {}
    void *FUN_005db480(unsigned flags);
    RHPortraitRenderer005ca330 m_renderer;
};

class RHPortraitLifetime005d6200 : public RHPortraitLifetime005db4a0
{
public:
    ~RHPortraitLifetime005d6200() {}
};

// VTABLE: GAME 0x0067a51c
class RHPortraitLifetime005db5a0 : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitLifetime005db5a0() {}
    ~RHPortraitLifetime005db5a0() {}
    void *FUN_005db580(unsigned flags);
    RHPortraitRenderer005cc110 m_renderer;
};

class RHPortraitLifetime005d63b0 : public RHPortraitLifetime005db5a0
{
public:
    ~RHPortraitLifetime005d63b0() {}
};

class RHPortraitLifetime005d6320 : public RHPortraitLifetime005d63b0
{
public:
    RHPortraitLifetime005d6320();
    SBGeoBoundingBox2D m_box;
};

typedef RHGameLifetime00516750 RHPortraitMessageWidgetBase;

class RHPortraitActorCalls
{
public:
    const std::wstring &FUN_00492730();
};

class RHPortraitUnk005d0180
{
public:
    ~RHPortraitUnk005d0180();
    void *FUN_005d09f0(unsigned flags);
};

#include "RHPortraitInputRenderer.h"

// VTABLE: GAME 0x0067a044
class RHPortraitInputRendererMember : public RHPortraitInputRenderer
{
public:
    RHPortraitInputRendererMember()
    {
    }
    void *FUN_005d1b40(unsigned flags);
};

// VTABLE: GAME 0x0067a00c
class RHPortraitInputWidget : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitInputWidget();
    ~RHPortraitInputWidget();
    void *FUN_005d09b0(unsigned flags);
    RHPortraitInputRendererMember m_renderer;
};

class RHPortraitTextLines
{
public:
    RHPortraitTextLines();
    ~RHPortraitTextLines()
    {
        m_list.clear();
    }
    std::list<std::wstring> m_list;
    std::list<std::wstring>::iterator m_current;
    bool m_dirty;
    int m_index;
    undefined m_18[8];
    std::wstring m_text;
};

class RHPortraitItemIndices
{
public:
    ~RHPortraitItemIndices()
    {
        m_list.clear();
    }
    std::list<unsigned long> m_list;
    std::list<unsigned long>::iterator m_current;
    bool m_dirty;
    int m_index;
};

// VTABLE: GAME 0x00679fd4
class RHPortraitUnk005cf570 : public RHPortraitInputWidget
{
public:
    ~RHPortraitUnk005cf570();
    void *FUN_005d09d0(unsigned flags);
    RHPortraitTextLines m_first;
    RHPortraitTextLines m_second;
    RHPortraitItemIndices m_items;
    undefined m_17c[0x28];
    SBGeoPoint2D m_point;
    SBGeoBoundingBox2D m_firstBox;
    SBGeoBoundingBox2D m_secondBox;
};

class RHPortraitInputCalls
{
public:
    int FUN_005cfc30(const void *input);
};

#include "RHPortraitRenderer0060dab0.h"

#include "RHPortraitRenderer006212d0.h"

#include "SBUIInputFieldText.h"

#include "RHFocusManager.h"

typedef RHFocusManager RHPortraitUIOwner;

class RHPortraitTextLinkedCalls
{
public:
    void FUN_0053f9f0(void *stop);
};

typedef RHMenuScreenView RHPortraitTextResourceCalls;

struct SBUIInputFieldUnkResource;

class RHMapWideText;

class SBUIInputFieldUnk00621440
{
public:
    bool FUN_00621470(unsigned int id);
    void FUN_0061e340();
    void FUN_0061e060(const std::wstring &text);
    void FUN_0061e4b0();
    std::wstring FUN_0061df60();
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
    void FUN_0061e2b0(unsigned index);
};

#include "SBUIKeyboardCalls.h"
#include "RHMenuScreenView.h"

unsigned FUN_005fb1d0(unsigned key);
int FUN_005fb0f0(unsigned key, unsigned short *characters, const void *state, unsigned flags);
