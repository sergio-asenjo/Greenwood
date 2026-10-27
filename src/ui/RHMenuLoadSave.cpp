// RHMenuLoadSave.cpp — menu TU (code 0x00530180..). See RHMenuLoadSave.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuCancelCalls.h"
#include "RHMenuLoadSave.h"
#include <list>
#include "RHGameSaveCalls.h"
#include "RHUnk006114c0.h"
#include "RHEngineBackgroundCalls.h"
#include "RHEngineWidenedCalls.h"
#include "RHPortraitUnk005d5950.h"
#include "ToolboxWideString.h"
#include "RHScriptListCore.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "SBUIRendererListbox.h"
#include "RHCopyPointers.h"
#include "SBPicture.h"

extern undefined g_unk0x006c0e48[];
extern wchar_t g_unk0x006c0b50[1];
extern RHUnk005ef320 *g_unk0x6c11d0;

// FUNCTION: GAME 0x00530180
void RHMenuLoadSave::FUN_00530180(RHMenuEvent *event)
{
    if (FUN_005301a0(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x005301a0
bool RHMenuLoadSave::FUN_005301a0(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = ((RHMenuCancelCalls *)this)->OnCancel(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = FUN_005314d0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x140)
        handled = FUN_00531710(2, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x340)
        handled = FUN_005316a0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x240)
        handled = FUN_005316a0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x140)
        handled = FUN_005316a0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00463d80(0, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x5e4)
        handled = FUN_00531710(2, event->m_widget, event->m_data);
    if (event->m_type == 15 && event->m_widget == (char *)this + 0x5e4)
        handled = FUN_00531720(15, event->m_widget, event->m_data);
    if (event->m_type == 10 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00531740(10, event->m_widget, event->m_data);
    if (event->m_type == 9 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00531740(9, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x005304f0
void *RHMenuLoadSave::FUN_005304f0(unsigned flags)
{
    this->~RHMenuLoadSave();
    if (flags & 1)
        operator delete(this);
    return this;
}

inline void RHLoadSaveInsertWidget(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

class RHLoadSaveWidgetVector : public std::vector<void *>
{
public:
    void Clear()
    {
        iterator last = FUN_004598e0(end(), end(), begin());
        typedef void (RHLoadSaveWidgetVector::*Destroy)(iterator, iterator);
        Destroy destroy = &RHLoadSaveWidgetVector::_Destroy;
        (this->*destroy)(last, end());
        _Last = last;
    }
};

#define m_accept (*(RHPortraitButton *)((char *)this + 0x140))
#define m_remove (*(RHPortraitButton *)((char *)this + 0x240))
#define m_cancel (*(RHPortraitButton *)((char *)this + 0x340))
#define m_picture (*(RHMapWidget *)((char *)this + 0x7e4))
#define m_slots (*(RHMenuLoadSaveList *)((char *)this + 0x5e4))
#define m_text (*(RHPortraitEditableWidget *)((char *)this + 0x440))

// STUB: GAME 0x005307d0
bool RHMenuLoadSave::FUN_005307d0()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        m_screen->FUN_0053be80(std::string("Default"));
        SBUIListboxUnk0061e890 *normal = (SBUIListboxUnk0061e890 *)m_screen->FUN_0053be80(std::string(
            // STRING: GAME 0x006b0e3c
            "ListDefault"));
        SBUIListboxUnk0061e890 *focused = (SBUIListboxUnk0061e890 *)m_screen->FUN_0053be80(std::string(
            // STRING: GAME 0x006b0e30
            "ListFocused"));
        SBUIListboxUnk0061e890 *selected = (SBUIListboxUnk0061e890 *)m_screen->FUN_0053be80(std::string(
            // STRING: GAME 0x006b0e20
            "ListSelected"));
        RHLoadSaveWidgetVector widgets;
        m_accept.FUN_005d1e30((int)m_screen, FUN_005e23d0(*(bool *)((char *)this + 0x8b8) ? 10 : 11), 0xbe);
        m_remove.FUN_005d1e30((int)m_screen, FUN_005e23d0(8), 0xbe);
        m_cancel.FUN_005d1e30((int)m_screen, FUN_005e23d0(0x10), 0xbe);
        ((RHMenuCampaignMap *)this)->V30(&m_accept);
        ((RHMenuCampaignMap *)this)->V30(&m_remove);
        ((RHMenuCampaignMap *)this)->V30(&m_cancel);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_accept, true);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_remove, true);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, true);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_accept, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_accept, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 1);
        RHLoadSaveInsertWidget(widgets, &m_accept);
        RHLoadSaveInsertWidget(widgets, &m_remove);
        RHLoadSaveInsertWidget(widgets, &m_cancel);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        widgets.Clear();
        *(bool *)((char *)this + 0x144) = false;
        *(bool *)((char *)this + 0x244) = false;
        {
            std::wstring text(g_unk0x006c0b50);
            m_picture.V30(text, RHMapBox(460.0f, 0.0f, 460.0f, 0.0f), 0, 0xa4);
        }
        ((RHMenuCampaignMap *)this)->V30(&m_picture);
        RHLoadSaveInsertWidget(widgets, &m_picture);
        ((RHMenuWindow *)this)->FUN_00544600(widgets, 2);
        widgets.Clear();
        if (*(bool *)((char *)this + 0x8b8))
        {
            {
                std::wstring text(g_unk0x006c0b50);
                ((RHMapWidget *)&m_slots)->V30(text, RHMapBox(30.0f, 10.0f, 450.0f, 460.0f), 0, 0xc9);
            }
            ((SBUIListboxUnk0061d980 *)&m_slots.m_renderer)->FUN_0061d980(normal, focused, selected, false);
            ((RHMenuCampaignMap *)this)->V30(&m_slots);
            focus.FUN_004ffc20(&m_slots ? (RHFocusFocusableView *)((char *)this + 0x7ac) : 0);
        }
        else
        {
            ((RHMapWidget *)&m_slots)->V30(g_unk0x006c0b50, RHMapBox(30.0f, 10.0f, 450.0f, 430.0f), 0, 0xc9);
            ((SBUIListboxUnk0061d980 *)&m_slots.m_renderer)->FUN_0061d980(normal, focused, selected, false);
            ((RHMenuCampaignMap *)this)->V30(&m_slots);
            focus.FUN_004ffc20(&m_slots ? (RHFocusFocusableView *)((char *)this + 0x7ac) : 0);
            m_text.FUN_005d2810(SBGeoPoint2D(30.0f, 440.0f), (RHMenuScreenView *)m_screen);
            m_text.SetMaximum(45);
            ((RHMenuCampaignMap *)this)->V30(&m_text);
            m_text.Activate(m_screen->FUN_0053bf30());
        }
        PopulateSaveGameList();
        FUN_00531bd0();
        return true;
    }
    return false;
}

