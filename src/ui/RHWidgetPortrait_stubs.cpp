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

// FUNCTION: GAME 0x0049f510
char RHUnk005d73d0Actor::FUN_0049f510()
{
    return *(char *)((char *)*(void **)((char *)this + 0x600) + 0x16);
}
void RHWidgetPortrait::FUN_005d9c30() {}
RHPortraitRenderer005ca330::RHPortraitRenderer005ca330() {}
RHPortraitRenderer005ca330::~RHPortraitRenderer005ca330() {}
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

class RHPortraitRenderer0060dad0
{
public:
    ~RHPortraitRenderer0060dad0();
};

class RHPortraitRenderer0060da10
{
public:
    ~RHPortraitRenderer0060da10();
};

class RHPortraitRenderer0060d470
{
public:
    RHPortraitRenderer0060d470();
    ~RHPortraitRenderer0060d470();
};

RHPortraitRenderer0060dad0::~RHPortraitRenderer0060dad0() {}
RHPortraitRenderer0060da10::~RHPortraitRenderer0060da10() {}
RHPortraitRenderer0060d470::~RHPortraitRenderer0060d470() {}
RHPortraitRenderer0060d470::RHPortraitRenderer0060d470() {}

class RHUnk005490a0Message
{
public:
    RHUnk005490a0Message(int command, int value);
    ~RHUnk005490a0Message();
    char data[0x10];
};

struct RHPortraitQuickEntry
{
    ~RHPortraitQuickEntry();
};

RHPortraitQuickEntry::~RHPortraitQuickEntry() {}

class RHPortraitPCList
{
public:
    void FUN_005c8e40(unsigned index);
};

void RHPortraitPCList::FUN_005c8e40(unsigned) {}
RHPortraitUnk005cf320::~RHPortraitUnk005cf320() {}
RHPortraitUnk005cf570::~RHPortraitUnk005cf570() {}
RHPortraitUnk005d0180::~RHPortraitUnk005d0180() {}
void RHPortraitInputRenderer::FUN_0061d570(unsigned short, int) {}
unsigned RHPortraitInputRenderer::FUN_0061d5e0() { return 0; }
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d3f0(unsigned short, int) { return SBGeoBoundingBox2D(); }
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d7c0() { return SBGeoBoundingBox2D(); }
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d620() { return SBGeoBoundingBox2D(); }
unsigned RHPortraitInputRenderer::FUN_0061d950() { return 0; }
bool RHPortraitInputCalls::FUN_005cfc30(const void *) { return false; }
RHPortraitRenderer006212d0::RHPortraitRenderer006212d0() {}
RHPortraitRenderer006212d0::~RHPortraitRenderer006212d0() {}
RHPortraitText0061db10::RHPortraitText0061db10() {}
RHPortraitText0061db10::~RHPortraitText0061db10() {}
void RHPortraitTextLinkedCalls::FUN_0053f9f0(void *) {}
unsigned SBUIInputFieldTextUnk::FUN_0061dd30() { return 0; }
unsigned FUN_005fb1d0(unsigned key) { return key; }
int FUN_005fb0f0(unsigned, unsigned short *, const void *, unsigned) { return 0; }
void *RHPortraitTextResourceCalls::FUN_0053be80(const std::string &) { return 0; }
