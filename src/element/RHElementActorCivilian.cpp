// RHElementActorCivilian.cpp — translation unit with __FILE__ evidence at
// 0x004711c0 ("P:\Robin Hood\rhelementactorcivilian.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004711c0 -> RHElementActorCivilian::Serialize(SBFile&)):
//   - TU:        rhelementactorcivilian.cpp (embedded __FILE__ string
//                0x006ae370).
//   - Class:     RHElementActorCivilian (symbols/oracle-correlation.tsv:
//                rhelementactorcivilian -> class RHElementActorCivilian,
//                35 methods).
//   - Method:    RHElementActorCivilian::Serialize(SBFile&) — the Mac oracle's
//                rhelementactorcivilian.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x00087798 Serialize).
//   - Signals:
//       * the function first calls the base 0x0048b5d0 with `this` unchanged
//         and returns false immediately if it fails; 0x0048b5d0 writes the tag
//         "RHElementActorNPC" (string 0x006ae5cc) — i.e. the base
//         RHElementActorNPC::Serialize is invoked first on the same object;
//       * on success it writes the tag "RHElementActorCivilian" (string
//         0x006ae454) via 0x005e1b70 — the name matches the TU's class;
//       * then ONE SBFile::Access 0x005f52b0 on this+0x704 (size 4) with the
//         "Serialize failed reason is %s" assert pattern (format 0x006a7390,
//         empty fallback 0x006773d0) at line 753 (0x2f1) — the exact serializer
//         idiom seen in RHElementPurse;
//       * no loop and no `new`.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "RHElementActorCivilian.h"
#include "RHElementActorHumanCore.h"

#ifndef RHMOBILEUNK00607DA0_VIEW
#define RHMOBILEUNK00607DA0_VIEW
class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};
#endif

DECOMP_SIZE_ASSERT(RHElementActorNPC, 0x704)
DECOMP_SIZE_ASSERT(RHElementActorCivilian, 0x70c)
DECOMP_SIZE_ASSERT(RHCivilianProfileView, 0x34)
DECOMP_SIZE_ASSERT(RHCivilianSpriteView, 0x19e)
DECOMP_SIZE_ASSERT(RHUnk005ef320, 0x10e)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(std::vector<unsigned short>, 0x10)
DECOMP_SIZE_ASSERT(RHCampaignProfiles, 0x70)

class RHUnk006c0838
{
public:
    void FUN_0045ab50();
};

// GLOBAL: GAME 0x006c0838
RHUnk006c0838 g_unk0x6c0838;

void RHUnk006c0838::FUN_0045ab50()
{
}

// LIBRARY: GAME 0x00471050
void FUN_00471050()
{
    g_unk0x6c0838.FUN_0045ab50();
}

// FUNCTION: GAME 0x00470180
unsigned short RHElementActorCivilian::FUN_00470180()
{
    return 0;
}

// FUNCTION: GAME 0x00470190
void RHElementActorCivilian::FUN_00470190(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned)
{
}

// FUNCTION: GAME 0x004701a0
char RHElementActorCivilian::FUN_004701a0()
{
    void *table = RHCivilianField<void *>(this, 0x49c);
    unsigned offset = RHCivilianField<unsigned>(table, 4);
    return RHCivilianField<char>((char *)this + offset, 0x4c0);
}

#include "RHArtificialIntelligenceCore.h"

// FUNCTION: GAME 0x004701c0
void RHElementActorCivilian::FUN_004701c0(int remark, unsigned flags)
{
    int *table = RHCivilianField<int *>(this, 0x49c);
    ((RHArtificialIntelligence *)((char *)this + table[1] + 0x49c))->Unk00418c40(remark, flags);
}

// FUNCTION: GAME 0x004701f0
int RHElementActorCivilian::FUN_004701f0()
{
    return RHCivilianField<int>(m_708, 0x38);
}

bool FUN_00470e30(unsigned int index);
bool FUN_00470350(const std::vector<unsigned short> &values);

// FUNCTION: GAME 0x00470310
bool RHElementActorCivilian::FUN_00470310()
{
    std::vector<unsigned short> *arrays =
        RHCivilianField<std::vector<unsigned short> *>(this, 0x700);
    std::vector<unsigned short> *last = arrays + 10;
    std::vector<unsigned short> *first = arrays + RHCivilianField<unsigned>(this, 0x704);
    int count = 0;
    for (; first != last; ++first)
        if (FUN_00470350(*first))
            ++count;
    return count != 0;
}

