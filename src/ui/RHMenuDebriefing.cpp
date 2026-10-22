// RHMenuDebriefing.cpp — menu TU (code 0x00528d60..0x0052a58f). See RHMenuDebriefing.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuDebriefing.h"

extern std::string g_unk0x006c0ed8;

// GLOBAL: GAME 0x006c0be8
RHMenuLoadSaveResult RHMenuDebriefing::gameOperation;

// GLOBAL: GAME 0x006c0bf2
bool RHMenuDebriefing::bLoadingRequested;

// FUNCTION: GAME 0x00528d60
void RHMenuDebriefing::RouteEvent(RHMenuEvent *event)
{
    if (HandleEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00528d80
bool RHMenuDebriefing::HandleEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == &m_load)
        handled = OnLoad(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_restart)
        handled = OnRestart(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_ok)
        handled = OnOK(2, event->m_widget, event->m_data);
    return handled;
}

class RHDebriefingStat
{
public:
    virtual std::wstring GetText() const;
};

// FUNCTION: GAME 0x00528e00
RHMenuDebriefing::RHMenuDebriefing(RHMenuScreenView *screen, const RHDebriefingStat *stat, bool won, bool last)
    : RHMenuWindowFocus(0, screen, 0x93, 0, false),
      m_titleResource(((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("MissionTitle"))),
      m_debriefResource(((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("Debrief"))),
      m_title(GetTitle(won)),
      m_text(stat->GetText()),
      m_won(won),
      m_last(last)
{
}

// FUNCTION: GAME 0x00529050
void *RHMenuDebriefing::FUN_00529050(unsigned flags)
{
    this->~RHMenuDebriefing();
    if (flags & 1)
        operator delete(this);
    return this;
}

extern RHUnk0048a970 *g_unk0x6c0b3c;

// FUNCTION: GAME 0x00529070
RHMenuDebriefing::RHMenuDebriefing(RHMenuScreenView *screen, const std::wstring &text, bool won, bool last)
    : RHMenuWindowFocus(0, screen, 0x93, 0, false),
      m_titleResource(((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("MissionTitle"))),
      m_debriefResource(((RHPortraitTextResourceCalls *)screen)->FUN_0053be80(std::string("PopupScroll"))),
      m_title(GetTitle(won)),
      m_text(text),
      m_won(won),
      m_last(last)
{
}

// FUNCTION: GAME 0x005292f0
RHMenuDebriefing::~RHMenuDebriefing()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_titleWidget);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_textWidget);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_load);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_restart);
}

// FUNCTION: GAME 0x00529ab0
void RHMenuDebriefing::Display(unsigned long id, bool won, bool last)
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    gameOperation.m_choice = 0;
    gameOperation.m_slot = 0;
    bLoadingRequested = false;
    if (last == true)
        screen.FUN_0053be40(1);
    FUN_00529e60((RHMapWindow *)&screen, (const RHMapWideText &)GetText(id, won), won, last);
    bLoadingRequested |= ((RHDebriefingScreenCalls *)&screen)->FUN_0053cd20();
    if (!bLoadingRequested)
    {
        DisplaySingle(&screen, (const RHDebriefingStat *)((RHScriptBatchCalls *)g_pEngine)->Unk004e3cc0(), won, last);
        bLoadingRequested |= ((RHDebriefingScreenCalls *)&screen)->FUN_0053cd20();
    }
}

// FUNCTION: GAME 0x00529c10
void RHMenuDebriefing::Display(const std::vector<unsigned long> &ids, bool won, bool last)
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    gameOperation.m_choice = 0;
    gameOperation.m_slot = 0;
    bLoadingRequested = false;
    if (last == true)
        screen.FUN_0053be40(1);
    for (std::vector<unsigned long>::const_iterator it = ids.begin(); it != ids.end(); ++it)
    {
        FUN_00529e60((RHMapWindow *)&screen, (const RHMapWideText &)GetText(*it, won), won, last);
        if (!bLoadingRequested)
            bLoadingRequested = ((RHDebriefingScreenCalls *)&screen)->FUN_0053cd20();
        if (bLoadingRequested == true)
            break;
    }
}

class RHSaveGame;

inline void RHDebriefingAppend(std::vector<unsigned long> &ids, const unsigned long &id)
{
    SBArray<RHSaveGame *> &array = (SBArray<RHSaveGame *> &)ids;
    array.Insert(array.m_last, 1, (RHSaveGame *const &)id);
}

// FUNCTION: GAME 0x00529d60
void RHMenuDebriefing::DisplayAll()
{
    RHDebriefingResources *resources = (RHDebriefingResources *)g_pEngine->GetDynResources(0);
    std::vector<unsigned long> ids;
    unsigned long id;
    for (id = 0; id != resources->m_34; ++id)
        RHDebriefingAppend(ids, id);
    Display(ids, false, false);
    ids.erase(ids.begin(), ids.end());
    for (id = 0; id != resources->m_2c; ++id)
        RHDebriefingAppend(ids, id);
    Display(ids, true, false);
}

