#ifndef RHGAMEWIDGETLIFETIME_H
#define RHGAMEWIDGETLIFETIME_H

#include "Decomp.h"
#include "RHPortraitRenderer0060dab0.h"
#include <string>
#include <map>

class SBGeoBoundingBox2D;

// VTABLE: GAME 0x0067a630
// SIZE 0x80
class RHGameWidgetLifetimeBase
{
public:
    RHGameWidgetLifetimeBase();
    ~RHGameWidgetLifetimeBase();
    virtual void *FUN_005dee10(unsigned flags);
    bool Create(const std::wstring &name, const SBGeoBoundingBox2D &box, unsigned long flags);
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
    undefined m_44[8];
    unsigned long m_4c[4];
    undefined m_5c[4];
#ifdef SBGEO_BOUNDINGBOX2D_VIEW
    SBGeoBoundingBox2D m_60;
#else
    undefined m_60[0x14];
#endif
    undefined m_74[8];
    int m_state;
};

typedef RHPortraitRenderer0060dab0 RHGameRenderer0060dad0;

class SBUIUnk006006f0;
class RHUnk005ef320;

class RHGameRenderer0060da10
{
public:
    RHGameRenderer0060da10();
    ~RHGameRenderer0060da10();
    undefined4 m_vptr;
    SBUIUnk006006f0 *m_resource;
    undefined m_box[0x14];
    RHUnk005ef320 *m_draw;
    unsigned long m_target;
    undefined m_24[0x14];
    long m_resourceId;
    undefined m_3c[4];
    long m_40;
    long m_44;
    undefined m_48[4];
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

class SBResourceWidgetID
{
public:
    int m_value;
    bool operator<(const SBResourceWidgetID &other) const
    {
        return m_value < other.m_value;
    }
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
    BlinkingItem m_current;
    unsigned m_currentId;
    unsigned m_frame;
    bool m_active;
    char m_61[3];
    std::map<SBResourceWidgetID, BlinkingItem> m_items;
};

typedef RHUIRendererBlinking RHGameRenderer005c9270;

// VTABLE: GAME 0x00678ce0
class RHGameLifetime00515b40 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00515b40() {}
    ~RHGameLifetime00515b40() {}
    void *FUN_00517280(unsigned flags);
    RHGameRenderer0060dad0 m_renderer;
};

// VTABLE: GAME 0x00678c48
class RHGameLifetime00515d30 : public RHGameLifetime00515b40
{
public:
    ~RHGameLifetime00515d30() {}
    void *FUN_005172a0(unsigned flags);
};

// VTABLE: GAME 0x00678fc8
class RHGameLifetime005161a0 : public RHGameLifetime00515b40
{
public:
    RHGameLifetime005161a0() {}
    ~RHGameLifetime005161a0() {}
    void *FUN_005173e0(unsigned flags);
};

// VTABLE: GAME 0x00677624
class RHGameLifetime00517590 : public RHGameWidgetLifetimeBase
{
public:
    RHGameLifetime00517590() {}
    ~RHGameLifetime00517590() {}
    virtual void *FUN_005dee10(unsigned flags);
    RHGameRenderer0060da10 m_renderer;
};

class RHGameLifetime0044fe90 : public RHGameLifetime00517590
{
public:
    // FUNCTION: GAME 0x0044fca0
    RHGameLifetime0044fe90()
    {
        *(unsigned *)this = 0x006775e4;
        m_cc = 0;
    }
    ~RHGameLifetime0044fe90() {}
    int m_cc;
};

// VTABLE: GAME 0x00678c10
class RHGameLifetime00515f00 : public RHGameLifetime00517590
{
public:
    RHGameLifetime00515f00() {}
    ~RHGameLifetime00515f00() {}
    void *FUN_005172c0(unsigned flags);
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
    ~RHGameLifetime00525880() {}
    void *FUN_00525860(unsigned flags);
    RHGameRenderer0060dbc0 m_renderer;
};

class RHGameLifetime00525560 : public RHGameLifetime00525880
{
public:
    RHGameLifetime00525560()
    {
        *(unsigned *)this = 0x006791a8;
        m_fc = true;
        m_fd = true;
    }
    ~RHGameLifetime00525560() {}
    void *FUN_005258e0(unsigned flags);
    bool m_fc;
    bool m_fd;
};

#endif