#undef m_accept
#undef m_remove
#undef m_cancel
#undef m_picture
#undef m_slots
#undef m_text

// FUNCTION: GAME 0x00531110
RHMenuLoadSaveResult RHMenuLoadSave::FUN_00531110(RHMenuWindowUI *ui, bool save)
{
    RHMenuLoadSaveResult result;
    RHMenuScreenView screen(0, 0xbd, 0, ui);
    RHMenuLoadSave menu(&screen, save);
    menu.FUN_005307d0();
    menu.FUN_00544b80(true, true);
    switch (menu.FUN_00531220())
    {
    case 0:
        result.m_choice = 7;
        break;
    case 1:
        result.m_choice = 8;
        break;
    }
    result.m_slot = menu.FUN_00531230();
    return result;
}

// FUNCTION: GAME 0x00531220
int RHMenuLoadSave::FUN_00531220()
{
    return *(int *)((char *)this + 0x8bc);
}

// FUNCTION: GAME 0x00531230
int RHMenuLoadSave::FUN_00531230()
{
    return *(int *)((char *)this + 0x8c0);
}

static __forceinline unsigned long &RHMenuLoadSaveIndexAt(RHSectorActorList *list, int index)
{
    list->Unk005c8e40(index);
    return **(std::list<unsigned long>::iterator *)&list->m_cur;
}

