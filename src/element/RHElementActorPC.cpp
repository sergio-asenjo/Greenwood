#include "RHElementActorPC.h"
#include "RHElementActorPC_calls.h"
#include "RHPCStatusCore.h"
#include "RHPlayerProfileAccess.h"
#include "RHCampaignPropertyCalls.h"
#include "RHMalignityActorCalls.h"
#include "RHEngineActorActionCalls.h"
#include "RHHumanActorCalls.h"
#include "RHWidgetPortraitClass.h"
#include "RHActorMessage.h"
#include "RHActorTranslation.h"
#include "RHPCSelectionQueryCalls.h"
#include "RHMalignityVisibilityCalls.h"
#include "RHElementActorHumanCore.h"
#include "RHHumanSequenceElement.h"
#include "RHPortraitActorCalls.h"
#include "RHPathQueryCalls.h"
#include "RHUnk005fc400.h"
#include "RHBow.h"
#include "RHTitbits.h"
#include "RHMalignityPosition.h"
#include "RHUnk004a6310.h"
#include "RHProjectileInitCalls.h"
#include "RHUnk004d8460Calls.h"
#include "RHProjectileVector.h"

extern undefined g_unk0x006c0e48[];

extern "C" int rand();

class RHActorTranslationSequenceCalls;

DECOMP_SIZE_ASSERT(RHElementActorPC, 0x60c)
DECOMP_SIZE_ASSERT(RHUnk00549250, 0x14)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHActorPCWidgetState, 0xe8)
DECOMP_SIZE_ASSERT(RHCampaignProfiles, 0x70)
DECOMP_SIZE_ASSERT(RHActorPCProfileNode, 0x18)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHPCDescription, 0x48)
DECOMP_SIZE_ASSERT(RHUnk0048f280, 0x60c)

extern RHUnk005c38b0 *g_unk0x6c10e8;
extern float g_unk0x006774ec;
extern float g_unk0x00677484;
extern float g_unk0x00677f9c;
extern double g_unk0x00677d90;
std::wstring FUN_005e23d0(unsigned long id);

// GLOBAL: GAME 0x00677f88
float g_unk0x00677f88 = 75.0f;
RHMessenger *RHUnk00546050();

// GLOBAL: GAME 0x00677fa0
float g_unk0x00677fa0 = 562500.0f;

// STRING: GAME 0x006ae5e0
#define g_actorPCFile "P:\\Robin Hood\\RHelementactorpc.cpp"
// STRING: GAME 0x006ae858
#define g_unknownInitialAction "ACHTUNG : Unknown initial action %d !"

// FUNCTION: GAME 0x00455ce0
RHPCDescription *RHActorPCProfileCalls::FUN_00455ce0(void *profile)
{
    for (RHPCDescription **it = m_104.begin(); it != m_104.end(); ++it)
    {
        if (RHActorPCField<void *>(*it, 0x40) == profile)
            return *it;
    }
    return 0;
}

// FUNCTION: GAME 0x00455d40
void RHActorPCProfileCalls::FUN_00455d40(RHPCDescription *description)
{
    std::vector<RHPCDescription *> &descriptions = m_104;
    descriptions.insert(descriptions.end(), description);
}

// FUNCTION: GAME 0x0045aaf0
RHUnk0045aaf0::RHUnk0045aaf0()
{
    m_0 = 0;
    m_4 = 0;
}

// FUNCTION: GAME 0x0045ab50
RHUnk0045aaf0::~RHUnk0045aaf0()
{
}

// FUNCTION: GAME 0x0048ec00
void RHScriptBatchCalls::Unk0048ec00(void *scroll)
{
    RHTitbits *titbits = (RHTitbits *)g_unk0x6c10e8;
    if (scroll == RHActorPCField<void *>(this, 0x500))
        return;
    if (!scroll)
        titbits->FUN_005c8120(0xe, (RHElement *)this);
    RHActorPCField<void *>(this, 0x500) = scroll;
    if (scroll)
    {
        titbits->FUN_005c8120(0xe, (RHElement *)this);
        RHUnk00613e90 position;
        ((RHScriptBatchCalls *)titbits)->Unk005c2ec0(&position, 0, 0xe, this, 0, 0, 0, -1);
    }
}

// Parked: flat subobjects omit the original member-cleanup EH states.
// STUB: GAME 0x0048f280
RHUnk0048f280::RHUnk0048f280(void *description)
{
    ((RHUnk00471630 *)this)->RHUnk00471630::RHUnk00471630(12, 0, description);
    ((SBGeoPoint2D *)((char *)this + 0x4f0))->SBGeoPoint2D::SBGeoPoint2D();
    RHActorPCField<int>(this, 0x4f8) = 0;
    RHActorPCField<char>(this, 0x4fc) = 0;
    char allocator;
    RHActorPCField<char>(this, 0x55c) = allocator;
    RHActorPCField<RHScriptNode *>(this, 0x560) = ((RHUnk0046eb30 *)((char *)this + 0x55c))->Unk0059f720(0, 0);
    RHActorPCField<int>(this, 0x564) = 0;
    RHActorPCField<char>(this, 0x56c) = 1;
    ((SBGeoPoint2D *)((char *)this + 0x584))->SBGeoPoint2D::SBGeoPoint2D();
    ((RHUnk0045aaf0 *)((char *)this + 0x590))->RHUnk0045aaf0::RHUnk0045aaf0();
    ((RHUnk00613e90 *)((char *)this + 0x5d4))->RHUnk00613e90::RHUnk00613e90();
    RHActorPCField<int>(this, 0x5e8) = 0;
    RHActorPCField<void *>(this, 0x5f8) = description;
    RHActorPCField<void *>(this, 0x5fc) = RHActorPCField<void *>(description, 0x40);
    RHActorPCField<void *>(this, 0x600) = description;
    RHActorPCField<unsigned>(this, 0) = 0x677dfc;
    RHActorPCField<unsigned>(this, 0xa8) = 0x677df8;
    RHActorPCField<unsigned>(this, 0x104) = 0x677df4;
    RHActorPCField<unsigned short>(this, 0x10) = 1;
    void *profile = RHActorPCField<void *>(this, 0x5fc);
    const char *name = RHActorPCField<char *>(profile, 8);
    if (name == 0)
        name = "";
    if (strcmp(name, "RobinTown") == 0)
    {
        RHActorPCField<char>(this, 0x5f5) = 1;
        if (((RHBonusEngineView *)g_pEngine)->Flag())
        {
            RHCampaignProfiles *profiles = g_unk0x6c0e84;
            if (profiles == 0)
                g_unk0x6c0e84 = profiles = new RHCampaignProfiles;
            RHActorPCField<void *>(this, 0x5fc) = profiles->m_14[0];
            RHActorPCField<void *>(RHActorPCField<void *>(this, 0x5f8), 0x40) = RHActorPCField<void *>(this, 0x5fc);
            name = RHActorPCField<char *>(RHActorPCField<void *>(this, 0x5fc), 8);
            if (name == 0)
                name = "";
            if (strcmp(name, "RobinHood") != 0)
                SBAssert(1, g_actorPCFile, 0x8d,
                    // STRING: GAME 0x006ae65c
                    "UNGLAUBLICH ABER WAHR : Robin Hood profile is not at position 0 in character profiles !");
        }
    }
    else if (strcmp(name, "RobinHood") == 0)
    {
        RHActorPCField<char>(this, 0x5f5) = 1;
        if (!((RHBonusEngineView *)g_pEngine)->Flag())
        {
            RHCampaignProfiles *profiles = g_unk0x6c0e84;
            if (profiles == 0)
                g_unk0x6c0e84 = profiles = new RHCampaignProfiles;
            RHActorPCField<void *>(this, 0x5fc) = profiles->m_14[1];
            RHActorPCField<void *>(RHActorPCField<void *>(this, 0x5f8), 0x40) = RHActorPCField<void *>(this, 0x5fc);
            name = RHActorPCField<char *>(RHActorPCField<void *>(this, 0x5fc), 8);
            if (name == 0)
                name = "";
            if (strcmp(name, "RobinTown") != 0)
                SBAssert(1, g_actorPCFile, 0x9c,
                    // STRING: GAME 0x006ae604
                    "UNGLAUBLICH ABER WAHR : Robin Town profile is not at position 1 in character profiles !");
        }
    }
    else
        RHActorPCField<char>(this, 0x5f5) = 0;
    RHActorPCField<char>(this, 0x604) = 0;
    RHActorPCField<char>(this, 0x496) = g_unk0x6c0689;
    RHActorPCField<char>(this, 0x5f4) = g_unk0x6c0689;
    RHActorPCField<char>(this, 0x12) = 1;
    for (unsigned i = 0; i < 3; ++i)
    {
        RHActorPCField<int>(this, 0x514 + i * 4) = 0;
        RHActorPCField<int>(this, 0x520 + i * 4) = 0;
        RHActorPCField<int>(this, 0x544 + i * 4) = 0;
        RHActorPCField<int>(this, 0x52c + i * 4) = 0;
        RHActorPCField<int>(this, 0x538 + i * 4) = -1;
        RHActorPCField<unsigned short>(this, 0x50e + i * 2) = 0;
    }
    RHActorPCField<unsigned short>(this, 0x580) = 0;
    RHActorPCField<char>(this, 0x58c) = 0;
    RHActorPCField<char>(this, 0x92) = 0;
    RHActorPCField<char>(this, 0x556) = 0;
    RHActorPCField<char>(this, 0x557) = 0;
    RHActorPCField<char>(this, 0x558) = 0;
    RHActorPCField<unsigned short>(this, 0x55a) = 0xffff;
    RHActorPCField<int>(this, 0x480) = 0;
    RHActorPCField<unsigned short>(this, 0x98) = g_unk0x6c11d0->Unk(165, 255, 82);
    RHActorPCField<unsigned short>(this, 0x94) = g_unk0x6c11d0->Unk(165, 255, 82);
    RHActorPCField<unsigned short>(this, 0x96) = g_unk0x6c11d0->Unk(165, 255, 82);
    RHActorPCField<float>(this, 0x48c) = 1.0f;
    RHActorPCField<int>(this, 0x484) = 20;
    RHActorPCField<char>(this, 0x4e8) = 1;
    for (unsigned j = 0; j < 3; ++j)
    {
        RHActorPCField<char>(this, 0x508 + j) = 0;
        RHActorPCField<char>(this, 0x50b + j) = 0;
    }
    RHActorPCField<int>(this, 0x500) = 0;
    RHActorPCField<int>(this, 0x504) = 0;
    RHActorPCField<RHUnk00549250 *>(this, 0x4ac) = new RHUnk00549250(1, this, 0);
    RHActorPCField<RHUnk00549250 *>(this, 0x4b0) = new RHUnk00549250(1, this, 1);
    RHActorPCField<RHUnk00549250 *>(this, 0x4b4) = new RHUnk00549250(1, this, 2);
    RHActorPCField<RHUnk00549250 *>(this, 0x4b8) = new RHUnk00549250(3, this, 0);
    RHActorPCField<RHUnk00549250 *>(this, 0x4bc) = new RHUnk00549250(3, this, 1);
    RHActorPCField<RHUnk00549250 *>(this, 0x4c0) = new RHUnk00549250(3, this, 2);
    RHActorPCField<RHUnk00549250 *>(this, 0x4c4) = new RHUnk00549250(10, this, 0);
    RHActorPCField<RHUnk00549250 *>(this, 0x4c8) = new RHUnk00549250(10, this, 1);
    RHActorPCField<RHUnk00549250 *>(this, 0x4cc) = new RHUnk00549250(10, this, 2);
    RHActorPCField<int>(this, 0x5cc) = 0;
    RHActorPCField<int>(this, 0x5d4) = 0;
    RHActorPCField<int>(this, 0x5d8) = 0;
    RHActorPCField<int>(this, 0x5dc) = 0;
    RHActorPCField<int>(this, 0x5e0) = 0;
    RHActorPCField<int>(this, 0x5e4) = 0;
    RHActorPCField<unsigned short>(this, 0x4ea) = 0xffff;
    RHActorPCField<int>(this, 0x5ec) = -1;
    RHActorPCField<int>(this, 0x144) = 1;
    RHActorPCField<int>(this, 0x4ec) = 0;
    RHActorPCField<int>(this, 0x5f0) = 12;
    if (RHActorPCField<char>(g_unk0x6c0b3c, 0x5a))
    {
        RHUnk00613e90 position;
        ((RHScriptBatchCalls *)g_unk0x6c10e8)->Unk005c2ec0(&position, 0, 16, this, 0, 0, 0, -1);
    }
    RHActorPCField<char>(this, 0x605) = 0;
}

