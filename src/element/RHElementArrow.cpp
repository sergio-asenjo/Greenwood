// RHElementArrow.cpp — translation unit with __FILE__ evidence at
// 0x004a6e10 ("P:\Robin Hood\RHElementArrow.cpp",
// symbols/functions-by-file.tsv).
//
// BINDING (0x004a6e10 -> RHElementArrow::Serialize(SBFile&)):
//   - TU:        rhelementarrow.cpp (embedded __FILE__ string 0x006ae978).
//   - Class:     RHElementArrow (symbols/oracle-correlation.tsv:
//                rhelementarrow -> class RHElementArrow, 18 methods).
//   - Method:    RHElementArrow::Serialize(SBFile&) — the Mac oracle's
//                rhelementarrow.cpp has exactly one such method
//                (symbols/mac-functions-by-file.tsv, symbols/mac-RH.txt:1764).
//   - Signals:
//       * the function first writes the tag "RHElementArrow" (string
//         0x006ae99c) via 0x005e1b70 — the name matches the TU's class;
//       * it then calls the base 0x004b7500 with `this` unchanged and returns
//         false immediately if it fails; 0x004b7500 writes the tag
//         "RHElementProjectile" — i.e. RHElementProjectile::Serialize is
//         invoked on the same object;
//       * on success it calls 0x00450370 on this+0x15c — the RHBow analogue of
//         the already-matched RHSword::SerializePointer (0x00450370's __FILE__
//         is P:\Robin Hood\RHBow.cpp), i.e. a pointer field at +0x15c;
//       * SEVEN SBFile::Access 0x005f52b0 checks: this+0x160/1, +0x161/1,
//         +0x162/1, +0x163/1 at lines 379..382, +0x164/2 at line 383, then the
//         file.m_bLoading gate (mov al,[esi+4]; test; je) selecting +0x166/1 at
//         line 387 (read) or line 391 (write) — the exact serializer idiom seen
//         in RHElementPurse / RHElementWaspNest;
//       * no loop and no `new`.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHElementArrow.h"

// FUNCTION: GAME 0x004a6640
char RHElementArrow::FUN_004a6640()
{
    return m_161;
}

#include "RHUnk00613e90.h"
#include "RHUnk005fc3b0.h"

// GLOBAL: GAME 0x00678318
double g_unk0x00678318 = 57.295777918682042;

struct RHArrowTrajectoryNode
{
    RHArrowTrajectoryNode *next;
    RHArrowTrajectoryNode *previous;
    RHUnk00613e90 *position;
};

// STUB: GAME 0x004a66f0
void RHElementArrow::GetOrientations(unsigned char &heading, short &pitch)
{
    RHUnk00613e90 current;
    RHUnk00613e90 next;
    RHUnk00613e90 delta;
    SBGeoVector2D direction;
    if (*(int *)((char *)this + 0x140) > 0)
    {
        current = *(RHUnk00613e90 *)(*(char **)((char *)this + 0x50) + 0x10);
        next = *(*(RHArrowTrajectoryNode **)((char *)this + 0x13c))->next->position;
        delta = next;
        delta.x -= current.x;
        delta.y -= current.y;
        delta.z -= current.z;
        float scale = 1.0f / delta.Norm();
        delta.x = scale * delta.x;
        delta.y = scale * delta.y;
        delta.z = scale * delta.z;
        float x = delta.x;
        float y = delta.y;
        direction.m_x = x;
        direction.m_y = y;
        heading = ((RHUnk005fc3b0 &)direction).FUN_005fcc50(0.57357645f);
        ((RHUnk005fc3b0 &)direction).Unk005fc6a0(1.0f);
        pitch = (short)(acos(((RHUnk005fc3b0 &)direction).Unk005fc6a0(1.0f)) * g_unk0x00678318);
        if (pitch > 60)
            pitch = 60;
        if (delta.z < 0.0f)
            pitch = -pitch;
        m_163 = heading;
        m_164 = pitch;
        return;
    }
    else
    {
        heading = m_163;
        pitch = m_164;
    }
}

#include "RHSequenceInteractionAction.h"

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

class RHScriptBatchCalls
{
public:
    unsigned int Unk004baea0();
    void *Unk0058a940(void *context, int value, void *element);
};

#include "RHBonusInfo.h"

class RHArrowMotionCalls
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
    virtual void V48() = 0;
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c() = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78() = 0;
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88(const RHUnk00613e90 &position, const RHUnk00613e90 &velocity) = 0;
};

#include "RHSequenceTimedCalls.h"
#include "RHMalignityStimulus.h"
#include "RHMalignityPosition.h"
#include "RHArtificialIntelligenceCore.h"

class RHArrowHumanCalls : public RHArrowMotionCalls
{
public:
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4() = 0;
    virtual void Vc8() = 0;
    virtual void Vcc() = 0;
    virtual void Vd0() = 0;
    virtual void Vd4() = 0;
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec() = 0;
    virtual void Vf0() = 0;
    virtual void Vf4() = 0;
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual bool V10c(RHElementArrow *arrow) = 0;
};