// Parked: the trimmed temporary inlines its tidy call and the zero register is not hoisted.
// STUB: GAME 0x00531240
void RHMenuLoadSave::FUN_00531240()
{
    bool done = false;
    bool load = *(bool *)((char *)this + 0x8b8);
    if (!load || *(unsigned short *)((char *)this + 0x6f0) != 0)
    {
        if (load)
        {
            *(RHSaveGame **)((char *)this + 0x8c0) = (*(RHSaveGameManager **)((char *)this + 0x8b4))->GetSaveGame(
                RHMenuLoadSaveIndexAt((RHSectorActorList *)((char *)this + 0x6e8), *(unsigned short *)((char *)this + 0x760)));
            *(int *)((char *)this + 0x8bc) = 0;
            done = true;
        }
        else
        {
            std::wstring &name = *(std::wstring *)((char *)this + 0x450);
            name = ((SBUIInputFieldUnk00621440 *)m_field)->FUN_0061df60();
            std::wstring text(name);
            text = Toolbox::TrimWideString(text);
            if (text.size())
            {
                if (*(unsigned short *)((char *)this + 0x760) != 0xffff)
                {
                    bool confirmed = RHMenuYesNo::AskForConfirmation(m_screen, FUN_005e23d0(0x21));
                    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
                    if (confirmed)
                    {
                        RHSaveGame *save = (*(RHSaveGameManager **)((char *)this + 0x8b4))->GetSaveGame(
                            RHMenuLoadSaveIndexAt((RHSectorActorList *)((char *)this + 0x6e8), *(unsigned short *)((char *)this + 0x760)));
                        save->SetText(text);
                        *(RHSaveGame **)((char *)this + 0x8c0) = save;
                        done = true;
                        *(int *)((char *)this + 0x8bc) = 1;
                    }
                    else
                    {
                        *(RHSaveGame **)((char *)this + 0x8c0) = 0;
                        *(int *)((char *)this + 0x8bc) = 2;
                    }
                }
                else
                {
                    RHSaveGameManager *manager = *(RHSaveGameManager **)((char *)this + 0x8b4);
                    *(RHSaveGame **)((char *)this + 0x8c0) = manager->GetSaveGame(manager->CreateSaveGame(text));
                    done = true;
                    *(int *)((char *)this + 0x8bc) = 1;
                    ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
                }
            }
        }
        if (done)
            ((RHGameMenuCalls *)this)->FUN_00544b30();
    }
}

template<class T> inline T &SBList<T>::Get(int wanted)
{
    RHUnk0046eb30 &list = *(RHUnk0046eb30 *)this;
    int size = list.count;
    if (list.valid)
    {
        if (wanted <= (size + 1) / 2)
        {
            list.cursor = list.FUN_0046eb80().node;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted, category);
        }
        else
        {
            list.cursor = list.head;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - size, category);
        }
        list.valid = false;
        list.index = wanted;
    }
    else
    {
        int previous = list.index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    list.cursor = list.FUN_0046eb80().node;
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, category);
                }
            }
            else if (wanted < (previous + size) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, category);
            }
            else
            {
                list.cursor = list.head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - size, category);
            }
            list.index = wanted;
        }
    }
    return *m_current;
}

// STUB: GAME 0x005314d0
bool RHMenuLoadSave::FUN_005314d0(int, void *, void *)
{
    bool confirmed = RHMenuYesNo::AskForConfirmation(m_screen, FUN_005e23d0(0x20));
    if (confirmed)
    {
        unsigned long index = ((SBList<unsigned long> *)((char *)this + 0x6e8))->Get(*(unsigned short *)((char *)this + 0x760));
        (*(RHSaveGameManager **)((char *)this + 0x8b4))->RemoveSaveGame(index);
        ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
        PopulateSaveGameList();
        FUN_00531a80();
    }
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return false;
}