inline void RHElementActorPC::ApplyProjection(RHBonusProjection *projection)
{
    if (projection != 0)
    {
        if (!(projection->Flags() & 1))
            SBAssert(1, g_actorPCFile, 0x639,
                // STRING: GAME 0x006ae734
                "DA F\xc4LLT MIR NICHTS MEHR EIN ! Beam-me (%d,%d) not lying on projection area !", m_50->X(), m_50->Y());
        if (!projection->Inside(m_50->m_4.m_20))
            SBAssert(1, g_actorPCFile, 0x63d,
                // STRING: GAME 0x006ae6cc
                "DA F\xc4LLT MIR NICHTS MEHR EIN ! Beam-me (%d,%d) map position not lying in projection area screen box !", m_50->X(), m_50->Y());
    }
    m_50->m_4.FUN_0055fa20(projection);
}

// Parked: projection branches, register scheduling and word-mask width differ.
// STUB: GAME 0x00491fd0
void RHEngineReinforcementCalls::FUN_00491fd0(const RHbeamMe &beamMe)
{
    RHElementActorPC *actor = (RHElementActorPC *)this;
    *(unsigned short *)((char *)actor + 0x4ea) = beamMe.m_12;
    ((RHEngineSerializationCalls *)actor)->FUN_0048fa30();
    ((RHActorPCTemplateCalls *)actor)->FUN_00493660(0);
    {
        SBGeoVector2D vector(*(SBGeoVector2D *)((char *)actor->m_5fc + 0x84));
        RHBonusInfoBase &position = ((RHActorPCInfo *)actor->m_50)->Position();
        ((SBGeoVector2D *)((char *)&position + 0x80))->operator=(vector);
    }
    actor->m_50->m_4.SetPoint(beamMe.m_point);
    ((RHActorPCInfo *)actor->m_50)->Layer(beamMe.m_8);
    RHBonusGlobalView *global = actor->m_64;
    actor->m_50->m_e0 = beamMe.m_a == 0xffff ? global->m_4184 : global->m_4064[beamMe.m_a];
    RHBonusProjection *projection;
    projection = beamMe.m_c == 0xffff ? 0 : actor->m_64->m_4144[beamMe.m_c];
    actor->ApplyProjection(projection);
    ((RHActorPCInfo *)actor->m_50)->ByteValue(beamMe.m_e);
    actor->m_50->m_4.FUN_0055f290();
    actor->m_50->FUN_005bd560(0, true);
    actor->m_50->m_4.m_28 = actor->m_50->m_4.m_c;
    actor->m_50->RestorePoint();
    RHBonusInfoBase &position = actor->m_50->m_4;
    unsigned short flags = *(volatile const unsigned short *)&beamMe.m_10 & 0xf;
    position.m_d4 = flags;
    position.m_d6 = flags;
    if (g_unk0x6c0691 && beamMe.m_20.size())
        ((RHElementActor *)actor)->InitializeScript((std::string &)beamMe.m_20);
    actor->InitializeAction(beamMe.m_1c);
    ((RHScriptBatchCalls *)actor)->Unk00464630();
}

// FUNCTION: GAME 0x0048f910
unsigned short RHElementActorPC::FUN_0048f910()
{
    return 100;
}

// FUNCTION: GAME 0x0048f920
char RHElementActorPC::FUN_0048f920()
{
    return *((char *)this + 0x5f4);
}

// FUNCTION: GAME 0x0048f930
bool RHElementActorPC::FUN_0048f930()
{
    return *(int *)((char *)m_50 + 0x8c) == 11;
}

// FUNCTION: GAME 0x0048f980
bool RHElementActorPC::FUN_0048f980()
{
    return rand() > 0x3fff;
}

// FUNCTION: GAME 0x0048f9a0
char RHElementActorPC::FUN_0048f9a0()
{
    return *((char *)this + 0x5f5);
}

// FUNCTION: GAME 0x0048f9b0
unsigned short RHElementActorPC::FUN_0048f9b0()
{
    return *(unsigned short *)((char *)m_5fc + 0x38);
}

// FUNCTION: GAME 0x0048f9c0
unsigned short RHElementActorPC::FUN_0048f9c0()
{
    return *(unsigned short *)((char *)m_5fc + 0x36);
}

// FUNCTION: GAME 0x0048f9d0
unsigned short RHElementActorPC::FUN_0048f9d0()
{
    return *(unsigned short *)((char *)m_5fc + 0x3a);
}

// FUNCTION: GAME 0x0048f9e0
char RHElementActorPC::FUN_0048f9e0()
{
    return *((char *)m_5fc + 0x35);
}

// FUNCTION: GAME 0x0048f9f0
unsigned RHElementActorPC::FUN_0048f9f0()
{
    return *(unsigned *)((char *)m_5fc + 0x94);
}

// FUNCTION: GAME 0x0048fa00
unsigned RHElementActorPC::FUN_0048fa00()
{
    return *(unsigned *)((char *)m_5fc + 0x98);
}

void EmitRHActorPCSmallMethods(RHElementActorPC *actor)
{
    actor->AbortQuickAction(0);
    actor->SetQuickActionSequence((void *)0, (void *)0, 0, 0);
    actor->SetQuickActionSequence(0, 0, 0);
    actor->SetQuickActionSequence(0, 0, 0, 0, 0);
    actor->GetTooltipTextForAction(0);
    actor->FUN_00495f90(actor);
    actor->FUN_0049b930(0, 0, false);
    actor->FUN_00490450(actor, actor);
    actor->FUN_00490e10((RHElementActorHuman *)actor);
    actor->FUN_00493b40(actor, *(SBGeoPoint2D *)actor, 0, 0);
    actor->FUN_0049d400((RHSequenceElement *)actor);
    actor->FUN_0048f910();
    actor->FUN_0048f920();
    actor->FUN_0048f930();
    actor->FUN_0048f980();
    actor->FUN_0048f9a0();
    actor->FUN_0048f9b0();
    actor->FUN_0048f9c0();
    actor->FUN_0048f9d0();
    actor->FUN_0048f9e0();
    actor->FUN_0048f9f0();
    actor->FUN_0048fa00();
    actor->FUN_0049c660(0);
    actor->FUN_0049f500();
    actor->FUN_0049ff60();
}

// FUNCTION: GAME 0x00490910
void RHEngineActorActionCalls::FUN_00490910(unsigned short value)
{
    for (int index = value; index < 2; ++index)
    {
        RHActorPCField<unsigned>(this, 0x52c + index * 4) = RHActorPCField<unsigned>(this, 0x530 + index * 4);
        RHActorPCField<unsigned>(this, 0x514 + index * 4) = RHActorPCField<unsigned>(this, 0x518 + index * 4);
        RHActorPCField<unsigned>(this, 0x520 + index * 4) = RHActorPCField<unsigned>(this, 0x524 + index * 4);
        RHActorPCField<unsigned>(this, 0x538 + index * 4) = RHActorPCField<unsigned>(this, 0x53c + index * 4);
        RHActorPCField<unsigned>(this, 0x544 + index * 4) = RHActorPCField<unsigned>(this, 0x548 + index * 4);
        RHActorPCField<unsigned short>(this, 0x550 + index * 2) = RHActorPCField<unsigned short>(this, 0x552 + index * 2);
    }
    RHActorPCField<unsigned>(this, 0x540) = -1;
    RHActorPCField<unsigned>(this, 0x534) = 0;
    RHActorPCField<unsigned>(this, 0x51c) = 0;
    RHActorPCField<unsigned>(this, 0x528) = 0;
    RHActorPCField<unsigned>(this, 0x54c) = 0;
    RHActorPCField<unsigned short>(this, 0x554) = 0;
}

// FUNCTION: GAME 0x00493660
void RHActorPCTemplateCalls::FUN_00493660(int value)
{
    if ((char)value || RHActorPCField<int>(RHActorPCField<void **>(g_unk0x6c07fc, 0x178)[0], 0x3c) != 8)
    {
        void *menu = RHActorPCField<void *>(this, 0x4ec);
        if (!RHActorPCField<char>(menu, 0xca9))
            ((RHActorPCEngineCalls *)g_unk0x6c0b3c)->FUN_0050efb0(menu);
    }
}

#include "RHActorPriorityCalls.h"

// FUNCTION: GAME 0x00493a80
int RHUnk00493a80::FUN_00493a80()
{
    if ((RHActorPCField<char>(this, 0x12) ||
         ((unsigned char)(RHActorPCField<unsigned>(RHActorPCField<void *>(RHActorPCField<void *>(this, 0x50), 0xe0), 0x30) >> 13) & 1)) &&
        (!((RHActorPCVTableCalls *)this)->FUN_62() || !RHActorPCField<char>(g_unk0x6c0b3c, 0x57)) &&
        !((RHMalignityVisibilityCalls *)this)->FUN_004860b0() &&
        RHActorPCField<char>(this, 0x4e8) == 1)
        return 1;
    return 0;
}

// FUNCTION: GAME 0x00493ae0
int RHElementActorPC::FUN_00493ae0(bool allow, void *unused)
{
    if (((RHActorPCVTableCalls *)this)->FUN_0049e720() ||
        RHActorPCField<unsigned char>(this, 0x1ce) ||
        RHActorPCField<unsigned short>(this, 0x23c))
        return 0;
    void *sprite = m_50;
    if (RHActorPCField<int>(sprite, 0x8c) == 0x12)
        return 0;
    if (!allow && ((unsigned short)(RHActorPCField<unsigned>(RHActorPCField<void *>(sprite, 0xe0), 0x30) >> 13) & 1))
        return 0;
    return 1;
}

