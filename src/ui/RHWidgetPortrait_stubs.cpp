// Stub definitions for the external symbols RHWidgetPortrait.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHWidgetPortrait::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName are already
// defined once, in RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only
// declares them (include/SB.h, include/RHWidgetPortrait.h).

#include "SBNullstr.h"
#include "RHWidgetPortrait.h"

#include "SBUIRendererListbox.h"
#include "RHGameWidgetLifetime.h"

// FUNCTION: GAME 0x0049f510
char RHUnk005d73d0Actor::FUN_0049f510()
{
    return *(char *)((char *)*(void **)((char *)this + 0x600) + 0x16);
}
void RHWidgetPortrait::FUN_005d9c30() {}

// FUNCTION: GAME 0x005ca2f0
RHPortraitRenderer005ca330::RHPortraitRenderer005ca330()
{
    ((RHGameRenderer0060da10 *)this)->RHGameRenderer0060da10::RHGameRenderer0060da10();
    *(unsigned *)this = 0x679e6c;
    *(float *)((char *)this + 0x50) = 100.0f;
    *(float *)((char *)this + 0x4c) = 100.0f;
}
// FUNCTION: GAME 0x005ca310
void *RHPortraitRenderer005ca330::FUN_005ca310(unsigned flags)
{
    this->~RHPortraitRenderer005ca330();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005ca330
RHPortraitRenderer005ca330::~RHPortraitRenderer005ca330()
{
    *(unsigned *)this = 0x679e6c;
    ((RHGameRenderer0060da10 *)this)->RHGameRenderer0060da10::~RHGameRenderer0060da10();
}
// FUNCTION: GAME 0x005cca80
RHUnk005cca80::RHUnk005cca80()
{
    m_4 = 0;
    m_vptr = 0x679f30;
}
// FUNCTION: GAME 0x005ccb40
RHPortraitStrategyCalls::RHPortraitStrategyCalls()
{
    *(unsigned *)this = 0x679f38;
}
bool RHPortraitWidgetSetupCalls::FUN_0060d130(const std::wstring &, const SBGeoBoundingBox2D &, bool) { return true; }
RHPortraitRootLifetime::RHPortraitRootLifetime() {}
RHPortraitRootLifetime::~RHPortraitRootLifetime() {}
RHPortraitResourceCollection::RHPortraitResourceCollection(bool) {}
RHPortraitResourceCollection::~RHPortraitResourceCollection() {}
void RHPortraitCtorCalls::FUN_005d6940(unsigned short) {}
RHPortraitResourceCalls *RHPortraitResourceCalls::FUN_00502270() { return this; }
RHPortraitResourceCalls *FUN_005024f0(const std::string &) { return 0; }
RHPortraitLifetime005d6320::RHPortraitLifetime005d6320() {}
const std::wstring &RHPortraitActorCalls::FUN_00492730() { static std::wstring value; return value; }

typedef RHPortraitRenderer0060dab0 RHPortraitRenderer0060dad0;

#include "RHPortraitRenderer0060d470.h"


RHPortraitUnk005d0180::~RHPortraitUnk005d0180() {}

// FUNCTION: GAME 0x0061d5e0
unsigned RHPortraitInputRenderer::FUN_0061d5e0()
{
    float span = *(float *)((char *)this + 0x14) - *(float *)((char *)this + 0xc);
    unsigned count = ((SBUIListboxUnk0061d980 *)this)->m_4c->FUN_0061e890();
    return (unsigned)(span / count);
}


// FUNCTION: GAME 0x0061d950
unsigned RHPortraitInputRenderer::FUN_0061d950()
{
    float top = *(float *)((char *)this + 0x14);
    float bottom = *(float *)((char *)this + 0xc);
    return (unsigned)((top - bottom - 2.0f) / *(unsigned short *)((char *)this + 0x80));
}
DECOMP_SIZE_ASSERT(RHPortraitRenderer006212d0, 0x90)

// Parked: zero/one register allocation and literal-vptr/vector-store ordering differ.
// STUB: GAME 0x006212d0
RHPortraitRenderer006212d0::RHPortraitRenderer006212d0()
    : m_font(0), m_alternateFont(0), m_textObject(0), m_enabled(true)
{
    m_vptr = 0x0067ae60;
    m_offset.m_x = 0;
    m_offset.m_y = 0;
}

// Parked: non-polymorphic base model may schedule the vptr after the EH-state store.
// STUB: GAME 0x00621380
RHPortraitRenderer006212d0::~RHPortraitRenderer006212d0()
{
    m_vptr = 0x0067ae60;
    m_promptEnabled = false;
}
DECOMP_SIZE_ASSERT(RHPortraitText0061db10, 0x48)
DECOMP_SIZE_ASSERT(SBUIInputFieldCharacter, 0x08)

// Parked: folded payload-construction callee and initializer-slot scheduling differ.
// STUB: GAME 0x0061db10
RHPortraitText0061db10::RHPortraitText0061db10()
    : m_font(0), m_alternate(0), m_caretShown(false), m_maximum((unsigned int)-1)
{
    SBUIInputFieldCharacter value;
    value.character = 0;
    value.width = 0;
    m_characters.insert(m_characters.begin(), value);
    m_cursor = m_characters.begin();
}

// SYNTHETIC: GAME 0x0061dc00
// ??_GRHPortraitText0061db10@@UAEPAXI@Z

// FUNCTION: GAME 0x0061dc20
RHPortraitText0061db10::~RHPortraitText0061db10()
{
}
void RHPortraitTextLinkedCalls::FUN_0053f9f0(void *) {}
unsigned SBUIInputFieldTextUnk::FUN_0061dd30() { return 0; }