// Parked: target rotates the loop and duplicates the construct/display block, caching last in EBP.
// STUB: GAME 0x00529e60
void FUN_00529e60(RHMapWindow *screen, const RHMapWideText &text, bool won, bool last)
{
    std::wstring textLeft((const std::wstring &)text);
    while (true)
    {
        RHMenuDebriefing menu((RHMenuScreenView *)screen, textLeft, won, last);
        menu.Create();
        menu.FUN_00544b80(true, true);
        if (menu.HasTextLeft() != true || RHMenuDebriefing::IsLoadingRequested())
            break;
        textLeft = menu.GetTextLeft();
    }
}

// FUNCTION: GAME 0x0052a090
void RHMenuDebriefing::DisplaySingle(RHMenuScreenView *screen, const RHDebriefingStat *stat, bool won, bool last)
{
    RHMenuDebriefing menu(screen, stat, won, last);
    menu.Create();
    menu.FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x0052a120
RHMenuLoadSaveResult &RHMenuDebriefing::GetGameOperation()
{
    return gameOperation;
}

// FUNCTION: GAME 0x0052a130
std::wstring RHMenuDebriefing::GetText(unsigned long id, bool won)
{
    RHMapResources *manager = g_unk0x006c1840;
    RHDebriefingResources *resources = (RHDebriefingResources *)g_pEngine->GetDynResources(0);
    std::wstring text;
    if (resources)
    {
        unsigned resource = won ? resources->m_30 : resources->m_38;
        if (manager->FUN_00600fc0(resource))
        {
            if (!manager->FUN_006009e0(resource, id, (RHMapWideText &)text))
                text =
                    // STRING: GAME 0x006b0b14
                    L"Invalid debriefing ID...";
        }
        else
            text =
                // STRING: GAME 0x006b0ad4
                L"Unable to find the resource...";
    }
    else
        (std::basic_string<unsigned short> &)text =
            // STRING: GAME 0x006b0a84
            (const unsigned short *)L"No dynamic resources for this level...";
    return text;
}

// FUNCTION: GAME 0x0052a2f0
const std::wstring &RHMenuDebriefing::GetTextLeft() const
{
    return m_textLeft;
}

// FUNCTION: GAME 0x0052a300
std::wstring RHMenuDebriefing::GetTitle(bool won)
{
    return FUN_005e23d0(won ? 0x18 : 0x19);
}

// FUNCTION: GAME 0x0052a330
bool RHMenuDebriefing::HasTextLeft() const
{
    return m_textLeft.size() != 0;
}

// FUNCTION: GAME 0x0052a340
bool RHMenuDebriefing::IsLoadingRequested()
{
    return bLoadingRequested;
}

// FUNCTION: GAME 0x0052a350
bool RHMenuDebriefing::OnLoad(int, void *, void *)
{
    gameOperation = RHMenuLoadSave::FUN_00531110(m_screen->FUN_0053bf30(), true);
    if (gameOperation.m_choice == 7)
    {
        bLoadingRequested = true;
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        return false;
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x0052a3c0
bool RHMenuDebriefing::OnOK(int, void *, void *)
{
    m_textLeft = *(const std::wstring *)((SBUIUnk0060dd00 *)&m_textWidget.m_renderer)->FUN_0060dd00();
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0052a550
bool RHMenuDebriefing::OnRestart(int, void *, void *)
{
    RHUnk0056fb70 *profile = (RHUnk0056fb70 *)((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    gameOperation.m_slot = (int)profile->FUN_0056fb70(&g_unk0x006c0ed8);
    if (gameOperation.m_slot)
    {
        gameOperation.m_choice = 7;
        bLoadingRequested = true;
    }
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

const char *RHMenuDebriefingResourceName(int index)
{
    if (index == 0)
        return
            // STRING: GAME 0x006b0a50
            "MissionTitle";
    if (index == 1)
        return
            // STRING: GAME 0x006b090c
            "Debrief";
    return
        // STRING: GAME 0x006b0a60
        "PopupScroll";
}

void RHMenuDebriefingEmit(RHMenuDebriefing *menu, RHMenuEvent *event)
{
    menu->RouteEvent(event);
    menu->FUN_00529050(0);
    RHMenuDebriefing::Display((unsigned long)0, false, false);
    RHMenuDebriefing::Display(std::vector<unsigned long>(), false, false);
    RHMenuDebriefing::DisplayAll();
    RHMenuDebriefing::DisplaySingle(0, 0, false, false);
    RHMenuDebriefing::GetText(0, false);
    RHMenuDebriefing::GetGameOperation();
    menu->GetTextLeft();
    RHMenuDebriefing::GetTitle(false);
    menu->HasTextLeft();
    RHMenuDebriefing::IsLoadingRequested();
}