// FUNCTION: GAME 0x00494850
int RHElementActorPC::FUN_00494850(void *element)
{
    int kind = RHActorPCField<int>(element, 0x5c);
    if (kind == 0xb)
    {
        switch (RHActorPCField<int>(element, 0x10))
        {
        case 0x2d: case 0x53: case 0x5d: case 0x5e: case 0x5f:
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64:
            return 0;
        case 0x4d: case 0x4e:
            return 7;
        case 0x54: case 0x57: case 0x58: case 0x59: case 0x5a:
        case 0x5b: case 0x5c: case 0x65: case 0x66: case 0x67:
        case 0x68: case 0x69: case 0x6d: case 0x6e: case 0x6f:
        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
            return 8;
        case 0x18: case 0x51: case 0x52:
            return 10;
        }
        return ((RHHumanPriorityCalls *)this)->FUN_00471f20(element);
    }
    return kind;
}

// FUNCTION: GAME 0x0049c660
void RHElementActorPC::FUN_0049c660(unsigned short value)
{
    if (RHActorPCField<unsigned short>(this, 0x55a) == value)
        RHActorPCField<unsigned short>(this, 0x55a) = 0xffff;
}

extern float g_unk0x00677488;
extern float g_rhuirendererportrait_percent;

// GLOBAL: GAME 0x00677f98
float g_unk0x00677f98 = 140.0f;

// FUNCTION: GAME 0x00490450
bool RHElementActorPC::FUN_00490450(void *owner, void *target)
{
    unsigned count = RHActorPCField<unsigned>(owner, 0x10) & 0xffff;
    for (unsigned i = 0; i < count; ++i)
    {
        RHPathQueryCalls *list = (RHPathQueryCalls *)((char *)owner + 8);
        list->FUN_005c8e40((unsigned short)i);
        void *element = RHActorPCField<void *>(RHActorPCField<void *>(list, 0xc), 8);
        void *actor = RHActorPCField<void *>(element, 0x48);
        if ((RHActorPCField<unsigned>(actor, 4) & 7) == 4 &&
            !((RHActorPCVTableCalls *)actor)->FUN_slot66(element, target))
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x00490c80
void RHElementActorPC::AbortQuickAction(unsigned short action)
{
    ((RHTitbits *)g_unk0x6c10e8)->RemoveQuickActionTitbitsFor(this, action);
    RHActorPCField<int>(this, 0x52c + action * 4) = 0;
    RHActorPCField<unsigned short>(this, 0x550 + action * 2) = 0;
    RHActorPCField<void *>(this, 0x544 + action * 4) = 0;
    ((RHActorPCVTableCalls *)this)->FUN_92(0, 0, action, -1);
}

// FUNCTION: GAME 0x00490cd0
bool RHElementActorPC::SetQuickActionSequence(void *first, void *second, unsigned short action, unsigned long id)
{
    RHActorPCField<int>(this, 0x52c + action * 4) = 0;
    RHActorPCSequenceCalls *sequence = RHActorPCField<RHActorPCSequenceCalls *>(this, 0x520 + action * 4);
    if (sequence)
        sequence->Destroy(1);
    RHActorPCField<void *>(this, 0x520 + action * 4) = second;
    sequence = RHActorPCField<RHActorPCSequenceCalls *>(this, 0x514 + action * 4);
    if (sequence)
        sequence->Destroy(1);
    RHActorPCField<void *>(this, 0x514 + action * 4) = first;
    RHActorPCField<unsigned short>(this, 0x50e + action * 2) = 0;
    ((RHTitbits *)g_unk0x6c10e8)->RemoveQuickActionTitbitsFor(this, action);
    RHActorPCField<unsigned long>(this, 0x538 + action * 4) = id;
    return true;
}

// FUNCTION: GAME 0x00490d50
bool RHElementActorPC::SetQuickActionSequence(int value, unsigned short action, unsigned long id)
{
    ((RHTitbits *)g_unk0x6c10e8)->RemoveQuickActionTitbitsFor(this, action);
    ((RHActorPCVTableCalls *)this)->FUN_92(0, 0, action, -1);
    RHActorPCField<int>(this, 0x52c + action * 4) = value;
    RHActorPCField<unsigned long>(this, 0x538 + action * 4) = id;
    return true;
}

// FUNCTION: GAME 0x00490da0
bool RHElementActorPC::SetQuickActionSequence(int value, unsigned short action, unsigned long id, void *target, unsigned short amount)
{
    ((RHTitbits *)g_unk0x6c10e8)->RemoveQuickActionTitbitsFor(this, action);
    ((RHActorPCVTableCalls *)this)->FUN_92(0, 0, action, -1);
    RHActorPCField<int>(this, 0x52c + action * 4) = value;
    RHActorPCField<unsigned long>(this, 0x538 + action * 4) = id;
    RHActorPCField<void *>(this, 0x544 + action * 4) = target;
    RHActorPCField<unsigned short>(this, 0x550 + action * 2) = amount;
    return true;
}

// Parked: pointer-return and flag-store scheduling differ after two shapes.
// STUB: GAME 0x00490e10
void *RHElementActorPC::FUN_00490e10(RHElementActorHuman *target)
{
    if ((((RHActorPCVTableCalls *)this)->FUN_0049e720() || RHActorPCField<unsigned char>(this, 0x1ce)) &&
        !((RHUnk005d73d0Actor *)this)->FUN_0049f510())
        return ((RHElementActorHuman *)this)->FUN_004837f0(target);
    if (((RHUnk005d73d0Actor *)this)->FUN_0049f510())
    {
        if (target && (((RHScriptBatchCalls *)target)->Unk0049d560(25) ||
                       ((RHScriptBatchCalls *)target)->Unk0049d560(26)))
        {
            RHUnk0045aaf0 *result = (RHUnk0045aaf0 *)((char *)this + 0x14);
            result->FUN_0045abc0(0x5b, 0, 0);
            RHActorPCField<unsigned char>(this, 0x92) = 1;
            RHActorPCField<int>(this, 0xa0) = 0;
            RHActorPCField<unsigned short>(this, 0xa4) = 2;
            return result;
        }
        return 0;
    }
    RHUnk0045aaf0 *result = (RHUnk0045aaf0 *)((char *)this + 0x590);
    result->FUN_0045abc0(0x11, 0, 0);
    if (target && RHActorPCField<int>(RHActorPCField<void *>(this, 0x50), 0x8c) == 14 &&
        ((RHScriptBatchCalls *)target)->Unk0049d560(22))
    {
        RHActorPCField<unsigned char>(this, 0x92) = 1;
        RHActorPCField<int>(this, 0xa0) = 0;
        RHActorPCField<unsigned short>(this, 0xa4) = 2;
        result->FUN_0045abc0(0x63, 0, 0);
    }
    return result;
}

// FUNCTION: GAME 0x00493b40
unsigned short RHElementActorPC::FUN_00493b40(void *target, const SBGeoPoint2D &point, int, int)
{
    RHUnk005fc400 direction(RHActorPCField<SBGeoPoint2D>(RHActorPCField<void *>(this, 0x50), 0x24),
        target == 0 ? point : RHActorPCField<SBGeoPoint2D>(RHActorPCField<void *>(target, 0x50), 0x24));
    float distance = ((RHUnk005fc3b0 *)&direction)->Unk005fc6a0(1.0f);
    double factor = distance / RHActorPCField<RHBow *>(this, 0x258)->FUN_00450070(1);
    if (factor >= g_unk0x00677d90)
        factor = g_unk0x00677f88;
    else
        factor *= g_unk0x00677f88;
    return (unsigned short)factor;
}

// FUNCTION: GAME 0x00492d30
std::wstring RHElementActorPC::GetTooltipTextForAction(int action)
{
    switch (action)
    {
    case 1: return FUN_005e23d0(0x130);
    case 2: case 3: return FUN_005e23d0(0x135);
    case 4: return FUN_005e23d0(0x131);
    case 5: return FUN_005e23d0(0x134);
    case 6: case 7: return FUN_005e23d0(0x13a);
    case 8: return FUN_005e23d0(0x136);
    case 10: return FUN_005e23d0(0x13d);
    case 11: return FUN_005e23d0(0x133);
    case 13: case 14: return FUN_005e23d0(0x138);
    case 15: return FUN_005e23d0(0x13c);
    case 16: return FUN_005e23d0(0x137);
    case 17: return FUN_005e23d0(0x132);
    case 18: return FUN_005e23d0(0x13e);
    case 19: return FUN_005e23d0(0x13b);
    case 12: return FUN_005e23d0(0x139);
    case 20: return FUN_005e23d0(0x13f);
    }
    return std::wstring();
}

// FUNCTION: GAME 0x00495f90
void RHElementActorPC::FUN_00495f90(void *element)
{
    if (RHActorPCField<int>(element, 0x3c) == 1 &&
        RHActorPCField<int>(element, 0x40) >= 12 && RHActorPCField<int>(element, 0x40) <= 14)
    {
        int command = RHActorPCField<int>(element, 0x94);
        if (command == 6 || command == 0xbb)
            RHActorPCField<int>(element, 0x94) = 0x131;
    }
    else
        ((RHElementActorHuman *)this)->FUN_00474890(element);
}

// Parked: case fallthrough lengthens output-reference liveness and adds a saved register.
// STUB: GAME 0x00495fd0
void RHElementActorPC::GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third)
{
    switch (RHActorPCField<int>(element, 0x10))
    {
    case 0xa0: case 0xa1:
        if (RHActorPCField<unsigned char>(RHActorPCField<void *>(RHActorPCField<void *>(this, 0x50), 0xe0), 0xec))
        {
            first = 0x8001; second = 2;
            break;
        }
        ((RHElementActorHuman *)this)->GetTransitionFlags(element, first, second, third);
        break;
    case 0x32:
        first = 0x21; second = 1; break;
    case 0x53:
        first = 0x21; second = 0x241; break;
    case 0x54:
    {
        void *target = RHActorPCField<void *>(element, 0x64);
        first = 1;
        if (target && RHActorPCField<int>(target, 0xb0) == 9)
            second = 1;
        else
            second = 0x41;
        break;
    }
    case 0x5e:
        first = 1; second = 8; break;
    case 0x62:
        first = 1; second = 0x8000; break;
    case 0x64:
        first = 0x2000; second = 1; break;
    case 0x60:
        first = 1; second = 0x10; break;
    case 0x5d: case 0x61: case 0x63: case 0x65:
        first = 1; second = 1; break;
    case 0x66:
        first = 1; second = 0x20; break;
    case 0x2d:
        first = 0x103; second = 0x210; break;
    case 0x67: case 0x68:
        first = 1; second = 0x41; break;
    case 0x0a: case 0x57: case 0x58: case 0x59: case 0x5a: case 0x5b:
    case 0x5c: case 0x5f: case 0x69: case 0x6e: case 0x6f: case 0x70:
    case 0x71: case 0x72: case 0x73: case 0x74: case 0x75:
        first = 1; second = 1; break;
    case 0x6d:
        first = 1; second = 0x41; break;
    default:
        ((RHElementActorHuman *)this)->GetTransitionFlags(element, first, second, third);
    }
}

// FUNCTION: GAME 0x0049b930
void RHElementActorPC::FUN_0049b930(int amount, int unused, bool mode)
{
    int previous = ((RHActorPCVTableCalls *)this)->FUN_51();
    ((RHElementActorHuman *)this)->FUN_00482150(amount, unused, mode);
    int current = ((RHActorPCVTableCalls *)this)->FUN_51();
    RHActorPCField<RHWidgetPortrait *>(this, 0x4ec)->FUN_005d8ed0(current, 100);
    if (current == 0 && !((RHUnk005d73d0Actor *)this)->FUN_0049f510())
        ((RHActorPCVTableCalls *)this)->FUN_slot65(10, 0, 255);
    else if (current < previous - 20)
        ((RHActorPCVTableCalls *)this)->FUN_slot65(8, 0, 255);
}

struct RHPCSpeechNode
{
    RHPCSpeechNode *next;
    RHPCSpeechNode *previous;
    unsigned short action;
    unsigned short time;
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

class RHPCSpeechList
{
public:
    void Advance(int distance)
    {
        while (distance > 0) { current = current->next; --distance; }
        while (distance < 0) { current = current->previous; ++distance; }
    }
    void AdvanceCall(int distance)
    {
        std::bidirectional_iterator_tag category;
        FUN_005c9010(*(RHUnk005c9010Iterator *)&current, distance, category);
    }
    void Seek(int index)
    {
        if (dirty)
        {
            if (index <= (count + 1) / 2)
            {
                current = head->next;
                AdvanceCall(index);
            }
            else
            {
                current = head;
                AdvanceCall(index - count);
            }
            dirty = false;
            position = index;
        }
        else if (index != position)
        {
            if (index < position)
            {
                if (index < (position + 1) / 2)
                {
                    current = head->next;
                    AdvanceCall(index);
                }
                else
                    AdvanceCall(index - position);
            }
            else if (index < (position + count) / 2)
                Advance(index - position);
            else
            {
                current = head;
                Advance(index - count);
            }
            position = index;
        }
    }
    void Erase()
    {
        RHPCSpeechNode *node = current;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --count;
        dirty = true;
    }
    unsigned allocator;
    RHPCSpeechNode *head;
    int count;
    RHPCSpeechNode *current;
    bool dirty;
    int position;
};

// GLOBAL: GAME 0x006c08f2
unsigned short g_unk0x006c08f2;

// Parked: cached-list helper inlining omits original iterator-result frame slots and erase calls.
// STUB: GAME 0x0049c270
void RHElementActorPC::FUN_0049c270()
{
    RHPCSpeechList &list = RHActorPCField<RHPCSpeechList>(this, 0x55c);
    unsigned short count = (unsigned short)list.count;
    if (count)
    {
        unsigned index = count;
        do
        {
            --index;
            ((RHTitbitList *)&list)->At(index);
            ((RHTitbitList *)&list)->At(index);
            --list.current->time;
            list.Seek(index);
            if (list.current->time == 0)
            {
                list.Seek(index);
                list.Erase();
            }
        } while (--count);
    }
}

// Parked: cursor address hoisting adds a saved frame slot and changes list traversal registers.
// STUB: GAME 0x0049c4b0
bool RHElementActorPC::FUN_0049c4b0(unsigned short action)
{
    if (g_unk0x006c08f2 > 0)
        return false;
    RHPCSpeechList &list = RHActorPCField<RHPCSpeechList>(this, 0x55c);
    unsigned short count = (unsigned short)list.count;
    while (count)
    {
        list.Seek(count - 1);
        if (list.current->action = action)
            return false;
        --count;
    }
    return true;
}

class RHPCSequenceCompletionCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c(int result, bool completed) = 0;
};

// FUNCTION: GAME 0x0049d400
void RHElementActorPC::FUN_0049d400(RHSequenceElement *element)
{
    if (element->m_10 != 0x92)
        ((RHElementActorHuman *)this)->FUN_0047a880(element);
    else
    {
        ((RHActorPCVTableCalls *)this)->FUN_slot65(element->Unk00587160(15), 4, element->Unk00587160(17));
        ((RHPCSequenceCompletionCalls *)element)->V0c(0, true);
    }
}

// FUNCTION: GAME 0x0049d520
float RHElementActorPC::FUN_0049d520()
{
    int *actions = (int *)m_5fc;
    unsigned index = 0;
    actions += 0x17;
    for (; index < 4; ++index)
    {
        if (actions[index] == 0x16)
        {
            if (RHActorPCField<int>(m_50, 0x8c) == 0x10)
                return g_unk0x00677f98;
            return g_rhuirendererportrait_percent;
        }
    }
    return g_unk0x00677488;
}

// FUNCTION: GAME 0x0049d590
int RHElementActorPC::FUN_0049d590(int action)
{
    do
    {
        for (unsigned i = 0; i < 3; ++i)
        {
            if (RHActorPCField<int>(m_5fc, 0x48 + i * 4) == action)
                return i;
        }
        if (action != 13)
            return -1;
        action = 14;
    } while (true);
}

// FUNCTION: GAME 0x0049d5c0
int RHElementActorPC::FUN_0049d5c0(unsigned short action)
{
    return RHActorPCField<int>(m_5fc, 0x48 + action * 4);
}

// Parked: zero/result register lifetimes and constant-return widths differ.
// STUB: GAME 0x0049d5e0
unsigned short RHElementActorPC::FUN_0049d5e0(int action)
{
    unsigned short result = 0;
    unsigned short slot = FUN_0049d590(action);
    if (slot != 0xffff)
    {
        result = RHActorPCField<unsigned short>(m_5fc, 0x54 + slot * 2);
        switch (RHActorPCField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c))
        {
        case 2:
            switch (result)
            {
            case 12:
                return 9;
            case 6:
                return 4;
            }
            break;
        case 0:
            switch (result)
            {
            case 12:
                return 15;
            case 6:
                return 8;
            }
            break;
        }
    }
    return result;
}

