// RHWidgetPortrait.cpp — translation unit with __FILE__ evidence at 0x005d92c0
// ("P:\Robin Hood\RHWidgetPortrait.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005d92c0 -> RHWidgetPortrait::Serialize(SBFile&)):
//   - TU:        rhwidgetportrait.cpp (embedded __FILE__ string 0x006b8e28).
//   - Class:     RHWidgetPortrait (symbols/oracle-correlation.tsv:
//                rhwidgetportrait -> class RHWidgetPortrait, 51 methods).
//   - Method:    RHWidgetPortrait::Serialize(SBFile&) — the Mac oracle's
//                rhwidgetportrait.cpp has exactly one serializer
//                (mac-functions-by-file.tsv: 0x001f43d0 Serialize).
//   - Signals:
//       * the first act writes the tag "RHWidgetPortrait" (string 0x006b8e90);
//       * every field goes through SBFile::Access 0x005f52b0 / GetError
//         0x005f5f30 and the "Serialize failed reason is %s" assert pattern;
//       * the read/write split is driven by SBFile::m_bLoading (+4) and the
//         format version at SBFile+0x10 (compared against 0xf and 0x2b);
//       * the per-element loop walks three 0x104-byte elements at +0xa50 and
//         dispatches four this-call helpers (0x5d6690 / 0x5d67e0 / 0x5d73d0 /
//         0x5d7530) plus one virtual on the sub-object at +0x7bc.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses. ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp.)
//
// STATUS: 100% — exact byte match. The float member +0x16c is copied through
// an intermediate `float` temp (see `tmp`) so VC6 keeps the value on the x87
// stack (`fld`/`fstp`) exactly as the original does; a direct `m_16c = f10`
// compiles to an integer `mov` pair instead. The temp coalesces into f10's
// stack slot, so the 0x10 frame is unchanged.

#include "SBNullstr.h"
#include "RHSectorActorList.h"
#include "RHWidgetPortrait.h"
#include "../engine/RHGame_calls.h"
#include "../engine/SBUIRenderer.h"
#include "../element/RHElementActorPC.h"
#include "RHPortraitDrawCalls.h"
#include "../engine/SBUIRendererListbox.h"

// TEMPLATE: GAME 0x0059fb70
// ?pop_front@?$list@KV?$allocator@K@std@@@std@@QAEXXZ
// TEMPLATE: GAME 0x00564360
// ?pop_back@?$list@KV?$allocator@K@std@@@std@@QAEXXZ
template class std::list<unsigned long>;
// TEMPLATE: GAME 0x00534200
// ?clear@?$list@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAEXXZ
template class std::list<std::wstring>;

DECOMP_SIZE_ASSERT(RHWidgetPortrait, 0xe58)
DECOMP_SIZE_ASSERT(RHUnk005d92c0Sub, 0x04)
DECOMP_SIZE_ASSERT(RHUnk005d73d0Actor, 0x04)
DECOMP_SIZE_ASSERT(RHUnk005d92c0Elem, 0x104)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)


#define W(O) (*(RHUnk005d92c0Sub *)((char *)this + (O)))
#define P(O) (*(SBGeoPoint2D *)((char *)this + (O)))
#define A (*(RHUnk005d73d0Actor **)((char *)this + 0xe1c))

#include "SBFrameWnd.h"

#include "RHMapBox.h"

#include "RHPortraitAnimated.h"

struct RHPortraitWidgetEvent;

class RHPortraitTree
{
public:
    RHUnk00514e10::Node *FUN_005d5840(const RHPortraitWidgetEvent &event);
    undefined m_00[4];
    RHUnk00514e10::Node *m_head;
};

#include "RHPortraitUnk005d3880.h"

class RHPortraitBoxEvent
{
public:
    ~RHPortraitBoxEvent();
    int m_type;
    SBGeoBoundingBox2D m_box;
    void *m_widget;
    void *m_next;
};

class RHPortraitUnk005d3880;

struct RHPortraitWidgetUI
{
    undefined m_00[0x17f0];
    RHPortraitUnk005d3880 *m_selected;
    RHPortraitUnk005d3880 *m_captured;
    void Clear()
    {
        m_selected = 0;
        m_captured = 0;
    }
};

struct RHPortraitWidgetInput
{
    SBGeoPoint2D point;
    short wheel;
    unsigned short flags;
    RHGameWidgetInputCalls *shortcuts;
    RHPortraitWidgetUI *ui;
};

class RHPortraitWidgetStrategy
{
public:
    virtual void v0(unsigned flags) = 0;
    virtual void v1(unsigned value) = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual RHPortraitBoxEvent *v5(unsigned long frame) = 0;
    virtual RHPortraitWidgetEvent *v6(const RHPortraitWidgetInput &input) = 0;
    virtual void v7(const SBGeoBoundingBox2D &box) = 0;
    virtual void v8(const SBGeoPoint2D &point) = 0;
    undefined m_04[0xd8 - 4];
};

