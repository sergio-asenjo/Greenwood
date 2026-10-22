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
    void *FUN_0050e530();
    char FUN_0050e5c0();
    void FUN_0050e5d0(char value);
    char FUN_0050e5e0();
    void FUN_0050e850();
    void FUN_0050e860();
    void FUN_0050eb80(bool value);
    void FUN_0050ebe0(char value);
    void FUN_0050eca0(bool value);
    void FUN_0050ed10(bool value);
    void FUN_0050ec40(char value);
    void FUN_0050e800();
    int FUN_0050e7d0();
    void FUN_0050e7b0();
    void FUN_00512310();
    void FUN_0050f1a0(RHSaveGame *saveGame);
    bool FUN_0050f2d0(bool loading);
    bool SerializeForSherwood();
    void FUN_005105d0(unsigned char first, char second);
    bool FUN_00510750();
    bool FUN_005107a0(int *event);
    void FUN_00514140();
    void FUN_00513d00(void *);
    void FUN_00512c90(void *);
    void FUN_00513ae0(void *);
    void FUN_00513ac0(void *);
    void FUN_00513070(void *);
    void FUN_00513d10(void *);
    void FUN_00513490(void *);
    void FUN_00513d70(void *);
    void FUN_00513090(void *);
    void FUN_005139b0(void *);
    void FUN_00513360(void *);
    void FUN_00513110(void *);
    void FUN_005131d0(void *);
    void FUN_00513d30(void *);
    void FUN_005139e0(void *);
    void FUN_00513a20(void *);
    void FUN_00513da0(void *);
    void FUN_00513620(void *);
    void FUN_005130c0(void *);
    void FUN_00513a60(void *);
    void FUN_005134c0(void *);
    void FUN_00513df0(void *event);
    void FUN_00513150(void *);
    void FUN_005140b0();
    static void FUN_005145b0();
    static void GenerateDeadZoneForMouseInput();
    void FUN_00512be0(void *);
    void FUN_00513ff0();
    void FUN_00513390(void *);
    void FUN_00513520(void *);
    void FUN_005138b0(void *event);
    void FUN_00513210(void *);
    void FUN_00513e60();
    unsigned short FUN_00514470();
    void FUN_00512eb0(void *);
    void FUN_00513b00(int value);
    void FUN_00512cb0(void *event);
    void FUN_00513670(void *event);
    void FUN_00514c50();
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
    bool m_5d; // 0x5d
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