// FUNCTION: GAME 0x005316a0
bool RHMenuLoadSave::FUN_005316a0(int, void *, void *)
{
    if (m_fieldState == 13)
    {
        RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
        m_fieldState = m_598 ? 2 : 0;
        ((SBUIInputFieldTextUnk *)m_field)->FUN_0061e320(0);
        m_500 = -1;
        m_504 = -1;
        ui->m_17f0 = 0;
        ui->m_17f4 = 0;
    }
    return false;
}

// FUNCTION: GAME 0x00531710
bool RHMenuLoadSave::FUN_00531710(int, void *, void *)
{
    FUN_00531240();
    return false;
}

// FUNCTION: GAME 0x00531720
bool RHMenuLoadSave::FUN_00531720(int, void *, void *)
{
    FUN_00531a80();
    FUN_00531bd0();
    return false;
}

// Parked: the input-text return view inlines cleanup and adds a temporary frame slot.
// STUB: GAME 0x00531740
bool RHMenuLoadSave::FUN_00531740(int, void *, void *)
{
    if (!*(bool *)((char *)this + 0x8b8))
    {
        std::wstring &name = *(std::wstring *)((char *)this + 0x450);
        {
            std::wstring text = ((SBUIInputFieldUnk00621440 *)m_field)->FUN_0061df60();
            typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
            Assign assign = &std::wstring::assign;
            (name.*assign)((const std::wstring &)text, 0, std::wstring::npos);
        }
        std::wstring text(name, 0, std::wstring::npos);
        unsigned spaces = 0;
        if (text.size())
        {
            std::wstring::iterator last = text.end();
            for (std::wstring::iterator current = text.begin(); current != last; ++current)
                if (*current == L' ')
                    ++spaces;
        }
        *(bool *)((char *)this + 0x144) = text.size() && spaces != text.size();
    }
    return false;
}

class RHUnk00597a70;
void FUN_0059fb00(RHUnk00597a70 **destination, RHUnk00597a70 *const &value);

inline void RHLoadSaveAppendFlag(RHUnk0046eb30 &list, const unsigned long &value)
{
    RHScriptNode *position = list.head;
    RHScriptNode *node = list.Unk0059f720(position, position->prev);
    position->prev = node;
    node->prev->next = node;
    FUN_0059fb00((RHUnk00597a70 **)&node->data, (RHUnk00597a70 *const &)value);
    ++list.count;
    list.valid = true;
}

inline void RHMenuLoadSaveList::RemoveAll()
{
    m_128.RemoveAll();
    m_104.RemoveAll();
    m_158.RemoveAll();
    m_17c = 0xffff;
    m_17e = 0xffff;
    m_180 = 0;
    m_18e[0] = true;
    m_18e[1] = true;
}

inline void RHMenuLoadSaveList::AddItem(const std::wstring &text, unsigned long value, unsigned long flags)
{
    m_128.InsertLast(text);
    m_104.InsertLast(value);
    RHLoadSaveAppendFlag(*(RHUnk0046eb30 *)&m_158, flags);
}

