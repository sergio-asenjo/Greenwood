#ifndef RHGAME_CALLS_H
#define RHGAME_CALLS_H

#include "RHMessenger.h"
#include "RHGame.h"
#include <string>
#include <vector>
#include <windows.h>

class RHMenuCampaignMap;
class RHMenuMissionDescription;
class RHMenuBuyBlazons;
class RHGameBlazonWidget;

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
    undefined m_00;
};

class RHUnk00514e10
{
public:
    typedef std::pair<const int, int> Value;
    struct Node
    {
        Node *left;
        Node *parent;
        Node *right;
        Value value;
        int color;
    };
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : node(node) {}
        void FUN_005159d0();
        void FUN_00515a90();
        Iterator operator++(int) { Iterator old = *this; FUN_00515a90(); return old; }
        Node *node;
    };
    struct Pair
    {
        Pair() {}
        Pair(const Iterator &entry, bool inserted) : first(entry), second(inserted) {}
        Iterator first;
        bool second;
    };
    int &FUN_00514e10(const int &key);
    void FUN_00514e50();
    Iterator FUN_00514ec0(Iterator first, Iterator last);
    Pair FUN_00514ff0(const Value &value);
    Iterator FUN_00515120(Iterator entry);
    void FUN_00515640(Node *node);
    Iterator FUN_005156d0(Node *node, Node *parent, const Value &value);
    Node *&Root() { return m_head->parent; }
    Node *&Leftmost() { return m_head->left; }
    Node *&Rightmost() { return m_head->right; }
    Iterator begin() { return Iterator(Leftmost()); }
    static Node *&Left(Node *node) { return node->left; }
    static Node *&Right(Node *node) { return node->right; }
    static Node *&Parent(Node *node) { return node->parent; }
    static int &Color(Node *node) { return node->color; }
    void RotateLeft(Node *node);
    void RotateRight(Node *node);
    undefined m_00[4];
    Node *m_head;
    bool m_multi;
    undefined m_09[3];
    unsigned m_size;
};

class SBGeoPoint2D;

class RHUnk0050e540
{
public:
    struct Node
    {
        Node *next;
        Node *previous;
        void *value;
    };
    int FUN_0050e540(void *value);
    undefined m_00[0x3c];
    Node *m_head;
    int m_count;
    Node *volatile m_current;
    bool m_dirty;
    int m_index;
    bool m_searching;
    int m_result;
    void *volatile m_value;
};

#include "RHGameWidgetLifetime.h"

#include "RHGameRenderer005cb220.h"

#include "RHUIRendererShiftingClass.h"

typedef RHUIRendererShifting RHGameRenderer005cbe50;

// VTABLE: GAME 0x00678ef8
class RHGameLifetime00517300 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00517300() {}
    ~RHGameLifetime00517300() {}
    void *FUN_005172e0(unsigned flags);
    RHGameRenderer005cb220 m_renderer;
};

// VTABLE: GAME 0x00678f90
class RHGameLifetime00515fd0 : public RHGameLifetime00517300
{
public:
    RHGameLifetime00515fd0() {}
    ~RHGameLifetime00515fd0() {}
    void *FUN_00517360(unsigned flags);
};

// VTABLE: GAME 0x00678d68
class RHGameLifetime0050e6c0 : public RHGameLifetime00517300
{
public:
    RHGameLifetime0050e6c0() {}
    ~RHGameLifetime0050e6c0() {}
    void *FUN_0050e790(unsigned flags);
};

// VTABLE: GAME 0x00678ca8
class RHGameLifetime005174a0 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime005174a0() {}
    ~RHGameLifetime005174a0() {}
    void *FUN_00517480(unsigned flags);
    RHGameRenderer005cbe50 m_renderer;
};

class RHGameLifetime00516e20 : public RHGameLifetime005174a0
{
public:
    ~RHGameLifetime00516e20();
};

// VTABLE: GAME 0x00679038
class RHGameLifetime00517630 : public RHGameLifetime005174a0
{
public:
    RHGameLifetime00517630();
    unsigned m_d4;
    unsigned m_d8;
    unsigned m_dc;
    unsigned m_e0;
};

class RHGameLifetimeDeleteCalls
{
public:
    void FUN_0050a4f0();
    void *FUN_00517500(unsigned flags);
    void *FUN_00517520(unsigned flags);
    void *FUN_005176d0(unsigned flags);
};

class RHGameWidgetBaseCalls
{
public:
    void FUN_0060d290(const SBGeoPoint2D &position);
};

#include "RHGameWidgetRendererCalls.h"

#include "SBUIKeyboardCalls.h"

class RHGameWidgetAnimatedCalls
{
public:
    void FUN_005d5790(void *event, int state, bool option);
};

namespace std
{
    template<> void _Construct(RHUnk00514e10::Value *, const RHUnk00514e10::Value &);
}

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
    bool Unk0049d560(int action);
    RHScriptBatchCalls *Unk004e3cc0();
};

#include "RHGameCampaignView.h"

class RHGameMenuOwner
{
public:
    void FUN_0053c870(void *menu);
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
    virtual void v10(const SBGeoPoint2D &point); // vtable+0x28
    virtual void v11(const std::wstring &text); // vtable+0x2c
    virtual void v12(); // vtable+0x30
    virtual void v13(); // vtable+0x34
    virtual void v14(); // vtable+0x38
    virtual void v15(); // vtable+0x3c
    virtual void v16(); // vtable+0x40
    virtual void v17(); // vtable+0x44
    virtual void v18(); // vtable+0x48
    virtual void v19(); // vtable+0x4c
    virtual void v20(); // vtable+0x50
    virtual void v21(bool value); // vtable+0x54
};

