#include "RHElementScroll.h"
#include "VMCore.h"
#include "RHElementScrollStaticStorage.h"
#include "RHUnk004ba8d0.h"
#include <algorithm>
#include <string.h>

extern "C" int __cdecl rand();

class RHSprite
{
public:
    unsigned short FUN_005bdcf0(unsigned short frame);
};

// FUNCTION: GAME 0x00404780
void RHUnk00404860::FUN_00404780()
{
    ((VMCore *)m_0)->FUN_00639300(&std::string("Initialize"));
}

// FUNCTION: GAME 0x00404860
int RHUnk00404860::FUN_00404860(unsigned long value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    // STRING: GAME 0x006a6ce0
    ((VMCore *)m_0)->FUN_00639300(&std::string("IsTaken"));
    int result;
    ((VMCore *)m_0)->FUN_00639360(result);
    return result;
}

// FUNCTION: GAME 0x00404960
void RHUnk00404860::FUN_00404960(int value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    ((VMCore *)m_0)->FUN_00639300(&std::string("Hourglass"));
}

class RHEngine;
extern RHEngine *g_pEngine;

#include "RHPlayerProfileAccess.h"

class RHUnkTargetSprite
{
public:
    bool FUN_005b76e0(unsigned animation, unsigned short direction);
};

DECOMP_SIZE_ASSERT(RHElementObject, 0x100)
DECOMP_SIZE_ASSERT(VMCoreCustom, 0x60)
DECOMP_SIZE_ASSERT(RHElementScroll, 0x170)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, m_12) == 0x12)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, m_50) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, m_member) == 0xbc)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, m_bound) == 0x158)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, RHUnk00404860::m_0) == 0x160)
DECOMP_STATIC_ASSERT(offsetof(RHElementScroll, m_164) == 0x164)

// GLOBAL: GAME 0x006c09ec
RHElementScroll *g_scrollExecutingScript;

// SYNTHETIC: GAME 0x0040ee30
// ??1SBGeoBoundingBox2D@@QAE@XZ

void *FUN_004b3120(int type);

// Parked: native folds the pointer-vector helpers into another instantiation; receiver register differs.
// STUB: GAME 0x004b9b70
RHElementScroll::RHElementScroll()
    : RHElementObject(0xb, false, 0), m_164(0), m_168(0), m_16f(0)
{
    m_b0 = 0xc;
    Create(true, *(const RHElementObject *)FUN_004b3120(0xc));
    RHElementScrollStaticStorage::aAllScrolls.push_back(this);
    memset(m_16c, 0, sizeof(m_16c));
    ((RHUnk004ba7a0 *)this)->FUN_004ba7e0();
}

// SYNTHETIC: GAME 0x004b9e00
// RHElementScroll::`scalar deleting destructor'

// FUNCTION: GAME 0x004b9e20
RHElementScroll::~RHElementScroll()
{
    RHElementScrollStaticStorage::aAllScrolls.erase(
        std::remove(RHElementScrollStaticStorage::aAllScrolls.begin(), RHElementScrollStaticStorage::aAllScrolls.end(), this),
        RHElementScrollStaticStorage::aAllScrolls.end());
}

// FUNCTION: GAME 0x004b9f40
bool RHElementScroll::FUN_004b9f40()
{
    if (m_12)
    {
        if (m_bound)
        {
            if (++m_168 == 25)
            {
                SetScrollExecutingScript(this);
                FUN_00404960(0);
                ResetScrollExecutingScript();
                m_168 = 0;
            }
        }
        ((RHEngineWidenedCalls *)Info())->FUN_005b7f60(0);
    }
    return true;
}

// FUNCTION: GAME 0x004b9fa0
void RHElementScroll::FUN_004b9fa0()
{
    if (m_bound)
    {
        SetScrollExecutingScript(this);
        FUN_00404780();
        ResetScrollExecutingScript();
    }
    RHSprite *sprite = (RHSprite *)m_50;
    *(unsigned short *)((char *)sprite + 0x186) =
        rand() % sprite->FUN_005bdcf0(*(unsigned short *)((char *)sprite + 0x184));
}

#include "RHElementScrollStaticStorage.h"

// FUNCTION: GAME 0x004ba000
void FUN_004ba000()
{
    for (RHElementScroll **current = g_unk0x6c09dc; current != g_unk0x006c09e0; ++current)
        (*current)->FUN_004b9fa0();
}