// FUNCTION: GAME 0x005318c0
void RHMenuLoadSave::PopulateSaveGameList()
{
    RHSaveGameManager *manager = (RHSaveGameManager *)((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    manager->SortSaveGames();
    ((RHMenuLoadSaveList *)((char *)this + 0x5e4))->RemoveAll();
    for (unsigned long index = 0; index < manager->GetSaveGameCount(); ++index)
    {
        RHSaveGame *save = manager->GetSaveGame(index);
        if ((*(bool *)((char *)this + 0x8b8) == true && !((RHGameSaveCalls *)save)->FUN_0056e790() && !((RHGameSaveCalls *)save)->FUN_0056e7f0()) ||
            (*(bool *)((char *)this + 0x8b8) == false && !(unsigned char)save->FUN_0056e8b0()))
        {
            ((RHMenuLoadSaveList *)((char *)this + 0x5e4))->AddItem(save->FUN_0056e780(), index, 0);
        }
    }
}

// Parked: the empty-name wide-string construction inlines its copy and terminator calls.
// STUB: GAME 0x00531a80
void RHMenuLoadSave::FUN_00531a80()
{
    if (*(volatile unsigned short *)((char *)this + 0x760) != 0xffff)
    {
        RHSaveGame *save = (*(RHSaveGameManager **)((char *)this + 0x8b4))->GetSaveGame(
            RHMenuLoadSaveIndexAt((RHSectorActorList *)((char *)this + 0x6e8), *(unsigned short *)((char *)this + 0x760)));
        if (!*(bool *)((char *)this + 0x8b8))
            ((RHGameMenuText *)((char *)this + 0x440))->v11(save->FUN_0056e780());
        *(bool *)((char *)this + 0x144) = true;
        *(bool *)((char *)this + 0x244) = true;
    }
    else
    {
        if (!*(bool *)((char *)this + 0x8b8))
            ((RHGameMenuText *)((char *)this + 0x440))->v11(std::wstring(g_unk0x006c0b50));
        *(bool *)((char *)this + 0x144) = false;
        *(bool *)((char *)this + 0x244) = false;
    }
}

#include "RHPortraitDrawCalls.h"

typedef unsigned long (RHUnkFXDraw::*RHMenuCreateSurface)(unsigned short, unsigned short, unsigned long, bool);

// FUNCTION: GAME 0x00531bd0
void RHMenuLoadSave::FUN_00531bd0()
{
    if (*(bool *)((char *)this + 0x8b8) == true || *(int *)((char *)this + 0x8c4) != -1)
    {
        RHEngineWidenedCalls *draw = (RHEngineWidenedCalls *)g_unk0x6c11d0;
        if (*(int *)((char *)this + 0x8c4) != -1)
        {
            draw->FUN_005e5160(*(int *)((char *)this + 0x8c4));
            ((RHPortraitUnk005d5950 *)((char *)this + 0x7e4))->FUN_005d5940();
            *(int *)((char *)this + 0x8c4) = -1;
        }
        if (*(unsigned short *)((char *)this + 0x760) != 0xffff)
        {
            RHSaveGameManager *manager = (RHSaveGameManager *)((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
            RHSaveGame *save = manager->GetSaveGame(
                RHMenuLoadSaveIndexAt((RHSectorActorList *)((char *)this + 0x6e8), *(unsigned short *)((char *)this + 0x760)));
            RHUnk006114c0 picture;
            bool loaded = ((RHEngineBackgroundCalls *)&picture)->FUN_00611660(((RHGameSaveCalls *)save)->FUN_0056e6b0());
            if (loaded)
            {
                *(int *)((char *)this + 0x8c4) = (((RHUnkFXDraw *)draw)->*reinterpret_cast<RHMenuCreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
                    picture.m_width, picture.m_height, 0, false);
                ((SBPicture *)&picture)->SBPicture::Unk00613530((RHUnkFXDraw *)draw, *(int *)((char *)this + 0x8c4));
                ((RHPortraitUnk005d5950 *)((char *)this + 0x7e4))->FUN_005d5950(*(int *)((char *)this + 0x8c4));
                *(bool *)((char *)this + 0x7e8) = true;
            }
            return;
        }
    }
    *(bool *)((char *)this + 0x7e8) = false;
}

// FUNCTION: GAME 0x00531d60
void RHMenuLoadSaveListBase::FUN_00531d60()
{
    m_18a = 0xffff;
    m_18c = 0xffff;
}

// FUNCTION: GAME 0x00531d80
RHUnk00514e10::Pair RHMenuLoadSaveMap::FUN_00531d80(const RHUnk00514e10::Value &value)
{
    RHUnk00514e10::Pair answer;
    answer = m_tree.FUN_00514ff0(value);
    RHUnk00514e10::Pair result(answer.first, answer.second);
    return result;
}

// FUNCTION: GAME 0x00531db0
RHMenuLoadSaveEntry::RHMenuLoadSaveEntry(const int &key, const int &value) : m_key(key), m_value(value)
{
}

// FUNCTION: GAME 0x00531e30
void RHMenuLoadSaveText::FUN_00531e30()
{
    m_renderer.FUN_0061c610(((RHMenuLoadSaveListView *)this)->V24());
}

// FUNCTION: GAME 0x00531e50
int RHMenuLoadSaveListBase::FUN_00531e50()
{
    return 1;
}

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class RHMenuLoadSaveTextDispatch
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual unsigned v9() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual int v13(unsigned id) = 0;
};

static inline RHPortraitInputRenderer &RHMenuLoadSaveTextRenderer(RHMenuLoadSaveText *text)
{
    return *(RHPortraitInputRenderer *)((char *)text + 0x80);
}

// FUNCTION: GAME 0x00532040
RHMenuEvent *RHMenuLoadSaveText::FUN_00532040(unsigned value)
{
    unsigned buffer = value & 1;
    if (*(unsigned short *)((char *)this + 0x180) == ((unsigned short *)((char *)this + 0x18a))[buffer]
        && *(unsigned short *)((char *)this + 0x17e) == ((unsigned short *)((char *)this + 0x186))[buffer]
        && *(unsigned short *)((char *)this + 0x17c) == ((unsigned short *)((char *)this + 0x182))[buffer]
        && !((bool *)((char *)this + 0x18e))[buffer])
        return 0;
    RHMenuEvent *event;
    if (((bool *)((char *)this + 0x18e))[buffer])
    {
        ((bool *)((char *)this + 0x18e))[buffer] = false;
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&m_renderer)->FUN_0060d690());
        event = (RHMenuEvent *)((char *)this + 0x5c);
        *(void **)((char *)this + 0x78) = 0;
        *(void **)((char *)this + 0x74) = this;
        event->m_type = 3;
    }
    else
    {
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&m_renderer)->FUN_0060d690());
        RHMenuLoadSaveTextDispatch *dispatch = (RHMenuLoadSaveTextDispatch *)this;
        event = (RHMenuEvent *)((char *)this + 0x5c);
        event->m_type = dispatch->v13(dispatch->v9());
        *(void **)((char *)this + 0x78) = 0;
        *(void **)((char *)this + 0x74) = this;
    }
    *(unsigned *)((char *)&RHMenuLoadSaveTextRenderer(this) + 0x48) = value;
    ((unsigned short *)((char *)this + 0x18a))[buffer] = *(unsigned short *)((char *)this + 0x180);
    ((unsigned short *)((char *)this + 0x186))[buffer] = *(unsigned short *)((char *)this + 0x17e);
    ((unsigned short *)((char *)this + 0x182))[buffer] = *(unsigned short *)((char *)this + 0x17c);
    return event;
}

