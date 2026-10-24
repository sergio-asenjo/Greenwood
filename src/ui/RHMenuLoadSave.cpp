// RHMenuLoadSave.cpp — menu TU (code 0x00530180..). See RHMenuLoadSave.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuCancelCalls.h"
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

// FUNCTION: GAME 0x00531dd0
RHMenuLoadSaveText::~RHMenuLoadSaveText()
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

// Parked: both byte predicates emit TEST AL,AL instead of CMP AL,BL.
// STUB: GAME 0x00532d30
RHMenuEvent *RHMenuLoadSaveSlots::FUN_00532d30(const SBGeoPoint2D &point)
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
    slots->FUN_00532cf0(0);
    slots->FUN_00532d30(*(const SBGeoPoint2D *)list);
    box->FUN_00532d10(0);
}
