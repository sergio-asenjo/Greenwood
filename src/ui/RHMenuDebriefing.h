// RHMenuDebriefing — declarations for RHMenuDebriefing.cpp (decompiled TU).
//
// BINDING: the code run 0x00528d60..0x0052a58f lies between the RHMenuCampaignMap
// <iostream> glue (0x00528c90..0x00528d50) and the RHMenuDialogue glue (0x0052a590).
// Its vtable 0x006792c8 holds the deleting dtor 0x00529050 (slot 0) and the RouteEvent
// override 0x00528d60 (slot 20). The menu vtables are laid out in alphabetical TU order
// (RHMenuCampaignMap 0x006792xx, RHMenuDialogue 0x00679320). The method run follows the
// Zeta oracle's RHMenuDebriefing address order exactly (HandleEvent/RouteEvent, two
// constructors, destructor, Create, Display(ulong), Display(vector), DisplayAll,
// DisplaySingle(wstring), DisplaySingle(stat), GetGameOperation, GetText, GetTextLeft,
// GetTitle, HasTextLeft, IsLoadingRequested, OnLoad, OnOK, OnRestart); the three button
// handlers match Zeta's call sets (OnLoad: RHMenuLoadSave::Display/Close/Restore; OnOK:
// GetUnrenderedText/Close; OnRestart: GetActiveProfile/GetSaveGame/Close).

#ifndef RHMENUDEBRIEFING_H
#define RHMENUDEBRIEFING_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuLoadSave.h"
#include "RHMenuOptions.h"
#include "RHMenuShortMissionDescription.h"
#include <string>
#include <vector>

class RHDebriefingStat;

class RHDebriefingScreenCalls
{
public:
    bool FUN_0053cd20();
};

class RHDebriefingResources
{
public:
    undefined m_00[0x2c]; // 0x00
    unsigned m_2c; // 0x2c
    unsigned m_30; // 0x30
    unsigned m_34; // 0x34
    unsigned m_38; // 0x38
};

void FUN_00529e60(RHMapWindow *screen, const RHMapWideText &text, bool won, bool last);

#include "RHUnk0056fb70.h"

// SIZE 0x67c
class RHMenuDebriefing : public RHMenuWindowFocus
{
public:
    RHMenuDebriefing(RHMenuScreenView *screen, const RHDebriefingStat *stat, bool won, bool last);
    RHMenuDebriefing(RHMenuScreenView *screen, const std::wstring &text, bool won, bool last);
    ~RHMenuDebriefing();
    void RouteEvent(RHMenuEvent *event);
    bool HandleEvent(RHMenuEvent *event);
    void *FUN_00529050(unsigned flags);
    bool Create();
    static void Display(unsigned long id, bool won, bool last);
    static void Display(const std::vector<unsigned long> &ids, bool won, bool last);
    static void DisplayAll();
    static void DisplaySingle(RHMenuScreenView *screen, const RHDebriefingStat *stat, bool won, bool last);
    static std::wstring GetText(unsigned long id, bool won);
    static RHMenuLoadSaveResult &GetGameOperation();
    const std::wstring &GetTextLeft() const;
    static std::wstring GetTitle(bool won);
    bool HasTextLeft() const;
    static bool IsLoadingRequested();
    bool OnLoad(int msg, void *widget, void *data);
    bool OnOK(int msg, void *widget, void *data);
    bool OnRestart(int msg, void *widget, void *data);

    static RHMenuLoadSaveResult gameOperation;
    static bool bLoadingRequested;

    void *m_titleResource; // 0x140
    void *m_debriefResource; // 0x144
    RHPortraitButton m_ok; // 0x148
    RHPortraitButton m_restart; // 0x248
    RHPortraitButton m_load; // 0x348
    RHMenuShortMissionTitle m_titleWidget; // 0x448
    RHMenuShortMissionTitle m_textWidget; // 0x548
    std::wstring m_title; // 0x648
    std::wstring m_text; // 0x658
    bool m_won; // 0x668
    bool m_last; // 0x669
    std::wstring m_textLeft; // 0x66c
};

#endif
