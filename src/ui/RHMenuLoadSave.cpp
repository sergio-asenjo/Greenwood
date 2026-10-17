// RHMenuLoadSave.cpp — menu TU (code 0x00530180..). See RHMenuLoadSave.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuLoadSave.h"

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
        handled = FUN_0052ce80(2, event->m_widget, event->m_data);
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

class RHMenuLoadSaveUnk00532c50
{
public:
    void *FUN_00532c50();
};

// FUNCTION: GAME 0x00532c50
void *RHMenuLoadSaveUnk00532c50::FUN_00532c50()
{
    return (void *)((char *)this - 0x1c8);
}

void EmitRHMenuLoadSaveUnk00532c50(RHMenuLoadSaveUnk00532c50 *a)
{
    a->FUN_00532c50();
}

// FUNCTION: GAME 0x00532cd0
void *RHMenuLoadSaveText::FUN_00532cd0(unsigned flags)
{
    this->~RHMenuLoadSaveText();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00532cf0
void *RHMenuLoadSaveSlots::FUN_00532cf0(unsigned flags)
{
    this->~RHMenuLoadSaveSlots();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00532d10
void *RHMenuLoadSaveList::FUN_00532d10(unsigned flags)
{
    this->~RHMenuLoadSaveList();
    if (flags & 1)
        operator delete(this);
    return this;
}

void EmitRHMenuLoadSaveHelpers(RHMenuLoadSaveListBase *list, RHMenuLoadSaveMap *map, RHMenuLoadSaveText *text,
    RHMenuLoadSaveSlots *slots, RHMenuLoadSaveList *box, const int &key)
{
    list->FUN_00531d60();
    list->FUN_00531e50();
    map->FUN_00531d80(*(const RHUnk00514e10::Value *)&key);
    RHMenuLoadSaveEntry entry(key, key);
    text->FUN_00531e30();
    text->FUN_00532cd0(0);
    slots->FUN_00532cf0(0);
    box->FUN_00532d10(0);
}
