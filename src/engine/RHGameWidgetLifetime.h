#ifndef RHGAMEWIDGETLIFETIME_H
#define RHGAMEWIDGETLIFETIME_H

#include "Decomp.h"
#include "RHPortraitRenderer0060dab0.h"
#include <string>
#include <map>
#include "RHPortraitUnk005d3880.h"

class SBGeoBoundingBox2D;
struct RHPortraitWidgetInput;

// VTABLE: GAME 0x0067a630
// SIZE 0x80
class RHGameWidgetLifetimeBase
{
public:
    RHGameWidgetLifetimeBase();
    RHGameWidgetLifetimeBase(const RHGameWidgetLifetimeBase &other);
    ~RHGameWidgetLifetimeBase();
    RHGameWidgetLifetimeBase &operator=(const RHGameWidgetLifetimeBase &other);
    virtual void *FUN_005dee10(unsigned flags);
    virtual void AttachWidget(unsigned int display);
    virtual void ReleaseWidget();
    virtual void DrawWidget();
    virtual void ResetWidget();
    virtual unsigned long *UpdateWidget(unsigned index);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);
    virtual void SetWidgetBounds(const SBGeoBoundingBox2D &box);
    virtual void SetWidgetPosition(const SBGeoPoint2D &position);
    virtual int WidgetState();
    virtual void SetWidgetResource(long id);
    virtual void SetWidgetText(const std::wstring &text);
    virtual bool Create(const std::wstring &text, const SBGeoBoundingBox2D &box, unsigned long flags, long id);
    virtual unsigned SelectWidgetResource(unsigned id);

    RHPortraitRenderer0060d470 &BitmapRenderer();
    SBGeoBoundingBox2D &WidgetBounds();
    unsigned long *MakeWidgetFrame(unsigned index);
    bool ContainsWidgetPoint(const SBGeoPoint2D &point);
    RHPortraitWidgetEvent *MakeWidgetEvent(int type);
    void SetScrollFirst(int value) { *(int *)((char *)this + 0xd4) = value; }
    void SetScrollSecond(int value) { *(int *)((char *)this + 0xd8) = value; }
    void SetQuickActionFirst(int value) { *(int *)((char *)this + 0xdc) = value; }
    void SetQuickActionSecond(int value) { *(int *)((char *)this + 0xe0) = value; }
    void SetQuickActionThird(int value) { *(int *)((char *)this + 0xe8) = value; }
    void SetQuickActionFourth(int value) { *(int *)((char *)this + 0xe4) = value; }

    bool Create(const std::wstring &name, const SBGeoBoundingBox2D &box, unsigned long flags);
    void FUN_0060d290(const SBGeoPoint2D &position);
    bool m_04;
    bool m_05;
    bool m_06;
    bool m_07;
    bool m_08;
    short m_0a;
    unsigned long m_0c;
    std::wstring m_10;
    std::wstring m_20;
#ifdef SBGEO_BOUNDINGBOX2D_VIEW
    const SBGeoBoundingBox2D &Box() const { return m_30; }
    SBGeoBoundingBox2D m_30;
#else
    undefined m_30[0x14];
#endif
    unsigned long m_44;
    unsigned long m_48;
    RHPortraitWidgetEvent m_event;
    unsigned long m_5c;
#ifdef SBGEO_BOUNDINGBOX2D_VIEW
    SBGeoBoundingBox2D m_60;
#else
    undefined m_60[0x14];
#endif
    unsigned long m_74;
    unsigned long m_78;
    int m_state;
};

typedef RHPortraitRenderer0060dab0 RHGameRenderer0060dad0;

class SBDrawManager;

// VTABLE: GAME 0x0067a620
class RHGameRenderer0060da10 : public RHPortraitRenderer0060d470
{
public:
    RHGameRenderer0060da10();
    ~RHGameRenderer0060da10();
    RHGameRenderer0060da10 &operator=(const RHGameRenderer0060da10 &other);
    RHGameRenderer0060da10 &Assign(const RHGameRenderer0060da10 &other);
};

class RHGameRenderer0060dab0
{
public:
    RHGameRenderer0060dab0();
    ~RHGameRenderer0060dab0();
    undefined m_data[0x4c];
};

#include "RHPopupRenderer0060dbc0.h"

typedef RHPopupRenderer0060dbc0 RHGameRenderer0060dbc0;

enum SBResourceWidgetID
{
};

// SIZE 0x74
class RHUIRendererBlinking : public RHGameRenderer0060da10
{
public:
    struct BlinkingItem
    {
        BlinkingItem() {}
        unsigned long m_period;
        SBResourceWidgetID m_first;
        SBResourceWidgetID m_second;
    };
    RHUIRendererBlinking();
    ~RHUIRendererBlinking();
    void SetBlinking(SBResourceWidgetID, SBResourceWidgetID, SBResourceWidgetID, unsigned long);
    void RemoveBlinking(SBResourceWidgetID);
    void *FUN_005c9250(unsigned flags);
    bool FUN_005c9320(unsigned id);
    BlinkingItem m_current;
    unsigned m_currentId;
    unsigned m_frame;
    bool m_active;
    char m_61[3];
    std::map<SBResourceWidgetID, BlinkingItem> m_items;
};

typedef RHUIRendererBlinking RHGameRenderer005c9270;
typedef RHGameWidgetLifetimeBase RHPortraitBitmapWidget;

