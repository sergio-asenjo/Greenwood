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

#include "RHMenuShortMissionDescriptionCore.h"

#endif