// FUNCTION: GAME 0x00470350
bool FUN_00470350(const std::vector<unsigned short> &values)
{
    int count = 0;
    std::vector<unsigned short>::const_iterator last = values.end();
    std::vector<unsigned short>::const_iterator it = values.begin();
    for (; it != last; ++it)
        if (FUN_00470e30(*it))
            ++count;
    return count != 0;
}

class RHSprite
{
public:
    int PerformAction(RHOrder *order, int animation, int progression, bool reset);
};

// FUNCTION: GAME 0x00470390
int RHElementActorCivilian::FUN_00470390(RHOrder *order)
{
    if (m_149)
        return 2;
    if (order)
    {
        int command = RHCivilianField<int>(order, 0x24);
        switch (command)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return RHCivilianField<RHSprite *>(this, 0x50)->PerformAction(order, 0, 0, false);
        case 0x108:
            return RHCivilianField<RHSprite *>(this, 0x50)->PerformAction(order, command, 0, false);
        case 0x109:
        {
            int result = RHCivilianField<RHSprite *>(this, 0x50)->PerformAction(order, 0x109, 0, false);
            if (result == 3)
                FUN_00471090();
            return result;
        }
        case 0x10a:
            return RHCivilianField<RHSprite *>(this, 0x50)->PerformAction(order, 0x10a, 0, false);
        }
        return RHElementActorNPC::FUN_0048d510(order);
    }
    return 3;
}

// FUNCTION: GAME 0x00470460
int RHElementActorCivilian::FUN_00470460()
{
    return RHCivilianField<int>(m_708, 0x34) == 0;
}