// Parked: local coloring and projection-branch scheduling.
// STUB: GAME 0x004ba030
void RHElementScroll::InitializeFromMissionStream(SBFile &file)
{
    std::string unused;
    unsigned short x;
    unsigned short y;
    unsigned flags;
    unsigned value;
    unsigned short projectionIndex;
    unsigned short index;
    unsigned short layer;
    char taken;
    char scripted;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&flags, 4);
    file.Access(&value, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&index, 2);
    file.Access(&layer, 2);
    file.Access(m_16c, 3);
    file.Access(&m_16f, 1);
    file.Access(&taken, 1);
    if (taken)
        ((RHUnk004ba7a0 *)this)->Set(1);
    file.Access(&scripted, 1);
    if (scripted)
    {
        std::string name;
        FUN_005e0c90(file, name);
        if (name.empty())
            SBAssert(1,
                     // STRING: GAME 0x006aedd0
                     "P:\\Robin Hood\\RHElementScroll.Cpp", 101,
                     // STRING: GAME 0x006ae798
                     "Script error: a scripted object had no valid script class name.");
        if (g_unk0x6c0691 == 1)
        {
            RHUnkSectorScript *script = (RHUnkSectorScript *)((char *)this + 0x100);
            script->Unk00639a30(name);
            RHUnk00404860::m_0 = this ? script : 0;
        }
    }
    Info()->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    Info()->m_4.m_da = layer;
    Info()->m_e0 = index == 0xffff ? Global()->m_4184 : Global()->m_4064[index];
    RHBonusProjection *projection;
    if (projectionIndex != 0xffff)
        projection = Global()->m_4144[projectionIndex];
    else
        projection = 0;
    if (projection != 0)
    {
        if (!(projection->Flags() & 1))
            SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 245,
                      "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) not lying on projection area !",
                     Info()->X(), Info()->Y());
        if (!projection->Inside(Info()->m_4.m_20))
            SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 249,
                      "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) map position not lying in projection area screen box !",
                     Info()->X(), Info()->Y());
    }
    Info()->m_4.FUN_0055fa20(projection);
    Info()->m_4.FUN_0055f290();
    Info()->FUN_005bd560(0, true);
    Info()->m_4.m_28 = Info()->m_4.m_c;
    Info()->RestorePoint();
    Info()->m_4.SetFlags(flags & 0xf);
    FUN_004ba400();
}

// Parked: VC6 hoists the shared pop edi/esi above the branch; target pops after each call.
// STUB: GAME 0x004ba400
void RHElementScroll::FUN_004ba400()
{
    char *profile = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    if ((unsigned char)FUN_004ba550())
        m_12 = 1;
    else
        m_12 = m_16c[*(int *)(profile + 0x1c)];
    RHBonusInfo *info = Info();
    if (m_16f)
        ((RHUnkTargetSprite *)info)->FUN_005b76e0(0xbf, *(unsigned short *)((char *)info + 0xd8));
    else
        ((RHUnkTargetSprite *)info)->FUN_005b76e0(0xbe, *(unsigned short *)((char *)info + 0xd8));
}

// FUNCTION: GAME 0x004ba470
bool RHElementScroll::FUN_004b23c0(const void *first, void *second, int third)
{
    if (!m_12 || second == 0 || *(unsigned int *)((char *)g_pEngine + 0x4a00) > 1)
        return false;
    if (m_164 != 1 && m_164 != 3)
        return false;
    int last = third;
    return RHElementObject::FUN_004b23c0(first, second, last);
}

// FUNCTION: GAME 0x004ba4c0
bool RHElementScroll::IsRevealable() const
{
    return m_12 && m_164 == 0;
}