#include "RHMenuCampaignMapClass.h"

class RHMapCampaign
{
public:
    std::vector<void *> FUN_00528050();
};

class RHMapWindow
{
public:
    unsigned FUN_0053baa0(unsigned duration);
    void FUN_0053bb30(unsigned timer);
    void FUN_0053c7e0();
};

#include "RHGameMenuCalls.h"

#include "RHGameBlazonWidget.h"

extern RHUnk00452030 *g_unk0x6c07fc;
class RHEngine;
extern RHEngine *g_pEngine;

#include "RHSaveGame.h"

#include "RHGameSaveCalls.h"

// SIZE 0x04
class RHGameSaveOwner
{
public:
    virtual std::string v0() = 0; // vtable+0x00
};

std::string FUN_004e4c70(const std::string &first, const char *second);
std::string FUN_004e4b40(const std::string &first, const std::string &second);

class RHDialogueSet;

class RHEngine
{
public:
    void FUN_004d8fd0(class RHPCDescription *description);
    bool FUN_004c7c90();
    int FUN_004deeb0(const SBGeoPoint2D &point, SBGeoPoint2D &result);
    bool FUN_004c4570(SBFile &file);
    unsigned char FUN_004ded90(void *actor);
    RHDialogueSet *GetDynResources(unsigned long resources);
};

class RHCampaign
{
public:
    std::vector<RHPCDescription *> *FUN_004553f0();
    unsigned short GetNumberOfPeasantsToConvertToBlazons() const;
    void FUN_00455b20(RHPCDescription *character);
    void FUN_00455b80(RHPCDescription *character);
    void FUN_004559f0();
    void SelectMissions(bool forced);
    bool Serialize(SBFile &file);
    bool CopyBackupTo(SBFile &file) const;
};

#include "RHSaveGameManager.h"

class SBGeoPoint2D;

class RHUnk005fc3b0
{
public:
    float Unk005fc6a0(float value);
};

struct RHGameConfigTriple
{
    float values[3];
};

#include "RHUnk006114c0.h"

class RHGameTextCalls
{
public:
    void FUN_00514ac0(const std::wstring &text, unsigned duration);
};

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

#include "RHPlayerProfileManager.h"

class RHGameContinueCalls
{
public:
    RHSaveGame *FUN_0056f730(const std::wstring &, const std::string &);
    void FUN_0056f700(RHSaveGame *, RHSaveGame *, const std::wstring &);
};

extern undefined g_unk0x006c0e48[];
extern std::string g_unk0x006c0ea0;

class RHUnk00549250 : public RHUnk5490f0
{
public:
    RHUnk00549250(int command, void *actor);
    RHUnk00549250(int command, void *actor, int action);
    ~RHUnk00549250();
    char m_data[4]; // 0x10
};

class RHGamePortraitCalls
{
public:
    void FUN_005d9b10();
    void FUN_005d9ae0(unsigned short action, bool enabled);
    void FUN_005d9b70();
    void FUN_005d9a60(unsigned action);
    void FUN_005d9950(unsigned action);
    void FUN_005d9140(unsigned);
    void FUN_005d6690();
    bool FUN_005d8f20(unsigned);
    bool FUN_005d8fa0(unsigned, int);
};

class RHPortraitBar;
typedef RHPortraitBar RHGameNotificationCalls;

class RHGameSyncCalls
{
public:
    RHGamePortraitCalls *FUN_0050f140(void *);
    int FUN_0050f160(unsigned short index);
    void FUN_00513520(RHUnk00549250 &);
    void FUN_005134c0(RHUnk00549250 &);
    void FUN_00513b00(void *);
    void FUN_0050ed40();
    void FUN_00514670();
    void FUN_005146f0();
    void FUN_0048a970(RHUnk00549250 &);
};

class RHGameEngineCalls
{
public:
    bool FUN_004c7cd0();
    bool FUN_004c7cf0();
};

class RHEngineActionCalls
{
public:
    int FUN_004d2300(void *, unsigned);
};

class RHGameActorView
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50();
    virtual short v51(); // vtable+0xcc
    virtual void v52(); // vtable+0xd0
    virtual void v53(short action, bool first, bool second); // vtable+0xd4
    bool FUN_004936e0();
};

class RHActorPCTemplateCalls
{
public:
    void FUN_00493660(int);
};

class RHEngineReinforcementCalls
{
public:
    void FUN_004936a0(int);
};

class RHGameWidgetCalls
{
public:
    void FUN_0051df00(void *);
    void FUN_0051dfa0(bool first, bool second);
    void FUN_0051e020(void *widgets, unsigned value, bool empty);
};


extern unsigned char g_unk0x006a6d27;
extern unsigned char g_unk0x006c12b6;

#include "RHGameActionCalls.h"

#include "RHSectorActorList.h"

void FUN_0053a830();

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

#include "RHMapWideText.h"

#include "RHMapDescription.h"

#include "RHMapResources.h"

#include "RHMenuScreenView.h"

extern char *g_unk0x006c0664;
extern RHMapResources *g_unk0x006c1840;
void FUN_00529e60(RHMapWindow *, const RHMapWideText &, bool, bool);

#endif
