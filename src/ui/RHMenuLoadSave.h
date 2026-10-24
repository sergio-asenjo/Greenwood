// RHMenuLoadSave — declarations for RHMenuLoadSave.cpp (decompiled TU).
//
// BINDING: the vtable 0x00679570 holds the deleting dtor 0x005304f0 (slot 0) and the
// RouteEvent override 0x00530180 (slot 20, calling HandleEvent 0x005301a0 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuIntro and RHMenuMissionDescription (which holds 0x00535950); per-TU <iostream> init glue bounds the code run 0x00530180... Class name from
// that position and the handler set (symbols/mac-RH.txt RHMenuLoadSave (20 methods)).

#ifndef RHMENULOADSAVE_H
#define RHMENULOADSAVE_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"

// SIZE 0x8c8
class RHMenuLoadSave : public RHMenuWindowFocus
{
public:
    ~RHMenuLoadSave();
    void FUN_00530180(RHMenuEvent *event);
    bool FUN_005301a0(RHMenuEvent *event);
    void *FUN_005304f0(unsigned flags);
    RHMenuLoadSave(RHMenuScreenView *screen, bool save);
    void FUN_005307d0();
    static RHMenuLoadSaveResult FUN_00531110(RHMenuWindowUI *ui, bool save);
    int FUN_00531220();
    int FUN_00531230();
    void FUN_00531240();
    void FUN_00531a80();
    void FUN_00531bd0();
    bool FUN_00463d80(int msg, void *widget, void *data);
    bool FUN_005314d0(int msg, void *widget, void *data);
    bool FUN_005316a0(int msg, void *widget, void *data);
    bool FUN_00531710(int msg, void *widget, void *data);
    bool FUN_00531720(int msg, void *widget, void *data);
    bool FUN_00531740(int msg, void *widget, void *data);

    undefined m_140[0x37c]; // 0x140
    int m_fieldState; // 0x4bc
    undefined m_4c0[0x40]; // 0x4c0
    int m_500; // 0x500
    int m_504; // 0x504
    undefined m_508[0x48]; // 0x508
    undefined m_field[0x48]; // 0x550
    int m_598; // 0x598
    undefined m_59c[0x32c]; // 0x59c
};

class RHMenuLoadSaveListBase
{
public:
    void FUN_00531d60();
    int FUN_00531e50();
    undefined m_00[0x18a];
    unsigned short m_18a;
    unsigned short m_18c;
};

class RHMenuLoadSaveMap
{
public:
    RHUnk00514e10::Pair FUN_00531d80(const RHUnk00514e10::Value &value);
    RHUnk00514e10 m_tree;
};

class RHMenuLoadSaveEntry
{
public:
    RHMenuLoadSaveEntry(const int &key, const int &value);
    int m_key;
    int m_value;
};

class RHMenuLoadSaveListView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual unsigned long V24() = 0;
};

// VTABLE: GAME 0x00679608
class RHMenuLoadSaveText : public RHGameWidgetLifetimeBase
{
public:
    ~RHMenuLoadSaveText();
    void *FUN_00532cd0(unsigned flags);
    void FUN_00531e30();
    RHMenuEvent *FUN_00532040(unsigned value);
    int FUN_00533cd0(const SBGeoPoint2D &point);
    bool FUN_00533d80(const SBGeoPoint2D &point);
    RHPortraitInputRenderer m_renderer;
};

class RHMenuLoadSaveSlots
{
public:
    ~RHMenuLoadSaveSlots();
    void *FUN_00532cf0(unsigned flags);
    RHMenuEvent *FUN_00532d30(const SBGeoPoint2D &point);
};

class RHMenuLoadSaveList
{
public:
    ~RHMenuLoadSaveList();
    void *FUN_00532d10(unsigned flags);
};

#endif