// FUNCTION: GAME 0x0049d680
void RHElementActorPC::FUN_0049d680(int action)
{
    RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec)->FUN_005d9860();
    if (action)
        RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec)->FUN_005d9700(FUN_0049d590(action));
    RHActorPCField<int>(this, 0x500) = action;
}

// Parked: memset retains a separate destination base and chooses ECX instead of EDX.
// STUB: GAME 0x0049d6c0
void RHScriptBatchCalls::Unk0049d6c0()
{
    int action = RHActorPCField<int>(this, 0x500);
    RHActorPCField<int>(this, 0x500) = 0;
    RHActorPCField<int>(this, 0x504) = action;
    if (RHActorPCField<char>(this, 0x4e8))
    {
        memset((char *)this + 0x50b, 1, 3);
        void *menu = RHActorPCField<void *>(this, 0x4ec);
        if (RHActorPCField<char>(menu, 0xca9))
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(30, this));
        else
            ((RHGamePortraitCalls *)menu)->FUN_005d9b70();
    }
}

// Parked: pending-pointer load folds into a memory comparison.
// STUB: GAME 0x0049d780
void RHHumanActorCalls::FUN_0049d780()
{
    if (!RHActorPCField<void *>(this, 0x268) && RHActorPCField<char>(this, 0x4e8))
    {
        RHMessenger *messenger = RHUnk00546050();
        bool restore = false;
        for (unsigned index = 0; index < 3; ++index)
        {
            if (RHActorPCField<char>(this, 0x50b + index))
            {
                RHActorPCField<char>(this, 0x50b + index) = 0;
                if (!RHActorPCField<char>(this, 0x508 + index))
                {
                    void *menu = RHActorPCField<void *>(this, 0x4ec);
                    if (RHActorPCField<char>(menu, 0xca9))
                        messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(27, this, index));
                    else
                        ((RHWidgetPortrait *)menu)->FUN_005d9bc0();
                    if (((RHElementActorPC *)this)->FUN_0049d5c0(index) == RHActorPCField<int>(this, 0x504))
                        restore = true;
                }
            }
        }
        if (restore)
            messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(22, this, RHActorPCField<int>(this, 0x504)));
    }
}

// FUNCTION: GAME 0x0049d890
void RHElementActorPC::FUN_0049d890(unsigned short action)
{
    if (RHActorPCField<int>(this, 0x500) == FUN_0049d5c0(action))
        RHActorPCField<int>(this, 0x500) = 0;
    if (RHActorPCField<int>(this, 0x504) == FUN_0049d5c0(action))
        RHActorPCField<int>(this, 0x504) = 0;
    RHActorPCField<char>(this, 0x508 + action) = 1;
    RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
    if (RHActorPCField<char>(menu, 0xca9))
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(26, this, action));
    else
        ((RHGamePortraitCalls *)menu)->FUN_005d9950(action);
}

// Parked: input zero-extension and EH receiver/index register lifetimes differ.
// STUB: GAME 0x0049d960
void RHElementActorPC::FUN_0049d960(unsigned short action)
{
    RHActorPCField<char>(this, 0x508 + action) = 0;
    if (!RHActorPCField<char>(this, 0x50b + action))
    {
        RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
        if (RHActorPCField<char>(menu, 0xca9))
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(27, this, action));
        else
            ((RHGamePortraitCalls *)menu)->FUN_005d9a60(action);
    }
}

// FUNCTION: GAME 0x0049da00
void RHElementActorPC::FUN_0049da00(unsigned short action)
{
    RHActorPCField<char>(this, 0x50b + action) = 1;
    int current = RHActorPCField<int>(this, 0x500);
    if (current == FUN_0049d5c0(action))
    {
        RHActorPCField<int>(this, 0x504) = current;
        RHActorPCField<int>(this, 0x500) = 0;
    }
    RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
    if (RHActorPCField<char>(menu, 0xca9))
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(26, this, action));
    else
        ((RHGamePortraitCalls *)menu)->FUN_005d9950(action);
}

// FUNCTION: GAME 0x0049dad0
void RHElementActorPC::FUN_0049dad0(unsigned short action)
{
    RHActorPCField<char>(this, 0x50b + action) = 0;
    if (!RHActorPCField<char>(this, 0x508 + action))
    {
        RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
        if (RHActorPCField<char>(menu, 0xca9))
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(27, this, action));
        else
            ((RHGamePortraitCalls *)menu)->FUN_005d9a60(action);
        int previous = RHActorPCField<int>(this, 0x504);
        if (FUN_0049d5c0(action) == previous)
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(22, this, previous));
    }
}

// Parked: the body combines exception-managed geometry, actor-state branches and many out-of-run action factories.
// STUB: GAME 0x0049dbc0
void RHElementActorPC::FUN_0049dbc0()
{
}

// FUNCTION: GAME 0x0049e720
char RHElementActorPC::FUN_0049e720()
{
    if (((RHActorPCVTableCalls *)this)->FUN_0049e720() ||
        RHActorPCField<char>(this, 0x1ce) || !RHActorPCField<char>(this, 0x12))
        return false;
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action >= 21 && action <= 22)
        return false;
    return true;
}

// FUNCTION: GAME 0x0049e760
void RHElementActorPC::FUN_0049e760(int value)
{
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action != 11)
    {
        if (action > 13 && action <= 16)
        {
            FUN_0049e8f0(value);
            return;
        }
    }
    else
    {
        ((RHPCCombatCalls *)this)->FUN_0049bb20(12, 1);
    }
    ((RHElementActorHuman *)this)->FUN_004748f0((RHActorTranslationSequenceCalls *)value);
}