// FUNCTION: GAME 0x004ba4e0
bool RHElementScroll::FUN_004ba4e0(unsigned long value)
{
    RHBonusInfo *info = Info();
    m_164 = 3;
    ((RHUnkTargetSprite *)info)->FUN_005b76e0(0xc0, *(unsigned short *)((char *)info + 0xd8));
    if (!*(char *)((char *)this + 0x158))
        return false;
    SetScrollExecutingScript(this);
    int result = FUN_00404860(value);
    ResetScrollExecutingScript();
    if (result)
    {
        m_164 = 2;
        ((RHUnk004ba7a0 *)this)->FUN_004ba7e0();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004ba550
int RHElementScroll::FUN_004ba550()
{
    char *profile = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    int index = *(int *)(profile + 0x1c);
    if (index == 0)
    {
        if (!m_16c[index])
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x004ba580
void *RHElementScroll::Refresh(unsigned long surface, float value,
                               const SBGeoBoundingBox2D &box, unsigned long flags)
{
    int status = m_164;
    if (status != 1 && status != 3)
        return 0;
    void *result = RHElementObject::Refresh(surface, value, box, flags);
    return result;
}

// FUNCTION: GAME 0x004ba5c0
void RHElementScroll::ResetScrollExecutingScript()
{
    g_scrollExecutingScript = 0;
}

// Parked: helper entities and allocation/EH cleanup shape differ.
// STUB: GAME 0x004ba5d0
void *RHElementScroll::FUN_004ba5d0()
{
    if (!IsRevealable())
    {
        ((RHUnk004ba7a0 *)this)->Set(1);
        return this;
    }
    if (!(unsigned char)FUN_004ba550())
    {
        ((RHUnk004ba7a0 *)this)->Set(1);
        return this;
    }
    void *element = operator new(0x100);
    if (element != 0)
        ((RHElementBonus *)element)->RHElementBonus::RHElementBonus((RHElementBonus::BonusType)0xa, false, 1);
    ((RHUnk00462730 *)element)->FUN_00462730(this, 0);
    g_pEngine->AddElement((RHElement *)element, false, true);
    ((RHUnk004ba7a0 *)this)->Set(2);
    return element;
}

// FUNCTION: GAME 0x004ba690
bool RHElementScroll::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006aedf4
                    "RHElementScroll");
    if (file.Access(&m_164, 4) < 0)
    {
        SBString *err = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementScroll.Cpp", 497,
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : "");
        return false;
    }
    if (file.Access(&m_168, 4) < 0)
    {
        SBString *err = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementScroll.Cpp", 498,
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : "");
        return false;
    }
    if (file.m_version > 7 && g_unk0x6c0691 && m_bound)
        VMCore::SerializeMemberVariable(file);
    return RHElementObject::Serialize(file);
}

// FUNCTION: GAME 0x004ba760
void RHElementScroll::SetScrollExecutingScript(RHElementScroll *scroll)
{
    if (g_scrollExecutingScript)
        SBAssert(1, "P:\\Robin Hood\\RHElementScroll.Cpp", 525,
                 // STRING: GAME 0x006aee04
                 "Fatal: two scrolls cannot execute script at the same time.");
    g_scrollExecutingScript = scroll;
}

// FUNCTION: GAME 0x004ba7a0
void RHUnk004ba7a0::Set(int status)
{
    *(int *)((char *)this + 0x164) = status;
    if (status == 3)
    {
        RHBonusInfo *info = *(RHBonusInfo **)((char *)this + 0x50);
        ((RHUnkTargetSprite *)info)->FUN_005b76e0(0xc0, *(unsigned short *)((char *)info + 0xd8));
    }
    FUN_004ba7e0();
}

// FUNCTION: GAME 0x004ba7e0
void RHUnk004ba7a0::FUN_004ba7e0()
{
    int status = *(int *)((char *)this + 0x164);
    if (status == 1 || status == 3)
        *(unsigned short *)((char *)this + 0x8c) = 1;
    else
        *(unsigned short *)((char *)this + 0x8c) = 0;
}

// SYNTHETIC: GAME 0x004ba840
// ??_ERHElementScroll@@WBFM@AEPAXI@Z

// FUNCTION: GAME 0x004ba8d0
RHUnk004ba8d0::RHUnk004ba8d0(void *victim) : RHProjectileLifetime(5, victim)
{
    *(unsigned *)this = 0x67890c;
    m_b0 = 6;
}

void EmitRHUnk004ba8d0(void *storage, void *victim)
{
    ((RHUnk004ba8d0 *)storage)->RHUnk004ba8d0::RHUnk004ba8d0(victim);
}

unsigned RHElementScroll::V68()
{
    return 0;
}

void RHElementScroll::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
    Serialize(file);
    SetScrollExecutingScript(this);
    FUN_004ba400();
    ((RHUnk004ba7a0 *)this)->Set(0);
}
