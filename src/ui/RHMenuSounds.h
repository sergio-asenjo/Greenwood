// RHMenuSounds — declarations for RHMenuSounds.cpp (decompiled TU).
//
// BINDING: the code run 0x00541370..0x00543dbb sits between two per-TU
// <iostream> init glue groups (0x005412f0 / 0x00543df0) and owns the vtable
// 0x00679998 (deleting dtor 0x00541780, RouteEvent 0x00541370) plus the
// 0xd8-byte widget vtable 0x006799f0 (vector deleting dtor 0x00543a90, ctor
// 0x00543af0). The handler at 0x00543750 copies a 12-byte block at +0x118c
// into the active profile's +0x44 sound settings, matching the Mac oracle's
// RHMenuSounds (OnCancel/OnChange/OnOK/SynchronizeWidgets,
// symbols/mac-RH.txt:3014-3023).
//
// Layout (from 0x00543750):
//   +0x118c  12-byte sound settings copy
//   +0x1198  bool, settings changed

#ifndef RHMENUSOUNDS_H
#define RHMENUSOUNDS_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"

// SIZE 0xc
struct RHMenuSoundsInput : public SBGeoPoint2D
{
    short m_08; // 0x08
    unsigned char m_buttons; // 0x0a
};

// SIZE 0x10
struct RHMenuSoundsEvent
{
    int m_type; // 0x00
    void *m_widget; // 0x04
    void *m_data; // 0x08
    int m_0c; // 0x0c
};

class RHMenuSoundsSliderBase : public RHGameWidgetLifetimeBase
{
public:
    RHMenuSoundsSliderBase() {}
    RHGameRenderer0060dad0 m_renderer; // 0x80
};

// SIZE 0xd8
class RHMenuSoundsSlider : public RHMenuSoundsSliderBase
{
public:
    RHMenuSoundsSlider();
    RHMenuSoundsEvent *FUN_00543bb0(const RHMenuSoundsInput &input);
    RHMenuSoundsEvent *MakeEvent(int type);
    int FUN_00543d10();

    // FUNCTION: GAME 0x00543dc0
    void FUN_00543dc0(RHMenuSoundsSlider *stop)
    {
        if (stop != this)
        {
            m_highlighted = false;
            if (m_parent)
                m_parent->FUN_00543dc0(stop);
        }
    }

    RHMenuSoundsSlider *m_parent; // 0xd0
    bool m_highlighted; // 0xd4
};

// SIZE 0xc
struct RHMenuSoundsSettings
{
    unsigned long m_00; // 0x00
    unsigned long m_04; // 0x04
    unsigned long m_08; // 0x08
};

// SIZE 0x119c
class RHMenuSounds : public RHMenuWindowFocus
{
public:
    RHMenuSounds(void *screen);
    ~RHMenuSounds();
    void *FUN_00541780(unsigned flags);
    void FUN_00541a90();
    static bool FUN_00543460(void *ui);
    void FUN_00541370(RHMenuEvent *event);
    bool FUN_00541390(RHMenuEvent *event);
    bool FUN_0052ce80(int msg, void *widget, void *data);
    bool FUN_00543520(int msg, void *widget, void *data);
    bool FUN_00543750(int msg, void *widget, void *data);

    undefined m_140[0x100]; // 0x140
    undefined m_240[0x100]; // 0x240
    undefined m_340[0x114]; // 0x340
    undefined m_454[0x114]; // 0x454
    undefined m_568[0x114]; // 0x568
    undefined m_67c[0x114]; // 0x67c
    undefined m_790[0xcc]; // 0x790
    undefined m_85c[0xcc]; // 0x85c
    undefined m_928[0xcc]; // 0x928
    undefined m_9f4[0xcc]; // 0x9f4
    undefined m_ac0[0x6cc]; // 0xac0
    RHMenuSoundsSettings m_settings; // 0x118c
    bool m_changed; // 0x1198
};

#define m_sliderBox (*(SBGeoBoundingBox2D *)((char *)this + 0x30))
#define m_sliderEvent (*(RHMenuSoundsEvent *)((char *)this + 0x4c))
#define m_sliderVisible (*(bool *)((char *)this + 0x04))

inline RHMenuSoundsEvent *RHMenuSoundsSlider::MakeEvent(int type)
{
    m_sliderEvent.m_type = type;
    m_sliderEvent.m_widget = this;
    m_sliderEvent.m_data = 0;
    m_sliderEvent.m_0c = 0;
    return &m_sliderEvent;
}
#define m_sliderEnabled (*(bool *)((char *)this + 0x06))

#endif