class RHMenuLoadSaveUnk00532c50
{
public:
    void *FUN_00532c50();
    RHMenuEvent *FUN_00532c60(bool enabled);
};

// FUNCTION: GAME 0x00532c50
void *RHMenuLoadSaveUnk00532c50::FUN_00532c50()
{
    return (void *)((char *)this - 0x1c8);
}

// FUNCTION: GAME 0x00532c60
RHMenuEvent *RHMenuLoadSaveUnk00532c50::FUN_00532c60(bool enabled)
{
    RHMenuEvent *event = 0;
    unsigned short &selected = *(unsigned short *)((char *)this - 0x4c);
    if (enabled && selected == 0xffff && *(unsigned short *)((char *)this - 0xbc) > 0)
    {
        unsigned short value = *(unsigned short *)((char *)this - 0x4a);
        if (value == 0xffff)
            value = *(unsigned short *)((char *)this - 0x48);
        selected = value;
        *(void **)((char *)this + 0x2c) = (char *)this - 0x1c8;
        int &eventType = *(int *)((char *)this + 0x28);
        eventType = 15;
        *(int *)((char *)this + 0x30) = selected;
        *(void **)((char *)this + 0x34) = 0;
        event = (RHMenuEvent *)&eventType;
    }
    *(bool *)((char *)this + 0x24) = enabled;
    ((RHGameWidgetAnimatedCalls *)((char *)this + 8))->FUN_005d5790(event, *(int *)((char *)this - 0x14c), false);
    return event;
}

