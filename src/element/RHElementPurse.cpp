// RHElementPurse.cpp — translation unit with __FILE__ evidence at 0x004b9830
// ("P:\Robin Hood\RHElementPurse.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x004b9830 -> RHElementPurse::Serialize(SBFile&)):
//   - TU:        rhelementpurse.cpp (embedded __FILE__ string 0x006aed9c).
//   - Class:     RHElementPurse (symbols/oracle-correlation.tsv:
//                rhelementpurse -> class RHElementPurse, 14 methods).
//   - Method:    RHElementPurse::Serialize(SBFile&) — the Mac oracle's
//                rhelementpurse.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x000d8ca4 Serialize).
//   - Signals:
//       * the function's first act writes the tag "RHElementPurse" (string
//         0x006aedc0) via 0x005e1b70 — the name matches the TU's class;
//       * SBFile::Access 0x005f52b0 on this+0x168 (size 2) with the
//         "Serialize failed reason is %s" assert pattern (format 0x006a7390,
//         empty fallback 0x006773d0) — the exact serializer idiom seen in
//         RHSword::SerializePointer;
//       * the tail is a direct call to 0x004b7500 with `this` unchanged, and
//         0x004b7500 is the rhelementprojectile.cpp function that first writes
//         the tag "RHElementProjectile" (string 0x006aed88) — i.e. the base
//         RHElementProjectile::Serialize is invoked last on the same object.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities. The
// base's tag 0x006aed88 / __FILE__ belong to rhelementprojectile.cpp and are
// deliberately not annotated here.)

#include "SBNullstr.h"
#include "RHElementPurse.h"
#include "RHEngineWidenedCalls.h"
#include "RHUnkTargetSpriteCalls.h"
#include "RHEngineSerializationCalls.h"
#include "RHProjectileSoundCalls.h"
#include <list>
#include <algorithm>

class RHEngine;
extern RHEngine *g_pEngine;
class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

DECOMP_SIZE_ASSERT(RHElementPurse, 0x16c)

// FUNCTION: GAME 0x0049d390
RHElementPurse::~RHElementPurse()
{
}

// FUNCTION: GAME 0x004b90f0
RHElementPurse::RHElementPurse(void *victim) : RHProjectileLifetime(4, victim), m_unk168(0)
{
    *(unsigned long *)this = 0x00678800;
    *(unsigned long *)((char *)this + 0xb0) = 7;
}

// FUNCTION: GAME 0x004b9180
void *RHElementPurse::FUN_004b9180(unsigned flags)
{
    this->~RHElementPurse();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004b9200
int RHElementPurse::FUN_004b9200()
{
    return 506;
}

// FUNCTION: GAME 0x004b9210
int RHElementPurse::FUN_004b9210()
{
    return 7;
}

// FUNCTION: GAME 0x004b97c0
bool RHElementPurse::FUN_004b97c0()
{
    if (*((char *)this + 0x132)) {
        bool result = ((RHProjectileRefreshCalls *)this)->FUN_004b82e0();
        (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(3);
        return result;
    }
    RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50);
    if (*(unsigned *)((char *)sprite + 0x1dc) != 0xc5 && *(unsigned *)((char *)this + 0xb4) != 0xc5) {
        *(unsigned *)((char *)this + 0xb4) = 0xc5;
        sprite->FUN_005bd450();
        (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    }
    (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(8);
    return true;
}

// FUNCTION: GAME 0x004b9830
bool RHElementPurse::Serialize(SBFile &file)
{
    // STRING: GAME 0x6aedc0
    RHSerializeName(file, "RHElementPurse");

    if (file.Access(&m_unk168, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6aed9c
                 "P:\\Robin Hood\\RHElementPurse.cpp",
                 240,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    return ((RHElementProjectile *)this)->RHElementProjectile::Serialize(file);
}

// FUNCTION: GAME 0x004b98a0
unsigned short RHElementPurse::FUN_004b98a0()
{
    std::list<RHElementCoin *> &coins = *(std::list<RHElementCoin *> *)((char *)this + 0x15c);
    unsigned short amount = 0;
    for (std::list<RHElementCoin *>::iterator coin = coins.begin(); coin != coins.end(); ++coin) {
        if (*((char *)*coin + 0x12)) {
            amount += 10;
            ((RHEngineSerializationCalls *)g_pEngine)->FUN_004d88e0(*coin, 0, 1);
        }
    }
    coins.clear();
    return amount;
}

struct RHPurseCoinNode
{
    RHPurseCoinNode *next;
    RHPurseCoinNode *prev;
    RHElementCoin *data;
};

struct RHPurseCoinList
{
    char allocator;
    RHPurseCoinNode *head;
    unsigned count;
};

// FUNCTION: GAME 0x004b9920
void RHElementPurse::AddChild(RHElementCoin *coin)
{
    std::list<RHElementCoin *> &coins = *(std::list<RHElementCoin *> *)((char *)this + 0x15c);
    if (std::find(coins.begin(), coins.end(), coin) == coins.end())
    {
        RHPurseCoinList &list = *(RHPurseCoinList *)((char *)this + 0x15c);
        RHPurseCoinNode *next = list.head;
        RHPurseCoinNode *previous = next->prev;
        RHPurseCoinNode *node = (RHPurseCoinNode *)::operator new(sizeof(RHPurseCoinNode));
        node->next = next ? next : node;
        node->prev = previous ? previous : node;
        next->prev = node;
        node->prev->next = node;
        new (&node->data) RHElementCoin *(coin);
        ++list.count;
    }
}

// FUNCTION: GAME 0x004b9990
void RHElementPurse::FUN_004b9990()
{
    char *sprite = *(char **)((char *)this + 0x50);
    int sound;
    switch (*(unsigned *)(sprite + 0xfc)) {
    case 0:
        sound = 0x1e1;
        break;
    case 1:
        sound = 0x1f4;
        break;
    case 2:
        sound = 0x1ed;
        break;
    case 7:
        sound = 0x1e7;
        break;
    default:
        sound = 0x1da;
        break;
    }
    ((RHSound *)g_unk0x006c1070)->FUN_005a8070(sound, *(const SBGeoPoint2D *)(sprite + 0x24), 9);
}

// Force emission: RHSword-style serializers are pulled in only when
// referenced; this non-inlinable out-of-line call keeps Serialize in the build.
void RHElementPurse::Emit(SBFile &file)
{
    FUN_004b9180(0);
    FUN_004b9200();
    FUN_004b9210();
    FUN_004b97c0();
    FUN_004b98a0();
    AddChild(0);
    FUN_004b9990();
    RHElementPurse::Serialize(file);
}