// Parked: scalar slots, geometry temporaries and named callees differ.
// STUB: GAME 0x00470480
void RHElementActorCivilian::FUN_00470480(SBFile &file)
{
    unsigned short mapX, mapY, projectionIndex, animationIndex, direction;
    unsigned flags, state, identifier;
    int profileIndex;
    file.Access(&mapX, 2);
    file.Access(&mapY, 2);
    file.Access(&flags, 4);
    file.Access(&state, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&animationIndex, 2);
    file.Access(&direction, 2);
    file.Access(&identifier, 4);
    file.Access(&profileIndex, 4);

    if (!g_unk0x6c0e84)
        g_unk0x6c0e84 = new RHCampaignProfiles;
    m_708 = RHCivilianField<RHCivilianProfileView **>(g_unk0x6c0e84, 0x64)[profileIndex];
    if (FUN_00470ce0())
    {
        RHCivilianField<unsigned short>(this, 0x98) = g_unk0x6c11d0->Unk(115, 40, 203);
        RHCivilianField<unsigned short>(this, 0x94) = g_unk0x6c11d0->Unk(115, 40, 203);
        RHCivilianField<unsigned short>(this, 0x96) = g_unk0x6c11d0->Unk(115, 40, 203);
    }
    void *status = RHCivilianField<void *>(this, 0x49c);
    unsigned statusOffset = RHCivilianField<unsigned>(status, 4);
    file.Access((char *)this + statusOffset + 0x4a4, 2);
    int value;
    file.Access(&value, 4);
    RHCivilianField<int>(this, 0x4f0) = value;
    if (FUN_00470ca0())
        FUN_00470a10(file);

    void *&info = RHCivilianField<void *>(this, 0x50);
    ((RHUnkTargetSprite *)info)->FUN_005bd050(
        !RHCivilianField<char>(g_pEngine, 0x4aa8),
        *(std::string *)m_708, *(std::string *)((char *)m_708 + 0x10), 0);
    void *global = RHCivilianField<void *>(this, 0x64);
    SBGeoVector2D extent(*RHCivilianField<SBGeoPoint2D *>(global, 0x4164));
    ((RHMobileUnk00607da0 *)&RHCivilianField<SBGeoBoundingBox2D>(info, 0x98))->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D(-extent, extent));
    RHCivilianField<unsigned short>(info, 0x94) = 0;
    RHCivilianField<unsigned long>(this, 0x54) =
        RHCivilianField<RHUnkFXDraw *>(this, 0x60)->Unk005e4ed0(
            ((RHCivilianSpriteView *)info)->FUN_005bdef0(),
            ((RHCivilianSpriteView *)info)->FUN_005bdf20(), 0, 0);
    RHCivilianField<unsigned long>(this, 0x58) =
        RHCivilianField<RHUnkFXDraw *>(this, 0x60)->Unk005e4ed0(
            ((RHCivilianSpriteView *)info)->FUN_005bdef0() + 6,
            ((RHCivilianSpriteView *)info)->FUN_005bdf20(), 0, 0);
    {
        SBGeoPoint2D position((float)mapX, (float)mapY);
        void *base = (char *)info + 4;
        RHCivilianField<SBGeoPoint2D>(base, 0x20) = position;
        SBGeoVector2D displacement(position);
        SBGeoBoundingBox2D *box = (SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)base)->Unk0055fa10(
            RHCivilianField<int>(base, 0x88));
        ((RHMobileUnk00607da0 *)&RHCivilianField<SBGeoBoundingBox2D>(base, 0xc0))->FUN_00607da0((const RHMobileUnk00607da0 &)box->FUN_006090d0(displacement));
        RHCivilianField<int>(base, 4) = 2;
    }
    RHCivilianField<unsigned short>(info, 0xde) = direction;
    RHCivilianField<void *>(info, 0xe0) = animationIndex == 0xffff
        ? RHCivilianField<void *>(global, 0x4184)
        : RHCivilianField<void **>(global, 0x4064)[animationIndex];
    RHBonusProjection *projection = projectionIndex == 0xffff ? 0
        : RHCivilianField<RHBonusProjection **>(global, 0x4144)[projectionIndex];
    if (projection)
    {
        if ((RHCivilianField<unsigned>(projection, 0) & 4) == 0)
            SBAssert(1, "P:\\Robin Hood\\rhelementactorcivilian.cpp", 359,
                // STRING: GAME 0x006ae404
                "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) not lying on projection area !",
                (short)RHCivilianField<float>(info, 0x24), (short)RHCivilianField<float>(info, 0x28));
        if (!RHCivilianField<SBGeoBoundingBox2D>(projection, 0x38).FUN_00608400(
                RHCivilianField<SBGeoPoint2D>(info, 0x24)))
            SBAssert(1, "P:\\Robin Hood\\rhelementactorcivilian.cpp", 363,
                // STRING: GAME 0x006ae39c
                "DA F\xc4LLT MIR NICHTS MEHR EIN ! Civilian (%d,%d) map position not lying in projection area screen box !",
                (short)RHCivilianField<float>(info, 0x24), (short)RHCivilianField<float>(info, 0x28));
    }
    ((RHBonusInfoBase *)((char *)info + 4))->FUN_0055fa20(projection);
    RHCivilianField<unsigned>(info, 0xfc) = identifier;
    ((RHBonusInfoBase *)((char *)info + 4))->FUN_0055f290();
    ((RHBonusInfo *)info)->FUN_005bd560(0, true);
    RHCivilianField<undefined4>(info, 0x2c) = RHCivilianField<undefined4>(info, 0x10);
    RHCivilianField<undefined4>(info, 0x30) = RHCivilianField<undefined4>(info, 0x14);
    RHCivilianField<undefined4>(info, 0x34) = RHCivilianField<undefined4>(info, 0x18);
    RHCivilianField<SBGeoPoint2D>(info, 0x40) = RHCivilianField<SBGeoPoint2D>(info, 0x24);
    RHCivilianField<unsigned short>(info, 0xd8) = flags & 15;
    RHCivilianField<unsigned short>(info, 0xda) = flags & 15;
    statusOffset = RHCivilianField<unsigned>(RHCivilianField<void *>(this, 0x49c), 4);
    RHCivilianField<unsigned>((char *)this + statusOffset, 0x4c4) = state;
    std::string script;
    unsigned char hasScript;
    file.Access(&hasScript, 1);
    if (hasScript)
    {
        FUN_005e0c90(file, script);
        if (g_unk0x6c0691 && script.size())
            ((RHElementActor *)this)->InitializeScript(script);
    }
}

// FUNCTION: GAME 0x00470a10
void RHElementActorCivilian::FUN_00470a10(SBFile &file)
{
    std::vector<unsigned short> *&arrays = *(std::vector<unsigned short> **)((char *)this + 0x700);
    arrays = new std::vector<unsigned short>[10];
    unsigned offset = 0;
    int remaining = 10;
    do
    {
        unsigned short count;
        file.Access(&count, 2);
        while (count != 0)
        {
            unsigned short value;
            file.Access(&value, 2);
            std::vector<unsigned short> &array = *(std::vector<unsigned short> *)((char *)arrays + offset);
            array.insert(array.end(), value);
            --count;
        }
        offset += 16;
    } while (--remaining != 0);
}

