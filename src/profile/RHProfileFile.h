#ifndef RHPROFILEFILE_H
#define RHPROFILEFILE_H

#include "RHProfileManager.h"
#include "RHProfileFileCore.h"

unsigned long FUN_005e1d00(SBFile &file);
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
bool FUN_005e2020(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
void FUN_005e2300(SBFile &file);
RHProfileText operator+(const RHProfileText &first, const RHProfileText &second);

#endif