class RHPortraitUnk005d3fe0
{
public:
    RHPortraitWidgetEvent &BeginEvent()
    {
        m_event.widget = this;
        return m_event;
    }
    void FUN_005d3fe0(unsigned value);
    void FUN_005d4020();
    void FUN_005d4060();
    void FUN_005d40b0();
    RHPortraitBoxEvent *FUN_005d40f0(unsigned long frame);
    RHPortraitWidgetEvent *FUN_005d3ef0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d4240(const RHPortraitWidgetInput &input);
    void FUN_005d4280(const SBGeoPoint2D &point);
    void FUN_005d4360(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *FUN_005d4480(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d45a0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d46e0(const RHPortraitWidgetInput &input);
    undefined m_00[0x30];
    SBGeoBoundingBox2D m_box;
    undefined m_44[8];
    RHPortraitWidgetEvent m_event;
    undefined m_5c[0x20];
    int m_state;
    RHPortraitWidgetStrategy *m_widgets;
    unsigned m_count;
    unsigned m_index;
    RHPortraitBoxEvent **m_events;
};

class __declspec(novtable) RHPortraitUnk005d5100
{
public:
    RHPortraitUnk005d5100()
    {
        ((RHPortraitStrategyCalls *)this)->RHPortraitStrategyCalls::RHPortraitStrategyCalls();
    }
    RHPortraitWidgetEvent *FUN_005d3ac0();
    virtual RHPortraitWidgetEvent *FUN_005d5090();
    virtual void *FUN_005d51a0();
    virtual void FUN_0048a970(char value) {}
    virtual int FUN_005d5100(const SBGeoPoint2D &point);
    virtual bool FUN_005d51b0() { return true; }
    virtual RHPortraitWidgetEvent *FUN_005d51c0(char value);
    virtual RHPortraitWidgetEvent *FUN_005d5210(char value);
};

#include "RHPortraitUnk005d5950.h"

DECOMP_SIZE_ASSERT(RHPortraitWidgetStrategy, 0xd8)
DECOMP_SIZE_ASSERT(RHPortraitWidgetEvent, 0x10)

class RHPortraitButtonDispatch
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
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual RHPortraitWidgetEvent *v15(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v16(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v17(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v18(const RHPortraitWidgetInput &input) = 0;
    virtual int v19(const RHPortraitWidgetInput &input) = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual RHPortraitWidgetEvent *v22(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v23(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v24(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v25(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v26(const RHPortraitWidgetInput &input) = 0;
    virtual RHPortraitWidgetEvent *v27(const RHPortraitWidgetInput &input) = 0;
};

class RHPortraitRendererDispatch
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3(const SBGeoBoundingBox2D &box) = 0;
};


inline void RHPortraitAssignWideText(void *destination, const std::wstring &text)
{
    std::wstring &(std::wstring::*assign)(const std::wstring &, unsigned, unsigned) = &std::wstring::assign;
    (((std::wstring *)destination)->*assign)(text, 0, std::basic_string<unsigned short>::npos);
}

inline int &RHPortraitMapLookup(RHUnk00514e10 &map, int key)
{
    RHUnk00514e10::Value value(key, 0);
    RHUnk00514e10::Pair result;
    result = map.FUN_00514ff0(value);
    return result.first.node->value.second;
}

#include "RHPortraitButtonBase.h"

class __declspec(novtable) RHPortraitLifetime005d5350 : public RHPortraitButtonBase
{
public:
    RHPortraitLifetime005d5350()
    {
        *(unsigned *)this = 0x0067a2f0;
        m_state = 6;
    }
    ~RHPortraitLifetime005d5350() {}
    void *FUN_005d55f0(unsigned flags);
};

class __declspec(novtable) RHPortraitRadioLifetimeBase : public RHPortraitLifetime005d5350
{
public:
    RHPortraitRadioLifetimeBase() : m_selected(0) {}
    char m_selected;
    undefined m_d9[3];
};

// VTABLE: GAME 0x0067a264 RHPortraitRadioLifetimeBase
// VTABLE: GAME 0x0067a2d4 RHPortraitUnk005d5100
class RHPortraitRadioLifetime : public RHPortraitRadioLifetimeBase, public RHPortraitAnimated, public RHPortraitUnk005d5100
{
public:
    RHPortraitRadioLifetime();
    ~RHPortraitRadioLifetime();
    void *FUN_005d4ab0(unsigned flags);
    RHPortraitWidgetEvent m_secondary;
    char m_10c;
    char m_10d;
    undefined m_10e[2];
};

class __declspec(novtable) RHPortraitLinkedLifetime : public RHPortraitRadioLifetime
{
public:
    RHPortraitLinkedLifetime();
    ~RHPortraitLinkedLifetime();
    void *FUN_005d39d0(unsigned flags);
    void *m_linked;
};

// VTABLE: GAME 0x0067a240
class RHPortraitGroupLifetimeBase : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitGroupLifetimeBase() : m_widgets(0), m_count(0), m_index(0)
    {
    }
    ~RHPortraitGroupLifetimeBase();
    void *FUN_005d4410(unsigned flags);
    RHPortraitWidgetStrategy *m_widgets;
    unsigned m_count;
    unsigned m_index;
    RHPortraitBoxEvent **m_events;
    int m_type;
    SBGeoBoundingBox2D m_box;
    void *m_widget;
    void *m_next;
};

// VTABLE: GAME 0x0067a21c
class RHPortraitGroupLifetime : public RHPortraitGroupLifetimeBase, public RHPortraitAnimated
{
public:
    RHPortraitGroupLifetime();
    ~RHPortraitGroupLifetime();
    void *FUN_005d3dc0(unsigned flags);
};

DECOMP_SIZE_ASSERT(RHPortraitRadioLifetime, 0x110)
DECOMP_SIZE_ASSERT(RHPortraitUnk005d5100, 0x04)
DECOMP_SIZE_ASSERT(RHPortraitRadioLifetimeBase, 0xdc)
DECOMP_SIZE_ASSERT(RHPortraitGroupLifetimeBase, 0xb0)
DECOMP_SIZE_ASSERT(RHPortraitGroupLifetime, 0xcc)

class RHPortraitLifetime005d6260 : public RHGameLifetime00517590
{
public:
    ~RHPortraitLifetime005d6260() {}
};

class RHPortraitLifetime005d62c0 : public RHGameLifetime00517590
{
public:
    ~RHPortraitLifetime005d62c0() {}
};

class __declspec(novtable) RHPortraitActionWidget : public RHPortraitLifetime005d6200
{
public:
    RHPortraitActionWidget()
    {
        m_state = 0;
        *(unsigned *)this = 0x0067a48c;
        m_messages[0] = 0;
        m_messages[1] = 0;
        m_messages[2] = 0;
        m_messages[3] = 0;
    }
    int m_messages[4];
};

class __declspec(novtable) RHPortraitMessageBitmap : public RHGameLifetime00517590
{
public:
    RHPortraitMessageBitmap()
    {
        m_state = 0;
        *(unsigned *)this = 0x0067a434;
        m_messages[0] = 0;
        m_messages[1] = 0;
        m_messages[2] = 0;
        m_messages[3] = 0;
    }
    int m_messages[4];
};

class __declspec(novtable) RHPortraitMessageWidget : public RHPortraitMessageWidgetBase
{
public:
    RHPortraitMessageWidget()
    {
        m_value = 0;
        *(unsigned *)this = 0x0067a3d0;
        m_messages[0] = 0;
        m_messages[1] = 0;
        m_messages[2] = 0;
        m_messages[3] = 0;
    }
    int m_messages[4];
    int m_e4;
};

class __declspec(novtable) RHPortraitBitmap : public RHPortraitLifetime005d6260
{
public:
    RHPortraitBitmap()
    {
        *(unsigned *)this = 0x00678b60;
        m_state = 0;
    }
};

class __declspec(novtable) RHPortraitCustomBitmap : public RHGameLifetime00516a60
{
public:
    RHPortraitCustomBitmap()
    {
        *(unsigned *)this = 0x00678bb8;
        m_state = 0;
    }
};

class __declspec(novtable) RHPortraitCustomBackground : public RHGameLifetime00516a60
{
public:
    RHPortraitCustomBackground()
    {
        *(unsigned *)this = 0x0067a398;
    }
};

class RHPortraitResourceInterface
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2(unsigned flags) = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5(RHPortraitResourceCollection &collection, bool value) = 0;
    virtual void v6() = 0;
};

class __declspec(novtable) RHPortraitFullLifetime : public RHPortraitRootLifetime
{
public:
    RHPortraitFullLifetime(unsigned short index, RHPortraitActorCalls *actor);
    ~RHPortraitFullLifetime();
    void *FUN_005d61e0(unsigned flags);
    RHPortraitActionWidget m_action;
    RHPortraitMessageBitmap m_first;
    RHPortraitMessageBitmap m_second;
    RHPortraitMessageWidget m_buttonFirst;
    RHPortraitMessageWidget m_buttonSecond;
    RHPortraitMessageWidget m_buttonThird;
    RHPortraitBitmap m_bitmapFirst;
    RHPortraitCustomBitmap m_customFirst;
    RHPortraitBitmap m_bitmapSecond;
    RHPortraitCustomBackground m_customSecond;
    RHPortraitLifetime005d6320 m_quick[3];
    undefined m_c88[0x22];
    unsigned short m_caa;
    int m_cac;
    undefined m_cb0[4];
    SBGeoBoundingBox2D m_positions[9];
    SBGeoBoundingBox2D m_hiddenPositions[9];
    RHPortraitActorCalls *m_actor;
    SBGeoPoint2D m_point;
    RHPortraitResourceInterface *m_portraitResource;
    RHPortraitResourceInterface *m_backgroundResource;
    RHPortraitResourceCollection m_resources;
    unsigned short m_e50[3];
};

class RHPortraitSetupDispatch
{
public:
    virtual void v0() = 0;
    virtual void v1(unsigned value) = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual bool v12(const std::wstring &text, const SBGeoBoundingBox2D &box, bool value, const std::wstring &name) = 0;
};

inline const char *RHPortraitResourceName()
{
    // STRING: GAME 0x006b8e58
    return "PCPortrait";
}

inline const char *RHPortraitBackgroundName()
{
    // STRING: GAME 0x006b01a0
    return "Background";
}

inline const wchar_t *RHPortraitSwordName()
{
    // STRING: GAME 0x006b8e4c
    return L"Sword";
}

DECOMP_SIZE_ASSERT(RHPortraitActionWidget, 0xec)
DECOMP_SIZE_ASSERT(RHPortraitMessageBitmap, 0xdc)
DECOMP_SIZE_ASSERT(RHPortraitMessageWidget, 0xe8)
DECOMP_SIZE_ASSERT(RHPortraitCustomBitmap, 0xf4)
DECOMP_SIZE_ASSERT(RHPortraitFullLifetime, 0xe58)

#include <list>
#include <vector>

class RHPortraitInputField
{
public:
    void FUN_005cf300();
    void FUN_005cf380();
    RHPortraitBoxEvent *FUN_005cf880(unsigned value);
    RHPortraitWidgetEvent *FUN_005d0a10(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d0a90(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d0d00(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1090(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1270(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d14e0(const RHPortraitWidgetInput &input);
    bool FUN_005d1630(const RHPortraitWidgetInput &input, unsigned short key);
    void FUN_005d1670();
    void FUN_005d1700();
    bool FUN_005d1790(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d1810(const RHPortraitWidgetInput &input);
    unsigned short FUN_005d18f0(const SBGeoPoint2D &point);
    RHPortraitInputRenderer &Renderer() { return *(RHPortraitInputRenderer *)((char *)this + 0x80); }
    undefined m_00[0x4c];
    RHPortraitWidgetEvent m_event;
    undefined m_5c[0x7c - 0x5c];
    int m_state;
    undefined m_80[0x10c - 0x80];
    int m_10c;
    undefined m_110[0x13c - 0x110];
    unsigned m_13c;
    undefined m_140[0x188 - 0x140];
    unsigned short m_188;
    unsigned short m_18a;
    unsigned short m_18c;
};

// FUNCTION: GAME 0x005cf300
void RHPortraitInputField::FUN_005cf300()
{
    *(unsigned short *)((char *)this + 0x196) = 0xffff;
    *(unsigned short *)((char *)this + 0x198) = 0xffff;
}

// FUNCTION: GAME 0x005cf320
RHPortraitInputWidget::~RHPortraitInputWidget()
{
}

// FUNCTION: GAME 0x005cf380
void RHPortraitInputField::FUN_005cf380()
{
    int value = -1;
    *(int *)((char *)this + 0xc0) = value;
    *(int *)((char *)this + 0xc4) = value;
}

class RHPortraitTextWidgetDispatch
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

// FUNCTION: GAME 0x005cf880
RHPortraitBoxEvent *RHPortraitInputField::FUN_005cf880(unsigned value)
{
    unsigned buffer = value & 1;
    if (m_18c == ((unsigned short *)((char *)this + 0x196))[buffer]
        && m_18a == ((unsigned short *)((char *)this + 0x192))[buffer]
        && m_188 == ((unsigned short *)((char *)this + 0x18e))[buffer]
        && !((bool *)((char *)this + 0x19a))[buffer])
        return 0;
    RHPortraitBoxEvent *event;
    if (((bool *)((char *)this + 0x19a))[buffer])
    {
        ((bool *)((char *)this + 0x19a))[buffer] = false;
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&Renderer())->FUN_0060d690());
        event = (RHPortraitBoxEvent *)((char *)this + 0x5c);
        *(void **)((char *)this + 0x78) = 0;
        *(void **)((char *)this + 0x74) = this;
        event->m_type = 3;
    }
    else
    {
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&Renderer())->FUN_0060d690());
        RHPortraitTextWidgetDispatch *dispatch = (RHPortraitTextWidgetDispatch *)this;
        event = (RHPortraitBoxEvent *)((char *)this + 0x5c);
        event->m_type = dispatch->v13(dispatch->v9());
        *(void **)((char *)this + 0x78) = 0;
        *(void **)((char *)this + 0x74) = this;
    }
    *(unsigned *)((char *)&Renderer() + 0x48) = value;
    ((unsigned short *)((char *)this + 0x196))[buffer] = m_18c;
    ((unsigned short *)((char *)this + 0x192))[buffer] = m_18a;
    ((unsigned short *)((char *)this + 0x18e))[buffer] = m_188;
    return event;
}

void EmitPortraitInputReset(RHPortraitInputField *field)
{
    field->FUN_005cf300();
    field->FUN_005cf380();
    field->FUN_005cf880(0);
}

// FUNCTION: GAME 0x005cfc30
int RHPortraitInputCalls::FUN_005cfc30(const void *input)
{
    const SBGeoPoint2D &point = *(const SBGeoPoint2D *)input;
    if (((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_006083b0(point) &&
        !((RHPortraitInputRenderer *)((char *)this + 0x80))->FUN_0061d7c0().FUN_00608400(point))
        return 1;
    return 0;
}

class RHPortraitUnk005d06d0
{
public:
    void *FUN_005d06d0();
    RHPortraitWidgetEvent *FUN_005d06e0(bool enabled);
};

// FUNCTION: GAME 0x005d06d0
void *RHPortraitUnk005d06d0::FUN_005d06d0()
{
    return (void *)((char *)this - 0x1d4);
}

// FUNCTION: GAME 0x005d06e0
RHPortraitWidgetEvent *RHPortraitUnk005d06d0::FUN_005d06e0(bool enabled)
{
    RHPortraitWidgetEvent *event = 0;
    unsigned short &selected = *(unsigned short *)((char *)this - 0x4c);
    if (enabled && selected == 0xffff && *(unsigned short *)((char *)this - 0xc8) > 0)
    {
        unsigned short value = *(unsigned short *)((char *)this - 0x4a);
        if (value == 0xffff)
            value = *(unsigned short *)((char *)this - 0x48);
        selected = value;
        *(void **)((char *)this + 0x2c) = (char *)this - 0x1d4;
        int &eventType = *(int *)((char *)this + 0x28);
        eventType = 15;
        *(int *)((char *)this + 0x30) = selected;
        *(void **)((char *)this + 0x34) = 0;
        event = (RHPortraitWidgetEvent *)&eventType;
    }
    *(bool *)((char *)this + 0x24) = enabled;
    ((RHGameWidgetAnimatedCalls *)((char *)this + 8))->FUN_005d5790(event, *(int *)((char *)this - 0x158), false);
    return event;
}

void EmitRHPortraitUnk005d06d0(RHPortraitUnk005d06d0 *strategy)
{
    strategy->FUN_005d06d0();
    strategy->FUN_005d06e0(false);
}

// FUNCTION: GAME 0x005d09b0
void *RHPortraitInputWidget::FUN_005d09b0(unsigned flags)
{
    this->~RHPortraitInputWidget();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d09d0
void *RHPortraitUnk005cf570::FUN_005d09d0(unsigned flags)
{
    this->~RHPortraitUnk005cf570();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d09f0
void *RHPortraitUnk005d0180::FUN_005d09f0(unsigned flags)
{
    this->~RHPortraitUnk005d0180();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: Boolean tests still use test al,al instead of the retained zero register.
// STUB: GAME 0x005d0a10
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d0a10(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    Renderer().FUN_0061d570(m_18c, m_13c);
    if ((unsigned char)((RHPortraitInputCalls *)this)->FUN_005cfc30(&input))
    {
        result = &m_event;
        m_state = 1;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        result->type = 0;
    }
    else if (FUN_005d1790(input))
    {
        result = &m_event;
        m_state = 4;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        result->type = 0;
    }
    return result;
}

// Parked: Focus, scroll and hover branches need register and return-tail alignment.
// STUB: GAME 0x005d0a90
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d0a90(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    RHPortraitInputRenderer &renderer = Renderer();
    renderer.FUN_0061d570(m_18c, m_13c);
    if (FUN_005d1790(input))
    {
        if (!(input.flags & 0x40))
            m_state = 4;
        if (m_18a != 0xffff)
        {
            result = &m_event;
            m_18a = 0xffff;
            m_event.widget = this;
            m_event.value = 0xffff;
            m_event.next = 0;
            result->type = 14;
        }
    }
    else if (!((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_006083b0(input.point))
    {
        m_state = 0;
        if (m_18a != 0xffff)
        {
            result = &m_event;
            m_18a = 0xffff;
            m_event.widget = this;
            m_event.value = 0xffff;
            m_event.next = 0;
            result->type = 14;
        }
    }
    else if (input.wheel != 0)
    {
        RHPortraitWidgetEvent *scroll = 0;
        if (input.wheel > 0)
        {
            if (m_18c > 0)
            {
                --m_18c;
                renderer.FUN_0061d570(m_18c, m_13c);
                scroll = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                scroll->type = 13;
            }
        }
        else if (input.wheel < 0)
        {
            unsigned limit = m_13c;
            unsigned short line = m_18c;
            if (renderer.FUN_0061d5e0() + line + 1 <= limit)
            {
                m_18c = line + 1;
                renderer.FUN_0061d570(m_18c, m_13c);
                scroll = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                scroll->type = 12;
            }
        }
        return scroll;
    }
    else if (input.flags & 8)
    {
        result = &m_event;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        result->type = 2;
    }
    else if (input.flags & 2)
    {
        if (m_188 != 0xffff)
        {
            result = &m_event;
            m_188 = 0xffff;
            m_event.widget = this;
            m_event.value = 0xffff;
            m_event.next = 0;
            result->type = 15;
        }
    }
    else
    {
        unsigned short position = FUN_005d18f0(input.point);
        if (input.flags & 0x40)
        {
            m_state = 2;
            input.ui->m_selected = (RHPortraitUnk005d3880 *)this;
        }
        SBGeoPoint2D &previous = *(SBGeoPoint2D *)((char *)this + 0x1a4);
        if (m_18a != position && previous.FUN_005fc0e0(input.point))
        {
            m_18a = position;
            previous = input.point;
            result = &m_event;
            m_event.widget = this;
            result->type = 14;
            m_event.value = m_18a;
            m_event.next = 0;
        }
    }
    return result;
}

// Parked: Repeated line-box temporaries and scroll paths need frame/EH alignment.
// STUB: GAME 0x005d0d00
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d0d00(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    RHPortraitInputRenderer &renderer = Renderer();
    renderer.FUN_0061d570(m_18c, m_13c);
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(input.point) && !renderer.FUN_0061d7c0().FUN_00608400(input.point))
    {
        if (!(input.flags & 0x40))
            m_state = 1;
    }
    else if (!box.FUN_006083b0(input.point))
        m_state = 0;
    else if (input.wheel != 0)
    {
        RHPortraitWidgetEvent *scroll = 0;
        if (input.wheel > 0)
        {
            if (m_18c > 0)
            {
                --m_18c;
                renderer.FUN_0061d570(m_18c, m_13c);
                scroll = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                scroll->type = 13;
            }
        }
        else if (input.wheel < 0)
        {
            unsigned limit = m_13c;
            unsigned short line = m_18c;
            if (renderer.FUN_0061d5e0() + line + 1 <= limit)
            {
                m_18c = line + 1;
                renderer.FUN_0061d570(m_18c, m_13c);
                scroll = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                scroll->type = 12;
            }
        }
        return scroll;
    }
    else if (input.flags & 1)
    {
        if (input.point.m_y < renderer.FUN_0061d620().m_first.m_y && m_18c > 0)
        {
            --m_18c;
            renderer.FUN_0061d570(m_18c, m_13c);
            *(SBGeoPoint2D *)((char *)this + 0x1a4) = input.point;
            result = &m_event;
            m_event.widget = this;
            m_event.value = 0;
            m_event.next = 0;
            result->type = 13;
        }
        else if (input.point.m_y > renderer.FUN_0061d620().m_second.m_y)
        {
            unsigned limit = m_13c;
            unsigned short line = m_18c;
            if (renderer.FUN_0061d5e0() + line + 1 <= limit)
            {
                m_18c = line + 1;
                renderer.FUN_0061d570(m_18c, m_13c);
                *(SBGeoPoint2D *)((char *)this + 0x1a4) = input.point;
                result = &m_event;
                m_event.widget = this;
                m_event.value = 0;
                m_event.next = 0;
                result->type = 12;
            }
        }
    }
    else if ((input.flags & 0x40) && renderer.FUN_0061d620().FUN_006083b0(input.point))
    {
        *(SBGeoPoint2D *)((char *)this + 0x1a4) = input.point;
        input.ui->m_selected = (RHPortraitUnk005d3880 *)this;
        m_state = 5;
    }
    return result;
}

// Parked: Scroll and selection live ranges need codegen alignment.
// STUB: GAME 0x005d1090
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d1090(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    RHPortraitInputRenderer &renderer = Renderer();
    renderer.FUN_0061d570(m_18c, m_13c);
    if (input.wheel != 0)
    {
        RHPortraitWidgetEvent *scroll = 0;
        if (input.wheel > 0)
        {
            if (m_18c > 0)
            {
                --m_18c;
                renderer.FUN_0061d570(m_18c, m_13c);
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                scroll = &m_event;
                scroll->type = 13;
            }
        }
        else if (input.wheel < 0)
        {
            unsigned limit = m_13c;
            unsigned short line = m_18c;
            if (renderer.FUN_0061d5e0() + line + 1 <= limit)
            {
                m_18c = line + 1;
                renderer.FUN_0061d570(m_18c, m_13c);
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                scroll = &m_event;
                scroll->type = 12;
            }
        }
        return scroll;
    }
    unsigned short position = FUN_005d18f0(input.point);
    if (m_18a != position)
    {
        m_18a = position;
        result = &m_event;
        m_event.widget = this;
        result->type = 14;
        m_event.value = position;
        m_event.next = 0;
    }
    if ((unsigned char)((RHPortraitInputCalls *)this)->FUN_005cfc30(&input))
    {
        if (input.flags & 1)
        {
            m_188 = m_18a;
            input.ui->Clear();
            result = &m_event;
            m_event.next = 0;
            m_event.widget = this;
            m_event.value = m_188;
            m_state = 1;
            result->type = 15;
            return result;
        }
        else if (input.flags & 8)
        {
            input.ui->Clear();
            result = &m_event;
            m_event.value = 0;
            m_event.next = 0;
            m_event.widget = this;
            m_state = 1;
            result->type = 2;
            return result;
        }
    }
    else
        m_state = 3;
    return result;
}

// Parked: Drag-distance and repeated geometry temporary EH slots need alignment.
// STUB: GAME 0x005d1270
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d1270(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    if (input.flags & 0x40)
    {
        SBGeoPoint2D &previous = *(SBGeoPoint2D *)((char *)this + 0x1a4);
        bool moved;
        {
            SBGeoPoint2D difference = previous.Unk005fc110(input.point);
            float distance = ((RHUnk005fc3b0 *)&difference)->Unk005fc6a0(1.0f);
            moved = Renderer().FUN_0061d950() < distance;
        }
        if (moved)
        {
            if (input.point.m_y < previous.m_y)
            {
                if (m_18c > 0)
                {
                    --m_18c;
                    Renderer().FUN_0061d570(m_18c, m_13c);
                    previous = input.point;
                    result = &m_event;
                    m_event.widget = this;
                    result->type = 13;
                    m_event.value = m_18c;
                    m_event.next = 0;
                }
            }
            else
            {
                unsigned short line = m_18c;
                unsigned limit = m_13c;
                if (Renderer().FUN_0061d5e0() + line + 1 <= limit)
                {
                    m_18c = line + 1;
                    previous = input.point;
                    Renderer().FUN_0061d570(m_18c, m_13c);
                    result = &m_event;
                    m_event.widget = this;
                    result->type = 12;
                    m_event.value = m_18c;
                    m_event.next = 0;
                }
            }
        }
    }
    else
    {
        input.ui->Clear();
        if (((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_006083b0(input.point) &&
            !Renderer().FUN_0061d7c0().FUN_00608400(input.point))
            m_state = 1;
        else if (Renderer().FUN_0061d7c0().FUN_00608400(input.point))
            m_state = 4;
        else
            m_state = 0;
    }
    return result;
}

// Parked: Scroll event and capture receiver scheduling need codegen alignment.
// STUB: GAME 0x005d14e0
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d14e0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *outside = 0;
    if (((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_00608400(input.point))
    {
        RHPortraitWidgetEvent *result = 0;
        short delta = input.wheel;
        if (delta > 0)
        {
            if (m_18c > 0)
            {
                --m_18c;
                Renderer().FUN_0061d570(m_18c, m_13c);
                result = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                result->type = 13;
            }
        }
        else if (delta < 0)
        {
            unsigned limit = m_13c;
            unsigned short line = m_18c;
            RHPortraitInputRenderer &renderer = Renderer();
            if (renderer.FUN_0061d5e0() + line + 1 <= limit)
            {
                m_18c = line + 1;
                renderer.FUN_0061d570(m_18c, m_13c);
                RHPortraitWidgetEvent *event = &m_event;
                m_event.next = 0;
                m_event.widget = this;
                m_event.value = 0;
                event->type = 12;
                result = event;
            }
        }
        if ((unsigned char)((RHPortraitInputCalls *)this)->FUN_005cfc30(&input))
            m_state = 2;
        else if (input.flags & 1)
        {
            m_state = 4;
            input.ui->Clear();
        }
        return result;
    }
    if (input.flags & 1)
    {
        m_state = 0;
        input.ui->Clear();
    }
    return outside;
}

// FUNCTION: GAME 0x005d1630
bool RHPortraitInputField::FUN_005d1630(const RHPortraitWidgetInput &input, unsigned short key)
{
    int pressed = input.shortcuts->FUN_0060e240(key);
    int state = ((int *)((char *)input.shortcuts + 0xa0c))[key];
    if (pressed == 1 && (state == 2 || state == 0))
        return true;
    return false;
}

// Parked: Constant-mask allocation and branch placement differ from the target.
// STUB: GAME 0x005d1670
void RHPortraitInputField::FUN_005d1670()
{
    unsigned short invalid = 0xffff;
    unsigned short position = m_188;
    if (position != invalid)
    {
        if (position < m_10c - 1)
        {
            unsigned short line = m_18c;
            m_188 = position + 1;
            if (m_188 >= Renderer().FUN_0061d5e0() + line)
                m_18c = line + 1;
        }
    }
    else
        m_188 = m_18a != invalid ? m_18a : m_18c;
    m_18a = invalid;
}

// Parked: The compiler folds the invalid index instead of retaining it in esi.
// STUB: GAME 0x005d1700
void RHPortraitInputField::FUN_005d1700()
{
    const unsigned short invalid = 0xffff;
    if (m_188 == invalid)
    {
        unsigned short position = m_18a != invalid ? m_18a : m_18c;
        m_18a = invalid;
        m_188 = position;
        return;
    }
    if (m_188 > 0)
    {
        unsigned short line = m_18c;
        --m_188;
        if (m_188 < line)
            m_18c = line - 1;
    }
    m_18a = invalid;
}

// FUNCTION: GAME 0x005d1790
bool RHPortraitInputField::FUN_005d1790(const RHPortraitWidgetInput &input)
{
    return Renderer().FUN_0061d7c0().FUN_00608400(input.point);
}

// FUNCTION: GAME 0x005d1810
RHPortraitWidgetEvent *RHPortraitInputField::FUN_005d1810(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *scroll = 0;
    short wheel = input.wheel;
    unsigned short &line = m_18c;
    if (wheel > 0)
    {
        if (line > 0)
        {
            --line;
            Renderer().FUN_0061d570(line, m_13c);
            m_event.next = 0;
            m_event.widget = this;
            scroll = &m_event;
            m_event.value = 0;
            scroll->type = 13;
        }
    }
    else if (wheel < 0)
    {
        unsigned limit = m_13c;
        RHPortraitInputRenderer &renderer = Renderer();
        unsigned short current = line;
        if (renderer.FUN_0061d5e0() + current + 1 <= limit)
        {
            line = current + 1;
            renderer.FUN_0061d570(line, m_13c);
            m_event.next = 0;
            m_event.widget = this;
            scroll = &m_event;
            m_event.value = 0;
            scroll->type = 12;
        }
    }
    return scroll;
}

struct RHPortraitTextLine
{
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
};

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHPortraitTextNode
{
    RHPortraitTextNode *next;
    RHPortraitTextNode *previous;
    RHPortraitTextLine value;
};

class RHPortraitTextCursor
{
public:
    RHPortraitTextLine &At(int index)
    {
        int count = m_count;
        std::bidirectional_iterator_tag category;
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                m_current = m_head->next;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
            }
            else
            {
                m_current = m_head;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        m_current = (RHPortraitTextNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
                    }
                    else
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                }
                else if (index < (previous + count) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                else
                {
                    m_current = m_head;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
                }
                m_index = index;
            }
        }
        return m_current->value;
    }
    int m_allocator;
    RHPortraitTextNode *m_head;
    int m_count;
    RHPortraitTextNode *m_current;
    bool m_dirty;
    int m_index;
};

// Parked: Cached-list iterator and line-box temporary codegen need alignment.
// STUB: GAME 0x005d18f0
unsigned short RHPortraitInputField::FUN_005d18f0(const SBGeoPoint2D &point)
{
    for (unsigned short index = 0; index < m_10c; ++index)
    {
        RHPortraitTextCursor &lines = *(RHPortraitTextCursor *)((char *)this + 0x164);
        if (Renderer().FUN_0061d3f0(index - m_18c, lines.At(index).m_00).FUN_00608400(point))
            return index;
    }
    return 0xffff;
}

#include <stddef.h>

DECOMP_SIZE_ASSERT(std::wstring, 0x10)
DECOMP_SIZE_ASSERT(RHPortraitInputWidget, 0x104)
DECOMP_SIZE_ASSERT(RHPortraitTextLines, 0x30)
DECOMP_SIZE_ASSERT(RHPortraitItemIndices, 0x18)
DECOMP_SIZE_ASSERT(RHPortraitUnk005cf570, 0x1d4)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitUnk005cf570, m_first) == 0x104)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitUnk005cf570, m_second) == 0x134)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitUnk005cf570, m_items) == 0x164)

// Parked: cached-list helper identities and inline cleanup boundaries differ.
// STUB: GAME 0x005cf570
RHPortraitUnk005cf570::~RHPortraitUnk005cf570()
{
}

// FUNCTION: GAME 0x005d1aa0
RHPortraitTextLines::RHPortraitTextLines() : m_dirty(true)
{
}

// FUNCTION: GAME 0x005cf760
unsigned short RHPortraitUnk005cf570::AddItem(const std::wstring &text, std::wstring value, unsigned long index)
{
    m_second.Append(text);
    m_first.Append(value);
    m_items.Append(index);
    return m_first.m_list.size() - 1;
}

void EmitRHPortraitListItem(RHPortraitUnk005cf570 &widget, const std::wstring &text, std::wstring value, unsigned long index)
{
    widget.AddItem(text, value, index);
}

// TEMPLATE: GAME 0x005d0750
// ??Hstd@@YA?AV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@0@ABV10@PBG@Z

std::wstring EmitRHPortraitWideConcatenation(const std::wstring &text, const wchar_t *suffix)
{
    std::wstring (*concatenate)(const std::wstring &, const wchar_t *) = &std::operator+;
    return concatenate(text, suffix);
}

// TEMPLATE: GAME 0x004242b0 FOLDED
// ?_Buynode@?$list@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@IAEPAU_Node@12@PAU312@0@Z

// TEMPLATE: GAME 0x0059f720 FOLDED
// ?_Buynode@?$list@KV?$allocator@K@std@@@std@@IAEPAU_Node@12@PAU312@0@Z

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAKABK@Z

// FUNCTION: GAME 0x005d1ae0
RHPortraitInputWidget::RHPortraitInputWidget()
{
}

// FUNCTION: GAME 0x005d1b40
void *RHPortraitInputRendererMember::FUN_005d1b40(unsigned flags)
{
    this->RHPortraitInputRendererMember::~RHPortraitInputRendererMember();
    if (flags & 1)
        operator delete(this);
    return this;
}

#include "RHPortraitButton.h"

// SYNTHETIC: GAME 0x005d1b60
// RHPortraitInputRendererMember::~RHPortraitInputRendererMember

DECOMP_SIZE_ASSERT(RHPortraitButton, 0x100)
DECOMP_SIZE_ASSERT(RHPortraitButtonStrategy, 0x04)

// FUNCTION: GAME 0x005d1bf0
RHPortraitButton::RHPortraitButton() : RHPortraitAnimated(2), m_f8(0), m_fc(0)
{
    RHUnk00514e10 &map = m_map;
    RHPortraitMapLookup(map, 0) = 1;
    RHPortraitMapLookup(map, 2) = 0;
}

// FUNCTION: GAME 0x005d1ce0
void *RHPortraitButton::FUN_005d1ce0(unsigned flags)
{
    this->~RHPortraitButton();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d1d00
RHPortraitButton::~RHPortraitButton()
{
}

// FUNCTION: GAME 0x005d1de0
RHPortraitWidgetEvent *RHPortraitButtonStrategy::FUN_005d1de0()
{
    RHPortraitWidgetEvent *event = 0;
    if (*((char *)this - 0xd4))
    {
        RHGameWidgetAnimatedCalls *animated = (RHGameWidgetAnimatedCalls *)((char *)this + 4);
        *(void **)((char *)this - 0x88) = (char *)this - 0xd8;
        event = (RHPortraitWidgetEvent *)((char *)this - 0x8c);
        event->type = 2;
        *(int *)((char *)this - 0x84) = 0;
        *(int *)((char *)this - 0x80) = 0;
        animated->FUN_005d5790(event, *(int *)((char *)this - 0x5c), 0);
    }
    return event;
}

// Parked: The box address and resource input have different constructor-call live ranges.
// STUB: GAME 0x005d1e30
bool RHPortraitButton::FUN_005d1e30(int mode, const std::wstring &text, int resource)
{
    {
        RHMapBox box(0.0f, 0.0f, 0.0f, 0.0f);
        if (!resource)
            resource = -1;
        ((RHGameWidgetLifetimeBase *)this)->Create(text, *(SBGeoBoundingBox2D *)&box, 0);
        RHPortraitRendererDispatch *renderer = (RHPortraitRendererDispatch *)((char *)this + 0x80);
        renderer->v3(*(SBGeoBoundingBox2D *)&box);
        ((SBUIUnk0060d530 *)renderer)->FUN_0060d550(resource);
        *(int *)((char *)this + 0xa4) = 0;
        RHPortraitAssignWideText((char *)this + 0xa8, text);
        SBGeoBoundingBox2D &bounds = Box();
        if (bounds.m_second.m_x - bounds.m_first.m_x == 0.0f)
            ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)renderer)->FUN_0060d690());
    }
    ((RHPortraitRenderer005cadc0 *)((char *)this + 0x80))->FUN_005cae10(mode);
    return true;
}

// FUNCTION: GAME 0x005d1f30
RHPortraitButton *RHPortraitButtonStrategy::FUN_005d1f30()
{
    return (RHPortraitButton *)((char *)this - 0xd8);
}

// FUNCTION: GAME 0x005d1f40
void RHPortraitButtonStrategy::FUN_005d1f40(bool value)
{
    *(bool *)((char *)this + 0x24) = value;
}

// FUNCTION: GAME 0x005d1f50
int RHPortraitButtonStrategy::FUN_005d1f50(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this - 0xa8);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this - 0x58))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)) == true)
        return true;
    return false;
}

// FUNCTION: GAME 0x005d1ff0
int RHPortraitButtonStrategy::FUN_005d1ff0()
{
    return *(int *)((char *)this - 0x5c) == 0;
}

void EmitPortraitStrategyAccessors(RHPortraitButtonStrategy *strategy)
{
    strategy->FUN_005d1f30();
    strategy->FUN_005d1f40(true);
    strategy->FUN_005d1ff0();
}

