#include "RHElementFX.h"
#include "RHElementTarget.h"
#include "RHCopyPointers.h"
#include "../ai/RHFastFindArrayOps.h"
#include "VMCore.h"
#include "RHMalignityActorCalls.h"
#include "RHElementPositionCalls.h"
#include "RHUnk00613e90.h"
#include "RHHumanSequenceElement.h"
#include "RHSpriteLastFrameCalls.h"
#include "RHSpriteCore.h"
#include "RHMobileUnk006100e0.h"
#include <vector>
#include <new>
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHElementTarget, 0x18c)
DECOMP_SIZE_ASSERT(RHScript, 4)
DECOMP_SIZE_ASSERT(SBSimpleVirtualMachine, 0x5c)
DECOMP_SIZE_ASSERT(VMCoreCustom, 0x60)
DECOMP_STATIC_ASSERT(offsetof(RHElementTarget, m_15c) == 0x15c)
DECOMP_SIZE_ASSERT(std::vector<RHMobileUnk006100e0 *>, 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHElementTarget, m_16c) == 0x16c)

class RHElementActor;
extern RHElementActor *g_unk0x6c100c;
extern char g_unk0x6c0691;

unsigned FUN_004baeb0(void *actor);
int FUN_004baf00(volatile int type);

// FUNCTION: GAME 0x004034e0
int RHUnkTargetScriptRef::FUN_004034e0()
{
    ((VMCore *)m_0)->FUN_00639300(&std::string("Initialize"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004035d0
int RHUnkTargetScriptRef::FUN_004035d0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6bdc
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByApple"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004036d0
int RHUnkTargetScriptRef::FUN_004036d0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6bf0
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByArrow"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004037d0
int RHUnkTargetScriptRef::FUN_004037d0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c04
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByHand"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004038d0
int RHUnkTargetScriptRef::FUN_004038d0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c14
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByHeal"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004039d0
int RHUnkTargetScriptRef::FUN_004039d0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c24
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByLever"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00403ad0
int RHUnkTargetScriptRef::FUN_00403ad0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c38
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByMoney"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00403bd0
int RHUnkTargetScriptRef::FUN_00403bd0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c4c
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedBySearch"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00403cd0
int RHUnkTargetScriptRef::FUN_00403cd0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c60
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByStone"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00403dd0
int RHUnkTargetScriptRef::FUN_00403dd0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c74
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedBySword"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x00403ed0
int RHUnkTargetScriptRef::FUN_00403ed0(int activator)
{
    ((VMCore *)m_0)->FUN_006392e0(&activator, 4);
    // STRING: GAME 0x006a6c88
    ((VMCore *)m_0)->FUN_00639300(&std::string("ActivatedByListenable"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// Parked: counted unsigned-short sprite getters corrected; local-slot coloring and SetPoint temporaries remain.
// STUB: GAME 0x004bb820
void RHElementTarget::InitializeFromMissionStream(SBFile &file)
{
    std::string profile;
    std::string name;
    short x;
    short y;
    short z;
    unsigned flags;
    unsigned row;
    unsigned short projectionIndex;
    unsigned short index;
    unsigned short layer;
    short offsetY;
    short offsetX;
    short unused0;
    short unused1;
    char flag;
    unsigned short count;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&z, 2);
    file.Access(&flags, 4);
    file.Access(&row, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&index, 2);
    file.Access(&layer, 2);
    FUN_005e0c90(file, name);
    FUN_005e0c90(file, profile);
    file.Access(&RHElementTarget_m_168, 4);
    file.Access(&offsetY, 2);
    file.Access(&offsetX, 2);
    file.Access(&unused0, 2);
    file.Access(&unused1, 2);
    *(unsigned *)&RHElementTarget_m_f8 = 0x58635fa9;
    file.Access(&flag, 1);
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short pointX;
        short pointY;
        file.Access(&pointX, 2);
        file.Access(&pointY, 2);
        RHElementTarget_m_d4.FUN_00611100(SBGeoPoint2D((float)pointX, (float)pointY));
        float height = (float)pointY;
        if (height < RHElementTarget_m_f8)
            RHElementTarget_m_f8 = height;
    }
    file.Access(&flag, 1);
    Info()->FUN_005bd050(2, name, profile, 0);
    char enabled;
    file.Access(&enabled, 1);
    if (enabled)
        RHElementTarget_m_a8 = 1;
    else
        RHElementTarget_m_a8 = 0;
    char scripted;
    file.Access(&scripted, 1);
    if (scripted)
    {
        std::string scriptName;
        FUN_005e0c90(file, scriptName);
        if (scriptName.empty())
            SBAssert(1,
                     // STRING: GAME 0x006aee40
                     "P:\\Robin Hood\\RHelementtarget.cpp", 101,
                     "Script error: a scripted object had no valid script class name.");
        if (g_unk0x6c0691 == 1)
        {
            RHUnkSectorScript *script = &RHElementTarget_m_fc;
            script->Unk00639a30(scriptName);
            RHElementTarget_m_15c = this ? script : 0;
        }
    }
    *(unsigned long *)(((char *)this) + 0x54) = Draw()->Unk005e4ed0(((RHCivilianSpriteView *)Info())->FUN_005bdef0(), ((RHCivilianSpriteView *)Info())->FUN_005bdf20(), 0, 0);
    *(unsigned long *)(((char *)this) + 0x58) = Draw()->Unk005e4ed0(((RHCivilianSpriteView *)Info())->FUN_005bdef0() + 6, ((RHCivilianSpriteView *)Info())->FUN_005bdf20(), 0, 0);
    Info()->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    Info()->m_4.m_da = layer;
    Info()->m_e0 = index == 0xffff ? Global()->m_4184 : Global()->m_4064[index];
    RHBonusProjection *projection;
    if (projectionIndex != 0xffff)
        projection = Global()->m_4144[projectionIndex];
    else
        projection = 0;
    Info()->m_4.FUN_0055fa20(projection);
    if (projection)
    {
        if (!(projection->Flags() & 1))
            SBAssert(1, "P:\\Robin Hood\\RHelementtarget.cpp", 705,
                     // STRING: GAME 0x006aeecc
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Target (%d,%d) not lying on projection area !",
                     Info()->m_4.m_20.m_x, Info()->m_4.m_20.m_y);
        if (!projection->Inside(Info()->m_4.m_20))
            SBAssert(1, "P:\\Robin Hood\\RHelementtarget.cpp", 709,
                     // STRING: GAME 0x006aee64
                     "DA F\xc4LLT MIR NICHTS MEHR EIN ! Target (%d,%d) map position not lying in projection area screen box !",
                     Info()->m_4.m_20.m_x, Info()->m_4.m_20.m_y);
    }
    if (z >= 0)
    {
        Info()->m_4.FUN_0055f290();
        float height = (float)z;
        float screenY = (float)(y + z);
        float screenX = (float)x;
        Info()->m_4.m_c = RHUnk005df4f0(screenX, screenY, height);
        Info()->m_4.m_4 = 1;
    }
    else
        Info()->m_4.FUN_0055f290();
    Info()->FUN_005bd560(0, true);
    Info()->m_4.m_28 = Info()->m_4.m_c;
    Info()->m_4.SetPoint(SBGeoPoint2D((float)offsetX, (float)offsetY));
    Info()->RestorePoint();
    Info()->m_4.m_4 = 7;
    Info()->FUN_005b76e0(row, flags);
    Info()->m_4.SetFlags(flags & 0xf);
    if (g_unk0x6c0691 && RHElementTarget_m_154)
        ((RHUnkTargetScriptRef *)(((char *)this) + 0x15c))->FUN_004034e0();
}

// FUNCTION: GAME 0x004bad80
RHElementTarget::~RHElementTarget()
{
    m_16c.clear();
}

// FUNCTION: GAME 0x004bad60
RHElementTarget *RHElementTarget::FUN_004bad60(char flags)
{
    this->RHElementTarget::~RHElementTarget();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004bae60
void RHElementTarget::FUN_004bae60(RHTargetSequenceCalls *sequence, int (RHUnkTargetScriptRef::*callback)(int))
{
    if (g_unk0x6c0691 && RHElementTarget_m_154)
    {
        RHUnkTargetScriptRef *script = this ? (RHUnkTargetScriptRef *)(((char *)this) + 0x15c) : 0;
        (script->*callback)(sequence->m_64);
    }
    sequence->V0c(0, true);
}

// FUNCTION: GAME 0x004baf50
int RHElementTarget::FUN_004baf50(void *actor)
{
    if ((RHElementTarget_m_168 & 0x100) && ((RHScriptBatchCalls *)actor)->Unk0049d560(23))
        return 0x55;
    if ((RHElementTarget_m_168 & 0x10) && ((RHScriptBatchCalls *)actor)->Unk0049d560(9))
        return 0x6e;
    if (RHElementTarget_m_168 & 2)
        return 0x70;
    if (RHElementTarget_m_168 & 4)
        return 0x6f;
    if (RHElementTarget_m_168 & 0x400)
        return 0x74;
    if ((RHElementTarget_m_168 & 8) && ((RHMalignityActorCalls *)actor)->Vf8())
        return 0x71;
    return 0;
}

// FUNCTION: GAME 0x004baff0
int RHElementTarget::FUN_004baff0(void *actor)
{
    if ((RHElementTarget_m_168 & 0x100) && ((RHScriptBatchCalls *)actor)->Unk0049d560(23))
        return 0x70;
    if ((RHElementTarget_m_168 & 0x10) && ((RHScriptBatchCalls *)actor)->Unk0049d560(9))
        return ((RHMalignityActorCalls *)actor)->Vf8() ? 0xb6 : 0x112;
    if (RHElementTarget_m_168 & 2)
        return 0xc5;
    if (RHElementTarget_m_168 & 4)
        return 0xc6;
    if (RHElementTarget_m_168 & 0x400)
        return 0x5b;
    if ((RHElementTarget_m_168 & 8) && ((RHMalignityActorCalls *)actor)->Vf8())
        return 0x67;
    return 0;
}

// FUNCTION: GAME 0x004bb0a0
int RHElementTarget::FUN_004bb0a0(void *actor)
{
    if ((RHElementTarget_m_168 & 0x100) && ((RHScriptBatchCalls *)actor)->Unk0049d560(23))
        return 0x33;
    if (RHElementTarget_m_168 & 2)
        return 0x30;
    if (RHElementTarget_m_168 & 4)
        return 0x2f;
    if (RHElementTarget_m_168 & 0x400)
        return 0x27;
    if ((RHElementTarget_m_168 & 8) && ((RHMalignityActorCalls *)actor)->Vf8())
        return 0x24;
    if (RHElementTarget_m_168 & 1)
        return 0x0e;
    if (RHElementTarget_m_168 & 0x10)
        return ((RHMalignityActorCalls *)actor)->Vf8() ? 0x1f : 0x36;
    if (RHElementTarget_m_168 & 0x20)
        return 0x0a;
    if (RHElementTarget_m_168 & 0x40)
        return 0x25;
    return (RHElementTarget_m_168 & 0x80) ? 0x2d : 3;
}

// Parked: direct box access omits the canonical base getter call.
// STUB: GAME 0x004bb180
RHUnk00613e90 RHElementPositionCalls::FUN_004bb180()
{
    void *sprite = *(void **)((char *)this + 0x50);
    RHUnk00613e90 result = *(RHUnk00613e90 *)((char *)sprite + 0x10);
    SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)sprite + 0x1a0));
    result.z += box.FUN_00608f40().m_y - box.m_p0.m_y;
    return result;
}

// FUNCTION: GAME 0x004bb240
bool RHElementTarget::FUN_004bb240(void *point, void *pc, int focus) const
{
    if (((char *)this)[0x12])
    {
        const std::vector<RHMobileUnk006100e0 *> &points = m_16c;
        unsigned count = points.size();
        for (unsigned i = 0; i < count; ++i)
            points[i]->FUN_00578c50();
        if (((char *)this)[0x12] && pc && *(unsigned *)((char *)g_pEngine + 0x4a00) <= 1)
        {
            unsigned filter;
            switch (focus)
            {
            case 4:
            case 7:
            case 8:
            case 9:
            case 10:
                filter = FUN_004baf00(focus);
                break;
            case 3:
                filter = FUN_004baeb0(pc);
                break;
            default:
                filter = 0;
                break;
            }
            return filter && (*(const unsigned *)(((char *)this) + 0x168) & filter) &&
                   (*(RHSprite *const *)(((char *)this) + 0x50))->FUN_005b9e30(point, *(void *const *)(((char *)this) + 0x54), false);
        }
    }
    return false;
}

#include "RHSequenceConstructionCalls.h"
#include "RHSequenceGenericConstruction.h"
#include "RHSequenceInteractionAction.h"
#include "RHSequenceMovementConstruction.h"
#include "RHSequenceAppendCalls.h"
#include "RHSequenceLaunchCalls.h"
#include "RHElementActorHumanBase.h"
#include "RHActorMessage.h"
#include "RHMessenger.h"
#include "RHTitbitsCore.h"

extern RHMessenger *RHUnk00546050();
extern RHTitbits *g_unk0x6c10e8;

template<class T> inline T &RHTargetField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// STUB: GAME 0x004bb3a0
bool RHElementTarget::FUN_004bb3a0(void *point, unsigned flags, RHElementActorPC *actor)
{
    unsigned short focus = RHTargetField<unsigned short>(RHUnk00546050(), 0x26);
    int animation;
    if (flags & 8)
    {
        if (!RHTargetField<bool>(RHUnk00546050(), 0x20))
        {
            ((RHElementActor *)actor)->FUN_0046bb80();
            return true;
        }
        animation = 10;
    }
    else
        animation = RHTargetField<int>(RHTargetField<void *>(actor, 0x50), 0x8c) == 10 ? 16 : 6;
    int command = FUN_004baf50(actor);
    if (command)
    {
        if (!RHTargetField<bool>(RHUnk00546050(), 0x20))
        {
            unsigned short level = 1;
            RHUnk00582220 *sequence = new RHUnk00582220;
            if (sequence->FUN_00582640(level, actor, animation,
                RHTargetField<SBGeoPoint2D>(RHTargetField<void *>(actor, 0x50), 0x24),
                RHTargetField<void *>(RHTargetField<void *>(actor, 0x50), 0xe0),
                RHTargetField<unsigned short>(RHTargetField<void *>(actor, 0x50), 0xde),
                RHTargetField<SBGeoPoint2D>(Info(), 0x24), RHTargetField<void *>(Info(), 0xe0),
                RHTargetField<unsigned short>(Info(), 0xde), this, 0.0f, 0, 1.0f))
            {
                RHUnk005866a0 *turn = new RHUnk005866a0(level++, 26, actor);
                turn->Unk00587010(8, ((RHElementActor *)this)->FUN_00462920());
                ((RHUnk00585500 *)turn)->Unk(sequence);
                RHUnk00585ea0 *action = new RHUnk00585ea0(level, command, actor, this);
                ((RHUnk00585500 *)action)->Unk(sequence);
                ((RHUnk0058a3d0 *)*(void **)((char *)this + 0x5c))->Unk((void *)"", 0, sequence);
                ((RHMalignityActorCalls *)actor)->V104(12, 0, 255);
                return true;
            }
            ((RHMalignityActorCalls *)actor)->V104(14, 0, 255);
            if (sequence)
                sequence->FUN_00582280(1);
            return true;
        }
        RHUnk00582220 *sequence = new RHUnk00582220;
        RHUnk00588530 *movement = new RHUnk00588530(1, 21, actor, animation,
            RHTargetField<SBGeoPoint2D>(Info(), 0x24), RHTargetField<void *>(Info(), 0xe0),
            RHTargetField<unsigned short>(Info(), 0xde), 0.0f, 0);
        ((RHUnk00585500 *)movement)->Unk(sequence);
        RHUnk00582220 *postSequence = new RHUnk00582220;
        RHUnk005866a0 *turn = new RHUnk005866a0(1, 26, actor);
        turn->Unk00587010(8, ((RHElementActor *)this)->FUN_00462920());
        ((RHUnk00585500 *)turn)->Unk(postSequence);
        RHUnk00585ea0 *action = new RHUnk00585ea0(2, command, actor, this);
        ((RHUnk00585500 *)action)->Unk(postSequence);
        movement->m_68 = (RHMovementOwned *)postSequence;
        RHUnk00613e90 position;
        ((RHMalignityActorCalls *)actor)->V170(command, false, focus,
            g_unk0x6c10e8->AddTitbit(position, 0, (RHtitbitKind)3, (RHElement *)this,
                FUN_004bb0a0(actor), actor, animation == 10, 0xffffffff));
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(6, 0));
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004bbf80
bool RHElementTarget::FUN_004bbf80()
{
    if (((char *)this)[0x12])
        ((RHEngineWidenedCalls *)Info())->FUN_005b7f60(*(unsigned long *)(((char *)this) + 0x164));
    return true;
}

// STUB: GAME 0x004bbfa0
bool RHElementTarget::Serialize(SBFile &file)
{
    RHElementTarget *const self = this;
#define target_data ((char *)self)
#define m_16c self->m_16c
    // STRING: GAME 0x006aef1c
    RHSerializeName(file, "RHElementTarget");
    if (file.Access(&RHElementTarget_m_160, 4) < 0)
    {
        SBString *error = file.GetError();
        const char *reason = error->m_chars ? error->m_chars : "";
        SBAssert(0,
                 "P:\\Robin Hood\\RHelementtarget.cpp", 0x372,
                 "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&RHElementTarget_m_164, 4) < 0)
    {
        SBString *error = file.GetError();
        const char *reason = error->m_chars ? error->m_chars : "";
        SBAssert(0,
                 "P:\\Robin Hood\\RHelementtarget.cpp", 0x373,
                 "Serialize failed reason is %s", reason);
        return false;
    }
    if (g_unk0x6c0691 && RHElementTarget_m_154)
        ((VMCore *)(target_data + 0xfc))->SerializeMemberVariable(file);
    if (file.m_version >= 0x1f)
    {
        unsigned count;
        RHMobileUnk006100e0 *element;
        if (file.m_bLoading)
        {
            RHScriptFXArray *vector = (RHScriptFXArray *)&m_16c;
            void **last = FUN_004598e0(((RHScriptFXArray *)&m_16c)->last,
                                       ((RHScriptFXArray *)&m_16c)->last,
                                       ((RHScriptFXArray *)&m_16c)->first);
            vector->Unk005008e0(last, vector->last);
            vector->last = last;
            vector->dirty = 1;
            if (file.Access(&count, 4) < 0)
            {
                SBString *error = file.GetError();
                const char *reason = error->m_chars ? error->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHelementtarget.cpp", 0x386,
                         "Serialize failed reason is %s", reason);
                return false;
            }
            for (unsigned index = 0; index < count; ++index)
            {
                g_pEngine->SerializeElementPointer(file, *(RHElement **)&element);
#pragma inline_depth(0)
                m_16c.insert(m_16c.end(), 1, element);
#pragma inline_depth()
                vector->dirty = 1;
            }
        }
        else
        {
            if (!((RHScriptFXArray *)&m_16c)->first)
                count = 0;
            else
                count = (unsigned)((RHMobileUnk006100e0 **)((RHScriptFXArray *)&m_16c)->last -
                                   (RHMobileUnk006100e0 **)((RHScriptFXArray *)&m_16c)->first);
            if (file.Access(&count, 4) < 0)
            {
                SBString *error = file.GetError();
                const char *reason = error->m_chars ? error->m_chars : "";
                SBAssert(0,
                         "P:\\Robin Hood\\RHelementtarget.cpp", 0x390,
                         "Serialize failed reason is %s", reason);
                return false;
            }
            for (unsigned index = 0; index < count; ++index)
            {
                element = ((RHMobileUnk006100e0 **)((RHScriptFXArray *)&m_16c)->first)[index];
                g_pEngine->SerializeElementPointer(file, *(RHElement **)&element);
            }
        }
    }
    return ((RHElementFX *)self)->RHElementFX::Serialize(file);
#undef target_data
#undef m_16c
}

// FUNCTION: GAME 0x004bc1d0
bool RHElementTarget::FUN_004bc1d0(RHTargetSequenceCalls *sequence)
{
    RHElementActor *saved = g_unk0x6c100c;
    g_unk0x6c100c = (RHElementActor *)this;
    switch (((RHSequenceElement *)sequence)->m_10)
    {
    case 0x99:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_004035d0);
        break;
    case 0x93:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_004036d0);
        break;
    case 0x95:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_004037d0);
        break;
    case 0x9a:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_004038d0);
        break;
    case 0x96:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_004039d0);
        break;
    case 0x9b:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_00403ad0);
        break;
    case 0x97:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_00403bd0);
        break;
    case 0x98:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_00403cd0);
        break;
    case 0x94:
        FUN_004bae60(sequence, &RHUnkTargetScriptRef::FUN_00403dd0);
        break;
    case 0xa6:
        *(int *)(((char *)this) + 0x160) = ((RHSequenceElement *)sequence)->Unk00587160(0x15);
        *(unsigned *)(((char *)this) + 0x164) = 8;
        Info()->FUN_005b76e0(*(unsigned *)(((char *)this) + 0x160), *(unsigned short *)((char *)Info() + 0xd8));
        ((RHUnk005bd5b0 *)Info())->Unk(false);
        sequence->V0c(0, true);
        break;
    case 0xa4:
        *(int *)(((char *)this) + 0x160) = ((RHSequenceElement *)sequence)->Unk00587160(0x15);
        *(unsigned *)(((char *)this) + 0x164) = 0;
        Info()->FUN_005b76e0(*(unsigned *)(((char *)this) + 0x160), *(unsigned short *)((char *)Info() + 0xd8));
        ((RHUnk005bd5b0 *)Info())->Unk(false);
        sequence->V0c(0, true);
        break;
    case 0xa5:
        *(int *)(((char *)this) + 0x160) = ((RHSequenceElement *)sequence)->Unk00587160(0x15);
        *(unsigned *)(((char *)this) + 0x164) = 1;
        Info()->FUN_005b76e0(*(unsigned *)(((char *)this) + 0x160), *(unsigned short *)((char *)Info() + 0xd8));
        ((RHUnk005bd5b0 *)Info())->Unk(false);
        sequence->V0c(0, true);
        break;
    }
    g_unk0x6c100c = saved;
    return true;
}

// FUNCTION: GAME 0x004bc3d0
void RHElementTarget::FUN_004bc3d0(int activator)
{
    if ((RHElementTarget_m_168 & 0x200) && g_unk0x6c0691)
    {
        RHElementTarget_m_168 &= ~0x200;
        ((RHUnkTargetScriptRef *)(((char *)this) + 0x15c))->FUN_00403ed0(activator);
    }
}

void RHElementTarget::Emit(SBFile &file)
{
    FUN_004baf50(0);
    FUN_004baff0(0);
    FUN_004bb0a0(0);
    FUN_004bb240(0, 0, 0);
    FUN_004bae60(0, &RHUnkTargetScriptRef::FUN_004035d0);
    ((RHElementPositionCalls *)this)->FUN_004bb180();
    FUN_004bbf80();
    InitializeFromMissionStream(file);
    FUN_004bc3d0(0);
}
