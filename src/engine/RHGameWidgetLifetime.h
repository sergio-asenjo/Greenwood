#ifndef RHGAMEWIDGETLIFETIME_H
#define RHGAMEWIDGETLIFETIME_H

#include "Decomp.h"
#include "RHPortraitRenderer0060dab0.h"

class RHGameWidgetLifetimeBase
{
public:
    RHGameWidgetLifetimeBase();
    ~RHGameWidgetLifetimeBase();
    virtual void FUN_0060d290(unsigned long hardware);
    undefined m_04[0x78];
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

#ifndef RHPOPUPRENDERER0060DBC0_VIEW
#define RHPOPUPRENDERER0060DBC0_VIEW
// SIZE 0x7c
class RHPopupRenderer0060dbc0
{
public:
    RHPopupRenderer0060dbc0();
    ~RHPopupRenderer0060dbc0();
    bool FUN_0060dd10(unsigned id);
    undefined m_data[0x7c];
};
#endif

typedef RHPopupRenderer0060dbc0 RHGameRenderer0060dbc0;

class RHGameRenderer005c9270
{
public:
    RHGameRenderer005c9270();
    ~RHGameRenderer005c9270();
    undefined m_data[0x50];
};

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
    void *FUN_0044fef0(unsigned flags);
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
    ~RHGameLifetime00516430() {}
    void *FUN_00517400(unsigned flags);
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