// FUNCTION: GAME 0x005d2000
RHPortraitWidgetEvent *RHPortraitButton::FUN_005d2000(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event;
    if (!*((char *)this + 4))
        event = 0;
    else
    {
        switch (RHPortraitButtonBase::m_state)
        {
        case 0: event = FUN_005d2090(input); break;
        case 1: event = FUN_005d2120(input); break;
        case 3: event = FUN_005d21f0(input); break;
        case 2: event = FUN_005d22c0(input); break;
        }
    }
    ((RHGameWidgetAnimatedCalls *)((char *)this + 0xdc))->FUN_005d5790(event, RHPortraitButtonBase::m_state, 0);
    return event;
}

// FUNCTION: GAME 0x005d2090
RHPortraitWidgetEvent *RHPortraitButton::FUN_005d2090(const RHPortraitWidgetInput &input)
{
    SBGeoBoundingBox2D &box = Box();
    if (box.FUN_006083b0(input.point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(input.point.Unk005fc110(*(SBGeoPoint2D *)&box)) == true &&
        !(input.flags & 0x40))
        RHPortraitButtonBase::m_state = 1;
    return 0;
}

// Parked: The zero value is hoisted across point cleanup rather than created in the event arm.
// STUB: GAME 0x005d2120
RHPortraitWidgetEvent *RHPortraitButton::FUN_005d2120(const RHPortraitWidgetInput &input)
{
    SBGeoBoundingBox2D &box = Box();
    if (box.FUN_006083b0(input.point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(input.point.Unk005fc110(*(SBGeoPoint2D *)&box)))
    {
        if (input.flags & 0x40)
        {
            RHPortraitButtonBase::m_state = 3;
            input.ui->m_selected = (RHPortraitUnk005d3880 *)this;
            return 0;
        }
        RHPortraitWidgetEvent *event = &Event();
        *(void **)((char *)this + 0x50) = this;
        *(int *)((char *)this + 0x54) = 0;
        *(int *)((char *)this + 0x58) = 0;
        event->type = 0;
        return event;
    }
    RHPortraitButtonBase::m_state = 0;
    return 0;
}

// Parked: Event and capture-zero liveness changes the point temporary registers and EH offsets.
// STUB: GAME 0x005d21f0
RHPortraitWidgetEvent *RHPortraitButton::FUN_005d21f0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result;
    SBGeoBoundingBox2D &box = Box();
    if (box.FUN_006083b0(input.point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(input.point.Unk005fc110(*(SBGeoPoint2D *)&box)))
    {
        if (input.flags & 9)
        {
            input.ui->Clear();
            RHPortraitButtonBase::m_state = 1;
            result = &Event();
            *(void **)((char *)this + 0x50) = this;
            *(int *)((char *)this + 0x54) = 0;
            *(int *)((char *)this + 0x58) = 0;
            result->type = 2;
        }
        else
            result = 0;
    }
    else
    {
        RHPortraitButtonBase::m_state = 2;
        result = 0;
    }
    return result;
}

// FUNCTION: GAME 0x005d22c0
RHPortraitWidgetEvent *RHPortraitButton::FUN_005d22c0(const RHPortraitWidgetInput &input)
{
    SBGeoBoundingBox2D &box = Box();
    if (box.FUN_006083b0(input.point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(input.point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        RHPortraitButtonBase::m_state = 3;
    else if (input.flags & 1)
    {
        input.ui->Clear();
        RHPortraitButtonBase::m_state = 0;
    }
    return 0;
}

// FUNCTION: GAME 0x005d2370
RHPortraitWidgetEvent *RHPortraitButtonStrategy::FUN_005d2370(bool value)
{
    RHPortraitWidgetEvent *event = 0;
    *(int *)((char *)this + 0x20) = value == 1;
    if (*((char *)this - 0xd4) == 1)
    {
        if (value)
        {
            *(void **)((char *)this - 0x88) = (char *)this - 0xd8;
            event = (RHPortraitWidgetEvent *)((char *)this - 0x8c);
            event->type = 0;
            *(int *)((char *)this - 0x84) = 0;
            *(int *)((char *)this - 0x80) = 0;
        }
        ((RHGameWidgetAnimatedCalls *)((char *)this + 4))->FUN_005d5790(event, *(int *)((char *)this + 0x20), 0);
    }
    return event;
}

// FUNCTION: GAME 0x005d23d0
RHPortraitWidgetEvent *RHPortraitButtonStrategy::FUN_005d23d0(bool value)
{
    *(int *)((char *)this + 0x20) = value == 1 ? 3 : 0;
    return 0;
}

// FUNCTION: GAME 0x005d23f0
int RHPortraitButton::FUN_005d23f0()
{
    int result;
    if (!*((char *)this + 4))
        return 0;
    int state = RHPortraitButtonBase::m_state;
    if (state <= m_f8)
        state = m_f8;
    switch (state)
    {
    case 0: result = 1; break;
    case 1: result = m_fc == 1 ? 1 : 2; break;
    case 3: result = 3; break;
    case 2: result = 2; break;
    }
    return result;
}

// SYNTHETIC: GAME 0x005d2460
// ??1RHPortraitButtonBase@@QAE@XZ

// FUNCTION: GAME 0x005d24c0
void RHPortraitButtonBase::FUN_005d24c0()
{
    unsigned id = ((RHPortraitButtonDispatch *)this)->v9();
    ((RHPortraitRenderer005cadc0 *)&m_renderer)->FUN_005cafa0(id);
}

// FUNCTION: GAME 0x005d24e0
void RHPortraitButtonBase::FUN_005d24e0()
{
    ((SBUIUnk0060d530 *)&m_renderer)->FUN_0060d520();
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x005d24f0
void *RHPortraitButtonBase::FUN_005d24f0(unsigned flags)
{
    this->~RHPortraitButtonBase();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

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
    RHPortraitWidgetEvent *FUN_005d3090(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005d33d0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent &Event() { return *(RHPortraitWidgetEvent *)((char *)this + 0x4c); }
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
    bool FUN_005d2810(const SBGeoPoint2D &point, RHPortraitTextResourceCalls *resources);
    RHPortraitWidgetEvent *FUN_005d2a70(const RHPortraitWidgetInput &input);
};

DECOMP_SIZE_ASSERT(RHPortraitTextWidgetBase, 0x110)
DECOMP_SIZE_ASSERT(RHPortraitTextWidget, 0x180)
DECOMP_SIZE_ASSERT(RHPortraitEditableStrategy, 0x08)
DECOMP_SIZE_ASSERT(RHPortraitEditableWidget, 0x1a4)

// FUNCTION: GAME 0x005d25c0
RHPortraitEditableWidget::RHPortraitEditableWidget() : RHPortraitAnimated(42)
{
    RHUnk00514e10 &map = m_map;
    RHPortraitMapLookup(map, 0) = 1;
    RHPortraitMapLookup(map, 2) = 0;
}

// FUNCTION: GAME 0x005d26f0
void *RHPortraitEditableWidget::FUN_005d26f0(unsigned flags)
{
    this->~RHPortraitEditableWidget();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d2710
RHPortraitEditableWidget::~RHPortraitEditableWidget()
{
}

// GLOBAL: GAME 0x006c0b50
wchar_t g_unk0x006c0b50[1] = {0};

// Parked: Resource lookup binding and nested string/box lifetimes need codegen alignment.
// STUB: GAME 0x005d2810
bool RHPortraitEditableWidget::FUN_005d2810(const SBGeoPoint2D &point, RHPortraitTextResourceCalls *resources)
{
    // STRING: GAME 0x006b0d50
    void *resource = resources->FUN_0053be80(std::string("EditField"));
    RHPortraitRendererDispatch *renderer = (RHPortraitRendererDispatch *)&m_renderer;
    {
        std::wstring text(g_unk0x006c0b50);
        SBGeoBoundingBox2D box(point, point);
        ((RHGameWidgetLifetimeBase *)this)->Create(text, box, 0);
        renderer->v3(box);
        ((SBUIUnk0060d530 *)renderer)->FUN_0060d550(0xbf);
        *(int *)((char *)this + 0xa4) = 0;
        RHPortraitAssignWideText((char *)this + 0xa8, text);
        SBGeoBoundingBox2D &bounds = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
        if (bounds.m_second.m_x - bounds.m_first.m_x == 0.0f)
            ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)renderer)->FUN_0060d690());
    }
    *(void **)((char *)this + 0x124) = resource;
    *(void **)((char *)this + 0x128) = resource;
    ((SBUIInputFieldUnk00621440 *)renderer)->FUN_00621440((SBUIInputFieldUnkResource *)&m_text);
    ((SBUIInputFieldUnk00621440 *)renderer)->FUN_00621c30(*(SBGeoBoundingBox2D *)&RHMapBox(10.0f, 10.0f, 403.0f, 20.0f));
    ((SBGeoVector2D *)((char *)this + 0x108))->operator=(SBGeoVector2D(-1.0f, -5.0f));
    return true;
}

// Parked: Animated text-state switch and linked-widget cleanup need codegen alignment.
// STUB: GAME 0x005d2a70
RHPortraitWidgetEvent *RHPortraitEditableWidget::FUN_005d2a70(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    RHPortraitWidgetEvent &event = *(RHPortraitWidgetEvent *)((char *)this + 0x4c);
    if (*((char *)this + 4))
    {
        switch (RHPortraitTextWidgetBase::m_state)
        {
        case 0:
            if (((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point) && !(input.flags & 0x40))
            {
                result = &event;
                RHPortraitTextWidgetBase::m_state = 1;
                event.widget = this;
                event.value = 0;
                result->type = 0;
                event.next = 0;
            }
            break;
        case 1:
            if (((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point))
            {
                if (input.flags & 0x40)
                {
                    RHPortraitTextWidgetBase::m_state = 4;
                    input.ui->m_selected = (RHPortraitUnk005d3880 *)this;
                }
            }
            else if (!(input.flags & 0x40))
            {
                RHPortraitTextWidgetBase::m_state = 0;
                input.ui->Clear();
            }
            break;
        case 4:
            if (((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point))
            {
                if (input.flags & 1)
                {
                    if (!m_linked)
                    {
                        RHPortraitTextWidgetBase::m_state = 13;
                        ((SBUIInputFieldUnk00621440 *)&m_text)->FUN_0061e340();
                        ((SBUIInputFieldTextUnk *)&m_text)->FUN_0061e320(1);
                        result = &event;
                        event.next = 0;
                        event.widget = this;
                        event.value = 0;
                        result->type = 8;
                    }
                    else
                    {
                        RHPortraitTextWidgetBase::m_state = 2;
                        input.ui->Clear();
                        RHPortraitTextWidget *linked = m_linked;
                        if (linked != this)
                        {
                            if (linked->m_state == 2 || linked->m_state == 13)
                            {
                                ((SBUIInputFieldTextUnk *)&linked->m_text)->FUN_0061e320(0);
                                linked->m_state = 0;
                            }
                            if (linked->m_linked)
                                ((RHPortraitTextLinkedCalls *)linked->m_linked)->FUN_0053f9f0(this);
                        }
                    }
                }
            }
            else
            {
                RHPortraitTextWidgetBase::m_state = 1;
                if (input.flags & 1)
                    input.ui->Clear();
            }
            break;
        case 2:
            if (((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point) && (input.flags & 8))
            {
                result = &event;
                event.next = 0;
                event.widget = this;
                event.value = 0;
                result->type = 3;
            }
            break;
        case 13:
            result = FUN_005d33d0(input);
            break;
        }
    }
    ((RHGameWidgetAnimatedCalls *)((char *)this + 0x188))->FUN_005d5790(result, RHPortraitTextWidgetBase::m_state, 0);
    if (m_owner && RHPortraitTextWidgetBase::m_state != 13)
    {
        m_owner->FUN_00500790(true);
        m_owner->FUN_00500780(true);
    }
    return result;
}

// FUNCTION: GAME 0x005d2ca0
RHPortraitTextWidget *RHPortraitEditableStrategy::FUN_005d2ca0()
{
    return (RHPortraitTextWidget *)((char *)this - 0x180);
}

void EmitPortraitEditableAccessors(RHPortraitEditableStrategy *strategy)
{
    strategy->FUN_005d2ca0();
}

// FUNCTION: GAME 0x005d2cb0
RHPortraitWidgetEvent *RHPortraitEditableStrategy::FUN_005d2cb0(bool)
{
    RHPortraitWidgetUI *ui = (RHPortraitWidgetUI *)m_owner->FUN_004fffd0();
    RHPortraitTextWidget *widget = (RHPortraitTextWidget *)((char *)this - 0x180);
    if (widget->m_state != 13)
    {
        ui->m_selected = (RHPortraitUnk005d3880 *)widget;
        widget->m_state = 13;
        ((SBUIInputFieldUnk00621440 *)&widget->m_text)->FUN_0061e340();
        ((SBUIInputFieldTextUnk *)&widget->m_text)->FUN_0061e320(1);
    }
    return 0;
}

// FUNCTION: GAME 0x005d2cf0
void RHPortraitTextWidget::FUN_005d2cf0(const std::wstring &text)
{
    *(int *)((char *)this + 0xc0) = -1;
    *(int *)((char *)this + 0xc4) = -1;
    *(std::wstring *)((char *)this + 0x10) = text;
    m_text.FUN_0061e060(text);
}

// SYNTHETIC: GAME 0x005d2e60
// ??1RHPortraitTextWidgetBase@@QAE@XZ

// FUNCTION: GAME 0x005d2ec0
void RHPortraitTextWidgetBase::FUN_005d2ec0()
{
    unsigned id = ((RHPortraitTextWidgetDispatch *)this)->v9();
    ((SBUIInputFieldUnk00621440 *)&m_renderer)->FUN_00621470(id);
}

// FUNCTION: GAME 0x005d2ee0
void RHPortraitTextWidgetBase::FUN_005d2ee0(const SBGeoBoundingBox2D &box)
{
    RHPortraitRendererDispatch &renderer = *(RHPortraitRendererDispatch *)&m_renderer;
    renderer.v3(box);
    ((RHMobileUnk00607da0 *)((char *)this + 0x30))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&renderer)->FUN_0060d690());
}

// FUNCTION: GAME 0x005d2f10
void RHPortraitTextWidgetBase::FUN_005d2f10(const SBGeoPoint2D &point)
{
    ((RHGameWidgetBaseCalls *)this)->FUN_0060d290(point);
    SBGeoBoundingBox2D copy(point);
    ((RHPortraitRendererDispatch *)&m_renderer)->v3(copy);
}

// FUNCTION: GAME 0x005d2fa0
int RHPortraitTextWidget::FUN_005d2fa0()
{
    if (!*((char *)this + 4))
        return 0;
    int result;
    switch (m_state)
    {
    case 0: result = 1; break;
    case 1: result = 2; break;
    case 4: result = 4; break;
    case 2:
    case 13: result = 3; break;
    default:
        if (result != 1)
            return result;
    }
    if (result == 1 && !*((char *)this + 6))
        result = 255;
    return result;
}

// FUNCTION: GAME 0x005d3020
inline RHPortraitTextWidget::~RHPortraitTextWidget()
{
}

// Parked: Text-state switch registers and linked-widget return tails need alignment.
// STUB: GAME 0x005d3090
RHPortraitWidgetEvent *RHPortraitTextWidget::FUN_005d3090(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result;
    if (*((char *)this + 4))
    {
        switch (m_state)
        {
        case 0:
            result = 0;
            if ((unsigned char)((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point) && !(input.flags & 0x40))
            {
                result = &Event();
                m_state = 1;
                Event().widget = this;
                Event().value = 0;
                result->type = 0;
                Event().next = 0;
            }
            break;
        case 1:
            result = 0;
            if ((unsigned char)((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point))
            {
                if (input.flags & 0x40)
                {
                    m_state = 4;
                    input.ui->m_selected = (RHPortraitUnk005d3880 *)this;
                }
            }
            else if (!(input.flags & 0x40))
            {
                m_state = 0;
                input.ui->Clear();
            }
            break;
        case 4:
            result = 0;
            if ((unsigned char)((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point))
            {
                if (input.flags & 1)
                {
                    if (!m_linked)
                    {
                        m_state = 13;
                        ((SBUIInputFieldUnk00621440 *)&m_text)->FUN_0061e340();
                        ((SBUIInputFieldTextUnk *)&m_text)->FUN_0061e320(1);
                        result = &Event();
                        Event().next = 0;
                        Event().widget = this;
                        Event().value = 0;
                        result->type = 8;
                    }
                    else
                    {
                        m_state = 2;
                        input.ui->Clear();
                        RHPortraitTextWidget *linked = m_linked;
                        if (linked != this)
                        {
                            if (linked->m_state == 2 || linked->m_state == 13)
                            {
                                ((SBUIInputFieldTextUnk *)&linked->m_text)->FUN_0061e320(0);
                                linked->m_state = 0;
                            }
                            if (linked->m_linked)
                                ((RHPortraitTextLinkedCalls *)linked->m_linked)->FUN_0053f9f0(this);
                        }
                    }
                }
            }
            else
            {
                m_state = 1;
                if (input.flags & 1)
                    input.ui->Clear();
            }
            break;
        case 2:
            result = 0;
            if ((unsigned char)((RHPortraitUnk005d3880 *)this)->FUN_005d3880(input.point) && (input.flags & 8))
            {
                result = &Event();
                Event().next = 0;
                Event().widget = this;
                Event().value = 0;
                result->type = 3;
            }
            break;
        case 13:
            return FUN_005d33d0(input);
        default:
            result = 0;
        }
    }
    else
        result = 0;
    return result;
}

// Parked: The cached branch exchanges the event pointer and shared vtable registers.
// STUB: GAME 0x005d3290
RHPortraitBoxEvent *RHPortraitTextWidget::FUN_005d3290(unsigned value)
{
    *(unsigned *)((char *)this + 0xc8) = value;
    ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&m_renderer)->FUN_0060d690());
    *(void **)((char *)this + 0x78) = 0;
    *(void **)((char *)this + 0x74) = this;
    unsigned index = value & 1;
    SBUIInputFieldTextUnk *text = (SBUIInputFieldTextUnk *)&m_text;
    if (m_caretFlags[index] == text->FUN_0061e230() &&
        m_indices[index] == text->FUN_0061dd00() &&
        m_positions[index] == (unsigned short)text->FUN_0061df50())
    {
        RHPortraitTextWidgetDispatch *widget = (RHPortraitTextWidgetDispatch *)this;
        RHPortraitBoxEvent &event = *(RHPortraitBoxEvent *)((char *)this + 0x5c);
        event.m_type = widget->v13(widget->v9());
        return &event;
    }
    else
    {
        RHPortraitBoxEvent *event = (RHPortraitBoxEvent *)((char *)this + 0x5c);
        event->m_type = 1;
        m_caretFlags[index] = text->FUN_0061e230();
        m_indices[index] = text->FUN_0061dd00();
        m_positions[index] = (unsigned short)text->FUN_0061df50();
        return event;
    }
}

// FUNCTION: GAME 0x005d3360
void RHPortraitTextWidget::FUN_005d3360()
{
    unsigned id = ((RHPortraitTextWidgetDispatch *)this)->v9();
    if (id != 255)
    {
        *((char *)this + 0x104) = *((char *)this + 4);
        ((SBUIInputFieldUnk00621440 *)&m_renderer)->FUN_00621470(id);
    }
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x005d3390
void *RHPortraitTextWidgetBase::FUN_005d3390(unsigned flags)
{
    this->~RHPortraitTextWidgetBase();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// FUNCTION: GAME 0x005d33b0
void *RHPortraitTextWidget::FUN_005d33b0(unsigned flags)
{
    this->~RHPortraitTextWidget();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: Keyboard conversion bindings and text-event EH/register layout need alignment.
// STUB: GAME 0x005d33d0
RHPortraitWidgetEvent *RHPortraitTextWidget::FUN_005d33d0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *result = 0;
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    RHPortraitWidgetEvent &event = *(RHPortraitWidgetEvent *)((char *)this + 0x4c);
    SBUIInputFieldTextUnk &text = *(SBUIInputFieldTextUnk *)&m_text;
    SBUIInputFieldUnk00621440 &textCalls = *(SBUIInputFieldUnk00621440 *)&m_text;
    if (!(box.FUN_006083b0(input.point) &&
          ((RHGameWidgetRendererCalls *)&m_renderer)->FUN_0060d890(input.point.Unk005fc110(box.m_first))) &&
        (input.flags & 0x40))
    {
        if (m_linked)
            m_state = 2;
        else
            m_state = 0;
        result = &event;
        event.next = 0;
        event.widget = this;
        result->type = 9;
        event.value = 0;
        m_state = m_linked ? 2 : 0;
        text.FUN_0061e320(0);
        *(int *)((char *)this + 0xc0) = -1;
        *(int *)((char *)this + 0xc4) = -1;
        input.ui->Clear();
        return result;
    }
    unsigned short key = 0;
    int scanCode = 0;
    for (; key <= 255; ++key, ++scanCode)
    {
        int pressed = input.shortcuts->FUN_0060e240(key);
        char released = ((RHPortraitKeyboardCalls *)input.shortcuts)->FUN_0060e270(key);
        int state = ((int *)((char *)input.shortcuts + 0xa0c))[key];
        if (pressed == 1)
        {
            if (state == 0 || state == 2)
            {
                unsigned short characters[2] = {0, 0};
                unsigned converted = FUN_005fb1d0(scanCode & 0x7f);
                if (converted > 0)
                {
                    switch (converted)
                    {
                    case 37: m_text.FUN_0061e240(1); break;
                    case 39: m_text.FUN_0061e240(0); break;
                    case 36: m_text.FUN_0061e240(2); break;
                    case 35: m_text.FUN_0061e240(3); break;
                    case 8: text.FUN_0061e2b0(-1); break;
                    case 46: text.FUN_0061e2b0(text.FUN_0061dd30() + 1); break;
                    case 9:
                    case 13:
                    case 27:
                    case 38:
                    case 40:
                        continue;
                    default:
                        if (FUN_005fb0f0(scanCode, characters, (char *)input.shortcuts + 0x1610, 2) > 0)
                        {
                            if (!characters[0])
                                continue;
                            m_text.Insert(characters[0]);
                            *(int *)((char *)this + 0xc0) = -1;
                            *(int *)((char *)this + 0xc4) = -1;
                        }
                        else
                        {
                            // STRING: GAME 0x006b8dd8
                            const char *file = "P:\\Robin Hood\\SBLibNG/SBWidgetInputField.h";
                            // STRING: GAME 0x006b8e04
                            const char *message = "No conversion for the scan code %i\n";
                            SBAssert(false, file, 0x278, message, scanCode);
                            continue;
                        }
                        break;
                    }
                }
                else if (FUN_005fb0f0(scanCode, characters, (char *)input.shortcuts + 0x1610, 2) > 0)
                {
                    if (!characters[0])
                        continue;
                    m_text.Insert(characters[0]);
                    *(int *)((char *)this + 0xc0) = -1;
                    *(int *)((char *)this + 0xc4) = -1;
                }
                else
                {
                    SBAssert(false, "P:\\Robin Hood\\SBLibNG/SBWidgetInputField.h", 0x278,
                        "No conversion for the scan code %i\n", scanCode);
                    continue;
                }
                result = &event;
                event.next = 0;
                event.widget = this;
                event.value = 0;
                result->type = 10;
            }
        }
        else if (pressed == 0 && released == 1)
        {
            unsigned converted = FUN_005fb1d0(scanCode & 0x7f);
            if (converted == 27)
            {
                m_state = m_linked ? 2 : 0;
                textCalls.FUN_0061e4b0();
                text.FUN_0061e320(0);
                *(int *)((char *)this + 0xc0) = -1;
                *(int *)((char *)this + 0xc4) = -1;
                input.ui->Clear();
                result = &event;
                event.next = 0;
                result->type = 9;
                event.widget = this;
                event.value = 0;
            }
            else if (converted == 13 && textCalls.FUN_0061df60().size() != 0)
            {
                m_state = m_linked ? 2 : 0;
                text.FUN_0061e320(0);
                *(int *)((char *)this + 0xc0) = -1;
                *(int *)((char *)this + 0xc4) = -1;
                input.ui->Clear();
                RHPortraitWidgetEvent &secondary = *(RHPortraitWidgetEvent *)((char *)this + 0x15c);
                result = &event;
                event.next = &secondary;
                result->type = 9;
                event.widget = this;
                event.value = 0;
                secondary.type = 2;
                secondary.next = 0;
                secondary.widget = this;
                secondary.value = 0;
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x005d3880
int RHPortraitUnk005d3880::FUN_005d3880(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// FUNCTION: GAME 0x005d39a0
RHPortraitLinkedLifetime::RHPortraitLinkedLifetime() : m_linked(0)
{
    *(unsigned *)this = 0x0067a1ac;
    *(unsigned *)((char *)this + 0xdc) = 0x0067a190;
}

// FUNCTION: GAME 0x005d39d0
void *RHPortraitLinkedLifetime::FUN_005d39d0(unsigned flags)
{
    this->~RHPortraitLinkedLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d39f0
RHPortraitLinkedLifetime::~RHPortraitLinkedLifetime()
{
    *(unsigned *)this = 0x0067a1ac;
    *(unsigned *)((char *)this + 0xdc) = 0x0067a190;
}

// FUNCTION: GAME 0x005d3a10
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d3a10(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = FUN_005d4cb0(input);
    if (m_state == 9)
    {
        for (RHPortraitWidgetEvent *entry = event; entry; entry = entry->next)
        {
            if (entry->type == 2 && m_linked)
            {
                m_linked->FUN_005d3a80(this);
                break;
            }
        }
    }
    return event;
}

// FUNCTION: GAME 0x005d3a60
void RHPortraitUnk005d3880::FUN_005d3a60(const RHPortraitWidgetInput &input)
{
    FUN_005d4fe0(input);
    if (m_state == 6)
        m_state = 9;
}

// FUNCTION: GAME 0x005d3a80
void RHPortraitUnk005d3880::FUN_005d3a80(const void *stop)
{
    for (RHPortraitUnk005d3880 *widget = this; stop != widget; widget = widget->m_linked)
    {
        if (widget->m_state == 9)
        {
            widget->m_state = 6;
            widget->m_selected = 0;
        }
        if (widget->m_linked == 0)
            return;
    }
}

// FUNCTION: GAME 0x005d3ab0
void RHPortraitUnk005d3880::FUN_005d3ab0(RHPortraitUnk005d3880 *linked)
{
    m_linked = linked;
}

// FUNCTION: GAME 0x005d3ac0
RHPortraitWidgetEvent *RHPortraitUnk005d5100::FUN_005d3ac0()
{
    if (*((char *)this - 0xd8) && *(int *)((char *)this - 0x60) == 6)
    {
        RHPortraitWidgetEvent *event = RHPortraitUnk005d5100::FUN_005d5090();
        (*(RHPortraitUnk005d3880 **)((char *)this + 0x34))->FUN_005d3a80((char *)this - 0xdc);
        return event;
    }
    return 0;
}

// FUNCTION: GAME 0x005d3b00
bool RHPortraitUnk005d3880::FUN_005d3b00(char value)
{
    *((char *)this + 4) = value;
    return true;
}

// FUNCTION: GAME 0x005d3b10
void *RHPortraitUnk005d3880::FUN_005d3b10()
{
    return m_b8;
}

// FUNCTION: GAME 0x005d3b20
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d3b20(const void *)
{
    RHPortraitWidgetEvent *event = &m_event;
    if (event->type != 2 && event->type != 7)
        event->type = 2;
    else
        event->type = 7;
    m_event.value = m_selected == 1;
    m_event.next = 0;
    m_event.widget = this;
    return event;
}

// FUNCTION: GAME 0x005d3b60
int RHPortraitUnk005d3880::FUN_005d3b60(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// FUNCTION: GAME 0x005d3cb0
RHPortraitGroupLifetime::RHPortraitGroupLifetime() : RHPortraitAnimated(11)
{
    RHUnk00514e10 &map = m_map;
    RHPortraitMapLookup(map, 0) = 1;
    RHPortraitMapLookup(map, 16) = 1;
    RHPortraitMapLookup(map, 2) = 0;
}

// FUNCTION: GAME 0x005d3dc0
void *RHPortraitGroupLifetime::FUN_005d3dc0(unsigned flags)
{
    this->~RHPortraitGroupLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d3de0
RHPortraitGroupLifetime::~RHPortraitGroupLifetime()
{
}

// FUNCTION: GAME 0x005d3ef0
RHPortraitWidgetEvent *RHPortraitUnk005d3fe0::FUN_005d3ef0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event;
    switch (m_state)
    {
    case 0: event = FUN_005d4480(input); break;
    case 1: event = FUN_005d45a0(input); break;
    case 2: event = FUN_005d46e0(input); break;
    default: event = 0; break;
    }
    ((RHGameWidgetAnimatedCalls *)((char *)this + 0xb0))->FUN_005d5790(event, m_state, 0);
    return event;
}

// FUNCTION: GAME 0x005d3f50
inline RHPortraitGroupLifetimeBase::~RHPortraitGroupLifetimeBase()
{
    if (m_widgets)
        m_widgets->v0(3);
    void *allocation = m_events;
    operator delete(allocation);
}

// FUNCTION: GAME 0x005d3fe0
void RHPortraitUnk005d3fe0::FUN_005d3fe0(unsigned value)
{
    for (unsigned i = 0; i < m_count; ++i)
        m_widgets[i].v1(value);
}

// FUNCTION: GAME 0x005d4020
void RHPortraitUnk005d3fe0::FUN_005d4020()
{
    for (unsigned i = 0; i < m_count; ++i)
        m_widgets[i].v2();
}

// FUNCTION: GAME 0x005d4060
void RHPortraitUnk005d3fe0::FUN_005d4060()
{
    for (unsigned i = 0; i < m_count; ++i)
    {
        if (!m_events[i] || m_events[i]->m_type != 0)
            m_widgets[i].v3();
    }
}

// FUNCTION: GAME 0x005d40b0
void RHPortraitUnk005d3fe0::FUN_005d40b0()
{
    for (unsigned i = 0; i < m_count; ++i)
        m_widgets[i].v4();
}

// FUNCTION: GAME 0x005d40f0
RHPortraitBoxEvent *RHPortraitUnk005d3fe0::FUN_005d40f0(unsigned long frame)
{
    bool produced = false;
    int type = 1;
    SBGeoBoundingBox2D bounds;
    for (unsigned i = 0; i < m_count; ++i)
    {
        m_events[i] = m_widgets[i].v5(frame);
        if (m_events[i])
        {
            produced = true;
            if (type <= m_events[i]->m_type)
                type = m_events[i]->m_type;
        }
    }
    if (produced == 1)
    {
        *(int *)((char *)this + 0x90) = type;
        *(void **)((char *)this + 0xac) = 0;
        *(void **)((char *)this + 0xa8) = this;
        ((RHMobileUnk00607da0 *)((char *)this + 0x94))->FUN_00607da0((const RHMobileUnk00607da0 &)RHMapBox(0, 0, 0, 0));
        return (RHPortraitBoxEvent *)((char *)this + 0x90);
    }
    return 0;
}

// FUNCTION: GAME 0x005d4240
RHPortraitWidgetEvent *RHPortraitUnk005d3fe0::FUN_005d4240(const RHPortraitWidgetInput &input)
{
    switch (m_state)
    {
    case 0: return FUN_005d4480(input);
    case 1: return FUN_005d45a0(input);
    case 2: return FUN_005d46e0(input);
    }
    return 0;
}

// FUNCTION: GAME 0x005d4280
void RHPortraitUnk005d3fe0::FUN_005d4280(const SBGeoPoint2D &point)
{
    SBGeoVector2D displacement = point.Unk005fc110(m_box.m_first);
    for (unsigned i = 0; i < m_count; ++i)
    {
        SBGeoPoint2D position(*(SBGeoPoint2D *)((char *)&m_widgets[i] + 0x30));
        position.FUN_005fc1e0(displacement);
        m_widgets[i].v8(position);
    }
    ((RHMobileUnk006091b0 *)&m_box)->FUN_006091b0(displacement);
}

// FUNCTION: GAME 0x005d4360
void RHPortraitUnk005d3fe0::FUN_005d4360(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D box(m_box);
    SBGeoVector2D displacement = point.Unk005fc110(m_box.m_first);
    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(displacement);
    ((RHPortraitWidgetStrategy *)this)->v7(box);
}

// FUNCTION: GAME 0x005d4410
void *RHPortraitGroupLifetimeBase::FUN_005d4410(unsigned flags)
{
    this->~RHPortraitGroupLifetimeBase();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d4430
RHPortraitBoxEvent::~RHPortraitBoxEvent()
{
}

// FUNCTION: GAME 0x005d4480
RHPortraitWidgetEvent *RHPortraitUnk005d3fe0::FUN_005d4480(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    if (m_box.FUN_00608400(input.point) && !(input.flags & 0x40))
    {
        RHPortraitWidgetInput local;
        memcpy(&local, &input, sizeof(local));
        local.flags &= 0xff7d;
        for (unsigned i = 0; i < m_count; ++i)
            m_widgets[i].v6(local);
        m_state = 1;
        if (m_count)
        {
            SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)m_widgets + 0x30);
            unsigned width = (unsigned)(box.m_second.m_x - box.m_first.m_x);
            float left = m_box.m_first.m_x;
            m_index = (int)((input.point.m_x - left) / width);
        }
        BeginEvent().type = 0;
        m_event.value = 0;
        m_event.next = 0;
        event = &m_event;
    }
    return event;
}

// FUNCTION: GAME 0x005d45a0
RHPortraitWidgetEvent *RHPortraitUnk005d3fe0::FUN_005d45a0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    unsigned previous = m_index;
    RHPortraitWidgetInput local;
    if (m_box.FUN_00608400(input.point))
    {
        if (input.flags & 0x40)
        {
            m_state = 2;
            void *ui = input.ui;
            *(void **)((char *)ui + 0x17f0) = this;
        }
    }
    else
        m_state = 0;
    memcpy(&local, &input, sizeof(local));
    local.flags &= 0xff7d;
    for (unsigned i = 0; i < m_count; ++i)
        m_widgets[i].v6(local);
    if (m_count)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)m_widgets + 0x30);
        unsigned width = (unsigned)(box.m_second.m_x - box.m_first.m_x);
        float left = m_box.m_first.m_x;
        m_index = (int)((input.point.m_x - left) / width);
    }
    if (previous != m_index)
    {
        RHPortraitWidgetEvent *result = &m_event;
        m_event.widget = this;
        m_event.value = 0;
        result->type = 16;
        m_event.next = 0;
        event = result;
    }
    return event;
}

// FUNCTION: GAME 0x005d46e0
RHPortraitWidgetEvent *RHPortraitUnk005d3fe0::FUN_005d46e0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetInput local;
    RHPortraitWidgetEvent *event = 0;
    if (input.flags & 1)
    {
        if (m_box.FUN_00608400(input.point))
            m_state = 1;
        else
            m_state = 0;
        input.ui->Clear();
        RHPortraitWidgetEvent *result = &m_event;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        result->type = 2;
        event = result;
    }
    memcpy(&local, &input, sizeof(local));
    local.flags &= 0xff7d;
    if (m_box.m_second.m_x <= input.point.m_x)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)&m_widgets[m_count - 1] + 0x30);
        float right = m_box.m_second.m_x;
        float position = right - (box.m_second.m_x - box.m_first.m_x) * 0.5f;
        local.point.m_x = position;
    }
    else if (m_box.m_first.m_x >= input.point.m_x)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)m_widgets + 0x30);
        float left = m_box.m_first.m_x;
        float position = left + (box.m_second.m_x - box.m_first.m_x) * 0.5f;
        local.point.m_x = position;
    }
    else
        local.point.m_x = input.point.m_x;
    if (m_box.m_second.m_y <= input.point.m_y)
    {
        float bottom = m_box.m_second.m_y;
        float position = bottom - (*(volatile float *)&m_box.m_second.m_y - m_box.m_first.m_y) * 0.5f;
        local.point.m_y = position;
    }
    else if (m_box.m_first.m_y >= input.point.m_y)
    {
        float top = *(volatile float *)&m_box.m_first.m_y;
        float position = top + (m_box.m_second.m_y - m_box.m_first.m_y) * 0.5f;
        local.point.m_y = position;
    }
    else
        local.point.m_y = input.point.m_y;
    for (unsigned i = 0; i < m_count; ++i)
        m_widgets[i].v6(local);
    unsigned previous = m_index;
    if (m_count)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)m_widgets + 0x30);
        unsigned width = (unsigned)(box.m_second.m_x - box.m_first.m_x);
        float left = m_box.m_first.m_x;
        m_index = (int)((local.point.m_x - left) / width);
    }
    if (previous != m_index)
    {
        RHPortraitWidgetEvent *result = &m_event;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        result->type = 16;
        event = result;
    }
    return event;
}

// FUNCTION: GAME 0x005d49b0
RHPortraitRadioLifetime::RHPortraitRadioLifetime() : RHPortraitAnimated(2), m_10c(0), m_10d(0)
{
    RHUnk00514e10 &map = m_map;
    RHPortraitMapLookup(map, 0) = 1;
    RHPortraitMapLookup(map, 2) = 0;
}

// FUNCTION: GAME 0x005d4ab0
void *RHPortraitRadioLifetime::FUN_005d4ab0(unsigned flags)
{
    this->~RHPortraitRadioLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005d4ad0
RHPortraitRadioLifetime::~RHPortraitRadioLifetime()
{
}

// Parked: The constructed box receiver and resource identifier exchange registers.
// STUB: GAME 0x005d4bb0
bool RHPortraitUnk005d3880::FUN_005d4bb0(int mode, const std::wstring &text, const SBGeoPoint2D &origin, int resource)
{
    {
        const SBGeoBoundingBox2D &local = SBGeoBoundingBox2D(origin, origin);
        const SBGeoBoundingBox2D *box = &local;
        if (resource == 0)
            resource = -1;
        ((RHGameWidgetLifetimeBase *)this)->Create(text, *box, 0);
        RHPortraitRendererDispatch *renderer = (RHPortraitRendererDispatch *)((char *)this + 0x80);
        renderer->v3(*box);
        ((SBUIUnk0060d530 *)renderer)->FUN_0060d550(resource);
        *(int *)((char *)this + 0xa4) = 0;
        RHPortraitAssignWideText((char *)this + 0xa8, text);
        SBGeoBoundingBox2D &bounds = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
        if (bounds.m_second.m_x - bounds.m_first.m_x == 0.0f)
            ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)renderer)->FUN_0060d690());
    }
    ((RHPortraitRenderer005cadc0 *)((char *)this + 0x80))->FUN_005cae10(mode);
    return true;
}

