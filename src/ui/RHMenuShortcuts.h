// RHMenuShortcuts — declarations for RHMenuShortcuts.cpp (decompiled TU).
//
// BINDING: the code run 0x0053fae0..0x005406ab sits between two per-TU
// <iostream> init glue groups (0x0053fa50 / 0x005406b0) and owns the vtable
// 0x006798e8 (deleting dtor 0x0053fca0, RouteEvent 0x0053fae0). Its handlers
// copy an RHKeyConfig at +0x868 to/from the active profile's key configs
// (+0x34 / +0x3c, the same block RHGameInputTranslator::ReflectActiveKeyConfig
// reads) and reset it with RHKeyConfig::SetToPreset(0 / 1, flag), matching the
// Mac oracle's RHMenuShortcuts (OnDefault1/OnDefault2/OnOK/OnUserDefined,
// symbols/mac-RH.txt:2995-3005).
//
// Layout (from 0x00540540..0x00540650):
//   +0x640  key list widget (0x005ced90)
//   +0x850  bool, user-defined set active
//   +0x868  RHKeyConfig being edited
//   +0x870  active profile (key configs at +0x34 / +0x3c)

#ifndef RHMENUSHORTCUTS_H
#define RHMENUSHORTCUTS_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "../engine/RHGameInputTranslator.h"
#include "../engine/RHKeyConfig.h"

class RHMenuShortcutsKeys : public RHKeyConfig
{
public:
    RHMenuShortcutsKeys(const RHKeyConfig &other) : RHKeyConfig(other) {}
    RHMenuShortcutsKeys &FUN_0051ebf0(const RHKeyConfig &other);
};

// SIZE 0x44
class RHMenuShortcutsProfile
{
public:
    undefined m_00[0x34]; // 0x00
    RHMenuShortcutsKeys m_keys34; // 0x34
    RHMenuShortcutsKeys m_keys3c; // 0x3c
};

// SIZE 0x210
class RHMenuShortcutsList
{
public:
    RHMenuShortcutsList();
    ~RHMenuShortcutsList();
    void FUN_005ced90();

    undefined m_00[0x210]; // 0x00
};

extern bool g_unk0x6c069c;
class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

// SIZE 0x874
class RHMenuShortcuts : public RHMenuWindowFocus
{
public:
    RHMenuShortcuts(void *screen);
    ~RHMenuShortcuts();
    void *FUN_0053fca0(unsigned flags);
    void FUN_0053fdd0();
    static void FUN_00540480(void *ui);
    void FUN_0053fae0(RHMenuEvent *event);
    bool FUN_0053fb00(RHMenuEvent *event);
    bool FUN_0052ce80(int msg, void *widget, void *data);
    bool FUN_00540540(int msg, void *widget, void *data);
    bool FUN_00540590(int msg, void *widget, void *data);
    bool FUN_005405e0(int msg, void *widget, void *data);
    bool FUN_00540650(int msg, void *widget, void *data);

    RHPortraitButton m_button140; // 0x140
    RHPortraitButton m_button240; // 0x240
    RHPortraitButton m_button340; // 0x340
    RHPortraitButton m_button440; // 0x440
    RHPortraitButton m_button540; // 0x540
    RHMenuShortcutsList m_list; // 0x640
    bool m_userDefined; // 0x850
    undefined m_851[0x17]; // 0x851
    RHMenuShortcutsKeys m_keys; // 0x868
    RHMenuShortcutsProfile *m_profile; // 0x870
};

#endif
