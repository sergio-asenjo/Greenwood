#ifndef RHELEMENTTARGET_H
#define RHELEMENTTARGET_H

#include "RHElementScroll.h"

class RHUnkTargetPoints
{
public:
    void FUN_00611100(const SBGeoPoint2D &point);
};

class RHUnkTargetSprite : public RHBonusInfo
{
public:
    bool FUN_005bd050(int kind, const std::string &name, const std::string &profile, int flag);
    bool FUN_005b76e0(unsigned index, unsigned short row);
};

class RHCivilianSpriteView
{
public:
    unsigned short FUN_005bdef0();
    unsigned short FUN_005bdf20();
    undefined m_00[0x19a];
    undefined2 m_19a;
    undefined2 m_19c;
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int width, int height, int flags, int retain);
};

class RHUnk005df4f0 : public RHBonusTriple
{
public:
    RHUnk005df4f0(float x, float y, float z);
};

class RHUnkTargetScriptRef
{
public:
    void FUN_004034e0();
};

class RHElementTarget
{
public:
    void InitializeFromMissionStream(SBFile &file);
    void Emit(SBFile &file);
    RHUnkTargetSprite *&Info() { return *(RHUnkTargetSprite **)(m_data + 0x50); }
    RHUnkFXDraw *&Draw() { return *(RHUnkFXDraw **)(m_data + 0x60); }
    RHBonusGlobalView *&Global() { return *(RHBonusGlobalView **)(m_data + 0x64); }
    char m_data[0x16c]; // +0x50 sprite, +0x54/+0x58 surfaces, +0x60 draw, +0x64 registry
};

#define RHElementTarget_m_a8 (*(int *)(m_data + 0xa8))
#define RHElementTarget_m_d4 (*(RHUnkTargetPoints *)(m_data + 0xd4))
#define RHElementTarget_m_f8 (*(float *)(m_data + 0xf8))
#define RHElementTarget_m_fc (*(RHUnkSectorScript *)(m_data + 0xfc))
#define RHElementTarget_m_154 (*(char *)(m_data + 0x154))
#define RHElementTarget_m_15c (*(RHUnkSectorScript **)(m_data + 0x15c))
#define RHElementTarget_m_168 (*(unsigned *)(m_data + 0x168))

#endif