// LIBRARY: GAME 0x00470c80
// ??_F?$vector@GV?$allocator@G@std@@@std@@QAEXXZ

// FUNCTION: GAME 0x00470ca0
bool RHElementActorCivilian::FUN_00470ca0()
{
    return m_708->m_30 == 4;
}

// FUNCTION: GAME 0x00470cc0
bool RHElementActorCivilian::FUN_00470cc0()
{
    return m_708->m_30 == 3;
}

// FUNCTION: GAME 0x00470ce0
bool RHElementActorCivilian::FUN_00470ce0()
{
    return m_708->m_30 == 5;
}

bool RHCivilianVirtualBool(void *object, unsigned offset);

// Parked: branch helpers and the sprite receiver's exact callee are unresolved.
// STUB: GAME 0x00470d00
bool RHElementActorCivilian::FUN_00470d00(void *first, void *second, int kind)
{
    if (!RHCivilianField<char>(this, 0x12))
        return false;

    if (kind != 5 && kind != 0x10 && kind != 2 &&
        RHCivilianField<unsigned>(g_pEngine, 0x4a00) > 1)
        return false;

    if (kind == 3)
    {
        if (RHCivilianField<char>(this, 8) ||
            RHCivilianField<void *>(this, 0x500) ||
            !FUN_00470ca0() ||
            !RHCivilianVirtualBool(second, 0xf8))
            return false;

        unsigned action = RHCivilianField<unsigned>(RHCivilianField<void *>(this, 0x50), 0x1dc);
        return action != 0x108 && action != 0x109 && action != 0x10a;
    }

    if (kind == 0xf)
        return RHCivilianField<char>(this, 8) != 0;

    return true;
}

#define SBGeoPoint2D RHElemScrollPoint2D
#define SBGeoVector2D RHElemScrollVector2D
#define SBGeoBoundingBox2D RHElemScrollBoundingBox2D
#define RHUnkPathActorInfoBase RHElemScrollPathActorInfoBase
#define RHBonusInfoBase RHElemScrollBonusInfoBase
#define RHBonusInfo RHElemScrollBonusInfo
#include "RHElementScroll.h"
#undef RHBonusInfo
#undef RHBonusInfoBase
#undef RHUnkPathActorInfoBase
#undef SBGeoBoundingBox2D
#undef SBGeoVector2D
#undef SBGeoPoint2D

#include "../ui/RHMinimap.h"

// GLOBAL: GAME 0x006c09dc
RHElementScroll **g_unk0x6c09dc;

// FUNCTION: GAME 0x00470e30
bool FUN_00470e30(unsigned int index)
{
    RHElementScroll **scrolls = g_unk0x6c09dc;
    return scrolls[index]->IsRevealable();
}

#define RHCIVILIAN_VIRTUAL_BOOL(object, offset) \
    ((bool (__fastcall *)(void *))(*(void ***)object)[(offset) / 4])(object)

// Parked: allocation cleanup and helper-call entities remain unresolved.
// STUB: GAME 0x00470e50
bool RHElementActorCivilian::FUN_00470e50(void *first, void *second, int kind)
{
    if (RHCIVILIAN_VIRTUAL_BOOL(this, 0x48) ||
        RHCivilianField<char>(this, 0x1ce) ||
        RHCivilianField<void *>(this, 0x500) ||
        !FUN_00470ca0() ||
        !RHCIVILIAN_VIRTUAL_BOOL(second, 0xf8))
        return false;

    if (RHCivilianField<int>(g_pEngine, 0x4a00) <= 50)
        return false;

    void *event = ::operator new(0x68);
    if (!event)
        return false;

    RHCivilianField<void *>(event, 0) = first;
    RHCivilianField<void *>(event, 4) = this;
    RHCivilianField<void *>(event, 8) = second;
    RHCivilianField<unsigned>(event, 0x10) = kind;
    RHCivilianField<unsigned short>(this, 0x6fc) = 3;
    return true;
}

#undef RHCIVILIAN_VIRTUAL_BOOL

// GLOBAL: GAME 0x006c0c50
RHMinimap *g_unk0x6c0c50;

// FUNCTION: GAME 0x00471060
void FUN_00471060(unsigned int index)
{
    RHElementScroll **scrolls = g_unk0x6c09dc;
    RHMinimap *minimap = g_unk0x6c0c50;
    minimap->FUN_0054a440(scrolls[index]->FUN_004ba5d0());
}

