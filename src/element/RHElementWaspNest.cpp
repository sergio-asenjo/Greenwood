// RHElementWaspNest.cpp — translation unit with __FILE__ evidence at
// 0x004be1e0 ("P:\Robin Hood\RHElementWaspNest.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004be1e0 -> RHElementWaspNest::Serialize(SBFile&)):
//   - TU:        rhelementwaspnest.cpp (embedded __FILE__ string 0x006aef5c).
//   - Class:     RHElementWaspNest (symbols/oracle-correlation.tsv:
//                rhelementwaspnest -> class RHElementWaspNest, 11 methods).
//   - Method:    RHElementWaspNest::Serialize(SBFile&) — the Mac oracle's
//                rhelementwaspnest.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv: 0x000dced0 Serialize).
//   - Signals:
//       * the function first calls the base 0x004b7500 with `this` unchanged and
//         returns false immediately if it fails; 0x004b7500 writes the tag
//         "RHElementProjectile" — i.e. the base
//         RHElementProjectile::Serialize is invoked first on the same object;
//       * NO type tag is written by this function;
//       * the read path (file.m_bLoading != 0) checks a dword at file+0x10
//         against 0x10 and returns true when below, else ONE
//         SBFile::Access 0x005f52b0 on this+0x15c (size 4) at line 149 (0x95);
//       * the write path (file.m_bLoading == 0) does ONE
//         SBFile::Access 0x005f52b0 on this+0x15c (size 4) at line 153 (0x99);
//       * both use the "Serialize failed reason is %s" assert pattern (format
//         0x006a7390, empty fallback 0x006773d0);
//       * no loop and no `new`.
//
// The `// STRING:` marker pins this TU's __FILE__ literal to its original
// Game.exe address: the original is a fixed-base EXE, so its absolute string
// pointers carry no relocation records and reccmp cannot discover them by
// scanning. ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHElementWaspNest.h"
#include "RHProjectileSoundCalls.h"
#include "RHProjectileLifetime.h"
#include "RHElementWasp.h"
#include "RHEngineWidenedCalls.h"
#include "RHUnkTargetSpriteCalls.h"
#include "RHUnk004d8460Calls.h"

DECOMP_SIZE_ASSERT(RHElementProjectile, 0x15c)
DECOMP_SIZE_ASSERT(RHElementWaspNest, 0x160)

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

class __declspec(novtable) RHUnk004be050 : public RHProjectileLifetime
{
public:
    RHUnk004be050();
    unsigned int m_15c;
};

DECOMP_SIZE_ASSERT(RHUnk004be050, 0x160)

// FUNCTION: GAME 0x004be050
RHUnk004be050::RHUnk004be050() : RHProjectileLifetime(0, 0), m_15c(0)
{
    *(unsigned long *)this = 0x00678aa0;
    *(unsigned long *)((char *)this + 0xb0) = 11;
}

inline void RHSetWaspNestAnimation(RHElementWaspNest *nest, unsigned row)
{
    unsigned &current = *(unsigned *)((char *)nest + 0xb4);
    if (current != row)
    {
        RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)nest + 0x50);
        current = row;
        sprite->FUN_005bd450();
        (*(RHUnkTargetSprite **)((char *)nest + 0x50))->FUN_005b76e0(row, 0);
    }
}

// FUNCTION: GAME 0x004be0e0
void RHElementWaspNest::FUN_004be0e0()
{
    RHEngine *engine = g_pEngine;
    FUN_004b8230();
    RHSetWaspNestAnimation(this, 0xc5);
    int count = 20;
    do
    {
        RHUnk004bc4d0 *wasp = new RHUnk004bc4d0(this);
        ((RHUnk004bc5b0 *)wasp)->FUN_004bc5b0(1);
        ((RHUnk004d8460 *)engine)->FUN_004d8460(wasp, 0, 1);
        --count;
    } while (count != 0);
    m_unk15c = 20;
}

// FUNCTION: GAME 0x004be1a0
bool RHElementWaspNest::FUN_004be1a0()
{
    if (((RHProjectileRefreshCalls *)this)->FUN_004b82e0())
    {
        if (m_unk15c > 0)
        {
            void *sprite = *(void **)((char *)this + 0x50);
            ((RHSound *)g_unk0x006c1070)->FUN_005a8070(0x1fb, *(const SBGeoPoint2D *)((char *)sprite + 0x24), 9);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004be1e0
bool RHElementWaspNest::Serialize(SBFile &file)
{
    if (RHElementProjectile::Serialize(file))
    {
        if (file.m_bLoading)
        {
            if (file.m_version >= 0x10)
            {
                if (file.Access(&m_unk15c, 4) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0,
                             // STRING: GAME 0x6aef5c
                             "P:\\Robin Hood\\RHElementWaspNest.cpp",
                             149,
                             "Serialize failed reason is %s",
                             reason);
                    return false;
                }
                return true;
            }
        }

        if (!file.m_bLoading)
        {
            if (file.Access(&m_unk15c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHElementWaspNest.cpp",
                         153,
                         "Serialize failed reason is %s",
                         reason);
                return false;
            }
        }

        return true;
    }

    return false;
}

// FUNCTION: GAME 0x004be290
void RHElementWaspNest::WaspKilled()
{
    if (m_unk15c > 0)
        --m_unk15c;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementWaspNest::Serialize in the
// build.
void RHElementWaspNest::Emit(SBFile &file)
{
    RHUnk004be050 initialized;
    FUN_004be0e0();
    Serialize(file);
    WaspKilled();
}
