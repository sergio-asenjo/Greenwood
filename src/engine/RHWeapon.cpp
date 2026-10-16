#include "RHWeapon.h"

// FUNCTION: GAME 0x005cc510
RHWeapon::RHWeapon()
{
    m_vptr = 0x00679edc;
}

void EmitRHWeapon(RHWeapon *weapon)
{
    weapon->RHWeapon::RHWeapon();
}