// FUNCTION: GAME 0x005d4cb0
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4cb0(const RHPortraitWidgetInput &input)
{
    RHPortraitButtonDispatch *widget = (RHPortraitButtonDispatch *)this;
    RHPortraitWidgetEvent *event;
    switch (m_state)
    {
    case 5: event = widget->v23(input); break;
    case 7: event = widget->v24(input); break;
    case 6: event = widget->v22(input); break;
    case 9: event = widget->v25(input); break;
    case 8: event = widget->v26(input); break;
    case 10: event = widget->v27(input); break;
    default: event = 0; break;
    }
    ((RHGameWidgetAnimatedCalls *)((char *)this + 0xe0))->FUN_005d5790(event, m_state, 0);
    return event;
}

// FUNCTION: GAME 0x005d4d60
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4d60(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    if (*((char *)this + 4) && (char)FUN_005d4db0(*(SBGeoPoint2D *)&input) && !(input.flags & 0x40))
    {
        event = &m_event;
        m_event.value = 0;
        m_event.next = 0;
        m_state = 5;
        event->type = 0;
        m_event.widget = this;
    }
    return event;
}

// FUNCTION: GAME 0x005d4db0
int RHPortraitUnk005d3880::FUN_005d4db0(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// Parked: Retaining the UI receiver exchanges this/input registers; direct access reloads the receiver.
// STUB: GAME 0x005d4e50
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4e50(const RHPortraitWidgetInput &input)
{
    if ((char)FUN_005d4db0(*(SBGeoPoint2D *)&input))
    {
        if (input.flags & 0x40)
        {
            m_state = 7;
            input.ui->m_selected = this;
        }
    }
    else
    {
        if (!(input.flags & 0x40))
        {
            m_state = 6;
            m_selected = 0;
        }
        if (input.flags & 9)
        {
            input.ui->m_selected = 0;
            input.ui->m_captured = 0;
        }
    }
    return 0;
}

// FUNCTION: GAME 0x005d4ec0
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4ec0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    if (!(char)FUN_005d4db0(*(SBGeoPoint2D *)&input))
    {
        if (input.flags & 0x40)
        {
            m_state = 5;
            m_selected = 0;
        }
    }
    else if ((input.flags & 1) || (input.flags & 8))
    {
        m_state = 9;
        m_selected = 1;
        void *ui = input.ui;
        *(void **)((char *)ui + 0x17f0) = 0;
        *(void **)((char *)ui + 0x17f4) = 0;
        event = &m_event;
        m_event.widget = this;
        m_event.value = 0;
        m_event.next = 0;
        event->type = 2;
    }
    return event;
}

// FUNCTION: GAME 0x005d4f30
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4f30(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    if (*((char *)this + 4) && (char)FUN_005d4db0(*(SBGeoPoint2D *)&input) && !(input.flags & 0x40))
    {
        event = &m_event;
        m_event.value = 0;
        m_event.next = 0;
        m_state = 8;
        event->type = 0;
        m_event.widget = this;
    }
    return event;
}

// Parked: Input-flag scheduling and the UI receiver register remain different.
// STUB: GAME 0x005d4f80
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4f80(const RHPortraitWidgetInput &input)
{
    if (!(char)FUN_005d4db0(*(SBGeoPoint2D *)&input))
    {
        unsigned char flags = (unsigned char)input.flags;
        if (!(flags & 0x40))
        {
            m_state = 9;
            m_selected = 1;
        }
        if (input.flags & 9)
        {
            input.ui->Clear();
        }
    }
    else if (input.flags & 0x40)
    {
        m_state = 10;
        input.ui->m_selected = this;
    }
    return 0;
}