// FUNCTION: GAME 0x0049e7b0
void RHElementActorPC::FUN_0049e7b0(int value)
{
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action != 11)
    {
        if (action > 13 && action <= 16)
        {
            FUN_0049e8f0(value);
            return;
        }
    }
    else
    {
        ((RHPCCombatCalls *)this)->FUN_0049bb20(12, 1);
    }
    ((RHElementActorHuman *)this)->FUN_00474ad0((RHActorTranslationSequenceCalls *)value);
}

// FUNCTION: GAME 0x0049e800
void RHElementActorPC::FUN_0049e800(int value)
{
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action != 11)
    {
        if (action > 13 && action <= 16)
        {
            FUN_0049e8f0(value);
            return;
        }
    }
    else
    {
        ((RHPCCombatCalls *)this)->FUN_0049bb20(12, 1);
    }
    ((RHElementActorHuman *)this)->FUN_00483c90((RHActorTranslationSequenceCalls *)value);
}

// Parked: the out-of-run callback calls still bind as unmatched offsets, and their receiver scheduling differs.
// STUB: GAME 0x0049e850
void RHElementActorPC::FUN_0049e850(int first, int second)
{
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action > 13 && action <= 16)
        FUN_0049e8f0(first);
    (void)second;
}

// Parked: the out-of-run callback calls still bind as unmatched offsets, and their receiver scheduling differs.
// STUB: GAME 0x0049e8a0
void RHElementActorPC::FUN_0049e8a0(int first, int second)
{
    int action = RHActorPCField<int>(m_50, 0x8c);
    if (action > 13 && action <= 16)
        FUN_0049e8f0(first);
    (void)second;
}

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;
extern char g_unk0x6c0560[4];

#include "RHSequenceGenericCalls.h"

// FUNCTION: GAME 0x0049e8f0
void RHElementActorPC::FUN_0049e8f0(int value)
{
    RHActorTranslationSequenceCalls *sequence = (RHActorTranslationSequenceCalls *)value;
    RHOrder *order;
    switch (RHActorPCField<int>(m_50, 0x8c))
    {
    case 16:
    {
        order = new RHOrder;
        order->m_24 = 0x12d;
        order->m_2a = 0;
        *(RHUnk00613e90 *)(order->m_04 + 4) = RHActorPCField<RHUnk00613e90>(RHActorPCField<void *>(RHActorPCField<void *>(this, 0x254), 0x50), 0x10);
        RHActorPCField<int>(sequence, 0x5c) = 0;
        RHUnk00584d60 *event = new RHUnk00584d60(1, 0x2d, RHActorPCField<void *>(this, 0x254));
        RHActorPCField<void *>(RHActorPCField<void *>(this, 0x254), 0x5cc) = 0;
        RHActorPCField<void *>(this, 0x254) = 0;
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, event);
        break;
    }
    case 14:
    case 15:
        order = new RHOrder;
        order->m_2a = 0;
        order->m_24 = 0x2c;
        if (RHActorPCField<void *>(this, 0x5cc))
        {
            RHUnk00584d60 *event = new RHUnk00584d60(1, 0x2d, RHActorPCField<void *>(this, 0x5cc));
            ((RHMalignityActorCalls *)RHActorPCField<void *>(this, 0x5cc))->V154(event);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, event);
        }
        break;
    default:
        order = (RHOrder *)value;
        break;
    }
    sequence->FUN_00585970(order);
    ((RHMalignityActorCalls *)this)->V154(sequence);
}

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &point);
};

class RHMalignityGridCalls
{
public:
    bool FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &other, unsigned short layer);
};

// Parked: geometry temporary colouring and folded vector-constructor identity differ.
// STUB: GAME 0x0049eab0
bool RHElementActorPC::FUN_0049eab0(SBGeoPoint2D &result)
{
    RHUnk00613e90 origin;
    SBGeoBoundingBox2D bounds;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    void *profile = (char *)m_50 + 4;
    ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(
        *(const RHMobileUnk00607da0 *)((RHUnkPathActorInfoBase *)profile)->Unk0055fa10(
            RHActorPCField<int>(profile, 0x88)));
    ((RHMobileUnk006091b0 *)&bounds)->FUN_006091b0(SBGeoVector2D(SBGeoPoint2D(origin.x, origin.y)));
    unsigned short layer = RHActorPCField<unsigned short>(m_50, 0xde);
    bool successful = ((RHMalignityGridCalls *)g_unk0x6c0a9c)->FUN_004f5e50(bounds,
        SBGeoPoint2D(origin.x, origin.y), layer) == true;
    if (successful)
    {
        result = bounds.FUN_00608f40();
        successful = true;
    }
    else
        successful = false;
    return successful;
}

// FUNCTION: GAME 0x0049ec20
unsigned short RHElementActorPC::FUN_0049ec20(unsigned action)
{
    unsigned short *counter = ((RHPCStatus *)m_600)->GetAmmoCounter(action);
    if (counter)
        return *counter;
    return 0xffff;
}

// FUNCTION: GAME 0x0049ec50
void RHElementActorPC::FUN_0049ec50(unsigned action, unsigned short amount)
{
    unsigned short *counter = ((RHPCStatus *)m_600)->GetAmmoCounter(action);
    if (counter)
    {
        unsigned short slot = FUN_0049d590(action);
        unsigned short previous = *counter;
        if (previous + amount <= FUN_0049d5e0(action))
        {
            *counter = previous + amount;
            ((unsigned short *)((char *)RHActorPCField<void *>(this, 0x4ec) + 0xe50))[slot] = *counter;
        }
        if (*counter != 0)
            FUN_0049d960(slot);
    }
}

class RHElementApple
{
public:
    RHElementApple(RHElementActorHuman *actor);
    char m_data[0x15c];
};

enum RHobjectType
{
};

struct RHElementObjectTypeBits
{
    RHobjectType type : 4;
};

static inline RHobjectType RHActorPCObjectType(const void *element)
{
    return ((const RHElementObjectTypeBits *)((const char *)element + 4))->type;
}

// FUNCTION: GAME 0x0049ece0
void RHElementActorPC::FUN_0049ece0(const void *target)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 destination;
    RHUnk00613e90 direction;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    if (RHActorPCObjectType(target) == 4)
        ((RHElementActor *)target)->FUN_00478c20(destination, false);
    else
        destination = ((RHElementPositionCalls *)target)->FUN_004bb180();
    direction = RHUnk00613e90(origin, destination);
    RHElementApple *apple = new RHElementApple((RHElementActorHuman *)this);
    ((RHUnk004a6310 *)apple)->FUN_004a6310(1);
    ((RHActorPCVTableCalls *)apple)->FUN_28(1);
    *(RHProjectileVector *)&direction = ((RHProjectileThrowCalls *)apple)->FUN_004b4260(*(RHProjectileVector *)&direction, 15.0f, 0.8f, 0, RHActorPCObjectType(target) == 4 ? target : 0);
    ((RHActorPCVTableCalls *)apple)->FUN_34(origin, direction);
    ((RHActorPCVTableCalls *)apple)->FUN_10();
    void *sprite = RHActorPCField<void *>(this, 0x50);
    RHMalignityPosition position;
    position.x = RHActorPCField<float>(sprite, 0x24);
    position.y = RHActorPCField<float>(sprite, 0x28);
    position.layer = RHActorPCField<unsigned short>(sprite, 0xde);
    position.area = RHActorPCField<void *>(sprite, 0xe0);
    RHActorPCField<RHMalignityPosition>(apple, 0x118) = position;
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(apple, 0, 1);
    ((RHActorPCVTableCalls *)this)->FUN_56(0xb, 1, 1);
}

class RHUnk004ba8d0
{
public:
    RHUnk004ba8d0(void *victim);
    char m_data[0x15c];
};

// FUNCTION: GAME 0x0049eeb0
void RHElementActorPC::FUN_0049eeb0(const void *target)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 destination;
    RHUnk00613e90 direction;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    if (RHActorPCObjectType(target) == 4)
        ((RHElementActor *)target)->FUN_00478c20(destination, false);
    else
        destination = ((RHElementPositionCalls *)target)->FUN_004bb180();
    direction = RHUnk00613e90(origin, destination);
    RHUnk004ba8d0 *projectile = new RHUnk004ba8d0(this);
    ((RHUnk004ba900 *)projectile)->FUN_004ba900(1);
    ((RHActorPCVTableCalls *)projectile)->FUN_28(1);
    *(RHProjectileVector *)&direction = ((RHProjectileThrowCalls *)projectile)->FUN_004b4260(*(RHProjectileVector *)&direction, 0.001f, 0.1f, 1, RHActorPCObjectType(target) == 4 ? target : 0);
    ((RHActorPCVTableCalls *)projectile)->FUN_34(origin, direction);
    ((RHActorPCVTableCalls *)projectile)->FUN_10();
    void *sprite = RHActorPCField<void *>(this, 0x50);
    RHMalignityPosition position;
    position.x = RHActorPCField<float>(sprite, 0x24);
    position.y = RHActorPCField<float>(sprite, 0x28);
    position.layer = RHActorPCField<unsigned short>(sprite, 0xde);
    position.area = RHActorPCField<void *>(sprite, 0xe0);
    RHActorPCField<RHMalignityPosition>(projectile, 0x118) = position;
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(projectile, 0, 1);
    ((RHActorPCVTableCalls *)this)->FUN_56(5, 1, 1);
}

class RHElementPurse
{
public:
    RHElementPurse(void *victim);
    char m_data[0x16c];
};

// FUNCTION: GAME 0x0049f080
void RHElementActorPC::FUN_0049f080(const RHUnk00613e90 &point)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 direction;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    direction = RHUnk00613e90(origin, point);
    RHElementPurse *projectile = new RHElementPurse(this);
    ((RHUnk004b91a0 *)projectile)->FUN_004b91a0(1);
    ((RHActorPCVTableCalls *)projectile)->FUN_28(1);
    RHActorPCField<unsigned short>(projectile, 0x168) = 5;
    *(RHProjectileVector *)&direction = ((RHProjectileThrowCalls *)projectile)->FUN_004b4260(*(RHProjectileVector *)&direction, 15.0f, 0.2f, 0, 0);
    ((RHActorPCVTableCalls *)projectile)->FUN_34(origin, direction);
    ((RHActorPCVTableCalls *)projectile)->FUN_10();
    void *sprite = RHActorPCField<void *>(this, 0x50);
    RHMalignityPosition position;
    position.x = RHActorPCField<float>(sprite, 0x24);
    position.y = RHActorPCField<float>(sprite, 0x28);
    position.layer = RHActorPCField<unsigned short>(sprite, 0xde);
    position.area = RHActorPCField<void *>(sprite, 0xe0);
    RHActorPCField<RHMalignityPosition>(projectile, 0x118) = position;
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(projectile, 0, 1);
    ((RHActorPCVTableCalls *)this)->FUN_56(4, 1, 1);
    ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(1, -50);
}

