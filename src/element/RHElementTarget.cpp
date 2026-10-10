#include "RHElementTarget.h"

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
    *(unsigned long *)(m_data + 0x54) = Draw()->Unk005e4ed0(((RHCivilianSpriteView *)Info())->FUN_005bdef0(), ((RHCivilianSpriteView *)Info())->FUN_005bdf20(), 0, 0);
    *(unsigned long *)(m_data + 0x58) = Draw()->Unk005e4ed0(((RHCivilianSpriteView *)Info())->FUN_005bdef0() + 6, ((RHCivilianSpriteView *)Info())->FUN_005bdf20(), 0, 0);
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
        ((RHUnkTargetScriptRef *)(m_data + 0x15c))->FUN_004034e0();
}

void RHElementTarget::Emit(SBFile &file)
{
    InitializeFromMissionStream(file);
}
