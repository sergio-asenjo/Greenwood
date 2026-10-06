#ifndef RHGAME_CALLS_H
#define RHGAME_CALLS_H

#include "RHMessenger.h"
#include "RHGame.h"
#include <string>
#include <windows.h>

class RHMenuCampaignMap;
class RHMenuMissionDescription;
class RHMenuBuyBlazons;
class RHGameBlazonWidget;

RHMessenger *RHUnk00546050();

struct RHGameMissionProfile
{
    char m_00[0x34];
    int m_34;
    char m_38[0x30];
    unsigned short m_68;
    unsigned short m_6a;
};

struct RHGameMission
{
    RHGameMissionProfile *m_profile;
};

class RHUnk00452030
{
public:
    int Get(int index);
};

class RHUnk00450b60
{
public:
    void Unk(int property, int amount);
};

class RHScriptBatchCalls
{
public:
    void Unk004520e0(int index, int value);
    void Unk004e3220(int value);
};

class RHGameCampaignView
{
public:
    char m_00[0x178];
    RHGameMission *m_178;
    RHGameMission *m_17c;
    RHGameMission *m_180;
    void FUN_00451a90();
    void FUN_00453b70(RHGameMission *mission);
    int FUN_00456190(RHGameMission *mission);
    int FUN_004561d0(RHGameMission *mission);
    int FUN_00456230(RHGameMission *mission);
    void FUN_00456540(bool flag, RHGameMission *mission);
};

class RHGameMenuCalls
{
public:
    void FUN_005283d0();
    void FUN_00535950(int first, int second, int third);
    void FUN_00544b30();
    void FUN_00528380(const std::wstring &text);
};

class RHGameBlazonWidget
{
public:
    void FUN_005cc900(int value);
    void FUN_005cc920(int value);
};

extern RHUnk00452030 *g_unk0x6c07fc;
class RHEngine;
extern RHEngine *g_pEngine;

class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &name, int mode);
    void FUN_005f5290();
    char m_14[0x44];
};

class RHSaveGame
{
public:
    struct Header
    {
        Header();
        unsigned long m_00;
        unsigned long m_04;
        unsigned long m_08;
    };
    std::string FUN_0056e5d0() const;
    static bool SerializeHeader(SBFile &file, Header &header);
};

class RHGameSaveCalls
{
public:
    std::string FUN_0056e6b0();
    char FUN_0056e790();
    bool FUN_0056e7f0();
    bool FUN_0056e850();
    void FUN_0056ecc0();
};

class RHEngine
{
public:
    bool FUN_004c4570(SBFile &file);
};

class RHCampaign
{
public:
    bool Serialize(SBFile &file);
    bool CopyBackupTo(SBFile &file) const;
};

class RHGameConfig
{
public:
    RHGameConfig();
    ~RHGameConfig();
    void FUN_006134a0(void *configuration);
    bool FUN_00611960(SBFile &file);
    char m_00[0x38];
};

class RHGameTextCalls
{
public:
    void FUN_00514ac0(const std::wstring &text, unsigned duration);
};

std::wstring FUN_005e23d0(unsigned long id);

class RHGameSaveHeader
{
public:
    RHGameSaveHeader(unsigned long mode);
    unsigned long m_00;
    unsigned long m_04;
    unsigned long m_08;
};

class RHMapWideText
{
public:
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_size;
    unsigned m_capacity;
    RHMapWideText(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>()) : m_allocator(allocator) { Tidy(false); }
    void Tidy(bool);
    void FUN_004580c0(const std::wstring &text, unsigned first, unsigned count);
    ~RHMapWideText()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            operator delete(m_chars - 1);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_size = 0, m_capacity = 0;
    }
};

class RHMapDescription
{
public:
    RHMapDescription();
    ~RHMapDescription();
    bool FUN_0063cda0(unsigned);
    struct Entry
    {
        char m_00[0x30];
        unsigned m_30;
        char m_34[4];
        unsigned m_38;
        char m_3c[0x0c];
    };
    Entry *FUN_0063c9e0(unsigned);
    char m_00[0x1c];
};

class RHMapResources
{
public:
    bool FUN_00600fc0(unsigned);
    bool FUN_006009e0(unsigned, unsigned, RHMapWideText &);
};

class RHMapWindow;
class RHGameDialog
{
public:
    RHGameDialog(int first, int second, bool third, bool fourth, void *owner);
    ~RHGameDialog();
    char m_00[0x1990];
};

extern char *g_unk0x006c0664;
extern RHMapResources *g_unk0x006c1840;
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, unsigned);

#endif
