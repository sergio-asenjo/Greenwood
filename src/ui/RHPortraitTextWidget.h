#ifndef RHPORTRAITTEXTWIDGET_H
#define RHPORTRAITTEXTWIDGET_H

#include "Decomp.h"
#include "RHWidgetPortrait.h"
#include "RHGameWidgetLifetime.h"
#include "RHPortraitRenderer006212d0.h"
#include <string>

class SBGeoBoundingBox2D;
class SBGeoPoint2D;
class RHPortraitBoxEvent;
struct RHPortraitWidgetEvent;
struct RHPortraitWidgetInput;

// VTABLE: GAME 0x0067a158
class RHPortraitTextWidgetBase : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitTextWidgetBase() {}
    ~RHPortraitTextWidgetBase() {}
    void *FUN_005d3390(unsigned flags);
    void FUN_005d2ee0(const SBGeoBoundingBox2D &box);
    void FUN_005d2f10(const SBGeoPoint2D &point);
    void FUN_005d2ec0();
    RHPortraitRenderer006212d0 m_renderer;
};

// VTABLE: GAME 0x0067a120
class RHPortraitTextWidget : public RHPortraitTextWidgetBase
{
public:
    RHPortraitTextWidget() : m_linked(0)
    {
        m_state = 0;
        m_indices[0] = 0;
        m_indices[1] = 0;
        m_caretFlags[0] = 0;
        m_caretFlags[1] = 0;
        m_positions[0] = 0;
        m_positions[1] = 0;
    }
    ~RHPortraitTextWidget();
    void *FUN_005d33b0(unsigned flags);
    int FUN_005d2fa0();
    void FUN_005d3360();
    RHPortraitBoxEvent *FUN_005d3290(unsigned value);
    void FUN_005d2cf0(const std::wstring &text);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *OnIdle(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *OnHover(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *OnPressed(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *OnSelected(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d33d0(const RHPortraitWidgetInput &input);
    void FUN_0053f9f0(RHPortraitTextWidget *stop);
    void Select()
    {
        RHPortraitTextWidget *linked = m_linked;
        if (linked)
        {
            m_state = 2;
            if (this != linked)
            {
                if (linked->m_state == 2 || linked->m_state == 13)
                {
                    ((SBUIInputFieldTextUnk *)&linked->m_text)->FUN_0061e320(0);
                    linked->m_state = 0;
                }
                linked = linked->m_linked;
                if (linked)
                    linked->FUN_0053f9f0(this);
            }
        }
    }
    RHPortraitWidgetEvent &Event() { return m_event; }
    RHPortraitText0061db10 m_text;
    RHPortraitTextWidget *m_linked;
    undefined m_15c[0x10];
    int m_indices[2];
    char m_caretFlags[2];
    undefined m_176[2];
    unsigned m_positions[2];
};

struct __declspec(novtable) RHPortraitEditableStrategy
{
    RHPortraitEditableStrategy()
    {
        ((RHUnk005cca80 *)this)->RHUnk005cca80::RHUnk005cca80();
    }
    virtual RHPortraitTextWidget *FUN_005d2ca0();
    virtual RHPortraitWidgetEvent *FUN_005d2cb0(bool active);
    RHPortraitUIOwner *m_owner;
};

// VTABLE: GAME 0x0067a0e0 RHPortraitTextWidget
// VTABLE: GAME 0x0067a118 RHPortraitEditableStrategy
class RHPortraitEditableWidget : public RHPortraitTextWidget, public RHPortraitAnimated, public RHPortraitEditableStrategy
{
public:
    RHPortraitEditableWidget();
    ~RHPortraitEditableWidget();
    void *FUN_005d26f0(unsigned flags);
    bool FUN_005d2810(const SBGeoPoint2D &point, RHMenuScreenView *resources);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);

    void SetMaximum(unsigned maximum) { m_text.m_maximum = maximum; }
    void Activate(void *ui)
    {
        if (RHPortraitTextWidget::m_state != 13)
        {
            *(RHPortraitEditableWidget **)((char *)ui + 0x17f0) = this;
            SBUIInputFieldTextUnk *text = (SBUIInputFieldTextUnk *)&m_text;
            RHPortraitTextWidget::m_state = 13;
            ((SBUIInputFieldUnk00621440 *)text)->FUN_0061e340();
            text->FUN_0061e320(1);
        }
    }
    bool IsSelected() const
    {
        return RHPortraitTextWidget::m_state == 4 || RHPortraitTextWidget::m_state == 2 ||
               RHPortraitTextWidget::m_state == 1 || RHPortraitTextWidget::m_state == 13;
    }
    const std::wstring &GetText() const
    {
        RHPortraitEditableWidget *widget = const_cast<RHPortraitEditableWidget *>(this);
        widget->m_10 = ((SBUIInputFieldUnk00621440 *)&widget->m_text)->FUN_0061df60();
        return m_10;
    }
    void SetInfo(const std::wstring &text)
    {
        m_renderer.m_prompt.assign(text);
        m_renderer.m_promptEnabled = true;
    }
};

#endif
