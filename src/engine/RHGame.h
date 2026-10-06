#ifndef RHGAME_H
#define RHGAME_H

class SBFile;
class RHMenuCampaignMap;
class RHMenuMissionDescription;
class RHMenuBuyBlazons;
class RHGameBlazonWidget;
class RHSaveGame;

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
    char m_opaque00[0x18];
    void *m_18;
    char m_opaque1c[0x54 - 0x1c];
    char m_54;
    char m_55;
    char m_56;
    char m_57;
    char m_58;
    char m_59;
    char m_5a;
    char m_5b;
    char m_5c;
    char m_5d;
    char m_5e;
    char m_5f;
    char m_60;
    char m_61;
    char m_62;
    char m_opaque63[0x29b0 - 0x63];
    RHGameBlazonWidget *m_29b0;
    char m_opaque29b4[0x3558 - 0x29b4];
    char m_3558;
    char m_3559;
    char m_355a;
    char m_355b;
    char m_opaque355c[0x3578 - 0x355c];
    void *m_3578;
};

#endif
