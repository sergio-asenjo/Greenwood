#include "RHElementActorPC.h"
#include "RHElementActorPC_calls.h"

extern RHUnk005c38b0 *g_unk0x6c10e8;

// STRING: GAME 0x006ae5e0
#define g_actorPCFile "P:\\Robin Hood\\RHelementactorpc.cpp"
// STRING: GAME 0x006ae858
#define g_unknownInitialAction "ACHTUNG : Unknown initial action %d !"

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
}