// FUNCTION: GAME 0x005d4fe0
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d4fe0(const RHPortraitWidgetInput &input)
{
    RHPortraitWidgetEvent *event = 0;
    if (!(char)FUN_005d4db0(*(SBGeoPoint2D *)&input))
    {
        if (input.flags & 0x40)
            m_state = 8;
    }
    else
    {
        unsigned short flags = input.flags;
        unsigned released = flags & 1;
        if ((unsigned short)released || (flags & 8))
        {
            m_state = (unsigned short)released ? 6 : 9;
            m_selected = m_state == 9;
            input.ui->Clear();
            event = &m_event;
            m_event.widget = this;
            m_event.value = 0;
            m_event.next = 0;
            event->type = 7;
            if (input.flags & 8)
            {
                RHPortraitWidgetEvent *next = (RHPortraitWidgetEvent *)((char *)this + 0xfc);
                *(void **)((char *)this + 0x100) = this;
                m_event.next = next;
                *(int *)((char *)this + 0x104) = 0;
                *(void **)((char *)this + 0x108) = 0;
                next->type = 3;
            }
        }
    }
    return event;
}

// FUNCTION: GAME 0x005d5090
RHPortraitWidgetEvent *RHPortraitUnk005d5100::FUN_005d5090()
{
    if (*((char *)this - 0xd8))
    {
        RHPortraitWidgetEvent *event;
        if (*(int *)((char *)this - 0x60) == 9)
        {
            event = (RHPortraitWidgetEvent *)((char *)this - 0x90);
            *((char *)this - 4) = 0;
            *(int *)((char *)this - 0x60) = 6;
            event->type = 7;
        }
        else
        {
            *(volatile char *)((char *)this - 4) = 1;
            *(int *)((char *)this - 0x60) = 9;
            event = (RHPortraitWidgetEvent *)((char *)this - 0x90);
            event->type = 2;
        }
        *(void *volatile *)((char *)this - 0x8c) = (char *)this - 0xdc;
        *(int *)((char *)this - 0x88) = 0;
        *(void **)((char *)this - 0x84) = 0;
        return event;
    }
    return 0;
}

// FUNCTION: GAME 0x005d5100
int RHPortraitUnk005d5100::FUN_005d5100(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this - 0xac);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this - 0x5c))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        return true;
    return false;
}

// FUNCTION: GAME 0x005d51a0
void *RHPortraitUnk005d5100::FUN_005d51a0()
{
    return (char *)this - 0xdc;
}

// FUNCTION: GAME 0x005d51c0
RHPortraitWidgetEvent *RHPortraitUnk005d5100::FUN_005d51c0(char value)
{
    *(volatile char *)((char *)this + 0x30) = value;
    char enabled = *((char *)this - 0xd8);
    if (enabled && value == 1)
    {
        *(void **)((char *)this - 0x8c) = (char *)this - 0xdc;
        RHPortraitWidgetEvent *event = (RHPortraitWidgetEvent *)((char *)this - 0x90);
        event->type = 7;
        *(int *)((char *)this - 0x88) = 0;
        *(void **)((char *)this - 0x84) = 0;
        return event;
    }
    return 0;
}

// FUNCTION: GAME 0x005d5210
RHPortraitWidgetEvent *RHPortraitUnk005d5100::FUN_005d5210(char value)
{
    if (*((char *)this - 0xd8))
        *((char *)this + 0x31) = value;
    return 0;
}

// FUNCTION: GAME 0x005d5230
int RHPortraitUnk005d3880::FUN_005d5230()
{
    if (*((char *)this + 0x10d) == 1)
        return 3;
    if (*((char *)this + 0x10c) == 1)
        return 2;
    if (!*((char *)this + 4))
        return 0;
    int result;
    switch (m_state)
    {
    case 5: if (*((char *)this + 5) == 1) return 2; result = 1; break;
    case 6:
    case 7: result = 1; break;
    case 8: if (*((char *)this + 5) == 1) return 4; result = 3; break;
    case 9:
    case 10: result = 3; break;
    }
    if ((result == 1 || result == 3) && *((char *)this + 6) != 1)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x005d52d0
int RHPortraitUnk005d3880::FUN_005d52d0()
{
    if (!*((char *)this + 4))
        return 0;
    int result;
    switch (m_state)
    {
    case 5: if (*((char *)this + 5) == 1) return 2; result = 1; break;
    case 6:
    case 7: result = 1; break;
    case 8: if (*((char *)this + 5) == 1) return 4; result = 3; break;
    case 9:
    case 10: result = 3; break;
    }
    if ((result == 1 || result == 3) && *((char *)this + 6) != 1)
        result = 255;
    return result;
}

// SYNTHETIC: GAME 0x005d5350
// ??1RHPortraitLifetime005d5350@@QAE@XZ

// FUNCTION: GAME 0x005d53b0
RHPortraitWidgetEvent *RHPortraitUnk005d3880::FUN_005d53b0(const RHPortraitWidgetInput &input)
{
    RHPortraitButtonDispatch *widget = (RHPortraitButtonDispatch *)this;
    if (!*((char *)this + 4))
    {
        if (*((char *)this + 8) && (char)widget->v19(input) &&
            ((SBUIUnk0060dae0 *)((char *)this + 0x80))->FUN_0060db80(0))
        {
            m_event.next = 0;
            RHPortraitWidgetEvent *event = &m_event;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 18;
            return event;
        }
        return 0;
    }
    if (*(unsigned short *)((char *)this + 0x0a))
    {
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 1)
        {
            if (!m_selected)
                m_state = 10;
            else
                m_state = 7;
            return widget->v17(input);
        }
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2 ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3)
        {
            if (!m_selected)
            {
                m_selected = 1;
                m_state = 9;
            }
            else
            {
                m_selected = 0;
                m_state = 6;
            }
            return widget->v16(input);
        }
    }
    if ((char)widget->v19(input))
    {
        unsigned short flags = input.flags;
        if (flags & 0x40)
        {
            if (!m_selected)
                m_state = 7;
            else
                m_state = 10;
            return widget->v17(input);
        }
        if (flags & 8)
        {
            RHPortraitWidgetEvent *event = &m_event;
            m_event.value = m_selected == 1;
            m_event.next = 0;
            m_event.widget = this;
            event->type = 7;
            return event;
        }
        if (flags & 1)
        {
            if (!m_selected)
            {
                m_selected = 1;
                m_state = 9;
            }
            else
            {
                m_selected = 0;
                m_state = 6;
            }
            return widget->v16(input);
        }
        if (!(flags & 0x12))
        {
            if (*((char *)this + 5) == 1)
            {
                if (!m_selected)
                    m_state = 5;
                else
                    m_state = 8;
                return widget->v15(input);
            }
        }
        else
            return widget->v18(input);
    }
    if (m_state == 5 || m_state == 7)
        m_state = 6;
    if (m_state == 8 || m_state == 10)
        m_state = 9;
    return 0;
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x005d55f0
void *RHPortraitLifetime005d5350::FUN_005d55f0(unsigned flags)
{
    this->~RHPortraitLifetime005d5350();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// FUNCTION: GAME 0x005d56c0
RHPortraitAnimated::RHPortraitAnimated(int id) : m_id(id)
{
    unsigned char allocator;
    unsigned char comparator;
    unsigned char *bytes = m_map.m_00;
    bytes[0] = allocator;
    m_map.m_00[1] = comparator;
    m_map.m_multi = false;
    {
        RHUnk00641782 guard;
        if (!g_unk0x006c0b48)
        {
            RHUnk00514e10::Node *node = (RHUnk00514e10::Node *)operator new(sizeof(RHUnk00514e10::Node));
            node->parent = 0;
            node->color = 1;
            g_unk0x006c0b48 = node;
            node->left = 0;
            g_unk0x006c0b48->right = 0;
        }
        ++g_unk0x006c0b4c;
        RHUnk00514e10::Node *parent = g_unk0x006c0b48;
        RHUnk00514e10::Node *node = (RHUnk00514e10::Node *)operator new(sizeof(RHUnk00514e10::Node));
        node->parent = parent;
        node->color = 0;
        m_map.m_head = node;
        m_map.m_size = 0;
        node->left = node;
        m_map.m_head->right = m_map.m_head;
    }
    m_state = 0;
    m_handled = 0;
}

#include "../engine/SBResourceUnkKeyTree.h"
#include "../sound/RHSoundCore.h"

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

inline SBResourceUnkKeyIterator RHPortraitFind(RHUnk00514e10 &map, const RHPortraitWidgetEvent &key)
{
    SBResourceUnkKeyIterator found((SBResourceUnkKeyNode *)((RHPortraitTree &)map).FUN_005d5840(key));
    SBResourceUnkTreeEnd &view = (SBResourceUnkTreeEnd &)map;
    return (found.m_node != view.FUN_00617690().m_node && key.type >= (int)found.m_node->m_key
        ? found : view.FUN_00617690());
}

// Parked: the event and found-node registers are swapped (esi/ebp).
// STUB: GAME 0x005d5790
void RHGameWidgetAnimatedCalls::FUN_005d5790(void *event, int state, bool option)
{
    RHPortraitAnimated *animated = (RHPortraitAnimated *)this;
    if (animated->m_state != state || option == true) {
        animated->m_state = state;
        animated->m_handled = 0;
    }
    if (animated->m_handled)
        return;
    for (RHPortraitWidgetEvent *current = (RHPortraitWidgetEvent *)event; current; current = current->next) {
        SBResourceUnkKeyIterator position = RHPortraitFind(animated->m_map, *current);
        if (position.m_node != (SBResourceUnkKeyNode *)animated->m_map.m_head) {
            animated->m_handled = 1;
            ((RHSound *)g_unk0x006c1070)->FUN_005a9170((animated->m_id << 16) + ((RHUnk00514e10::Node *)position.m_node)->value.second);
            return;
        }
    }
}

// FUNCTION: GAME 0x005d5840
RHUnk00514e10::Node *RHPortraitTree::FUN_005d5840(const RHPortraitWidgetEvent &event)
{
    RHUnk00641782 guard;
    RHUnk00514e10::Node *node = m_head->parent;
    RHUnk00514e10::Node *result = m_head;
    while (node != g_unk0x006c0b48)
    {
        if (node->value.first < event.type)
            node = node->right;
        else
        {
            result = node;
            node = node->left;
        }
    }
    return result;
}

// FUNCTION: GAME 0x005d5940
void RHPortraitUnk005d5950::FUN_005d5940()
{
    ((RHGameRenderer005cb220 *)((char *)this + 0x80))->FUN_005cb2a0();
}

// FUNCTION: GAME 0x005d5950
void RHPortraitUnk005d5950::FUN_005d5950(int value)
{
    ((RHGameRenderer005cb220 *)((char *)this + 0x80))->FUN_005cb2b0(value);
}

// Parked: Subobject constructor inlining and temporary-string EH coloring differ.
// STUB: GAME 0x005d5a20
RHPortraitFullLifetime::RHPortraitFullLifetime(unsigned short index, RHPortraitActorCalls *actor)
    : m_actor(actor),
      m_portraitResource((RHPortraitResourceInterface *)FUN_005024f0(std::string(RHPortraitResourceName()))->FUN_00502270()),
      m_backgroundResource((RHPortraitResourceInterface *)FUN_005024f0(std::string(RHPortraitBackgroundName()))->FUN_00502270()),
      m_resources(false)
{
    *((char *)this + 0xca6) = 0;
    *((char *)this + 0xca7) = 0;
    *((char *)this + 0xca8) = 0;
    *((char *)this + 0xca9) = 0;
    m_caa = 0;
    m_cac = 0;
    *(unsigned *)this = 0x0067a348;
    unsigned short *counter = (unsigned short *)((char *)this + 0xc9e);
    for (int remaining = 3; remaining; --remaining, ++counter)
    {
        counter[-3] = 0;
        counter[0] = 0;
    }
    FUN_0061a800(&m_second);
    FUN_0061a800(&m_first);
    FUN_0061a800(&m_action);
    FUN_0061a800(&m_buttonFirst);
    FUN_0061a800(&m_buttonSecond);
    FUN_0061a800(&m_buttonThird);
    FUN_0061aa30(&m_buttonFirst);
    FUN_0061aa30(&m_buttonSecond);
    FUN_0061aa30(&m_buttonThird);
    m_buttonFirst.m_value = (int)&m_buttonSecond;
    m_buttonSecond.m_value = (int)&m_buttonThird;
    m_buttonThird.m_value = (int)&m_buttonFirst;
    FUN_0061a800(&m_quick[0]);
    FUN_0061a800(&m_quick[1]);
    FUN_0061a800(&m_quick[2]);
    FUN_0061a800(&m_bitmapFirst);
    FUN_0061a800(&m_customFirst);
    FUN_0061a800(&m_bitmapSecond);
    ((RHUnk005d92c0Sub *)&m_bitmapFirst)->v21(0);
    ((RHUnk005d92c0Sub *)&m_customFirst)->v21(0);
    ((RHUnk005d92c0Sub *)&m_bitmapSecond)->v21(0);
    FUN_0061aa30(&m_bitmapFirst);
    FUN_0061aa30(&m_customFirst);
    ((RHUnk005d92c0Sub *)&m_quick[0])->v21(0);
    ((RHUnk005d92c0Sub *)&m_quick[1])->v21(0);
    ((RHUnk005d92c0Sub *)&m_quick[2])->v21(0);
    {
        std::wstring text = FUN_005e23d0(0x11e);
        *((char *)&m_quick[0] + 8) = 1;
        RHPortraitAssignWideText((char *)&m_quick[0] + 0x20, text);
    }
    {
        std::wstring text = FUN_005e23d0(0x11e);
        *((char *)&m_quick[1] + 8) = 1;
        RHPortraitAssignWideText((char *)&m_quick[1] + 0x20, text);
    }
    {
        std::wstring text = FUN_005e23d0(0x11e);
        *((char *)&m_quick[2] + 8) = 1;
        RHPortraitAssignWideText((char *)&m_quick[2] + 0x20, text);
    }
    m_e50[0] = 0;
    m_e50[1] = 0;
    m_e50[2] = 0;
    m_portraitResource->v5(m_resources, false);
    if (m_backgroundResource)
        m_backgroundResource->v5(m_resources, false);
    {
        std::wstring text(RHPortraitSwordName());
        RHMapBox box(0, 0, 0, 0);
        ((RHPortraitSetupDispatch *)&m_customSecond)->v12(text, *(SBGeoBoundingBox2D *)&box, false, actor->FUN_00492730());
    }
    ((RHPortraitSetupDispatch *)&m_customSecond)->v1(0);
    ((RHPortraitCtorCalls *)this)->FUN_005d6940(index);
    *(void **)((char *)this + 0x94) = this;
    *(int *)((char *)this + 0x98) = 0;
    *(int *)((char *)this + 0x90) = 11;
    *(void **)((char *)this + 0x9c) = 0;
}

// FUNCTION: GAME 0x005d61e0
void *RHPortraitFullLifetime::FUN_005d61e0(unsigned flags)
{
    this->~RHPortraitFullLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x005d6200
// ??1RHPortraitLifetime005d6200@@QAE@XZ

// SYNTHETIC: GAME 0x005d6260
// ??1RHPortraitLifetime005d6260@@QAE@XZ

// SYNTHETIC: GAME 0x005d62c0
// ??1RHPortraitLifetime005d62c0@@QAE@XZ

// SYNTHETIC: GAME 0x005d6320
// ??1RHPortraitLifetime005d6320@@QAE@XZ

// SYNTHETIC: GAME 0x005d63b0
// ??1RHPortraitLifetime005d63b0@@QAE@XZ

// Parked: Shared bitmap destructors remain out of line and alter EH cleanup states.
// STUB: GAME 0x005d6410
RHPortraitFullLifetime::~RHPortraitFullLifetime()
{
    *(volatile unsigned *)this = 0x0067a348;
    m_portraitResource->v6();
    if (m_portraitResource)
        m_portraitResource->v2(1);
    if (m_backgroundResource)
    {
        m_backgroundResource->v6();
        if (m_backgroundResource)
            m_backgroundResource->v2(1);
    }
}

void EmitPortraitWidgetBatch99(RHPortraitUnk005d3880 *widget, RHPortraitUnk005d3fe0 *group, RHPortraitUnk005d5100 *strategy, RHPortraitTree *tree, RHPortraitAnimated *animated, RHPortraitUnk005d5950 *rendererWidget, const SBGeoPoint2D &point, const RHPortraitWidgetInput &input)
{
    widget->FUN_005d3880(point);
    widget->FUN_005d3a10(input);
    widget->FUN_005d3a60(input);
    widget->FUN_005d3a80(widget);
    widget->FUN_005d3ab0(widget);
    widget->FUN_005d3b00(1);
    widget->FUN_005d3b10();
    widget->FUN_005d3b20(&input);
    widget->FUN_005d3b60(point);
    group->FUN_005d3fe0(0);
    group->FUN_005d4020();
    group->FUN_005d4060();
    group->FUN_005d40b0();
    group->FUN_005d40f0(0);
    group->FUN_005d3ef0(input);
    group->FUN_005d4240(input);
    group->FUN_005d4280(point);
    group->FUN_005d4360(point);
    ((RHPortraitBoxEvent *)((char *)group + 0x90))->~RHPortraitBoxEvent();
    group->FUN_005d4480(input);
    group->FUN_005d45a0(input);
    group->FUN_005d46e0(input);
    widget->FUN_005d4cb0(input);
    widget->FUN_005d4bb0(0, *(std::wstring *)widget, point, -1);
    widget->FUN_005d4db0(point);
    widget->FUN_005d4d60(input);
    widget->FUN_005d4e50(input);
    widget->FUN_005d4ec0(input);
    widget->FUN_005d4f30(input);
    widget->FUN_005d4f80(input);
    widget->FUN_005d4fe0(input);
    strategy->FUN_005d3ac0();
    strategy->FUN_005d5090();
    strategy->FUN_005d5100(point);
    strategy->FUN_005d51a0();
    strategy->FUN_005d51c0(0);
    strategy->FUN_005d5210(0);
    widget->FUN_005d5230();
    widget->FUN_005d52d0();
    widget->FUN_005d53b0(input);
    tree->FUN_005d5840(widget->m_event);
    animated->RHPortraitAnimated::RHPortraitAnimated(2);
    rendererWidget->FUN_005d5940();
    rendererWidget->FUN_005d5950(0);
    ((RHPortraitLinkedLifetime *)widget)->RHPortraitLinkedLifetime::RHPortraitLinkedLifetime();
    ((RHPortraitLinkedLifetime *)widget)->FUN_005d39d0(0);
    ((RHPortraitRadioLifetime *)widget)->FUN_005d4ab0(0);
    ((RHPortraitGroupLifetime *)group)->RHPortraitGroupLifetime::RHPortraitGroupLifetime();
    ((RHPortraitGroupLifetime *)group)->FUN_005d3dc0(0);
    ((RHPortraitGroupLifetimeBase *)group)->FUN_005d4410(0);
    ((RHPortraitLifetime005d5350 *)widget)->FUN_005d55f0(0);
    ((RHPortraitLifetime005d6200 *)widget)->~RHPortraitLifetime005d6200();
    ((RHPortraitLifetime005d6260 *)widget)->~RHPortraitLifetime005d6260();
    ((RHPortraitLifetime005d62c0 *)widget)->~RHPortraitLifetime005d62c0();
    ((RHPortraitLifetime005d6320 *)widget)->~RHPortraitLifetime005d6320();
    ((RHPortraitLifetime005d63b0 *)widget)->~RHPortraitLifetime005d63b0();
    ((RHPortraitFullLifetime *)widget)->RHPortraitFullLifetime::RHPortraitFullLifetime(0, (RHPortraitActorCalls *)group);
    ((RHPortraitFullLifetime *)widget)->FUN_005d61e0(0);
}

class RHPortraitBitmapWidget
{
public:
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual void Unk20();
    virtual void Unk24();
    virtual void Unk28();
    virtual void Unk2c();
    virtual bool Create(const std::wstring &text, const RHMapBox &box, unsigned long flags, long id);
    void SetScrollFirst(int value)
    {
        *(int *)((char *)this + 0xd4) = value;
    }
    void SetScrollSecond(int value)
    {
        *(int *)((char *)this + 0xd8) = value;
    }
    void SetQuickActionFirst(int value)
    {
        *(int *)((char *)this + 0xdc) = value;
    }
    void SetQuickActionSecond(int value)
    {
        *(int *)((char *)this + 0xe0) = value;
    }
    void SetQuickActionThird(int value)
    {
        *(int *)((char *)this + 0xe8) = value;
    }
    void SetQuickActionFourth(int value)
    {
        *(int *)((char *)this + 0xe4) = value;
    }
};

// FUNCTION: GAME 0x005cf390
bool RHPortraitBitmapWidget::Create(const std::wstring &text, const RHMapBox &box, unsigned long flags, long id)
{
    long resource = id;
    if (resource == 0)
        resource = -1;
    ((RHGameWidgetLifetimeBase *)this)->Create(text, box, flags);
    ((RHPortraitRenderer0060d470 *)((char *)this + 0x80))->FUN_0060d6a0(box);
    RHPortraitRenderer0060d470 &renderer = *(RHPortraitRenderer0060d470 *)((char *)this + 0x80);
    ((SBUIUnk0060d530 *)&renderer)->FUN_0060d550(resource);
    *(unsigned long *)((char *)this + 0xa4) = flags;
    ((RHPortraitRenderer0060d470 *)((char *)this + 0x80))->AssignName(text);
    SBGeoBoundingBox2D &bounds = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (bounds.Width() == 0.0f)
        ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(*(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)&renderer)->FUN_0060d690());
    return true;
}

void EmitRHPortraitBitmapCreate(RHPortraitBitmapWidget &widget, const std::wstring &text, const RHMapBox &box)
{
    widget.RHPortraitBitmapWidget::Create(text, box, 0, 0);
}

inline void RHWidgetPortrait::SetScrollState(long value)
{
    m_174 = m_178 = value;
}

// FUNCTION: GAME 0x005d75c0
bool RHWidgetPortrait::FUN_005d75c0(long first, long second, long third)
{
    ((RHPortraitBitmapWidget *)((char *)this + 0xa0))->Create(g_unk0x006c0b50, *(const RHMapBox *)((char *)this + 0xd68), 0, first);
    SetScrollState(second);
    ((RHPortraitBitmapWidget *)((char *)this + 0x18c))->Create(g_unk0x006c0b50, *(const RHMapBox *)((char *)this + 0xd7c), 0, third);
    return true;
}

// FUNCTION: GAME 0x005d7730
bool RHWidgetPortrait::FUN_005d7730(long id)
{
    ((RHPortraitBitmapWidget *)((char *)this + 0x268))->Create(g_unk0x006c0b50, *(const RHMapBox *)((char *)this + 0xd90), 0, id);
    return true;
}

// FUNCTION: GAME 0x005d7810
bool RHWidgetPortrait::FUN_005d7810(unsigned int index, long id, void *value, int first, int second, int third)
{
    RHPortraitBitmapWidget *widget;
    unsigned char box;
    switch (index) {
    case 0:
        box = 6;
        widget = (RHPortraitBitmapWidget *)((char *)this + 0x97c);
        break;
    case 1:
        box = 7;
        widget = (RHPortraitBitmapWidget *)((char *)this + 0xa80);
        break;
    case 2:
        box = 8;
        widget = (RHPortraitBitmapWidget *)((char *)this + 0xb84);
        break;
    }
    *(void **)((char *)this + index * 4 + 0xc88) = value;
    *(char *)((char *)this + index + 0xc94) = 0;
    widget->Create(g_unk0x006c0b50, *(const RHMapBox *)((char *)this + 0xcb4 + box * 20), 0, id);
    widget->SetQuickActionSecond(second);
    widget->SetQuickActionThird(third);
    widget->SetQuickActionFirst(first);
    return true;
}

// FUNCTION: GAME 0x005d7930
bool RHWidgetPortrait::FUN_005d7930(long id)
{
    // STRING: GAME 0x006b8e64
    return ((RHPortraitBitmapWidget *)((char *)this + 0x5fc))->Create(L"Amulet", RHMapBox(0.0f, 0.0f, 0.0f, 0.0f), 0, id);
}

// FUNCTION: GAME 0x005d7a30
bool RHWidgetPortrait::FUN_005d7a30(long id)
{
    // STRING: GAME 0x006b8e74
    return ((RHPortraitBitmapWidget *)((char *)this + 0x6c8))->Create(L"Guard", RHMapBox(0.0f, 0.0f, 0.0f, 0.0f), 0, id);
}

// FUNCTION: GAME 0x005d7b30
bool RHWidgetPortrait::FUN_005d7b30(long id)
{
    // STRING: GAME 0x006b8e80
    return ((RHPortraitBitmapWidget *)((char *)this + 0x7bc))->Create(L"Trumpet", RHMapBox(0.0f, 0.0f, 94.0f, 31.0f), 0, id);
}

// FUNCTION: GAME 0x005d7c40
bool RHWidgetPortrait::FUN_005d7c40(unsigned int index, long id, int first, int second, int third, int fourth, int fifth, const std::wstring &text)
{
    SBGeoBoundingBox2D box;
    RHPortraitBitmapWidget *widget;
    switch (index) {
    case 0:
        widget = (RHPortraitBitmapWidget *)((char *)this + 0x344);
        ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)((char *)this + 0xcf0));
        break;
    case 1:
        widget = (RHPortraitBitmapWidget *)((char *)this + 0x42c);
        ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)((char *)this + 0xd04));
        break;
    case 2:
        widget = (RHPortraitBitmapWidget *)((char *)this + 0x514);
        ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)((char *)this + 0xd18));
        break;
    }
    {
        SBGeoBoundingBox2D resourceBox(*(const SBGeoPoint2D *)&box);
        widget->Create(g_unk0x006c0b50, *(const RHMapBox *)&resourceBox, 0, id);
    }
    widget->SetScrollSecond(second);
    widget->SetScrollFirst(first);
    widget->SetQuickActionFirst(third);
    widget->SetQuickActionSecond(fourth);
    widget->SetQuickActionFourth(fifth);
    if (!text.empty()) {
        *((char *)widget + 8) = 1;
        *(std::wstring *)((char *)widget + 0x20) = text;
    }
    return true;
}