class RHUnk004be050
{
public:
    RHUnk004be050();
    char m_data[0x160];
};

// FUNCTION: GAME 0x0049f210
void RHElementActorPC::FUN_0049f210(const RHUnk00613e90 &point)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 direction;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    direction = RHUnk00613e90(origin, point);
    RHUnk004be050 *projectile = new RHUnk004be050;
    ((RHUnk004be080 *)projectile)->FUN_004be080(1);
    ((RHActorPCVTableCalls *)projectile)->FUN_28(1);
    *(RHProjectileVector *)&direction = ((RHProjectileThrowCalls *)projectile)->FUN_004b4260(*(RHProjectileVector *)&direction, 50.0f, 0.5f, 0, 0);
    ((RHActorPCVTableCalls *)projectile)->FUN_34(origin, direction);
    ((RHActorPCVTableCalls *)projectile)->FUN_10();
    void *sprite = RHActorPCField<void *>(this, 0x50);
    RHMalignityPosition position;
    position.x = RHActorPCField<float>(sprite, 0x24);
    position.y = RHActorPCField<float>(sprite, 0x28);
    position.layer = RHActorPCField<unsigned short>(sprite, 0xde);
    position.area = RHActorPCField<void *>(sprite, 0xe0);
    RHActorPCField<RHMalignityPosition>(projectile, 0x118) = position;
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(projectile, 0, 1);
    ((RHActorPCVTableCalls *)this)->FUN_56(0x13, 1, 1);
}

class RHElementNet
{
public:
    RHElementNet(void *victim);
    void FUN_004b1730();
    char m_data[0x1c8];
};

// FUNCTION: GAME 0x0049f380
void RHElementActorPC::FUN_0049f380(const RHUnk00613e90 &point)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 direction;
    ((RHHumanActorCalls *)this)->FUN_00479430(origin, -666.0f);
    direction = RHUnk00613e90(origin, point);
    RHElementNet *projectile = new RHElementNet(0);
    ((RHUnk004b0980 *)projectile)->FUN_004b0980(1);
    ((RHActorPCVTableCalls *)projectile)->FUN_28(1);
    *(RHProjectileVector *)&direction = ((RHProjectileThrowCalls *)projectile)->FUN_004b4260(*(RHProjectileVector *)&direction, 30.0f, 0.6f, 0, 0);
    ((RHActorPCVTableCalls *)projectile)->FUN_34(origin, direction);
    projectile->FUN_004b1730();
    ((RHActorPCVTableCalls *)projectile)->FUN_10();
    void *sprite = RHActorPCField<void *>(this, 0x50);
    RHMalignityPosition position;
    position.x = RHActorPCField<float>(sprite, 0x24);
    position.y = RHActorPCField<float>(sprite, 0x28);
    position.layer = RHActorPCField<unsigned short>(sprite, 0xde);
    position.area = RHActorPCField<void *>(sprite, 0xe0);
    RHActorPCField<RHMalignityPosition>(projectile, 0x118) = position;
    ((RHUnk004d8460 *)g_pEngine)->FUN_004d8460(projectile, 0, 1);
    ((RHActorPCVTableCalls *)this)->FUN_56(0x11, 1, 1);
}

// FUNCTION: GAME 0x0049f500
unsigned short RHElementActorPC::FUN_0049f500()
{
    return RHActorPCField<unsigned short>(m_600, 0x14);
}

// FUNCTION: GAME 0x0049f520
void RHElementActorPC::FUN_0049f520(unsigned action, unsigned short amount, char notify)
{
    unsigned short *counter = ((RHPCStatus *)m_600)->GetAmmoCounter(action);
    if (counter)
    {
        unsigned short slot = FUN_0049d590(action);
        *counter = amount >= *counter ? 0 : *counter - amount;
        ((unsigned short *)((char *)RHActorPCField<void *>(this, 0x4ec) + 0xe50))[slot] = *counter;
        if (*counter == 0)
        {
            FUN_0049d890(slot);
            if (notify && !RHActorPCField<char>(g_unk0x6c0b3c, 0x5a))
                ((RHActorPCVTableCalls *)this)->FUN_slot65(0x18, 0, 0xff);
        }
    }
}

// FUNCTION: GAME 0x0049f5c0
void RHElementActorPC::FUN_0049f5c0(unsigned action, unsigned short value)
{
    unsigned short *counter = ((RHPCStatus *)m_600)->GetAmmoCounter(action);
    if (counter)
    {
        unsigned short slot = FUN_0049d590(action);
        if (value <= FUN_0049d5e0(action))
        {
            *counter = value;
            ((unsigned short *)((char *)RHActorPCField<void *>(this, 0x4ec) + 0xe50))[slot] = *counter;
            if (*counter == 0)
                FUN_0049d890(slot);
            else
                FUN_0049d960(slot);
        }
    }
}

// FUNCTION: GAME 0x0049f640
void RHElementActorPC::FUN_0049f640(unsigned action, short value)
{
    unsigned short *counter = ((RHPCStatus *)m_600)->GetAmmoCounter(action);
    if (counter)
    {
        unsigned short slot = FUN_0049d590(action);
        *counter = value;
        ((unsigned short *)((char *)RHActorPCField<void *>(this, 0x4ec) + 0xe50))[slot] = *counter;
        if (*counter == 0)
            FUN_0049d890(slot);
        else
            FUN_0049d960(slot);
    }
}

// Parked: this query constructs geometry temporaries and relies on out-of-run coordinate/vector helpers.
// STUB: GAME 0x0049f6c0
unsigned RHElementActorPC::FUN_0049f6c0()
{
    return 0;
}

#include "RHMissionStat.h"

// FUNCTION: GAME 0x0049fa20
void RHElementActorPC::FUN_0049fa20(unsigned amount, void *source)
{
    RHUnk00452030 *campaign = g_unk0x6c07fc;
    if (amount >= (int)((RHActorPCVTableCalls *)this)->FUN_51())
    {
        if (((RHUnk005d73d0Actor *)this)->FUN_0049f510())
            return;
        if (((RHActorPCVTableCalls *)this)->FUN_62() == true && campaign->Get(0) >= 1)
        {
            RHActorPCField<char>(m_600, 0x16) = 1;
            ((RHActorPCVTableCalls *)this)->FUN_slot53(5, (int)source, 0);
            ((RHActorPCVTableCalls *)this)->FUN_slot55(300, (int)source, 0);
            RHMessenger *messenger = RHUnk00546050();
            messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(3, this, 0));
            messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(3, this, 1));
            messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(3, this, 2));
            ((RHWidgetPortrait *)RHActorPCField<void *>(this, 0x4ec))->Method005d73d0();
            ((RHActorPCVTableCalls *)this)->FUN_17(3);
            ((RHUnk00450b60 *)campaign)->Unk(0, -1);
            return;
        }
        ((RHElementActorHuman *)this)->FUN_0047e9a0(amount, (int)source);
    }
    else
        ((RHElementActorHuman *)this)->FUN_0047e9a0(amount, (int)source);
}

// FUNCTION: GAME 0x0049fbc0
bool RHElementActorPC::FUN_0049fbc0()
{
    int &counter = RHActorPCField<int>(this, 0x5ec);
    if (counter == -1)
        return false;
    if (counter == 0)
    {
        counter = -1;
        return true;
    }
    --counter;
    return false;
}

// Parked: VC6 spills the action kind instead of the remaining-room temporary, shifting every carried register.
// STUB: GAME 0x0049fbf0
void RHElementActorPC::FUN_0049fbf0(void *actor, bool consume)
{
    unsigned kind = RHActorPCField<unsigned>(actor, 0xa8);
    unsigned short count = ((RHActorPCVTableCalls *)this)->FUN_57(kind);
    unsigned room = FUN_0049d5e0(kind) - count;
    count = RHActorPCField<unsigned short>(actor, 0xae);
    if (room < count && consume)
    {
        ((RHActorPCVTableCalls *)actor)->FUN_28(count - room);
        count = (unsigned short)room;
    }
    else
        ((RHEngineSerializationCalls *)g_pEngine)->FUN_004d88e0(actor, 0, 1);
    if (consume)
        ((RHActorPCVTableCalls *)this)->FUN_58(kind, count);
}

// FUNCTION: GAME 0x0049fc80
void RHElementActorPC::FUN_0049fc80(int index, unsigned amount)
{
    unsigned previous = RHActorPCField<unsigned>(m_600, 8 + index * 8);
    ((RHScriptBatchCalls *)this)->Unk00485200(index, amount);
    if (previous != RHActorPCField<unsigned>(m_600, 8 + index * 8))
        ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(2, 100);
}

// Parked: random placement and vector construction depend on out-of-run geometry and script helpers.
// STUB: GAME 0x0049fcd0
void RHElementActorPC::FUN_0049fcd0()
{
}

class RHElementActor;
class RHUnk0046bd20
{
public:
    int FUN_0046bd20();
};

class RHSectorActorList
{
public:
    int Unk004b8f80(RHElementActor *const &value, bool mode);
};

#include "RHSequenceInteractionAction.h"

// Parked: VC6 allocates a dedicated zero register for the five null compares (cmp reg,ebx) where the target uses test; EH new-state frames also differ (0.47514).
// STUB: GAME 0x0049fe20
void RHElementActorPC::FUN_0049fe20()
{
    void *owner = RHActorPCField<void *>(this, 0x268);
    if (!owner)
        return;
    RHElementActor *self = (RHElementActor *)this;
    RHSectorActorList *list = (RHSectorActorList *)((char *)g_pEngine + 0x49f8);
    bool listed;
    if (self)
        listed = list->Unk004b8f80(self, true) != -1;
    else
        listed = RHActorPCField<void *>(g_pEngine, 0x4a00) != 0;
    if (listed == true)
        return;
    int state = ((RHUnk0046bd20 *)this)->FUN_0046bd20();
    if (state >= 0x3b && state <= 0x43)
        return;
    int action = ((RHPCCombatCalls *)this)->FUN_00485240(1);
    void *element;
    if (action == 0x34)
        element = new RHUnk00584d60(1, 0x34, this);
    else if (action > 0x3a && action <= 0x43)
    {
        void *target = RHActorPCField<void *>(this, 0x268);
        void *extra = target ? *(void **)(**(char ***)((char *)this + 0x264) + 8) : 0;
        element = new RHUnk00585ea0(1, action, this, extra);
    }
    else
        return;
    ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
}
// FUNCTION: GAME 0x0049ff60
unsigned short RHElementActorPC::FUN_0049ff60()
{
    return RHActorPCField<unsigned short>(m_5fc, 0x8e);
}

// FUNCTION: GAME 0x0049ff70
void RHElementActorPC::FUN_0049ff70()
{
    struct Position
    {
        float x;
        float y;
        float z;
    };
    Position source = *(Position *)((char *)m_50 + 0x10);
    Position destination = source;
    float height = source.z;
    source.z = height + g_unk0x00677484;
    height = destination.z;
    destination.z = height + g_unk0x00677f9c;
    ((RHMalignityGeometryCalls *)m_64)->FUN_004eff80(*(RHUnk00613e90 *)&destination, *(RHUnk00613e90 *)&source, 1);
}

