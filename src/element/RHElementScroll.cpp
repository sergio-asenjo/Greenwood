#include "RHElementScroll.h"
#include "VMCore.h"

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

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

class RHUnkTargetSprite
{
public:
    bool FUN_005b76e0(unsigned animation, unsigned short direction);
};

DECOMP_SIZE_ASSERT(RHElementObject, 0x100)
DECOMP_SIZE_ASSERT(RHScrollScript, 0x60)
DECOMP_SIZE_ASSERT(RHScrollUnk0040ee30, 0x14)
DECOMP_SIZE_ASSERT(RHElementScroll, 0x170)

// GLOBAL: GAME 0x006c09ec
RHElementScroll *g_scrollExecutingScript;

// FUNCTION: GAME 0x0040ee30
RHScrollUnk0040ee30::~RHScrollUnk0040ee30()
{
}

// FUNCTION: GAME 0x004b9f40
bool RHElementScroll::FUN_004b9f40()
{
    if (m_12)
    {
        if (m_100.m_58)
        {
            if (++m_168 == 25)
            {
                SetScrollExecutingScript(this);
                ((RHUnk00404860 *)&m_160)->FUN_00404960(0);
                ResetScrollExecutingScript();
                m_168 = 0;
            }
        }
        ((RHScrollSpriteRefreshCalls *)Info())->FUN_005b7f60(0);
    }
    return true;
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
            RHUnkSectorScript *script = (RHUnkSectorScript *)&m_100;
            script->Unk00639a30(name);
            m_160 = this ? script : 0;
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
bool RHElementScroll::FUN_004ba470(void *first, void *second, void *third)
{
    if (!m_12 || second == 0 || *(unsigned int *)((char *)g_pEngine + 0x4a00) > 1)
        return false;
    if (m_164 != 1 && m_164 != 3)
        return false;
    void *last = third;
    return ((RHScrollObjectCalls *)this)->FUN_004b23c0(first, second, last);
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
    int result = ((RHUnk00404860 *)((char *)this + 0x160))->FUN_00404860(value);
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
int RHElementScroll::FUN_004ba580(unsigned long first, unsigned long second,
                                   unsigned long third, unsigned long fourth) const
{
    int status = m_164;
    if (status != 1 && status != 3)
        return false;
    int result = ((const RHScrollObjectCalls *)this)->FUN_004b2b60(first, second, third, fourth);
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
        ((RHUnk004a7150 *)element)->FUN_004a7150(0xa, 0, 1);
    ((RHUnk00462730 *)element)->FUN_00462730(this, 0);
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(element, 0, 1);
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
    if (file.m_version > 7 && g_unk0x6c0691 && m_100.m_58)
        m_100.FUN_006348f0(file);
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

void RHElementScroll::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
    Serialize(file);
    SetScrollExecutingScript(this);
    FUN_004ba400();
    ((RHUnk004ba7a0 *)this)->Set(0);
    ((RHScrollUnk0040ee30 *)this)->~RHScrollUnk0040ee30();
}