void EmitRHMenuLoadSaveUnk00532c50(RHMenuLoadSaveUnk00532c50 *a)
{
    a->FUN_00532c50();
    a->FUN_00532c60(false);
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x00532cd0
void *RHMenuLoadSaveText::FUN_00532cd0(unsigned flags)
{
    this->RHMenuLoadSaveText::~RHMenuLoadSaveText();
    if (flags & 1)
        operator delete(this);
    return this;
}

#pragma inline_depth(0)
// FUNCTION: GAME 0x00532cf0
template<class Renderer, class Item> void *SBWidgetListBox<Renderer, Item>::FUN_00532cf0(unsigned flags)
{
    this->~SBWidgetListBox();
    if (flags & 1)
        operator delete(this);
    return this;
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x00532d10
void *RHMenuLoadSaveList::FUN_00532d10(unsigned flags)
{
    this->RHMenuLoadSaveList::~RHMenuLoadSaveList();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// Parked: both byte predicates emit TEST AL,AL instead of CMP AL,BL.
// STUB: GAME 0x00532d30
template<class Renderer, class Item> RHMenuEvent *SBWidgetListBox<Renderer, Item>::FUN_00532d30(const SBGeoPoint2D &point)
{
    RHMenuEvent *result = 0;
    ((RHMenuLoadSaveText *)this)->m_renderer.FUN_0061d570(
        *(unsigned short *)((char *)this + 0x180), *(int *)((char *)this + 0x130));
    if ((unsigned char)((RHMenuLoadSaveText *)this)->FUN_00533cd0(point))
    {
        result = (RHMenuEvent *)((char *)this + 0x4c);
        *(int *)((char *)this + 0x7c) = 1;
        *(void **)((char *)this + 0x50) = this;
        *(void **)((char *)this + 0x54) = 0;
        *(void **)((char *)this + 0x58) = 0;
        result->m_type = 0;
    }
    else if (((RHMenuLoadSaveText *)this)->FUN_00533d80(point))
    {
        result = (RHMenuEvent *)((char *)this + 0x4c);
        *(int *)((char *)this + 0x7c) = 4;
        *(void **)((char *)this + 0x50) = this;
        *(void **)((char *)this + 0x54) = 0;
        *(void **)((char *)this + 0x58) = 0;
        result->m_type = 0;
    }
    return result;
}

// Parked: the zero and scroll registers are exchanged against the inlined wheel handler.
// STUB: GAME 0x00533800
RHMenuEvent *RHMenuLoadSaveText::FUN_00533800(const SBGeoPoint2D &input)
{
    RHMenuEvent *scroll = 0;
    if (((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_00608400(input))
    {
        short wheel = *(const short *)((const char *)&input + 8);
        unsigned short &line = *(unsigned short *)((char *)this + 0x180);
        if (wheel > 0)
        {
            if (line > 0)
            {
                --line;
                m_renderer.FUN_0061d570(line, *(int *)((char *)this + 0x130));
                scroll = (RHMenuEvent *)((char *)this + 0x4c);
                *(void **)((char *)this + 0x58) = 0;
                *(void **)((char *)this + 0x50) = this;
                *(void **)((char *)this + 0x54) = 0;
                scroll->m_type = 13;
            }
        }
        else if (wheel < 0)
        {
            unsigned limit = *(unsigned *)((char *)this + 0x130);
            RHPortraitInputRenderer &renderer = m_renderer;
            unsigned short current = line;
            if (renderer.FUN_0061d5e0() + current + 1 <= limit)
            {
                line = current + 1;
                renderer.FUN_0061d570(line, *(int *)((char *)this + 0x130));
                scroll = (RHMenuEvent *)((char *)this + 0x4c);
                *(void **)((char *)this + 0x58) = 0;
                *(void **)((char *)this + 0x50) = this;
                *(void **)((char *)this + 0x54) = 0;
                scroll->m_type = 12;
            }
        }
        if ((unsigned char)FUN_00533cd0(input))
            m_state = 2;
        else if (*(const unsigned short *)((const char *)&input + 0xa) & 1)
        {
            m_state = 4;
            RHMenuWindowUI *ui = *(RHMenuWindowUI *const *)((const char *)&input + 0x10);
            ui->m_17f0 = 0;
            ui->m_17f4 = 0;
        }
        return scroll;
    }
    if (*(const unsigned short *)((const char *)&input + 0xa) & 1)
    {
        m_state = 0;
        RHMenuWindowUI *ui = *(RHMenuWindowUI *const *)((const char *)&input + 0x10);
        ui->m_17f0 = 0;
        ui->m_17f4 = 0;
    }
    return 0;
}

// STUB: GAME 0x00533950
template<class Renderer, class Item> SBWidgetListBox<Renderer, Item>::SBWidgetListBox()
{
    m_17c = 0xffff;
    m_17e = 0xffff;
    m_180 = 0;
    m_198.m_x = -1.0f;
    m_198.m_y = -1.0f;
    m_182[0] = 0xffff;
    m_182[1] = 0xffff;
    m_186[0] = 0xffff;
    m_186[1] = 0xffff;
    m_18a[0] = 0xffff;
    m_18a[1] = 0xffff;
    m_18e[0] = false;
    m_18e[1] = false;
    m_state = 0;
}

// FUNCTION: GAME 0x00533cd0
int RHMenuLoadSaveText::FUN_00533cd0(const SBGeoPoint2D &point)
{
    if (((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_006083b0(point) &&
        !m_renderer.FUN_0061d7c0().FUN_00608400(point))
        return 1;
    return 0;
}

// FUNCTION: GAME 0x00533d80
bool RHMenuLoadSaveText::FUN_00533d80(const SBGeoPoint2D &point)
{
    return m_renderer.FUN_0061d7c0().FUN_00608400(point);
}

#pragma inline_depth(0)
void EmitRHMenuLoadSaveHelpers(RHMenuLoadSaveListBase *list, RHMenuLoadSaveMap *map, RHMenuLoadSaveText *text,
    RHMenuLoadSaveSlots *slots, RHMenuLoadSaveList *box, const int &key)
{
    list->FUN_00531d60();
    list->FUN_00531e50();
    map->FUN_00531d80(*(const RHUnk00514e10::Value *)&key);
    RHMenuLoadSaveEntry entry(key, key);
    text->FUN_00531e30();
    text->FUN_00532040(0);
    text->FUN_00532cd0(0);
    text->FUN_00533cd0(*(const SBGeoPoint2D *)list);
    text->FUN_00533d80(*(const SBGeoPoint2D *)list);
    slots->RHMenuLoadSaveSlots::SBWidgetListBox();
    slots->FUN_00532cf0(0);
    slots->FUN_00532d30(*(const SBGeoPoint2D *)list);
    box->FUN_00532d10(0);
}
#pragma inline_depth()

// FUNCTION: GAME 0x00533f70
RHMenuEvent *RHMenuLoadSaveText::FUN_00533f70(const SBGeoPoint2D &input)
{
    RHMenuEvent *scroll = 0;
    short wheel = *(const short *)((const char *)&input + 8);
    unsigned short &line = *(unsigned short *)((char *)this + 0x180);
    if (wheel > 0)
    {
        if (line > 0)
        {
            --line;
            m_renderer.FUN_0061d570(line, *(int *)((char *)this + 0x130));
            *(void **)((char *)this + 0x58) = 0;
            *(void **)((char *)this + 0x50) = this;
            scroll = (RHMenuEvent *)((char *)this + 0x4c);
            *(void **)((char *)this + 0x54) = 0;
            scroll->m_type = 13;
        }
    }
    else if (wheel < 0)
    {
        unsigned limit = *(unsigned *)((char *)this + 0x130);
        RHPortraitInputRenderer &renderer = m_renderer;
        unsigned short current = line;
        if (renderer.FUN_0061d5e0() + current + 1 <= limit)
        {
            line = current + 1;
            renderer.FUN_0061d570(line, *(int *)((char *)this + 0x130));
            *(void **)((char *)this + 0x58) = 0;
            *(void **)((char *)this + 0x50) = this;
            scroll = (RHMenuEvent *)((char *)this + 0x4c);
            *(void **)((char *)this + 0x54) = 0;
            scroll->m_type = 12;
        }
    }
    return scroll;
}
