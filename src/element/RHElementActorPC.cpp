#include "RHElementActorPC.h"
#include "RHElementActorPC_calls.h"

DECOMP_SIZE_ASSERT(RHElementActorPC, 0x60c)
DECOMP_SIZE_ASSERT(RHUnk005492a0, 0x14)
DECOMP_SIZE_ASSERT(RHActorPCBoxCalls, 0x14)
DECOMP_SIZE_ASSERT(RHActorPCWidgetState, 0xe8)
DECOMP_SIZE_ASSERT(RHCampaignProfiles, 0x70)
DECOMP_SIZE_ASSERT(RHActorPCProfileNode, 0x18)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHPCDescription, 0x48)
DECOMP_SIZE_ASSERT(RHUnk0048f280, 0x60c)
DECOMP_SIZE_ASSERT(RHUnk005fc030, 0x08)

extern RHUnk005c38b0 *g_unk0x6c10e8;
RHMessenger *RHUnk00546050();

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

// Parked: flat subobjects omit the original member-cleanup EH states.
// STUB: GAME 0x0048f280
RHUnk0048f280::RHUnk0048f280(void *description)
{
    ((RHUnk00471630 *)this)->RHUnk00471630::RHUnk00471630(12, 0, description);
    ((RHUnk005fc030 *)((char *)this + 0x4f0))->RHUnk005fc030::RHUnk005fc030();
    RHActorPCField<int>(this, 0x4f8) = 0;
    RHActorPCField<char>(this, 0x4fc) = 0;
    char allocator;
    RHActorPCField<char>(this, 0x55c) = allocator;
    RHActorPCField<RHScriptNode *>(this, 0x560) = ((RHUnk0046eb30 *)((char *)this + 0x55c))->Unk0059f720(0, 0);
    RHActorPCField<int>(this, 0x564) = 0;
    RHActorPCField<char>(this, 0x56c) = 1;
    ((RHUnk005fc030 *)((char *)this + 0x584))->RHUnk005fc030::RHUnk005fc030();
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
    RHActorPCField<RHUnk005492a0 *>(this, 0x4ac) = new RHUnk005492a0(1, this, 0);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4b0) = new RHUnk005492a0(1, this, 1);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4b4) = new RHUnk005492a0(1, this, 2);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4b8) = new RHUnk005492a0(3, this, 0);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4bc) = new RHUnk005492a0(3, this, 1);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4c0) = new RHUnk005492a0(3, this, 2);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4c4) = new RHUnk005492a0(10, this, 0);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4c8) = new RHUnk005492a0(10, this, 1);
    RHActorPCField<RHUnk005492a0 *>(this, 0x4cc) = new RHUnk005492a0(10, this, 2);
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
        SBGeoVector2D vector(*(SBGeoPoint2D *)((char *)actor->m_5fc + 0x84));
        RHBonusInfoBase &position = ((RHActorPCInfo *)actor->m_50)->Position();
        ((RHUnk005fc3b0 *)((char *)&position + 0x80))->FUN_005fc430(vector);
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

int RHElementActorPC::FUN_0049d5c0(unsigned short action)
{
    return RHActorPCField<int>(m_5fc, 0x48 + action * 4);
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
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk005492a0(26, this, action));
    else
        menu->FUN_005d9950(action);
}

// Parked: EH prologue and receiver/index register allocation differ.
// STUB: GAME 0x0049d960
void RHElementActorPC::FUN_0049d960(unsigned short action)
{
    RHActorPCField<char>(this, 0x508 + action) = 0;
    if (!RHActorPCField<char>(this, 0x50b + action))
    {
        RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
        if (RHActorPCField<char>(menu, 0xca9))
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk005492a0(27, this, action));
        else
            menu->FUN_005d9a60(action);
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
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk005492a0(26, this, action));
    else
        menu->FUN_005d9950(action);
}

// FUNCTION: GAME 0x0049dad0
void RHElementActorPC::FUN_0049dad0(unsigned short action)
{
    RHActorPCField<char>(this, 0x50b + action) = 0;
    if (!RHActorPCField<char>(this, 0x508 + action))
    {
        RHActorPCWidgetCalls *menu = RHActorPCField<RHActorPCWidgetCalls *>(this, 0x4ec);
        if (RHActorPCField<char>(menu, 0xca9))
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk005492a0(27, this, action));
        else
            menu->FUN_005d9a60(action);
        int previous = RHActorPCField<int>(this, 0x504);
        if (FUN_0049d5c0(action) == previous)
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk005492a0(22, this, previous));
    }
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
        SBGeoVector2D vector(*(SBGeoPoint2D *)((char *)actor->m_5fc + 0x84));
        ((RHUnk005fc3b0 *)((char *)&((RHActorPCInfo *)actor->m_50)->Position() + 0x80))->FUN_005fc430(vector);
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

void RHElementActorPC::Emit(int action)
{
    InitializeAction(action);
    FUN_0049d590(action);
    FUN_0049d890(action);
    FUN_0049d960(action);
    FUN_0049da00(action);
    FUN_0049dad0(action);
}

// deferred: 0x0050efb0 is byte-exact; unannotated pending reccmp #534.
void RHActorPCEngineCalls::FUN_0050efb0(void *value)
{
    m_196c->FUN_0055e710(value);
}

// deferred: 0x005492a0 is byte-exact; unannotated pending reccmp #534.
RHUnk005492a0::RHUnk005492a0(int command, void *actor, int action)
{
    ((RHActorPCMessageBaseCalls *)this)->FUN_00549030(2, action);
    m_c = command;
    m_10 = actor;
    m_0 = 0x679b6c;
}

// deferred: 0x0055fa10 is byte-exact; called by RHPath::TestIfPathIsFine.
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

// Parked: comparison scheduling differs; effective-only match.
// STUB: GAME 0x005d9860
void RHActorPCWidgetCalls::FUN_005d9860()
{
    if (RHActorPCField<char>(this, 0x410) == 1)
    {
        RHActorPCField<char>(this, 0x410) = 0;
        RHActorPCField<int>(this, 0x390) = 0;
        if (RHActorPCField<int>(this, 0x3c0) == 8)
            RHActorPCField<int>(this, 0x3c0) = 5;
        if (RHActorPCField<int>(this, 0x3c0) == 9)
            RHActorPCField<int>(this, 0x3c0) = 6;
    }
    if (RHActorPCField<char>(this, 0x4f8) == 1)
    {
        RHActorPCField<char>(this, 0x4f8) = 0;
        RHActorPCField<int>(this, 0x478) = 0;
        if (RHActorPCField<int>(this, 0x4a8) == 8)
            RHActorPCField<int>(this, 0x4a8) = 5;
        if (RHActorPCField<int>(this, 0x4a8) == 9)
            RHActorPCField<int>(this, 0x4a8) = 6;
    }
    if (RHActorPCField<char>(this, 0x5e0) == 1)
    {
        RHActorPCField<char>(this, 0x5e0) = 0;
        RHActorPCField<int>(this, 0x560) = 0;
        if (RHActorPCField<int>(this, 0x590) == 8)
            RHActorPCField<int>(this, 0x590) = 5;
        if (RHActorPCField<int>(this, 0x590) == 9)
            RHActorPCField<int>(this, 0x590) = 6;
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