// STUB: GAME 0x004a68e0
bool RHElementArrow::HitHuman(RHElementActorHuman *target)
{
    bool result;
    if (!m_161)
    {
        if (!((RHArrowHumanCalls *)target)->Vf8() ||
            (unsigned char)(*(unsigned *)((char *)target + 4) & 15) != 4)
        {
            if (((RHArrowHumanCalls *)target)->V10c(this))
            {
                RHUnk005861c0 *action = new RHUnk005861c0(1, 0x28, target, InteractionTarget(), (void *)this,
                    (unsigned short)m_bow->FUN_004502e0(m_160 == 0));
                ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, action);
                if ((unsigned char)(*(unsigned *)((char *)target + 4) & 15) == 4)
                {
                    RHArtificialIntelligence *ai = (RHArtificialIntelligence *)((char *)target + 0x49c +
                        (*(int **)((char *)target + 0x49c))[1]);
                    RHMalignityStimulus stimulus;
                    stimulus.m_20 = 0x20;
                    stimulus.m_type = 2;
                    *(RHMalignityPosition *)stimulus.m_00 = *(RHMalignityPosition *)((char *)this + 0x118);
                    ai->V24(&stimulus);
                }
                result = true;
            }
            else if ((unsigned char)(*(unsigned *)((char *)target + 4) & 15) == 12 ||
                (unsigned char)(*(unsigned *)((char *)target + 4) & 31) == 20)
            {
                FUN_004a6b80(target, false);
                m_166 = 1;
                return false;
            }
            else
                result = false;
        }
        else
            result = false;
    }
    else
        result = false;
    m_166 = 0;
    return result;
}

// FUNCTION: GAME 0x004a6a70
void RHElementArrow::FUN_004a6a70(void *target)
{
    if (!m_161)
        FUN_004a6b80(target, true);
    m_166 = 1;
}

// Parked: VC6 merges the early false return and reorders flag stores across return setup.
// STUB: GAME 0x004a6aa0
bool RHElementArrow::FUN_004a6aa0(void *target)
{
    if (!m_161)
    {
        if (((RHScriptBatchCalls *)target)->Unk004baea0() & 1)
        {
            RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x93, target, InteractionTarget());
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, action);
            m_166 = 0;
            return true;
        }
        else
        {
            FUN_004a6b80(target, false);
            m_166 = 1;
            return false;
        }
    }
    m_166 = 0;
    return false;
}

// FUNCTION: GAME 0x004a6b80
void RHElementArrow::FUN_004a6b80(void *, bool flag)
{
    RHUnk00613e90 velocity;
    RHUnk005fc3b0 direction;
    unsigned char heading;
    short pitch;
    GetOrientations(heading, pitch);
    m_160 = 0;
    m_161 = 1;
    if (flag)
    {
        m_162 = (heading + 4) & 15;
        direction.Unk005fcd40(m_162, 0.57357645f);
        velocity.Set(direction.m_x * 30.0f, direction.m_y * 30.0f, -20.0f);
    }
    else
    {
        m_162 = heading ^ 8;
        direction.Unk005fcd40(m_162, 0.57357645f);
        velocity.Set(direction.m_x * 30.0f, direction.m_y * 10.0f, 0.0f);
    }
    ((RHArrowMotionCalls *)this)->V88(*(RHUnk00613e90 *)(*(char **)((char *)this + 0x50) + 0x10), velocity);
    ((RHBonusInfoBase *)(*(char **)((char *)this + 0x50) + 4))->FUN_0055f290();
    ((RHArrowMotionCalls *)this)->V28();
}

// FUNCTION: GAME 0x004a6e10
bool RHElementArrow::Serialize(SBFile &file)
{
    // STRING: GAME 0x6ae99c
    RHSerializeName(file, "RHElementArrow");

    if (RHElementProjectile::Serialize(file))
    {
        RHBow::SerializePointer(file, m_bow);

        if (file.Access(&m_160, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x6ae978
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     379,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_161, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     380,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_162, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     381,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_163, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     382,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.Access(&m_164, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     "P:\\Robin Hood\\RHElementArrow.cpp",
                     383,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (file.m_bLoading)
        {
            if (file.m_version >= 0x10)
            {
                if (file.Access(&m_166, 1) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0,
                             "P:\\Robin Hood\\RHElementArrow.cpp",
                             387,
                             "Serialize failed reason is %s",
                             reason);
                    return false;
                }
                return true;
            }
        }

        if (!file.m_bLoading)
        {
            if (file.Access(&m_166, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHElementArrow.cpp",
                         391,
                         "Serialize failed reason is %s",
                         reason);
                return false;
            }
        }

        return true;
    }

    return false;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementArrow::Serialize in the build.
// FUNCTION: GAME 0x004a6ff0
int RHElementArrow::FUN_004a6ff0()
{
    if (m_166 == 1 && !m_161)
        return 0x1fe;
    return -1;
}

void RHElementArrow::Emit(SBFile &file)
{
    Serialize(file);
}