// Parked: several resource/message construction paths and their shared cleanup remain unaligned.
// STUB: GAME 0x005d7ea0
bool RHWidgetPortrait::FUN_005d7ea0()
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        RHUnk005d92c0Sub *widget = (RHUnk005d92c0Sub *)((char *)this + 0x97c + i * 0x104);
        widget->v08(P(0xcb4 + i * 20));
    }
    return true;
}

// Parked: the large action/resource dispatch still lacks its complete state and message model.
// STUB: GAME 0x005d8430
bool RHWidgetPortrait::FUN_005d8430()
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        char *element = (char *)this + 0xa50 + i * 0x104;
        if (*(char *)(element + 0x4e))
            *(char *)(element + 0x50) = 1;
        if (*(char *)(element + 0x4f))
            *(char *)(element + 0x51) = 1;
    }
    return true;
}

// FUNCTION: GAME 0x005d8ed0
void RHWidgetPortrait::FUN_005d8ed0(int value, int height)
{
    float maximum = (float)(unsigned short)height;
    m_16c = (float)(unsigned short)value;
    if (maximum != 0.0f)
        m_170 = maximum;
}

// FUNCTION: GAME 0x005d8f20
bool RHGamePortraitCalls::FUN_005d8f20(unsigned index)
{
    if (!*((char *)this + index + 0xc94))
    {
        void *previous = *(void **)((char *)this + index * 4 + 0xc88);
        RHUnk005d92c0Sub &widget = W(0x97c + index * 0x104);
        *(void **)((char *)this + index * 4 + 0xc88) = widget.v20();
        widget.v10((long)previous);
        *((char *)this + index + 0xc94) = 1;
    }
    char *slot = (char *)this + index * 0x104;
    ((RHUnk005d92c0Sub *)(slot + 0x97c))->DisableQuick(slot);
    return true;
}

#include "RHTitbitsCore.h"

extern RHTitbits *g_unk0x6c10e8;

// Parked: The retained resource-owner load uses edi before the ecx receiver copy.
// STUB: GAME 0x005d8fa0
bool RHGamePortraitCalls::FUN_005d8fa0(unsigned index, int enabled)
{
    if (*(char *)((char *)this + index + 0xc94))
    {
        void *previous = *(void **)((char *)this + index * 4 + 0xc88);
        RHUnk005d92c0Sub &widget = W(0x97c + index * 0x104);
        *(void **)((char *)this + index * 4 + 0xc88) = widget.v20();
        widget.v10((long)previous);
        *((char *)this + index + 0xc94) = 0;
    }
    char *slot = (char *)this + index * 0x104;
    ((RHUnk005d92c0Sub *)(slot + 0x97c))->v21(enabled);
    if ((unsigned char)enabled)
    {
        unsigned long action = *(unsigned long *)((char *)*(void **)((char *)this + 0xe1c) + (unsigned short)index * 4 + 0x538);
        RHTitbits *titbits = (RHTitbits *)g_unk0x6c10e8;
        bool running = titbits->IsRunningForQA(action);
        *(int *)(slot + 0xa50) = (unsigned short)titbits->FUN_005c7fb0(action);
        *(char *)(slot + 0xa55) = running;
    }
    else
    {
        *(int *)(slot + 0xa50) = -1;
        *(char *)(slot + 0xa55) = 0;
    }
    return true;
}

// FUNCTION: GAME 0x005d9070
void RHWidgetPortrait::FUN_005d9070()
{
    W(0x7bc).v21(1);
}

// FUNCTION: GAME 0x005d9090
bool RHWidgetPortrait::FUN_005d9090(unsigned int index)
{
    W(0x97c + index * 0x104).v21(0);
    return true;
}

// Parked at 0.6579: receiver/index scheduling and the final byte/integer copy differ.
// STUB: GAME 0x005d90c0
bool RHWidgetPortrait::FUN_005d90c0(unsigned int index)
{
    extern RHEngine *g_pEngine;
    RHEngineActionCalls *engine = *(RHEngineActionCalls *volatile *)&g_pEngine;
    char *element = (char *)this + index * 0x104;
    char *slot = element + 0x97c;
    ((RHUnk005d92c0Sub *)slot)->v21(engine->FUN_004d2300(*(void **)((char *)this + 0xe1c), index));
    *(unsigned short *)(slot + 0xec) = 24;
    *(unsigned short *)(slot + 0xee) = 10;
    ((RHMobileUnk00607da0 *)(slot + 0xf0))->FUN_00607da0(*(RHMobileUnk00607da0 *)(slot + 0x30));
    if (index != 2)
    {
        char state = *(char *)(element + 0xb59);
        int action = *(int *)(element + 0xb54);
        *(int *)(element + 0xa50) = action;
        *(char *)(element + 0xa55) = state;
    }
    return true;
}

// FUNCTION: GAME 0x005d9140
void RHGamePortraitCalls::FUN_005d9140(unsigned int index)
{
    *(unsigned short *)((char *)this + 0xc98 + index * 2) = 6;
    *(unsigned short *)((char *)this + 0xc9e + index * 2) = 5;
}

// Parked: By-value resource IDs materialize register constants instead of immediate pushes.
// STUB: GAME 0x005d9160
void RHWidgetPortrait::FUN_005d9160()
{
    SBResourceWidgetID id = {1};
    SBResourceWidgetID first = {1};
    SBResourceWidgetID second = {2};
    ((RHUIRendererBlinking *)((char *)this + 0x748))->SetBlinking(id, first, second, 25);
}

// Parked: Loop strength reduction retains an extra widget pointer and saved register.
// STUB: GAME 0x005d9180
void RHWidgetPortrait::FUN_005d9180()
{
    unsigned short *counter = (unsigned short *)((char *)this + 0xc98);
    char *element = (char *)this + 0xa54;
    int remaining = 3;
    for (; remaining; ++counter, element += 0x104, --remaining)
    {
        if (counter[3] == 5)
        {
            ((RHUnk005d92c0Sub *)(element - 0xd8))->v21(1);
            *element = counter[0] % 2 == 0;
        }
        if (counter[0] > 0 && --counter[3] == 0)
        {
            --counter[0];
            counter[3] = counter[0] != 0 ? 5 : 0;
            if (counter[0] == 0)
                *element = 1;
        }
    }
}

// FUNCTION: GAME 0x005d9210
SBGeoBoundingBox2D RHWidgetPortrait::FUN_005d9210() const
{
    SBGeoBoundingBox2D box;
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)((const char *)this + 0xd0));
    box.FUN_00607e90(*(const SBGeoBoundingBox2D *)((const char *)this + 0x298));
    box.FUN_00607e90(*(const SBGeoBoundingBox2D *)((const char *)this + 0x1bc));
    return box;
}

// FUNCTION: GAME 0x005d6690
bool RHWidgetPortrait::Method005d6690()
{
    m_arr[2].m_4e = 1;
    W(0x344).v08(P(0xcf0));
    W(0x42c).v08(P(0xd04));
    if (!m_arr[2].m_50)
        W(0x514).v08(P(0xd18));
    W(0x18c).v08(P(0xcc8));
    W(0xa0).v08(P(0xcb4));
    W(0x268).v08(P(0xcdc));
    W(0).v15(&W(0x344));
    W(0).v15(&W(0x42c));
    if (!m_arr[2].m_50)
        W(0).v15(&W(0x514));
    P(0xe20) = P(0xcdc);
    float x = P(0xe20).m_x;
    P(0xe20).m_x = x + 52.0f;
    float y = P(0xe20).m_y;
    P(0xe20).m_y = y + 10.0f;
    W(0x97c).v08(P(0xd2c));
    W(0xa80).v08(P(0xd40));
    W(0xb84).v08(P(0xd54));
    W(0x888).v08(P(0xcdc));
    return true;
}

// FUNCTION: GAME 0x005d67e0
bool RHWidgetPortrait::Method005d67e0()
{
    m_arr[2].m_4e = 0;
    if (!m_arr[2].m_4f)
    {
        W(0x344).v08(P(0xcf0));
        W(0x42c).v08(P(0xd04));
        if (!m_arr[2].m_50)
            W(0x514).v08(P(0xd18));
        W(0x18c).v08(P(0xd7c));
        W(0xa0).v08(P(0xd68));
        W(0x268).v08(P(0xd90));
        W(0).v14(&W(0x344));
        W(0).v14(&W(0x42c));
        if (!m_arr[2].m_50)
            W(0).v14(&W(0x514));
        P(0xe20) = P(0xd90);
        float x = P(0xe20).m_x;
        P(0xe20).m_x = x + 52.0f;
        float y = P(0xe20).m_y;
        P(0xe20).m_y = y + 10.0f;
        W(0x97c).v08(P(0xde0));
        W(0xa80).v08(P(0xdf4));
        W(0xb84).v08(P(0xe08));
        W(0x888).v08(P(0xd90));
    }
    return true;
}

// FUNCTION: GAME 0x005d73d0
bool RHWidgetPortrait::Method005d73d0()
{
    W(0xa0).v08(P(0x1bc).FUN_005fc200(SBGeoVector2D(0.0f, 23.0f)));
    if (A->FUN_0049f510())
    {
        W(0xa0).v21(1);
        W(0x18c).v21(1);
        FUN_005d8ed0(A->v51(), (int)(P(0xd8).m_x - P(0xd0).m_x));
    }
    else
    {
        W(0xa0).v21(0);
        W(0x18c).v21(0);
    }
    FUN_005da1f0();
    FUN_005d9c30();
    W(0).v14(&W(0x344));
    W(0).v14(&W(0x42c));
    W(0).v14(&W(0x514));
    W(0).v14(&W(0x268));
    m_arr[2].m_4f = 1;
    m_arr[2].m_4e = 0;
    return true;
}

// FUNCTION: GAME 0x005d7530
bool RHWidgetPortrait::Method005d7530()
{
    m_arr[2].m_4f = 0;
    m_arr[2].m_4e = 0;
    W(0xa0).v21(1);
    W(0x18c).v21(1);
    FUN_005da1f0();
    FUN_005d9c30();
    W(0).v15(&W(0x344));
    W(0).v15(&W(0x42c));
    if (!m_arr[2].m_50)
        W(0).v15(&W(0x514));
    W(0).v15(&W(0x268));
    Method005d67e0();
    return true;
}

