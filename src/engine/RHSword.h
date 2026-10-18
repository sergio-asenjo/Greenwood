// Declarations shared by RHSword.cpp (the decompiled TU) and RHSword_stubs.cpp
// (external-symbol stubs). Kept minimal and evidence-driven; member layout is
// only what the target instructions actually touch.

#include "SB.h"

class __declspec(novtable) RHSword
{
public:
    RHSword();
    ~RHSword();
    virtual bool Serialize(SBFile &file);
    int m_unk4;
    char FUN_005c1b60() const;
    unsigned short FUN_005c1f90(int index) const;
    unsigned short FUN_005c1fb0(int index) const;

    static bool SerializePointer(SBFile &file, RHSword *&ptr);
};