// FUNCTION: GAME 0x0049ffe0
void RHElementActorPC::FUN_0049ffe0(void *first, unsigned char flag, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh)
{
    FUN_004a0020(first, (unsigned char)(flag >> 3) & 1, third, fourth, fifth, sixth, seventh);
}

// Parked: the 0x31d-byte body constructs and dispatches several actions; only its wrapper call shape is modeled.
// STUB: GAME 0x004a0020
void RHElementActorPC::FUN_004a0020(void *, unsigned char, unsigned, unsigned, unsigned, unsigned, unsigned)
{
}

// Parked: event dispatch depends on out-of-run allocation and message-manager calls.
// STUB: GAME 0x004a0340
void RHElementActorPC::FUN_004a0340(void *, void *, unsigned, unsigned, int, char)
{
}

// FUNCTION: GAME 0x004a05a0
void RHElementActorPC::FUN_004a05a0()
{
    RHActorPCField<char>(RHActorPCField<void *>(this, 0x600), 0x16) = 0;
    RHActorPCVTableCalls *vtable = (RHActorPCVTableCalls *)this;
    vtable->FUN_slot55(0, 0, 1);
    vtable->FUN_slot65(0x13, 0, 0xff);
    vtable->FUN_slot53(0x32, 0, 0);
    ((RHScriptBatchCalls *)this)->Unk00464630();
}

// Parked: explicit squared-sum grouping fixes the arithmetic order, but copy and x87 lifetimes still differ.
// STUB: GAME 0x004a05f0
char RHElementActorPC::FUN_004a05f0(const RHElementActorPC *other)
{
    volatile float position[3];
    position[0] = RHActorPCField<float>(other->m_50, 0x10);
    position[1] = RHActorPCField<float>(other->m_50, 0x14);
    position[2] = RHActorPCField<float>(other->m_50, 0x18);
    float deltaX = position[0] - RHActorPCField<float>(m_50, 0x10);
    float deltaY = position[1] - RHActorPCField<float>(m_50, 0x14);
    position[2] -= RHActorPCField<float>(m_50, 0x18);
    deltaY *= g_unk0x006774ec;
    float distance = deltaY * deltaY + position[2] * position[2] + deltaX * deltaX;
    if (distance >= g_unk0x00677fa0)
        return 0;
    return 1;
}

// FUNCTION: GAME 0x004a0670
void RHElementActorPC::FUN_004a0670()
{
    RHMalignityActorCalls **first = RHActorPCField<RHMalignityActorCalls **>(g_pEngine, 0x495c);
    unsigned short count;
    if (!first)
        count = 0;
    else
        count = RHActorPCField<RHMalignityActorCalls **>(g_pEngine, 0x4960) - first;
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = RHActorPCField<RHMalignityActorCalls **>(g_pEngine, 0x495c)[index];
        if (actor->FUN_0048e670(this))
        {
            actor->FUN_0048e870(this);
            break;
        }
    }
}

class RHUnk004a06e0Array
{
public:
    void **m_first;
    void **m_last;
};

extern float g_rhuirendererportrait_percent;

// FUNCTION: GAME 0x004a06e0
void RHElementActorPC::FUN_004a06e0(unsigned char value)
{
    SBGeoPoint2D origin(*(SBGeoPoint2D *)((char *)RHActorPCField<void *>(this, 0x50) + 0x24));
    RHUnk004a06e0Array &actors = *(RHUnk004a06e0Array *)((char *)g_pEngine + 0x48dc);
    unsigned short count = actors.m_first == 0 ? 0 : actors.m_last - actors.m_first;
    for (unsigned short index = 0; index < count; ++index)
    {
        void **first = ((RHUnk004a06e0Array *)((char *)g_pEngine + 0x48dc))->m_first;
        RHElementActorPC *actor = (RHElementActorPC *)first[index];
        if ((RHActorPCField<unsigned>(actor, 4) & 3) == 3 &&
            RHActorPCField<int>(actor, 0xb0) == 8)
        {
            if (origin.Unk005fc110(*(SBGeoPoint2D *)((char *)RHActorPCField<void *>(actor, 0x50) + 0x24))
                    .FUN_005fc700(1.0f) < g_rhuirendererportrait_percent)
                RHActorPCField<char>(actor, 0xfc) = (char)value;
        }
    }
}

// Parked: complex EH-managed geometry setup and virtual dispatch depend on unassigned helper entities.
// STUB: GAME 0x004a07f0
void RHElementActorPC::FUN_004a07f0(unsigned, unsigned, unsigned)
{
}

extern float g_unk0x00677db8;

// GLOBAL: GAME 0x00677fa4
float g_unk0x00677fa4 = 1.3f;

// Parked: two independent x87 loads are scheduled before their target positions.
// STUB: GAME 0x004a0a30
bool RHElementActorPC::FUN_004a0a30(RHUnk00613e90 &position)
{
    RHUnk00613e90 origin;
    RHUnk00613e90 difference;
    ((RHMalignityActorCalls *)this)->FUN_00478c20(origin, false);
    float factor = 1.9499999f;
    int animation = RHActorPCField<volatile int>(m_50, 0x8c);
    if (animation != 0x10)
        factor = 1.5f;
    switch (RHActorPCField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c))
    {
    case 0:
    {
        float value = factor;
        factor = value * g_unk0x00677fa4;
        break;
    }
    case 2:
    {
        float value = factor;
        factor = value * g_unk0x00677db8;
        break;
    }
    }
    difference = position.FUN_005df550(origin);
    float y = difference.y;
    difference.y = y * g_unk0x006774ec;
    if (difference.z >= g_unk0x00677488)
    {
        unsigned range = RHActorPCField<unsigned short>(g_pEngine, 0x4cc0);
        if (difference.x * difference.x + difference.z * difference.z + difference.y * difference.y <
            (range * range) * factor * factor &&
            ((RHMalignityGeometryCalls *)g_unk0x6c0a9c)->FUN_004eff80(origin, position, 2))
        {
            if (RHActorPCField<int>(m_50, 0x8c) == 0x10)
                ((RHActorPCVTableCalls *)this)->FUN_slot65(0xf, 0, 0xff);
            return true;
        }
    }
    else
    {
        SBGeoVector2D planar(difference.x, difference.y);
        unsigned short radius = RHActorPCField<unsigned short>(g_pEngine, 0x4cc0);
        float range = -difference.z;
        range += (int)radius;
        range *= factor;
        if (planar.Unk005fc6d0(1.0f) < range * range &&
            ((RHMalignityGeometryCalls *)g_unk0x6c0a9c)->FUN_004eff80(origin, position, 2))
        {
            if (RHActorPCField<int>(m_50, 0x8c) == 0x10)
                ((RHActorPCVTableCalls *)this)->FUN_slot65(0xf, 0, 0xff);
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x004a0c90
void RHElementActorPC::FUN_004a0c90(int actor, int mode, bool flag)
{
    FUN_004a0cc0(0);
    ((RHElementActorHuman *)this)->FUN_0047c600((RHElementActorHuman *)actor, mode, flag);
}

// FUNCTION: GAME 0x004a0cc0
void RHElementActorPC::FUN_004a0cc0(RHElementActorPC *other)
{
    if (other == 0)
    {
        RHElementActorPC *linked = RHActorPCField<RHElementActorPC *>(this, 0x5e0);
        if (linked)
            RHActorPCField<RHElementActorPC *>(linked, 0x5e4) = 0;
        RHActorPCField<int>(this, 0x5d4) = 0;
        RHActorPCField<int>(this, 0x5d8) = 0;
        RHActorPCField<int>(this, 0x5dc) = 0;
    }
    else
        RHActorPCField<RHElementActorPC *>(other, 0x5e4) = this;
    RHActorPCField<RHElementActorPC *>(this, 0x5e0) = other;
}

// Parked: this action allocates several EH-managed messages and dispatches through unassigned manager helpers.
// STUB: GAME 0x004a0d10
void RHElementActorPC::FUN_004a0d10(void *, void *, unsigned, unsigned, unsigned, unsigned, void *)
{
}

// Parked: local colouring and projection scheduling differ beyond rule 28.
// STUB: GAME 0x004a0f10
RHElementActorPC *RHElementActorPC::CreatePCFromMissionStream(SBFile &file)
{
    RHCampaignProfiles *profiles = g_unk0x6c0e84;
    if (profiles == 0)
    {
        profiles = new RHCampaignProfiles;
        g_unk0x6c0e84 = profiles;
    }
    RHBonusGlobalView *global = (RHBonusGlobalView *)g_unk0x6c0a9c;
    RHActorPCProfileCalls *campaign = (RHActorPCProfileCalls *)g_unk0x6c07fc;
    char scripted;
    short x;
    short y;
    int flags;
    int action;
    unsigned short projectionIndex;
    unsigned short areaIndex;
    unsigned short layer;
    int value;
    int profileIndex;
    int unused;
    file.Access(&x, 2);
    file.Access(&y, 2);
    file.Access(&flags, 4);
    file.Access(&action, 4);
    file.Access(&projectionIndex, 2);
    file.Access(&areaIndex, 2);
    file.Access(&layer, 2);
    file.Access(&value, 4);
    file.Access(&profileIndex, 4);
    file.Access(&unused, 4);
    profiles = (RHCampaignProfiles *)profiles->m_14;
    void *profile = ((void **)profiles)[profileIndex];
    RHPCDescription *description;
    if (!*((char *)profile + 0x35))
    {
        description = new RHPCDescription(profile, true);
        campaign->FUN_00455d40(description);
    }
    else
    {
        description = campaign->FUN_00455ce0(profile);
        if (description == 0)
        {
            description = new RHPCDescription(profile, true);
            campaign->FUN_00455d40(description);
        }
        else
            description->m_14 = 100;
    }
    RHElementActorPC *actor = (RHElementActorPC *)new RHUnk0048f280(description);
    description->m_44 = 1;
    ((RHEngineSerializationCalls *)actor)->FUN_0048fa30();
    {
        SBGeoVector2D vector(*(SBGeoVector2D *)((char *)actor->m_5fc + 0x84));
        ((SBGeoVector2D *)((char *)&((RHActorPCInfo *)actor->m_50)->Position() + 0x80))->operator=(vector);
    }
    actor->m_50->m_4.SetPoint(SBGeoPoint2D((float)x, (float)y));
    ((RHActorPCInfo *)actor->m_50)->Layer(layer);
    ((RHActorPCInfo *)actor->m_50)->Area(areaIndex == 0xffff ? global->m_4184 : global->m_4064[areaIndex]);
    RHBonusProjection *projection = projectionIndex == 0xffff ? 0 : global->m_4144[projectionIndex];
    if (projection != 0)
    {
        if (!(projection->Flags() & 1))
            SBAssert(1, g_actorPCFile, 0x2712,
                // STRING: GAME 0x006ae824
                "Warning ! PC (%d,%d) not lying on projection area !", actor->m_50->X(), actor->m_50->Y());
        if (!projection->Inside(actor->m_50->m_4.m_20))
            SBAssert(1, g_actorPCFile, 0x2716,
                // STRING: GAME 0x006ae7d8
                "Warning ! PC (%d,%d) map position not lying in projection area screen box !", actor->m_50->X(), actor->m_50->Y());
    }
    actor->m_50->m_4.FUN_0055fa20(projection);
    ((RHActorPCInfo *)actor->m_50)->Value(value);
    actor->m_50->m_4.FUN_0055f290();
    actor->m_50->FUN_005bd560(0, true);
    ((RHActorPCInfo *)actor->m_50)->Restore();
    actor->m_50->RestorePoint();
    actor->m_50->m_4.SetFlags(flags & 0xf);
    file.Access(&scripted, 1);
    if (scripted)
    {
        std::string name;
        FUN_005e0c90(file, name);
        if (name.size() == 0)
            SBAssert(1, g_actorPCFile, 0x65,
                "Script error: a scripted object had no valid script class name.");
        if (g_unk0x6c0691 == 1)
        {
            ((RHUnkSectorScript *)((char *)actor + 0xa8))->Unk00639a30(name);
            actor->m_108 = actor ? (char *)actor + 0xa8 : 0;
        }
    }
    if (g_unk0x6c0691 && actor->m_100)
        ((RHActorScriptContext *)(actor ? (char *)actor + 0x108 : 0))->FUN_004030a0();
    actor->InitializeAction(action);
    ((RHScriptBatchCalls *)actor)->Unk00464630();
    return actor;
}

// FUNCTION: GAME 0x004a1450
void RHElementActorPC::InitializeAction(int action)
{
    struct PositionStorage
    {
        float first[3];
        float second[3];
    } storage;
    switch (action)
    {
    case 0:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 1);
        break;
    case 3:
    case 270:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 0);
        break;
    case 14:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(10, 0);
        break;
    case 45:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(13, 0);
        break;
    case 47:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(12, 0);
        break;
    case 48:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(3, 0);
        break;
    case 134:
        {
            ((RHScriptBatchCalls *)this)->Unk0046bcf0(21, 0);
            RHUnk00613e90 *position = (RHUnk00613e90 *)storage.first;
            position->RHUnk00613e90::RHUnk00613e90();
            ((RHScriptBatchCalls *)g_unk0x6c10e8)->Unk005c2ec0(position, 0, 15, this, 0, 0, 0, -1);
        }
        break;
    case 136:
        {
            ((RHScriptBatchCalls *)this)->Unk0046bcf0(22, 0);
            RHUnk00613e90 *position = (RHUnk00613e90 *)storage.second;
            position->RHUnk00613e90::RHUnk00613e90();
            ((RHScriptBatchCalls *)g_unk0x6c10e8)->Unk005c2ec0(position, 0, 15, this, 0, 0, 0, -1);
        }
        break;
    case 159:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(8, 0);
        break;
    case 162:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(6, 0);
        break;
    case 219:
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(18, 0);
        break;
    default:
        SBAssert(0, g_actorPCFile, 0x276d, g_unknownInitialAction, action);
        ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 0);
        break;
    }
}