// GLOBAL: GAME 0x006c0874
unsigned char g_unk0x6c0874;

bool RHCivilianVirtualBool(void *object, unsigned offset)
{
    void **vtable = *(void ***)object;
    typedef bool (__fastcall *Method)(void *);
    return ((Method)vtable[offset / 4])(object);
}

// Parked: virtual receivers and global helper calls remain source-shape approximations.
// STUB: GAME 0x00470f70
void *RHElementActorCivilian::FUN_00470f70(void *element)
{
    if ((g_unk0x6c0874 & 1) == 0)
    {
        g_unk0x6c0874 |= 1;
        g_unk0x6c0838.FUN_0045ab50();
    }

    if (RHCivilianVirtualBool(this, 0x48) ||
        RHCivilianField<char>(this, 0x1ce) ||
        !FUN_00470ca0() ||
        !RHCivilianVirtualBool(element, 0xf8))
        return 0;

    if (RHCivilianField<int>(g_pEngine, 0x4a00) <= 50)
        return 0;

    RHCivilianField<char>(this, 0x92) = 1;
    RHCivilianField<int>(this, 0xa0) = 0;
    RHCivilianField<unsigned short>(this, 0xa4) = 2;
    g_unk0x6c0838.FUN_0045ab50();
    return &g_unk0x6c0838;
}

// Parked: the list dispatch, status callback and transition-call schedule differ.
// STUB: GAME 0x00471090
void RHElementActorCivilian::FUN_00471090()
{
    unsigned &current = RHCivilianField<unsigned>(this, 0x704);
    if (current == 10)
    {
        g_unk0x6c0c50->FUN_00549f50();
        return;
    }

    std::vector<unsigned short> *arrays =
        RHCivilianField<std::vector<unsigned short> *>(this, 0x700);
    std::vector<unsigned short> &values = arrays[current];
    unsigned revealable = 0;
    for (std::vector<unsigned short>::iterator it = values.begin(); it != values.end(); ++it)
        if (FUN_00470e30(*it))
            ++revealable;

    unsigned message;
    unsigned duration = 10;
    if (revealable != 0)
    {
        for (std::vector<unsigned short>::iterator it = values.begin(); it != values.end(); ++it)
            FUN_00471060(*it);
        g_unk0x6c0c50->FUN_00549f50();
        message = FUN_00470310() ? 99 : 101;
    }
    else
        message = FUN_00470310() ? 100 : 102;

    (void)message;
    (void)duration;
    RHCivilianField<unsigned short>(this, 0x6fc) = 3;
    ++current;
}

