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
#include "RHMenuShortMissionDescription.h"

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

// VTABLE: GAME 0x006799f0
// SIZE 0xd8
class RHMenuSoundsSlider : public RHGameLifetime00515b40
{
public:
    RHMenuSoundsSlider();
    ~RHMenuSoundsSlider() {}
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

#include "RHPortraitLinkedLifetimeView.h"

class RHPortraitGroupLifetime
{
public:
    RHPortraitGroupLifetime();
    ~RHPortraitGroupLifetime();
    undefined m_00[0xcc];
};

#pragma inline_depth(0)
class __declspec(novtable) RHMenuSoundsTitle : public RHGameLifetime00525880
{
public:
    RHMenuSoundsTitle()
    {
        *(unsigned *)this = 0x006791a8;
        m_fc = true;
        m_fd = true;
    }

    bool m_fc;
    bool m_fd;
};
#pragma inline_depth()

// SIZE 0xc
#include "RHSoundConfig.h"
typedef RHSoundConfig RHMenuSoundsSettings;

// SIZE 0x119c
// VTABLE: GAME 0x00679998
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
    bool FUN_00543520(int msg, void *widget, void *data);
    bool FUN_00543750(int msg, void *widget, void *data);

    RHPortraitButton m_140;
    RHPortraitButton m_240;
    RHPortraitLinkedLifetime m_340;
    RHPortraitLinkedLifetime m_454;
    RHPortraitLinkedLifetime m_568;
    RHPortraitLinkedLifetime m_67c;
    RHPortraitGroupLifetime m_790;
    RHPortraitGroupLifetime m_85c;
    RHPortraitGroupLifetime m_928;
    RHPortraitGroupLifetime m_9f4;
    RHPortraitGroupLifetime m_ac0;
    RHMenuShortMissionTitle m_b8c;
    RHMenuShortMissionTitle m_c8c;
    RHMenuShortMissionTitle m_d8c;
    RHMenuShortMissionTitle m_e8c;
    RHMenuShortMissionTitle m_f8c;
    RHMenuSoundsTitle m_108c;
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