extern "C" int __cdecl rand();

// FUNCTION: GAME 0x004a18c0
bool RHElementActorPC::FUN_004a18c0(void *target)
{
    if (((RHActorPCHumanCalls *)this)->FUN_004859b0(target) == 1)
    {
        unsigned short chance = *(unsigned short *)(*(char **)(*(char **)((char *)this + 0x25c) + 4) + 0x14);
        bool result = rand() % 101 > chance;
        return result;
    }
    return false;
}

// FUNCTION: GAME 0x0050efb0
void RHActorPCEngineCalls::FUN_0050efb0(void *value)
{
    m_196c->AddPortrait((RHWidgetPortrait *)value);
}

// FUNCTION: GAME 0x005492a0
RHUnk00549250::RHUnk00549250(int command, void *actor, int action)
    : RHMessage(2, action), m_0c(command), m_10(actor)
{
}

// FUNCTION: GAME 0x005492d0
RHUnk00549250::~RHUnk00549250()
{
}

// FUNCTION: GAME 0x0055fa10
void *RHUnkPathActorInfoBase::Unk0055fa10(int value)
{
    return (char *)this + 0x94;
}

// FUNCTION: GAME 0x0055fa20
void RHBonusInfoBase::FUN_0055fa20(RHBonusProjection *projection)
{
    RHActorPCField<RHBonusProjection *>(this, 0xe8) = projection;
    if (projection)
    {
        RHActorPCField<void *>(this, 0xec) = (char *)projection + 0xa8;
        m_4 &= ~1;
        RHActorPCField<unsigned>(this, 8) &= ~2;
    }
    else
    {
        unsigned flags = m_4;
        RHActorPCField<void *>(this, 0xec) = 0;
        m_4 = flags & ~1;
        RHActorPCField<unsigned>(this, 8) &= ~2;
    }
}

// GLOBAL: GAME 0x006774cc
float g_unk0x006774cc = 0.001f;

// FUNCTION: GAME 0x005644c0
RHCampaignProfiles::RHCampaignProfiles()
{
    char listAllocator;
    RHActorPCField<char>(this, 4) = listAllocator;
    RHActorPCProfileNode *head = new RHActorPCProfileNode;
    head->next = head;
    head->previous = head;
    RHActorPCField<RHActorPCProfileNode *>(this, 8) = head;
    RHActorPCField<int>(this, 0xc) = 0;
    char firstAllocator;
    RHActorPCField<char>(this, 0x10) = firstAllocator;
    RHActorPCField<int>(this, 0x14) = 0;
    RHActorPCField<int>(this, 0x18) = 0;
    RHActorPCField<int>(this, 0x1c) = 0;
    char secondAllocator;
    RHActorPCField<char>(this, 0x20) = secondAllocator;
    RHActorPCField<int>(this, 0x24) = 0;
    RHActorPCField<int>(this, 0x28) = 0;
    RHActorPCField<int>(this, 0x2c) = 0;
    char thirdAllocator;
    RHActorPCField<char>(this, 0x30) = thirdAllocator;
    RHActorPCField<int>(this, 0x34) = 0;
    RHActorPCField<int>(this, 0x38) = 0;
    RHActorPCField<int>(this, 0x3c) = 0;
    char fourthAllocator;
    RHActorPCField<char>(this, 0x40) = fourthAllocator;
    RHActorPCField<int>(this, 0x44) = 0;
    RHActorPCField<int>(this, 0x48) = 0;
    RHActorPCField<int>(this, 0x4c) = 0;
    char fifthAllocator;
    RHActorPCField<char>(this, 0x50) = fifthAllocator;
    RHActorPCField<int>(this, 0x54) = 0;
    RHActorPCField<int>(this, 0x58) = 0;
    RHActorPCField<int>(this, 0x5c) = 0;
    char sixthAllocator;
    RHActorPCField<char>(this, 0x60) = sixthAllocator;
    RHActorPCField<int>(this, 0x64) = 0;
    RHActorPCField<int>(this, 0x68) = 0;
    RHActorPCField<int>(this, 0x6c) = 0;
    RHActorPCField<unsigned>(this, 0) = 0x679be0;
    g_unk0x6c0e84 = this;
}

// FUNCTION: GAME 0x005bd560
void RHBonusInfo::FUN_005bd560(void *value, bool flag)
{
    if (value == 0)
        RHActorPCField<unsigned>(this, 0x1c4) = RHActorPCField<unsigned>(this, 0x14);
    else if (flag)
        RHActorPCField<float>(this, 0x1c4) = RHActorPCField<float>(RHActorPCField<void *>(value, 0x50), 0x1c4) - g_unk0x006774cc;
    else
    {
        float depth = RHActorPCField<float>(RHActorPCField<void *>(value, 0x50), 0x1c4);
        RHActorPCField<float>(this, 0x1c4) = depth + g_unk0x006774cc;
    }
}

// FUNCTION: GAME 0x005d9700
void RHActorPCWidgetCalls::FUN_005d9700(unsigned short action)
{
    switch (action)
    {
    case 0:
        {
            RHActorPCWidgetState *state = (RHActorPCWidgetState *)((char *)this + 0x344);
            state->Mark();
            state->ClearLinked();
        }
        break;
    case 1:
        {
            RHActorPCWidgetState *state = (RHActorPCWidgetState *)((char *)this + 0x42c);
            state->Mark();
            if (state->m_d0)
                state->m_d0->FUN_005db620(state);
        }
        break;
    case 2:
        {
            RHActorPCWidgetState *state = (RHActorPCWidgetState *)((char *)this + 0x514);
            state->Mark();
            state->ClearLinked();
        }
        break;
    }
}

template<class T>
inline T &RHActorPCWidgetField(void *actor, int offset)
{
    return *(T *)((char *)actor + offset);
}

// FUNCTION: GAME 0x005d9860
void RHActorPCWidgetCalls::FUN_005d9860()
{
    if (RHActorPCWidgetField<char>(this, 0x410) == 1)
    {
        RHActorPCWidgetField<char>(this, 0x410) = 0;
        RHActorPCWidgetField<int>(this, 0x390) = 0;
        if (RHActorPCWidgetField<int>(this, 0x3c0) == 8)
            RHActorPCWidgetField<int>(this, 0x3c0) = 5;
        if (RHActorPCWidgetField<int>(this, 0x3c0) == 9)
            RHActorPCWidgetField<int>(this, 0x3c0) = 6;
    }
    if (RHActorPCWidgetField<char>(this, 0x4f8) == 1)
    {
        RHActorPCWidgetField<char>(this, 0x4f8) = 0;
        RHActorPCWidgetField<int>(this, 0x478) = 0;
        if (RHActorPCWidgetField<int>(this, 0x4a8) == 8)
            RHActorPCWidgetField<int>(this, 0x4a8) = 5;
        if (RHActorPCWidgetField<int>(this, 0x4a8) == 9)
            RHActorPCWidgetField<int>(this, 0x4a8) = 6;
    }
    if (RHActorPCWidgetField<char>(this, 0x5e0) == 1)
    {
        RHActorPCWidgetField<char>(this, 0x5e0) = 0;
        RHActorPCWidgetField<int>(this, 0x560) = 0;
        if (RHActorPCWidgetField<int>(this, 0x590) == 8)
            RHActorPCWidgetField<int>(this, 0x590) = 5;
        if (RHActorPCWidgetField<int>(this, 0x590) == 9)
            RHActorPCWidgetField<int>(this, 0x590) = 6;
    }
}

// FUNCTION: GAME 0x00608400
bool SBGeoBoundingBox2D::FUN_00608400(const SBGeoPoint2D &point) const
{
    if (!m_flag)
        return false;
    return m_p0.m_x <= point.m_x && m_p1.m_x >= point.m_x
        && m_p0.m_y <= point.m_y && m_p1.m_y >= point.m_y;
}

void RHActorPCEmitHelpers(RHActorPCProfileCalls *profiles, RHActorPCTemplateCalls *actor, RHActorPCEngineCalls *engine, void *value)
{
    profiles->FUN_00455ce0(value);
    profiles->FUN_00455d40((RHPCDescription *)value);
    actor->FUN_00493660(0);
    engine->FUN_0050efb0(value);
    ((RHActorPCWidgetCalls *)value)->FUN_005d9860();
    ((RHActorPCWidgetCalls *)value)->FUN_005d9700(0);
}