// VTABLE: GAME 0x00678ce0
class RHGameLifetime00515b40 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00515b40() {}
    ~RHGameLifetime00515b40() {}
    RHGameLifetime00515b40 &operator=(const RHGameLifetime00515b40 &other);
    RHGameLifetime00515b40 &Assign(const RHGameLifetime00515b40 &other);
    virtual void *FUN_005dee10(unsigned flags);
    virtual void DrawWidget();
    virtual unsigned SelectWidgetResource(unsigned id);
    RHGameRenderer0060dad0 m_renderer;
};

// VTABLE: GAME 0x00678c48
class RHGameLifetime00515d30 : public RHGameLifetime00515b40
{
public:
    RHGameLifetime00515d30() { m_state = 0; }
    ~RHGameLifetime00515d30() {}
    virtual void *FUN_005dee10(unsigned flags);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);
    virtual int WidgetState();
    virtual void SetWidgetResource(long id);
    virtual RHPortraitWidgetEvent *LeaveWidget(const RHPortraitWidgetInput &input);
    virtual RHPortraitWidgetEvent *EnterWidget(const RHPortraitWidgetInput &input);
    virtual RHPortraitWidgetEvent *ReleaseWidgetButton(const RHPortraitWidgetInput &input);
    virtual RHPortraitWidgetEvent *PressWidgetButton(const RHPortraitWidgetInput &input);
    virtual RHPortraitWidgetEvent *OtherWidgetButton(const RHPortraitWidgetInput &input);
    virtual bool ContainsWidgetInput(const RHPortraitWidgetInput &input);
    virtual long WidgetResource();
    virtual bool SetWidgetEnabled(char enabled);
};

// VTABLE: GAME 0x00678fc8
class RHGameLifetime005161a0 : public RHGameLifetime00515b40
{
public:
    RHGameLifetime005161a0() {}
    ~RHGameLifetime005161a0() {}
    RHGameLifetime005161a0 &operator=(const RHGameLifetime005161a0 &other);
    void *FUN_005173e0(unsigned flags);
};

// VTABLE: GAME 0x00677624
class RHGameLifetime00517590 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00517590() {}
    ~RHGameLifetime00517590() {}
    RHGameLifetime00517590 &operator=(const RHGameLifetime00517590 &other);
    RHGameLifetime00517590 &Assign(const RHGameLifetime00517590 &other);
    virtual void *FUN_005dee10(unsigned flags);
    RHGameRenderer0060da10 m_renderer;
};

// VTABLE: GAME 0x00678c10
class RHGameLifetime00515f00 : public RHGameLifetime00517590
{
public:
    RHGameLifetime00515f00() {}
    ~RHGameLifetime00515f00() {}
    RHGameLifetime00515f00 &operator=(const RHGameLifetime00515f00 &other);
    virtual void *FUN_005dee10(unsigned flags);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);
    virtual int WidgetState();
};

class RHGameLifetime0044fe90 : public RHGameLifetime00515f00
{
public:
    // FUNCTION: GAME 0x0044fca0
    RHGameLifetime0044fe90()
    {
        *(unsigned *)this = 0x006775e4;
        m_cc = 0;
    }
    ~RHGameLifetime0044fe90() {}
    RHGameLifetime0044fe90 &operator=(const RHGameLifetime0044fe90 &other);
    int m_cc;
};

// VTABLE: GAME 0x00678b60
class RHGameLifetime00516430 : public RHGameLifetime00517590
{
public:
    RHGameLifetime00516430() { m_state = 0; }
    ~RHGameLifetime00516430() {}
    virtual void *FUN_005dee10(unsigned flags);
};

// VTABLE: GAME 0x00678e50
class RHGameLifetime00516750 : public RHGameLifetime00517590
{
public:
    RHGameLifetime00516750();
    ~RHGameLifetime00516750() {}
    void *FUN_00517420(unsigned flags);
    unsigned m_strategy;
    int m_value;
};

// VTABLE: GAME 0x00679000
class RHGameLifetime00516a60 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00516a60() {}
    ~RHGameLifetime00516a60() {}
    void *FUN_00517440(unsigned flags);
    RHGameRenderer005c9270 m_renderer;
};

// VTABLE: GAME 0x00678bb8
class RHGameLifetime00516c50 : public RHGameLifetime00516a60
{
public:
    ~RHGameLifetime00516c50() {}
    void *FUN_00517460(unsigned flags);
};

// VTABLE: GAME 0x006791e0
class RHGameLifetime00525880 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00525880();
    enum BaseExpansion { InlineBase };
    explicit RHGameLifetime00525880(BaseExpansion) {}
    ~RHGameLifetime00525880() {}
    virtual void *FUN_005dee10(unsigned flags);
    virtual void DrawWidget();
    virtual unsigned SelectWidgetResource(unsigned id);
    RHGameRenderer0060dbc0 m_renderer;
};

// VTABLE: GAME 0x006791a8
class RHGameLifetime00525560 : public RHGameLifetime00525880
{
public:
    RHGameLifetime00525560() : RHGameLifetime00525880(InlineBase)
    {
        m_fc = true;
        m_fd = true;
    }
    enum BaseConstruction { SeparateBase };
    explicit RHGameLifetime00525560(BaseConstruction)
    {
        m_fc = true;
        m_fd = true;
    }
    ~RHGameLifetime00525560() {}
    virtual void *FUN_005dee10(unsigned flags);
    virtual void ResetWidget();
    virtual unsigned long *UpdateWidget(unsigned index);
    virtual RHPortraitWidgetEvent *HandleWidget(const RHPortraitWidgetInput &input);
    virtual int WidgetState();
    virtual void SetWidgetText(const std::wstring &text);
    bool m_fc;
    bool m_fd;
};

#endif