// FUNCTION: GAME 0x004711c0
bool RHElementActorCivilian::Serialize(SBFile &file)
{
    if (!RHElementActorNPC::Serialize(file))
        return false;

    // STRING: GAME 0x6ae454
    RHSerializeName(file, "RHElementActorCivilian");

    if (file.Access(&m_unk704, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6ae370
                 "P:\\Robin Hood\\rhelementactorcivilian.cpp",
                 753,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return true;
}

class RHCivilianAdjustedReceiver
{
public:
    void FUN_00471590(unsigned char flags);
};

bool RHElementActorCivilian::FUN_004646e0(RHElementActorCivilian *) { return false; }

// FUNCTION: GAME 0x00471240
bool RHElementActorCivilian::FUN_00471240(RHElementActorCivilian *arg)
{
    unsigned type = RHCivilianField<unsigned>(arg, 0x10);
    if (!FUN_00470ca0() || type == 0x76 || type == 0x8f || type == 0xa1)
        return FUN_00475810(arg);
    return false;
}

// FUNCTION: GAME 0x00471280
void RHElementActorCivilian::GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third)
{
    if (*(int *)((char *)element + 0x10) != 0x76)
        RHElementActorNPC::GetTransitionFlags(element, first, second, third);
    else
        first = 1;
}

// FUNCTION: GAME 0x004712b0
int RHElementActorCivilian::FUN_004712b0(RHSoldierSequenceElement *element)
{
    int type = element->m_5c;
    if (type == 0xb)
    {
        if (element->m_10 != 0x76)
            return ((RHSoldierNPCCalls *)this)->FUN_0048d100(element);
        return 8;
    }
    return type;
}

// FUNCTION: GAME 0x00471400
void RHElementActorCivilian::FUN_00471400(int first, int second)
{
    if (!RHCivilianField<int>(this, 0x500))
        ((RHElementActorHuman *)this)->FUN_00471e50(first, second);
}

// FUNCTION: GAME 0x00471420
void RHElementActorCivilian::FUN_00471420(int first, int second)
{
    if (!RHCivilianField<int>(this, 0x500))
        ((RHElementActorHuman *)this)->FUN_0047e9a0(first, second);
}

// FUNCTION: GAME 0x00471590
void RHCivilianAdjustedReceiver::FUN_00471590(unsigned char flags)
{
    char *receiver = (char *)this + (*(int **)((char *)this - 0x250))[1] - 0x250;
    receiver[0x174] |= flags;
}

void EmitRHCivilianAdjustedReceiver(RHCivilianAdjustedReceiver *receiver, unsigned char flags)
{
    receiver->FUN_00471590(flags);
}

// FUNCTION: GAME 0x00485990
bool RHElementActorCivilian::FUN_00485990()
{
    if ((RHCivilianField<unsigned>(this, 4) & 0x1f) == 4)
        return FUN_00470ca0();
    return *(int *)(RHCivilianField<char *>(this, 0x50) + 0x8c) == 0x14;
}

// FUNCTION: GAME 0x005bdef0
unsigned short RHCivilianSpriteView::FUN_005bdef0()
{
    unsigned short width = m_19a;
    int remainder = (int)width % 4;
    if (remainder != 0)
        width += 4 - remainder;
    return width;
}

// FUNCTION: GAME 0x005bdf20
unsigned short RHCivilianSpriteView::FUN_005bdf20()
{
    return m_19c;
}

// FUNCTION: GAME 0x005ef320
unsigned short RHUnk005ef320::Unk(int red, int green, int blue)
{
    if (m_10c == 16)
        return (((((unsigned char)red & 0xf8) << 5) | ((unsigned char)green & 0xfc)) << 3) | ((unsigned)(unsigned char)blue >> 3);
    return (((((unsigned char)red & 0xf8) << 5) | ((unsigned char)green & 0xf8)) << 2) | ((unsigned)(unsigned char)blue >> 3);
}

// FUNCTION: GAME 0x005fc450
SBGeoVector2D SBGeoVector2D::operator-() const
{
    SBGeoVector2D opposite;
    opposite.m_x = -m_x;
    opposite.m_y = -m_y;
    return SBGeoVector2D(opposite);
}

// FUNCTION: GAME 0x00607ba0
SBGeoBoundingBox2D::SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    m_p0 = first;
    m_p1 = second;
    m_flag = true;
}

void RHElementActorCivilian::Emit(SBFile &file)
{
    FUN_00470180();
    FUN_00470190(0, 0, 0, 0, 0, 0, 0);
    FUN_004701a0();
    FUN_004701c0(0, 0);
    FUN_004701f0();
    FUN_00470460();
    FUN_00470cc0();
    Serialize(file);
    FUN_00470ca0();
    FUN_00470ce0();
    FUN_00471240(0);
    FUN_004712b0(0);
    FUN_00485990();
}

class RHCivilianVisibilityDispatch
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual bool V48() = 0;
};

// FUNCTION: GAME 0x00475810
bool RHElementActorCivilian::FUN_00475810(RHElementActorCivilian *arg)
{
    m_149 = 0;
    int kind = RHCivilianField<int>(arg, 0x10);
    if (((RHCivilianVisibilityDispatch *)this)->V48() || RHCivilianField<char>(this, 0x1ce) ||
        RHCivilianField<short>(this, 0x23c) != 0)
    {
        switch (kind)
        {
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x2a:
        case 0x2b:
        case 0x4a:
        case 0xa1:
            break;
        case 0x2c:
            if (((RHCivilianVisibilityDispatch *)this)->V48() || RHCivilianField<char>(this, 0x1ce) ||
                RHCivilianField<short>(this, 0x23c) != 1)
                return false;
            break;
        default:
            return false;
        }
    }
    bool result;
    if (kind == 0x23 && (RHCivilianField<unsigned>(this, 4) & 0xf) == 0xc)
    {
        switch (RHCivilianField<int>(RHCivilianField<void *>(this, 0x50), 0x1dc))
        {
        case 0x55:
        case 0x57:
        case 0x5a:
        case 0x5d:
        case 0x5e:
            result = false;
            ((RHElementActorHuman *)this)->FUN_00485d20((RHSequenceElement *)arg);
            goto done;
        }
    }
    result = FUN_004646e0(arg);
done:
    return result;
}
