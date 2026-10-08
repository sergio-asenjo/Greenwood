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

// SIZE 0x6c
struct RHGameMissionProfile
{
    undefined m_00[0x34]; // 0x00
    int m_34; // 0x34
    undefined m_38[0x30]; // 0x38
    unsigned short m_68; // 0x68
    unsigned short m_6a; // 0x6a
};

// SIZE 0x0c
struct RHGameMission
{
    RHGameMissionProfile *m_profile; // 0x00
    unsigned short m_04; // 0x04
    unsigned short m_06; // 0x06
    unsigned m_08; // 0x08
    bool FUN_0054c800();
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

// SIZE 0x184
class RHGameCampaignView
{
public:
    undefined m_00[0x178]; // 0x00
    RHGameMission *m_178; // 0x178
    RHGameMission *m_17c; // 0x17c
    RHGameMission *m_180; // 0x180
    void FUN_00451a90();
    void FUN_00453b70(RHGameMission *mission);
    int FUN_00456190(RHGameMission *mission);
    int FUN_004561d0(RHGameMission *mission);
    int FUN_00456230(RHGameMission *mission);
    void FUN_00456540(bool flag, RHGameMission *mission);
    unsigned short FUN_00456270();
    void FUN_00456e40(char value);
};

class RHGameMenuOwner
{
public:
    void FUN_0053c870(void *menu);
    unsigned FUN_0053baa0(unsigned duration);
    void FUN_0053bb30(unsigned timer);
};

class RHGameMenuText
{
public:
    virtual void v0(); // vtable+0x00
    virtual void v1(); // vtable+0x04
    virtual void v2(); // vtable+0x08
    virtual void v3(); // vtable+0x0c
    virtual void v4(); // vtable+0x10
    virtual void v5(); // vtable+0x14
    virtual void v6(); // vtable+0x18
    virtual void v7(); // vtable+0x1c
    virtual void v8(); // vtable+0x20
    virtual void v9(); // vtable+0x24
    virtual void v10(); // vtable+0x28
    virtual void v11(const std::wstring &text); // vtable+0x2c
};

class RHGameMenuCalls
{
public:
    void FUN_005283d0();
    void FUN_00535950(int first, int second, int third);
    void FUN_00544b30();
    void FUN_00528380(const std::wstring &text);
};

class RHGameBlazonValue
{
public:
    void FUN_0044f960(int value);
    void FUN_0044f8d0(int value);
};

// SIZE 0xb4
class RHGameBlazonWidget
{
public:
    void FUN_005cc900(int value);
    void FUN_005cc920(int value);
    undefined m_00[0xb0]; // 0x00
    RHGameBlazonValue *m_b0; // 0xb0
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

// SIZE 0x04
class RHGameSaveOwner
{
public:
    virtual std::string v0() = 0; // vtable+0x00
};

std::string FUN_004e4c70(const std::string &first, const char *second);
std::string FUN_004e4b40(const std::string &first, const std::string &second);

class RHEngine
{
public:
    bool FUN_004c4570(SBFile &file);
};

class RHCampaign
{
public:
    void SelectMissions(bool forced);
    bool Serialize(SBFile &file);
    bool CopyBackupTo(SBFile &file) const;
};

template<class T>
class SBArray
{
public:
    int m_grow; // 0x00
    T *m_first; // 0x04
    T *m_last; // 0x08
    T *m_end; // 0x0c
    void Insert(T *position, unsigned count, const T &value);
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

// SIZE 0x0c
class RHGameSaveHeader
{
public:
    RHGameSaveHeader(unsigned long mode);
    unsigned long m_00; // 0x00
    unsigned long m_04; // 0x04
    unsigned long m_08; // 0x08
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
    // SIZE 0x48
    struct Entry
    {
        undefined m_00[0x30]; // 0x00
        unsigned m_30; // 0x30
        undefined m_34[4]; // 0x34
        unsigned m_38; // 0x38
        undefined m_3c[0x08]; // 0x3c
        unsigned m_44; // 0x44
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