// FUNCTION: GAME 0x005d92c0
bool RHWidgetPortrait::Serialize(SBFile &file)
{
    char b12;
    char bf;
    float f10;
    float tmp;
    int b14;
    int iArr;
    char bArr;

    // STRING: GAME 0x6b8e90
    RHSerializeName(file, "RHWidgetPortrait");

    if (file.Access(m_e50, 6) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8e28
                 "P:\\Robin Hood\\RHWidgetPortrait.cpp",
                 1207,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_arr[2].m_50, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1209, "Serialize failed reason is %s", reason);
        return false;
    }

    if (FileVersion(file) >= 0xf)
    {
        if (file.Access(&m_arr[2].m_51, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1213, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (file.m_bLoading)
    {
        if (file.Access(&b12, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1218, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&bf, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1219, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&f10, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1221, "Serialize failed reason is %s", reason);
            return false;
        }
        // Copy through `tmp` so VC6 models the value as an x87 value and emits
        // `fld [esp+0x10]; ...; fstp [edi+0x16c]` (sunk past the next Access's
        // argument setup). A direct `m_16c = f10` in a member function compiles
        // to an integer `mov` pair because eax is free (this is the only reason
        // the original differs here). `tmp` coalesces into f10's slot.
        tmp = f10;
        m_16c = tmp;
        if (file.Access(&b14, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1225, "Serialize failed reason is %s", reason);
            return false;
        }
        m_7bc.v21(b14);
        if (b12)
            Method005d73d0();
        else
            Method005d7530();
        if (bf)
            Method005d6690();
        else
            Method005d67e0();
    }
    else
    {
        if (file.Access(&m_arr[2].m_4f, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1250, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&m_arr[2].m_4e, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1251, "Serialize failed reason is %s", reason);
            return false;
        }
        // Same temp trick as the store path: `tmp = m_16c` makes VC6 hold the
        // member in ST0 and sink `fstp [esp+0x14]` past the Access argument
        // pushes, matching `fld [edi+0x16c]; lea eax,[esp+0x10]; push 4;
        // fstp [esp+0x14]; push eax`. A direct `f10 = m_16c` would use movs.
        tmp = m_16c;
        f10 = tmp;
        if (file.Access(&f10, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1254, "Serialize failed reason is %s", reason);
            return false;
        }
        // b14 is a 4-byte local (the load path passes all 32 bits to v21), but
        // only its low byte is serialised here; the target narrows the store to
        // one byte, so write the byte explicitly.
        *(char *)&b14 = m_7c0;
        if (file.Access(&b14, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1258, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    if (!file.m_bLoading)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            iArr = m_arr[i].m_00;
            if (file.Access(&iArr, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1270, "Serialize failed reason is %s", reason);
                return false;
            }
            bArr = m_arr[i].m_05;
            if (file.Access(&bArr, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1273, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            if (file.Access(&iArr, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1280, "Serialize failed reason is %s", reason);
                return false;
            }
            if (FileVersion(file) >= 0x2b)
            {
                if (file.Access(&bArr, 1) < 0)
                {
                    SBString *err = file.GetError();
                    const char *reason = err->m_chars ? err->m_chars : "";
                    SBAssert(0, "P:\\Robin Hood\\RHWidgetPortrait.cpp", 1284, "Serialize failed reason is %s", reason);
                    return false;
                }
            }
            else
            {
                bArr = 0;
            }
            m_arr[i].m_00 = iArr;
            m_arr[i].m_05 = bArr;
        }
    }

    return true;
}

// Force emission.
void RHWidgetPortrait::Emit(SBFile &file)
{
    Serialize(file);
}

// SIZE 0xe8
class RHPortraitActionButton
{
public:
    virtual void v00(); // vtable+0x00
    virtual void v01(); // vtable+0x04
    virtual void v02(); // vtable+0x08
    virtual void v03(); // vtable+0x0c
    virtual void v04(); // vtable+0x10
    virtual void v05(); // vtable+0x14
    virtual void v06(); // vtable+0x18
    virtual void v07(); // vtable+0x1c
    virtual void v08(); // vtable+0x20
    virtual void v09(); // vtable+0x24
    virtual void v10(int value); // vtable+0x28
    virtual void v11(); // vtable+0x2c
    virtual void v12(); // vtable+0x30
    virtual void v13(); // vtable+0x34
    virtual void v14(); // vtable+0x38
    virtual void v15(); // vtable+0x3c
    virtual void v16(); // vtable+0x40
    virtual void v17(); // vtable+0x44
    virtual void v18(); // vtable+0x48
    virtual void v19(); // vtable+0x4c
    virtual int v20(); // vtable+0x50
    virtual void v21(bool enabled); // vtable+0x54
    void Release()
    {
        if (m_cc == 1)
        {
            m_cc = 0;
            m_4c = 0;
            if (m_7c == 8)
                m_7c = 5;
            if (m_7c == 9)
                m_7c = 6;
        }
    }
    bool m_04; // 0x04
    char m_05; // 0x05
    char m_06; // 0x06
    undefined m_07[0x4c - 0x07]; // 0x07
    int m_4c; // 0x4c
    undefined m_50[0x7c - 0x50]; // 0x50
    int m_7c; // 0x7c
    undefined m_80[0xcc - 0x80]; // 0x80
    char m_cc; // 0xcc
    undefined m_cd[3]; // 0xcd
    void *m_d0; // 0xd0
    undefined m_d4[0x14]; // 0xd4
};

DECOMP_SIZE_ASSERT(RHPortraitActionButton, 0xe8)

#define B(O) (*(RHPortraitActionButton *)((char *)this + (O)))
#define TWO_BUTTONS (*((char *)this + 0xca8))

// FUNCTION: GAME 0x005d9920
void RHWidgetPortrait::FUN_005d9920()
{
    m_arr[2].m_50 = 1;
    W(0).v14(&W(0x514));
    ((RHPortraitCtorCalls *)this)->FUN_005d6940(*(unsigned short *)((char *)this + 0xca4));
}

// FUNCTION: GAME 0x005d9950
void RHGamePortraitCalls::FUN_005d9950(unsigned action)
{
    switch (action)
    {
    case 0:
        B(0x344).Release();
        B(0x344).v21(0);
        break;
    case 1:
        B(0x42c).Release();
        B(0x42c).v21(0);
        break;
    case 2:
        if (!TWO_BUTTONS)
        {
            B(0x514).Release();
            B(0x514).v21(0);
        }
        break;
    }
}

// FUNCTION: GAME 0x005d9a20
bool RHWidgetPortrait::FUN_005d9a20(int action)
{
    switch (action)
    {
    case 0:
        return B(0x344).m_04;
    case 1:
        return B(0x42c).m_04;
    case 2:
        if (!m_arr[2].m_50)
            return B(0x514).m_04;
    }
    return false;
}

// FUNCTION: GAME 0x005d9a60
void RHGamePortraitCalls::FUN_005d9a60(unsigned action)
{
    RHWidgetPortrait *portrait = (RHWidgetPortrait *)this;
    switch (action)
    {
    case 0:
        B(0x344).v21(portrait->FUN_005d9eb0(0));
        break;
    case 1:
        B(0x42c).v21(portrait->FUN_005d9eb0(1));
        break;
    case 2:
        if (!TWO_BUTTONS)
            B(0x514).v21(portrait->FUN_005d9eb0(2));
        break;
    }
}

// FUNCTION: GAME 0x005d9ae0
void RHGamePortraitCalls::FUN_005d9ae0(unsigned short action, bool enabled)
{
    B(0x97c + action * 0x104).v21(enabled);
}

// FUNCTION: GAME 0x005d9b10
void RHGamePortraitCalls::FUN_005d9b10()
{
    char *pending = (char *)this + 0xc94;
    RHPortraitActionButton *button = &B(0x97c);
    int *saved = (int *)((char *)this + 0xc88);
    for (int count = 3; count != 0; --count)
    {
        if (*pending)
        {
            *pending = 0;
            int previous = *saved;
            *saved = button->v20();
            button->v10(previous);
            *pending = 0;
        }
        ++saved;
        button = (RHPortraitActionButton *)((char *)button + 0x104);
        ++pending;
    }
}

// FUNCTION: GAME 0x005d9b70
void RHGamePortraitCalls::FUN_005d9b70()
{
    B(0x344).v21(0);
    B(0x42c).v21(0);
    if (!TWO_BUTTONS)
        B(0x514).v21(0);
}

// FUNCTION: GAME 0x005d9bc0
void RHWidgetPortrait::FUN_005d9bc0()
{
    B(0x344).v21(FUN_005d9eb0(0));
    B(0x42c).v21(FUN_005d9eb0(1));
    if (!m_arr[2].m_50)
        B(0x514).v21(FUN_005d9eb0(2));
}

// FUNCTION: GAME 0x005d9eb0
bool RHWidgetPortrait::FUN_005d9eb0(int action)
{
    if (((RHElementActorPC *)A)->FUN_0049d590(4) == action
        && (g_unk0x6c07fc->Get(1) < 50 || !A->v57(4)))
        return false;
    return true;
}

class RHUIRendererCustom
{
public:
    bool Render(unsigned int id);
};

class RHPortraitWidgetRenderer
{
public:
    virtual void v0(); // vtable+0x00
    virtual void v1(int value); // vtable+0x04
};

#define PORTRAIT_WIDGET_VIRTUALS \
    virtual void v00(); \
    virtual void v01(); \
    virtual void v02(); \
    virtual void v03(); \
    virtual void v04(); \
    virtual void v05(); \
    virtual void v06(); \
    virtual void v07(); \
    virtual void v08(); \
    virtual unsigned int v09();

// SIZE 0xdc
class RHPortraitWidget005da4a0
{
public:
    PORTRAIT_WIDGET_VIRTUALS
    void FUN_005da4a0();
    void FUN_005da4c0(long id);
    void FUN_005da4f0(const std::wstring &text);
    void FUN_005da700(int value);
    int FUN_005da720();
    int FUN_005da780(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *FUN_005da820(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005da860(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005da8f0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005da930(const RHPortraitWidgetInput &input);
    void FUN_005dec30(const SBGeoBoundingBox2D &box);
    RHPortraitWidgetEvent *FUN_005daea0(const RHPortraitWidgetInput &input);
    char m_04; // 0x04
    char m_05; // 0x05
    char m_06; // 0x06
    undefined m_07[3]; // 0x07
    unsigned short m_0a; // 0x0a
    undefined m_0c[0x30 - 0x0c]; // 0x0c
    SBGeoBoundingBox2D m_box; // 0x30
    undefined m_44[0x4c - 0x44]; // 0x44
    RHPortraitWidgetEvent m_event; // 0x4c
    undefined m_5c[0x7c - 0x5c]; // 0x5c
    int m_7c; // 0x7c
    undefined m_renderer[0x4c]; // 0x80
    RHUnk5490f0 *m_messages[4]; // 0xcc
};

// SIZE 0xe8
class RHActorPCWidgetState
{
public:
    PORTRAIT_WIDGET_VIRTUALS
    void FUN_005db620(RHActorPCWidgetState *state);
    int FUN_005da970();
    RHPortraitWidgetEvent *FUN_005daa00(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005daa80(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005dab00(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005dab40(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005dab80(const RHPortraitWidgetInput &input);
    void ClearLinked()
    {
        if (m_d0 && this != m_d0)
        {
            RHActorPCWidgetState *linked = m_d0;
            if (linked->m_cc == 1)
            {
                if (linked->m_7c == 9)
                    linked->m_7c = 6;
                if (linked->m_7c == 8)
                    linked->m_7c = 5;
                linked->m_cc = 0;
            }
            linked->m_d0->FUN_005db620(this);
        }
    }
    char m_04; // 0x04
    char m_05; // 0x05
    char m_06; // 0x06
    undefined m_07[0x4c - 0x07]; // 0x07
    RHPortraitWidgetEvent m_event; // 0x4c
    undefined m_5c[0x7c - 0x5c]; // 0x5c
    int m_7c; // 0x7c
    undefined m_80[0xcc - 0x80]; // 0x80
    char m_cc; // 0xcc
    undefined m_cd[3]; // 0xcd
    RHActorPCWidgetState *m_d0; // 0xd0
    RHUnk5490f0 *m_messages[5]; // 0xd4
};

// SIZE 0xec
class RHPortraitWidget005dafd0
{
public:
    PORTRAIT_WIDGET_VIRTUALS
    void FUN_005dafd0();
    RHPortraitWidgetEvent *FUN_005db080(const RHPortraitWidgetInput &input);
    int FUN_005db0a0();
    int FUN_005db100(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *FUN_005db1a0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005db1e0(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005db270(const RHPortraitWidgetInput &input);
    RHPortraitWidgetEvent *FUN_005db2b0(const RHPortraitWidgetInput &input);
    int FUN_005db2f0(unsigned int id);
    void FUN_005db350();
    char m_04; // 0x04
    char m_05; // 0x05
    char m_06; // 0x06
    undefined m_07[3]; // 0x07
    unsigned short m_0a; // 0x0a
    undefined m_0c[0x4c - 0x0c]; // 0x0c
    RHPortraitWidgetEvent m_event; // 0x4c
    undefined m_5c[0x7c - 0x5c]; // 0x5c
    int m_7c; // 0x7c
    undefined m_renderer[0x5c]; // 0x80
    RHUnk5490f0 *m_messages[4]; // 0xdc
    unsigned short m_ec; // 0xec
    unsigned short m_ee; // 0xee
    SBGeoBoundingBox2D m_box; // 0xf0
};

DECOMP_SIZE_ASSERT(RHPortraitWidget005da4a0, 0xdc)
DECOMP_SIZE_ASSERT(RHActorPCWidgetState, 0xe8)
DECOMP_SIZE_ASSERT(RHPortraitWidget005dafd0, 0x104)

inline void RHPortraitPost(RHUnk5490f0 *const &message)
{
    RHMessenger *messenger = RHUnk00546050();
    if (message)
        messenger->RHUnk005460c0(*message);
}

// FUNCTION: GAME 0x005da4a0
void RHPortraitWidget005da4a0::FUN_005da4a0()
{
    ((RHUIRendererCustom *)m_renderer)->Render(v09());
}

// FUNCTION: GAME 0x005da4c0
void RHPortraitWidget005da4a0::FUN_005da4c0(long id)
{
    SBUIUnk0060d530 &renderer = *(SBUIUnk0060d530 *)m_renderer;
    renderer.FUN_0060d550(id);
    ((RHMobileUnk00607da0 *)&m_box)->FUN_00607da0(*(RHMobileUnk00607da0 *)renderer.FUN_0060d690());
}

// FUNCTION: GAME 0x005da4f0
void RHPortraitWidget005da4a0::FUN_005da4f0(const std::wstring &text)
{
    *(std::wstring *)((char *)this + 0x10) = text;
    *(std::wstring *)((char *)this + 0xa8) = text;
}

void EmitRHPortraitWidgetText(RHPortraitWidget005da4a0 &widget, const std::wstring &text)
{
    void (RHPortraitWidget005da4a0::*setText)(const std::wstring &) = &RHPortraitWidget005da4a0::FUN_005da4f0;
    (widget.*setText)(text);
}

// FUNCTION: GAME 0x005da700
void RHPortraitWidget005da4a0::FUN_005da700(int value)
{
    ((RHPortraitWidgetRenderer *)m_renderer)->v1(value);
}

// FUNCTION: GAME 0x005da720
int RHPortraitWidget005da4a0::FUN_005da720()
{
    int result;
    if (!m_04)
        return 0;
    switch (m_7c)
    {
    case 2:
    case 3:
        return 3;
    case 1:
        return 2;
    case 0:
        result = 1;
        break;
    }
    if (result == 1 && !m_06)
        result = 0xff;
    return result;
}

// FUNCTION: GAME 0x005da780
int RHPortraitWidget005da4a0::FUN_005da780(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = m_box;
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)m_renderer)->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// FUNCTION: GAME 0x005da820
RHPortraitWidgetEvent *RHPortraitWidget005da4a0::FUN_005da820(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[0]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005da860
RHPortraitWidgetEvent *RHPortraitWidget005da4a0::FUN_005da860(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[1]);
    if ((input.flags & 1) || (m_0a && input.shortcuts->FUN_0060e240(m_0a) == 2))
        m_event.type = 2;
    else if ((input.flags & 8) || (m_0a && input.shortcuts->FUN_0060e240(m_0a) == 3))
        m_event.type = 3;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005da8f0
RHPortraitWidgetEvent *RHPortraitWidget005da4a0::FUN_005da8f0(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[2]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005da930
RHPortraitWidgetEvent *RHPortraitWidget005da4a0::FUN_005da930(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[3]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 4;
    return &m_event;
}

// FUNCTION: GAME 0x005da970
int RHActorPCWidgetState::FUN_005da970()
{
    int result;
    if (!m_04)
        return 0;
    switch (m_7c)
    {
    case 5:
    case 8:
        if (m_05 == 1)
            return m_cc ? 4 : 2;
        result = m_cc ? 3 : 1;
        break;
    case 6:
    case 7:
        result = 1;
        break;
    case 9:
    case 10:
        result = 3;
        break;
    default:
        if (result != 3 && result != 1)
            return result;
    }
    if (m_06 != 1)
        result = 0xff;
    return result;
}

// FUNCTION: GAME 0x005daa00
RHPortraitWidgetEvent *RHActorPCWidgetState::FUN_005daa00(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[0]);
    m_event.type = 2;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    ClearLinked();
    return &m_event;
}

// FUNCTION: GAME 0x005daa80
RHPortraitWidgetEvent *RHActorPCWidgetState::FUN_005daa80(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[1]);
    m_event.type = 7;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    ClearLinked();
    return &m_event;
}

// FUNCTION: GAME 0x005dab00
RHPortraitWidgetEvent *RHActorPCWidgetState::FUN_005dab00(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[2]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 4;
    return &m_event;
}

// FUNCTION: GAME 0x005dab40
RHPortraitWidgetEvent *RHActorPCWidgetState::FUN_005dab40(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[3]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 5;
    return &m_event;
}

// FUNCTION: GAME 0x005dab80
RHPortraitWidgetEvent *RHActorPCWidgetState::FUN_005dab80(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[4]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 6;
    return &m_event;
}

// FUNCTION: GAME 0x005daea0
RHPortraitWidgetEvent *RHPortraitWidget005da4a0::FUN_005daea0(const RHPortraitWidgetInput &input)
{
    if (m_04)
    {
        SBGeoBoundingBox2D &box = m_box;
        if (box.FUN_006083b0(input.point) == 1 &&
            ((RHGameWidgetRendererCalls *)m_renderer)->FUN_0060d890(input.point.Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        {
            if (!(input.flags & 1))
            {
                RHPortraitWidgetEvent *event = &m_event;
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                event->type = 0;
                return event;
            }
        }
        else if (!m_0a || input.shortcuts->FUN_0060e240(m_0a) != 2)
        {
            m_7c = 0;
            return 0;
        }
        RHPortraitWidgetEvent *event = &m_event;
        if (m_event.type != 2 && m_event.type != 7)
        {
            m_event.next = 0;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 2;
            return event;
        }
        m_event.next = 0;
        m_event.value = 0;
        m_event.widget = this;
        event->type = 7;
        return event;
    }
    return 0;
}

// FUNCTION: GAME 0x005dafd0
void RHPortraitWidget005dafd0::FUN_005dafd0()
{
    ((RHUIRendererShiftingTitbit *)m_renderer)->Render(v09());
}

// FUNCTION: GAME 0x005db080
RHPortraitWidgetEvent *RHPortraitWidget005dafd0::FUN_005db080(const RHPortraitWidgetInput &input)
{
    m_event.next = 0;
    m_event.widget = this;
    m_event.type = 1;
    m_event.value = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005db0a0
int RHPortraitWidget005dafd0::FUN_005db0a0()
{
    int result;
    if (!m_04)
        return 0;
    switch (m_7c)
    {
    case 2:
    case 3:
        return 3;
    case 1:
        return 2;
    case 0:
        result = 1;
        break;
    }
    if (result == 1 && !m_06)
        result = 0xff;
    return result;
}

// FUNCTION: GAME 0x005db100
int RHPortraitWidget005dafd0::FUN_005db100(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)m_renderer)->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// FUNCTION: GAME 0x005db1a0
RHPortraitWidgetEvent *RHPortraitWidget005dafd0::FUN_005db1a0(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[0]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005db1e0
RHPortraitWidgetEvent *RHPortraitWidget005dafd0::FUN_005db1e0(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[1]);
    if ((input.flags & 1) || (m_0a && input.shortcuts->FUN_0060e240(m_0a) == 2))
        m_event.type = 2;
    else if ((input.flags & 8) || (m_0a && input.shortcuts->FUN_0060e240(m_0a) == 3))
        m_event.type = 3;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005db270
RHPortraitWidgetEvent *RHPortraitWidget005dafd0::FUN_005db270(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[2]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 0;
    return &m_event;
}

// FUNCTION: GAME 0x005db2b0
RHPortraitWidgetEvent *RHPortraitWidget005dafd0::FUN_005db2b0(const RHPortraitWidgetInput &input)
{
    RHPortraitPost(m_messages[3]);
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    m_event.type = 4;
    return &m_event;
}

static inline unsigned int RHPortraitAnimatedComparison(SBUIUnk0060dae0 *renderer, unsigned int id)
{
    unsigned int previous = ((unsigned int *)((char *)renderer + 0x40))[(*(unsigned int *)((char *)renderer + 0x48)) & 1];
    unsigned int current = id == 255 ? 0 : renderer->FUN_0060db80(id);
    if (current == (unsigned int)-1)
        return 3;
    if (previous != current)
        return current == 0 ? 2 : 1;
    return 0;
}

// FUNCTION: GAME 0x005db2f0
int RHPortraitWidget005dafd0::FUN_005db2f0(unsigned int id)
{
    if (m_ec != 0)
        return 1;
    return RHPortraitAnimatedComparison((SBUIUnk0060dae0 *)m_renderer, id);
}

// FUNCTION: GAME 0x005db350
void RHPortraitWidget005dafd0::FUN_005db350()
{
    SBGeoBoundingBox2D &bounds = m_box;
    if (bounds.Unk00608f30() &&
        bounds.m_second.m_x - bounds.m_first.m_x > 0.0f &&
        bounds.m_second.m_y - bounds.m_first.m_y > 0.0f)
        ((RHMobileUnk00607da0 *)((char *)this + 0x30))->FUN_00607da0((const RHMobileUnk00607da0 &)
            bounds.FUN_006090d0(SBGeoVector2D((float)m_ec, 0.0f)));
    if (m_ec)
    {
        if (m_ec > m_ee)
            m_ec -= m_ee;
        else
        {
            m_ec = 0;
            m_ee = 0;
            bounds.FUN_00607d90();
        }
    }
    ((RHUIRendererShiftingTitbit *)m_renderer)->SetCounter(m_ec);
    ((RHUIRendererShiftingTitbit *)m_renderer)->Render(v09());
}

class RHPortraitLifetime005dae40 : public RHGameLifetime00516a60
{
public:
    ~RHPortraitLifetime005dae40() {}
    void *FUN_005db560(unsigned flags);
};

class RHPortraitDeleting
{
public:
    void *FUN_005db500(unsigned flags);
    void *FUN_005db520(unsigned flags);
    void *FUN_005db540(unsigned flags);
    void *FUN_005db600(unsigned flags);
    void *FUN_005db690(unsigned flags);
    void *FUN_005dee30(unsigned flags);
    void *FUN_005deff0(unsigned flags);
    void *FUN_005df010(unsigned flags);
};

#include "RHGameWidgetLifetime.h"

typedef RHGameRenderer0060da10 RHPortraitRenderer0060da10;

typedef RHPortraitRenderer0060dab0 RHPortraitRenderer0060dad0;

#include "RHPortraitRenderer0060d470.h"

// SYNTHETIC: GAME 0x005dae40
// ??1RHPortraitLifetime005dae40@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db480
void *RHPortraitLifetime005db4a0::FUN_005db480(unsigned flags)
{
    this->~RHPortraitLifetime005db4a0();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// SYNTHETIC: GAME 0x005db4a0
// ??1RHPortraitLifetime005db4a0@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db500
void *RHPortraitDeleting::FUN_005db500(unsigned flags)
{
    RHPortraitLifetime005d6200 *self = (RHPortraitLifetime005d6200 *)this;
    self->~RHPortraitLifetime005d6200();
    if (flags & 1)
        operator delete(self);
    return self;
}
#pragma inline_depth()

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db520
void *RHPortraitDeleting::FUN_005db520(unsigned flags)
{
    RHPortraitLifetime005d6260 *self = (RHPortraitLifetime005d6260 *)this;
    self->~RHPortraitLifetime005d6260();
    if (flags & 1)
        operator delete(self);
    return self;
}
#pragma inline_depth()

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db540
void *RHPortraitDeleting::FUN_005db540(unsigned flags)
{
    RHPortraitLifetime005d62c0 *self = (RHPortraitLifetime005d62c0 *)this;
    self->~RHPortraitLifetime005d62c0();
    if (flags & 1)
        operator delete(self);
    return self;
}
#pragma inline_depth()

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db560
void *RHPortraitLifetime005dae40::FUN_005db560(unsigned flags)
{
    this->~RHPortraitLifetime005dae40();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db580
void *RHPortraitLifetime005db5a0::FUN_005db580(unsigned flags)
{
    this->~RHPortraitLifetime005db5a0();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// SYNTHETIC: GAME 0x005db5a0
// ??1RHPortraitLifetime005db5a0@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db600
void *RHPortraitDeleting::FUN_005db600(unsigned flags)
{
    RHPortraitLifetime005d6320 *self = (RHPortraitLifetime005d6320 *)this;
    self->~RHPortraitLifetime005d6320();
    if (flags & 1)
        operator delete(self);
    return self;
}
#pragma inline_depth()

// FUNCTION: GAME 0x005db620
void RHActorPCWidgetState::FUN_005db620(RHActorPCWidgetState *state)
{
    for (RHActorPCWidgetState *widget = this; state != widget; widget = widget->m_d0)
    {
        if (widget->m_cc == 1)
        {
            if (widget->m_7c == 9)
                widget->m_7c = 6;
            if (widget->m_7c == 8)
                widget->m_7c = 5;
            widget->m_cc = 0;
        }
    }
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x005db690
void *RHPortraitDeleting::FUN_005db690(unsigned flags)
{
    RHPortraitLifetime005d63b0 *self = (RHPortraitLifetime005d63b0 *)this;
    self->~RHPortraitLifetime005d63b0();
    if (flags & 1)
        operator delete(self);
    return self;
}
#pragma inline_depth()

// SYNTHETIC: GAME 0x005db6b0
// ??0RHPortraitLifetime005db4a0@@QAE@XZ

// FUNCTION: GAME 0x005db700
RHGameLifetime00516750::RHGameLifetime00516750()
{
    m_state = 6;
    *(char *)&m_strategy = 0;
}


// SIZE 0x20
class RHPortraitRecord005dec40
{
public:
    RHPortraitRecord005dec40 &operator=(const RHPortraitRecord005dec40 &other);
    int m_00; // 0x00
    undefined m_box[0x14]; // 0x04
    int m_18; // 0x18
    int m_1c; // 0x1c
};

#include <algorithm>

void FUN_005df400(RHUnk005d92c0Sub *widget);

#include "RHPortraitRootList.h"
#include "RHUnk005db7e0.h"

// FUNCTION: GAME 0x005db7e0
RHUnk005db7e0::~RHUnk005db7e0()
{
    std::vector<RHUnk005db7e0Entry>::iterator entry;
    for (entry = m_entries.begin(); entry != m_entries.end(); ++entry)
    {
        FUN_005df300((RHUnk005d92c0Sub *)&entry->m_08);
        if (entry->m_04 != 0 || entry->m_00 != 0)
        {
            FUN_005df300((RHUnk005d92c0Sub *)&entry->m_d8);
            FUN_005df300((RHUnk005d92c0Sub *)&entry->m_1a8);
        }
    }
}

DECOMP_SIZE_ASSERT(RHUnk005db7e0, 0xc0)
DECOMP_SIZE_ASSERT(RHUnk005db7e0Entry, 0x278)
DECOMP_SIZE_ASSERT(RHUnk005db7e0Slot, 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005db7e0, m_entries) == 0xb0)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005db7e0Entry, m_08) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005db7e0Entry, m_d8) == 0xd8)
DECOMP_STATIC_ASSERT(offsetof(RHUnk005db7e0Entry, m_1a8) == 0x1a8)

// FUNCTION: GAME 0x005dc690
void RHUnk005db7e0::FUN_005dc690(const SBGeoBoundingBox2D &bounds)
{
    SBGeoPoint2D position;
    ((SBFrameWnd *)this)->FUN_0061ad20(bounds);
    unsigned width = m_entries.size() * 50 - 10;
    position = bounds.m_first;
    position.FUN_005fc1e0(SBGeoVector2D(bounds.Width() * 0.5f - (width >> 1), 0.0f));
    for (std::vector<RHUnk005db7e0Entry>::iterator entry = m_entries.begin(); entry != m_entries.end(); ++entry)
    {
        ((RHUnk005d92c0Sub *)&entry->m_08)->v08(position);
        ((RHUnk005d92c0Sub *)&entry->m_d8)->v08(position.Unk005fc190(SBGeoVector2D(25.0f, 30.0f)));
        if (entry->m_00 != 0 || entry->m_04 != 0)
            ((RHUnk005d92c0Sub *)&entry->m_1a8)->v08(position.Unk005fc190(SBGeoVector2D(-1.0f, 2.0f)));
        position.FUN_005fc1e0(SBGeoVector2D(50.0f, 0.0f));
    }
}

// TEMPLATE: GAME 0x00460900 FOLDED
// ?compare@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEHIIPBDI@Z

// FUNCTION: GAME 0x005dc8a0
int FUN_005dc8a0(const std::string &name)
{
    if (name == "Robin des bois")
        return 6;
    if (name == "Robin des villes")
        return 6;
    if (name == "Petit Jean")
        return 1;
    if (name == "Frere Tuck")
        return 9;
    if (name == "Stutely")
        return 8;
    if (name == "Will Ecarlate")
        return 7;
    if (name == "Lady Marianne")
        return 2;
    if (name == "Paysan A")
        return 3;
    if (name == "Paysan B")
        return 4;
    if (name == "Paysan C")
        return 5;
    return 0;
}

#include "RHCampaignCommandLine.h"

inline bool RHPortraitNamesEqual(const std::string &left, const std::string &right)
{
    return ((RHCampaignCommandLine *)&left)->FUN_0045a010(*(const RHProfileText *)&right) == 0;
}

// FUNCTION: GAME 0x005dcbb0
int FUN_005dcbb0(const std::string &name)
{
    if (RHPortraitNamesEqual(name, std::string("Robin des bois")))
        return 1;
    if (name == std::string("Robin des villes"))
        return 1;
    if (name == std::string("Petit Jean"))
        return 4;
    if (name == std::string("Frere Tuck"))
        return 5;
    if (name == std::string("Stutely"))
        return 2;
    if (name == std::string("Will Ecarlate"))
        return 3;
    if (name == std::string("Lady Marianne"))
        return 6;
    return 0;
}

// FUNCTION: GAME 0x005de100
void FUN_005de100(unsigned short *destination, const unsigned short &value)
{
    *destination = value;
}

// LIBRARY: GAME 0x005de110
// ?_Nullstr@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@CAPBGXZ

// FUNCTION: GAME 0x005dec30
void RHPortraitWidget005da4a0::FUN_005dec30(const SBGeoBoundingBox2D &box)
{
    ((RHMobileUnk00607da0 *)&m_box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)&box);
}

// FUNCTION: GAME 0x005dec40
RHPortraitRecord005dec40 &RHPortraitRecord005dec40::operator=(const RHPortraitRecord005dec40 &other)
{
    m_00 = other.m_00;
    ((RHMobileUnk00607da0 *)m_box)->FUN_00607da0(*(const RHMobileUnk00607da0 *)other.m_box);
    m_18 = other.m_18;
    m_1c = other.m_1c;
    return *this;
}

// FUNCTION: GAME 0x005dee10
void *RHGameWidgetLifetimeBase::FUN_005dee10(unsigned flags)
{
    RHGameWidgetLifetimeBase *self = this;
    self->~RHGameWidgetLifetimeBase();
    if (flags & 1)
        operator delete(self);
    return self;
}

// FUNCTION: GAME 0x005dee30
void *RHPortraitDeleting::FUN_005dee30(unsigned flags)
{
    RHPortraitRenderer0060dad0 *self = (RHPortraitRenderer0060dad0 *)this;
    self->RHPortraitRenderer0060dad0::~RHPortraitRenderer0060dad0();
    if (flags & 1)
        operator delete(self);
    return self;
}

// FUNCTION: GAME 0x005deff0
void *RHPortraitDeleting::FUN_005deff0(unsigned flags)
{
    RHPortraitRenderer0060da10 *self = (RHPortraitRenderer0060da10 *)this;
    self->~RHPortraitRenderer0060da10();
    if (flags & 1)
        operator delete(self);
    return self;
}

// FUNCTION: GAME 0x005df010
void *RHPortraitDeleting::FUN_005df010(unsigned flags)
{
    RHPortraitRenderer0060d470 *self = (RHPortraitRenderer0060d470 *)this;
    self->RHPortraitRenderer0060d470::~RHPortraitRenderer0060d470();
    if (flags & 1)
        operator delete(self);
    return self;
}

// FUNCTION: GAME 0x005df0e0
RHPortraitRootList::~RHPortraitRootList()
{
    *(unsigned *)this = 0x00678ea8;
}

DECOMP_SIZE_ASSERT(RHPortraitRootList, 0xb0)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitRootList, m_items) == 0xa0)

// FUNCTION: GAME 0x005df120
bool RHPortraitRootList::FUN_005df120(RHUnk005d92c0Sub *widget)
{
    if (FUN_0061a800(widget))
    {
        m_items.push_back(widget);
        return true;
    }
    return false;
}

// TEMPLATE: GAME 0x0059fb00 FOLDED
// ?_Construct@std@@YAXPAPAVRHUnk005d92c0Sub@@ABQAV2@@Z

// TEMPLATE: GAME 0x004fe450 FOLDED
// ?_Ufill@?$vector@PAVRHUnk005d92c0Sub@@V?$allocator@PAVRHUnk005d92c0Sub@@@std@@@std@@IAEXPAPAVRHUnk005d92c0Sub@@IABQAV3@@Z

// TEMPLATE: GAME 0x004fe420 FOLDED
// ?_Ucopy@?$vector@PAVRHUnk005d92c0Sub@@V?$allocator@PAVRHUnk005d92c0Sub@@@std@@@std@@IAEPAPAVRHUnk005d92c0Sub@@PBQAV3@0PAPAV3@@Z

// TEMPLATE: GAME 0x005008e0 FOLDED
// ?_Destroy@?$vector@PAVRHUnk005d92c0Sub@@V?$allocator@PAVRHUnk005d92c0Sub@@@std@@@std@@IAEXPAPAVRHUnk005d92c0Sub@@0@Z

// FUNCTION: GAME 0x005df300
bool RHPortraitRootList::FUN_005df300(RHUnk005d92c0Sub *widget)
{
    if (widget)
    {
        if (FUN_0061a920(widget))
        {
            FUN_005df400(widget);
            m_items.erase(std::remove(m_items.begin(), m_items.end(), widget), m_items.end());
            return true;
        }
        return false;
    }
    std::for_each(m_items.begin(), m_items.end(), FUN_005df400);
    m_items.erase(m_items.begin(), m_items.end());
    return FUN_0061a920(0);
}

// FUNCTION: GAME 0x005df400
void FUN_005df400(RHUnk005d92c0Sub *widget)
{
    widget->v02();
}

// FUNCTION: GAME 0x005dcb10
int FUN_005dcb10(int value)
{
    switch (value)
    {
    case 1:
        return 1;
    case 9:
        return 5;
    case 25:
    case 26:
        return 2;
    case 21:
        return 3;
    case 22:
        return 4;
    case 28:
        return 6;
    case 2:
    case 3:
        return 7;
    case 27:
        return 8;
    case 13:
    case 14:
        return 9;
    case 23:
        return 10;
    }
    return 0;
}

struct RHPortraitKeyed
{
    undefined m_00[0x40]; // 0x00
    int m_40; // 0x40
};

// SIZE 0x278
struct RHPortraitQuickEntry
{
    ~RHPortraitQuickEntry();
    int m_00; // 0x00
    int m_04; // 0x04
    RHGameLifetime00517590 m_08; // 0x08
    undefined m_d4[4]; // 0xd4
    RHGameLifetime00517590 m_d8; // 0xd8
    undefined m_1a4[4]; // 0x1a4
    RHGameLifetime00515b40 m_1a8; // 0x1a8
};

// FUNCTION: GAME 0x005dc5d0
RHPortraitQuickEntry::~RHPortraitQuickEntry()
{
}

#include "RHPCActionQueryCalls.h"

struct RHPortraitPCNode
{
    undefined m_00[8]; // 0x00
    char *m_actor; // 0x08
};

class RHPortraitPCList
{
public:
    __forceinline void FUN_005c8e40(unsigned index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    undefined m_00[8]; // 0x00
    unsigned m_08; // 0x08
    RHPortraitPCNode *m_0c; // 0x0c
};

#include "RHPortraitQuickList.h"


// Parked: VC6 swaps the stack slots of the hoisted PC count and the entry cursor.
// STUB: GAME 0x005dd1d0
bool RHPortraitQuickList::FUN_005dd1d0(RHPortraitPCList &list)
{
    RHPortraitQuickEntry *entry = m_first;
    unsigned count = list.m_08;
    for (; entry != m_last; ++entry)
    {
        bool enabled = false;
        int action = entry->m_00;
        if (action)
        {
            for (unsigned i = 0; i < count; ++i)
            {
                list.FUN_005c8e40(i);
                char *actor = list.m_0c->m_actor;
                if (((RHUnk0049d4f0 *)actor)->Unk(action) || ((RHScriptBatchCalls *)actor)->Unk0049d560(action))
                {
                    enabled = true;
                    break;
                }
                if (action == 25)
                {
                    if (((RHScriptBatchCalls *)actor)->Unk0049d560(26))
                    {
                        enabled = true;
                        break;
                    }
                }
                else if (action == 26)
                {
                    if (((RHScriptBatchCalls *)actor)->Unk0049d560(25))
                    {
                        enabled = true;
                        break;
                    }
                }
                else if (action == 13)
                {
                    if (((RHUnk0049d4f0 *)actor)->Unk(14))
                    {
                        enabled = true;
                        break;
                    }
                }
                else if (action == 14)
                {
                    if (((RHUnk0049d4f0 *)actor)->Unk(13))
                    {
                        enabled = true;
                        break;
                    }
                }
            }
        }
        else
        {
            int pc = entry->m_04;
            if (pc)
            {
                for (unsigned i = 0; i < count; ++i)
                {
                    list.FUN_005c8e40(i);
                    if (*(int *)(list.m_0c->m_actor + 0x5fc) == pc)
                    {
                        enabled = true;
                        break;
                    }
                }
            }
        }
        entry->m_1a8.m_04 = enabled;
    }
    return true;
}

// FUNCTION: GAME 0x005dd320
void FUN_005dd320(int key, std::vector<RHPortraitKeyed *> &list)
{
    for (std::vector<RHPortraitKeyed *>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ((*it)->m_40 == key)
        {
            list.erase(it);
            return;
        }
    }
}

// FUNCTION: GAME 0x005da340
std::wstring RHWidgetPortrait::GetPCName() const
{
    std::wstring name = *(const std::wstring *)(*(const char *const *)(*(const char *const *)((const char *)this + 0xe1c) + 0x600) + 0x2c);
    if (!(*(RHUnk005d73d0Actor *const *)((const char *)this + 0xe1c))->v62())
    {
        for (std::wstring::iterator it = name.begin(); it != name.end(); ++it)
        {
            if (*it == L' ')
            {
                *it = L'\n';
                break;
            }
        }
    }
    return name;
}

#include "RHSoundCore.h"

// FUNCTION: GAME 0x005d9c30
void RHWidgetPortrait::FUN_005d9c30()
{
    SBGeoBoundingBox2D frame;
    SBGeoBoundingBox2D bounds(P(0xd0), P(0x1c4));
    ((RHMobileUnk00607da0 *)&frame)->FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)this + 0x62c));
    {
        SBGeoVector2D origin(*(SBGeoVector2D *)&bounds.m_first);
        W(0x5fc).v08(SBGeoPoint2D((bounds.Width() - frame.Width()) * 0.5f,
                                  (bounds.Height() - frame.Height()) * 0.5f)
                          .Unk005fc190(origin));
    }
    ((RHMobileUnk00607da0 *)&frame)->FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)this + 0x6f8));
    {
        SBGeoVector2D origin(*(SBGeoVector2D *)&bounds.m_first);
        W(0x6c8).v08(SBGeoPoint2D((bounds.Width() - frame.Width()) * 0.5f,
                                  (bounds.Height() - frame.Height()) * 0.5f)
                          .Unk005fc190(origin));
    }
    if (A->FUN_0049f510())
    {
        W(0x5fc).v21(1);
        W(0).v15(&W(0x5fc));
        W(0x6c8).v21(0);
        extern RHEngine *g_pEngine;
        (*(RHSound **)((char *)g_pEngine + 0x45e0))->PlayJingle(7);
    }
    else
    {
        W(0x5fc).v21(0);
        W(0).v14(&W(0x5fc));
        W(0x6c8).v21(0);
        W(0).v14(&W(0x6c8));
    }
}

// FUNCTION: GAME 0x005da1f0
void RHWidgetPortrait::FUN_005da1f0()
{
    SBGeoBoundingBox2D frame;
    SBGeoBoundingBox2D bounds(P(0xd0), P(0x1c4));
    ((RHMobileUnk00607da0 *)&frame)->FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)this + 0x7ec));
    SBGeoVector2D origin(*(SBGeoVector2D *)&bounds.m_first);
    W(0x7bc).v08(SBGeoPoint2D((bounds.Width() - frame.Width()) * 0.5f,
                              (bounds.Height() - frame.Height()) * 0.5f)
                      .Unk005fc190(origin));
}

// FUNCTION: GAME 0x005dd370
RHPortraitWidgetEvent *RHPortraitQuickList::FUN_005dd370(const void *input)
{
    RHPortraitWidgetEvent *events = (RHPortraitWidgetEvent *)FUN_0061a6e0(input);
    for (RHPortraitWidgetEvent *event = events; event; event = event->next)
    {
        if (event->type == 0)
        {
            for (RHPortraitQuickEntry *entry = m_first; entry != m_last; ++entry)
            {
                if ((void *)&entry->m_08 == (void *)event->widget)
                {
                    if (!entry->m_04 && entry->m_00)
                        RHUnk00546050()->RHUnk005460c0(RHUnk5490f0(0x2d, entry->m_00));
                    break;
                }
            }
        }
    }
    return events;
}

#include "RHAction.h"

RHaction &EmitRHRequirementActionArrayAccess(std::vector<RHaction> &actions, unsigned index)
{
    return actions.at(index);
}

void EmitRHRequirementActionArrayInsert(std::vector<RHaction> &actions,
    RHaction *position, unsigned count, const RHaction &value)
{
    typedef std::vector<RHaction> Actions;
    void (Actions::*insert)(RHaction *, unsigned, const RHaction &) = &Actions::insert;
    (actions.*insert)(position, count, value);
}

// TEMPLATE: GAME 0x004582d0 FOLDED
// ?insert@?$vector@W4RHaction@@V?$allocator@W4RHaction@@@std@@@std@@QAEXPAW4RHaction@@IABW43@@Z

class RHWidgetRequirements
{
public:
    static std::vector<RHaction> PurifyActions(const std::vector<RHaction> &actions);
};

// FUNCTION: GAME 0x005dd430
std::vector<RHaction> RHWidgetRequirements::PurifyActions(const std::vector<RHaction> &actions)
{
    std::vector<RHaction> result;
    for (std::vector<RHaction>::const_iterator it = actions.begin(); it != actions.end(); ++it)
    {
        if (std::find(result.begin(), result.end(), *it) == result.end())
            result.push_back(*it);
    }
    return result;
}

// TEMPLATE: GAME 0x005dda30
// ?_Xran@?$vector@W4RHaction@@V?$allocator@W4RHaction@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x005dd530
// ??1?$vector@URHPortraitQuickEntry@@V?$allocator@URHPortraitQuickEntry@@@std@@@std@@QAE@XZ

// TEMPLATE: GAME 0x005dd570
// ?size@?$vector@URHPortraitQuickEntry@@V?$allocator@URHPortraitQuickEntry@@@std@@@std@@QBEIXZ

void EmitPortraitQuickEntries(std::vector<RHPortraitQuickEntry> *entries)
{
    std::vector<RHPortraitQuickEntry>::size_type (std::vector<RHPortraitQuickEntry>::*size)() const = &std::vector<RHPortraitQuickEntry>::size;
    (entries->*size)();
    std::vector<RHPortraitQuickEntry> local;
    FUN_005df400(0);
}

#pragma inline_depth(0)
void EmitRHPortraitLifetimeConstructors()
{
    RHPortraitLifetime005db4a0 first;
}
#pragma inline_depth()

// Parked: the vector argument uses the constructor result instead of its stack address.
// STUB: GAME 0x0061d3f0
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d3f0(unsigned short line, int value)
{
    SBGeoBoundingBox2D box;
    SBGeoBoundingBox2D &bounds = m_position;
    float width = bounds.m_second.m_x - bounds.m_first.m_x;
    unsigned index = line;
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)RHMapBox(
        0.0f, (float)((unsigned)((SBUIListboxUnk0061d980 *)this)->m_4c->FUN_0061e890() * index),
        width - ((RHUnkFXDraw *)m_drawManager)->FUN_005e56c0(m_68),
        (float)((unsigned)((SBUIListboxUnk0061d980 *)this)->m_4c->FUN_0061e890() * (index + 1))));
    if (value & 0x1000)
    {
        box.m_10 = true;
        box.m_first.m_x += m_82;
    }
    return box.FUN_006090d0(SBGeoVector2D((const SBGeoVector2D &)bounds.m_first));
}

// FUNCTION: GAME 0x0061d570
bool RHPortraitInputRenderer::FUN_0061d570(unsigned short position, int value)
{
    unsigned short limit = (unsigned short)value;
    *(unsigned short *)((char *)this + 0x80) = limit;
    unsigned short visible = (unsigned short)FUN_0061d5e0();
    if (visible > limit)
    {
        *(float *)((char *)this + 0x74) = 1.0f;
        *(float *)((char *)this + 0x78) = 0.0f;
    }
    else
    {
        *(float *)((char *)this + 0x74) = (float)visible / limit;
        *(float *)((char *)this + 0x78) = (float)position / limit;
    }
    return true;
}

// Parked: repeated-height evaluation, right-edge spills and EH-state scheduling differ.
// STUB: GAME 0x0061d620
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d620()
{
    SBGeoBoundingBox2D box;
    float height = m_position.m_second.m_y - m_position.m_first.m_y;
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)RHMapBox(
        0.0f, (height - 2.0f) * *(float *)((char *)this + 0x78),
        ((RHUnkFXDraw *)m_drawManager)->FUN_005e56c0(m_64),
        (m_position.m_second.m_y - m_position.m_first.m_y - 2.0f) *
        (*(float *)((char *)this + 0x74) + *(float *)((char *)this + 0x78))));
    float right = m_position.m_second.m_x;
    float top = m_position.m_first.m_y + 1.0f;
    right -= 1.0f;
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)box.FUN_006090d0(
        SBGeoVector2D(right - ((RHUnkFXDraw *)m_drawManager)->FUN_005e56c0(m_64), top)));
    return box;
}

// FUNCTION: GAME 0x0061d7c0
SBGeoBoundingBox2D RHPortraitInputRenderer::FUN_0061d7c0()
{
    SBGeoBoundingBox2D box;
    if (m_68 == -1)
        return SBGeoBoundingBox2D(0.0f, 0.0f, 0.0f, 0.0f);
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)RHMapBox(
        0.0f, 0.0f, ((RHUnkFXDraw *)m_drawManager)->FUN_005e56c0(m_68),
        m_position.m_second.m_y - m_position.m_first.m_y));
    float top = m_position.m_first.m_y;
    float right = m_position.m_second.m_x;
    ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)box.FUN_006090d0(
        SBGeoVector2D(right - ((RHUnkFXDraw *)m_drawManager)->FUN_005e56c0(m_68), top)));
    return box;
}
