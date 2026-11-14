#ifndef RHELEMENTSCROLL_H
#define RHELEMENTSCROLL_H

#include "RHElementBonus.h"
#include "Decomp.h"
#include <string>

#include "RHUnkSectorScript.h"
#include "RHEngine.h"
#include "RHElementScrollCore.h"

void RHSerializeName(SBFile &file, const char *name);
#include "RHEngineWidenedCalls.h"
bool FUN_005e0c90(SBFile &file, std::string &value);
extern char g_unk0x6c0691;
extern RHElementScroll *g_scrollExecutingScript;
#include "RHPlayerProfileManagerStorage.h"

#endif
