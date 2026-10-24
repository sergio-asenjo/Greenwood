// RHMenuShortMissionDescription — declarations for
// RHMenuShortMissionDescription.cpp (decompiled TU).
//
// BINDING: the code run 0x00540730..0x005412cb sits between two per-TU
// <iostream> init glue groups (0x005406b0 / 0x005412f0) and owns the vtable
// 0x00679940 (deleting dtor 0x00540830). Unlike its focus-managed siblings it
// derives directly from RHMenuWindow (its constructor calls 0x00543e70) and
// has no RouteEvent override (slot 0x00679990 is the base 0x0048a970),
// matching the Mac oracle's RHMenuShortMissionDescription, which has no
// HandleEvent/RouteEvent (symbols/mac-RH.txt:3006-3013).
//
// Layout (from 0x00540730 / 0x00540850 / 0x00540d20):
//   +0x378  owned object released through 0x0044eeb0 + operator delete

#ifndef RHMENUSHORTMISSIONDESCRIPTION_H
#define RHMENUSHORTMISSIONDESCRIPTION_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"

#include "RHMenuShortMissionBlazons.h"

typedef RHGameRenderer0060dbc0 RHMenuShortMissionRenderer;

// SIZE 0x100
#include "RHMenuShortMissionTitle.h"

typedef RHGameLifetime00515f00 RHMenuShortMissionText;

// SIZE 0xd0
typedef RHGameLifetime0044fe90 RHMenuShortMissionPicture;

// SIZE 0x380
// VTABLE: GAME 0x00679940
class RHMenuShortMissionDescription : public RHMenuWindow
{
public:
    RHMenuShortMissionDescription(RHMenuWindowScreen *screen);
    ~RHMenuShortMissionDescription();
    void *FUN_00540830(unsigned flags);
    void FUN_00540d20();
    std::wstring FUN_00540d50();

    RHMenuShortMissionTitle m_title; // 0xc8
    RHMenuShortMissionText m_text; // 0x1c8
    RHMenuShortMissionPicture m_picture; // 0x294
    SBGeoBoundingBox2D m_box; // 0x364
    RHMenuShortMissionBlazons *m_blazons; // 0x378
    void *m_mission; // 0x37c
};

#endif
