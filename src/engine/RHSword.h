// Declarations shared by RHSword.cpp (the decompiled TU) and RHSword_stubs.cpp
// (external-symbol stubs). Kept minimal and evidence-driven; member layout is
// only what the target instructions actually touch.

#include "SB.h"

class RHSword
{
public:
    RHSword();
    ~RHSword();
    virtual bool Serialize(SBFile &file);
    int m_unk4;

    static bool SerializePointer(SBFile &file, RHSword *&ptr);
};
