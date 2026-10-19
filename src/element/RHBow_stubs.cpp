#include "SBNullstr.h"
#include "RHBow.h"
#include "RHWeapon.h"

// Kept out of line so the `new RHBow` cleanup EH frame stays in SerializePointer.
// FUNCTION: GAME 0x00450020
RHBow::RHBow()
{
    ((RHWeapon *)this)->RHWeapon::RHWeapon();
    m_04 = 0;
    *(unsigned *)this = 0x0067765c;
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
