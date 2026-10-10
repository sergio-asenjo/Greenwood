#ifndef RHGAME_H
#define RHGAME_H

#include "Decomp.h"

class SBFile;
class RHMenuCampaignMap;
class RHMenuMissionDescription;
class RHMenuBuyBlazons;
class RHGameBlazonWidget;
class RHSaveGame;

// SIZE 0x357c
class RHGame
{
public:
    bool Serialize(SBFile &file);
    bool Serialize(unsigned long mode, RHSaveGame *saveGame, bool loading);
    void DisplayLostLeicester();
    void UpdateBlazons(RHMenuCampaignMap *map, RHMenuMissionDescription *description, RHMenuBuyBlazons *buy, bool flag);
    void FUN_0050e850();
    void FUN_0050e800();
    void FUN_0050e7b0();
    void FUN_0050f1a0(RHSaveGame *saveGame);
    void FUN_00514140();
    void Emit(SBFile &file);

private:
    undefined m_opaque00[0x18]; // 0x00
    void *m_18; // 0x18
    undefined m_opaque1c[0x54 - 0x1c]; // 0x1c
    char m_54; // 0x54
    char m_55; // 0x55
    char m_56; // 0x56
    char m_57; // 0x57
    char m_58; // 0x58
    char m_59; // 0x59
    char m_5a; // 0x5a
    char m_5b; // 0x5b
    char m_5c; // 0x5c
    char m_5d; // 0x5d
    char m_5e; // 0x5e
    char m_5f; // 0x5f
    char m_60; // 0x60
    char m_61; // 0x61
    char m_62; // 0x62
    undefined m_opaque63[0x29b0 - 0x63]; // 0x63
    RHGameBlazonWidget *m_29b0; // 0x29b0
    undefined m_opaque29b4[0x3558 - 0x29b4]; // 0x29b4
    char m_3558; // 0x3558
    char m_3559; // 0x3559
    char m_355a; // 0x355a
    char m_355b; // 0x355b
    undefined m_opaque355c[4]; // 0x355c
    unsigned m_3560; // 0x3560
    undefined m_opaque3564[0x3578 - 0x3564]; // 0x3564
    void *m_3578; // 0x3578
};

#endif
