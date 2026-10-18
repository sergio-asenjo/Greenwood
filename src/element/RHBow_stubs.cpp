#include "SBNullstr.h"
#include "RHBow.h"

// 0x00450020 is RHBow's default ctor; unmarked (not a counted row).
// Kept out of line so the `new RHBow` cleanup EH frame stays in SerializePointer.
RHBow::RHBow()
{
    m_04 = 0;
}

RHBow::~RHBow() {}

// FUNCTION: GAME 0x004504b0
int RHBow::FUN_004504b0(float value) const
{
    if (FUN_00450070(0) >= value)
        return 0;
    return 1;
}

void EmitRHBow(RHBow *bow)
{
    int (RHBow::*f)(float) const = &RHBow::FUN_004504b0;
    (bow->*f)(0.0f);
}
