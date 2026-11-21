#ifndef RHSWORD_H
#define RHSWORD_H

// Declarations shared by RHSword.cpp (the decompiled TU) and RHSword_stubs.cpp
// (external-symbol stubs). Kept minimal and evidence-driven; member layout is
// only what the target instructions actually touch.

#include "SB.h"

class RHHtHWeaponProfile;

class __declspec(novtable) RHSword
{
public:
    RHSword();
    ~RHSword();
    virtual bool Serialize(SBFile &file);
    const RHHtHWeaponProfile *m_profile;
    unsigned short GetRange(int index) const;
    int FUN_005c2130(float value, int first, int second);
    char FUN_005c1b60() const;
    unsigned short FUN_005c1f90(int index) const;
    unsigned short FUN_005c1fb0(int index) const;

    static bool SerializePointer(SBFile &file, RHSword *&ptr);
};

#endif
